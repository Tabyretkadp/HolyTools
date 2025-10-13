CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -lpcap

SRC = main.cpp \
      core/menu.cpp \
      core/visual/banners.cpp \
      tools/sniff/pcap_sniff.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = holytools

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)

