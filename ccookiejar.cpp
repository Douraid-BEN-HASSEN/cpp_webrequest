#include "ccookiejar.h"

CCookieJar::CCookieJar()
{
}

QList<QNetworkCookie> CCookieJar::allCookies()
{
    return this->QNetworkCookieJar::allCookies();
}

QNetworkCookie CCookieJar::getCookie(QString pName)
{
    foreach (const QNetworkCookie &cookie, this->allCookies()) {
        if(cookie.name() == pName) return cookie;
    }
}

void CCookieJar::setCookie(QString pName, QByteArray pValue)
{
    QList<QNetworkCookie> cookies = this->allCookies();
    for(int it=0; it < cookies.length(); it++) {
        if(cookies[it].name() == pName) cookies[it].setValue(pValue);
    }
    this->setAllCookies(cookies);
}

CCookieJar::~CCookieJar()
{
}


