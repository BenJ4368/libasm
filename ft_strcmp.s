section .text
global ft_strcmp
extern __errno_location

ft_strcmp:
    ; Vérifier si les pointeurs sont nuls
    test rdi, rdi ; premiere chaine nulle?
    jz .error
    test rsi, rsi ; deuxieme chaine nulle?
    jz .error

    ; Initialiser le résultat
    xor rax, rax

.loop:
    ; Charger les octets (lettres) actuels des deux chaînes
    mov al, [rdi]
    mov dl, [rsi]

    ; Comparer les octets
    cmp al, dl
    jne .not_equal

    test al, al ; Vérifier si l'octet est nul (fin de chaine 1)
    jz .equal

    ; Passer aux octets suivants
    inc rdi
    inc rsi
    jmp .loop

.not_equal:
    ; Calculer la différence
    sub al, dl
    movsx rax, al
    ret

.equal:
    ; Les chaînes sont égales
    xor rax, rax
    ret

.error:
    ; Définir errno à EFAULT (14) pour indiquer un mauvais pointeur
    push rax
    call __errno_location wrt ..plt
    pop rdx
    mov dword [rax], 14 ; EFAULT
    ; set errno (adresse de errno dans rax) a 14 (EFAULT) (dword pour 32 bits)
    mov rax, -1
    ret

; "wrt ..plt" pour que le code soit compatible en mode PIC (Position Independent Code)
; wrt = with respect to (NASM syntaxe spéciale)
; ..plt = indique qu’on veut que l'appel passe par l’entrée de la fonction dans la table des symboles dynamiques (PLT)
