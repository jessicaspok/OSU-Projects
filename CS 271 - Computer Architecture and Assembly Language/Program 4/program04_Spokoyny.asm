TITLE Program 4     (program04_Spokoyny.asm)

; Author: Jessica Spokoyny
; Course / Project ID : CS 271 Program 4                 Date: 02/10/16
; Description:  This program will calculate composite numbers. The user  
;	will specify how many composites (s)he would like to see and the  
;	program will display that many.

INCLUDE Irvine32.inc

LOWER_LIMIT = 1							
UPPER_LIMIT = 1000							
MAX_PER_PAGE = 200
MAX_PER_LINE = 10

.data
intro_1		BYTE		"		CS 271 Program 4 - Composite Numbers", 0	   
intro_2		BYTE		"			  By Jessica Spokoyny", 0

extra_1		BYTE		"**EC 1: Program displays the numbers in aligned columns.", 0
extra_2		BYTE		"**EC 2: Program displays more composites (up to 1,000). ", 0
extra_3		BYTE		"	and shows the results one page at a time (with 200 per page)", 0

instruct_1	BYTE		"Enter the number of composite numbers you would like to see. ", 0
instruct_2	BYTE		"I will accept orders for up to 1,000 composites.", 0

prompt_1		BYTE		"Enter the number of composites to display [1 .. 1000]: ", 0
			
notInRange	BYTE		"Out of range. Try again.",0

goodbye		BYTE		"Results certified by Jessica Spokoyny. Bye bye!", 0
continue		BYTE		"Press any key to continue...", 0

numComposites	DWORD	?					;Number of composites to display
composite		DWORD	4					;First composite number is 4
compbool		DWORD	?					;Bool variable for checking if number is composite
total		DWORD	0					;Total number of composites printed
remainder		DWORD	?
tabs			BYTE		9, 0					;ASCII tab

.code
main PROC
	call introduction			;display introduction
	call getUserData			;ask user for number of composites to print
	call showComposites			;calculate and show composite numbers
	call farewell				;display farewell message
	exit						;exit to operating system
main ENDP

;------------------------------------------------------------------------------
; introduction
;
; Displays the program's introduction, extra credit, and instructions
;
; Receives:		 none
; Returns:		 none
; Preconditions:	 none
; Registers changed: EDX
;------------------------------------------------------------------------------
introduction PROC

	mov		edx, OFFSET intro_1		;Display introduction
	call		WriteString
	call		CrLf	
	mov		edx, OFFSET intro_2	
	call		WriteString
	call		CrLf					
	call		CrLf					

	mov		edx, OFFSET extra_1		;Display extra credit descriptions
	call		WriteString
	call		CrLf	

	mov		edx, OFFSET extra_2		
	call		WriteString
	call		CrLf	

	mov		edx, OFFSET extra_3		
	call		WriteString
	call		CrLf	
	call		CrLf

	mov		edx, OFFSET instruct_1	;Display instructions
	call		WriteString
	call		CrLf					
	mov		edx, OFFSET instruct_2
	call		WriteString
	call		CrLf					
	call		CrLf		
	
	ret			

introduction ENDP

;------------------------------------------------------------------------------
; getUserData
;
; Gets the number of composites to print from the user
;
; Receives:		 none
; Returns:		 numComposites = number of composites to print
; Preconditions:	 none
; Registers changed: EAX, EDX
;------------------------------------------------------------------------------
getUserData PROC

	mov		edx,OFFSET prompt_1
	call		WriteString
	call		ReadInt
	
	mov		numComposites,eax
	call		CrLf
	call		validate			;Validates user entry
	ret

getUserData ENDP

;------------------------------------------------------------------------------
; validate
;
; Verifies that 1 <= n <= UPPER_LIMIT where n is the user-entered number.
;
; Receives:		 numComposites = number of composites to print
; Returns:		 none
; Preconditions:	 a value has been entered
; Registers changed: EAX, EDX
;------------------------------------------------------------------------------
validate PROC
	mov		eax, numComposites
	
	cmp		eax,LOWER_LIMIT		;If number < 1		
	jl		error				
	cmp		eax,UPPER_LIMIT		;If number > UPPER_LIMIT
	jg		error				
	ret

error:
	mov		edx,OFFSET notInRange	;Show error and prompt for new number
	call		WriteString
	call		CrLf
	call		getUserData
	
