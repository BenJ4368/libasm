section .text
global ft_write
extern __errno_location

ft_write:
    ; Input: rdi = fd, rsi = buf, rdx = count
    ; Output: rax = number of bytes written or -1 on error

    ; Appel système pour write
    mov rax, 1      ; Numéro de l'appel système pour write
    syscall         ; Effectue l'appel système

    ; Vérifier si l'appel a échoué
    cmp rax, 0
    jl .error       ; Si rax < 0, il y a une erreur

    ; Retourner le nombre d'octets écrits
    ret

.error:
    ; Sauvegarder le code d'erreur
    neg rax         ; Obtenir la valeur absolue du code d'erreur
    push rax        ; Sauvegarder rax sur la pile

    ; Appeler __errno_location pour obtenir l'adresse de errno
    call __errno_location wrt ..plt

    ; Restaurer le code d'erreur et définir errno
    pop rdx         ; Restaurer le code d'erreur dans rdx
    mov [rax], edx  ; Définir errno au code d'erreur

    ; Retourner -1 pour indiquer une erreur
    mov rax, -1
    ret

; "wrt ..plt" pour que le code soit compatible en mode PIC (Position Independent Code)
; wrt = with respect to (NASM syntaxe spéciale)
; ..plt = indique qu’on veut que l'appel passe par l’entrée de la fonction dans la table des symboles dynamiques (PLT)
