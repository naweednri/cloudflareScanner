#pragma once
#include "cloudflare.h"
#include <QNetworkAccessManager>
#include <QDebug>
#include <QNetworkReply>
#include <QEventLoop>
cloudflare::cloudflare(const QString url):_url(url),_manager(new QNetworkAccessManager(this))
{}
QString* cloudflare::scrape()
{

    QString* html = new QString;
    qDebug()<<"Start scraping";
    QNetworkRequest req(QUrl{_url});
    QNetworkReply* reply = _manager->get(req);
    QObject::connect(reply,&QNetworkReply::readyRead,[=](){
        html->append(QString(reply->readAll()));
        qDebug()<<"readyRead...";
    });
    
    QObject::connect(reply,&QNetworkReply::downloadProgress,this,[](qint64 bytesReceived,qint64 bytesTotal)
                     {
                         qDebug()<<"Progress: "<<bytesReceived<<"bytes / "<<bytesTotal<<"bytes";
                     });

    QObject::connect(reply,&QNetworkReply::finished,this,[=]()
                     {
        qDebug()<<*html;
        qDebug()<<"Finished";
                     });
    
    return html;
}

bool cloudflare::IPsBySubnet(std::string_view rawIPs)
{
    return true;
}

bool cloudflare::run()
{
    scrape();
    return true;
}

cloudflare::~cloudflare()
{

}