validate ENDP

;------------------------------------------------------------------------------
; showComposites
;
; Prints user entered quantity of composite numbers. 
;
; Receives:		 validated numComposites
; Returns:		 none
; Preconditions:	 a value has been entered and verified
; Registers changed: EAX, EBX, ECX, EDX
;------------------------------------------------------------------------------
showComposites PROC

	call		CrLf
	mov		ecx, numComposites		;Set counter to user-entered value
	
printLoop:
	mov		compbool, 0			;Set bool variable to 0
	call		isComposite			;Check if number is composite
		
	cmp		compbool, 1			;If it is composite, print it
	je		printValue
		
	inc		composite				;Otherwise, move on to test next number
	
printValue:
	inc		total				;Increment number of composites printed
	
	mov		eax, 0				
	mov		eax, composite			;Set EAX = the number to be tested
	call		WriteDec
	mov		edx, OFFSET tabs		;Leave space between numbers
	call		WriteString
		
	;Check if number needs to go on the next line
	mov		eax, 0				;Clear registers
	mov		ebx, 0
	mov		edx, 0				
	
	mov		eax, total			;Divide numbers printed / 10
	mov		ebx, MAX_PER_LINE
	div		ebx
	mov		remainder, edx
		
	cmp		remainder, 0			;If remainder != 0, stay on same line
	jne		noNewLine
	call		newPage				;Else, check if new line should be on current or new page
	call		CrLf
		
noNewLine:
	inc		composite				;Increment to find next composite
	loop		printLoop
	ret

showComposites ENDP

;------------------------------------------------------------------------------
; isComposite
;
; Checks if each number is composite or prime. 
;
; Receives:		 composite = number to be tested
; Returns:		 compBool set to either 1 (meaning composite) or 0 (prime)
; Preconditions:	 none
; Registers changed: EAX, EBX, EDX
;------------------------------------------------------------------------------
isComposite PROC
	mov		edx, 0				;Clear edx
	mov		eax, composite			
	mov		ebx, 2				;First try dividing by 2
	div		ebx					
	cmp		edx, 0				
	je		setComposite			;If remainder = 0, it's even, so it's composite
	inc		ebx					;If remainder !=0, set the divisor to the next number (3)
	
divisionLoop:
	mov		edx, 0				;Clear edx
	mov		eax, 0				;Clear eax
		
	cmp		ebx, composite			;If the number being tested = divisor, then it's prime
	je		setNotComposite
		
	mov		eax, composite			;If not, try dividing by divisor
	div		ebx	
	cmp		edx, 0
	je		setComposite			;If remainder = 0 then it's composite
	
	add		ebx, 2				;Increment divisor by 2 (even numbers can be skipped)
	jmp		divisionLoop
	
setComposite:
	mov		compbool, 1
	ret
	
setNotComposite:
	mov		compbool, 0
	ret
		
isComposite ENDP

;------------------------------------------------------------------------------
; newPage
;
; Checks whether the composite to be printed can be on the same page, or if it
; should be moved to the next page
;
; Receives:		 total = number of composites that have been printed
; Returns:		 none
; Preconditions:	 none
; Registers changed: EAX, EBX, EDX
;------------------------------------------------------------------------------

newPage PROC
	mov		eax, 0				;Clear registers
	mov		ebx, 0
	mov		edx, 0
	
	mov		eax, total			;Set eax = number of composites printed
	mov		ebx, MAX_PER_PAGE		;Set ebx = max number printed per page
	div		ebx					
	cmp		edx, 0				;If max_per_page is not a factor of total, 
	jne		Return				;Keep printing on the same page
	
	call		CrLf					
	mov		edx, 0
	mov		edx, OFFSET continue	;Prompt user to continue
	call		WriteString		
	call		ReadString			
	call		Clrscr				;Clear screen
	
Return:
	ret
newPage ENDP

;------------------------------------------------------------------------------
; farewell
;
; Prints a farewell message once all numbers have been printed
;
; Receives:		 none
; Returns:		 none
; Preconditions:	 none
; Registers changed: EDX
;------------------------------------------------------------------------------
farewell PROC
	
	call		Crlf
	call		Crlf
	mov		edx,OFFSET goodbye
	call		WriteString
	call		Crlf
	call		Crlf
	ret

farewell ENDP


END main