#include <stdint.h>
#include <string.h>

#include <kernel/idt.h>

#define IDT_ENTRIES 256

struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idtp;

void idt_load() {
	asm volatile ("lidt %0" : : "m" (idtp));
}

void idt_set_entry(struct idt_entry* entry, uint32_t base, uint16_t selector, uint8_t flags) {
	entry->base_low = base & 0xFFFF;
	entry->selector = selector;
	entry->zero = 0;
	entry->flags = flags | 0x60;
	entry->base_high = (base >> 16) & 0xFFFF;
}

void idt_initialize() {
	idtp.limit = sizeof(idt) - 1;
	idtp.base = (uint32_t)&idt;
	memset(&idt, 0, sizeof(idt));
	
	idt_load();
}
