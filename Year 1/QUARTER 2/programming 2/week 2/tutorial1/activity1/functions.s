	.file	"functions.c"
	.text
	.type	seed_prng, @function
seed_prng:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movzbl	seeded.0(%rip), %eax
	xorl	$1, %eax
	testb	%al, %al
	je	.L5
	movl	$0, %edi
	call	time@PLT
	movl	%eax, %edi
	call	srand@PLT
	movl	$0, -4(%rbp)
	jmp	.L3
.L4:
	call	rand@PLT
	addl	$1, -4(%rbp)
.L3:
	cmpl	$49, -4(%rbp)
	jle	.L4
	movb	$1, seeded.0(%rip)
.L5:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	seed_prng, .-seed_prng
	.section	.rodata
.LC0:
	.string	"Invalid input. Try again: "
.LC1:
	.string	"%d"
	.text
	.globl	read_int
	.type	read_int, @function
read_int:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	jmp	.L7
.L9:
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
.L8:
	call	getchar@PLT
	cmpl	$10, %eax
	jne	.L8
.L7:
	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	cmpl	$1, %eax
	jne	.L9
	nop
.L10:
	call	getchar@PLT
	cmpl	$10, %eax
	jne	.L10
	movl	-12(%rbp), %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L12
	call	__stack_chk_fail@PLT
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	read_int, .-read_int
	.section	.rodata
.LC2:
	.string	"%f"
	.text
	.globl	read_float
	.type	read_float, @function
read_float:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	jmp	.L14
.L16:
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
.L15:
	call	getchar@PLT
	cmpl	$10, %eax
	jne	.L15
.L14:
	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	cmpl	$1, %eax
	jne	.L16
	nop
.L17:
	call	getchar@PLT
	cmpl	$10, %eax
	jne	.L17
	movss	-12(%rbp), %xmm0
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L19
	call	__stack_chk_fail@PLT
.L19:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	read_float, .-read_float
	.section	.rodata
.LC3:
	.string	"%lf"
	.text
	.globl	read_double
	.type	read_double, @function
read_double:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	jmp	.L21
.L23:
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
.L22:
	call	getchar@PLT
	cmpl	$10, %eax
	jne	.L22
.L21:
	leaq	-16(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	cmpl	$1, %eax
	jne	.L23
	nop
.L24:
	call	getchar@PLT
	cmpl	$10, %eax
	jne	.L24
	movsd	-16(%rbp), %xmm0
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L26
	call	__stack_chk_fail@PLT
.L26:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	read_double, .-read_double
	.section	.rodata
.LC4:
	.string	" %c"
.LC5:
	.string	"Enter a single character! "
	.text
	.globl	read_char
	.type	read_char, @function
read_char:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	jmp	.L28
.L30:
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
.L29:
	call	getchar@PLT
	cmpl	$10, %eax
	jne	.L29
.L28:
	leaq	-14(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	cmpl	$1, %eax
	jne	.L30
	movl	$0, -12(%rbp)
	jmp	.L31
.L33:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movsbq	-13(%rbp), %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	jne	.L31
	addl	$1, -12(%rbp)
.L31:
	call	getchar@PLT
	movb	%al, -13(%rbp)
	cmpb	$10, -13(%rbp)
	jne	.L33
	cmpl	$0, -12(%rbp)
	jle	.L34
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L34:
	cmpl	$0, -12(%rbp)
	jg	.L28
	movzbl	-14(%rbp), %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L37
	call	__stack_chk_fail@PLT
.L37:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	read_char, .-read_char
	.globl	random_int
	.type	random_int, @function
random_int:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	call	seed_prng
	call	rand@PLT
	movl	%eax, %ecx
	movl	-8(%rbp), %eax
	subl	-4(%rbp), %eax
	leal	1(%rax), %esi
	movl	$2147483647, %eax
	cltd
	idivl	%esi
	leal	1(%rax), %edi
	movl	%ecx, %eax
	cltd
	idivl	%edi
	movl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	random_int, .-random_int
	.globl	random_float
	.type	random_float, @function
random_float:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movss	%xmm0, -4(%rbp)
	movss	%xmm1, -8(%rbp)
	call	seed_prng
	call	rand@PLT
	pxor	%xmm1, %xmm1
	cvtsi2ssl	%eax, %xmm1
	movss	-8(%rbp), %xmm0
	subss	-4(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	movss	.LC6(%rip), %xmm1
	divss	%xmm1, %xmm0
	addss	-4(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	random_float, .-random_float
	.globl	max_int
	.type	max_int, @function
max_int:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jle	.L43
	movl	-4(%rbp), %eax
	jmp	.L44
.L43:
	movl	-8(%rbp), %eax
.L44:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	max_int, .-max_int
	.globl	min_int
	.type	min_int, @function
min_int:
.LFB14:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	.L46
	movl	-4(%rbp), %eax
	jmp	.L47
.L46:
	movl	-8(%rbp), %eax
.L47:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	min_int, .-min_int
	.globl	get_current_date
	.type	get_current_date, @function
get_current_date:
.LFB15:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, %edi
	call	time@PLT
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	cmpq	$-1, %rax
	jne	.L49
	movl	$0, %eax
	jmp	.L52
.L49:
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	localtime@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L51
	movl	$0, %eax
	jmp	.L52
.L51:
	movq	-16(%rbp), %rax
	movl	20(%rax), %eax
	leal	1900(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, (%rax)
	movq	-16(%rbp), %rax
	movl	16(%rax), %edx
	movq	-40(%rbp), %rax
	addq	$4, %rax
	addl	$1, %edx
	movl	%edx, (%rax)
	movq	-40(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	-16(%rbp), %rax
	movl	12(%rax), %eax
	movl	%eax, (%rdx)
	movl	$1, %eax
.L52:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L53
	call	__stack_chk_fail@PLT
.L53:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	get_current_date, .-get_current_date
	.globl	get_current_time
	.type	get_current_time, @function
get_current_time:
.LFB16:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, %edi
	call	time@PLT
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	cmpq	$-1, %rax
	jne	.L55
	movl	$0, %eax
	jmp	.L58
.L55:
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	localtime@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L57
	movl	$0, %eax
	jmp	.L58
.L57:
	movq	-16(%rbp), %rax
	movl	8(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, (%rax)
	movq	-40(%rbp), %rax
	leaq	4(%rax), %rdx
	movq	-16(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, (%rdx)
	movq	-40(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	movl	$1, %eax
.L58:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L59
	call	__stack_chk_fail@PLT
.L59:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	get_current_time, .-get_current_time
	.globl	read_string
	.type	read_string, @function
read_string:
.LFB17:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movq	stdin(%rip), %rdx
	movl	-28(%rbp), %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	fgets@PLT
	movq	-24(%rbp), %rax
	movl	$10, %esi
	movq	%rax, %rdi
	call	strrchr@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L62
	movq	-8(%rbp), %rax
	movb	$0, (%rax)
.L62:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	read_string, .-read_string
	.local	seeded.0
	.comm	seeded.0,1,1
	.section	.rodata
	.align 4
.LC6:
	.long	1325400064
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
