NAME = pipex
NAME_BONUS = pipex_bonus
SRC_DIR = srcs
SRC_DIR_BONUS = srcs_bonus
OBJ_DIR = objs
OBJ_DIR_BONUS = objs_bonus
SRCS = main.c \
	   pipex.c \
	   pipex_utils.c \
	   error.c 
SRCS_BONUS = main_bonus.c \
	   pipex_bonus.c \
	   pipex_utils_bonus.c \
	   prompt_bonus.c \
	   filename_bonus.c \
	   error_bonus.c
SRCS := $(SRCS:%=$(SRC_DIR)/%)
SRCS_BONUS := $(SRCS_BONUS:%=$(SRC_DIR_BONUS)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS := $(SRCS_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)
DEPS := $(OBJS:.o=.d)
DEPS := $(OBJS_BONUS:.o=.d)
CC = cc
C_FLAGS = -Wall -Wextra -Werror -MMD
INC_LIBFT = ./libft/libft.a
DIR_DUP     = mkdir -p $(@D)

all : $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	make -j -C ./libft
	$(CC) $(C_FLAGS) $(OBJS) $(INC_LIBFT) -o $@

bonus : $(NAME_BONUS)

$(OBJ_DIR_BONUS)/%.o:$(SRC_DIR_BONUS)/%.c
	$(DIR_DUP)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME_BONUS) : $(OBJS_BONUS)
	make -j -C ./libft
	$(CC) $(C_FLAGS) $(OBJS_BONUS) $(INC_LIBFT) -o $@

-include $(DEPS)

clean :
	make -j clean -C ./libft
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	rm -f $(DEPS)
	rm -f $(DEPS_BONUS)
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_BONUS)

fclean : clean
	make -j fclean -C ./libft
	rm -f pipex
	rm -f pipex_bonus

re : fclean
	make all

.PHONY : all clean fclean re