#include <cstdio>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include "include/data.hpp"
#include "proto/ns.grpc.pb.h"
#include "proto/ns.pb.h"

class NetStatsImpl final : public ns::NetStatsService::Service
{
public:
    ::grpc::Status
    GetNetStats(::grpc::ServerContext *context, const ::ns::Request *request, ::ns::Response *response) override
    {
        WriteLockGuard guard(lock);
        NetStats st;
        // st.num_arp = 0;
        // st.num_bcast_arp = 0;
        // st.num_ipv6 = 0;
        // st.num_ipv4 = 0;
        // st.num_multicast = 0;
        for (auto &item : net_stats_list)
        {

            // memcpy(st.pci_id, item.pci_id, sizeof(item.pci_id));
            // st.num_arp += item.num_arp;
            // st.num_bcast_arp += item.num_bcast_arp;
            st.num_ipv4 += item.num_ipv4;
            st.num_ipv6 += item.num_ipv6;
            st.num_multicast += item.num_multicast;
            st.num_pkgts += item.num_pkgts;

            for (auto it : item.src_ip_or_mac_stats)
            {
                st.src_ip_or_mac_stats[it.first] += it.second;
            }

            for (auto it : item.dest_ip_or_mac_stats)
            {
                st.dest_ip_or_mac_stats[it.first] += it.second;
            }

            for (auto it : item.device_stats)
            {
                st.device_stats[it.first].arp_stats += it.second.arp_stats;
            }

            // for (auto it = item.arp_stats.begin(); it != item.arp_stats.end(); ++it)
            // {
            //     st.arp_stats[it->first] += it->second;
            // }
        }

        uint32_t interval = static_cast<uint32_t>(net_stats_list.size());
        std::string msg = "success";
        response->set_msg(msg);
        auto &net_stats = *response->mutable_net_stats();

        // response->set_pci_id(st.pci_id);
        // response->set_num_arp(st.num_arp);
        net_stats.set_num_ipv4(st.num_ipv4);
        net_stats.set_num_ipv6(st.num_ipv6);
        net_stats.set_num_multicast(st.num_multicast);
        net_stats.set_num_pkgts(st.num_pkgts);
        net_stats.set_rate(st.num_pkgts * 1.0 / interval);

        auto device_stats = net_stats.mutable_device_stats();
        auto src_ipmac_stats = net_stats.mutable_src_ipmac_stats();
        auto dest_ipmac_stats = net_stats.mutable_dest_ipmac_stats();

        // auto &arp_stats = *response->mutable_arp_stats();
        for (auto it : st.src_ip_or_mac_stats)
        {
            (*src_ipmac_stats)[it.first].set_num_pkgs(it.second.num_pkgs);
            (*src_ipmac_stats)[it.first].set_rate(it.second.num_pkgs * 1.0 / interval);
        }

        for (auto it : st.dest_ip_or_mac_stats)
        {
            (*dest_ipmac_stats)[it.first].set_num_pkgs(it.second.num_pkgs);
            (*dest_ipmac_stats)[it.first].set_rate(it.second.num_pkgs * 1.0 / interval);
        }

        for (auto it : st.device_stats)
        {
            auto arp_stats = (*device_stats)[it.first].mutable_arp_stats();
            arp_stats->set_num_arp(it.second.arp_stats.num_arp);
            arp_stats->set_num_bcast_arp(it.second.arp_stats.num_bcast_arp);
            arp_stats->set_num_gratuitous_arp(it.second.arp_stats.num_gratuitous_arp);
            arp_stats->set_num_probe_arp(it.second.arp_stats.num_probe_arp);
            arp_stats->set_num_req_arp(it.second.arp_stats.num_req_arp);
            arp_stats->set_num_resp_arp(it.second.arp_stats.num_resp_arp);
            arp_stats->set_rate(it.second.arp_stats.num_arp * 1.0 / interval);
        }

        // for (auto it = st.arp_stats.begin(); it != st.arp_stats.end(); ++it)
        // {
        //     ns::ARPStats entry;
        //     entry.set_num_pkts(it->second);
        //     entry.set_rate(it->second / seconds);

        //     auto ip = ipv4_to_string(it->first);
        //     arp_stats.insert({ip, std::move(entry)});
        // }

        return grpc::Status::OK;
    }
};

void run_server()
{
    std::string server_address("localhost:50051");
    NetStatsImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    printf("Server listening on %s\n", server_address.c_str());

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();
}
