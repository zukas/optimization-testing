	.file	"main.cpp"
# GNU C++14 (Ubuntu 6.3.0-12ubuntu2) version 6.3.0 20170406 (x86_64-linux-gnu)
#	compiled by GNU C version 6.3.0 20170406, GMP version 6.1.2, MPFR version 3.1.5, MPC version 1.0.3, isl version 0.15
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultiarch x86_64-linux-gnu -D_GNU_SOURCE main.cpp
# -mtune=generic -march=x86-64 -fverbose-asm -fstack-protector-strong
# -Wformat -Wformat-security
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -fasynchronous-unwind-tables -fauto-inc-dec -fchkp-check-incomplete-type
# -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
# -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
# -fchkp-use-static-bounds -fchkp-use-static-const-bounds
# -fchkp-use-wrappers -fcommon -fdelete-null-pointer-checks
# -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
# -fexceptions -ffunction-cse -fgcse-lm -fgnu-runtime -fgnu-unique -fident
# -finline-atomics -fira-hoist-pressure -fira-share-save-slots
# -fira-share-spill-slots -fivopts -fkeep-static-consts
# -fleading-underscore -flifetime-dse -flto-odr-type-merging -fmath-errno
# -fmerge-debug-strings -fpeephole -fplt -fprefetch-loop-arrays
# -freg-struct-return -fsched-critical-path-heuristic
# -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
# -fsched-last-insn-heuristic -fsched-rank-heuristic -fsched-spec
# -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-fusion
# -fsemantic-interposition -fshow-column -fsigned-zeros
# -fsplit-ivs-in-unroller -fssa-backprop -fstack-protector-strong
# -fstdarg-opt -fstrict-volatile-bitfields -fsync-libcalls -ftrapping-math
# -ftree-cselim -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im
# -ftree-loop-ivcanon -ftree-loop-optimize -ftree-parallelize-loops=
# -ftree-phiprop -ftree-reassoc -ftree-scev-cprop -funit-at-a-time
# -funwind-tables -fverbose-asm -fzero-initialized-in-bss
# -m128bit-long-double -m64 -m80387 -malign-stringops
# -mavx256-split-unaligned-load -mavx256-split-unaligned-store
# -mfancy-math-387 -mfp-ret-in-387 -mfxsr -mglibc -mieee-fp
# -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone -msse -msse2
# -mstv -mtls-direct-seg-refs -mvzeroupper

	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.section	.text._ZN6Object9UpdateFooEf,"axG",@progbits,_ZN6Object9UpdateFooEf,comdat
	.align 2
	.weak	_ZN6Object9UpdateFooEf
	.type	_ZN6Object9UpdateFooEf, @function
_ZN6Object9UpdateFooEf:
.LFB2297:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -24(%rbp)	# this, this
	movss	%xmm0, -28(%rbp)	# f, f
	movq	-24(%rbp), %rax	# this, tmp97
	movss	8(%rax), %xmm1	# this_2(D)->m_Velocity, _3
	movq	-24(%rbp), %rax	# this, tmp98
	movss	8(%rax), %xmm0	# this_2(D)->m_Velocity, _4
	mulss	%xmm0, %xmm1	# _4, _5
	movq	-24(%rbp), %rax	# this, tmp99
	movss	12(%rax), %xmm2	# this_2(D)->m_Velocity, _6
	movq	-24(%rbp), %rax	# this, tmp100
	movss	12(%rax), %xmm0	# this_2(D)->m_Velocity, _7
	mulss	%xmm2, %xmm0	# _6, _8
	addss	%xmm1, %xmm0	# _5, _9
	call	sqrtf@PLT	#
	movd	%xmm0, %eax	#, tmp101
	movl	%eax, -4(%rbp)	# tmp101, mag
	movq	-24(%rbp), %rax	# this, tmp102
	movss	56(%rax), %xmm1	# this_2(D)->m_Foo, _12
	movss	-4(%rbp), %xmm0	# mag, tmp103
	mulss	-28(%rbp), %xmm0	# f, _14
	addss	%xmm1, %xmm0	# _12, _15
	movq	-24(%rbp), %rax	# this, tmp104
	movss	%xmm0, 56(%rax)	# _15, this_2(D)->m_Foo
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2297:
	.size	_ZN6Object9UpdateFooEf, .-_ZN6Object9UpdateFooEf
	.text
	.globl	main
	.type	main, @function
main:
.LFB2298:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$80, %rsp	#,
	movq	%fs:40, %rax	#, tmp95
	movq	%rax, -8(%rbp)	# tmp95, D.43678
	xorl	%eax, %eax	# tmp95
	call	rand@PLT	#
	pxor	%xmm0, %xmm0	# _4
	cvtsi2ss	%eax, %xmm0	# _3, _4
	movss	.LC0(%rip), %xmm1	#, tmp92
	divss	%xmm1, %xmm0	# tmp92, _5
	leaq	-80(%rbp), %rax	#, tmp93
	movq	%rax, %rdi	# tmp93,
	call	_ZN6Object9UpdateFooEf	#
	movl	$0, %eax	#, _7
	movq	-8(%rbp), %rdx	# D.43678, tmp96
	xorq	%fs:40, %rdx	#, tmp96
	je	.L4	#,
	call	__stack_chk_fail@PLT	#
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2298:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1099694080
	.ident	"GCC: (Ubuntu 6.3.0-12ubuntu2) 6.3.0 20170406"
	.section	.note.GNU-stack,"",@progbits
