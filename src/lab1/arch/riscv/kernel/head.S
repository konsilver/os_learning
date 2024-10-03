    .extern start_kernel
    .section .text.init
    .globl _start
_start:
    la sp, boot_stack_top

    la a0, _traps
    csrw stvec, a0  

    li t0, 0x20  
    csrs sie, t0

    rdtime a0
    lui a0, %hi(10000000)
    addi a0, a0, %lo(10000000)
    call sbi_set_timer 

    li a0, 0x2
    csrs sstatus, a0 # enable SIE

    la a0, start_kernel
    jr a0
    
    .section .bss.stack
    .globl boot_stack
boot_stack:
    .space 4096

    .globl boot_stack_top
boot_stack_top:
