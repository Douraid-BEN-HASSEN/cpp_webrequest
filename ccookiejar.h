#ifndef CCOOKIEJAR_H
#define CCOOKIEJAR_H

#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QList>
class CCookieJar: public QNetworkCookieJar
{
public:
    CCookieJar();
    ~CCookieJar();
    QList<QNetworkCookie> allCookies();
    QNetworkCookie getCookie(QString);
    void setCookie(QString, QByteArray);
};

#endif // CCOOKIEJAR_H
