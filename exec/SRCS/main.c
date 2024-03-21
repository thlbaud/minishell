/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:35:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/20 13:55:39 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../HDRS/pipex.h"
#include "../include/libft/libft.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_args	all_args;
	int		i;

	if (argc < 5)
		return (ft_putstr_fd("Incorrect number of arguments\n", 2), 1);
	all_args.num_cmd = argc - 3;
	all_args.argv = argv;
	all_args.env = env;
	all_args.pid = malloc(sizeof(pid_t) * all_args.num_cmd);
	if (!all_args.pid)
		exit (EXIT_FAILURE);
	fork_n_exec(&all_args);
	i = 0;
	while (i < all_args.num_cmd)
	{
		waitpid(all_args.pid[i], NULL, 0);
		++i;
	}
	return (0);
}
