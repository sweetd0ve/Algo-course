        .text
        .global main
main:
        movl    $0, %ebx
        movl    $0, %ecx
        call    sum
        movl    %ebx, %eax
        call    writei32
        call    nl
        call    finish

sum:
        call    readi32
        jc      sum_end
        addl    %eax, %ebx
        jno     sum
        call	sum_OF

sum_end:
        call	finish

sum_OF:
        adcl    $0, %ecx
        movl    $0x7ffffffe, %ebx
        addl    %ecx, %ebx
        call	finish
