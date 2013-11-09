#include <dlfcn.h>
#include <cmath>

#define as(x...) #x "\n"
#ifdef __x86_64__
#define jmp(trampoline)\
		as(movq    trampoline(%rip), %rax)\
		as(jmp     *%rax)
#else
#define jmp(trampoline)\
		as(movl    trampoline, %eax)\
		as(jmp     *%eax)
#endif

#define wrapper(defname, wname, libhandle, optname)\
	decltype(&defname) wname##_init();\
	extern "C" { decltype(&defname) trampoline_##defname = wname##_init(); }\
	decltype(&defname) wname##_init(){\
		if(void* func = dlsym(libhandle, #optname)) return decltype(&defname)(func);\
		else return defname;\
	}\
	asm(\
			as(.global wname)\
			as(.hidden wname)\
			as(.type   wname, @function)\
		as(wname:)\
			jmp(trampoline_##defname)\
			as(.size   wname, .-wname)\
	)

void* libmhandle;

#define wrapper_finite(name)\
	wrapper(name, __wrap___##name##_finite, libmhandle?libmhandle:(libmhandle = dlopen("libm.so.6", RTLD_LAZY|RTLD_NOLOAD)), __##name##_finite)
