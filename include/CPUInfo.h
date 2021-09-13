/// @file CpuInfo.h
/// @author Masayoshi Kamai

#ifndef CPU_INFO_H_
#define CPU_INFO_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


//----------------------------------------------------------------------------------------------------
// Defines
//----------------------------------------------------------------------------------------------------
#ifndef CPUINFO_MAX_CACHES
    #define CPUINFO_MAX_CACHES                      (5)
#endif

#ifndef CPUINFO_MAX_PROCESSOR_TOPOLOGY_LEVELS
    #define CPUINFO_MAX_PROCESSOR_TOPOLOGY_LEVELS   (5)
#endif

#ifndef CPUINFO_MAX_FEATURE_SUBLEAFS
    #define CPUINFO_MAX_EXT_FEATURE_SUBLEAFS        (1)
#endif

//----------------------------------------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------------------------------------
#include "detail/cpuinfo_type.h"
#include "detail/cpuid.h"


namespace CpuInfo {

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

/// @enum ProcessorType
enum class ProcessorType : DWORD {
    OriginalOEM,
    OverDrive,
    Dual,
    IntelReserved,
};

// @enum Feature
enum class Feature : DWORD {
    FPU                 = 0,    ///< Supports Intel387 float instruction unit
    VME                 = 1,    ///< Supports v86 mode
    DE                  = 2,    ///< Supports I/O break
    PSE                 = 3,    ///< Supports 4MiB page
    TSC                 = 4,    ///< Supports Time Stamp Counter
    MSR                 = 5,    ///< Supports Model Specific Register(RDMSR, WRMSR)
    PAE                 = 6,    ///< Supports Physical Address Extension
    MCE                 = 7,    ///< Supports Machine Check Exception
    CX8                 = 8,    ///< Supports CMPXCHG8 instruction
    APIC                = 9,    ///< Supports On chip APIC
    // reserved 10
    SEP                 = 11,   ///< Supports SYSENTER and SYSEXIT instructions
    MTRR                = 12,   ///< Supports Memory Type Range Ragister
    PGE                 = 13,   ///< Supports PTR Global Bit
    MCA                 = 14,   ///< Supports Machine Check Architecture
    CMOV                = 15,   ///< Supports Conditional Move instructions
    PAT                 = 16,   ///< Supports Page Attribute Table
    PSE_36              = 17,   ///< Supports 36-bit page size extension
    PSN                 = 18,   ///< Supports Processor Serial Number
    CLFSH               = 19,   ///< Supports CLFLUSH instruction
    // reserved 20
    DS                  = 21,   ///< Supports Debug Store
    ACPI                = 22,   ///< Supports Thermal Monitor and Software Controlled Clock Facilities
    MMX                 = 23,   ///< Supports Intel MMX Technology
    FXSR                = 24,   ///< Supports FXSAVE and FXRSTOR instructions
    SSE                 = 25,   ///< Supports Streaming SIMD Extension instructions
    SSE2                = 26,   ///< Supports Streaming SIMD Extension 2 instructions
    SS                  = 27,   ///< Supports Self Snoop
    HTT                 = 28,   ///< Supports Hyper-Threading Technology
    TM                  = 29,   ///< Supports Thermal Monitor
    // reserved 30
    PBE                 = 31,   ///< Supports Pending Break Enable
};

// @enum Feature2
enum class Feature2 : DWORD {
    SSE3                = 0,    ///< Supports Streaming SIMD Extension 3 instructions
    PCLMULQDQ           = 1,    ///< Supports PCLMULQDQ instrucsion
    DTES64              = 2,    ///< Supports 64-bit Debug Store
    MONITOR             = 3,    ///< Supports MONITOR and MWAIT instructions
    DS_CPL              = 4,    ///< Supports CPL Qualified Debug Store
    VMX                 = 5,    ///< Supports Vertual Machine Extensions
    SMX                 = 6,    ///< Supports Safer Mode Extensions
    EIST                = 7,    ///< Supports Enhanced Intel SpeedStep Technology
    TM2                 = 8,    ///< Supports Thermal Monitor 2
    SSSE3               = 9,    ///< Supports Supplemental Streaming SIMD Extensions 3 instructions
    CNXT_ID             = 10,   ///< Supports L1 Context ID
    // reserved 11
    FMA                 = 12,   ///< Supports Fused Multiply Add
    CMPXCHG16B          = 13,   ///< Supports CMPXCHG16B instruction
    XTPR                = 14,   ///< Supports xTPR Update Control
    PDCM                = 15,   ///< Supports Perfmon and Debug Capability
    // reserved 16
    PCID                = 17,   ///< Supports Process Context Identifiers
    DCA                 = 18,   ///< Supports Direct Cache Access
    SSE4_1              = 19,   ///< Supports Streaming SIMD Extension instructions 4.1
    SSE4_2              = 20,   ///< Supports Streaming SIMD Extension instructions 4.2
    X2APIC              = 21,   ///< Supports Extended x2APIC
    MOVBE               = 22,   ///< Supports MOVBE instruciton
    POPCNT              = 23,   ///< Supports POPCNT instruction
    TSC_DEADLINE        = 24,   ///< Supports Time Stamp Counter Deadline
    AES                 = 25,   ///< Supports AES instruction extensions
    XSAVE               = 26,   ///< Supports XSAVE/XSTOR States
    OSXSAVE             = 27,   ///< Supports OS-Enabled Extended State Management
    AVX                 = 28,   ///< Supports Advanced Vector Extension instructions
    F16C                = 29,   ///< Supports 16-bit floating-point conversion instructions
    RDRAND              = 30,   ///< Supports RDRAND instruction
    HYPERVISOR          = 31,   ///< Hyperbisor present bit
};

// @enum Feature3
enum class Feature3 : DWORD {
    FSGSBASE            = 0,    ///< Supports RDFSBASE/RDGSBASE/WRFSBASE/WRGSBASE
    TSC_ADJUST          = 1,    ///< Supports IA-32 TSC adjustment
    SGX                 = 2,    ///< Supports Intel Software Guard Extensions
    BMI1                = 3,    ///< Supports 1st group bit manipulation extensions
    HLE                 = 4,    ///< Supports Hardware Lock Elision
    AVX2                = 5,    ///< Supports Advanced Vector Extension 2 instructions
    FDP_EXCPTN_ONLY     = 6,    ///< Supports x87 FPU Data Pointer Exception Only
    SMEP                = 7,    ///< Supports Supervisor Mode Execution Protection
    BMI2                = 8,    ///< Supports 2nd group bit manipulation extensions
    ERMS                = 9,    ///< Supports Enhanced REP MOVSB/STOSB
    INVPCID             = 10,   ///< Supports Invalidate Processor Context ID
    RTM                 = 11,   ///< Supports Restricted Transactional Memory
    PQM                 = 12,
    FPUCSDS             = 13,   ///< Supports Deprecates FPU CS and FPU DS values
    IMPX                = 14,   ///< Supports Intel Memory Protection Extensions
    PQE                 = 15,
    AVX512_F            = 16,   ///< Supports AVX512 Foundation
    AVX512_DQ           = 17,   ///< Supports AVX512 Doubleword and Quadword instructions
    RDSEED              = 18,   ///< Supports RDSEED instruction
    ADX                 = 19,   ///< Supports ADCX and ADOX instructions
    SMAP                = 20,   ///< Supports Supervisor-Mode Access Prevention
    AVX512_IFMA         = 21,   ///< Supports AVX512 Integer Fused Multiply Add
    PCOMMIT             = 22,   ///< Supports PCOMMIT instruction
    CLFLUSHOPT          = 23,   ///< Supports CLFLUSHOPT instruction
    CLWB                = 24,   ///< Supports CLWB instruction
    IPT                 = 25,   ///< Supports Intel Processor Trace
    AVX512_PF           = 26,   ///< Supports AVX512 Prefetch instruction
    AVX512_ER           = 27,   ///< Supports AVX512 Exponential and Reciprocal instructions
    AVX512_CD           = 28,   ///< Supports AVX512 Conflict Detection instructions
    SHA                 = 29,   ///< Supports Intel SHA Extensions
    AVX512_BW           = 30,   ///< Supports AVX512 Byte and Word instructions
    AVX512_VL           = 31,   ///< Supports AVX512 Vector Length Extentions
};

// @enum Feature4
enum class Feature4 : DWORD {
    PREFETCHWT1         = 0,    ///< Supports PREFETCHWT1 instruction
    AVX512_VBMI         = 1,    ///< Supports AVX512 Vector Byte Manipulation Instructions
    UMIP                = 2,
    PKU                 = 3,
    OSPKE               = 4,
    WAITPKG             = 5,
    AVX512_VBMI2        = 6,    ///< Supports AVX512 Vector Byte Manipulation Instructions 2
    CET_SS              = 7,
    GFNI                = 8,
    VAES                = 9,
    VPCLMULQDQ          = 10,
    AVX512_VNNI         = 11,   ///< Supports AVX512 Vector Neural Network Instructions
    AVX512_BITALG       = 12,   ///< Supports AVX512 Bit Algorithms instructions
    // reserved 13
    AVX512_VPOPCNTDQ    = 14,   ///< Supports AVX512 Vector Population Count instruction
    // reserved 15
    // reserved 16
    // reserved 17
    // reserved 18
    // reserved 19
    // reserved 20
    // reserved 21
    RDPID               = 22,
    // reserved 23
    // reserved 24
    CLDEMOTE            = 25,
    // reserved 26
    MOVDIRI             = 27,
    MOVDIR64B           = 28,
    ENQCMD              = 29,
    SGX_LC              = 30,
    PKS                 = 31,
};

// @enum Feature5
enum class Feature5 : DWORD {
    // reserved 0
    // reserved 1
    AVX512_4VNNIW           = 2,    ///< Supports AVX512 Vector Neural Network Instructions Word variable precision
    AVX512_4FMAPS           = 3,    ///< Supports AVX512 Fused Multiply Accumulation Packed Single precision
    FSRM                    = 4,
    // reserved 5
    // reserved 6
    // reserved 7
    AVX512_VP2INTERSECT     = 8,    ///< Supports AVX512 Vector Pair Intersection to a Pair of Mask Registers
    SRBDS_CTRL              = 9,
    MD_CLEAR                = 10,
    // reserved 11
    // reserved 12
    TSX_FORCE_ABORT         = 13,
    SERIALIZE               = 14,
    HYBRID                  = 15,
    TSXLDTRK                = 16,
    // reserved 17
    PCONFIG                 = 18,
    LBR                     = 19,
    CET_IBT                 = 20,
    // reserved 21
    AMX_BF16                = 22,
    // reserved 23
    AMX_TILE                = 24,
    AMX_INT8                = 25,
    IBRS_IBPB               = 26,
    STIBP                   = 27,
    L1D_FLUSH               = 28,
    IA32_ARCH_CAPABILITIES  = 29,
    IA32_CORE_CAPABILITIES  = 30,
    SSDB                    = 31,
};

// @enum Feature6
enum class Feature6 : DWORD {
    // reserved 0
    // reserved 1
    // reserved 2
    // reserved 3
    // reserved 4
    AVX512_BF16         = 5,  ///< Supports AVX512 16-bit Float instructions
    // reserved 6
    // reserved 7
    // reserved 8
    // reserved 9
    // reserved 10
    // reserved 11
    // reserved 12
    // reserved 13
    // reserved 14
    // reserved 15
    // reserved 16
    // reserved 17
    // reserved 18
    // reserved 19
    // reserved 20
    // reserved 21
    // reserved 22
    // reserved 23
    // reserved 24
    // reserved 25
    // reserved 26
    // reserved 27
    // reserved 28
    // reserved 29
    // reserved 30
    // reserved 31
};

// @enum ExtFeature
enum class ExtFeature : DWORD {
    FPU                 = 0,    ///< Supports Intel387 float instruction unit
    VME                 = 1,    ///< Supports v86 mode
    DE                  = 2,    ///< Supports I/O break
    PSE                 = 3,    ///< Supports 4MiB page
    TSC                 = 4,    ///< Supports Time Stamp Counter
    MSR                 = 5,    ///< Supports Model Specific Register(RDMSR, WRMSR)
    PAE                 = 6,    ///< Supports Physical Address Extension
    MCE                 = 7,    ///< Supports Machine Check Exception
    CX8                 = 8,    ///< Supports CMPXCHG8 instruction
    APIC                = 9,    ///< Supports On chip APIC
    // reserved 10
    SYS_CALL            = 11,   ///< Supports SYSCALL/SYSRET instructions
    MTRR                = 12,   ///< Supports Memory Type Range Ragister
    PGE                 = 13,   ///< Supports PTR Global Bit
    MCA                 = 14,   ///< Supports Machine Check Architecture
    CMOV                = 15,   ///< Supports Conditional Move instructions
    PAT                 = 16,   ///< Supports Page Attribute Table
    PSE_36              = 17,   ///< Supports 36-bit page size extension
    // reserved 18
    MP                  = 19,   ///< Supports Multiprocessing Capable
    NX_XD               = 20,   ///< Suports No-eXecute Page Protection
    // reserved 21
    MMX_PLUS            = 22,   ///< Supports MMX Extensions
    MMX                 = 23,   ///< Supports Intel MMX Technology
    FXSR                = 24,   ///< Supports FXSAVE and FXRSTOR instructions
    FFXSR               = 25,   ///< Supports FXSAVE/FXRSTORE optimization
    PAGE_1GB            = 26,   ///< Supports 1GiB large page
    RDTSCP              = 27,   ///< Supports RDTSCP instruction
    // reserved 28
    LM                  = 29,   ///< Supports AMD64/Intel64 Long Mode
    AMD_3DNOW_PLUS      = 30,   ///< Supports 3DNow! instruction extensions
    AMD_3DNOW           = 31,   ///< Supports 3DNow! instructions
};

// @enum ExtFeature2
enum class ExtFeature2 : DWORD {
    LAHF                = 0,    ///< Suports 64-bit mode LAHF/SAHF instructions
    CMP_LEGACY          = 1,    ///< Core Multi-Proceessing legacy mode
    SVM                 = 2,    ///< Suports Secure Virtual Machine
    EAS                 = 3,    ///< Suports Extended APIC
    AMC8                = 4,    ///< Suports 
    ABM                 = 5,    ///< Suports Advanced Bit Manipulation
    SSE4A               = 6,    ///< Suports Streaming SIMD Extension 4a
    MASSE               = 7,    ///< Suports Misaligned SSE mode
    PREFETCH            = 8,    ///< Suports PREFETCH/PREFETCHW instructions
    OSVW                = 9,    ///< Suports OS Visible Workaround
    IBS                 = 10,   ///< Suports Instruction Based Sampling
    XOP                 = 11,   ///< Suports eXtended Operations
    SKINIT              = 12,   ///< Suports SKINIT/STGI instructions
    WDT                 = 13,   ///< Suports Watch Dog Timer
    // reserved 14
    LWP                 = 15,   ///< Supports Light Weight Profiling
    FMA4                = 16,   ///< Supports 4 operands FMA instructions
    TCE                 = 17,   ///< Supports Translation Cache Extension
    // reserved 18
    MSR                 = 19,
    // reserved 20
    TBM                 = 21,   ///< Supports Trailing Bit Manipulation instruction
    TOPOLOGY_EXT        = 22,   ///< Supports Topology Extensions
    PERFCTR_CORE        = 23,
    PERFCTR_NB          = 24,
    // reserved 25
    DBX                 = 26,
    PERFTSC             = 27,
    PERFCTR_L2          = 28,
    // reserved 29
    // reserved 30
    // reserved 31
};

// @enum ExtFeature3
enum class ExtFeature3 : DWORD {
    TS                  = 0,    ///< Supports Temperature Sensor
    FID                 = 1,    ///< Supports Frequency ID Control
    VID                 = 2,    ///< Supports Voltage ID Control
    TTP                 = 3,    ///< Supports Thermal Trip
    TM                  = 4,    ///< Supports Thermal Monitoring
    STC                 = 5,    ///< Supports Software Thermal Control
    MUL                 = 6,    ///< Supports 100MHz Multiplier Steps
    HWPS                = 7,    ///< Supports Hardware P-State Control
    ITSC                = 8,    ///< Supports Invariant TSC
    // reserved 9
    // reserved 10
    // reserved 11
    // reserved 12
    // reserved 13
    // reserved 14
    // reserved 15
    // reserved 16
    // reserved 17
    // reserved 18
    // reserved 19
    // reserved 20
    // reserved 21
    // reserved 22
    // reserved 23
    // reserved 24
    // reserved 25
    // reserved 26
    // reserved 27
    // reserved 28
    // reserved 29
    // reserved 30
    // reserved 31
};

/// @enum CacheType
enum class CacheType : DWORD {
    Null,           ///< Null, no more caches
    Data,           ///< Data cache
    Instruction,    ///< Instruction cache
    Unified,        ///< Unified cache
};

/// @enum TopologyLevelType
enum class TopologyLevelType : DWORD {
    Invalid,
    Thread,
    Core,
};

/// @enum CacheAssociativity
enum class CacheAssociativity : DWORD {
    Disabled        = 0x00,
    DirectMapped    = 0x01,
    Way2            = 0x02,
//  reserved        = 0x03,
    Way4            = 0x04,
//  reserved        = 0x05,
    Way8            = 0x06,
//  reserved        = 0x07,
    Way16           = 0x08,
//  reserved        = 0x09,
    Way32           = 0x0a,
    Way48           = 0x0b,
    Way64           = 0x0c,
    Way96           = 0x0d,
    Way128          = 0x0e,
    Full            = 0x0f,
};

/// @struct Context_t
struct Context_t {
    DWORD EAX_00000000H[4];
    DWORD EAX_00000001H[4];
    DWORD EAX_00000002H[4];
    DWORD EAX_00000003H[4];
    DWORD EAX_00000004H[CPUINFO_MAX_CACHES][4];
    DWORD EAX_00000005H[4];
    DWORD EAX_00000006H[4];
    DWORD EAX_00000007H[CPUINFO_MAX_EXT_FEATURE_SUBLEAFS + 1][4];
    DWORD EAX_00000009H[4];
    DWORD EAX_0000000AH[4];
    DWORD EAX_0000000BH[CPUINFO_MAX_PROCESSOR_TOPOLOGY_LEVELS][4];
    DWORD EAX_0000000DH[4];
    DWORD EAX_00000016H[4];

