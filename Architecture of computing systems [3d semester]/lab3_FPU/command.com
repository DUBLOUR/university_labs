; comment has implemented
PUSH 5
PUSH 3
CPY 1     ; =a
CPY 1     ; =b
SWP
; stack = [a, b, a, b]
SUB       ; =a-b
; [a, b, a-b]
CPY 2     ; =a
CPY 2     ; =b
; [a, b, a-b, b, a]
ADD
; [a, b, a-b, a+b]
DIV       
; [a, b, (a+b)/(a-b)]
SWP
POP
SWP
POP
; [(a+b)/(a-b)]



; comment has implemented
PUSH a
PUSH b
SUB     ; remove last 2 and
        ; add his substraction
PUSH a
PUSH b
ADD     ; add his 
DIV

# push a
# push b
# sub
# push a
# push b
# add
# div


; set accum value as 5
MOV R2
; copy accum to R2

OR 9    ; acc |= 9 = 13
MOV R0  ; R0 = 13
MOV -34 ; acc = -34
OR R2   ; acc |= 13
MOV R10 ; invalid, ignore
MOV R1 