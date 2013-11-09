#include "wrapper.hpp"

wrapper_finite(acosf);
wrapper_finite(log);
wrapper_finite(exp);
wrapper_finite(pow);
wrapper_finite(logf);
wrapper_finite(expf);
wrapper_finite(asin);
wrapper_finite(atan2f);
wrapper_finite(log10f);
wrapper_finite(atan2);
wrapper_finite(acos);

#include <cstring>
asm(".symver memcpy, memcpy@GLIBC_2.2.5");
extern "C" void* __wrap_memcpy(void* dest, const void* src, size_t n) { return ::memcpy(dest, src, n); }
