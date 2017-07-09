.section .text
.global _isr0
.type _isr0, @function
_isr0:
	cli
	pushw $0

	pushw $0
	jmp _isr_common_handler
.size _isr0, . - _isr0

.section .text
.global _isr1
.type _isr1, @function
_isr1:
	cli
	pushw $0

	pushw $1
	jmp _isr_common_handler
.size _isr1, . - _isr1

.section .text
.global _isr2
.type _isr2, @function
_isr2:
	cli
	pushw $0

	pushw $2
	jmp _isr_common_handler
.size _isr2, . - _isr2

.section .text
.global _isr3
.type _isr3, @function
_isr3:
	cli
	pushw $0

	pushw $3
	jmp _isr_common_handler
.size _isr3, . - _isr3

.section .text
.global _isr4
.type _isr4, @function
_isr4:
	cli
	pushw $0

	pushw $4
	jmp _isr_common_handler
.size _isr4, . - _isr4

.section .text
.global _isr5
.type _isr5, @function
_isr5:
	cli
	pushw $0

	pushw $5
	jmp _isr_common_handler
.size _isr5, . - _isr5

.section .text
.global _isr6
.type _isr6, @function
_isr6:
	cli
	pushw $0

	pushw $6
	jmp _isr_common_handler
.size _isr6, . - _isr6

.section .text
.global _isr7
.type _isr7, @function
_isr7:
	cli
	pushw $0

	pushw $7
	jmp _isr_common_handler
.size _isr7, . - _isr7

.section .text
.global _isr8
.type _isr8, @function
_isr8:
	cli
	

	pushw $8
	jmp _isr_common_handler
.size _isr8, . - _isr8

.section .text
.global _isr9
.type _isr9, @function
_isr9:
	cli
	pushw $0

	pushw $9
	jmp _isr_common_handler
.size _isr9, . - _isr9

.section .text
.global _isr10
.type _isr10, @function
_isr10:
	cli
	

	pushw $10
	jmp _isr_common_handler
.size _isr10, . - _isr10

.section .text
.global _isr11
.type _isr11, @function
_isr11:
	cli
	

	pushw $11
	jmp _isr_common_handler
.size _isr11, . - _isr11

.section .text
.global _isr12
.type _isr12, @function
_isr12:
	cli
	

	pushw $12
	jmp _isr_common_handler
.size _isr12, . - _isr12

.section .text
.global _isr13
.type _isr13, @function
_isr13:
	cli
	

	pushw $13
	jmp _isr_common_handler
.size _isr13, . - _isr13

.section .text
.global _isr14
.type _isr14, @function
_isr14:
	cli
	

	pushw $14
	jmp _isr_common_handler
.size _isr14, . - _isr14

.section .text
.global _isr15
.type _isr15, @function
_isr15:
	cli
	pushw $0

	pushw $15
	jmp _isr_common_handler
.size _isr15, . - _isr15

.section .text
.global _isr16
.type _isr16, @function
_isr16:
	cli
	pushw $0

	pushw $16
	jmp _isr_common_handler
.size _isr16, . - _isr16

.section .text
.global _isr17
.type _isr17, @function
_isr17:
	cli
	

	pushw $17
	jmp _isr_common_handler
.size _isr17, . - _isr17

.section .text
.global _isr18
.type _isr18, @function
_isr18:
	cli
	pushw $0

	pushw $18
	jmp _isr_common_handler
.size _isr18, . - _isr18

.section .text
.global _isr19
.type _isr19, @function
_isr19:
	cli
	pushw $0

	pushw $19
	jmp _isr_common_handler
.size _isr19, . - _isr19

.section .text
.global _isr20
.type _isr20, @function
_isr20:
	cli
	pushw $0

	pushw $20
	jmp _isr_common_handler
.size _isr20, . - _isr20

.section .text
.global _isr21
.type _isr21, @function
_isr21:
	cli
	pushw $0

	pushw $21
	jmp _isr_common_handler
.size _isr21, . - _isr21

.section .text
.global _isr22
.type _isr22, @function
_isr22:
	cli
	pushw $0

	pushw $22
	jmp _isr_common_handler
.size _isr22, . - _isr22

.section .text
.global _isr23
.type _isr23, @function
_isr23:
	cli
	pushw $0

	pushw $23
	jmp _isr_common_handler
.size _isr23, . - _isr23

.section .text
.global _isr24
.type _isr24, @function
_isr24:
	cli
	pushw $0

	pushw $24
	jmp _isr_common_handler
.size _isr24, . - _isr24

.section .text
.global _isr25
.type _isr25, @function
_isr25:
	cli
	pushw $0

	pushw $25
	jmp _isr_common_handler
.size _isr25, . - _isr25

.section .text
.global _isr26
.type _isr26, @function
_isr26:
	cli
	pushw $0

	pushw $26
	jmp _isr_common_handler
.size _isr26, . - _isr26

.section .text
.global _isr27
.type _isr27, @function
_isr27:
	cli
	pushw $0

	pushw $27
	jmp _isr_common_handler
.size _isr27, . - _isr27

.section .text
.global _isr28
.type _isr28, @function
_isr28:
	cli
	pushw $0

	pushw $28
	jmp _isr_common_handler
.size _isr28, . - _isr28

.section .text
.global _isr29
.type _isr29, @function
_isr29:
	cli
	pushw $0

	pushw $29
	jmp _isr_common_handler
.size _isr29, . - _isr29

.section .text
.global _isr30
.type _isr30, @function
_isr30:
	cli
	

	pushw $30
	jmp _isr_common_handler
.size _isr30, . - _isr30

.section .text
.global _isr31
.type _isr31, @function
_isr31:
	cli
	pushw $0

	pushw $31
	jmp _isr_common_handler
.size _isr31, . - _isr31

_isr_common_handler:
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
	movl 	$_fault_handler, %eax
	call 	*%eax
	popl 	%eax

	popw	%gs
	popw	%fs
	popw	%es
	popw	%ds
	popa

	addl $8, %esp
	iret