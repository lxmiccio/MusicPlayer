#include "HttpRequestWorker.h"

#include "Settings.h"

HttpRequestWorker::HttpRequestWorker(QObject* parent) : QObject(parent)
{
    qsrand(QDateTime::currentDateTime().toTime_t());

    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRequestFinished(QNetworkReply*)));
}

void HttpRequestWorker::albumInfoLastFm(const QString& artist, const QString& album)
{
    HttpRequestInput input("http://ws.audioscrobbler.com/2.0/", "GET");
    input.addParameter("method", "album.getinfo");
    input.addParameter("api_key", Settings::apiKeyLastFm());
    input.addParameter("artist", artist);
    input.addParameter("album", album);
    input.addParameter("format", "json");

    execute(input);
}

void HttpRequestWorker::artistInfoLastFm(const QString& artist)
{
    HttpRequestInput input("http://ws.audioscrobbler.com/2.0/", "GET");
    input.addParameter("method", "artist.getinfo");
    input.addParameter("api_key", Settings::apiKeyLastFm());
    input.addParameter("artist", artist);
    input.addParameter("format", "json");

    execute(input);
}

QString HttpRequestWorker::encodeAttribute(QString attribute, QString input)
{
    bool utfEncoding = false;

    QString result = "";
    QByteArray input_c = input.toLocal8Bit();

    for(quint16 i = 0; i < input_c.length(); ++i)
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
        /* Return simple version */
        return QString("%1=\"%2\"").arg(attribute, result);
    }

    QString resultUtf8 = "";
    for(quint16 i = 0; i < input_c.length(); ++i)
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

void HttpRequestWorker::execute(HttpRequestInput input)
{
    m_input = input;

    m_error = "";
    m_networkError = QNetworkReply::NoError;
    m_response = "";

    if(m_input.files().length() > 0)
    {
        input.setLayout(LAYOUT_MULTIPART);
    }
    if(m_input.layout() == LAYOUT_NOT_SET)
    {
        m_input.setLayout(m_input.httpMethod() == "GET" || m_input.httpMethod() == "HEAD" ? LAYOUT_ADDRESS : LAYOUT_URL_ENCODED);
    }

    QString boundary = "";
    QByteArray requestContent = "";

    if(m_input.layout() == LAYOUT_ADDRESS || m_input.layout() == LAYOUT_URL_ENCODED)
    {
        if(m_input.parameters().count() > 0)
        {
            bool first = true;
            foreach(QString key, m_input.parameters().keys())
            {
                if(!first)
                {
                    requestContent.append("&");
                }

                first = false;

                requestContent.append(key);
                requestContent.append("=");
                requestContent.append(m_input.parameter(key));

                //request_content.append(QUrl::toPercentEncoding(key));
                //request_content.append("=");
                //request_content.append(QUrl::toPercentEncoding(m_input.vars.value(key)));
            }

            if(m_input.layout() == LAYOUT_ADDRESS)
            {
                m_input.setUrl(m_input.url() + "?" + requestContent);
                requestContent = "";
            }
        }
    }
    else
    {
        boundary = "__-----------------------" + QString::number(QDateTime::currentDateTime().toTime_t()) + QString::number(qrand());

        QString boundaryDelimiter = "--";
        QString newLine = "\r\n";

        /* Add parameters */
        foreach(QString key, m_input.parameters().keys())
        {
            /* Add boundary */
            requestContent.append(boundaryDelimiter);
            requestContent.append(boundary);
            requestContent.append(newLine);

            /* Add header */
            requestContent.append("Content-Disposition: form-data; ");
            requestContent.append(encodeAttribute("name", key));
            requestContent.append(newLine);
            requestContent.append("Content-Type: text/plain");
            requestContent.append(newLine);

            /* Add header to body splitter */
            requestContent.append(newLine);

            /* Add variable content */
            requestContent.append(m_input.parameter(key));
            requestContent.append(newLine);
        }

        /* Add files */
        for(QList<HttpRequestInputFileElement>::iterator i_file = m_input.files().begin(); i_file != m_input.files().end(); ++i_file)
        {
            QFile file(i_file->localFilename);
            QFileInfo fileInfo(i_file->localFilename);

            if(i_file->localFilename.isEmpty() || i_file->variableName.isEmpty() || !fileInfo.exists() || !fileInfo.isFile() || !file.open(QIODevice::ReadOnly))
            {
                /* Skip the current file */
                continue;
            }

            if(i_file->requestFilename.isEmpty())
            {
                i_file->requestFilename = i_file->localFilename;
            }

            /* Add boundary */
            requestContent.append(boundaryDelimiter);
            requestContent.append(boundary);
            requestContent.append(newLine);

            /* Add header */
            requestContent.append(QString("Content-Disposition: form-data; %1; %2").arg(encodeAttribute("name", i_file->variableName), encodeAttribute("filename", i_file->requestFilename)));
            requestContent.append(newLine);

            /* Add mime type */
            if(!i_file->mimeType.isEmpty())
            {
                requestContent.append("Content-Type: ");
                requestContent.append(i_file->mimeType);
                requestContent.append(newLine);
            }

            requestContent.append("Content-Transfer-Encoding: binary");
            requestContent.append(newLine);

            /* Add header to body splitter */
            requestContent.append(newLine);

            /* Add file content */
            requestContent.append(file.readAll());
            requestContent.append(newLine);

            file.close();
        }

        /* Add end of the body */
        requestContent.append(boundaryDelimiter);
        requestContent.append(boundary);
        requestContent.append(boundaryDelimiter);
    }

    QNetworkRequest request = QNetworkRequest(QUrl(m_input.url()));
    request.setRawHeader("User-Agent", "Agent name goes here");

    if(m_input.layout() == LAYOUT_URL_ENCODED)
    {
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    }
    else if(m_input.layout() == LAYOUT_MULTIPART)
    {
        request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=" + boundary);
    }

    if(m_input.httpMethod() == "GET")
    {
        m_manager->get(request);
    }
    else if(m_input.httpMethod() == "POST")
    {
        m_manager->post(request, requestContent);
    }
    else if(m_input.httpMethod() == "PUT")
    {
        m_manager->put(request, requestContent);
    }
    else if(m_input.httpMethod() == "HEAD")
    {
        m_manager->head(request);
    }
    else if(m_input.httpMethod() == "DELETE")
    {
        m_manager->deleteResource(request);
    }
    else
    {
        QBuffer buffer(&requestContent);
        m_manager->sendCustomRequest(request, m_input.httpMethod().toLatin1(), &buffer);
    }
}

