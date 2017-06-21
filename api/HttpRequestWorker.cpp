#include "HttpRequestWorker.h"

#include <QDebug>

HttpRequestWorker::HttpRequestWorker(QObject* parent) : QObject(parent)
{
    qsrand(QDateTime::currentDateTime().toTime_t());

    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_manager_finished(QNetworkReply*)));
}

QString HttpRequestWorker::http_attribute_encode(QString attribute, QString input)
{
    bool utfEncoding = false;

    QString result = "";
    QByteArray input_c = input.toLocal8Bit();

    for(quint16 i = 0; i < input_c.length(); i++)
    {
        char c = input_c.at(i);
        if(c == '\\' || c == '/' || c == '\0' || c < ' ' || c > '~')
        {
            utfEncoding = true; /* Ignore and request UTF-8 version */
        }
        else if(c == '"')
        {
            result += "\\\"";
        }
        else
        {
            result += c;
        }
    }

    if(result.length() == 0)
    {
        utfEncoding = true;
    }

    if(!utfEncoding)
    {
        return QString("%1=\"%2\"").arg(attribute, result); /* Return simple version */
    }

    QString resultUtf8 = "";
    for(quint16 i = 0; i < input_c.length(); i++)
    {
        char c = input_c.at(i);
        if((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            resultUtf8 += c;
        }
        else
        {
            resultUtf8 += "%" + QString::number(static_cast<unsigned char>(input_c.at(i)), 16).toUpper();
        }
    }

    /* Return enhanced version with UTF-8 support */
    return QString("%1=\"%2\"; %1*=utf-8''%3").arg(attribute, result, resultUtf8);
}

void HttpRequestWorker::execute(HttpRequestInput* input)
{
    if(input)
    {
        m_response = "";
        m_networkError = QNetworkReply::NoError;
        m_error = "";

        QByteArray request_content = "";

        // decide on the variable layout

        if(input->files.length() > 0)
        {
            input->var_layout = LAYOUT_MULTIPART;
        }
        if(input->var_layout == LAYOUT_NOT_SET)
        {
            input->var_layout = input->httpMethod() == "GET" || input->httpMethod() == "HEAD" ? LAYOUT_ADDRESS : LAYOUT_URL_ENCODED;
        }


        // prepare request content

        QString boundary = "";

        if(input->var_layout == LAYOUT_ADDRESS || input->var_layout == LAYOUT_URL_ENCODED)
        {
            if(input->vars.count() > 0)
            {
                bool first = true;
                foreach(QString key, input->vars.keys())
                {
                    if(!first)
                    {
                        request_content.append("&");
                    }

                    first = false;

                    //                    request_content.append(QUrl::toPercentEncoding(key));
                    //                    request_content.append("=");
                    //                    request_content.append(QUrl::toPercentEncoding(input->vars.value(key)));

                    request_content.append(key);
                    request_content.append("=");
                    request_content.append(input->vars.value(key));
                }

                if(input->var_layout == LAYOUT_ADDRESS)
                {
                    input->setUrl(input->url() + "?" + request_content);
                    request_content = "";
                }
            }
        }
        else
        {
            boundary = "__-----------------------"
                    + QString::number(QDateTime::currentDateTime().toTime_t())
                    + QString::number(qrand());

            QString boundary_delimiter = "--";
            QString new_line = "\r\n";

            // add variables
            foreach(QString key, input->vars.keys())
            {
                // add boundary
                request_content.append(boundary_delimiter);
                request_content.append(boundary);
                request_content.append(new_line);

                // add header
                request_content.append("Content-Disposition: form-data; ");
                request_content.append(http_attribute_encode("name", key));
                request_content.append(new_line);
                request_content.append("Content-Type: text/plain");
                request_content.append(new_line);

                // add header to body splitter
                request_content.append(new_line);

                // add variable content
                request_content.append(input->vars.value(key));
                request_content.append(new_line);
            }

            // add files
            for (QList<HttpRequestInputFileElement>::iterator file_info = input->files.begin(); file_info != input->files.end(); file_info++) {
                QFileInfo fi(file_info->local_filename);

                // ensure necessary variables are available
                if(
                        file_info->local_filename == NULL || file_info->local_filename.isEmpty()
                        || file_info->variable_name == NULL || file_info->variable_name.isEmpty()
                        || !fi.exists() || !fi.isFile() || !fi.isReadable()
                        ) {
                    // silent abort for the current file
                    continue;
                }

                QFile file(file_info->local_filename);
                if(!file.open(QIODevice::ReadOnly))
                {
                    // silent abort for the current file
                    continue;
                }

                // ensure filename for the request
                if(file_info->request_filename == NULL || file_info->request_filename.isEmpty())
                {
                    file_info->request_filename = fi.fileName();
                    if(file_info->request_filename.isEmpty())
                    {
                        file_info->request_filename = "file";
                    }
                }

                // add boundary
                request_content.append(boundary_delimiter);
                request_content.append(boundary);
                request_content.append(new_line);

                // add header
                request_content.append(QString("Content-Disposition: form-data; %1; %2").arg(
                                           http_attribute_encode("name", file_info->variable_name),
                                           http_attribute_encode("filename", file_info->request_filename)
                                           ));
                request_content.append(new_line);

                if(file_info->mime_type != NULL && !file_info->mime_type.isEmpty())
                {
                    request_content.append("Content-Type: ");
                    request_content.append(file_info->mime_type);
                    request_content.append(new_line);
                }

                request_content.append("Content-Transfer-Encoding: binary");
                request_content.append(new_line);

                // add header to body splitter
                request_content.append(new_line);

                // add file content
                request_content.append(file.readAll());
                request_content.append(new_line);

                file.close();
            }

            // add end of body
            request_content.append(boundary_delimiter);
            request_content.append(boundary);
            request_content.append(boundary_delimiter);
        }


        qDebug() << input->url();

        // prepare connection

        QNetworkRequest request = QNetworkRequest(QUrl(input->url()));
        request.setRawHeader("User-Agent", "Agent name goes here");

        if(input->var_layout == LAYOUT_URL_ENCODED)
        {
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        }
        else if(input->var_layout == LAYOUT_MULTIPART)
        {
            request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=" + boundary);
        }

        if(input->httpMethod() == "GET")
        {
            m_manager->get(request);
        }
        else if(input->httpMethod() == "POST")
        {
            m_manager->post(request, request_content);
        }
        else if(input->httpMethod() == "PUT")
        {
            m_manager->put(request, request_content);
        }
        else if(input->httpMethod() == "HEAD")
        {
            m_manager->head(request);
        }
        else if(input->httpMethod() == "DELETE")
        {
            m_manager->deleteResource(request);
        }
        else
        {
            QBuffer buff(&request_content);
            m_manager->sendCustomRequest(request, input->httpMethod().toLatin1(), &buff);
        }
    }
}

void HttpRequestWorker::on_manager_finished(QNetworkReply *reply)
{
    m_networkError = reply->error();
    if(m_networkError == QNetworkReply::NoError)
    {
        m_response = reply->readAll();
        qDebug() << m_response;

        // Parse document
        QJsonDocument doc(QJsonDocument::fromJson(m_response));

        // Get JSON object
        QJsonObject json = doc.object();

        qDebug() << "sssssss"<< json;
        QJsonObject jsonMessage = json["message"].toObject();
        QJsonObject jsonBody = jsonMessage["body"].toObject();
        QJsonArray jsonTrackList = jsonBody["track_list"].toArray();
        QJsonObject jsonTrack = jsonTrackList.at(0).toObject()["track"].toObject();
        qDebug() << "sssss1111ss"<< jsonTrack;
        m_lyricsUrl = jsonTrack.value("track_share_url").toString();

        // Access properties
        qDebug() <<"dddddddddddddd------------------" << m_lyricsUrl;
    }
    else {
        m_error = reply->errorString();
    }

    reply->deleteLater();

    emit on_execution_finished(this);
}
