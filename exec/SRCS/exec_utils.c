/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:10 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/27 16:05:27 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

void	_pipe_closer(int *fd_pipe_r, int *fd_pipe_w, int *fd_files)
{
	if (fd_files)
	{
		if (fd_files[0] != fd_pipe_r[0] && fd_files[0] != 0)
			close (fd_files[0]);
		if (fd_files[1] != fd_pipe_w[1] && fd_files[1] != 1)
			close (fd_files[1]);
	}
	if (fd_pipe_r)
	{
		close (fd_pipe_r[0]);
		close (fd_pipe_r[1]);
	}
	if (fd_pipe_w)
	{
		close (fd_pipe_w[0]);
		close (fd_pipe_w[1]);
	}
}

void	_error_exit(t_data *args, char *str)
{
	perror(str);
	(void)args;
	exit (EXIT_FAILURE);
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
