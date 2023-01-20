#ifndef FB_VERIFY_EV44_H
#define FB_VERIFY_EV44_H
#include <cinttypes>
#include <cstddef>
#include <tuple>

bool verify_ev44(const uint8_t *buf, size_t buf_len);

std::tuple<uint8_t *, size_t> create_ev44();

#endif //FB_VERIFY_EV44_H
