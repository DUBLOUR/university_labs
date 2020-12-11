; comment has implemented
; floats always must contain decimal dot
PUSH 2.5    ; a
PUSH 3.1415 ; b
CPY 1     ; =a
CPY 1     ; =b
; stack = [a, b, a, b]
SUB       ; = b-a
; [a, b, b-a]
CPY 2     ; =a
CPY 2     ; =b
; [a, b, b-a, a, b]
ADD
; [a, b, b-a, a+b]
DIV       
; [a, b, (a+b)/(b-a)]
SWP
POP
SWP
POP
; [(a+b)/(b-a)]
; 8.0/2.0 = [4.0]

