TITLE Program 6	(program06a_Spokoyny.asm)

; Author: Jessica Spokoyny
; Course / Project ID : CS 271 Program 6A                Date: 03/09/16
; Description: This program gets 10 valid integers from the user and 
; stores the numeric values in an array. The program then displays the 
; integers, their sum, and their average.

INCLUDE Irvine32.inc

;------------------------------------------------------------------------------
; getString
; 
; Description:		 Displays a prompt, then gets the user's keyboard input 
;				 into a memory location.
; Receives:		 prompt to display, string buffer, length of string buffer
; Returns:		 none
; Registers changed: edx, ecx
;------------------------------------------------------------------------------
getString	MACRO	a, x, x_size

	push		edx
	push		ecx

	mov		edx, a			;display the prompt passed in
	call		WriteString
	mov		edx, x			;store user input
	mov		ecx, x_size
	call		ReadString

	pop		ecx
	pop		edx

ENDM

;------------------------------------------------------------------------------
; displayString
; 
; Description:		 Displays the string stored in a specific memory location.
; Receives:		 string to display
; Returns:		 none
; Registers changed: edx
;------------------------------------------------------------------------------
displayString	MACRO	x

	push		edx

	mov		edx, x
	call		WriteString

	pop		edx
ENDM


.data
intro		BYTE		"	    CS 271 Program 6a - Designing low-level I/O procedures", 13, 10
			BYTE		"		       	    By Jessica Spokoyny", 0
instruct		BYTE		"Please provide 10 unsigned decimal integers.", 13, 10
			BYTE		"Each number needs to be small enough to fit inside a 32 bit register.", 13, 10
			BYTE		"After you have finished inputting the raw numbers I will display a list", 13, 10
			BYTE		"of the integers, their sum, and their average value.", 0

prompt_1		BYTE		"Please enter an unsigned number: ", 0
prompt_2		BYTE		"Please try again: ", 0
error		BYTE		"ERROR: You did not enter an unsigned number or your number was too big.", 0

intList		BYTE		"You entered the following numbers:", 0
intSum		BYTE		"The sum of these numbers is: ", 0
intAvg		BYTE		"The average is: ", 0
farewell		BYTE		"Thanks for playing!", 0

comma		BYTE		", ", 0
array		DWORD	10 DUP(?)


.code
main	PROC
	
	push		OFFSET intro			;display intro message
	push		OFFSET instruct
	call		introduction

	push		OFFSET array			;get the ints from the user
	push		LENGTHOF array
	push		OFFSET prompt_1
	push		OFFSET prompt_2
	push		OFFSET error
	call		getData

	push		OFFSET array			;display the user's ints
	push		LENGTHOF array
	push		OFFSET intList
	push		OFFSET comma
	call		displayList

	push		OFFSET array			;calculate and display sum/avg
	push		LENGTHOF array
	push		OFFSET intSum
	push		OFFSET intAvg
	call		displaySumAvg

	push		OFFSET farewell		;display goodbye message
	call		goodbye

	exit
main	ENDP

;------------------------------------------------------------------------------
; introduction
; 
; Description:		 Displays title, programmer's name, and brief instructions
; Receives:		 intro string, instruct string
; Returns:		 none
; Registers changed: ebp, edx
;------------------------------------------------------------------------------
introduction PROC	USES	edx

	push			ebp
	mov			ebp, esp

	mov			edx, [ebp+16]		;@intro
	displayString	edx
	call			Crlf
	call			Crlf

	mov			edx, [ebp+12]		;@instruct
	displayString	edx
	call			Crlf
	call			Crlf

	pop			ebp
	ret			8

introduction ENDP

;------------------------------------------------------------------------------
; getData
;
; Description:		 Gets the user's keyboard input to fill an array. Calls 
;				 readVal to get the string of digits, which calls validate 
;				 to validate to validate the user's input, which calls 
;				 convertToNum to convert the digit string to numeric.
; Receives:		 array, LENGTHOF array, prompt_1 string, prompt_2 string, 
;				 error string
; Returns:		 none
; Registers changed: ebp, esi, ecx, eax
;------------------------------------------------------------------------------
getData PROC	USES esi ecx eax

	push		ebp
	mov		ebp, esp
	
	mov		esi, [ebp+36]		;@array
	mov		ecx, [ebp+32]		;length of array

fillArray:
	mov		eax, [ebp+28]		;@prompt_1
	push		eax
	push		[ebp+24]			;@prompt_2
	push		[ebp+20]			;@error
	call		readVal
	pop		[esi]			;store converted number in array
	add		esi, 4			;move on to next element of array
	loop		fillArray

	pop		ebp
	ret		20

getData ENDP

