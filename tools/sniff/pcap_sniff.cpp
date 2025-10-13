#include <arpa/inet.h>
#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <pcap.h>
#include <pcap/pcap.h>

void print_packet(const struct pcap_pkthdr *h, const u_char *packet) {
  for (int i = 0; i < h->len; i++) {
    printf("%02x ", packet[i]);
    if ((i + 1) % 16 == 0) {
      printf("\n");
    }
  }
  printf("\n\n");
}

void packet_handler(u_char *args, const struct pcap_pkthdr *header,
                    const u_char *packet) {
  struct iphdr *ip = (struct iphdr *)(packet + 14);

  if (ip->protocol == IPPROTO_TCP) {
    printf("- src:\t%s\n", inet_ntoa(*(struct in_addr *)&ip->saddr));
    printf("- dst:\t%s\n\n", inet_ntoa(*(struct in_addr *)&ip->daddr));
    printf("- MAC_dst:\t");
    for (int i = 0; i < 6; i++) {
      printf("%02x", packet[i]);
      if (i != 5) {
        printf(":");
      }
    }
    printf("\n");

    printf("- MAC_src:\t");
    for (int i = 6; i < 12; i++) {
      printf("%02x", packet[i]);
      if (i != 11) {
        printf(":");
      }
    }
    printf("\n");

    struct tcphdr *tcp = (struct tcphdr *)(packet + 14 + 20);

    printf("- port: %d -> %d\n\n", htons(tcp->th_sport), htons(tcp->th_dport));

    printf("== PACKET %d ===\n", header->len);
    print_packet(header, packet);
  }
}

int pcap_sniff() {
  char errbuf[PCAP_ERRBUF_SIZE];
  char *device = pcap_lookupdev(errbuf);

  if (device == nullptr) {
    std::cerr << "[!!] pcap_lookupdev: " << errbuf << std::endl;
    return 1;
  }

  pcap_t *handle = pcap_open_live(device, BUFSIZ, 1, 1000, errbuf);
  if (handle == nullptr) {
    std::cerr << "[!!] pcap_open_live: " << errbuf << std::endl;
    return 1;
  }

  pcap_loop(handle, 3, packet_handler, nullptr);

  pcap_close(handle);

  return 0;
}
