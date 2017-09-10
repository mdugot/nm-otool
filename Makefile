NAME= ft_nm
CC= gcc
CFLAGS= -Wall -Werror -Wextra
SRC_NAME= main.c macho.c magic.c binary.c command.c symtab.c type.c
SRC_PATH= ./sources/
INC_PATH= ./includes/
LIB_NAME= libft.a
LIB_ID= ft
LIB_PATH= ./libft/
LIB_INC= ./libft/includes/
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB= $(addprefix $(LIB_PATH), $(LIB_NAME))

.PHONY: all
all: $(NAME) end
	
end:
	@printf "\n$(NAME) successfully created\n"
	@printf "Run with \033[32m./$(NAME)\033[0m\n"

$(NAME): $(LIB) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) -L$(LIB_PATH) -I$(INC_PATH) -l$(LIB_ID) -ltermcap $(OBJ) 
	@printf "\033[2K[ \033[31mcompiling\033[0m ] $< \r"

$(LIB):
	@make re -C $(LIB_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	@$(CC) -I$(INC_PATH) -I$(LIB_INC) $(CFLAGS) -o $@ -c $<
	@printf " \033[2K[ \033[31mcompiling\033[0m ] $< \r"

.PHONY: clean
clean:
	@rm -f $(OBJ)
	@printf "[ \033[36mdelete\033[0m ] objects from $(NAME)\n"
	@rm -rf $(OBJ_PATH)
	@make $@ -C $(LIB_PATH)

.PHONY: fclean
fclean: clean
	@printf "[ \033[36mdelete\033[0m ] $(NAME)\n"
	@rm -f $(NAME)
	@make $@ -C $(LIB_PATH)

.PHONY: re
re: fclean all
