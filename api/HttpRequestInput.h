#ifndef HTTPREQUESTINPUT_H
#define HTTPREQUESTINPUT_H

#include <QDebug>

enum HttpRequestVarLayout {LAYOUT_NOT_SET, LAYOUT_ADDRESS, LAYOUT_URL_ENCODED, LAYOUT_MULTIPART};

class HttpRequestInputFileElement
{
public:
    QString variable_name;
    QString local_filename;
    QString request_filename;
    QString mime_type;

};

class HttpRequestInput
{
public:
    HttpRequestInput(QString url = "", QString httpMethod = "GET");

    void addParameter(QString key, QString value);
    void addFile(QString variable_name, QString local_filename, QString request_filename, QString mime_type);

    const QString& url();
    void setUrl(const QString& url);

    const QString& httpMethod();

    QString m_url;
    QString m_httpMethod;
    HttpRequestVarLayout var_layout;
    QMap<QString, QString> vars;
    QList<HttpRequestInputFileElement> files;



private:
};

#endif// HTTPREQUESTINPUT_H
