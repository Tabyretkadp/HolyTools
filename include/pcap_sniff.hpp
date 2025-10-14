#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <pcap.h>
#include <pcap/pcap.h>

void dump(const struct pcap_pkthdr *header, const u_char *packet);
void packet_handler(u_char *args, const struct pcap_pkthdr *header,
                    const u_char *packet);
int sniff();
