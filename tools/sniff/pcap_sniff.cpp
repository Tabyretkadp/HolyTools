#include <arpa/inet.h>
#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <pcap.h>
#include <pcap/pcap.h>

void dump(const struct pcap_pkthdr *header, const u_char *packet) {
  if (packet == nullptr) {
    printf("<not data>\n");
    return;
  }

  int data_offset = 14 + 20 + 20;
  const u_char *data = packet + data_offset;
  int data_len = header->len - data_offset;

  for (int i = 0; i < data_len; i++) {
    printf("%02x ", data[i]);
    if ((i + 1) % 16 == 0) {
      printf("\n");
    }
  }
  if (header->len % 16 != 0) {
    printf("\n");
  }
  printf("\n");
}

void packet_handler(u_char *args, const struct pcap_pkthdr *header,
                    const u_char *packet) {
  struct iphdr *ip = (struct iphdr *)(packet + 14);
  printf("packet %d bite\n", header->len);
  printf(" - src:\t%s\n", inet_ntoa(*(struct in_addr *)&ip->saddr));
  printf(" - dst:\t%s\n\n", inet_ntoa(*(struct in_addr *)&ip->daddr));
  printf(" - MAC_src:\t");
  for (int i = 6; i < 12; i++) {
    printf("%02x", packet[i]);
    if (i != 11) {
      printf(":");
    }
  }
  printf("\n");

  printf(" - MAC_dst:\t");
  for (int i = 0; i < 6; i++) {
    printf("%02x", packet[i]);
    if (i != 5) {
      printf(":");
    }
  }
  printf("\n\n");

  struct tcphdr *tcp = (struct tcphdr *)(packet + 14 + ip->ihl * 4);

  printf(" - port:\t%u -> %u\n", ntohs(tcp->th_sport), ntohs(tcp->th_dport));
  printf(" - seq #:\t%u\n", htons(tcp->seq));
  printf(" - ask #:\t%u\n\n", htons(tcp->ack));

  dump(header, packet);
}

int main() {
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

  pcap_loop(handle, 0, packet_handler, nullptr);

  pcap_close(handle);

  return 0;
}
