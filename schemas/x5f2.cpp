#include "x5f2.h"
#include "x5f2_status_generated.h"

bool verify_x5f2(const uint8_t *buf, size_t buf_len) {
  auto verifier = flatbuffers::Verifier(buf, buf_len);
  return VerifyStatusBuffer(verifier);
}