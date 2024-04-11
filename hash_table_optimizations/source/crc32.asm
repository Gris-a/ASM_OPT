extern strlen

section     .text
global CRC32

; ===============================================
; entry:
;       rdi     key addr
;       rsi     mod
; exit:
;       rax     crc32 hash value
; ===============================================
CRC32:
; -----------------------------------------------
    push rdi
    push rsi
; -----------------------------------------------
    call strlen                                 ; get key len
; -----------------------------------------------
    pop rsi
    pop rdi
; -----------------------------------------------
    mov rcx, rax
    and rcx, 7
    shr rax, 3
; -----------------------------------------------
    lea rdx, SwitchTable[rcx * 8]
    mov rcx, rax
    xor eax, eax
    jmp [rdx]                                   ; jump to remainder of key_len / 8
; -----------------------------------------------
Remainder1:
    mov dl, [rdi]
    crc32 eax, dl

    add rdi, 1
    jmp Remainder0
; -----------------------------------------------
Remainder2:
    mov dx, [rdi]
    crc32 eax, dx

    add rdi, 2
    jmp Remainder0
; -----------------------------------------------
Remainder3:
    mov dl, [rdi]
    crc32 eax, dl

    mov dx, [rdi + 1]
    crc32 eax, dx

    add rdi, 3
    jmp Remainder0
; -----------------------------------------------
Remainder4:
    mov edx, [rdi]
    crc32 eax, edx

    add rdi, 4
    jmp Remainder0
; -----------------------------------------------
Remainder5:
    mov dl, [rdi]
    crc32 eax, dl

    mov edx, [rdi + 1]
    crc32 eax, edx

    add rdi, 5
    jmp Remainder0
; -----------------------------------------------
Remainder6:
    mov dx, [rdi]
    crc32 eax, dx

    mov edx, [rdi + 2]
    crc32 eax, edx

    add rdi, 6
    jmp Remainder0
; -----------------------------------------------
Remainder7:
    mov dl, [rdi]
    crc32 eax, dl

    mov dx, [rdi + 1]
    crc32 eax, dx

    mov edx, [rdi + 3]
    crc32 eax, edx

    add rdi, 7
; -----------------------------------------------
Remainder0:
    dec rsi
; -----------------------------------------------
    test rcx, rcx
    jz EndNext
Next:                                           ; count crc by words of 8-bytes size
    mov rdx, [rdi]
    crc32 rax, rdx

    add rdi, 8
    loop Next
EndNext:
; -----------------------------------------------
    and rax, rsi
    ret
; -----------------------------------------------

section     .rodata
align 8

SwitchTable:
    dq  Remainder0
    dq  Remainder1
    dq  Remainder2
    dq  Remainder3
    dq  Remainder4
    dq  Remainder5
    dq  Remainder6
    dq  Remainder7