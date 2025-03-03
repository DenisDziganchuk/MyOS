ENTRY(_start)

SECTIONS
{
	/* Kernel is loaded at 1MB in physical memory. */
	. = 0x00100000;

	_kernel_start = .;

	.multiboot.data : {
        *(.multiboot.data)
	}

	.multiboot.text : {
		*(.multiboot.text)
	}

	/* Map kernel at higher-half. */
	. += 0xC0000000;

	/* Executable code. */
	.text BLOCK(4K) : AT (ADDR (.text) - 0xC0000000)
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) : AT (ADDR (.rodata) - 0xC0000000)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : AT (ADDR (.data) - 0xC0000000)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : AT (ADDR (.bss) - 0xC0000000)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}

	_kernel_end = .;
}