;------------------------------------------------------------------------------
; readVal
;
; Description:		 Invokes the getString macro to get the user’s string of 
;				 digits, calls validate to validate the user's input, which  
;				 then calls convertToNum to convert the digit string to 
;				 numeric.
; Receives:		 prompt_1 string, prompt_2 string, error string
; Returns:		 validated user input 
; Registers changed: ebp, eax, ebx, esi, ecx
;------------------------------------------------------------------------------
readVal PROC	USES	eax ebx

	LOCAL	userNum[10]:BYTE, valid:DWORD

	push		esi
	push		ecx
	mov		eax, [ebp+16]		;@prompt_1
	lea		ebx, userNum

inputLoop:
	getString	eax, ebx, LENGTHOF userNum
	mov		ebx, [ebp+8]		;@error
	push		ebx
	lea		eax, valid
	push		eax
	lea		eax, userNum
	push		eax
	push		LENGTHOF userNum
	call		validate
	pop		edx
	mov		[ebp+16], edx		;store converted number
	mov		eax, valid		;check if userNum is valid
	cmp		eax, 1
	mov		eax, [ebp+12]		;@prompt_2
	lea		ebx, userNum
	jne		inputLoop

	pop		ecx
	pop		esi

	ret		8				;leave result on the stack

readVal ENDP

;------------------------------------------------------------------------------
; validate
; 
; Description:		 Validates that a user input string is an unsigned integer. 
;				 Calls convertToNum check that it fits in a 32-bit register
; Receives:		 error string, valid (from readVal), userNum, LENGTHOF 
;				 userNum
; Returns:		 converted number, valid
; Registers changed: ebp, esi, ecx, eax, edx
;------------------------------------------------------------------------------
validate PROC	USES	esi ecx eax edx

	LOCAL tooBig:DWORD

	mov			esi, [ebp+12]		;@userNum
	mov			ecx, [ebp+8]		;length of userNum
	cld

checkString:						;load in the string byte by byte
	lodsb
	cmp			al, 0			;check for null
	je			nullChar
	cmp			al, 48			;can't be less than 48 (ascii 0)
	jl			invalid
	cmp			al, 57			;can't be more than 57 (ascii 9)
	ja			invalid
	loop			checkString

invalid:
	call			Crlf
	mov			edx, [ebp+20]		;@error
	displayString	edx
	call			Crlf
	mov			edx, [ebp+16]		;@valid
	mov			eax, 0
	mov			[edx], eax		;set valid to false
	jmp			endVal

nullChar:							
	mov			edx, [ebp+8]		;check that some int was entered
	cmp			ecx, edx			
	je			invalid			
	lea			eax, tooBig
	mov			edx, 0
	mov			[eax], edx
	push			[ebp+12]			;@userNum
	push			[ebp+8]			;length or userNum
	lea			edx, tooBig
	push			edx
	call			convertToNum
	mov			edx, tooBig		;check if converted number is too big
	cmp			edx, 1
	je			invalid
	mov			edx, [ebp+16]		;@valid
	mov			eax, 1			;set valid to true
	mov			[edx], eax

endVal:
	call			Crlf
	pop			edx				;result of convertToNum
	mov			[ebp+20], edx		;store result in [ebp+20]

	ret			12				;leave result on the stack

validate	ENDP

;------------------------------------------------------------------------------
; convertToNum
;
; Description:		 Converts a digit string to numeric.
; Receives:		 userNum, LENGTHOF userNum, tooBig (from validate)
; Returns:		 converted number (or placeholder if number was too big), 
;				 tooBig
; Registers changed: ebp, esi, ecx, eax, ebx, edx
;------------------------------------------------------------------------------
convertToNum PROC	USES	esi ecx eax ebx edx

	LOCAL tempNum:DWORD

	mov		esi, [ebp+16]			;@userNum
	mov		ecx, [ebp+12]			;length of userNum
	lea		eax, tempNum
	xor		ebx, ebx				
	mov		[eax], ebx			
	xor		eax, eax
	xor		edx, eax				;clear Of and CF
	cld

readDigits:						;load in the string byte by byte
	lodsb
	cmp		eax, 0				;check for end of string
	je		endRead
	sub		eax, 48				;convert from ascii
	mov		ebx, eax
	mov		eax, tempNum
	mov		edx, 10
	mul		edx
	jc		numtooBig				;check CF
	add		eax, ebx
	jc		numtooBig				;check CF
	mov		tempNum, eax			;store in tempNum
	mov		eax, 0				
	loop		readDigits

endRead:
	mov		eax, tempNum
	mov		[ebp+16], eax			;store converted number
	jmp		done

numtooBig:						;result can't fit in 32-bit register
	mov		ebx, [ebp+8]			;@tooBig
	mov		eax, 1				;set tooBig to true
	mov		[ebx], eax
	mov		eax, 0
	mov		[ebp+16], eax			;placeholder

