/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:35:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/03 20:44:58 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../HDRS/parsing.h"
#include "../HDRS/structure.h"
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline int	_how_many_cmd(t_section *cmd)
{
	t_section	*temp;
	int			counter;

	temp = cmd;
	counter = 0;
	while (temp)
	{
		temp = temp->next;
		++counter;
	}
	return (counter);
}

int	main(int argc, char **argv, char **env)
{
	t_data		args;
	char		*line;
	int			count;
	int			i;

	(void)argc;
	(void)argv;
	args.env = _map_cpy(env);
	while (42)
	{
		line = readline(ft_strjoin (_define_cwd(), "$ "));
		args.head = parsing(line);
		if (!args.head->next && _is_a_buildin(&args, args.head, NULL, NULL) == 1)
			;
		else
		{
			count = _how_many_cmd(args.head);	
			if (count == 0)
				exit (EXIT_FAILURE);
			args.pid = malloc(sizeof(pid_t) * count);
			if (!args.pid)
				exit (EXIT_FAILURE);
			fork_n_exec(&args, args.head);
			i = 0;
			while (i < count)
			{
				waitpid(args.pid[i], NULL, 0);
				++i;
			}
			ft_sectclear(args.head);
		}
	}
	return (0);
}
