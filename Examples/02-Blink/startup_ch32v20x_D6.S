
	.section	.init,"ax",@progbits
	.global	_start
	.align	1
 _start:   
	j	handle_reset

	.section	.text.handle_reset,"ax",@progbits
	.align	1

handle_reset:

    jal main



