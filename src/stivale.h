struct stivale_header {
    uint64_t stack;   // This is the stack address which will be in ESP/RSP
                      // when the kernel is loaded.
                      // It can only be set to NULL for 64-bit kernels. 32-bit
                      // kernels are mandated to provide a vaild stack.
                      // 64-bit and 32-bit valid stacks must be at least 256 bytes
                      // in usable space and must be 16 byte aligned addresses.

    uint16_t flags;   // Flags
                      // bit 0  0 = text mode, 1 = graphics framebuffer mode
                      // bit 1  0 = 4-level paging, 1 = use 5-level paging (if
                      //                                available)
                      //        Ignored if booting a 32-bit kernel.
                      // bit 2  Formerly used to indicate whether to enable KASLR,
                      //        this flag is now reserved as KASLR is enabled in the
                      //        bootloader configuration instead. Presently
                      //        reserved and unused.
                      // All other bits are undefined and must be 0.

    uint16_t framebuffer_width;   // These 3 values are parsed if a graphics mode
    uint16_t framebuffer_height;  // is requested. If all values are set to 0
    uint16_t framebuffer_bpp;     // then the bootloader will pick the best possible
                                  // video mode automatically (recommended).
    uint64_t entry_point;      // If not 0, this field will be jumped to at entry
                               // instead of the ELF entry point.
} __attribute__((packed));

struct stivale_struct {
    uint64_t cmdline;               // Physical address of a null-terminated cmdline
    uint64_t memory_map_addr;       // Physical address of the memory map (entries described below)
    uint64_t memory_map_entries;    // Count of memory map entries
    uint64_t framebuffer_addr;      // Physical address of the framebuffer and related info
    uint16_t framebuffer_pitch;     // Pitch in bytes
    uint16_t framebuffer_width;     // Width and height in pixels
    uint16_t framebuffer_height;
    uint16_t framebuffer_bpp;       // Bits per pixel
    uint64_t rsdp;                  // Physical address the ACPI RSDP structure
    uint64_t module_count;          // Count of modules that stivale loaded according to config
    uint64_t modules;               // Physical address of the first entry in the linked list of modules (described below)
    uint64_t epoch;                 // UNIX epoch at boot, read from system RTC
    uint64_t flags;                 // Flags
                                    // bit 0: 1 if booted with BIOS, 0 if booted with UEFI
                                    // bit 1: 1 if extended colour information passed, 0 if not
                                    // All other bits are undefined and set to 0.
    // Extended colour information follows, only access if bit 1 of flags is set.
    uint8_t  fb_memory_model;       // Memory model: 1=RGB, all other values undefined
    uint8_t  fb_red_mask_size;      // RGB mask sizes and left shifts
    uint8_t  fb_red_mask_shift;
    uint8_t  fb_green_mask_size;
    uint8_t  fb_green_mask_shift;
    uint8_t  fb_blue_mask_size;
    uint8_t  fb_blue_mask_shift;
} __attribute__((packed));

struct mmap_entry {
    uint64_t base;      // Physical address of base of the memory section
    uint64_t length;    // Length of the section
    uint32_t type;      // Type (described below)
    uint32_t unused;
} __attribute__((packed));

