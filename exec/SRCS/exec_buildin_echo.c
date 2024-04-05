/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:49:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/05 19:00:12 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline int	_write_echo(char **path_cmd, int fd)
{
	int	i;

	i = 1;
	if (ft_strncmp(path_cmd[i], "-n", 2) == 0)
		++i;
	while (path_cmd[i])
	{
		if (write(fd, path_cmd[i], ft_strlen(path_cmd[i], 0)) == -1)
			return (-1);
		if (path_cmd[++i])
			if (write(fd, " ", 1) == -1)
				return (-1);
	}
	if (ft_strncmp(path_cmd[1], "-n", 2) != 0 || !path_cmd[1])
		write(fd, "\n", 1);
	return (0);
}

void	_bi_echo(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	int	fd_f[2];
	int	result;

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	if (fd_f[1] == 1 && s_cmd->next)
		fd_f[1] = fd_pw[1];
	result = _write_echo(s_cmd->path_cmd, fd_f[1]);
	_pipe_closer(fd_pr, fd_pw, fd_f);
	if (result == -1)
		_error_exit(args, NULL, 1);
}
