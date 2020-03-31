#include "f142.h"
#include "f142_logdata_generated.h"

bool verify_f142(const uint8_t *buf, size_t buf_len) {
  auto verifier = flatbuffers::Verifier(buf, buf_len);
  return VerifyLogDataBuffer(verifier);
}