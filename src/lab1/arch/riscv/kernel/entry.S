.extern trap_handler
.section .text.entry
.align 2
.globl _traps 
_traps:
    addi sp, sp, -32*8        # 为 31 个寄存器和 sepc 分配栈空间

    sd ra, 0*8(sp)
    sd sp, 1*8(sp)
    sd gp, 2*8(sp)
    sd tp, 3*8(sp)
    sd t0, 4*8(sp)
    sd t1, 5*8(sp)
    sd t2, 6*8(sp)
    sd s0, 7*8(sp)
    sd s1, 8*8(sp)
    sd a0, 9*8(sp)
    sd a1, 10*8(sp)
    sd a2, 11*8(sp)
    sd a3, 12*8(sp)
    sd a4, 13*8(sp)
    sd a5, 14*8(sp)
    sd a6, 15*8(sp)
    sd a7, 16*8(sp)
    sd s2, 17*8(sp)
    sd s3, 18*8(sp)
    sd s4, 19*8(sp)
    sd s5, 20*8(sp)
    sd s6, 21*8(sp)
    sd s7, 22*8(sp)
    sd s8, 23*8(sp)
    sd s9, 24*8(sp)
    sd s10, 25*8(sp)
    sd s11, 26*8(sp)
    sd t3, 27*8(sp)
    sd t4, 28*8(sp)
    sd t5, 29*8(sp)
    sd t6, 30*8(sp)

    csrr a0, scause  # 将 scause 的值存入 a0
    csrr a1, sepc    # 将 sepc 的值存入 a1
    
    sd a1, 31*8(sp)          # 将 a0 中的 sepc 存到栈上

    call trap_handler        # 调用 trap_handler 函数处理异常

    ld a0, 31*8(sp)          # 从栈上恢复 sepc
    csrw sepc, a0            # 将 a0 中的 sepc 恢复

    ld ra, 0*8(sp)
    ld gp, 2*8(sp)
    ld tp, 3*8(sp)
    ld t0, 4*8(sp)
    ld t1, 5*8(sp)
    ld t2, 6*8(sp)
    ld s0, 7*8(sp)
    ld s1, 8*8(sp)
    ld a0, 9*8(sp)
    ld a1, 10*8(sp)
    ld a2, 11*8(sp)
    ld a3, 12*8(sp)
    ld a4, 13*8(sp)
    ld a5, 14*8(sp)
    ld a6, 15*8(sp)
    ld a7, 16*8(sp)
    ld s2, 17*8(sp)
    ld s3, 18*8(sp)
    ld s4, 19*8(sp)
    ld s5, 20*8(sp)
    ld s6, 21*8(sp)
    ld s7, 22*8(sp)
    ld s8, 23*8(sp)
    ld s9, 24*8(sp)
    ld s10, 25*8(sp)
    ld s11, 26*8(sp)
    ld t3, 27*8(sp)
    ld t4, 28*8(sp)
    ld t5, 29*8(sp)
    ld t6, 30*8(sp)
    ld sp, 1*8(sp)
    
    addi sp, sp, 32*8        # 恢复栈指针
    sret                     # 从 _trap 返回
