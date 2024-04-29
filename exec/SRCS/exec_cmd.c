/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:49:18 by thibaud           #+#    #+#             */
/*   Updated: 2024/04/29 23:24:45 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static void	_fd_handler(t_data *args, t_section *s_cmd, int id)
{
	int		fd_f[2];
	int		res[2];

	fd_f[0] = 0;
	fd_f[1] = 1;
	res[0] = 0;
	res[1] = 0;
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	if (fd_f[0] != 0)
		res[0] = dup2(fd_f[0], 0);
	else if (s_cmd->prev)
		res[0] = dup2(args->pipe[0], 0);
	else if (s_cmd->prev && id % 2 == 0)
		res[0] = dup2(args->pipe_sec[0], 0);
	if (fd_f[1] != 1)
		res[1] = dup2(fd_f[1], 1);
	else if (s_cmd->next && id % 2 == 0)
		res[1] = dup2(args->pipe[1], 1);
	else if (s_cmd->next)
		res[1] = dup2(args->pipe_sec[1], 1);
	_close_pipe(args);
	_close_file(fd_f);
	if (res[0] == -1|| res[1] == -1)
		_exit_failure(args);
}

static void	_exec_cmd(t_data *args, t_section *s_cmd, int id)
{
	char	**to_exec;

	/*if (_is_a_buildin(args, s_cmd, fd_pw, fd_pr) == 1)
		_on_success(args, s_cmd, ALL);*/
	_pathfinder(args, s_cmd->path_cmd);
	if (!s_cmd->path_cmd[0])
		_on_success(args, s_cmd, ALL);
	_fd_handler(args, s_cmd, id);
	to_exec = _on_success(args, s_cmd, PARTIAL);
	execve(to_exec[0], to_exec, args->env);
	_exec_failed(to_exec, args->env);
}

void	fork_n_exec(t_data *args, t_section *s_cmd)
{
	int	i;

	if (pipe(args->pipe) == -1)
		_exit_failure(args);
	if (pipe(args->pipe_sec) == -1)
	{
		_close_pipe(args);
		_exit_failure(args);
	}
	i = 0;
	while (s_cmd)
	{
		args->pid[i] = fork();
		if (args->pid[i] == -1)
		{
			_close_pipe(args);
			_exit_failure(args);
		}
		if (args->pid[i] == 0)
			_exec_cmd(args, s_cmd, i);
		s_cmd = s_cmd->next;
		++i;
	}
	_close_pipe(args);
}
