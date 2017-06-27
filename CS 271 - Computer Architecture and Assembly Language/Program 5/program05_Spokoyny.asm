TITLE Program 5     (program05_Spokoyny.asm)

; Author: Jessica Spokoyny
; Course / Project ID : CS 271 Program 5                 Date: 02/26/16
; Description:  This program generates random numbers in the range 
; [100 .. 999], displays the original list, sorts the list, and 
; calculates the median value. Finally, it displays the list 
; sorted in descending order.

INCLUDE Irvine32.inc

MIN = 10		;min value for user request
MAX = 200		;max value for user request
LO = 100		;min value for randomly generated int
HI = 999		;max value for randomly generated int

.data
intro_1		BYTE		"		CS 271 Program 5 - Sorting Random Integers", 0	   
intro_2		BYTE		"			    By Jessica Spokoyny", 0

instruct_1	BYTE		"This program generates random numbers in the range [100 .. 999],", 0 
instruct_2	BYTE		"displays the original list, sorts the list, and calculates the", 0 
instruct_3	BYTE		"median value. Finally, it displays the list sorted in descending order.", 0

prompt_1		BYTE		"How many numbers should be generated? [10 .. 200]: ", 0
error		BYTE		"Invalid input", 0
unsorted		BYTE		"The unsorted random numbers: ", 0
sorted		BYTE		"The sorted list: ", 0
median		BYTE		"The median is ", 0

tabs			BYTE		9,0			;horizontal tab
period		BYTE		".", 0
request		DWORD	?			;number of random numbers to generate
array		DWORD	MAX DUP(?)	;array of requested ints


.code
main PROC
call		Randomize					;seeds random num generator

call		introduction				

;get data
	push		OFFSET request			
	push		OFFSET prompt_1		
	push		OFFSET error			
	call		getData				

;fill array
	push		OFFSET array			
	push		request				
	call		fillArray

;display unsorted array
	push		OFFSET tabs			
	push		OFFSET array			
	push		request				
	push		OFFSET unsorted		
	call		displayList	

;sort the array
	push		OFFSET array			
	push		request				
	call		sortArray


;display median
	push		request				
	push		OFFSET array			
	push		OFFSET median			
	push		OFFSET period			
	call		displayMedian

;display sorted array
	push		OFFSET tabs			
	push		OFFSET array			
	push		request				
	push		OFFSET sorted			
	call		displayList		

	exit	
main ENDP

;------------------------------------------------------------------------------
; introduction
;
; Description:	Displays title, programmer's name, and brief instructions
;
; Receives:	none
; Returns:	none
;------------------------------------------------------------------------------
introduction PROC

	mov		edx,OFFSET intro_1
	call		WriteString
	call		Crlf
	mov		edx,OFFSET intro_2
	call		WriteString
	call		Crlf
	call		Crlf

	mov		edx,OFFSET instruct_1
	call		WriteString
	call		Crlf
	mov		edx,OFFSET instruct_2
	call		WriteString
	call		Crlf
	mov		edx,OFFSET instruct_3
	call		WriteString
	call		Crlf
	call		Crlf

	ret

introduction ENDP


;------------------------------------------------------------------------------
; getData
;
; Description:	Gets a user request in the range [10 .. 200] for how many random
; numbers to generate.
;
; Receives:	address of request, address of titles
; Returns:	number of ints to generate
;------------------------------------------------------------------------------
getData PROC

	push		ebp
	mov		ebp,esp

	get:
		mov		edx,[ebp+12]		;@prompt_1 text
		call		WriteString
		call		readDec			;user request
	
		cmp		eax,MIN
		jl		invalid			;request < 10
		cmp		eax,MAX
		jg		invalid			;request > 200
		jmp		valid			

	invalid:
		mov		edx,[ebp+8]		;@error text
		call		WriteString
		call		Crlf

		jmp		get				;repeat until request valid

	valid:
		mov		ebx,[ebp+16]		;@request
		mov		[ebx],eax			

	pop		ebp

	ret	12			

getData ENDP


