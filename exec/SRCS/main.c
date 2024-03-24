/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:35:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/24 20:25:31 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../HDRS/parsing.h"
#include "../HDRS/structure.h"
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"
#include <stdio.h>

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
	t_data		all_args;
	char		*line;
	int			count;
	int			i;

	(void)argc;
	all_args.env = env;
	line = ft_strdup(argv[1]);
	if (!line)
		exit (EXIT_FAILURE);
	all_args.head = parsing(line);
	count =  _how_many_cmd(all_args.head);
	if (count == 0)
		exit (EXIT_FAILURE);
	all_args.pid = malloc(sizeof(pid_t) * count);
	if (!all_args.pid)
		exit (EXIT_FAILURE);
	fork_n_exec(&all_args, all_args.head);
	i = 0;
	while (i < count)
	{
		waitpid(all_args.pid[i], NULL, 0);
		++i;
	}
	ft_sectclear(all_args.head);
	return (0);
}
