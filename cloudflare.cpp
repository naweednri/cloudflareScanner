#pragma once
#include "cloudflare.h"

cloudflare::cloudflare(std::string url):_url{url}
{}
std::string* scrape()
{
    std::string tmp;
    //return for just skipping
    return &tmp;
}
bool cloudflare::IPsBySubnet(std::string_view rawIPs)
{
    return true;
}
cloudflare::~cloudflare()
{

}
