NM=ft_nm
OTOOL=ft_otool
CC= gcc
CFLAGS= -Wall -Werror -Wextra
SRC_NAME= main.c macho.c magic.c binary.c command.c symtab.c\
          type.c section.c display.c fat.c lib.c otool.c
SRC_PATH= ./sources/
INC_PATH= ./includes/
LIB_NAME= libft.a
LIB_ID= ft
LIB_PATH= ./libft/
LIB_INC= ./libft/includes/
OBJ_NAME= $(SRC_NAME:.c=.o)
NM_OBJ_PATH= ./nm_obj/
OTOOL_OBJ_PATH= ./otool_obj/
DEFINE_NM= TARGET=NM
DEFINE_OTOOL= TARGET=OTOOL
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
NM_OBJ= $(addprefix $(NM_OBJ_PATH), $(OBJ_NAME))
OTOOL_OBJ= $(addprefix $(OTOOL_OBJ_PATH), $(OBJ_NAME))
LIB= $(addprefix $(LIB_PATH), $(LIB_NAME))

.PHONY: all
all:
	$(MAKE) nm
	$(MAKE) otool

.PHONY: define_otool
define_otool:
	@echo DEFINE OTOOL
	$(eval DEFINE_TARGET := $(DEFINE_OTOOL))
	$(eval OBJ_PATH := $(OTOOL_OBJ_PATH))
	$(eval OBJ := $(OTOOL_OBJ))

.PHONY: define_nm
define_nm:
	@echo DEFINE NM
	$(eval DEFINE_TARGET := $(DEFINE_NM))
	$(eval OBJ_PATH := $(NM_OBJ_PATH))
	$(eval OBJ := $(NM_OBJ))

.PHONY: nm
nm: define_nm $(NM_OBJ) $(NM)

.PHONY: otool
otool: define_otool $(OTOOL)

define compile
	@$(CC) $(CFLAGS) -o $(1) -L$(LIB_PATH) -I$(INC_PATH) -l$(LIB_ID) $(OBJ) 
	@printf "\033[2K[ \033[31mcompiling\033[0m ] $(2) \r"
	@printf "\n$(1) successfully created\n"
endef

$(OTOOL): $(OTOOL_OBJ) $(LIB)
	$(call compile,$@,otool)
$(NM): $(NM_OBJ) $(LIB)
	$(call compile,$@,nm)


$(LIB):
	@make re -C $(LIB_PATH)

$(NM_OBJ_PATH)%.o $(OTOOL_OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	@$(CC) -I$(INC_PATH) -I$(LIB_INC) $(CFLAGS) -D $(DEFINE_TARGET) -o $@ -c $<
	@printf " \033[2K[ \033[31mcompiling\033[0m ] $< \r"

.PHONY: clean
clean:
	@rm -f $(NM_OBJ) $(OTOOL_OBJ)
	@printf "[ \033[36mdelete\033[0m ] objects\n"
	@rm -rf $(NM_OBJ_PATH) $(OTOOL_OBJ_PATH)
	@make $@ -C $(LIB_PATH)

.PHONY: fclean
fclean: clean
	@printf "[ \033[36mdelete\033[0m ] $(NM) and $(OTOOL)\n"
	@rm -f $(NM) $(OTOOL)
	@make $@ -C $(LIB_PATH)

.PHONY: re
re: fclean all
