; comment has implemented
MOV 5 
; set accum value as 5
MOV R2
; copy accum to R2

OR 9    ; acc |= 9 = 13
MOV R0  ; R0 = 13
MOV -34 ; acc = -34
OR R2   ; acc |= 13
MOV R1 