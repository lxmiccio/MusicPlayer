#include "HttpRequestInput.h"

HttpRequestInput::HttpRequestInput(QString url, QString httpMethod)
{
    m_url = url;
    m_httpMethod = httpMethod;

    var_layout = LAYOUT_NOT_SET;
}

void HttpRequestInput::addParameter(QString key, QString value) {
    vars[key] = value;
}

void HttpRequestInput::addFile(QString variable_name, QString local_filename, QString request_filename, QString mime_type) {
    HttpRequestInputFileElement file;
    file.variable_name = variable_name;
    file.local_filename = local_filename;
    file.request_filename = request_filename;
    file.mime_type = mime_type;
    files.append(file);
}

const QString& HttpRequestInput::url()
{
    return m_url;
}

void HttpRequestInput::setUrl(const QString& url)
{
    m_url = url;
}

const QString& HttpRequestInput::httpMethod()
{
    return m_httpMethod;
}
