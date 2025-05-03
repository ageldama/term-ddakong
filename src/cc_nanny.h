/**
 * cc/gcc warning/error mitigations
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef cc_nanny_h
#define cc_nanny_h 1

#if __GNUC__ || __clang__ || __INTEL_LLVM_COMPILER
#define UNUSED __attribute__ ((unused))
#else
#define UNUSED /**/
#endif

#endif /* ! cc_nanny_h */
