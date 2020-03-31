//#include "f142_logdata_generated.h"
#include "flatbuffers/flatbuffers.h"
#include "hs00_event_histogram_generated.h"
//#include "ns10_cache_entry_generated.h"
//#include "pl72_run_start_generated.h"
#include <fstream>
#include <iostream>

int main() {
  auto fb_file = std::fstream("/Users/mattclarke/Desktop/output.bin",
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

  std::cout << "\nlength = " << length << '\n';

  auto verifier = flatbuffers::Verifier((uint8_t *)memblock, length);
  bool is_verified = VerifyEventHistogramBuffer(verifier);

  std::cout << "\nVerified " << is_verified << '\n';

  return 0;
}