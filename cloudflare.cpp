#pragma once
#include "cloudflare.h"
#include <QNetworkAccessManager>
#include <QDebug>
#include <QNetworkReply>
#include <QEventLoop>
#include <QStringView>
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
        parseIP(html,cloudflare::IP::v4);
                     });
    return html;
}
void cloudflare::parseIP(QString* scraped,IP type)
{
    if(type==IP::v4)
    {
        QStringList IPs=(*scraped).split('\n');
        qDebug()<<"Parsing IPs";
        for(const auto& i:IPs)
        {
            IPsBySubnet(i);
        }
        qDebug()<<"Finished pushing IP";
    }
    else
    {

    }
}
//find all available IPs by taking IP in CIDR format
void cloudflare::IPsBySubnet(QStringView rawIPs)
{
    unsigned char prefixInt;
    QList<QStringView> splited = rawIPs.split('/');
    QStringView IP=splited[0];
    QStringView prefix=splited[1];
    QList<QStringView> IPOctet = IP.split('.');
    quint32 ipInt = (IPOctet[0].toInt()<<24)|(IPOctet[1].toInt()<<16)|(IPOctet[2].toInt()<<8)|(IPOctet[3].toInt());
    prefixInt = prefix.toInt();
    quint8 hostBits = 32-prefixInt;
    quint32 mask = (0xFFFFFFFF<<hostBits) & 0xFFFFFFFF;
    quint32 network = ipInt & mask;
    quint32 broadcast = network | (0xFFFFFFFF>>prefixInt);
    QString tmp;

    for(quint32 i = network+1;i<broadcast;i++)
    {
        tmp = QString::number((i >> 24)& 0xFF);
        tmp.append(".");
        tmp.append(QString::number((i>> 16)&0xFF));
        tmp.append(".");
        tmp.append(QString::number((i>> 8)& 0xFF));
        tmp.append(".");
        tmp.append(QString::number((i & 0xFF)));
        //qDebug()<<tmp;
        _IPv4.push_back(tmp);
    }
}

bool cloudflare::run()
{
    scrape();
    return true;
}

cloudflare::~cloudflare()
{

}
