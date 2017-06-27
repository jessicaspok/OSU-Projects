TITLE Program 1     (program01.asm)

; Author: Jessica Spokoyny
; Course / Project ID : CS 271 Program 1                 Date: 01/14/16
; Description:  This program will calculate the sum, difference, product,  
;	(integer) quotient and remainder of two numbers entered by the user, 
;	and report the result.

INCLUDE Irvine32.inc

.data
;Variable definitions

	intro_1		BYTE "	CS 271 Program 1		by Jessica Spokoyny", 0
	intro_2		BYTE	"Enter 2 numbers, and I'll show you the sum, difference, product, ", 0
	intro_3		BYTE	"quotient, and remainder. ", 0

	prompt_1		BYTE	"First number: ", 0
	num1			DWORD	?			;Integer to be entered by user
	prompt_2		BYTE	"Second number: ", 0
	num2			DWORD	?			;Integer to be entered by user

	zero			DWORD	0

	multRes		DWORD	?
	addRes		DWORD	?
	subRes		DWORD	?
	quotRes		DWORD	?
	remRes		DWORD	?

	addition		BYTE	" + ", 0
	subtraction	BYTE	" - ", 0
	multiplic		BYTE	" x ", 0
	division		BYTE	" / ", 0
	equals		BYTE	" = ", 0
	remainder		BYTE " remainder ", 0

	goodBye		BYTE	"Bye Bye! ", 0

;Extra Credit variable definitions

;Extra Credit 1
	extra_1		BYTE "**EC: Program repeats until the user chooses to quit.", 0
	quitMsg		BYTE "Press 1 to quit or 0 to keep playing: ",0

	quit			DWORD	?			;BOOL for user to repeat or exit

;Extra Credit 2
	extra_2		BYTE "**EC: Program validates the second number to be less than the first.", 0
	error		BYTE	"The second number must be less than the first.. Try again! ", 0
	error_1		BYTE	"The second number must be greater than 0.. Try again! ", 0

;Extra Credit 3
	extra_3		BYTE "**EC: Program calculates and displays the quotient as a ", 0
	extra_4		BYTE "	floating-point number, rounded to the nearest .001", 0
	floatMsg		BYTE "The quotient as a floating-point number is ",0
	dot			BYTE ".",0

	thousand		DWORD	1000			;Used to multiply and divide to get number rounded to .001
	floatBig		DWORD	0			;Floating point number multiplied by 1000
	floatSmall	REAL4	?			;Small floating point variable after conversion
	floatRem		DWORD	?			;Remainder when floatBig is divided by 1000
	lhs			DWORD	?			;Left-hand-side of the new floating-point number
	rhs			DWORD	?			;Right-hand-side of the new floating-point number
	temp			DWORD	?			;Temporary spot for floating-point value
	
	
.code
main PROC

;Introduction

	;Introduce program and author
		mov		edx, OFFSET intro_1		
		call		WriteString
		call		CrLf					;New line
		call		CrLf					

	;Display extra credit descriptions
		mov		edx, OFFSET extra_1		
		call		WriteString
		call		CrLf					
		mov		edx, OFFSET extra_2
		call		WriteString
		call		CrLf
		mov		edx, OFFSET extra_3
		call		WriteString
		call		CrLf
		mov		edx, OFFSET extra_4
		call		WriteString
		call		CrLf					
		call		CrLf	

	;Display instructions for the user
		mov		edx, OFFSET intro_2
		call		WriteString
		call		CrLf					
		mov		edx, OFFSET intro_3
		call		WriteString
		call		CrLf					
		call		CrLf					

;Get the data

.repeat								;Create loop to allow repetition
	
	L3:

	;Get first number
		mov		edx, OFFSET prompt_1
		call		WriteString
		call		ReadInt
		mov		num1, eax

	;Get second number
		mov		edx, OFFSET prompt_2
		call		WriteString
		call		ReadInt
		mov		num2, eax
		call		CrLf					

	;Extra credit 2- Validate the second number < first
		mov 		ebx, num1
		mov		ecx, num2
		cmp		ebx, ecx				;Compare ebx and ecx
		jbe		L1					;If (ecx >= ebx) go to L1


