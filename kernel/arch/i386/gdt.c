#include <stdint.h>

#include <kernel/gdt.h>

#define GDT_ENTRIES 5

#define GDT_ACCESS_PRESENT        0x80
#define GDT_ACCESS_RING0          0x00
#define GDT_ACCESS_RING3          0x60
#define GDT_ACCESS_EXECUTABLE     0x08
#define GDT_ACCESS_CODE_OR_DATA   0x10
#define GDT_ACCESS_WRITABLE       0x02

#define GDT_FLAG_4K_GRANULARITY   0x80
#define GDT_FLAG_32_BIT           0x40

struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_ptr gdtp;

void gdt_flush() {
	asm volatile ("lgdt (%0)" : : "r" (&gdtp));
}

void gdt_set_entry(struct gdt_entry* entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
	entry->limit_low = limit & 0xFFFF;
	entry->base_low = base & 0xFFFF;
	entry->base_middle = (base >> 16) & 0xFF;
	entry->access = access;
	entry->granularity = (limit >> 16) & 0x0F;
	entry->granularity |= (flags & 0xF0);
	entry->base_high = (base >> 24) & 0xFF;
}

void gdt_initialize() {
	gdtp.limit = sizeof(gdt) - 1;
	gdtp.base = (uint32_t)&gdt;

	gdt_set_entry(&gdt[0], 0, 0, 0, 0);
	gdt_set_entry(&gdt[1], 0, 0xFFFFFFFF, GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_CODE_OR_DATA, GDT_FLAG_4K_GRANULARITY | GDT_FLAG_32_BIT);
	gdt_set_entry(&gdt[2], 0, 0xFFFFFFFF, GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_CODE_OR_DATA | GDT_ACCESS_WRITABLE, GDT_FLAG_4K_GRANULARITY | GDT_FLAG_32_BIT);
	gdt_set_entry(&gdt[3], 0, 0xFFFFFFFF, GDT_ACCESS_PRESENT | GDT_ACCESS_RING3 | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_CODE_OR_DATA, GDT_FLAG_4K_GRANULARITY | GDT_FLAG_32_BIT);
	gdt_set_entry(&gdt[4], 0, 0xFFFFFFFF, GDT_ACCESS_PRESENT | GDT_ACCESS_RING3 | GDT_ACCESS_CODE_OR_DATA | GDT_ACCESS_WRITABLE, GDT_FLAG_4K_GRANULARITY | GDT_FLAG_32_BIT);

	gdt_flush();
}
