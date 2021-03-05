#include <yas/binary_iarchive.hpp>
#include <yas/binary_oarchive.hpp>
#include <yas/mem_streams.hpp>

#undef NDEBUG
#include <cassert>

/***************************************************************************/

int main() {
  char w0 = 33, r0 = 0;
  int w1 = 44, r1 = 0;
  float w2 = 3.14156, r2 = 0;
  double w3 = 3.14156259, r3 = 0;

  {
    yas::mem_ostream os;
    yas::binary_oarchive<yas::mem_ostream> oa(os);

    auto oo =
        YAS_OBJECT_NVP("vars", ("v0", w0), ("v1", w1), ("v2", w2), ("v3", w3));
    oa.serialize(oo);

    yas::mem_istream is(os.get_intrusive_buffer());
    yas::binary_iarchive<yas::mem_istream> ia(is);

    auto io =
        YAS_OBJECT_NVP("vars", ("v0", r0), ("v1", r1), ("v2", r2), ("v3", r3));
    ia.serialize(io);

    // TODO: stackoverflow.com/questions/17333
    assert(r0 == w0 && r1 == w1 && r2 == w2 && r3 == w3);
  }

  r0 = 0;
  r1 = 0;
  r2 = 0;
  r3 = 0;
  {
    yas::mem_ostream os;
    yas::binary_oarchive<yas::mem_ostream> oa(os);

    auto oo =
        YAS_OBJECT_NVP("vars", ("v0", w0), ("v1", w1), ("v2", w2), ("v3", w3));
    oa(oo);

    yas::mem_istream is(os.get_intrusive_buffer());
    yas::binary_iarchive<yas::mem_istream> ia(is);

    auto io =
        YAS_OBJECT_NVP("vars", ("v0", r0), ("v1", r1), ("v2", r2), ("v3", r3));
    ia(io);

    // TODO: stackoverflow.com/questions/17333
    assert(r0 == w0 && r1 == w1 && r2 == w2 && r3 == w3);
  }
}