    DWORD EAX_80000000H[4];
    DWORD EAX_80000001H[4];
    DWORD EAX_80000002H[4];
    DWORD EAX_80000003H[4];
    DWORD EAX_80000004H[4];
    DWORD EAX_80000005H[4];
    DWORD EAX_80000006H[4];
    DWORD EAX_80000007H[4];
    DWORD EAX_80000008H[4];
    DWORD EAX_8000000AH[4];
    DWORD EAX_80000010H[4];
    DWORD EAX_80000019H[4];
    DWORD EAX_8000001AH[4];
    DWORD EAX_8000001BH[4];
    DWORD EAX_8000001CH[4];
    DWORD EAX_8000001DH[CPUINFO_MAX_CACHES][4];
    DWORD EAX_8000001EH[4];
};


/// @brief Get and initialize Context_t
void Init(Context_t *dstCtx) {
    if (dstCtx == nullptr) {
        return;
    }

    Context_t ctx = { 0 };

    detail::cpuid(ctx.EAX_00000000H, 0x00, 0x00);
    detail::cpuid(ctx.EAX_00000001H, 0x01, 0x00);
    detail::cpuid(ctx.EAX_00000002H, 0x02, 0x00);

    const DWORD MaxLevel = ctx.EAX_00000000H[0];

    if (0x03u <= MaxLevel) {
        detail::cpuid(ctx.EAX_00000003H, 0x03, 0x00);
    }
    if (0x04u <= MaxLevel) {
        for (DWORD ecx = 0; ecx < CPUINFO_MAX_CACHES; ++ecx) {
            detail::cpuid(ctx.EAX_00000004H[ecx], 0x04, ecx);
        }
    }
    if (0x05u <= MaxLevel) {
        detail::cpuid(ctx.EAX_00000005H, 0x05, 0x00);
    }
    if (0x06u <= MaxLevel) {
        detail::cpuid(ctx.EAX_00000006H, 0x06, 0x00);
    }
    if (0x07u <= MaxLevel) {
        detail::cpuid(ctx.EAX_00000007H[0], 0x07, 0);
        
        
        DWORD MaxSubLeafs = ctx.EAX_00000007H[0][0];
        for (DWORD ecx = 1; ecx <= MaxSubLeafs; ++ecx) {
            if (CPUINFO_MAX_EXT_FEATURE_SUBLEAFS < ecx) {
                break;
            }
            detail::cpuid(ctx.EAX_00000007H[ecx], 0x07, ecx);
        }
    }
    if (0x09u <= MaxLevel) {
        detail::cpuid(ctx.EAX_00000009H, 0x09, 0x00);
    }
    if (0x0Au <= MaxLevel) {
        detail::cpuid(ctx.EAX_0000000AH, 0x0A, 0x00);
    }
    if (0x0Bu <= MaxLevel) {
        for (DWORD ecx = 0; ecx < CPUINFO_MAX_PROCESSOR_TOPOLOGY_LEVELS; ++ecx) {
            detail::cpuid(ctx.EAX_0000000BH[ecx], 0x0B, ecx);
        }
    }
    if (0x0Du <= MaxLevel) {
        detail::cpuid(ctx.EAX_0000000DH, 0x0D, 0x00);
    }
    if (0x16u <= MaxLevel) {
        detail::cpuid(ctx.EAX_00000016H, 0x16, 0x00);
    }

    // Extended area
    detail::cpuid(ctx.EAX_80000000H, 0x80000000, 0x00);

    const DWORD MaxExtLevel = ctx.EAX_80000000H[0];

    if (0x80000001u <= MaxExtLevel) {
        detail::cpuid(ctx.EAX_80000001H, 0x80000001, 0x00);
    }
    if (0x80000004u <= MaxExtLevel) {
        detail::cpuid(ctx.EAX_80000002H, 0x80000002, 0x00);
        detail::cpuid(ctx.EAX_80000003H, 0x80000003, 0x00);
        detail::cpuid(ctx.EAX_80000004H, 0x80000004, 0x00);
    }
    if (0x80000005u <= MaxExtLevel) {
        detail::cpuid(ctx.EAX_80000005H, 0x80000005, 0x00);
    }
    if (0x80000006u <= MaxExtLevel) {
        detail::cpuid(ctx.EAX_80000006H, 0x80000006, 0x00);
    }
    if (0x80000007u <= MaxExtLevel) {
        detail::cpuid(ctx.EAX_80000007H, 0x80000007, 0x00);
    }
    if (0x80000008u <= MaxExtLevel) {
        detail::cpuid(ctx.EAX_80000008H, 0x80000008, 0x00);
    }
    if (0x8000000Au <= MaxExtLevel) {
        detail::cpuid(ctx.EAX_8000000AH, 0x8000000A, 0x00);
    }
    if (0x80000010u <= MaxExtLevel) {
        detail::cpuid(ctx.EAX_80000010H, 0x80000010, 0x00);
    }
    if (0x80000019u <= MaxExtLevel) {
        detail::cpuid(ctx.EAX_80000019H, 0x80000019, 0x00);
    }
    if (0x8000001Au <= MaxExtLevel) {
        detail::cpuid(ctx.EAX_8000001AH, 0x8000001A, 0x00);
    }
    if (0x8000001Bu <= MaxExtLevel) {
        detail::cpuid(ctx.EAX_8000001BH, 0x8000001B, 0x00);
    }
    if (0x8000001Cu <= MaxExtLevel) {
        detail::cpuid(ctx.EAX_8000001CH, 0x8000001C, 0x00);
    }
    if (0x8000001Du <= MaxExtLevel) {
        for (DWORD ecx = 0; ecx < CPUINFO_MAX_CACHES; ++ecx) {
            detail::cpuid(ctx.EAX_8000001DH[ecx], 0x8000001D, ecx);
        }
    }
    if (0x8000001Eu <= MaxExtLevel) {
        detail::cpuid(ctx.EAX_8000001EH, 0x8000001E, 0x00);
    }

    dstCtx[0] = ctx;
}


//----------------------------------------------------------------------------------------------------
// Feature
//----------------------------------------------------------------------------------------------------
template<typename T>
bool HasFeature(const T feature, const Context_t &info) {
    return false;
}

template<>
bool HasFeature<Feature>(const Feature f, const Context_t &ctx) {
    return (ctx.EAX_00000001H[3] & (1u << (static_cast<DWORD>(f) & 0x1f))) != 0;
}

template<>
bool HasFeature<Feature2>(const Feature2 f, const Context_t &ctx) {
    return (ctx.EAX_00000001H[2] & (1u << (static_cast<DWORD>(f) & 0x1f))) != 0;
}

template<>
bool HasFeature<Feature3>(const Feature3 f, const Context_t &ctx) {
    return (ctx.EAX_00000007H[0][1] & (1u << (static_cast<DWORD>(f) & 0x1f))) != 0;
}

template<>
bool HasFeature<Feature4>(const Feature4 f, const Context_t &ctx) {
    return (ctx.EAX_00000007H[0][2] & (1u << (static_cast<DWORD>(f) & 0x1f))) != 0;
}

template<>
bool HasFeature<Feature5>(const Feature5 f, const Context_t &ctx) {
    return (ctx.EAX_00000007H[0][3] & (1u << (static_cast<DWORD>(f) & 0x1f))) != 0;
}

template<>
bool HasFeature<Feature6>(const Feature6 f, const Context_t &ctx) {
    return (ctx.EAX_00000007H[1][0] & (1u << (static_cast<DWORD>(f) & 0x1f))) != 0;
}

template<>
bool HasFeature<ExtFeature>(const ExtFeature f, const Context_t &ctx) {
    return (ctx.EAX_80000001H[3] & (1u << (static_cast<DWORD>(f) & 0x1f))) != 0;
}

template<>
bool HasFeature<ExtFeature2>(const ExtFeature2 f, const Context_t &ctx) {
    return (ctx.EAX_80000001H[2] & (1u << (static_cast<DWORD>(f) & 0x1f))) != 0;
}

template<>
bool HasFeature<ExtFeature3>(const ExtFeature3 f, const Context_t &ctx) {
    return (ctx.EAX_80000007H[3] & (1u << (static_cast<DWORD>(f) & 0x1f))) != 0;
}

//----------------------------------------------------------------------------------------------------
// Standard area
//----------------------------------------------------------------------------------------------------

// 00000000H Vendor-ID and Largest Standard Function

/// @brief Get the muximum number of standard function supported
CPUINFO_INLINE DWORD GetMaxSupportLevel(const Context_t &ctx) {
    return ctx.EAX_00000000H[0];
}

/// @brief Get the Vender-ID string(ASCII string)
CPUINFO_INLINE void GetVendorID(char *dst, const Context_t &ctx) {
    reinterpret_cast<DWORD *>(dst + 0)[0] = ctx.EAX_00000000H[1];
    reinterpret_cast<DWORD *>(dst + 4)[0] = ctx.EAX_00000000H[3];
    reinterpret_cast<DWORD *>(dst + 8)[0] = ctx.EAX_00000000H[2];
    dst[12] = '\0';
}

// 00000001H Feature Information

/// @brief Get the processor stepping
CPUINFO_INLINE DWORD GetProcessorStepping(const Context_t &ctx) {
    return ctx.EAX_00000001H[0] & 0x0f;
}

/// @brief Get the processor model
CPUINFO_INLINE DWORD GetProcessorModel(const Context_t &ctx) {
    return (ctx.EAX_00000001H[0] >> 4) & 0x0f;
}

/// @brief Get the processor family
CPUINFO_INLINE DWORD GetProcessorFamily(const Context_t &ctx) {
    return (ctx.EAX_00000001H[0] >> 8) & 0x0f;
}

/// @brief Get the processor type
CPUINFO_INLINE ProcessorType GetProcessorType(const Context_t &ctx) {
    return static_cast<ProcessorType>((ctx.EAX_00000001H[0] >> 12) & 0x03);
}

/// @brief Get the processor extended model
CPUINFO_INLINE DWORD GetProcessorExtendedModel(const Context_t &ctx) {
    return (ctx.EAX_00000001H[0] >> 16) & 0x03;
}

/// @brief Get the processor extended family
CPUINFO_INLINE DWORD GetProcessorExtendedFamily(const Context_t &ctx) {
    return (ctx.EAX_00000001H[0] >> 20) & 0xff;
}

/// @brief Get the brand index
CPUINFO_INLINE DWORD GetBlandIndex(const Context_t &ctx) {
    return ctx.EAX_00000001H[1] & 0xff;
}

/// @brief Get the CLFLUSH line size(Value * 8 = cache line size in bytes)
CPUINFO_INLINE DWORD GetCLFlushLineSizeInBytes(const Context_t &ctx) {
    return ((ctx.EAX_00000001H[1] >> 8) & 0xff) * 8;
}

/// @brief Get muximum number of logical processors per package(or can also be considered the number of APIC IDs reserved for this package)
CPUINFO_INLINE DWORD GetMaxLogicalProcessorsPerPackage(const Context_t &ctx) {
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(Feature::HTT, ctx) && !HasFeature(ExtFeature2::CMP_LEGACY, ctx)) {
            return 1;
        }
    }
    return (ctx.EAX_00000001H[1] >> 16) & 0xff;
}

