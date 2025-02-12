#include "include/arm.h"
#include "include/bootmode.h"
#include "include/printf.h"

#include <stdbool.h>
#include <stdint.h>

bootmode_t get_bootmode() {
    return *(volatile uint32_t *)0x480dc5e4;
}

void force_bootmode(bootmode_t mode) {
    dprintf("Forcing %d boot mode...\n", mode);

    *(volatile uint32_t *)0x480dc5e4 = mode;
    arch_clean_invalidate_cache_range(0x480dc5e4, 4);
}

void show_bootmode(bootmode_t mode) {
    switch (mode) {
        case BOOTMODE_NORMAL:
            video_printf("=> NORMAL mode...\n");
            break;
        case BOOTMODE_META:
            video_printf("=> META mode...\n");
            break;
        case BOOTMODE_RECOVERY:
            video_printf("=> RECOVERY mode...\n");
            break;
        case BOOTMODE_FACTORY:
            video_printf("=> FACTORY mode...\n");
            break;
        case BOOTMODE_ADVMETA:
            video_printf("=> ADVMETA mode...\n");
            break;
        case BOOTMODE_ATEFACT:
            video_printf("=> ATEFACT mode...\n");
            break;
        case BOOTMODE_ALARM:
            video_printf("=> ALARM mode...\n");
            break;
        case BOOTMODE_FASTBOOT:
            // video_printf("=> FASTBOOT mode...\n"); This is already displayed by default.
            break;
        default:
            video_printf("=> UNKNOWN mode...\n");
            break;
    }
}

void handle_late_bootmode() {
    bootmode_t mode = get_bootmode();
    show_bootmode(mode);
}
