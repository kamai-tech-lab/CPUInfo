/// @file cpuid.h
/// @author Masayoshi Kamai

#ifndef DETAIL_CPUID_H_
#define DETAIL_CPUID_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if defined(_MSC_VER) || defined(__ICL)
#include <intrin.h>
#endif

#include "cpuinfo_type.h"


namespace detail {

CPUINFO_INLINE void cpuid(DWORD info[4], const DWORD eax, const DWORD ecx) {
#if defined(_MSC_VER) || defined(__ICL)
    __cpuidex(reinterpret_cast<int*>(info), eax, ecx);
#elif defined(__GNUC__) || defined(__clang__)
    __asm__ __volatile__ (
        "cpuid\n\t"
        : "=a"(info[0]),"=b"(info[1]),"=c"(info[2]),"=d"(info[3])
        : "a"(eax),"c"(ecx) );
#else
    #error Unsupported this cpu architecture
#endif
}

} // namespace "detail"

#endif // DETAIL_CPUID_H_
