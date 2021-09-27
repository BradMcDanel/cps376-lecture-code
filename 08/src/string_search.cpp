#include <fstream>
#include <iostream>
#include <string>

std::string read_file(const std::string& filename) {
  std::ifstream file(filename);
  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
  return content;
}

int main() {
  std::string source = read_file("../data/warandpeace.txt");
  std::string target = "In 1789 a ferment arises in Paris;";

  // Using the standard library
  std::string::size_type pos = source.find(target);
  if (pos != std::string::npos) {
    std::cout << "Found at " << pos << std::endl;
  } else {
    std::cout << "Found at -1" << std::endl;
  }

  return 0;
}
