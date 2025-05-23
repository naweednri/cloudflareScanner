#ifndef CLOUDFLARE_H
#define CLOUDFLARE_H
#include <iostream>
#include <vector>
class cloudflare
{
public:
    cloudflare(std::string url);
    ~cloudflare();
    bool run() const;
private:
    std::string* scrape();
    bool IPsBySubnet(std::string_view rawIPs);
    std::vector<std::string>* _IPv4;
    std::vector<std::string>* _IPv6;
    const std::string _url;

};

#endif // CLOUDFLARE_H
