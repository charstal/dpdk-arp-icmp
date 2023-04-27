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

std::ostream &
operator<<(std::ostream &out, const ARPStats &b)
{
    out << "\tnum arp: " << b.num_arp
        << "\n\tnum broadcast arp: " << b.num_bcast_arp
        << "\n\tnum gratuitous arp: " << b.num_gratuitous_arp
        << "\n\tnum probe arp: " << b.num_probe_arp
        << "\n\tnum req arp: " << b.num_req_arp
        << "\n\tnum resp arp: " << b.num_resp_arp
        << std::endl;
    return out;
}

std::list<NetStats> net_stats_list;
RWLock lock;