/// @brief Get the default APIC ID
CPUINFO_INLINE DWORD GetAPICPhysicalID(const Context_t &ctx) {
    return (ctx.EAX_00000001H[1] >> 24) & 0xff;
}

// 00000002H Cache Descriptors

// 00000003H Processor Serial Number

/// @brief Get the processor serial number(Available in Pentinum III processor only)
CPUINFO_INLINE void GetProcessorSerialNumber(WORD dst[6], const Context_t &ctx) {
    if (HasFeature(Feature::PSN, ctx)) {
        dst[0] = ((ctx.EAX_00000001H[0] >> 16) & 0xffff);
        dst[1] = (ctx.EAX_00000001H[0] & 0xffff);
        dst[2] = ((ctx.EAX_00000003H[3] >> 16) & 0xffff);
        dst[3] = (ctx.EAX_00000003H[3] & 0xffff);
        dst[4] = ((ctx.EAX_00000003H[2] >> 16) & 0xffff);
        dst[5] = (ctx.EAX_00000003H[2] & 0xffff);
    } else {
        dst[0] = 0;
        dst[1] = 0;
        dst[2] = 0;
        dst[3] = 0;
        dst[4] = 0;
        dst[5] = 0;
    }
}

// 00000004H Deterministic Cache Parameters

