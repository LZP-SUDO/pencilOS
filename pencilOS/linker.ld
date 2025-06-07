/* kernel/linker.ld */
ENTRY(_start)

SECTIONS {
    . = 0x7E00;

    .text : {
        *(.text)
    }

    .data : {
        *(.data)
        *(.rodata*)
    }

    .bss : {
        *(.bss)
    }

    /DISCARD/ : {
        *(.eh_frame)
        *(.comment)
    }
}