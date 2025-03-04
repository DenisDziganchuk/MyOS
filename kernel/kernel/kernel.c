#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>

void kernel_main(void) {
	gdt_initialize();
	idt_initialize();
	
	terminal_initialize();
	printf("Hello, kernel World!\n\tsecond lind\be\vthird line\a");
}
