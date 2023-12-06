#ifndef CPUID_H
#define CPUID_H

typedef struct CpuId* cpuid_t;

/**************************************************
 * @brief Get CPU ID 
 * @return CPU ID
 * @note should use cpuid_free to free the memory
 **************************************************/
cpuid_t cpuid();

/**************************************************
 * @brief Free CPU ID memory
 * @param id CPU ID
 **************************************************/
void cpuid_free(cpuid_t id);

/**************************************************
 * @brief Get CPU vendor
 * @param id CPU ID
 * @return CPU vendor
 **************************************************/
const char* cpuid_get_vendor(cpuid_t id);

/**************************************************
 * @brief Get CPU brand
 * @param id CPU ID
 * @return CPU brand
 **************************************************/
const char* cpuid_get_brand(cpuid_t id);

/**************************************************
 * @brief Get CPU serial number
 * @param id CPU ID
 * @return CPU serial number
 **************************************************/
const char* cpuid_get_serial_number(cpuid_t id);

#endif // CPUID_H