// gdt.cpp
#include "gdt.h"

GDT::Entry GDT::entries[3];
GDT::Pointer GDT::ptr;

void GDT::initialize() {
    ptr.limit = sizeof(entries) - 1;
    ptr.base = (uint32_t)&entries;
    
    // 空描述符
    set_gate(0, 0, 0, 0, 0);
    
    // 代码段
    set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    
    // 数据段
    set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    
    // 加载GDT
    asm volatile("lgdt (%0)" : : "r" (&ptr));
}

void GDT::set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    entries[num].base_low = (base & 0xFFFF);
    entries[num].base_middle = (base >> 16) & 0xFF;
    entries[num].base_high = (base >> 24) & 0xFF;
    
    entries[num].limit_low = (limit & 0xFFFF);
    entries[num].granularity = ((limit >> 16) & 0x0F);
    
    entries[num].granularity |= (gran & 0xF0);
    entries[num].access = access;
}