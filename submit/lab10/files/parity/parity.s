	.text
	.globl get_parity
#edi contains n	
get_parity:

	#@TODO: add code here to set eax to 1 iff edi has even parity
	
	testl %eax, %eax
	jpe fix
	movl $0, %eax
	
return:

	ret
	
fix:
	
	movl $1, %eax
	jmp return
