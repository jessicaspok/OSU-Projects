TITLE Integer Accumulator     (Program03_Spokoyny.asm)

; Author: Jessica Spokoyny
; Course / Project ID : CS 271 Program 3                 Date: 02/03/16
; Description:  This program will introduce the programmer, get the user's name, prompt the user to enter numbers
;				until they enter a number outside of the bounds, and display some messages about their numbers.

INCLUDE Irvine32.inc

LOWER_LIMIT = -100
UPPER_LIMIT = -1

.data
userName			BYTE		33 DUP(0)
userNum			SDWORD	?

intro_1			BYTE		"		CS 271 Program 3 - Integer Accumulator	  		        ", 0	   
intro_2			BYTE		"			  By Jessica Spokoyny				        ", 0

prompt_1			BYTE		"What's your name? ", 0
greeting			BYTE		"Hello, ", 0

instruct_1		BYTE		"Please enter numbers in [-100, -1].					       ", 0
instruct_2		BYTE		"Enter a non-negative number when you are finished to see results.	       ", 0

prompt_2			BYTE		"Enter number ", 0
prompt_3			BYTE		"You entered ", 0
prompt_4			BYTE		" valid numbers.", 0

result_sum		BYTE		"The sum of your valid numbers is ", 0
result_round_avg	BYTE		"The rounded average is ", 0

colon			BYTE		": ", 0
period			BYTE		".", 0
exclam			BYTE		"! ", 0

invalid_1			BYTE		"Out of range. Enter a number in [-100, -1] or any non-negative number to finish.", 0
invalid_2			BYTE		"No valid numbers were entered.. No results to display..", 0

num_count			SDWORD 	?
sum_count			SDWORD	?
average			SDWORD	?

farewell_1		BYTE		"Thank you for playing Integer Accumulator!", 0
farewell_2		BYTE 	"It's been a pleasure to meet you, ", 0

extra_1			BYTE		"** EC1: Lines are numbered during user input.                                  ", 0

extra_2			BYTE		"** EC2: Average is displayed as a floating-point number,		       ", 0
extra_2a			BYTE		"	    rounded to the nearest .001.				       ", 0

extra_3			BYTE		"** EC3: Text color and background color changed to superbowl colors!           ", 0

result_float_avg	BYTE		"The float average is ", 0
thousand			DWORD	1000
remainder			DWORD	?

.code
main PROC

;Change text and background colors
 mov  eax,lightGreen+(cyan*7)
      call SetTextColor

;Introduce programmer
	mov		edx, OFFSET intro_1
	call		WriteString
	call		CrLf

	mov		edx, OFFSET intro_2
	call		WriteString
	call		CrLf
	call		CrLf

; Extra credit
	mov		edx, OFFSET extra_1
	call		WriteString
	call		CrLf
	
	mov		edx, OFFSET extra_2
	call		WriteString
	call		CrLf
	mov		edx, OFFSET extra_2a
	call		WriteString
	call		CrLf

	mov		edx, OFFSET extra_3
	call		WriteString
	call		CrLf
	call		CrLf

;Get user name and display greeting
	mov		edx, OFFSET prompt_1
	call		WriteString
	
	mov		edx, OFFSET userName
	mov		ecx, 32
	call		ReadString
	
	mov		edx, OFFSET greeting
	call		WriteString
	
	mov		edx, OFFSET userName
	call		WriteString
	
	mov		edx, OFFSET exclam
	call		WriteString
	call		CrLf
	call		CrLf

;Display Instructions
	mov 		edx, OFFSET instruct_1
	call		WriteString
	call		CrLf
	
	mov 		edx, OFFSET instruct_2
	call		WriteString
	call		CrLf
	call		CrLf

;Get numbers
	mov		num_count, 1
GetNum:
	mov		edx, OFFSET prompt_2
	call		WriteString
	
	mov		eax, num_count
	call		WriteDec
	
	mov		edx, OFFSET colon
	call		WriteString
	call		ReadInt
	
	cmp		eax, LOWER_LIMIT
	jl		OutOfRange
	
	cmp		eax, UPPER_LIMIT
	jg		TimeToExit
	
GoodNum:
	inc		num_count						;increment number count
	add		sum_count, eax					;add userNum to running sum
	dec		num_count			
	call		GetAverage
	
OutOfRange:
	mov		edx, OFFSET invalid_1
	call		WriteString
	call		CrLf
	jmp		GetNum
	
GetAverage:
	mov		eax, sum_count
	cdq									;Convert DWORD to QWORD
	
	mov		ebx, num_count
	idiv		ebx							;Signed divide (running sum)/(number of user inputs)
	mov		average, eax
	
	sub		edx, 1						;Convert negative remainder to positive
	not		edx
	
	mov		eax, thousand					;Multiply by 1000 to round to 3 places
	mul		edx
	
	div		ebx							;Long division
	mov		remainder, eax

	inc		num_count						;Iterate
	jmp		GetNum			
	
TimeToExit:

;Check count of valid numbers 
	cmp		num_count, 1					;If none, exit
	je		NoNums			

;Show Results	
	call		CrLf				
	mov		edx, OFFSET prompt_3			;How many numbers were entered
	call		WriteString
	
	dec		num_count			
	mov		eax, num_count
	call		WriteDec

	mov		edx, OFFSET prompt_4			;Sum result
	call		WriteString
	call		CrLf
	call		CrLf
	
	mov		edx, OFFSET result_sum
	call		WriteString
	
	mov		eax, sum_count		
	call		WriteInt
	
	mov		edx, OFFSET period
	call		WriteString
	call		CrLf
	
	mov		edx, OFFSET result_round_avg		;Rounded average result
	call		WriteString
	
	mov		eax, average		
	call		WriteInt

	mov		edx, OFFSET period
	call		WriteString
	call		CrLf

	mov		edx, OFFSET result_float_avg		;Float average result
	call		WriteString

	
	mov		eax, average		
	call		WriteInt
	mov		edx, OFFSET period
	call		WriteString
	mov		eax, remainder		
	call		WriteDec
	
	mov		edx, OFFSET period
	call		WriteString
	call		CrLf
	call		CrLf
	jmp		Goodbye

NoNums:
	mov		edx, OFFSET invalid_2			;Nothing to calculate
	call		WriteString
	call		CrLf
	call		CrLf
	
Goodbye:	
	mov		edx, OFFSET farewell_1
	call		WriteString
	call		CrLf
	
	mov		edx, OFFSET farewell_2
	call		WriteString
	
	mov		edx, OFFSET userName
	call		WriteString

	mov		edx, OFFSET exclam
	call		WriteString
	call		CrLf
	call		CrLf

exit
	
main ENDP
END main