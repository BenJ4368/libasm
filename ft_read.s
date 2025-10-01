section .text ; "ceci est du code executable"
global ft_read ; "rend ft_read visible depuis d'autres fichiers"
extern __errno_location ; "declare errno en fonction externe"

ft_read:
    mov rax, 0          ; set rax a 0 (0 = syscall de read)
    syscall             ; Effectue l'appel système (les arguments sont places dans rdi rsi et rdx)
    cmp rax, 0          ; Compare la valeur de retour du syscall
    jl .error           ; Si rax < 0, il y a une erreur
    ret

.error:
    neg rax            ; Obtenir la valeur absolue du code d'erreur dans rax
    push rax           ; push rax sur la stack avant l'appel à __errno_location
    call __errno_location wrt ..plt ; récupérer l'adresse de errno dans rax
    pop rdx            ; pop le haut de la stack dans rdx
    mov [rax], rdx     ; mettre le code d'erreur dans errno
    mov rax, -1        ; Retourner -1 pour indiquer une erreur
    ret


; "wrt ..plt" pour que le code soit compatible en mode PIC (Position Independent Code)
; wrt = with respect to (NASM syntaxe spéciale)
; ..plt = indique qu’on veut que l'appel passe par l’entrée de la fonction dans la table des symboles dynamiques (PLT)