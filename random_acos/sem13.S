        .text
        .global writeu32
writeu32:
        push    %ebp
        movl    %esp, %ebp
        push    %ebx
        push    %esi
        push    %edi

        movl	%ecx, %eax
        movl	$0, %ebx

loop:
		cmpl	$0, %ecx
		jle		loop_end

        mull	$0xcccccccd
        pushl	%eax


loop_end:
		cmpl	$0, %ebx
		



