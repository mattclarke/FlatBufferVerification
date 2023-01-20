#include "ev44.h"
#include "ev44_events_generated.h"

bool verify_ev44(const uint8_t *buf, size_t buf_len) {
  auto verifier = flatbuffers::Verifier(buf, buf_len);
  return VerifyEvent44MessageBuffer(verifier);
}

std::tuple<uint8_t *, size_t> create_ev44() {
  auto builder = flatbuffers::FlatBufferBuilder();
  builder.ForceDefaults(true);
  auto source = builder.CreateString("some_source");

  std::vector<int64_t> ref_times = {
      1618573589123781958, 1618573590133830371, 1618573593677164112,
      1618573594185190549, 1618573596217316066, 1618573596725363109,
      1618573601295720976, 1618573601799761445, 1618573607354064836};
  std::vector<int32_t> ref_times_idx = {2, 4, 5, 7};
  auto ref_fb = builder.CreateVector<int64_t>(ref_times);
  auto refi_fb = builder.CreateVector(ref_times_idx);

  std::vector<int32_t> tofs = {100, 200, 300, 400, 500, 600, 700, 800, 900};
  std::vector<int32_t> ids = {10, 20, 30, 40, 50, 60, 70, 80, 90};

  auto tofs_fb = builder.CreateVector(tofs);
  auto ids_fb = builder.CreateVector(ids);

  Event44MessageBuilder ev44builder(builder);
  ev44builder.add_reference_time(ref_fb);
  ev44builder.add_reference_time_index(refi_fb);
  ev44builder.add_time_of_flight(tofs_fb);
  ev44builder.add_pixel_id(ids_fb);
  ev44builder.add_message_id(123456);
  ev44builder.add_source_name(source);
  auto b = ev44builder.Finish();

  //  auto b = CreateEvent44Message(builder, source, 123456, ref_fb, refi_fb,
  //  tofs_fb, ids_fb);
  builder.Finish(b, "ev44");

  return {builder.GetBufferPointer(), builder.GetSize()};
}