/// @brief Get the cache type
CPUINFO_INLINE CacheType GetCacheType(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_CACHES <= index) {
        return CacheType::Null;
    }
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(ExtFeature2::TOPOLOGY_EXT, ctx)) {
            return CacheType::Null;
        }
        return static_cast<CacheType>(ctx.EAX_8000001DH[index][0] & 0x1f);
    }
    return static_cast<CacheType>(ctx.EAX_00000004H[index][0] & 0x1f);
}

/// @brief Get the cache level
CPUINFO_INLINE DWORD GetCacheLevel(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_CACHES <= index) {
        return 0;
    }
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(ExtFeature2::TOPOLOGY_EXT, ctx)) {
            return 0;
        }
        return (ctx.EAX_8000001DH[index][0] >> 5) & 0x7;
    }
    return (ctx.EAX_00000004H[index][0] >> 5) & 0x7;
}

/// @brief Get the self initializing cache level
CPUINFO_INLINE bool GetSelfInitializingCacheLevel(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_CACHES <= index) {
        return false;
    }
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(ExtFeature2::TOPOLOGY_EXT, ctx)) {
            return false;
        }
        return ((ctx.EAX_8000001DH[index][0] >> 8) & 0x1) != 0;
    }
    return ((ctx.EAX_00000004H[index][0] >> 8) & 0x1) != 0;
}

