//разбирали на семинаре

#include <asm/unistd_32.h>

        .text

        .global _start
        .type   _start, @function
_start:
    //
    // место под переменную.
    //
        subl    $4, %esp
    
io_loop:
        movl    $__NR_read, %eax
        movl    $0, %ebx
        movl    %esp, %ecx
        movl    $1, %edx
        int     $0x80
    
        cmp     $1, %eax
        jne     program_finish
    
        movb    (%esp), %bl

        cmpb    $'0', %bl
        jbe     not_process_digit
        cmpb    $'9',          %bl
        ja      not_process_digit
        movb    $'0', (%esp)
not_process_digit:
        movl    $__NR_write, %eax
        movl    $1, %ebx
        int     $0x80
        jmp     io_loop

program_finish:
        movl    $__NR_exit, %eax
        movl    $0, %ebx
        int     $0x80
