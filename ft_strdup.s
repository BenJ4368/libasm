section .text
global ft_strdup
extern malloc, ft_strlen, ft_strcpy, __errno_location

ft_strdup:
    ; Vérifier si le pointeur source est nul
    test rdi, rdi
    jz .error_null
    
    ; Sauvegarder le pointeur source sur la pile
    push rdi
    
    ; Calculer la longueur de la chaîne source
    call ft_strlen wrt ..plt
    inc rax          ; Inclure le caractère nul (\0)
    
    ; Allouer de la mémoire
    mov rdi, rax     ; taille à allouer
    push rax         ; sauvegarder la taille sur la pile
    call malloc wrt ..plt
    pop rcx          ; récupérer la taille (pas utilisée mais nettoie la pile)
    
    ; Vérifier l'allocation
    test rax, rax
    jz .error_alloc
    
    ; Préparer l'appel à ft_strcpy
    mov rdi, rax     ; destination = pointeur malloc
    pop rsi          ; source = pointeur original (depuis la pile)
    push rax         ; sauvegarder le pointeur malloc
    
    ; Copier la chaîne
    call ft_strcpy wrt ..plt
    
    ; Récupérer et retourner le pointeur malloc
    pop rax
    ret

.error_alloc:
    ; Nettoyer la pile (enlever le pointeur source sauvé)
    pop rdi
    
    ; Définir errno à ENOMEM
    call __errno_location wrt ..plt
    mov dword [rax], 12    ; ENOMEM
    xor rax, rax
    ret

.error_null:
    ; Définir errno à EINVAL
    call __errno_location wrt ..plt
    mov dword [rax], 22    ; EINVAL
    xor rax, rax
    ret

; "wrt ..plt" pour que le code soit compatible en mode PIC (Position Independent Code)
; wrt = with respect to (NASM syntaxe spéciale)
; ..plt = indique qu’on veut que l'appel passe par l’entrée de la fonction dans la table des symboles dynamiques (PLT)
