// Enable debug asserts on verification failure
#define FLATBUFFERS_DEBUG_VERIFICATION_FAILURE

#include "flatbuffers/flatbuffers.h"
#include "schemas/ev44.h"
#include "schemas/f142.h"
#include "schemas/f144.h"
#include "schemas/hs00.h"
#include "schemas/x5f2.h"
#include <fstream>
#include <iostream>

std::tuple<uint8_t *, size_t> generate_message(const std::string_view schema) {
  if (schema == "ev44") {
    auto [buffer, length] = create_ev44();
    return {buffer, length};
  } else {
    std::cout << "WARNING: Unrecognised schema" << '\n';
  }
  return {nullptr, 0};
}

void write_to_file(const std::string &filename, const uint8_t *buffer,
                   size_t length) {
  std::ofstream wf(filename, std::ios::out | std::ios::binary);
  wf.write((char const *)buffer, length);
  wf.close();
}

bool verify_message(const std::string &schema, const uint8_t *buffer,
                    size_t length) {
  bool is_verified = false;

  if (schema == "f144") {
    is_verified = verify_f144(buffer, length);
  } else if (schema == "hs00") {
    is_verified = verify_hs00(buffer, length);
  } else if (schema == "x5f2") {
    is_verified = verify_x5f2(buffer, length);
  } else if (schema == "ev44") {
    is_verified = verify_ev44(buffer, length);
  } else {
    std::cout << "WARNING: Unrecognised schema" << '\n';
    return false;
  }

  if (is_verified) {
    std::cout << "Successfully verified " << schema << " message\n";
  } else {
    std::cout << "Failed to verify " << schema << " message\n";
  }

  return is_verified;
}

void print_buffer(uint8_t const *const buffer, size_t length) {
  for (int i = 0; i < length; i++) {
    printf("%02X", buffer[i]);
  }
  std::cout << '\n' << "Message length = " << length << '\n';
}

std::string get_schema(uint8_t const *const buffer) {
  std::string schema = {(char)buffer[4]};
  schema.push_back((char)buffer[5]);
  schema.push_back((char)buffer[6]);
  schema.push_back((char)buffer[7]);
  return schema;
}

std::tuple<uint8_t *, size_t> load_file(std::string const &filename) {
  auto fb_file = std::fstream(filename, std::ios::in | std::ios::binary);
  // Go to the end
  fb_file.seekg(0, std::ios::end);
  int length = fb_file.tellg();
  char *memblock;
  memblock = new char[length];
  fb_file.seekg(0, std::ios::beg);
  fb_file.read(reinterpret_cast<char *>(memblock), length);
  fb_file.close();

  return {(uint8_t *)memblock, (size_t)length};
}

int main() {
  {
    auto [buffer, length] = load_file("fb_out");
    auto schema = get_schema(buffer);
    verify_message(schema, buffer, length);
    print_buffer(buffer, length);
  }

  {
    auto [buffer, length] = generate_message("ev44");
    verify_message("ev44", buffer, length);
    print_buffer(buffer, length);
    write_to_file("ev44_example.bin", buffer, length);
  }

  return 0;
}
