#include "f144.h"
#include "f144_logdata_generated.h"

bool verify_f144(const uint8_t *buf, size_t buf_len) {
  auto verifier = flatbuffers::Verifier(buf, buf_len);
  return VerifyLogDataBuffer(verifier);
}