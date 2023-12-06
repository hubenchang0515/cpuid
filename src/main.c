#include <stdio.h>
#include <stdlib.h>

#include "cpuid.h"

int main()
{
    cpuid_t id = cpuid();
    printf("Vendor: %s\n", cpuid_get_vendor(id));
    printf("Brand: %s\n", cpuid_get_brand(id));
    printf("Serial Number: %s\n", cpuid_get_serial_number(id));
    cpuid_free(id);
    return EXIT_FAILURE;
}