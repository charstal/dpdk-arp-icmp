#include <cstdint>
#include <cstdio>
#include <string>

#include <rte_arp.h>
#include <rte_byteorder.h>
#include <rte_ethdev.h>
#include <rte_ether.h>
#include <rte_mbuf.h>

#include "include/common.h"
#include "include/data.hpp"
#include "include/process.hpp"

#define NB_PKTS 32

static inline bool arp_check_probe(struct rte_arp_hdr *arp_hdr)
{
    uint32_t src_ip = rte_be_to_cpu_32(arp_hdr->arp_data.arp_sip);

    uint32_t dest_ip = rte_be_to_cpu_32(arp_hdr->arp_data.arp_tip);

    return src_ip == 0 && dest_ip != 0 &&
           rte_is_zero_ether_addr(&arp_hdr->arp_data.arp_tha) &&
           !rte_is_zero_ether_addr(&arp_hdr->arp_data.arp_sha);
}

static inline bool arp_check_gratuitous(struct rte_arp_hdr *arp_hdr)
{
    uint32_t src_ip = rte_be_to_cpu_32(arp_hdr->arp_data.arp_sip);
    uint32_t dest_ip = rte_be_to_cpu_32(arp_hdr->arp_data.arp_tip);

    return src_ip == dest_ip &&
           (rte_is_broadcast_ether_addr(&arp_hdr->arp_data.arp_tha) ||
            rte_is_zero_ether_addr(&arp_hdr->arp_data.arp_tha));
}

static inline void get_device_name(uint16_t port_id, std::string *buf)
{
    struct rte_eth_dev_info dev_info;
    rte_eth_dev_info_get(port_id, &dev_info);
    struct rte_device *device = dev_info.device;
    *buf = device->name;
    // strncpy(buf, device->name, PORT_PCI_DEV_ID_LENGTH);
}

static inline void mac_stats(struct rte_arp_hdr *arp_hdr, NetStats &st)
{

    // uint32_t src_ip = rte_be_to_cpu_32(arp_hdr->arp_data.arp_sip);
    // std::string str_src_ip = ipv4_to_string(src_ip);
    // uint32_t dest_ip = rte_be_to_cpu_32(arp_hdr->arp_data.arp_tip);
    // std::string str_dest_ip = ipv4_to_string(src_ip);

    char cstr_src_mac[18], cstr_dest_mac[18];
    rte_ether_addr src_mac = arp_hdr->arp_data.arp_sha;
    rte_ether_format_addr(cstr_src_mac, 18, &src_mac);
    rte_ether_addr dest_mac = arp_hdr->arp_data.arp_tha;
    rte_ether_format_addr(cstr_dest_mac, 18, &dest_mac);
    std::string str_src_mac = cstr_src_mac, dest_src_mac = cstr_dest_mac;

    // if (src_ip != 0 && src_ip != 0xffffffff)
    // {
    //     st.src_ip_or_mac_stats[str_src_ip].num_pkgs++;
    // }
    // else
    if (!rte_is_zero_ether_addr(&arp_hdr->arp_data.arp_sha) && !rte_is_broadcast_ether_addr(&arp_hdr->arp_data.arp_sha))
    {
        st.src_ip_or_mac_stats[str_src_mac].num_pkgs++;
    }

    // if (dest_ip != 0 && dest_ip != 0xffffffff)
    // {
    //     st.dest_ip_or_mac_stats[str_dest_ip].num_pkgs++;
    // }
    // else
    if (!rte_is_zero_ether_addr(&arp_hdr->arp_data.arp_tha) && !rte_is_broadcast_ether_addr(&arp_hdr->arp_data.arp_tha))
    {
        st.dest_ip_or_mac_stats[dest_src_mac].num_pkgs++;
    }
}

static inline void collect_stats_arp(struct rte_arp_hdr *arp_hdr, NetStats &st, std::string &device_name)
{
    mac_stats(arp_hdr, st);

    ARPStats &arp_stats = st.device_stats[device_name].arp_stats;

    arp_stats.num_arp++;

    if (rte_is_broadcast_ether_addr(&arp_hdr->arp_data.arp_tha))
    {
        arp_stats.num_bcast_arp++;
    }

    switch (rte_be_to_cpu_16(arp_hdr->arp_opcode))
    {
    case RTE_ARP_OP_REQUEST:
        arp_stats.num_req_arp++;
        break;
    case RTE_ARP_OP_REPLY:
        arp_stats.num_resp_arp++;
    }

    if (arp_check_gratuitous(arp_hdr))
    {
        arp_stats.num_gratuitous_arp++;
    }

    if (arp_check_probe(arp_hdr))
    {
        arp_stats.num_arp++;
    }

    // st.arp_stats[src_ip]++;
    // printf("Detect ARP requested by " IPV4_PRT_FMT "\n", IPV4_BYTES(src_ip));
    // st.++;
}

void collect_stats(uint16_t port_id, NetStats &st)
{
    struct rte_mbuf *pkts[NB_PKTS];

    std::string device_name;
    get_device_name(port_id, &device_name);
    // printf("device info is %s",st.pci_id);
    uint16_t nb_rx = rte_eth_rx_burst(port_id, 0, pkts, NB_PKTS);

    for (uint16_t i = 0; i < nb_rx; i++)
    {
        struct rte_ether_hdr *ether_hdr = rte_pktmbuf_mtod(pkts[i], struct rte_ether_hdr *);
        uint16_t ether_type = rte_be_to_cpu_16(ether_hdr->ether_type);

        // printf("Receive a packet from port %" PRIu16 ", type %04x\n", port_id, ether_type);

        switch (ether_type)
        {
        case RTE_ETHER_TYPE_ARP:
            collect_stats_arp(rte_pktmbuf_mtod_offset(pkts[i], struct rte_arp_hdr *, sizeof(struct rte_ether_hdr)), st, device_name);
            break;
        case RTE_ETHER_TYPE_IPV4:
            st.num_ipv4++;
            break;
        case RTE_ETHER_TYPE_IPV6:
            st.num_ipv6++;
            break;
        default:
            break;
        }

        if (rte_is_multicast_ether_addr(&ether_hdr->dst_addr))
        {
            st.num_multicast++;
        }

        st.num_pkgts++;

        rte_pktmbuf_free(pkts[i]);
    }
}
