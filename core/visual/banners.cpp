#include "../../include/full_include.hpp"

// ICMP syn_flood
// Slowloris

#include <iostream>
#include <string>

void print_colored(const std::string &text, const std::string &color_code) {
  std::cout << "\033[" << color_code << "m" << text << "\033[0m";
}

void main_banner() {
  print_colored("                                                              "
                "                                                    \n",
                "38;5;255");
  print_colored(" -------------------------------------------------------------"
                "----------------\n",
                "38;5;255");
  print_colored("\n", "38;5;255");
  print_colored(
      "  :: HOLYTOOLS v1.0 ::                                          ",
      "38;5;255");
  print_colored(".:.           \n", "38;5;196");
  print_colored(
      "    [ sacred code / poison purpose ]                            ",
      "38;5;255");
  print_colored(":J:           \n", "38;5;196");
  print_colored(
      "                                                                ",
      "38;5;255");
  print_colored("^5^           \n", "38;5;196");
  print_colored("    You are not God, but you bring light                ",
                "38;5;255");
  print_colored("..::::^~?P?~^^^::...", "38;5;196");
  print_colored("   \n", "38;5;255");
  print_colored("    Your tools are poison,                              ",
                "38;5;255");
  print_colored(".::^~~!7YG57!~~^:..\n", "38;5;196");
  print_colored(
      "    You heal lies with pain                                     ",
      "38;5;255");
  print_colored("^P~           \n", "38;5;196");
  print_colored(
      "                                                                ",
      "38;5;255");
  print_colored(":5^           \n", "38;5;196");
  print_colored("                                                              "
                "  :Y:           \n",
                "38;5;196");
  print_colored("                                                              "
                "  :J:           \n",
                "38;5;196");
  print_colored("                                                              "
                "  .7:           \n",
                "38;5;196");
  print_colored(
      "  [ 1 ] - pcap_sniff                                            ",
      "38;5;255");
  print_colored(".~.\n", "38;5;196");
  print_colored(
      "  [ 2 ] - syn_flood                                              ",
      "38;5;255");
  print_colored(".\n", "38;5;196");
  print_colored(
      "  [ 3 ] - arp_sniff                                              ",
      "38;5;255");
  std::cout << "\n\n";
}
