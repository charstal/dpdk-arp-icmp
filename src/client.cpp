#include <iostream>
#include <memory>
#include <string>
#include <iomanip>
#include <cstdio>

#include <grpcpp/grpcpp.h>

#include "proto/ns.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using ns::NetStatsService;
using ns::Request;
using ns::Response;

class GreeterClient
{
public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(NetStatsService::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  int GetNetStats()
  {
    // Data we are sending to the server.
    Request request;

    // Container for the data we expect from the server.
    Response response;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->GetNetStats(&context, request, &response);

    const auto msg = response.msg();
    const auto stats = response.net_stats();

    // Act upon its status.
    if (status.ok())
    {
      // std::cout << "@##################################################"
      //         << std::endl;
      std::cout << "--------------------------total-------------------------" << std::endl;
      std::cout << std::left;
      // std::cout << std::setw(12) << "scrip" << std::setw(12) << "arp-request-pkts"
      //             << std::setw(12) << "rate"<< std::endl;
      // std::cout << "----------------------------------------------------" << std::endl;
      // std::cout << "pci_id:  " << response.pci_id() << std::endl;
      // std::cout << "arp_rx_total_pps:  " << response.num_arp() << std::endl;
      // std::cout << "arp_rx_bcast_pps:  " << response.num_bcast_arp() << std::endl;

      auto &src_ipmac = stats.src_ipmac_stats();
      auto &dst_ipmac = stats.dest_ipmac_stats();

      std::cout << "Source ip or mac" << std::endl;
      for (auto ch : src_ipmac)
      {
        std::cout << "\t" << ch.first << std::endl;
        std::cout << "\t\tnum pkg: " << ch.second.num_pkgs() << std::endl;
        std::cout << "\t\trate: " << ch.second.rate() << std::endl;
      }
      std::cout << "Dest ip or mac" << std::endl;
      for (auto ch : dst_ipmac)
      {
        std::cout << "\t" << ch.first << std::endl;
        std::cout << "\t\tnum pkg: " << ch.second.num_pkgs() << std::endl;
        std::cout << "\t\trate: " << ch.second.rate() << std::endl;
      }

      std::cout << "ipv4 total:  " << stats.num_ipv4() << std::endl;
      std::cout << "ipv6 total:  " << stats.num_ipv6() << std::endl;
      std::cout << "multicast total:  " << stats.num_multicast() << std::endl;
      std::cout << "rate: " << stats.rate() << std::endl;

      std::cout << "--------------------------arp-------------------------" << std::endl;
      // arp
      for (auto it : stats.device_stats())
      {
        auto arp_stats = it.second.arp_stats();
        std::cout << "device name: " << it.first
                  << "\nnum arp: " << arp_stats.num_arp()
                  << "\nrate: " << arp_stats.rate()
                  << "\nnum broadcast arp: " << arp_stats.num_bcast_arp()
                  << "\nnum gratuitous arp: " << arp_stats.num_gratuitous_arp()
                  << "\nnum probe arp: " << arp_stats.num_probe_arp()
                  << "\nnum req arp: " << arp_stats.num_req_arp()
                  << "\nnum resp arp: " << arp_stats.num_resp_arp()
                  << std::endl;
      }

      // for(auto it : response.arp_stats()){
      //    ns::ARPStats tmp = it.second;
      //  std::cout << it.first <<std::setw(12) << "   amount: "<< tmp.num_pkts() << std::setw(12) << "    rate: " << tmp.rate() << std::endl;
      //}

      std::cout << "--------------------------end-------------------------" << std::endl;

      return 0;
    }
    else
    {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return -1;
    }
  }

private:
  std::unique_ptr<NetStatsService::Stub> stub_;
};

int main(int argc, char **argv)
{
  GreeterClient greeter(
      grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  int reply = greeter.GetNetStats();
  // std::cout << "Greeter received: " << reply << std::endl;

  return reply;
}
