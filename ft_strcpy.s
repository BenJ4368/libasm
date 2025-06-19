section .text
global ft_strcpy
extern __errno_location

ft_strcpy:
    ; Vérifier si le pointeur source est nul
    test rsi, rsi
    jz .error
    
    ; Vérifier si le pointeur destination est nul
    test rdi, rdi
    jz .error
    
    ; Sauvegarder le pointeur de destination original
    push rdi
    
    ; Copier les caractères de la source vers la destination
.loop:
    mov al, [rsi]     ; Charger le caractère de la source
    mov [rdi], al     ; Copier le caractère dans la destination
    test al, al       ; Vérifier si c'est le caractère nul
    jz .done          ; Si c'est le caractère nul, on a fini
    inc rsi           ; Avancer dans la source
    inc rdi           ; Avancer dans la destination
    jmp .loop

.done:
    ; Restaurer le pointeur de destination original dans rax
    pop rax
    ret

.error:
    ; Appeler __errno_location pour obtenir l'adresse d'errno
    call __errno_location wrt ..plt
    
    ; Définir errno à EFAULT (14)
    mov dword [rax], 14
    
    ; Retourner NULL
    xor rax, rax
    ret

; "wrt ..plt" pour que le code soit compatible en mode PIC (Position Independent Code)
; wrt = with respect to (NASM syntaxe spéciale)
; ..plt = indique qu’on veut que l'appel passe par l’entrée de la fonction dans la table des symboles dynamiques (PLT)
