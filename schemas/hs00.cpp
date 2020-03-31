#include "hs00.h"
#include "hs00_event_histogram_generated.h"

bool verify_hs00(const uint8_t *buf, size_t buf_len) {
  auto verifier = flatbuffers::Verifier(buf, buf_len);
  return VerifyEventHistogramBuffer(verifier);
}