/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:35:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/19 21:00:34 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../HDRS/pipex.h"
#include "../include/libft/libft.h"



int	main(int argc, char **argv, char **env)
{
	t_args	all_args;
	int		i;

	if (argc < 5)
		return (ft_putstr_fd("Incorrect number of arguments\n", 2), 1);
	all_args.num_cmd = argc - 3;
	all_args.argv = argv;
	all_args.env = env;
	if (pipe(all_args.fd_pipe) == -1)
		exit (EXIT_FAILURE);
	all_args.pid = malloc(sizeof(pid_t) * (argc - 3));
	if (!all_args.pid)
		_error(NULL, -1, all_args.fd_pipe);
	fork_n_exec(&all_args);
	close(all_args.fd_pipe[0]);
	close(all_args.fd_pipe[1]);
	i = 0;
	while (i < all_args.num_cmd)
	{
		waitpid(all_args.pid[i], NULL, 0);
		++i;
	}
	return (0);
}
