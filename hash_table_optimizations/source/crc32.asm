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
    dec rsi
    call strlen
; -----------------------------------------------
    mov rcx, rax
    and rcx, 3
    shr rax, 2
; -----------------------------------------------
    xor edx, edx
; -----------------------------------------------
    test rcx, rcx
    jz EndNext1
Next1:
    shl rdx, 8
    mov dl, [rdi]
    inc rdi
    loop Next1
EndNext1:
; -----------------------------------------------
    mov rcx, rax
    xor eax, eax
; -----------------------------------------------
    test rcx, rcx
    jz EndNext2
Next2:
    crc32 eax, edx
    mov rdx, [rdi]
    add rdi, 4
    loop Next2
EndNext2:
    crc32 eax, edx
; -----------------------------------------------
    and rax, rsi
    ret
; -----------------------------------------------