#include <font.h>
#include <kernel/alloc.h>
#include <kernel/atadrv.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/init.h>
#include <kernel/irq.h>
#include <kernel/isr.h>
#include <kernel/kbd.h>
#include <kernel/kshell.h>
#include <kernel/pit.h>
#include <kernel/power.h>
#include <kernel/serial.h>
#include <kernel/text.h>
#include <kernel/vbe.h>
#include <hw.h>
#include <macros.h>
#include <multiboot.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

//Copied from osdev.org
int detect_devtype(int slavebit, struct DEVICE *ctrl){      
    ata_soft_reset(ctrl->dev_ctl);                          
    outb(ctrl->base + REG_DEVSEL, 0xA0 | slavebit<<4);      
    inb(ctrl->dev_ctl);
    inb(ctrl->dev_ctl);
    inb(ctrl->dev_ctl);
    inb(ctrl->dev_ctl);
    unsigned cl=inb(ctrl->base + REG_CYL_LO);
    unsigned ch=inb(ctrl->base + REG_CYL_HI);

    if(cl == 0x14 && ch == 0xEB) return ATADEV_PATAPI;
    if(cl == 0x69 && ch == 0x96) return ATADEV_SATAPI;
    if(cl == 0 && ch == 0) return ATADEV_PATA;
    if(cl == 0x3c && ch == 0xc3) return ATADEV_SATA;

    return ATADEV_UNKNOWN;
}

int init_atadrv(){
    struct DEVICE *ctrl;
    ctrl->base = 0x1F0;
    ctrl->dev_ctl = 0x3F6;
    
    int type = detect_devtype(0, ctrl);     //TODO: Find the slavebit
    if(type == 10) {
        fg_color = YELLOW;
        printf("Warning : Unknown disk type");
        fg_color = FG;
        return 1;
    }
    return 0;
}
