        .text
        .global satsum

satsum:
        pushl   %ebp
        movl    %esp, %ebp
        movl    12(%ebp), %eax
        addl    8(%ebp), %eax
        jnc     end
        movl    $4294967295, %eax

end:
        popl    %ebp
        ret