;------------------------------------------------------------------------------
; fillArray
;
; Description:	Generates requested random integers in the range [lo = 100 .. 
; hi = 999], storing them in consecutive elements of an array.  
;
; Receives:	address of array, request
; Returns:	filled array
;------------------------------------------------------------------------------
fillArray PROC

	push		ebp
	mov		ebp,esp

	mov		edi,[ebp+12]			;@array
	mov		ecx,[ebp+8]			;request

	fill:	
		mov		eax, HI
		sub		eax, LO
		inc		eax	
		call		RandomRange		;generates number 0-899
		add		eax,LO		

		mov		[edi],eax			;place random number into array
		add		edi,4			;move on to next element
		loop		fill				;decrement count
	
	pop		ebp

	ret	8

fillArray ENDP


;------------------------------------------------------------------------------
; sortArray
;
; Description: Sorts the list in descending order (i.e., largest first).
;
; Receives:	address of array, request
; Returns:	sorted array
;------------------------------------------------------------------------------
sortArray PROC
	push		ebp
	mov		ebp,esp

	mov		ecx,[ebp+8]			;request
	dec		ecx					;ecx - 1

	outerLoop:
		push		ecx
		mov		esi, [ebp+12]		;@array

	innerLoop:
		mov		eax, [esi]		;value of current element
		cmp		[esi+4], eax		;if next < current, move on
		jl		next
		jmp		swap				

	swap:
		xchg		[esi+4], eax		;swap the values
		mov		[esi], eax

	next:
		add		esi, 4			;move on to next element		
		loop		innerLoop			;iterate

		pop		ecx
		loop		outerLoop

	pop		ebp

	ret	8			
sortArray ENDP


;------------------------------------------------------------------------------
; displayList
;
; Description:	Displays the list of integers, 10 numbers per line.
;
; Receives:	address of array, request, address of titles
; Returns:	none
;------------------------------------------------------------------------------
displayList PROC

	push		ebp			
	mov		ebp, esp

	mov		esi, [ebp+16]			;@array
	mov		ecx, [ebp+12]			;request
	mov		ebx, 0				;count how many printed

	call		Crlf					;print title
	mov		edx,[ebp+8]			;@unsorted text
	call		WriteString
	call		Crlf

	display:						;print numbers in array 
		mov		eax, [esi]
		call		WriteDec
		add		esi, 4			;move on to next element
		inc		ebx	
		cmp		ebx, 10			;check if new line is needed
		je		newLine
		mov		edx, [ebp+20]		;@tabs text
		call		WriteString
		jmp		next

	newLine:						;print on next line
		call		Crlf
		mov		ebx,0		

	next:						;continue
		loop		display
	
	call		Crlf					
	pop		ebp
	
	ret		16

displayList ENDP


;------------------------------------------------------------------------------
; displayMedian
;
; Description:	Calculates and displays the median value, rounded to the nearest
; integer.
;
; Receives:	address of array, request
; Returns:	median of array
;------------------------------------------------------------------------------
displayMedian PROC

	push		ebp
	mov		ebp, esp
	
	call		Crlf
	mov		eax, [ebp+20]			;request
	mov		esi, [ebp+16]			;@array

	mov		ebx, 2				;find middle element
	mov		edx, 0

	div		ebx					;request / 2
	cmp		edx, 0				;compare remainder to 0
	je		isEven				
	jmp		isOdd				

	isEven:
		mov		ebx, 4			;size of each element in array
		mul		ebx				;(request/2)*4 = offset

		mov		ebx, [esi+eax]		;int above midpoint
		sub		eax, 4			;int below midpoint
	
		add		ebx, [esi+eax]		;find avg of ints above and below midpoint
		mov		eax, ebx			
		mov		ebx, 2
		div		ebx				
		jmp		med

	isOdd:
		mov		ebx, 4			;4 = size of DWORD
		mul		ebx				
		mov		ebx, [esi+eax]		
		mov		eax, ebx
		jmp		med

	med:
		mov		edx, [ebp+12]		;@median text
		call		WriteString

		call		WriteDec			;print median
		mov		edx, [ebp+8]		;@period text
		call		WriteString		
		call		Crlf
	
	pop		ebp

	ret	12

displayMedian ENDP

END main