start = 0x516DE8;
ENTRY(start)
OUTPUT_FORMAT("elf32-i386")
SECTIONS {
    .text 0x401000 :
    {
        INCLUDE "code.ld";
    }
    .data 0x576000 :
    {
        INCLUDE "data.ld";
    }
    .bss 0x5A2000 :
    {
        . = . + 0x0E7800;
    }
}
