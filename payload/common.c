#include "include/arm.h"
#include "include/bootmode.h"
#include "include/commands.h"
#include "include/common.h"

int app() {
    return ((int (*)(void))(0x48022b38 | 1))();
}

void platform_init() {
    ((void (*)(void))(0x48002be0 | 1))();
}

bool mtk_detect_key(unsigned short key) {
    return ((bool (*)(unsigned short))(0x48004e28 | 1))(key);
}

void late_init() {
    handle_late_bootmode();
    register_commands();

    volatile uint16_t *x = (volatile uint16_t *)0x48041da0; // orange_state_warning
    x[0] = 0x2000; // movs r0, #0
    x[1] = 0x4770; // bx lr
    arch_clean_invalidate_cache_range((uint32_t)0x48041da0, 2);

    x = (volatile uint16_t *)0x48041cd0; // red_state_warning
    x[0] = 0x4770; // bx lr
    arch_clean_invalidate_cache_range((uint32_t)0x48041cd0, 2);

    x = (volatile uint16_t *)0x48061ea0; // dm_verity_corruption_warning
    x[0] = 0x4770; // bx lr
    arch_clean_invalidate_cache_range((uint32_t)0x48061ea0, 2);

    x = (volatile uint16_t *)0x480623e2; // libavb_verify_something
    x[0] = 0x2300; // mov.eq r3, #0x0 (BOOT_STATE_GREEN)
    arch_clean_invalidate_cache_range((uint32_t)0x480623e2, 2);
}

void early_init() {
    __asm__("mcr p15, 0, %0, c7, c5, 0" : : "r" (0));
    ((volatile uint32_t *)0x480ea8b8)[0] = BOOT_STATE_GREEN;
    arch_clean_invalidate_cache_range(0x480ea8b8, 4);
}
