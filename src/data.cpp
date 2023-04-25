#include <list>

#include "include/data.hpp"

ARPStats &ARPStats::operator+=(const ARPStats &b)
{
    this->num_arp += b.num_arp;
    this->num_req_arp += b.num_req_arp;
    this->num_resp_arp += b.num_resp_arp;
    this->num_gratuitous_arp += b.num_gratuitous_arp;
    this->num_probe_arp += b.num_probe_arp;

    return *this;
}

std::ostream &operator<<(std::ostream &out, const ARPStats &b)
{
    out << "num arp: " << b.num_arp
        << "\nnum broadcast arp: " << b.num_bcast_arp
        << "\nnum gratuitous arp: " << b.num_gratuitous_arp
        << "\nnum probe arp: " << b.num_probe_arp
        << "\nnum req arp: " << b.num_req_arp
        << "\nnum resp arp: " << b.num_resp_arp
        << std::endl;
    return out;
}

std::list<NetStats> net_stats_list;
RWLock lock;
