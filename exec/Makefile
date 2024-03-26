# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 10:53:51 by tmouche           #+#    #+#              #
#    Updated: 2024/03/26 15:28:22 by tmouche          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HDRS	:= execution.h parsing.h structure.h

SRCS	:=	main.c pars_cmd.c pars_data_clear.c pars_ft_lstadd_back.c pars_init.c pars_redirect.c pars_tools.c exec_checker_path.c exec_cmd.c exec_utils.c exec_alias.c

SRCS_D	:= SRCS/
HDRS_D	:= HDRS/
OBJS_D	:= OBJS/
INC_D	:= include/

CFLAGS	:= -Wall -Wextra -Werror -g
CC		:= cc
AR		:= ar rcs
RM		:= rm -rf

NAME	:= minishell	
OBJS	:= $(SRCS:%.c=$(OBJS_D)%.o)

all: libft $(NAME) 

$(NAME): $(OBJS_D) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -I$(INC_D)libft -L$(INC_D)libft -lft -o $(NAME)


$(OBJS_D)%.o: $(SRCS_D)%.c $(HDRS:%=$(HDRS_D)%) $(INC_D)libft Makefile
	$(CC) $(CFLAGS) -I$(INC_D)libft -c $< -o $@

$(OBJS_D):
	@mkdir -p $(OBJS_D)

libft:
	$(MAKE) -C $(INC_D)libft

clean:
	$(RM) -r $(OBJS_D)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(INC_D)libft fclean

re: fclean all

.PHONY: all clean fclean re libft
