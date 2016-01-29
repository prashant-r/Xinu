	.file	"host2netlc.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	host2netlc
	.type	host2netlc, @function
host2netlc:
.LFB24:
	.cfi_startproc
	movl	4(%esp), %ecx
	movl	%ecx, %edx
	sall	$8, %ecx
	sarl	$8, %edx
	andl	$-16711936, %ecx
	andl	$16711935, %edx
	orl	%ecx, %edx
	movl	%edx, %eax
	sarl	$16, %edx
	sall	$16, %eax
	orl	%edx, %eax
	ret
	.cfi_endproc
.LFE24:
	.size	host2netlc, .-host2netlc
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.ident	"GCC: (Gentoo 4.9.3 p1.4, pie-0.6.4) 4.9.3"
	.section	.note.GNU-stack,"",@progbits
