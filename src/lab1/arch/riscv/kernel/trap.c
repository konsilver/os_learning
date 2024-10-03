#include "stdint.h"

void trap_handler(uint64_t scause, uint64_t sepc) {
    if (scause & 0x8000000000000000L) {
        printk("Interruption occurred\n");
        if((scause & 0x7FFFFFFFFF) == 5){
            printk("[S] Supervisor Mode Timer Interrupt\n");
            clock_set_next_event();
        }
        else if((scause & 0x7FFFFFFFFF) == 9){
            printk("External interrupt occurred\n");
        }
    } else {
        printk("None Interruption\n");
    }
}