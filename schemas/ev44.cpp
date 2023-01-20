#include "ev44.h"
#include "ev44_events_generated.h"

bool verify_ev44(const uint8_t *buf, size_t buf_len) {
  auto verifier = flatbuffers::Verifier(buf, buf_len);
  return VerifyEvent44MessageBuffer(verifier);
}