/// @brief Get the full associative cache
CPUINFO_INLINE bool GetFullyAssociativeCache(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_CACHES <= index) {
        return false;
    }
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(ExtFeature2::TOPOLOGY_EXT, ctx)) {
            return 0;
        }
        return ((ctx.EAX_8000001DH[index][0] >> 9) & 0x1) != 0;
    }
    return ((ctx.EAX_00000004H[index][0] >> 9) & 0x1) != 0;
}

/// @brief Get maximum number of threads sharing this cache
CPUINFO_INLINE DWORD GetMaxThreadSharingCache(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_CACHES <= index) {
        return 0;
    }
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(ExtFeature2::TOPOLOGY_EXT, ctx)) {
            return 0;
        }
        return ((ctx.EAX_8000001DH[index][0] >> 14) & 0xfff) + 1;
    }
    return ((ctx.EAX_00000004H[index][0] >> 14) & 0xfff) + 1;
}

/// @brief Get the maximum number of processor cores in this physical processor package
CPUINFO_INLINE DWORD GetMaxCoresPerPackage(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_CACHES <= index) {
        return 0;
    }
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(ExtFeature2::TOPOLOGY_EXT, ctx)) {
            return 0;
        }
        return ((ctx.EAX_8000001DH[index][0] >> 26) & 0x3f) + 1;
    }
    return ((ctx.EAX_00000004H[index][0] >> 26) & 0x3f) + 1;
}

