ESP0 = 4
KERNEL_STACK = 12

.globl switch2_to
.globl first_return_from_kernel

switch2_to:
	pushl %ebp
	movl %esp,%ebp
	pushl %ebx
	pushl %edx
	pushl %eax

	movl 8(%ebp),%ebx
	cmpl %ebx,current
	je 1f

	movl %ebx,%eax
	xchgl %eax,current

	movl tss,%edx
	addl $4096,%ebx
	movl %ebx,ESP0(%edx)

	movl %esp,KERNEL_STACK(%eax)
	movl 8(%ebp),%ebx
	movl KERNEL_STACK(%ebx),%esp

	movl 12(%ebp),%edx
	lldt %dx

    movl $0x17,%edx
    mov %dx,%fs

    cmpl %eax,last_task_used_math
    jne 1f
    clts
1:
	popl %eax
	popl %edx
	popl %ebx
	popl %ebp
	ret

first_return_from_kernel:
    popl %edi
    popl %esi
    popl %ecx
    pop %gs
    pop %fs
    pop %es
    pop %ds
    iret