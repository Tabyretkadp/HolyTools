#include "../include/banners.hpp"
#include "../include/pcap_sniff.hpp"

#include <cstdlib>
#include <iostream>

void clear_console() {
#ifdef _WIN32
  std::system("cls");
#else
  std::system("clear");
#endif
}

void menu() {
  clear_console();
  main_banner();

  int menu_item = 0;
  std::cout << "  > ";
  std::cin >> menu_item;

  switch (menu_item) {
  case 1: {
    clear_console();
    brutforce_banner();
    sniff();
    break;
  }
  case 2:
    std::cout << "not yet :(" << std::endl;
    break;
  case 3:
    std::cout << "not yet and no ideas :(" << std::endl;
    break;
  }
}
