# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MakeERROR_BONUS                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galambey <galambey@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 11:40:45 by galambey          #+#    #+#              #
#    Updated: 2023/08/31 16:57:42 by galambey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= pipex
NAME_BONUS 	= pipex_bonus
CC 			= cc
C_FLAGS 	= -Wall -Wextra -Werror -MMD
INC_LIBFT 	= ./libft/megalibft.a

################################### SOURCES ###################################

ERROR_DIR         	=   error/
ERROR_SRCS        	=   error.c

PIPEX_DIR       	=   pipex/
PIPEX_SRCS      	=   main.c \
	   					pipex.c

UTILS_DIR        	=   utils/
UTILS_SRCS       	=   pipex_utils.c

ERROR_BONUS_DIR     =   error/
ERROR_BONUS_SRCS    =   error_bonus.c

HERE_DOC_DIR       	=   here_doc/
HERE_DOC_SRCS      	=   prompt_bonus.c \
	   					filename_bonus.c

PIPEX_BONUS_DIR     =   pipex/
PIPEX_BONUS_SRCS    =   main_bonus.c \
	   					pipex_bonus.c

UTILS_BONUS_DIR     =   utils/
UTILS_BONUS_SRCS    =   pipex_utils_bonus.c

############################# HANDLE DIRECTORIES ##############################

SRCS_DIR        	=     srcs/
SRCS_BONUS_DIR  	=     srcs_bonus/

SRCS				=	$(addprefix $(ERROR_DIR), $(ERROR_SRCS)) \
						$(addprefix $(PIPEX_DIR), $(PIPEX_SRCS)) \
						$(addprefix $(UTILS_DIR), $(UTILS_SRCS))

SRCS_BONUS			=	$(addprefix $(ERROR_BONUS_DIR), $(ERROR_BONUS_SRCS)) \
						$(addprefix $(HERE_DOC_DIR), $(HERE_DOC_SRCS)) \
						$(addprefix $(PIPEX_BONUS_DIR), $(PIPEX_BONUS_SRCS)) \
						$(addprefix $(UTILS_BONUS_DIR), $(UTILS_BONUS_SRCS)) \

OBJS_DIR 			= 	objs/
OBJS_BONUS_DIR 		= 	objs_bonus/

OBJS_NAMES 			= 	$(SRCS:.c=.o)
OBJS_BONUS_NAMES 	= 	$(SRCS_BONUS:.c=.o)

OBJS_FOLDER			=	$(addprefix $(OBJS_DIR), $(ERROR_DIR) \
                        $(PIPEX_DIR) \
                        $(UTILS_DIR))

OBJS_BONUS_FOLDER	=	$(addprefix $(OBJS_BONUS_DIR), $(ERROR_BONUS_DIR) \
                        $(HERE_DOC_DIR) \
                        $(PIPEX_BONUS_DIR) \
                        $(UTILS_BONUS_DIR))

OBJS			= $(addprefix $(OBJS_DIR), $(OBJS_NAMES))
OBJS_BONUS		= $(addprefix $(OBJS_BONUS_DIR), $(OBJS_BONUS_NAMES))

DEPS := $(OBJS:.o=.d)
DEPS := $(OBJS_BONUS:.o=.d)

#################################### RULES ####################################

all : $(NAME)

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	mkdir -p $(@D)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	make -j -C ./libft
	$(CC) $(C_FLAGS) $(OBJS) $(INC_LIBFT) -o $@

bonus : $(NAME_BONUS)

$(OBJS_BONUS_DIR)%.o:$(SRCS_BONUS_DIR)%.c
	mkdir -p $(@D)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME_BONUS) : $(OBJS_BONUS)
	make -j -C ./libft
	$(CC) $(C_FLAGS) $(OBJS_BONUS) $(INC_LIBFT) -o $@

-include $(DEPS)

clean :
	make -j clean -C ./libft
	rm -rf $(OBJS_DIR)
	rm -rf $(OBJS_BONUS_DIR)

fclean : clean
	make -j fclean -C ./libft
	rm -f pipex
	rm -f pipex_bonus

re : fclean
	make all

.PHONY : all bonus clean fclean re