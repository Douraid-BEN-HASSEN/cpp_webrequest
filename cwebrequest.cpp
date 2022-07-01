#include "cwebrequest.h"

CWebrequest::CWebrequest()
{
    this->_request = new QNetworkAccessManager();
    this->_cookieJar = new CCookieJar();
    this->_request->setCookieJar(this->_cookieJar);
}

QString CWebrequest::get(QString pUrl, QMap<QByteArray, QByteArray> options)
{
    QEventLoop loop;
    QNetworkRequest req(pUrl);

    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    for (QMap<QByteArray, QByteArray>::iterator it = options.begin(); it != options.end(); ++it) {
        req.setRawHeader(it.key(), it.value());
    }

    QNetworkReply* reply = this->_request->get(req);

    QObject::connect(reply, SIGNAL(redirected(const QUrl &)), this, SLOT(setRedirectedUri(const QUrl &)));
    QObject::connect(reply, SIGNAL(finished()), this, SLOT(handleReply()));
    QObject::connect(this, SIGNAL(replyFinished()), &loop, SLOT(quit()));

    loop.exec();

    return this->response;
}

QByteArray CWebrequest::post(QString pUrl, QByteArray pData, QMap<QByteArray, QByteArray> options)
{
    QEventLoop loop;
    QNetworkRequest req(pUrl);

    for (QMap<QByteArray, QByteArray>::iterator it = options.begin(); it != options.end(); ++it) {
        req.setRawHeader(it.key(), it.value());
    }

    QNetworkReply* reply = this->_request->post(req, pData);

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    return reply->readAll();
}

CCookieJar* CWebrequest::getCookieJar()
{
    return this->_cookieJar;
}

void CWebrequest::setCookieJar(CCookieJar &pCookieJar)
{
    this->_cookieJar = &pCookieJar;
    this->_request->setCookieJar(this->_cookieJar);
}

QString CWebrequest::getCookie(QString pCookieName)
{
    return this->_cookieJar->getCookie(pCookieName).value();
}

void CWebrequest::setCookie(QString pCookieName, QByteArray pCookieValue)
{
    this->_cookieJar->setCookie(pCookieName, pCookieValue);
}

void CWebrequest::setRedirectedUri(const QUrl &url)
{
    this->redirectUri = url;
}

void CWebrequest::handleReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if(this->redirectUri.url() != "")
    {
        QMap<QByteArray, QByteArray> headers;

        QString url = this->redirectUri.url();
        this->redirectionUri = this->redirectUri; // enregistrement de l'uri dans le membre protected
        this->redirectUri.setUrl("");
        this->get(url, headers);
    } else {
        this->response = reply->readAll();
        emit this->replyFinished();
    }
}

CWebrequest::~CWebrequest()
{
    delete this->_request;
    delete this->_cookieJar;
}
