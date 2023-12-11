#include <mach/mach.h>
#include <stdio.h>
#include "free_memory_api.h"

unsigned long long get_free_system_memory() {
    mach_port_t host = mach_host_self();
    vm_size_t page_size;
    host_page_size(host, &page_size);

    vm_statistics_data_t vm_stats;
    mach_msg_type_number_t count = sizeof(vm_stats) / sizeof(natural_t);
    if (host_statistics(host, HOST_VM_INFO, (host_info_t)&vm_stats, &count) != KERN_SUCCESS) {
        fprintf(stderr, "Failed to get host_statistics\n");
        return 1;
    }

    return (unsigned long long)vm_stats.free_count * (unsigned long long)page_size;
}