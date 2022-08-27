.text
.global sum
sum:
call    readi32
movl    %eax, %ebx
call    readi32
addl    %ebx, %eax
call    writei32
call    nl
call    finish
