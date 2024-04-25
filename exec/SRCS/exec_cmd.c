/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:49:18 by thibaud           #+#    #+#             */
/*   Updated: 2024/04/25 14:44:40 by tmouche          ###   ########.fr       */
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

static void	_exec_cmd(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	char	**to_exec;
	int		fd_f[2];

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (_is_a_buildin(args, s_cmd, fd_pw, fd_pr) == 1)
		_on_success(args, s_cmd, ALL);
	_pathfinder(args, s_cmd->path_cmd);
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	if (!s_cmd->path_cmd[0])
		_on_success(args, s_cmd, ALL);
	if (fd_f[0] == 0 && s_cmd->prev)
		fd_f[0] = fd_pr[0];
	if (dup2(fd_f[0], 0) == -1)
		_exit_failure(args);
	if (fd_f[1] == 1 && s_cmd->next)
		fd_f[1] = fd_pw[1];
	if (dup2(fd_f[1], 1) == -1)
		_exit_failure(args);
	_pipe_closer(fd_pr, fd_pw, fd_f);
	to_exec = _on_success(args, s_cmd, PARTIAL);
	execve(to_exec[0], to_exec, args->env);
	_exit_failure(args);
}

void	fork_n_exec(t_data *args, t_section *s_cmd)
{
	int	pipe_first[2];
	int	pipe_sec[2];
	int	i;

	i = 0;
	args->pipe = pipe_first;
	args->pipe_sec = pipe_sec;
	if (pipe(pipe_first) == -1)
		_exit_failure(args);
	if (pipe(pipe_sec) == -1)
		_exit_failure(args);
	while (s_cmd)
	{
		args->pid[i] = fork();
		if (args->pid[i] == -1)
		{
			_pipe_closer(args->pipe, args->pipe_sec, NULL);
			_exit_failure(args);
		}
		if (args->pid[i] == 0 && i % 2 == 0)
			_exec_cmd(args, s_cmd, args->pipe, args->pipe_sec);
		else if (args->pid[i] == 0)
			_exec_cmd(args, s_cmd, args->pipe_sec, args->pipe);
		s_cmd = s_cmd->next;
		++i;
	}
	_pipe_closer(args->pipe, args->pipe_sec, NULL);
}
