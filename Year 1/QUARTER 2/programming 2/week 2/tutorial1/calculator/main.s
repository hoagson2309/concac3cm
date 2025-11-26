	.file	"main.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"Enter an operator (%c, %c, %c, %c): "
.LC1:
	.string	"Invalid operator. Try again."
.LC2:
	.string	"+-*/"
	.text
	.globl	read_operator
	.type	read_operator, @function
read_operator:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$47, %r8d
	movl	$42, %ecx
	movl	$45, %edx
	movl	$43, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	call	read_char@PLT
	movb	%al, -1(%rbp)
	jmp	.L2
.L3:
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$47, %r8d
	movl	$42, %ecx
	movl	$45, %edx
	movl	$43, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	call	read_char@PLT
	movb	%al, -1(%rbp)
.L2:
	movsbl	-1(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	strchr@PLT
	testq	%rax, %rax
	je	.L3
	movzbl	-1(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	read_operator, .-read_operator
	.section	.rodata
.LC3:
	.string	"Enter your choice: "
.LC4:
	.string	"Invalid choice. Try again."
	.text
	.globl	read_choice
	.type	read_choice, @function
read_choice:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	call	read_int@PLT
	movl	%eax, -4(%rbp)
	jmp	.L6
.L7:
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	call	read_int@PLT
	movl	%eax, -4(%rbp)
.L6:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L7
	movl	-4(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jg	.L7
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	read_choice, .-read_choice
	.section	.rodata
.LC5:
	.string	"%s"
	.text
	.globl	read_operand
	.type	read_operand, @function
read_operand:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	call	read_double@PLT
	movq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	read_operand, .-read_operand
	.section	.rodata
	.align 8
.LC6:
	.string	"Do you want to perform another calculation? (y/n) "
.LC7:
	.string	"Invalid response. Try again."
.LC8:
	.string	"ynYN"
	.text
	.globl	another_calculation
	.type	another_calculation, @function
another_calculation:
.LFB3:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	call	read_char@PLT
	movb	%al, -1(%rbp)
	jmp	.L12
.L13:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	call	read_char@PLT
	movb	%al, -1(%rbp)
.L12:
	movsbl	-1(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	strchr@PLT
	testq	%rax, %rax
	je	.L13
	movsbl	-1(%rbp), %eax
	movl	%eax, %edi
	call	tolower@PLT
	cmpl	$121, %eax
	sete	%al
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	another_calculation, .-another_calculation
	.section	.rodata
	.align 8
.LC10:
	.string	"\nDivision by zero is not allowed."
	.text
	.globl	calculate
	.type	calculate, @function
calculate:
.LFB4:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, %eax
	movsd	%xmm0, -16(%rbp)
	movsd	%xmm1, -24(%rbp)
	movb	%al, -4(%rbp)
	movsbl	-4(%rbp), %eax
	cmpl	$47, %eax
	je	.L16
	cmpl	$47, %eax
	jg	.L17
	cmpl	$45, %eax
	je	.L18
	cmpl	$45, %eax
	jg	.L17
	cmpl	$42, %eax
	je	.L19
	cmpl	$43, %eax
	jne	.L17
	movsd	-16(%rbp), %xmm0
	addsd	-24(%rbp), %xmm0
	jmp	.L20
.L18:
	movsd	-16(%rbp), %xmm0
	subsd	-24(%rbp), %xmm0
	jmp	.L20
.L19:
	movsd	-16(%rbp), %xmm0
	mulsd	-24(%rbp), %xmm0
	jmp	.L20
.L16:
	pxor	%xmm0, %xmm0
	ucomisd	-24(%rbp), %xmm0
	jp	.L21
	pxor	%xmm0, %xmm0
	ucomisd	-24(%rbp), %xmm0
	jne	.L21
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	pxor	%xmm0, %xmm0
	jmp	.L20
.L21:
	movsd	-16(%rbp), %xmm0
	divsd	-24(%rbp), %xmm0
	jmp	.L20
.L17:
	pxor	%xmm0, %xmm0
.L20:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	calculate, .-calculate
	.section	.rodata
.LC11:
	.string	"Enter the first operand: "
.LC12:
	.string	"Enter the second operand: "
.LC13:
	.string	"%.4f %c %.4f = %.4f\n"
.LC14:
	.string	"Goodbye!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB5:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
.L25:
	call	read_operator
	movb	%al, -25(%rbp)
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	call	read_operand
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	call	read_operand
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movsbl	-25(%rbp), %eax
	movsd	-16(%rbp), %xmm0
	movq	-24(%rbp), %rdx
	movapd	%xmm0, %xmm1
	movq	%rdx, %xmm0
	movl	%eax, %edi
	call	calculate
	movq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	movsbl	-25(%rbp), %edx
	movsd	-8(%rbp), %xmm1
	movsd	-16(%rbp), %xmm0
	movq	-24(%rbp), %rax
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movl	%edx, %esi
	movq	%rax, %xmm0
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	movl	$3, %eax
	call	printf@PLT
	call	another_calculation
	testb	%al, %al
	jne	.L25
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.2.0-23ubuntu4) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
