#include "cpuid.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define H32(B64) ((uint32_t)(B64 >> 32))
#define L32(B64) ((uint32_t)(B64))

#define H16(B32) ((uint16_t)(B32 >> 16))
#define L16(B32) ((uint16_t)(B32))

#define OP_VENDOR       0
#define OP_FAMILY       1
#define OP_CACHE        2
#define OP_SERIAL       3
#define OP_BRAND_0      0x80000002
#define OP_BRAND_1      0x80000002
#define OP_BRAND_2      0x80000002

#define VENDOR_SIZE     12
#define BRAND_SIZE      48
#define SERIAL_SIZE     29

struct CpuId
{
    char vendor[VENDOR_SIZE + 1];
    char brand[BRAND_SIZE + 1];
    char serialNumber[SERIAL_SIZE + 1];
};

static void asm_cpuid(uint64_t dst[static 4], uint64_t op)
{
#if defined(__GNUC__)
    __asm__ __volatile__ (
        "movq %[op], %%rax;     \n"
        "cpuid;                 \n"
        "movq %%rax, %[meax];   \n"
        "movq %%rbx, %[mebx];   \n"
        "movq %%rcx, %[mecx];   \n"
        "movq %%rdx, %[medx];   \n"
        : [meax]"=r"(dst[0]), [mebx]"=r"(dst[1]), [mecx]"=r"(dst[2]), [medx]"=r"(dst[3])
        : [op]"r"(op)
        : "memory", "eax", "ebx", "ecx", "edx"
    );

#elif defined(WIN32)

#endif
}

/**************************************************
 * @brief Get CPU ID 
 * @return CPU ID
 * @note should use cpuid_free to free the memory
 **************************************************/
cpuid_t cpuid()
{
    cpuid_t id = (cpuid_t)malloc(sizeof(struct CpuId));

    uint64_t dest[4];

    // vendor
    asm_cpuid(dest, OP_VENDOR);
    memcpy(id->vendor, &(dest[1]), 4);
    memcpy(id->vendor + 4, &(dest[3]), 4);
    memcpy(id->vendor + 8, &(dest[2]), 4);
    id->vendor[VENDOR_SIZE] = 0;

    // brand
    asm_cpuid(dest, OP_BRAND_0);
    memcpy(id->brand, &(dest[0]), 4);
    memcpy(id->brand + 4, &(dest[1]), 4);
    memcpy(id->brand + 8, &(dest[2]), 4);
    memcpy(id->brand + 12, &(dest[3]), 4);
    asm_cpuid(dest, OP_BRAND_1);
    memcpy(id->brand, &(dest[0]), 4);
    memcpy(id->brand + 4, &(dest[1]), 4);
    memcpy(id->brand + 8, &(dest[2]), 4);
    memcpy(id->brand + 12, &(dest[3]), 4);
    asm_cpuid(dest, OP_BRAND_2);
    memcpy(id->brand, &(dest[0]), 4);
    memcpy(id->brand + 4, &(dest[1]), 4);
    memcpy(id->brand + 8, &(dest[2]), 4);
    memcpy(id->brand + 12, &(dest[3]), 4);
    id->brand[BRAND_SIZE] = 0;

    // serial
    asm_cpuid(dest, OP_FAMILY);
    uint64_t falimy = dest[0];
    asm_cpuid(dest, OP_SERIAL);
    snprintf(id->serialNumber, SERIAL_SIZE + 1, "%04X-%04X-%04X-%04X-%04X-%04X", 
                H16(L32(falimy)), L16(L32(falimy)), 
                H16(L32(dest[2])), L16(L32(dest[2])), 
                H16(L32(dest[3])), L16(L32(dest[3])));

    return id;
}

/**************************************************
 * @brief Free CPU ID memory
 * @param id CPU ID
 **************************************************/
void cpuid_free(cpuid_t id)
{
    free((void*)(id));
}

/**************************************************
 * @brief Get CPU vendor
 * @param id CPU ID
 * @return CPU vendor
 **************************************************/
const char* cpuid_get_vendor(cpuid_t id)
{
    return id->vendor;
}

/**************************************************
 * @brief Get CPU brand
 * @param id CPU ID
 * @return CPU brand
 **************************************************/
const char* cpuid_get_brand(cpuid_t id)
{
    return id->brand;
}

/**************************************************
 * @brief Get CPU serial number
 * @param id CPU ID
 * @return CPU serial number
 **************************************************/
const char* cpuid_get_serial_number(cpuid_t id)
{
    return id->serialNumber;
}