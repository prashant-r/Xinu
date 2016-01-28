	.text
	.globl	host2netla
host2netla:
	pushl %ebp
	movl %esp,%ebp
	movl 8(%ebp), %eax
	bswap %eax
	leave
	ret
