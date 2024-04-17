# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avaldin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 15:30:58 by avaldin           #+#    #+#              #
#    Updated: 2024/04/16 17:08:41 by avaldin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

		##		COMPILATION			##

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -g3

		##		EXECUTABLE			##

NAME		=	minishell

		##		PATH				##

SRC_PATH	=	src/
OBJ_PATH	=	.obj/

		##		SOURCES_FILES		##

SOURCES		=	ft_calloc.c\
				ft_strlen.c\
				ft_strdup.c\
				ft_lstadd_back.c\
				main.c\
				pars_cmd.c\
				main_parsing.c\
				redirection.c\
				parsing_tools.c\
				data_clear.c\
				signal.c\
				quote_expender.c\
				env_var.c\
				union.c\
				checking.c\
				cmd_split.c\
				red_syntax.c\




HEADER		=	header/minishell.h

		##		OBJECTS				##

OBJS		=	$(SOURCES:%.c=$(OBJ_PATH)%.o)

		##		RULES				##


all			:	$(NAME)
$(OBJS)		:	$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(HEADER) Makefile
	$(CC) $(FLAGS) -c $< -o $@

$(NAME)		:	$(OBJ_PATH) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lreadline

$(OBJ_PATH)	:
	@mkdir -p $(OBJ_PATH)

clean		:
	rm -rf $(OBJ_PATH)

fclean		:	clean
	rm -f $(NAME)

re        :    fclean all
.PHONY    :    all clean fclean re