/// @brief Get the system coherency line size
CPUINFO_INLINE DWORD GetSystemCoherencyLineSize(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_CACHES <= index) {
        return 0;
    }
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(ExtFeature2::TOPOLOGY_EXT, ctx)) {
            return 0;
        }
        return (ctx.EAX_8000001DH[index][1] & 0xfff) + 1;
    }
    return (ctx.EAX_00000004H[index][1] & 0xfff) + 1;
}

/// @brief Get the physical line partitions
CPUINFO_INLINE DWORD GetPhysicalLinePartitions(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_CACHES <= index) {
        return 0;
    }
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(ExtFeature2::TOPOLOGY_EXT, ctx)) {
            return 0;
        }
        return ((ctx.EAX_8000001DH[index][1] >> 12) & 0x3ff) + 1;
    }
    return ((ctx.EAX_00000004H[index][1] >> 12) & 0x3ff) + 1;
}

/// @brief Get the ways of associativity
CPUINFO_INLINE DWORD GetWaysAssociativity(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_CACHES <= index) {
        return 0;
    }
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(ExtFeature2::TOPOLOGY_EXT, ctx)) {
            return 0;
        }
        return ((ctx.EAX_8000001DH[index][1] >> 22) & 0x3ff) + 1;
    }
    return ((ctx.EAX_00000004H[index][1] >> 22) & 0x3ff) + 1;
}

/// @brief Get number of sets
CPUINFO_INLINE DWORD GetCacheNumSets(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_CACHES <= index) {
        return 0;
    }
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(ExtFeature2::TOPOLOGY_EXT, ctx)) {
            return 0;
        }
        return ctx.EAX_8000001DH[index][2] + 1;
    }
    return ctx.EAX_00000004H[index][2] + 1;
}

/// @brief Get the write back invalidate
CPUINFO_INLINE bool GetWriteBackInvalidate(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_CACHES <= index) {
        return false;
    }
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(ExtFeature2::TOPOLOGY_EXT, ctx)) {
            return false;
        }
        return (ctx.EAX_8000001DH[index][3] & 0x1) != 0;
    }
    return (ctx.EAX_00000004H[index][3] & 0x1) != 0;
}

/// @brief Get the cache inclusiveness
CPUINFO_INLINE bool GetCacheInclusiveness(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_CACHES <= index) {
        return false;
    }
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(ExtFeature2::TOPOLOGY_EXT, ctx)) {
            return false;
        }
        return ((ctx.EAX_8000001DH[index][3] >> 1) & 0x1) != 0;
    }
    return ((ctx.EAX_00000004H[index][3] >> 1) & 0x1) != 0;
}

/// @brief Get the complex cache indexing
CPUINFO_INLINE bool GetCacheComplexCacheIndexing(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_CACHES <= index) {
        return false;
    }
    // Verify that VenderID is "AuthenticAMD"
    if ((ctx.EAX_00000000H[1] == 0x68747541) && (ctx.EAX_00000000H[3] == 0x69746e65) && (ctx.EAX_00000000H[2] == 0x444d4163)) {
        if (!HasFeature(ExtFeature2::TOPOLOGY_EXT, ctx)) {
            return false;
        }
        return ((ctx.EAX_8000001DH[index][3] >> 2) & 0x1) != 0;
    }
    return ((ctx.EAX_00000004H[index][3] >> 2) & 0x1) != 0;
}

/// @brief Get specified cache capacity in bytes
CPUINFO_INLINE DWORD GetCacheSize(const DWORD index, const Context_t &ctx) {
    return GetSystemCoherencyLineSize(index, ctx) * GetPhysicalLinePartitions(index, ctx) * GetWaysAssociativity(index, ctx) * GetCacheNumSets(index, ctx);
}

// 00000005H MONITOR/MWAIT Parameters

/// @brief Get the smallest monitor line size in bytes
CPUINFO_INLINE DWORD GetSmallestMonitorLineSizeInBytes(const Context_t &ctx) {
    return ctx.EAX_00000005H[0] & 0xffff;
}

/// @brief Get the largest monitor line size in bytes
CPUINFO_INLINE DWORD GetLargestMonitorLineSizeInBytes(const Context_t &ctx) {
    return ctx.EAX_00000005H[1] & 0xffff;
}

/// @brief Get supported status of MONITOR/MWAIT extensions
CPUINFO_INLINE bool GetSupportedMONITORAndMWAITExtension(const Context_t &ctx) {
    return (ctx.EAX_00000005H[2] & 0x1) != 0;
}

/// @brief Get supported status for treating interrupts as break-events for MWAIT
CPUINFO_INLINE bool GetSupportedInterruptAsBreakEventForMWAIT(const Context_t &ctx) {
    return ((ctx.EAX_00000005H[2] >> 1) & 0x1) != 0;
}

/// @brief Get number of C0 sub-states supported using MONITOR/MWAIT
CPUINFO_INLINE bool GetNumC0SubStates(const Context_t &ctx) {
    return ctx.EAX_00000005H[3] & 0xf;
}

/// @brief Get number of C1 sub-states supported using MONITOR/MWAIT
CPUINFO_INLINE bool GetNumC1SubStates(const Context_t &ctx) {
    return (ctx.EAX_00000005H[3] >> 4) & 0xf;
}

