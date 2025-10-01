section .text
global ft_strlen

; Fonction ft_strlen
ft_strlen:
    xor rax, rax    ; Initialise le compteur à zéro
    ; rax = valeur de retour

.loop:
    cmp byte [rdi + rax], 0  ; Compare le byte actuel à zéro
    ; rdi = premier argument passé (adresse de la chaîne)
    je .end                  ; Si c'est zéro, fin de la chaîne
    inc rax                  ; Sinon, incrémente le compteur
    jmp .loop                ; Répète la boucle

.end:
    ret                       ; Retourne rax