.section .text
.global _irq0
.type _irq0, @function
_irq0:
	cli
	pushl $0

	pushl $32
	jmp _irq_common_handler
.size _irq0, . - _irq0

.global _irq1
.type _irq1, @function
_irq1:
	cli
	pushl $0

	pushl $33
	jmp _irq_common_handler
.size _irq1, . - _irq1

.global _irq2
.type _irq2, @function
_irq2:
	cli
	pushl $0

	pushl $34
	jmp _irq_common_handler
.size _irq2, . - _irq2

.global _irq3
.type _irq3, @function
_irq3:
	cli
	pushl $0

	pushl $35
	jmp _irq_common_handler
.size _irq3, . - _irq3

.global _irq4
.type _irq4, @function
_irq4:
	cli
	pushl $0

	pushl $36
	jmp _irq_common_handler
.size _irq4, . - _irq4

.global _irq5
.type _irq5, @function
_irq5:
	cli
	pushl $0

	pushl $37
	jmp _irq_common_handler
.size _irq5, . - _irq5

.global _irq6
.type _irq6, @function
_irq6:
	cli
	pushl $0

	pushl $38
	jmp _irq_common_handler
.size _irq6, . - _irq6

.global _irq7
.type _irq7, @function
_irq7:
	cli
	pushl $0

	pushl $39
	jmp _irq_common_handler
.size _irq7, . - _irq7

.global _irq8
.type _irq8, @function
_irq8:
	cli
	pushl $0

	pushl $40
	jmp _irq_common_handler
.size _irq8, . - _irq8

.global _irq9
.type _irq9, @function
_irq9:
	cli
	pushl $0

	pushl $41
	jmp _irq_common_handler
.size _irq9, . - _irq9

.global _irq10
.type _irq10, @function
_irq10:
	cli
	pushl $0

	pushl $42
	jmp _irq_common_handler
.size _irq10, . - _irq10

.global _irq11
.type _irq11, @function
_irq11:
	cli
	pushl $0

	pushl $43
	jmp _irq_common_handler
.size _irq11, . - _irq11

.global _irq12
.type _irq12, @function
_irq12:
	cli
	pushl $0

	pushl $44
	jmp _irq_common_handler
.size _irq12, . - _irq12

.global _irq13
.type _irq13, @function
_irq13:
	cli
	pushl $0

	pushl $45
	jmp _irq_common_handler
.size _irq13, . - _irq13

.global _irq14
.type _irq14, @function
_irq14:
	cli
	pushl $0

	pushl $46
	jmp _irq_common_handler
.size _irq14, . - _irq14

.global _irq15
.type _irq15, @function
_irq15:
	cli
	pushl $0

	pushl $47
	jmp _irq_common_handler
.size _irq15, . - _irq15


_irq_common_handler:
	pusha

	pushw 	%ds
	pushw 	%es
	pushw 	%fs
	pushw 	%gs

	movw 	$0x18, %ax
	movw 	%ax, %ds
	movw 	%ax, %es
	movw 	%ax, %fs
	movw 	%ax, %gs
	movl 	%esp, %eax
	pushl 	%eax
	movl 	$_irq_handler, %eax
	call 	*%eax
	popl 	%eax

	popw	%gs
	popw	%fs
	popw	%es
	popw	%ds
	popa

	addl $8, %esp
	sti
	iret
