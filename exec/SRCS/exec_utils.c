/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:10 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/24 19:50:13 by tmouche          ###   ########.fr       */
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

void	_error_exit(t_data *args)
{
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
