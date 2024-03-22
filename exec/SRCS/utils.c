/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:10 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/22 18:44:49 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/pipex.h"
#include "../include/libft/libft.h"

void	_pipe_closer(int *pipe, int	*pipe_sec)
{
	if (pipe)
	{
		close (pipe[0]);
		close (pipe[1]);
	}
	if (pipe_sec)
	{
		close (pipe_sec[0]);
		close (pipe_sec[1]);
	}
}

void	_write_error(char *str, char *file)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(file, 2);
	write(2, "\n", 1);
}

void	_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		++i;
	}
	free (tab);
}

void	_error(t_args *args, char **cmd, int err)
{
	_pipe_closer(args->pipe, args->pipe_sec);
	if (cmd)
		_freetab(cmd);
	free (args->pid);
	exit (EXIT_FAILURE);
}
