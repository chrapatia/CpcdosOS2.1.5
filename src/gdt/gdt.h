#pragma once

#include <stdint.h>
#include <stddef.h>

void CpcdosGDTInit();
void CpcdosGDTLoad();

struct gdt_pointer
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

typedef struct gdt_pointer gdt_ptr_t;

struct gdt_descriptor
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
}__attribute__((packed));

typedef struct gdt_descriptor gdt_desc_t;


