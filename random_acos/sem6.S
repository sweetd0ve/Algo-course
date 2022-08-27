		.text
		.global main
main:
		call    readi32
		subl    $0, %eax
		jge     .Lloop_begin
		call    finish


.Lloop_begin:
    	subl    $0, %eax
		jz      .Lafter_loop
		decl    %eax
		call    writei32
		call    nl
    	jmp  .Lloop_begin
.Lafter_loop:
    	