/// @brief Get number of C2 sub-states supported using MONITOR/MWAIT
CPUINFO_INLINE bool GetNumC2SubStates(const Context_t &ctx) {
    return (ctx.EAX_00000005H[3] >> 8) & 0xf;
}

/// @brief Get number of C3 sub-states supported using MONITOR/MWAIT
CPUINFO_INLINE bool GetNumC3SubStates(const Context_t &ctx) {
    return (ctx.EAX_00000005H[3] >> 12) & 0xf;
}

/// @brief Get number of C4 sub-states supported using MONITOR/MWAIT
CPUINFO_INLINE bool GetNumC4SubStates(const Context_t &ctx) {
    return (ctx.EAX_00000005H[3] >> 16) & 0xf;
}

// 00000006H Digital Thermal Sensor and Power Management Parameters
// 00000007H Structured Extended Feature Flags Enumeration
// 00000008H Reserved
// 00000009H Direct Cache Access Parameters
// 0000000AH Architectural Performance Monitor Features
// 0000000BH x2APIC Features/Processor Topology

/// @brief Get number of bits to shift right APIC ID to get next level APIC ID
CPUINFO_INLINE DWORD GetShiftAPICIDBits(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_PROCESSOR_TOPOLOGY_LEVELS <= index) {
        return 0;
    }
    return ctx.EAX_0000000BH[index][0] & 0x1f;
}

/// @brief Get number of factory-configured logical processors at the level
CPUINFO_INLINE DWORD GetNumFCLogicalProcessors(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_PROCESSOR_TOPOLOGY_LEVELS <= index) {
        return 0;
    }
    return ctx.EAX_0000000BH[index][1] & 0xffff;
}

/// @brief Get the level number
CPUINFO_INLINE DWORD GetTopologyLevel(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_PROCESSOR_TOPOLOGY_LEVELS <= index) {
        return 0;
    }
    return ctx.EAX_0000000BH[index][2] & 0xff;
}

/// @brief Get the level type
CPUINFO_INLINE TopologyLevelType GetTopologyLevelType(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_PROCESSOR_TOPOLOGY_LEVELS <= index) {
        return TopologyLevelType::Invalid;
    }
    return static_cast<TopologyLevelType>((ctx.EAX_0000000BH[index][2] >> 8) & 0xff);
}

/// @brief Get the extended APIC ID
CPUINFO_INLINE DWORD GetExtendedAPICID(const DWORD index, const Context_t &ctx) {
    if (CPUINFO_MAX_PROCESSOR_TOPOLOGY_LEVELS <= index) {
        return 0;
    }
    return ctx.EAX_0000000BH[index][3];
}

// 0000000CH Reserved
// 0000000DH XSAVE Features
// 0000000EH
// 0000000FH
// 00000010H
// 00000011H
// 00000012H
// 00000013H
// 00000014H
// 00000015H
// 00000016H

/// @brief Get the processsor base frequency
CPUINFO_INLINE DWORD GetProcessorBaseFrequency(const Context_t &ctx) {
    return ctx.EAX_00000016H[0] & 0xffff;
}

/// @brief Get the processsor max frequency
CPUINFO_INLINE DWORD GetMaxFrequency(const Context_t &ctx) {
    return ctx.EAX_00000016H[1] & 0xffff;
}

/// @brief Get the bus frequency
CPUINFO_INLINE DWORD GetBusFrequency(const Context_t &ctx) {
    return ctx.EAX_00000016H[1] & 0xffff;
}


//----------------------------------------------------------------------------------------------------
// Extended area
//----------------------------------------------------------------------------------------------------

// 80000000H Largest Extended Function

/// @brief Get the muximum number of extended function supported
CPUINFO_INLINE DWORD GetMaxExtendedSupportLevel(const Context_t &ctx) {
    return ctx.EAX_80000000H[0];
}

// 80000001H Extended Frature Bits
// 80000002H - 80000004H Processor Brand String

/// @brief Get processor brand string(ASCII string)
CPUINFO_INLINE void GetBrandString(char *dst, const Context_t &ctx) {
    reinterpret_cast<DWORD *>(dst +  0)[0] = ctx.EAX_80000002H[0];
    reinterpret_cast<DWORD *>(dst +  4)[0] = ctx.EAX_80000002H[1];
    reinterpret_cast<DWORD *>(dst +  8)[0] = ctx.EAX_80000002H[2];
    reinterpret_cast<DWORD *>(dst + 12)[0] = ctx.EAX_80000002H[3];
    reinterpret_cast<DWORD *>(dst + 16)[0] = ctx.EAX_80000003H[0];
    reinterpret_cast<DWORD *>(dst + 20)[0] = ctx.EAX_80000003H[1];
    reinterpret_cast<DWORD *>(dst + 24)[0] = ctx.EAX_80000003H[2];
    reinterpret_cast<DWORD *>(dst + 28)[0] = ctx.EAX_80000003H[3];
    reinterpret_cast<DWORD *>(dst + 32)[0] = ctx.EAX_80000004H[0];
    reinterpret_cast<DWORD *>(dst + 36)[0] = ctx.EAX_80000004H[1];
    reinterpret_cast<DWORD *>(dst + 40)[0] = ctx.EAX_80000004H[2];
    reinterpret_cast<DWORD *>(dst + 44)[0] = ctx.EAX_80000004H[3];
    dst[48] = '\0';
}

// 80000005H Reserved
// 80000006H Extended L2 Cache Features

/// @brief Get the L2 instruction TLB number of entries for 2MB and 4MB pages
CPUINFO_INLINE DWORD GetL2ITLBEntriesFor2MBAnd4MBPages(const Context_t &ctx) {
    return ctx.EAX_80000006H[0] & 0xfff;
}

/// @brief Get the L2 instruction TLB associativity for 2MB and 4MB pages
CPUINFO_INLINE DWORD GetL2ITLBAssociativityFor2MBAnd4MBPages(const Context_t &ctx) {
    return (ctx.EAX_80000006H[0] >> 12) & 0xf;
}

/// @brief Get the L2 data TLB number of entries for 2MB and 4MB pages
CPUINFO_INLINE DWORD GetL2DTLBEntriesFor2MBAnd4MBPages(const Context_t &ctx) {
    return (ctx.EAX_80000006H[0] >> 16) & 0xfff;
}

/// @brief Get the L2 data TLB associativity for 2MB and 4MB pages
CPUINFO_INLINE DWORD GetL2DTLBAssociativityFor2MBAnd4MBPages(const Context_t &ctx) {
    return (ctx.EAX_80000006H[0] >> 28) & 0xf;
}

