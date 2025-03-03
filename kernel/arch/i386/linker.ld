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
	_text_start = .;
	.text ALIGN(4K) : AT (ADDR (.text) - 0xC0000000)
	{
		*(.text)
	}
	_text_end = .;

	/* Read-only data. */
	_rodata_start = .;
	.rodata ALIGN(4K) : AT (ADDR (.rodata) - 0xC0000000)
	{
		*(.rodata)
	}
	_rodata_end = .;

	/* Read-write data (initialized) */
	_data_start = .;
	.data ALIGN(4K) : AT (ADDR (.data) - 0xC0000000)
	{
		*(.data)
	}
	_data_end = .;

	/* Read-write data (uninitialized) and stack */
	_bss_start = .;
	.bss ALIGN(4K) : AT (ADDR (.bss) - 0xC0000000)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
	_bss_end = .;

	_kernel_end = .;
}
