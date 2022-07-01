#ifndef CWEBREQUEST_H
#define CWEBREQUEST_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QMap>
#include <QNetworkCookieJar>
#include "ccookiejar.h"
#include <QUrl>

class CWebrequest: QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager *_request;
    CCookieJar *_cookieJar;
    QByteArray response;
    QUrl redirectUri;

public:
    // constructor
    CWebrequest();
    // destructor
    ~CWebrequest();
    QString get(QString, QMap<QByteArray, QByteArray>);
    QByteArray post(QString, QByteArray, QMap<QByteArray, QByteArray>);

    CCookieJar* getCookieJar();
    void setCookieJar(CCookieJar& pCookieJar);

    QString getCookie(QString pCookieName);
    void setCookie(QString pCookieName, QByteArray pCookieValue);

protected:
    QUrl redirectionUri;

public slots:
    void setRedirectedUri(const QUrl &url);
    void handleReply();

signals:
    void replyFinished();

};

#endif // CWEBREQUEST_H
