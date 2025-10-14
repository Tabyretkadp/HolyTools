#include "../../include/banners.hpp"

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
  print_colored("    ты не бог, но ты носишь свет                        ",
                "38;5;255");
  print_colored("..::::^~?P?~^^^::...", "38;5;196");
  print_colored("   \n", "38;5;255");
  print_colored("    твои инструменты — это яд,                           ",
                "38;5;255");
  print_colored(".::^~~!7YG57!~~^:..\n", "38;5;196");
  print_colored(
      "    ты лечишь ложь — болью                                      ",
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
      "  [ 1 ] - pcap_sniff                                             ",
      "38;5;255");
  print_colored(".~.\n", "38;5;196");
  print_colored(
      "  [ 2 ] - ???                                                    ",
      "38;5;255");
  print_colored(".\n", "38;5;196");
  std::cout << "\n";
}

void brutforce_banner() {
  print_colored(R"(
               @@@  @@@ @@@  @@@@@@@ @@@@@@@ @@@ @@@@@@@@@@ 
               @@!  @@@ @@! !@@        @!!   @@! @@! @@! @@!
               @!@  !@! !!@ !@!        @!!   !!@ @!! !!@ @!@
                !: .:!  !!: :!!        !!:   !!: !!:     !!:
                  ::    :    :: :: :    :    :    :      :  
  )",
                "38;5;196");
  print_colored(
      R"(                                                                                                                  
 -----------------------------------------------------------------------------

  )",
      "38;5;255");
}
