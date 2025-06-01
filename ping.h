#ifndef PING_H
#define PING_H

#include <boost/asio.hpp>
#include <istream>
#include <iostream>
#include <ostream>

#include "icmp_header.h"
#include "ipv4_header.h"

using boost::asio::ip::icmp;
using boost::asio::steady_timer;
namespace chrono = boost::asio::chrono;

class pinger
{
public:
    pinger(boost::asio::io_context& io_context, const char* destination);

private:
    void start_send();
    void handle_timeout();
    void start_receive();
    void handle_receive(std::size_t length);
    static unsigned short get_identifier();
    icmp::resolver resolver_;
    icmp::endpoint destination_;
    icmp::socket socket_;
    steady_timer timer_;
    unsigned short sequence_number_;
    chrono::steady_clock::time_point time_sent_;
    boost::asio::streambuf reply_buffer_;
    std::size_t num_replies_;
};

#endif // PING_H
