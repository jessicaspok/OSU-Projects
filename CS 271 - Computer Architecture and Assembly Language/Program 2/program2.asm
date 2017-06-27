TITLE Program 2     (program2.asm)

; Author: Jessica Spokoyny
; Course / Project ID : CS 271 Program 2                 Date: 01/20/16
; Description:  This program will get and display the user's name, get 
;	the number of Fibonacci numbers that the user wants to see, 
;	validate that number, calculate the Fibonacci numbers, and display
;	those in groups of 5 per line.

INCLUDE Irvine32.inc

UPPER_LIM			EQU		46
LOWER_LIM			EQU		1

.data
	intro_1		BYTE		"		CS 271 Program 2 - Fibonacci Numbers", 0	   
	intro_2		BYTE		"			  By Jessica Spokoyny", 0
	
	prompt_1		BYTE		"What is your name? ", 0
	prompt_2		BYTE		"How many Fibonacci terms do you want? ", 0

	instruct_1	BYTE		"Enter the number of Fibonacci terms to be displayed ", 0
	instruct_2	BYTE		"Give the number as an integer in the range [1 .. 46]. ", 0
	
	invalid		BYTE		"Out of range. Enter a number in [1 .. 46] ", 0
	greeting		BYTE		"Hi, ", 0
	farewell		BYTE		"Bye Bye, ", 0
	punct		BYTE		"!", 0
	
	userName		DWORD	33 DUP(0)			;Name to be entered by user
	userNum		DWORD	?				;Integer to be entered by user
	num2			DWORD	?
	col			DWORD	?				;Column counter
	

;Extra Credit variable definitions

;Extra Credit 1
	extra_1		BYTE		"**EC: Program displays the numbers in aligned columns.", 0
	five			DWORD	?	
	buffer		BYTE		9,0				;ASCII 9 = tab

;Extra Credit 2
	extra_2		BYTE		"**EC: Program changes text color to magenta ", 0
	extra_3		BYTE		"	and Fibonacci number columns to blue!", 0
	extra_4		BYTE		"** Also, program repeats until the user chooses to quit.", 0
	quitMsg		BYTE		"Press 1 to quit or 0 to keep playing: ",0
	quit			DWORD	?

.code
main PROC

;Extra Credit 2
	;Change text color to magenta
		mov		eax, lightMagenta+(black*16)	
		call		setTextColor

;Introduction

	;Introduce program and author
		mov		edx, OFFSET intro_1		
		call		WriteString
		call		CrLf	
		mov		edx, OFFSET intro_2	
		call		WriteString
		call		CrLf					
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

	;Get user's name
		mov		edx, OFFSET prompt_1
		call		WriteString
		mov		edx, OFFSET userName
		mov		ecx, 32
		call		ReadString
		call		CrLf	

	;Display greeting
		mov		edx, OFFSET greeting
		call		WriteString
		mov		edx, OFFSET userName
		call		WriteString
		mov		edx, OFFSET punct
		call		WriteString
		call		CrLf
		call		CrLf

;userInstructions

	;Display instructions for the user
		mov		edx, OFFSET instruct_1
		call		WriteString
		call		CrLf					
		mov		edx, OFFSET instruct_2
		call		WriteString
		call		CrLf					
		call		CrLf					

;getUserData
.repeat

	;Get number of terms
	GetTerms:
		mov		edx, OFFSET prompt_2
		call		WriteString
		call		ReadInt
		cmp		eax, LOWER_LIM
		jl		Error
		cmp		eax, UPPER_LIM
		jg		Error
		jmp		Valid

	;Number not in range
	Error:
		call		CrLf	
		mov		edx, OFFSET invalid
		call		WriteString
		call		Crlf
		call		CrLf	
		jmp		GetTerms

	;Number in range
	Valid:
		call		CrLf	
		mov		userNum, eax
		call		CrLf

	
;displayFibs

	;Set up 
		;Change text color to blue
		mov		eax, lightBlue+(black*16)
		call		setTextColor

		mov		eax, 1
		call		WriteDec				;Display first Fib term
		mov		edx, OFFSET buffer		
		call		WriteString
		mov		edx, OFFSET buffer		
		call		WriteString
		mov		eax, 0				;(n)
		mov		ebx, 1				;(n - 1)
		mov		num2, 0				;(n - 2)
		mov		ecx, userNum			;Set loop counter to user entered number
		dec		ecx					;Decrement loop counter as first term is already counted
		mov		col, 1				
		mov		five, 5				;Used to see if term should be on same line or next line
		
		;if userNum = 1, fibLoop unnecessary
		cmp		ecx, 1				
		jbe		Bye		
		
				
	;Loop
	fibLoop:
				
		inc		col					;Increment column counter
		
		;To calculate next Fib term (n) = (n - 1) + (n - 2)
		mov		eax, ebx				
		add		eax, num2				
		call		WriteDec				
		
		;Shift (n - 1) and (n - 2)
		mov		num2, ebx				
		mov		ebx, eax				
		
		;Tab to separate terms
		mov		edx,	OFFSET buffer		;For all spaces between numbers, tab once
		call		WriteString
		
		.if		ebx < 14930352			;When the numbers are small, tab twice to align
		mov		edx, OFFSET buffer		
		call		WriteString
		.else
		.endif

		;Five terms per line
		mov		eax, col				
		mov		edx, 0
		div		five					;Divide number of columns by 5
		cmp		edx, 0				;Compare remainder to 0
		je		NextLine				;When equal, move to next line
		jmp		SameLine				;Else, stay on same line

	NextLine:
		call		CrLf
		
	SameLine:
		loop		fibLoop				;Iterate fibLoop until ecx = 0
		
		
	
;farewell
Bye:	
	;Change text color back to magenta
		mov		eax, lightMagenta+(black*16)		
		call		setTextColor
	
	;spacing after Fib terms	
		call		CrLf	
		call		CrLf
		call		CrLf	

	;Repeat until the user chooses to quit
		mov		edx, OFFSET quitMsg
		call		WriteString
		call		ReadInt
		mov		quit, eax
		call		CrLf	

	.until quit == 1

	;Display goodbye message
		mov		edx, OFFSET farewell		
		call		WriteString
		mov		edx, OFFSET userName
		call		WriteString
		mov		edx, OFFSET punct
		call		WriteString
		call		CrLf					
		call		CrLf					

	exit								
main ENDP

END main