;Calculate values

	;Calculate sum
		mov		eax, num1
		add		eax, num2
		mov		addRes, eax

	;Calculate difference
		mov		eax, num1
		sub		eax, num2
		mov		subRes, eax

	;Calculate product
		mov		eax, num1
		mov		ebx, num2
		mul		ebx
		mov		multRes, eax

	;Calculate quotient and remainder
		mov		eax, num1
		mov		edx, 0				
		div		num2
		mov		quotRes, eax
		mov		remRes, edx

	;Extra credit 3- Calculate floating-point quotient
		fld		num1					;Load first number onto the stack
		fdiv		num2					;Divide first number by second number
		fimul	thousand				;Multiply result by 1000
		frndint						;Round result to the nearest integer
		fist		floatBig				;Convert result to an integer
		fst		floatSmall			;Copy value from stack to floatSmall


;Display results

	;Report sum
		mov		eax, num1				;Print first number
		call		WriteDec
		mov		edx, OFFSET addition	;Print '+' sign
		call		WriteString
		mov		eax, num2				;Print second number
		call		WriteDec
		mov		edx, OFFSET equals		;Print '=' sign
		call		WriteString	
		mov		eax, addRes			;Print sum
		call		WriteDec
		call		CrLf					

	;Report difference
		mov		eax, num1				;Print first number
		call		WriteDec
		mov		edx, OFFSET subtraction	;Print '-' sign
		call		WriteString
		mov		eax, num2				;Print second number
		call		WriteDec
		mov		edx, OFFSET equals		;Print '=' sign
		call		WriteString
		mov		eax, subRes			;Print difference
		call		WriteDec
		call		CrLf					

	;Report product		
		mov		eax, num1				;Print first number
		call		WriteDec
		mov		edx, OFFSET multiplic	;Print 'x' sign
		call		WriteString
		mov		eax, num2				;Print second number
		call		WriteDec
		mov		edx, OFFSET equals		;Print '=' sign
		call		WriteString
		mov		eax, multRes			;Print product
		call		WriteDec
		call		CrLf					

	;Report quotient and remainder		
		mov		eax, num1				;Print first number
		call		WriteDec
		mov		edx, OFFSET division	;Print '/' sign
		call		WriteString
		mov		eax, num2				;Print second number
		call		WriteDec
		mov		edx, OFFSET equals		;Print '=' sign
		call		WriteString
		mov		eax, quotRes			;Print quotient (integer)
		call		WriteDec
		mov		edx, OFFSET remainder	;Print 'remainder'
		call		WriteString
		mov		eax, remRes			;Print remainder
		call		WriteDec	
		call		CrLf					
		call		CrLf				
	
	;Extra credit 3- Report floating-point quotient
	
		mov		edx, OFFSET floatMsg	;Print float message
		call		WriteString
		mov		edx, 0				;Set edx to 0
		mov		eax, floatBig			;Set eax to floatBig
		cdq							;Convert DWORD to QWORD
		mov		ebx, 1000
		cdq							;Convert DWORD to QWORD
		div		ebx					;Divide floatBig by 1000
		mov		lhs, eax				;Save the part before the decimal 
		mov		floatRem, edx			;Save the part after the decimal
		mov		eax, lhs				;Print the part before the decimal
		call		WriteDec				
		mov		edx, OFFSET dot		;Print '.'
		call		WriteString

		mov		eax, lhs				;Set eax to the part before the decimal 
		mul		thousand				;Multiply eax by 1000
		mov		temp, eax				;Save result in temp variable
		mov		eax, floatBig			;Set eax to the result of the division x 1000 
		sub		eax, temp				;Subtract temp result from eax
		mov		rhs, eax				;Print the part after the decimal
		call		WriteDec
		call		CrLf	
		call		CrLf	
	
		jmp		L2


		
;Say goodbye

	L1:
	mov		edx, OFFSET error
	call		WriteString
	call		CrLf	
	call		CrLf	

	jmp		L3
	
	
	L2:
	;Extra credit 1- Repeat until the user chooses to quit
	mov		edx, OFFSET quitMsg
	call		WriteString
	call		ReadInt
	mov		quit, eax
	call		CrLf	

	.until quit == 1

	mov		edx, OFFSET goodBye
	call		WriteString
	call		CrLf					
	call		CrLf					

	exit								;Exit to operating system
main ENDP

END main
