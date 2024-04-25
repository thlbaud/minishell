/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:58:59 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/25 16:15:16 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

_Bool	_write_env(char **env, char *pre_str, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (pre_str)
			if (write(fd, pre_str, ft_strlen(pre_str, 0)) == -1
				|| write(fd, " ", 1) == -1)
				return (0);
		if (write(fd, env[i], ft_strlen(env[i], 0)) == -1
			|| write(fd, "\n", 1) == -1)
			return (0);
		++i;
	}
	return (1);
}

void	_bi_env(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	char	*error;
	int		fd_f[2];
	int		res;

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (s_cmd->file)
		if (_open_file(args, s_cmd->file, fd_f) == 0)
			return ;
	if (fd_f[1] == 1 && s_cmd->next)
		fd_f[1] = fd_pw[1];
	if (s_cmd->path_cmd[1])
	{
		_pipe_closer(fd_pr, fd_pw, fd_f);
		error = ft_strdup("env: Too much arguments\n");
		if (!error)
			_exit_failure(args);
		_on_error(args, error, 1, WRITE);
		return ;
	}
	res = _write_env(args->env, NULL, fd_f[1]);
	_pipe_closer(fd_pr, fd_pw, fd_f);
	if (res == -1)
		_exit_failure(args);
}
