#include "HttpRequestInput.h"

HttpRequestInput::HttpRequestInput(const QString& url, const QString& httpMethod)
{
    m_url = url;
    m_httpMethod = httpMethod;

    m_layout = LAYOUT_NOT_SET;
}

const QString& HttpRequestInput::httpMethod()
{
    return m_httpMethod;
}

const QString& HttpRequestInput::url()
{
    return m_url;
}

void HttpRequestInput::setUrl(const QString& url)
{
    m_url = url;
}

QList<HttpRequestInputFileElement>& HttpRequestInput::files()
{
    return m_files;
}

void HttpRequestInput::addFile(const QString& variableName, const QString& localFilename, const QString& requestFilename, const QString& mimeType)
{
    HttpRequestInputFileElement file;
    file.variableName = variableName;
    file.localFilename = localFilename;
    file.requestFilename = requestFilename;
    file.mimeType = mimeType;

    m_files.append(file);
}

QString HttpRequestInput::parameter(const QString& key)
{
    return m_parameters.value(key, "");
}

QMap<QString, QString> HttpRequestInput::parameters()
{
    return m_parameters;
}

void HttpRequestInput::addParameter(const QString& key, const QString& value)
{
    m_parameters.insert(key, value);
}

HttpRequestVarLayout HttpRequestInput::layout()
{
    return m_layout;
}

void HttpRequestInput::setLayout(HttpRequestVarLayout layout)
{
    m_layout = layout;
}