/// @brief Get the L2 instruction TLB number of entries for 4KB pages
CPUINFO_INLINE DWORD GetL2ITLBEntriesFor4KBPages(const Context_t &ctx) {
    return ctx.EAX_80000006H[1] & 0xfff;
}

/// @brief Get the L2 instruction TLB associativity for 4KB pages
CPUINFO_INLINE DWORD GetL2ITLBAssociativityFor4KBPages(const Context_t &ctx) {
    return (ctx.EAX_80000006H[1] >> 12) & 0xf;
}

/// @brief Get the L2 data TLB number of entries for 4KB pages
CPUINFO_INLINE DWORD GetL2DTLBEntriesFor4KBPages(const Context_t &ctx) {
    return (ctx.EAX_80000006H[1] >> 16) & 0xfff;
}

/// @brief Get the L2 data TLB associativity for 4KB pages
CPUINFO_INLINE DWORD GetL2DTLBAssociativityFor4KBPages(const Context_t &ctx) {
    return (ctx.EAX_80000006H[1] >> 28) & 0xf;
}

/// @brief L2 cache line size in bytes
CPUINFO_INLINE DWORD GetL2CacheLineSize(const Context_t &ctx) {
    return ctx.EAX_80000006H[2] & 0xff;
}

/// @brief Get the L2 cache line per tag
CPUINFO_INLINE DWORD GetL2CacheLinePerTag(const Context_t &ctx) {
    return ((ctx.EAX_80000006H[2] >> 8) & 0xf) != 0;
}

/// @brief Get the L2 cache associativity
CPUINFO_INLINE CacheAssociativity GetL2CacheAssociativity(const Context_t &ctx) {
    return static_cast<CacheAssociativity>((ctx.EAX_80000006H[2] >> 12) & 0xf);
}

/// @brief Get the L2 cache size described in 1KB units
CPUINFO_INLINE DWORD GetL2CacheSizeInKBytes(const Context_t &ctx) {
    return (ctx.EAX_80000006H[2] >> 16) & 0xffff;
}

/// @brief L3 cache line size in bytes
CPUINFO_INLINE DWORD GetL3CacheLineSize(const Context_t &ctx) {
    return ctx.EAX_80000006H[3] & 0xff;
}

/// @brief Get the L3 cache line per tag
CPUINFO_INLINE DWORD GetL3CacheLinePerTag(const Context_t &ctx) {
    return ((ctx.EAX_80000006H[3] >> 8) & 0xf) != 0;
}

/// @brief Get the L3 cache associativity
CPUINFO_INLINE CacheAssociativity GetL3CacheAssociativity(const Context_t &ctx) {
    return static_cast<CacheAssociativity>((ctx.EAX_80000006H[3] >> 12) & 0xf);
}

/// @brief Get the L3 cache size described in 512KB units((Vlue * 512KB) <= L3 cache size < ((Value + 1) * 512KB))
CPUINFO_INLINE DWORD GetL3CacheSizeIn512KBytes(const Context_t &ctx) {
    return ((ctx.EAX_80000006H[3] >> 18) & 0x3fff);
}

// 80000007H Advanced Power Management
// 80000008H Vertual and Physical Address Sizes

/// @brief Get maximum physical bytes address size in bits
CPUINFO_INLINE DWORD GetMaxPhysicalAddressBits(const Context_t &ctx) {
    return ctx.EAX_80000008H[0] & 0xff;
}

/// @brief Get maximum linear bytes address size in bits
CPUINFO_INLINE DWORD GetMaxLinearAddressBits(const Context_t &ctx) {
    return (ctx.EAX_80000008H[0] >> 8) & 0xff;
}

/// @brief Get maximum guest physical bytes address size in bits
CPUINFO_INLINE DWORD GetMaxGuestPhysicalAddressBits(const Context_t &ctx) {
    return (ctx.EAX_80000008H[0] >> 16) & 0xff;
}

// 80000009H Reserved
// 8000000AH SVM Revision and Feature Identification
// 8000000BH - 80000018H Reserved
// 80000019H TLB 1GB Page Identifiers

/// @brief Get the L1 instruction TLB number of entries for 1GB pages
CPUINFO_INLINE DWORD GetL1ITLBEntriesFor1GBPages(const Context_t &ctx) {
    return ctx.EAX_80000010H[0] & 0xfff;
}

/// @brief Get the L1 instruction TLB associativity for 1GB pages
CPUINFO_INLINE DWORD GetL1ITLBAssociativityFor1GBPages(const Context_t &ctx) {
    return (ctx.EAX_80000010H[0] >> 12) & 0xf;
}

/// @brief Get the L1 data TLB number of entries for 1GB pages
CPUINFO_INLINE DWORD GetL1DTLBEntriesFor1GBPages(const Context_t &ctx) {
    return (ctx.EAX_80000010H[0] >> 16) & 0xfff;
}

/// @brief Get the L1 data TLB associativity for 1GB pages
CPUINFO_INLINE DWORD GetL1DTLBAssociativityFor1GBPages(const Context_t &ctx) {
    return (ctx.EAX_80000010H[0] >> 28) & 0xf;
}

/// @brief Get the L2 instruction TLB number of entries for 1GB pages
CPUINFO_INLINE DWORD GetL2ITLBEntriesFor1GBPages(const Context_t &ctx) {
    return ctx.EAX_80000010H[1] & 0xfff;
}

/// @brief Get the L2 instruction TLB associativity for 1GB pages
CPUINFO_INLINE DWORD GetL2ITLBAssociativityFor1GBPages(const Context_t &ctx) {
    return (ctx.EAX_80000010H[1] >> 12) & 0xf;
}

/// @brief Get the L2 data TLB number of entries for 1GB pages
CPUINFO_INLINE DWORD GetL2DTLBEntriesFor1GBPages(const Context_t &ctx) {
    return (ctx.EAX_80000010H[1] >> 16) & 0xfff;
}

/// @brief Get the L2 data TLB associativity for 1GB pages
CPUINFO_INLINE DWORD GetL2DTLBAssociativityFor1GBPages(const Context_t &ctx) {
    return (ctx.EAX_80000010H[1] >> 28) & 0xf;
}

// 8000001AH Performance Optimization Identifiers
// 8000001BH Instruction Based Sampling Identifiers
// 8000001CH Lightweight Profiling Capabilities 0
// 8000001DH Cache Properties
// 8000001EH Extended APIC ID/Compute Unit Identifiers/Node Identifiers


} // namespace "CpuInfo"

#endif // CPU_INFO_H_
