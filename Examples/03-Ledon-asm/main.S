	
	.text
	.align	1
	.globl	main

	#-- Reset and Control Clock
	.equ RCC_BASE, 0x40021000
	.equ APB2PCENR, 6*4

	#-- Puerto A
	.equ GPIOA_BASE, 0x40010800
	.equ CFGHR, 1*4
	.equ BCR, 5*4

main:

	#-- Habilitar APB2: Puerto A
	li t0, RCC_BASE
	li t1, 0x4
	sw t1, APB2PCENR(t0)

	#-- Configurar pin A15
	li t0, GPIOA_BASE
	li t1, 0x30000000
	sw t1, CFGHR(t0)

	#-- Turn LED on
	li t1, 0x8000
	sw t1, BCR(t0)

	#-- Terminar
stop:
	j stop

