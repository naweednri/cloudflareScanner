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
    enum class IP
    {
        v4,v6
    };

private:
    QNetworkAccessManager* _manager;
    QString* scrape();
    void parseIP(QString* scraped,IP type);
    void IPsBySubnet(QStringView rawIPs);
    std::vector<QString> _IPv4;
    std::vector<QString> _IPv6;
    const QString _url;
};
#endif // CLOUDFLARE_H
