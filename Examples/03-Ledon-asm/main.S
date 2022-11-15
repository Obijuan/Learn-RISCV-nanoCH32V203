	
	.text
	.align	1
	.globl	main
	.type	main, @function

	.equ DIR, (0x40010800 + 4)
	.equ RCC_APB2PCENR, (0x40021000 + 6*4)
	.equ GPIOA_CFGHR,   (0x40010800 + 1*4)
	.equ GPIOA_BCR,     (0x40010800 + 5*4)

main:

	#-- Habilitar APB2: Puerto A
	li t0, RCC_APB2PCENR
	li t1, 0x4
	sw t1, (t0)

	#-- Configurar pin A15
	li t0, GPIOA_CFGHR
	li t1, 0x30000000
	sw t1, (t0)

	#-- Turn LED on
	li t0, GPIOA_BCR
	li t1, 0x8000
	sw t1, (t0)

stop:
	j stop

