#ifndef cc_nanny_h
#define cc_nanny_h 1

#if __GNUC__ || __clang__ || __INTEL_LLVM_COMPILER
#define UNUSED __attribute__ ((unused))
#else
#define UNUSED /**/
#endif

#endif /* ! cc_nanny_h */
