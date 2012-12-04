	.file	"pl8-3.c"
	.section	.rodata
	.align 4
.LC0:
	.string	"normal termination, exit status = %d\n"
	.align 4
.LC1:
	.string	"abnormal termination, signal number = %d%s\n"
.LC2:
	.string	""
	.align 4
.LC3:
	.string	"child stopped, signal number = %d\n"
	.text
	.globl	pr_exit
	.type	pr_exit, @function
pr_exit:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	call	mcount
	movl	8(%ebp), %eax
	andl	$127, %eax
	testl	%eax, %eax
	jne	.L2
	movl	8(%ebp), %eax
	andl	$65280, %eax
	movl	%eax, %edx
	sarl	$8, %edx
	movl	$.LC0, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	jmp	.L1
.L2:
	movl	8(%ebp), %eax
	andl	$127, %eax
	addl	$1, %eax
	sarb	%al
	testb	%al, %al
	jle	.L4
	movl	8(%ebp), %eax
	movl	%eax, %edx
	andl	$127, %edx
	movl	$.LC1, %eax
	movl	$.LC2, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	jmp	.L1
.L4:
	movl	8(%ebp), %eax
	andl	$255, %eax
	cmpl	$127, %eax
	jne	.L1
	movl	8(%ebp), %eax
	andl	$65280, %eax
	movl	%eax, %edx
	sarl	$8, %edx
	movl	$.LC3, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
.L1:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	pr_exit, .-pr_exit
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
