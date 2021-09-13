/// @file CPUInfo.cpp
/// @author Masayoshi Kamai

#include <stdio.h>
#include "CPUInfo.h"

void PrintBasicInfo(const CpuInfo::Context_t &ctx) {
    const char *procTypeStr[4] = {
       "Original OEM Processor",
       "Intel OverDirve(R) Processor",
       "Dual processor",
       "Intel reserved"
    };

    char venderID[13] = "";
    CpuInfo::GetVendorID(venderID, ctx);

    WORD ProcSerialNumber[6];
    CpuInfo::GetProcessorSerialNumber(ProcSerialNumber, ctx);

    printf("Max Support Level                  : %02XH\n", CpuInfo::GetMaxSupportLevel(ctx));
    printf("Vender ID                          : %12s\n", venderID);
    printf("Processor type                     : %s\n", procTypeStr[(DWORD)CpuInfo::GetProcessorType(ctx)]);
    printf("Ext family                         : %02XH\n", CpuInfo::GetProcessorExtendedFamily(ctx));
    printf("Ext model                          : %02XH\n", CpuInfo::GetProcessorExtendedModel(ctx));
    printf("family                             : %02XH\n", CpuInfo::GetProcessorFamily(ctx));
    printf("model                              : %02XH\n", CpuInfo::GetProcessorModel(ctx));
    printf("stepping                           : %02XH\n", CpuInfo::GetProcessorStepping(ctx));
    printf("brand index                        : %02XH\n", CpuInfo::GetBlandIndex(ctx));
    printf("APIC Physical ID                   : %02XH\n", CpuInfo::GetAPICPhysicalID(ctx));
    printf("CLFlush Line Size                  : %d bytes\n", CpuInfo::GetCLFlushLineSizeInBytes(ctx));
    printf("Max Logical Processors Per Package : %d\n", CpuInfo::GetMaxLogicalProcessorsPerPackage(ctx));
    printf("Processor Serial Number            : %04X-%04X-%04X-%04X-%04X-%04X\n", ProcSerialNumber[0], ProcSerialNumber[1], ProcSerialNumber[2], ProcSerialNumber[3], ProcSerialNumber[4], ProcSerialNumber[5]);
    printf("Feature                            :");

    const char *featureItems[32] = {
        "fpu", "vme", "de", "pse", "tsc", "msr", "pae", "mce",
        "cx8", "apic", "reserved10", "sep", "mtrr", "pge", "mca", "cmov",
        "pat", "pse-36", "psn", "clfsh", "reserved20", "ds", "acpi", "mmx",
        "fxsr", "sse", "sse2", "ss", "htt", "tm", "reserved30", "pbe"
    };
    for (DWORD i = 0; i < 32; ++i) {
        if (HasFeature(static_cast<CpuInfo::Feature>(i), ctx)) {
            printf(" %s", featureItems[i]);
        }
    }
    printf("\n");
    printf("Feature2                           :");

    const char *feature2Items[32] = {
        "sse3", "pclmulqdq", "dtes64", "monitor", "ds-cpl", "vmx", "smx", "eist",
        "tm2", "ssse3", "cnxt-id", "reserved11", "fma", "cmpxchg16b","xtpr","pdcm",
        "reserved16", "pcid", "dca", "sse4.1", "sse4.2", "x2apic", "movbe", "popcnt",
        "tsc-deadline", "aesni", "xsave", "osxsave", "avx", "f16c", "rdrand", "hyperv"
    };
    for (DWORD i = 0; i < 32; ++i) {
        if (HasFeature(static_cast<CpuInfo::Feature2>(i), ctx)) {
            printf(" %s", feature2Items[i]);
        }
    }
    printf("\n");
    printf("Feature3                           :");

    const char *feature3Items[32] = {
        "fsgsbase", "ia32_tsc_adjust", "sgx", "bmi1", "hle", "avx2", "reserved", "smep",
        "bmi2", "movsb/stosb", "invpcid", "rtm", "pqm", "fpucs/fpuds", "impx", "pqe",
        "avx512f", "avx512dq", "rdseed", "adx", "smap", "avx512_ifma", "reserved", "clflushopt",
        "clwb", "proctrace", "avx512pf", "avx512er", "avx512cd", "sha", "avx512bw", "avx512vl"
    };
    for (DWORD i = 0; i < 32; ++i) {
        if (HasFeature(static_cast<CpuInfo::Feature3>(i), ctx)) {
            printf(" %s", feature3Items[i]);
        }
    }
    printf("\n");
    printf("Feature4                           :");

    const char *feature4Items[32] = {
        "prefetchwt1", "avx512_vbmi", "umip", "pku", "ospke", "waitpkg", "avx512_vbmi2", "reserved",
        "gfni", "vaes", "vpclmulqdq", "avx512_vnni", "avx512_bitalg", "reserved13", "avx512_vpopcntdq", "reserved15",
        "reserved16", "reserved17", "reserved18", "reserved19", "reserved20", "reserved21", "rdpid", "reserved23",
        "reserved24", "cldemote", "reserved26", "movdiri", "movdir64b", "enqcmd", "sgx_lc", "pks"
    };
    for (DWORD i = 0; i < 32; ++i) {
        if (HasFeature(static_cast<CpuInfo::Feature4>(i), ctx)) {
            printf(" %s", feature4Items[i]);
        }
    }
    printf("\n");
    printf("Feature5                           :");
    
    const char *feature5Items[32] = {
        "reserved0", "reserved1", "avx512_4vnniw", "avx512_4fmaps", "fast_short_rep_mov", "reserved5", "reserved6", "reserved7",
        "avx512_vp2intersect", "srbds_ctrl", "md_clear", "reserved11", "reserved12", "tsx_force_abort", "serialize", "hybrid",
        "tsxldtrk", "reserved17", "pconfig", "lbr", "cet_ibt", "reserved21", "amx-bf16", "reserved23", "amx-tile", "amx-int8", "iprs/ibpb",
        "stibp", "l1d_flush","enum_ia32_arch","enum_ia32_core","enum_ssbd"
    };
    for (DWORD i = 0; i < 32; ++i) {
        if (HasFeature(static_cast<CpuInfo::Feature5>(i), ctx)) {
            printf(" %s", feature5Items[i]);
        }
    }
    printf("\n");
    printf("Feature6                           :");

    const char *feature6Items[32] = {
        "reserved0", "reserved1", "reserved2", "reserved3", "reserved4", "avx512_bf16", "reserved6", "reserved7",
        "reserved8", "reserved9", "reserved10", "reserved11", "reserved12", "reserved13", "reserved14", "reserved15",
        "reserved16", "reserved17", "reserved18", "reserved19", "reserved20", "reserved21", "reserved22", "reserved23",
        "reserved24", "reserved25", "reserved26", "reserved27", "reserved28", "reserved29", "reserved30", "reserved31"
    };
    for (DWORD i = 0; i < 32; ++i) {
        if (HasFeature(static_cast<CpuInfo::Feature6>(i), ctx)) {
            printf(" %s", feature6Items[i]);
        }
    }
    printf("\n");
}

