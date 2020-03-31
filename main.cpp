#include "flatbuffers/flatbuffers.h"
#include "schemas/f142.h"
#include "schemas/hs00.h"
#include <fstream>
#include <iostream>
#include <array>

int main() {
  auto fb_file = std::fstream("/Users/mattclarke/Desktop/fb_out",
                              std::ios::in | std::ios::binary);
  // Go to the end
  fb_file.seekg(0, std::ios::end);
  int length = fb_file.tellg();
  char *memblock;
  memblock = new char[length];
  fb_file.seekg(0, std::ios::beg);
  fb_file.read(reinterpret_cast<char *>(memblock), length);
  fb_file.close();

  for (int i = 0; i < length; i++) {
    printf("%02X", (uint8_t)memblock[i]);
  }

  std::cout << '\n' << "Message length = " << length << '\n';

  // Get schema ID
  std::string id = {memblock[4]};
  id.push_back(memblock[5]);
  id.push_back(memblock[6]);
  id.push_back(memblock[7]);

  std::cout << "Schema id in message = " << id << '\n';

  bool is_verified = false;

  if (id == "f142") {
    is_verified = verify_f142((uint8_t *) memblock, length);
  } else if (id == "hs00") {
    is_verified = verify_hs00((uint8_t *) memblock, length);
  } else {
    std::cout << "WARNING: Unrecognised schema" << '\n';
  }

  if (is_verified) {
    std::cout << "Successfully verified " << id << " message\n";
  } else {
    std::cout << "Failed to verify " << id << " message\n";
  }

  return 0;
}