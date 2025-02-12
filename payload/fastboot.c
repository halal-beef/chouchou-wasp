#include "include/fastboot.h"

void fastboot_info(const char *reason) {
    ((void (*)(const char *reason))(0x48030bb4 | 1))(reason);
}

void fastboot_fail(const char *reason) {
    ((void (*)(const char *reason))(0x48023724 | 1))(reason);
}

void fastboot_okay(const char *reason) {
    ((void (*)(const char *reason))(0x48023930 | 1))(reason);
}

void fastboot_register(const char *prefix,
                       void (*handle)(const char *arg, void *data, unsigned sz),
                       unsigned char security_enabled) {
    ((void (*)(const char *prefix, void (*handle)(const char *arg, void *data, unsigned sz), unsigned char security_enabled))(0x480232f4 | 1))(prefix, handle, security_enabled);
}
