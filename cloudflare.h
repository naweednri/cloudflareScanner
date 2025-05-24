#ifndef CLOUDFLARE_H
#define CLOUDFLARE_H
#include <iostream>
#include <vector>
#include <QString>
#include <QObject>
class QNetworkAccessManager;
class cloudflare : public QObject
{
    Q_OBJECT
public:
    cloudflare(const QString url);
    ~cloudflare();
    bool run();
private:
    QNetworkAccessManager* _manager;
    QString* scrape();
    bool IPsBySubnet(std::string_view rawIPs);
    std::vector<std::string>* _IPv4;
    std::vector<std::string>* _IPv6;
    const QString _url;
};
#endif // CLOUDFLARE_H
