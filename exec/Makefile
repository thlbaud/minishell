# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 10:53:51 by tmouche           #+#    #+#              #
#    Updated: 2024/05/15 00:01:48 by tmouche          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HDRS	:= execution.h parsing.h structure.h

SRCS	:=	main.c main_free.c\
			pars_checking.c pars_cmd_split.c pars_cmd.c pars_data_clear.c pars_env_var.c pars_ft_lstadd_back.c pars_init.c pars_quote_expender.c pars_red_syntax.c pars_redirect.c \
			pars_tools.c pars_union.c \
			exec_checker_path.c exec_cmd.c exec_utils.c exec_utils_2.c\
			exec_buildin.c exec_buildin_echo.c exec_buildin_pwd.c exec_buildin_env.c exec_buildin_unset.c exec_buildin_export.c exec_buildin_export_utils.c exec_buildin_export_history.c exec_buildin_exit.c exec_buildin_cd.c exec_buildin_cd_utils.c\
			exec_buildin_history.c exec_buildin_history_utils.c exec_buildin_utils.c exec_free.c exec_open.c exec_utils_error.c\
			signal.c \

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
	$(CC) $(CFLAGS) $(OBJS) -I$(INC_D)libft -L$(INC_D)libft -lft -o $(NAME) -lreadline


$(OBJS_D)%.o: $(SRCS_D)%.c $(HDRS:%=$(HDRS_D)%) $(INC_D)libft Makefile
	$(CC) $(CFLAGS) -I$(INC_D)libft -c $< -o $@

$(OBJS_D):
	@mkdir -p $(OBJS_D)

libft:
	$(MAKE) -C $(INC_D)libft
	$(MAKE) bonus -C $(INC_D)libft

clean:
	$(RM) -r $(OBJS_D)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(INC_D)libft fclean

re: fclean all

.PHONY: all clean fclean re libft