QByteArray HttpRequestWorker::response()
{
    return m_response;
}

HttpRequestInput HttpRequestWorker::input()
{
    return m_input;
}

bool HttpRequestWorker::isError()
{
    return m_networkError != QNetworkReply::NoError;
}

QNetworkReply::NetworkError HttpRequestWorker::error()
{
    return m_networkError;
}

QString HttpRequestWorker::errorMessage()
{
    return m_error;
}

void HttpRequestWorker::onRequestFinished(QNetworkReply* reply)
{
    m_networkError = reply->error();
    if(m_networkError == QNetworkReply::NoError)
    {
        m_response = reply->readAll();
    }
    else
    {
        m_error = reply->errorString();
    }

    reply->deleteLater();

    emit requestFinished(this);
}

QString HttpRequestWorker::coverUrl()
{
    QJsonDocument doc(QJsonDocument::fromJson(m_response));

    QJsonObject json = doc.object();

    QJsonObject jsonMessage = json["album"].toObject();
    QJsonArray jsonImages = jsonMessage["image"].toArray();

    QJsonValue url;
    if(jsonImages.size() == 6)
    {
        url = jsonImages.at(4).toObject().value("#text");
    }
    else if(jsonImages.size() > 0 && jsonImages.size() <= 5)
    {
        url = jsonImages.at(jsonImages.size() - 1).toObject().value("#text");
    }
    else
    {
        qDebug() << "Cover seems to be unavailable, jsonImages.size() is" << jsonImages.size();
    }

    return url.toString();
}

QString HttpRequestWorker::imageUrl()
{
    QJsonDocument doc(QJsonDocument::fromJson(m_response));

    QJsonObject json = doc.object();

    QJsonObject jsonMessage = json["artist"].toObject();
    QJsonArray jsonImages = jsonMessage["image"].toArray();

    QJsonValue url;
    if(jsonImages.size() == 6)
    {
        url = jsonImages.at(4).toObject().value("#text");
    }
    else if(jsonImages.size() > 0 && jsonImages.size() <= 5)
    {
        url = jsonImages.at(jsonImages.size() - 1).toObject().value("#text");
    }
    else
    {
        qDebug() << "Image seems to be unavailable, jsonImages.size() is" << jsonImages.size();
    }

    return url.toString();
}

QString HttpRequestWorker::lyricsUrl()
{
    /* Parse document */
    QJsonDocument doc(QJsonDocument::fromJson(m_response));

    /* Get JSON object */
    QJsonObject json = doc.object();

    QJsonObject jsonMessage = json["message"].toObject();
    QJsonObject jsonBody = jsonMessage["body"].toObject();
    QJsonArray jsonTrackList = jsonBody["track_list"].toArray();
    QJsonObject jsonTrack = jsonTrackList.at(0).toObject()["track"].toObject();

    return jsonTrack.value("track_share_url").toString();
}
