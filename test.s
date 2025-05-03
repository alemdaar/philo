	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15
	.globl	_routine                ## -- Begin function routine
	.p2align	4, 0x90
_routine:                               ## @routine
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	_mutex(%rip), %rdi
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	callq	_pthread_mutex_lock
	movl	$0, -12(%rbp)
	movq	$0, -24(%rbp)
	movl	%eax, -32(%rbp)         ## 4-byte Spill
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$10000, -24(%rbp)       ## imm = 0x2710
	jae	LBB0_6
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	_mails(%rip), %rax
	addq	$1, %rax
	movq	%rax, _mails(%rip)
	cmpl	$0, -12(%rbp)
	jne	LBB0_4
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$1, -12(%rbp)
	movl	%eax, -36(%rbp)         ## 4-byte Spill
LBB0_4:                                 ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_5
LBB0_5:                                 ##   in Loop: Header=BB0_1 Depth=1
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -24(%rbp)
	jmp	LBB0_1
LBB0_6:
	leaq	_mutex(%rip), %rdi
	callq	_pthread_mutex_unlock
	leaq	L_.str.2(%rip), %rdi
	movl	%eax, -40(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%ecx, %edi
	movl	%eax, -44(%rbp)         ## 4-byte Spill
	movq	%rdi, %rax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$112, %rsp
	xorl	%eax, %eax
	movl	%eax, %ecx
	movl	$0, -4(%rbp)
	leaq	-16(%rbp), %rdi
	movq	%rcx, %rsi
	leaq	_routine(%rip), %rdx
	callq	_pthread_create
	cmpl	$0, %eax
	je	LBB1_2
## %bb.1:
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	leaq	L_.str.3(%rip), %rsi
	movb	$0, %al
	callq	_fprintf
	movl	$1, -4(%rbp)
	movl	%eax, -60(%rbp)         ## 4-byte Spill
	jmp	LBB1_25
LBB1_2:
	xorl	%eax, %eax
	movl	%eax, %ecx
	leaq	-24(%rbp), %rdi
	movq	%rcx, %rsi
	leaq	_routine(%rip), %rdx
	callq	_pthread_create
	cmpl	$0, %eax
	je	LBB1_4
## %bb.3:
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	leaq	L_.str.4(%rip), %rsi
	movb	$0, %al
	callq	_fprintf
	movl	$1, -4(%rbp)
	movl	%eax, -64(%rbp)         ## 4-byte Spill
	jmp	LBB1_25
LBB1_4:
	xorl	%eax, %eax
	movl	%eax, %ecx
	leaq	-32(%rbp), %rdi
	movq	%rcx, %rsi
	leaq	_routine(%rip), %rdx
	callq	_pthread_create
	cmpl	$0, %eax
	je	LBB1_6
## %bb.5:
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	leaq	L_.str.4(%rip), %rsi
	movb	$0, %al
	callq	_fprintf
	movl	$1, -4(%rbp)
	movl	%eax, -68(%rbp)         ## 4-byte Spill
	jmp	LBB1_25
LBB1_6:
	xorl	%eax, %eax
	movl	%eax, %ecx
	leaq	-40(%rbp), %rdi
	movq	%rcx, %rsi
	leaq	_routine(%rip), %rdx
	callq	_pthread_create
	cmpl	$0, %eax
	je	LBB1_8
## %bb.7:
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	leaq	L_.str.4(%rip), %rsi
	movb	$0, %al
	callq	_fprintf
	movl	$1, -4(%rbp)
	movl	%eax, -72(%rbp)         ## 4-byte Spill
	jmp	LBB1_25
LBB1_8:
	xorl	%eax, %eax
	movl	%eax, %ecx
	leaq	-48(%rbp), %rdi
	movq	%rcx, %rsi
	leaq	_routine(%rip), %rdx
	callq	_pthread_create
	cmpl	$0, %eax
	je	LBB1_10
## %bb.9:
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	leaq	L_.str.4(%rip), %rsi
	movb	$0, %al
	callq	_fprintf
	movl	$1, -4(%rbp)
	movl	%eax, -76(%rbp)         ## 4-byte Spill
	jmp	LBB1_25
LBB1_10:
	xorl	%eax, %eax
	movl	%eax, %ecx
	leaq	-56(%rbp), %rdi
	movq	%rcx, %rsi
	leaq	_routine(%rip), %rdx
	callq	_pthread_create
	cmpl	$0, %eax
	je	LBB1_12
## %bb.11:
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	leaq	L_.str.4(%rip), %rsi
	movb	$0, %al
	callq	_fprintf
	movl	$1, -4(%rbp)
	movl	%eax, -80(%rbp)         ## 4-byte Spill
	jmp	LBB1_25
LBB1_12:
	xorl	%eax, %eax
	movl	%eax, %esi
	movq	-16(%rbp), %rdi
	callq	_pthread_join
	cmpl	$0, %eax
	je	LBB1_14
## %bb.13:
	leaq	L_.str.5(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$1, -4(%rbp)
	movl	%eax, -84(%rbp)         ## 4-byte Spill
	jmp	LBB1_25
LBB1_14:
	xorl	%eax, %eax
	movl	%eax, %esi
	movq	-24(%rbp), %rdi
	callq	_pthread_join
	cmpl	$0, %eax
	je	LBB1_16
## %bb.15:
	leaq	L_.str.6(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$1, -4(%rbp)
	movl	%eax, -88(%rbp)         ## 4-byte Spill
	jmp	LBB1_25
LBB1_16:
	xorl	%eax, %eax
	movl	%eax, %esi
	movq	-32(%rbp), %rdi
	callq	_pthread_join
	cmpl	$0, %eax
	je	LBB1_18
## %bb.17:
	leaq	L_.str.6(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$1, -4(%rbp)
	movl	%eax, -92(%rbp)         ## 4-byte Spill
	jmp	LBB1_25
LBB1_18:
	xorl	%eax, %eax
	movl	%eax, %esi
	movq	-40(%rbp), %rdi
	callq	_pthread_join
	cmpl	$0, %eax
	je	LBB1_20
## %bb.19:
	leaq	L_.str.6(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$1, -4(%rbp)
	movl	%eax, -96(%rbp)         ## 4-byte Spill
	jmp	LBB1_25
LBB1_20:
	xorl	%eax, %eax
	movl	%eax, %esi
	movq	-48(%rbp), %rdi
	callq	_pthread_join
	cmpl	$0, %eax
	je	LBB1_22
## %bb.21:
	leaq	L_.str.6(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$1, -4(%rbp)
	movl	%eax, -100(%rbp)        ## 4-byte Spill
	jmp	LBB1_25
LBB1_22:
	xorl	%eax, %eax
	movl	%eax, %esi
	movq	-56(%rbp), %rdi
	callq	_pthread_join
	cmpl	$0, %eax
	je	LBB1_24
## %bb.23:
	leaq	L_.str.6(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$1, -4(%rbp)
	movl	%eax, -104(%rbp)        ## 4-byte Spill
	jmp	LBB1_25
LBB1_24:
	leaq	_mutex(%rip), %rdi
	callq	_pthread_mutex_destroy
	movq	_mails(%rip), %rsi
	leaq	L_.str.7(%rip), %rdi
	movl	%eax, -108(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	$0, -4(%rbp)
	movl	%eax, -112(%rbp)        ## 4-byte Spill
LBB1_25:
	movl	-4(%rbp), %eax
	addq	$112, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__DATA,__data
	.globl	_mutex                  ## @mutex
	.p2align	3
_mutex:
	.quad	850045863               ## 0x32aaaba7
	.space	56

	.globl	_mails                  ## @mails
.zerofill __DATA,__common,_mails,8,3
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"entered\n"

L_.str.1:                               ## @.str.1
	.asciz	"strated\n"

L_.str.2:                               ## @.str.2
	.asciz	"finished\n"

L_.str.3:                               ## @.str.3
	.asciz	"Error creating thread 1\n"

L_.str.4:                               ## @.str.4
	.asciz	"Error creating thread 2\n"

L_.str.5:                               ## @.str.5
	.asciz	"join 1 failed\n"

L_.str.6:                               ## @.str.6
	.asciz	"join 2 failed\n"

L_.str.7:                               ## @.str.7
	.asciz	"mails : %zu\n"


.subsections_via_symbols
