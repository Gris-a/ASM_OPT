extern malloc
extern calloc
extern strcpy

section     .text
global HashTableFind

HashTableFind:
; -----------------------------------------------
    xor eax, eax                                ; eval crc32

    crc32 rax, qword [rsi +  0]
    crc32 rax, qword [rsi +  8]
    crc32 rax, qword [rsi + 16]
    crc32 rax, qword [rsi + 24]

    mov rcx, qword [rdi + 8]
    dec rcx
    and rax, rcx
; -----------------------------------------------
    shl rax, 4                                  ; rax = lst = table->data + hash
    add rax, qword [rdi + 16]

    mov rax, qword [rax +  8]                   ; rax = curr = lst->head->next
    mov rax, qword [rax + 16]
; -----------------------------------------------
    test rax, rax                               ; while curr != NULL
    jz EndListIter

    vmovdqu ymm0, yword [rsi]                   ; load key to ymm0

ListIter:
    mov rdx, qword [rax]                        ; strcmp(key, curr->key)
    vptest ymm0, yword [rdx]
    jnb NextIter

    vzeroupper                                  ; return rax = curr
    ret
NextIter:
    mov rax, qword [rax + 16]                   ; curr = curr->next

    test rax, rax                               ; while curr != NULL
    jnz ListIter
EndListIter:
; -----------------------------------------------
    vzeroupper                                  ; return rax = curr
    ret
; -----------------------------------------------