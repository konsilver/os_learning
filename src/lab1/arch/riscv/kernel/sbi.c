#include "stdint.h"
#include "sbi.h"

struct sbiret sbi_ecall(uint64_t eid, uint64_t fid,
                        uint64_t arg0, uint64_t arg1, uint64_t arg2,
                        uint64_t arg3, uint64_t arg4, uint64_t arg5) {
    struct sbiret ret;
    asm volatile(
        "mv a7, %[eid]\n"
        "mv a6, %[fid]\n"
        "mv a0, %[arg0]\n"
        "mv a1, %[arg1]\n"
        "mv a2, %[arg2]\n"
        "mv a3, %[arg3]\n"
        "mv a4, %[arg4]\n"
        "mv a5, %[arg5]\n"
        "ecall\n"
        "mv %0, a0\n"
        "mv %1, a1\n"  
        : "=r" (ret.error), "=r" (ret.value)
        : [eid] "r" (eid), [fid] "r" (fid), [arg0] "r" (arg0), [arg1] "r" (arg1), [arg2] "r" (arg2), [arg3] "r" (arg3),[arg4] "r" (arg4),[arg5] "r" (arg5)
        : "memory","a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7"
    );
    return ret; 
}


struct sbiret sbi_debug_console_write_byte(uint8_t byte) {
   struct sbiret ret;
    asm volatile(
        "mv a7, %[eid]\n"    
        "mv a6, %[fid]\n"    
        "mv a0, %[byte]\n"  
        "ecall\n"        
        "mv %0, a0\n"    
        "mv %1, a1\n"    
        : "=r" (ret.error), "=r" (ret.value)  
        : [eid] "r" (SBI_EID_DEBUG_CONSOLE), [fid] "r" (SBI_FID_CONSOLE_WRITE_BYTE), [byte] "r" (byte)  
        : "memory", "a0", "a1", "a6", "a7"   
    );
    if (ret.error != SBI_SUCCESS) {
        ret.value = 0;
    }
    return ret; 
}

struct sbiret sbi_system_reset(uint32_t reset_type, uint32_t reset_reason) {
    struct sbiret ret;
    asm volatile(
        "mv a7, %[eid]\n"     
        "mv a6, %[fid]\n"      
        "mv a0, %[type]\n"     
        "mv a1, %[reason]\n"   
        "ecall\n"               
        "mv %0, a0\n"           
        "mv %1, a1\n"            
        : "=r" (ret.error), "=r" (ret.value)  
        : [eid] "r" (SBI_EID_SYSTEM_RESET), [fid] "r" (SBI_FID_SYSTEM_RESET), [type] "r" (reset_type), [reason] "r" (reset_reason) 
        : "memory", "a0", "a1", "a6", "a7" 
    );
    if(ret.error!=SBI_SUCCESS) ret.value=0;
    return ret;  
}

struct sbiret sbi_set_timer(uint64_t stime_value) {
    struct sbiret ret;
    asm volatile(
        "mv a0, %[stime_value]\n"   
        "li a7, 0x54494D45\n"              
        "li a6, 0x00\n"           
        "ecall\n"                  
        "mv %0, a0\n"            
        "mv %1, a1\n"              
        : "=r" (ret.error), "=r" (ret.value)
        : [stime_value] "r" (stime_value)
        : "memory", "a0", "a1", "a6", "a7"
    );
    return ret;  
}