done:
	ret		8					;leave result on the stack

convertToNum ENDP

;------------------------------------------------------------------------------
; displayList
; 
; Description:		 Displays an array of numbers. Calls convertToChar to 
;				 convert the numeric values to strings of digits, and 
;				 invokes the displayString macro to produce the output.
; Receives:		 array, LENGTHOF array, intList string, comma string
; Returns:		 none
; Registers changed: ebp, esi, ecx, ebx, edx
;------------------------------------------------------------------------------
displayList PROC	USES	esi ebx ecx edx

	push			ebp
	mov			ebp, esp
		
	call			Crlf						
	mov			edx, [ebp+28]		;@intList
	displayString	edx				
	call			Crlf

	mov			esi, [ebp+36]		;@array
	mov			ecx, [ebp+32]		;length of array
	mov			ebx, 1			;counter for numbers displayed

printNum:
	push			[esi]
	call			WriteVal
	add			esi, 4			;move on to next integer
	cmp			ebx, [ebp+32]		;length of array
	jge			endList			;skip the comma at end of list
	mov			edx, [ebp+24]		;comma
	displayString	edx
	inc			ebx				;increment counter
	loop			printNum

endList:
	call			Crlf
	call			Crlf

	pop			ebp
	ret			16
displayList ENDP

;------------------------------------------------------------------------------
; displaySumAvg
; 
; Description:		 Displays the sum and average of an array of integers. 
; Receives:		 array, LENGTHOF array, intSum string, intAvg string
; Returns:		 none
; Registers changed: ebp, edx, esi, ecx, eax, ebx
;------------------------------------------------------------------------------
displaySumAvg PROC	USES	esi	edx ecx eax ebx
	
	push			ebp
	mov			ebp, esp

	mov			edx, [ebp+32]		;@intSum
	displayString	edx

	mov			esi, [ebp+40]		;@array
	mov			ecx, [ebp+36]		;length of array
	xor			eax, eax			;clear OF and CF
	
findSum:						
	add			eax, [esi]		;add current int
	add			esi, 4			;move on to next int
	loop			findSum		
	
	push			eax				;display sum
	call			writeVal					
	call			Crlf
	call			Crlf

	mov			edx, [ebp+28]		;@intAvg
	displayString	edx
	cdq

	mov			ebx, [ebp+36]		;length of array
	div			ebx

	push			eax				;display average
	call			writeVal
	call			Crlf
	
	pop			ebp
	ret			16

displaySumAvg	ENDP

;------------------------------------------------------------------------------
; writeVal
; 
; Description:		 Calls convertToChar to convert a numeric value to a string 
;				 of digits and invokes the displayString macro to produce 
;				 the output.
; Receives:		 integer from array
; Returns:		 none
; Registers changed: ebp, eax
;------------------------------------------------------------------------------
writeVal PROC	USES	eax
	
	LOCAL outputStr[11]:BYTE

	lea			eax, outputStr
	push			eax
	push			[ebp+8]			;integer to be converted	
	call			convertToChar

	lea			eax, outputStr
	displayString	eax

	ret			4

writeVal		ENDP

;------------------------------------------------------------------------------
; convertToChar
;
; Description:		 Converts a numeric value to a string of digits and saves 
;				 the result in outputStr
; Receives:		 outputStr, integer from array
; Returns:		 none
; Registers changed: ebp, eax, ebx, ecx
;------------------------------------------------------------------------------
convertToChar PROC	USES	eax ebx ecx
	
	LOCAL tempChar:DWORD			
		
	mov		eax, [ebp+8]			;move the integer to be converted to eax		
	mov		ebx, 10
	mov		ecx, 0				;counts the iterations of divideTen (number of digits in the integer)
	cld

divideTen:						;find number of digits in the int and push them in reverse order
	cdq
	div		ebx					;divide by 10
	push		edx					;the remainder will be the last digit of the integer
	inc		ecx				
	cmp		eax, 0				;when eax = 0, no more digits exist
	jne		divideTen

	mov		edi, [ebp+12]			;@outputStr

storeChar:
	pop		tempChar
	mov		al, BYTE PTR tempChar
	add		al, 48				;convert to ascii
	stosb
	loop		storeChar

	mov		al, 0
	stosb

	ret		8

convertToChar ENDP

;------------------------------------------------------------------------------
; goodbye
;
; Description:		 Displays goodbye message
; Receives:		 farewell string
; Returns:		 none
; Registers changed: ebp, edx
;------------------------------------------------------------------------------
goodbye PROC	USES	edx

	push			ebp
	mov			ebp, esp

	call			Crlf
	mov			edx, [ebp+12]		;@farewell
	displayString	edx
	call			Crlf
	call			Crlf

	pop			ebp

	ret	4

goodbye ENDP

END	main