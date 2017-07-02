#ifndef HTTPREQUESTWORKER_H
#define HTTPREQUESTWORKER_H

#include <QBuffer>
#include <QFile>
#include <QFileInfo>
#include <QNetworkReply>
#include <QObject>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "HttpRequestInput.h"

class HttpRequestWorker : public QObject
{
    Q_OBJECT

public:
    explicit HttpRequestWorker(QObject* parent = 0);

    QString encodeAttribute(QString attribute, QString input);
    void execute(HttpRequestInput* input);

    QString lyricsUrl();

    QByteArray m_response;
    QNetworkReply::NetworkError m_networkError;
    QString m_error;


signals:
    void on_execution_finished(HttpRequestWorker *worker);

private:
    QNetworkAccessManager *m_manager;

private slots:
    void on_manager_finished(QNetworkReply *reply);

};

#endif// HTTPREQUESTWORKER_H
