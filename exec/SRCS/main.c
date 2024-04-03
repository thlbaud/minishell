/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:35:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/03 12:34:02 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*void	print_pars(t_section *first)
{
	t_section	*sect;
	t_red		*red;
	int 		i = 1;
	int 		j;
	int 		k;

	sect = first;
	while (sect)
	{
		printf("\n           section %d\n\n", i);
		j = 1;
		k = 0;
		red = sect->first_red;
		printf("\ncmd = ");
		while (sect->cmd[k])
		{
			printf("arg %d = %s;    ", k, sect->cmd[k]);
			k++;
		}
		printf("\n");
		while (red)
		{
			printf("\nredirection %d\n\nred name = %s\ndirection = %d\n", j, red->file, red->direction);
			red = red->next;
			j++;
		}
		i++;
		printf("\n       ----------------------          \n");
		sect = sect->next;
	}
}*/

/*static t_exec	*_set_cmd(void)
{
	static t_section	cmd1;
	static t_exec	cmd2;
	static t_file	file2;
	char	**path1;
	char	**path2;

	// PREMIERE CMD
	path1 = malloc(sizeof(char *) * 3);
	path1[0] = malloc(4); 
	path1[1] = malloc(4);
	ft_strlcpy(path1[0], "cat", 4);
	ft_strlcpy(path1[1], "out", 4);
	path1[2] = NULL;
	cmd1.next = &cmd2;
	cmd1.prev = NULL;
	cmd1.path_cmd = path1;
	cmd1.file = NULL;
	
	// SECONDE CMD
	path2 = malloc(sizeof(char *) * 3);
	path2[0] = malloc(13); 
	path2[1] = NULL;
	ft_strlcpy(path2[0], "/usr/bin/ls", 12);
	cmd2.next = NULL;
	cmd2.prev = &cmd1;
	cmd2.path_cmd = path2;
	cmd2.file = &file2;
	
	// 2sd cmd file
	file2.name = "last";
	file2.redirect = 1;
	file2.next = NULL;
	return (&cmd1);
}*/

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
		line = readline("minishell/");
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