void PrintCacheInfo(const CpuInfo::Context_t &ctx) {
    const char *cacheTypeStr[4] = {
        "Null",
        "Data",
        "Instruction",
        "Unified"
    };

    for (DWORD i = 0; i < CPUINFO_MAX_CACHES; ++i) {
        if (GetCacheType(i, ctx) == CpuInfo::CacheType::Null) {
            break;
        }
        printf("Cache No.                          : %u\n", i);
        printf("Cache Type                         : %s\n", cacheTypeStr[(DWORD)GetCacheType(i, ctx)]);
        printf("Cache Level                        : %u\n", GetCacheLevel(i, ctx));
        printf("Self Init                          : %s\n", GetSelfInitializingCacheLevel(i, ctx) ? "True" : "False");
        printf("Fully Associative                  : %s\n", GetFullyAssociativeCache(i, ctx) ? "True" : "False");
        printf("Max Shared Logical Processors      : %u\n", GetMaxThreadSharingCache(i, ctx));
        printf("Max Packed Processor Cores         : %u\n", GetMaxCoresPerPackage(i, ctx));
        printf("System Coherency Line Size         : %u bytes\n", GetSystemCoherencyLineSize(i, ctx));
        printf("Physical Line Partitions           : %u\n", GetPhysicalLinePartitions(i, ctx));
        printf("Way of Associativity               : %u\n", GetWaysAssociativity(i, ctx));
        printf("Number of Sets                     : %u\n", GetCacheNumSets(i, ctx));
        printf("Write-Back Invalidate              : %s\n", GetWriteBackInvalidate(i, ctx) ? "True" : "False");
        printf("Cache Inclusiveness                : %s\n", GetCacheInclusiveness(i, ctx) ? "True" : "False");
        printf("Complex Cache Indexing             : %s\n", GetCacheComplexCacheIndexing(i, ctx) ? "True" : "False");
        printf("Cache Size                         : %u bytes\n", GetCacheSize(i, ctx));
    }
}

