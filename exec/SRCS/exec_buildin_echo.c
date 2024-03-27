/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:49:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/27 17:36:05 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

void	_bi_echo(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	int	fd_f[2];
	int	i;

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	if (fd_f[1] == 1 && s_cmd->next)
		fd_f[1] = fd_pw[1];
	i = 1;
	if (ft_strncmp(s_cmd->path_cmd[i], "-n", 2) == 0)
		++i;
	while (s_cmd->path_cmd[i])
	{
		if (write(fd_f[1], s_cmd->path_cmd[i], ft_strlen(s_cmd->path_cmd[i], 0)) == -1)
			_error_exit(args, NULL);
		++i;
	}
	if (ft_strncmp(s_cmd->path_cmd[1], "-n", 2) != 0 || !s_cmd->path_cmd[1])
		write(fd_f[1], "\n", 1);
	_pipe_closer(fd_pr, fd_pw, fd_f);
	exit (EXIT_SUCCESS);
}