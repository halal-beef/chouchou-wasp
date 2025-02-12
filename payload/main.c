#include "include/printf.h"
#include "include/arm.h"
#include "include/bootmode.h"
#include "include/common.h"

void chouchou() {
    late_init();
    int ret = app();

    // app() is expected to never return
    LOGE("app() returned %d\n", ret);
    while (1) {
        // Wait for WDT to reset the SoC
        __asm__("wfi");
    }
}

__attribute__((section(".text.start"))) int main(void) {
    dprintf("This is chouchou payload by R0rt1z2. Copyright 2025\n");

    patch_call(0x48020388, chouchou);

    // HMD or Huaqin, or whoever was responsible for
    // the bootloader on wasp never assigned a combo
    // for entering recovery mode, so we added it.
    // If the user holds volume up during boot, they
    // will enter recovery.
    if (mtk_detect_key(17)) {
	force_bootmode(BOOTMODE_RECOVERY);
    }

    early_init();
    platform_init();

    return 0;
}
