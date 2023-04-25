#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include <rte_cycles.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_ether.h>
#include <rte_launch.h>
#include <rte_lcore.h>
#include <rte_mbuf.h>
#include <rte_mempool.h>
#include <rte_rwlock.h>

#include "include/common.h"
#include "include/data.hpp"
#include "include/port.h"
#include "include/process.hpp"
#include "include/server.hpp"

using std::cout;
using std::endl;

uint32_t interval = 60;
static inline void print_stats(NetStats &st)
{
    // for (uint64_t i = 0; i < sizeof(st.pci_id); i++)
    // {
    //     printf("%c", st.pci_id[i]);
    // }
    cout << endl;
    cout << "num_ipv4: " << st.num_ipv4
         << "\nnum_ipv6: " << st.num_ipv6
         << "\nnum_multicast: " << st.num_multicast
         << "\nnum_pkgts: " << st.num_pkgts
         << endl;

    cout << "---------------------------arp----------------------------------" << endl;
    for (auto &it : st.device_stats)
    {
        cout << endl;
        cout << "device name: " << it.first;
        cout << it.second.arp_stats
             << endl;
    }
    // for (auto it = st.src_ip_or_mac_stats.begin(); it != st.arp_stats.end(); ++it)
    // {
    //     printf(IPV4_PRT_FMT "\t%" PRIu32 "\n", IPV4_BYTES(it->first), it->second);
    // }
    // printf("------------------------\n");
}

static inline void init_list()
{
    WriteLockGuard guard(lock);

    net_stats_list.clear();
    net_stats_list.emplace_front();
    // net_stats_list_2.clear();
    // net_stats_list_2.emplace_front();
}

__rte_noreturn int main_loop(__rte_unused void *arg)
{
    // tsc frequency
    const uint64_t period = rte_get_tsc_hz();
    // cur tsc
    uint64_t cur_cycles = rte_get_timer_cycles();

    for (;;)
    {
        uint16_t port_id;
        RTE_ETH_FOREACH_DEV(port_id)
        {
            WriteLockGuard guard(lock);
            auto &st = net_stats_list.front();
            // auto &st_2 = net_stats_list_2.front();
            if (port_id == 0)
            {
                collect_stats(port_id, st);
            }
            // else if (port_id == 1)
            // {
            //     collect_stats(port_id, st_2);
            // }
            uint64_t cur_tsc = rte_get_timer_cycles();
            if (cur_tsc - cur_cycles >= period)
            {
                print_stats(st);
                // print_stats(st_2);
                cur_cycles = cur_tsc;
                printf("------------------------\n");
                // 添加新节点，删除旧节点
                net_stats_list.emplace_front();
                if (net_stats_list.size() > interval)
                    net_stats_list.pop_back();
                // net_stats_list_2.emplace_front();
                // if (net_stats_list_2.size() > interval)
                //     net_stats_list_2.pop_back();

                // printf("------------------------\n");
            }
        }
    }
}

int main(int argc, char *argv[])
{
    switch (argc)
    {
    case 1:
        /* code */
        interval = 60;
        break;
    case 3:
        if (strcmp(argv[1], "-i") == 0)
        {
            interval = atoi(argv[2]);
            if (interval >= 1)
            {
                break;
            }
        }
    default:
        printf("Please enter the correct parameters, example: monitor -i 60 \n");
        exit(1);
    }
    printf("Interval %d", interval);

    int ac = 0;
    char *av[] = {};
    // eal init
    int ret = rte_eal_init(ac, av);
    if (ret < 0)
    {
        rte_exit(1, "Fail to initialize EAL\n");
    }
    cout << "Initialize EAL OK" << endl;
    // else
    // {
    // argc -= ret;
    // argv += ret;

    // }

    // uint16_t nb_ports = rte_eth_dev_count_avail();
    // if (nb_ports == 0)
    // {
    //     rte_exit(1, "No available Ethernet ports\n");
    // }
    // else
    // {
    //     printf("Available %" PRIu16 " Ethernet ports\n", nb_ports);
    // }

    // mbuf pool init
    struct rte_mempool *mbuf_pool =
        rte_pktmbuf_pool_create("mbuf_pool", 65535, 512, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());
    if (!mbuf_pool)
    {
        rte_exit(1, "Fail to create a mbuf pool\n");
    }
    printf("Create mbuf pool OK\n");

    // port init
    port_init_all(mbuf_pool);

    // list init
    init_list();
    // find a lcore
    unsigned int lcore_id = rte_get_next_lcore(-1, 1, 1);
    // run main_loop in lcore
    rte_eal_remote_launch(main_loop, NULL, lcore_id);
    // grpc server
    run_server();
    // wait finished
    rte_eal_mp_wait_lcore();
    // close port
    port_finalize_all();
    // clean up
    ret = rte_eal_cleanup();
    if (ret < 0)
    {
        rte_exit(1, "Fail to finalize EAL\n");
    }
    printf("Finalize EAL OK\n");

    return 0;
}