void PrintTopologyInfo(const CpuInfo::Context_t &ctx) {
    const char *topologyTypeStr[] = {
        "Invalid",
        "Thread",
        "Core",
    };

    for (DWORD i = 0; i < CPUINFO_MAX_PROCESSOR_TOPOLOGY_LEVELS; ++i) {
        if (GetTopologyLevelType(i, ctx) == CpuInfo::TopologyLevelType::Invalid) {
            break;
        }
        printf("Topology No.                    : %u\n", i);
        printf("Topology Level                  : %u\n", GetTopologyLevel(i, ctx));
        printf("Topology Type                   : %s\n", topologyTypeStr[(DWORD)GetTopologyLevelType(i, ctx)]);
        printf("Shift right APIC ID             : %u\n", GetShiftAPICIDBits(i, ctx));
        printf("FC Logical Processors           : %u\n", GetNumFCLogicalProcessors(i, ctx));
        printf("Enhances APIC ID                : %u\n", GetExtendedAPICID(i, ctx));
    }
}

void PrintFrequencyInfo(const CpuInfo::Context_t &ctx) {
    printf("Processor Base Frequency           : %u MHz\n", GetProcessorBaseFrequency(ctx));
    printf("Max Frequency                      : %u MHz\n", GetMaxFrequency(ctx));
    printf("Bus Frequency                      : %u MHz\n", GetBusFrequency(ctx));
}

void PrintExtInfo(const CpuInfo::Context_t &ctx) {
    const char *cacheAssocItems[32] = {
        "Disabled",             // 0x00
        "Direct mapped",        // 0x01
        "2-way",                // 0x02
        "Unknown03",            // 0x03
        "4-way",                // 0x04
        "Unknown05",            // 0x05
        "8-way",                // 0x06
        "Unknown07",            // 0x07
        "16-way",               // 0x08
        "Unknown09",            // 0x09
        "32-way",               // 0x0a
        "48-way",               // 0x0b
        "64-way",               // 0x0c
        "96-way",               // 0x0d
        "128-way",              // 0x0e
        "Fully Associative"     // 0x0f
    };

    char brandStr[49] = "";
    CpuInfo::GetBrandString(brandStr, ctx);

    printf("Max Ext Support Level              : %XH\n", GetMaxExtendedSupportLevel(ctx));
    printf("Brand String                       : %s\n", brandStr);
    printf("L2 Cache Line Size                 : %u bytes\n", GetL2CacheLineSize(ctx));
    printf("L2 Cache Line Per Tag              : %u bytes\n", GetL2CacheLinePerTag(ctx));
    printf("L2 Cache Associativity             : %s\n", cacheAssocItems[(DWORD)GetL2CacheAssociativity(ctx)]);
    printf("L2 Cache Size                      : %u Kbytes\n", GetL2CacheSizeInKBytes(ctx));
    printf("L3 Cache Line Size                 : %u bytes\n", GetL3CacheLineSize(ctx));
    printf("L3 Cache Line Per Tag              : %u bytes\n", GetL3CacheLinePerTag(ctx));
    printf("L3 Cache Associativity             : %s\n", cacheAssocItems[(DWORD)GetL3CacheAssociativity(ctx)]);
    printf("L3 Cache Size                      : %u Kbytes\n", GetL3CacheSizeIn512KBytes(ctx) * 512);
    printf("Max Physical Address Bits          : %u\n", GetMaxPhysicalAddressBits(ctx));
    printf("Max Linear Address Bits            : %u\n", GetMaxLinearAddressBits(ctx));
    printf("Max Guest Physical Address Bits    : %u\n", GetMaxGuestPhysicalAddressBits(ctx));
}


int main(void) {
    CpuInfo::Context_t ctx;
    CpuInfo::Init(&ctx);

    PrintBasicInfo(ctx);
    PrintCacheInfo(ctx);
    PrintTopologyInfo(ctx);
    PrintFrequencyInfo(ctx);
    PrintExtInfo(ctx);

    return 0;
}