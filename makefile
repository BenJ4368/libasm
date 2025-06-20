# Variables
NAME = libasm.a
SRC = ft_strdup.s \
	  ft_strcpy.s \
	  ft_strcmp.s \
	  ft_strlen.s \
	  ft_write.s \
	  ft_read.s
OBJ = $(SRC:.s=.o)


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)$(NAME) $(CYAN)created successfully! $(CLR_RMV)✔️"

%.o: %.s
	nasm -f elf64 $< -o $@

tester: $(NAME)
	gcc -fPIE -o tester main.c -L. -lasm

clean:
	@rm -f $(OBJ)
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean: clean
	@rm -f $(NAME) tester
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)✔️"

re: fclean all

.PHONY: all clean fclean re