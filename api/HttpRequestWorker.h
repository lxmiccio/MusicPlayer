#ifndef HTTPREQUESTWORKER_H
#define HTTPREQUESTWORKER_H

#include <QBuffer>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QObject>

#include "HttpRequestInput.h"

class HttpRequestWorker : public QObject
{
        Q_OBJECT

    public:
        explicit HttpRequestWorker(QObject* parent = 0);

        void albumInfoLastFm(const QString& artist, const QString& album);
        void artistInfoLastFm(const QString& artist);


        QString encodeAttribute(QString attribute, QString input);
        void execute(HttpRequestInput input);

        QByteArray response();

        HttpRequestInput input();

        bool isError();
        QNetworkReply::NetworkError error();
        QString errorMessage();

        QString coverUrl();
        QString lyricsUrl();

    signals:
        void requestFinished(HttpRequestWorker* worker);

    private slots:
        void onRequestFinished(QNetworkReply* reply);

    private:
        QNetworkAccessManager* m_manager;
        QByteArray m_response;

        HttpRequestInput m_input;

        QNetworkReply::NetworkError m_networkError;
        QString m_error;
};

#endif// HTTPREQUESTWORKER_H
