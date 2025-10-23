CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -lpcap -lnet

SRC = main.cpp \
      core/menu.cpp \
      core/visual/banners.cpp \
      tools/pcap_sniff/pcap_sniff.cpp \
      tools/syn_flood/syn_flood.cpp \
      tools/arp_sniffing/arp_sniffing.cpp \
      tools/icmp_flood/icmp_flood.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = holytools

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)

