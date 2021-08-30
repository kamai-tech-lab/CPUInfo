/// @file cpuinfo_type.h
/// @author Masayoshi Kamai

#ifndef DETAIL_CPUINFO_TYPE_H_
#define DETAIL_CPUINFO_TYPE_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


#if defined(_MSC_VER) || defined(__ICL)
    using sint8  = __int8;
    using uint8  = unsigned __int8;
    using sint16 = __int16;
    using uint16 = unsigned __int16;
    using sint32 = __int32;
    using uint32 = unsigned __int32;
    using sint64 = __int64;
    using uint64 = unsigned __int64;
#else
    using sint8  = char;
    using uint8  = unsigned char;
    using sint16 = short;
    using uint16 = unsigned short;
    using sint32 = int;
    using uint32 = unsigned int;
    using sint64 = long long;
    using uint64 = unsigned long long;
#endif

using BYTE  = uint8;
using WORD  = uint16;
using DWORD = uint32;
using QWORD = uint64;

#if !defined(__cpp_unicode_characters)
    using char16_t = uint16;
    using char32_t = uint32;
#endif
#if !defined(__cpp_char8_t) || ( __cpp_char8_t < 201803)
    using char8_t = char;
#endif

#if defined(_MSC_VER) || defined(__ICL)
    #define CPUINFO_INLINE               inline
    #define CPUINFO_FORCE_INLINE         __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    #define CPUINFO_INLINE               inline
    #define CPUINFO_FORCE_INLINE         inline __attribute__((always_inline))
#else
    #define CPUINFO_INLINE
    #define CPUINFO_FORCE_INLINE
#endif


#endif // DETAIL_CPUINFO_TYPE_H_
