/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:49:18 by thibaud           #+#    #+#             */
/*   Updated: 2024/03/20 14:27:18 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../HDRS/pipex.h"
#include "../include/libft/libft.h"
#include <stdio.h>

static void	_exec_last(t_args *args, int num_cmd, int *pipe, int *pipe_sec)
{
	char	**cmd;
	int		fd;

	_check_file(args, NULL, args->argv[num_cmd + 1], 2);
	_check_file(args, NULL, args->argv[num_cmd], -1);
	cmd = _pathfinder(args, args->argv[num_cmd]);
	if (!cmd)
		_error(args, NULL, -1);
	fd = open (args->argv[num_cmd + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		_error(args, NULL, 3);
	if (num_cmd % 2 == 0)
	{
		if (dup2(args->pipe_sec[0], 0) == -1)
			_error(args, NULL, 2);
	}
	else
	{
		if (dup2(args->pipe[0], 0) == -1)
			_error(args, NULL, 2);
	}
	if (dup2(fd, 1) == -1)
		_error(args, NULL, 2);
	_pipe_closer(pipe, pipe_sec);
	close (fd);
	if (execve(cmd[0], cmd, args->env) == -1)
		_error(args, NULL, 4);

}
static void	_exec_cmd(t_args *args, int num_cmd, int *pipe, int *pipe_sec)
{
	char	**cmd;

	_check_file(args, NULL, args->argv[num_cmd], -1);
	cmd = _pathfinder(args, args->argv[num_cmd]);
	if (!cmd)
		_error(args, NULL, -1);
	if (num_cmd % 2 == 0)
	{
		if (dup2(args->pipe_sec[0], 0) == -1)
			_error(args, NULL, 2);
		if (dup2(args->pipe[1], 1) == -1)
			_error(args, NULL, 2);
	}
	else
	{
		if (dup2(args->pipe[0], 0) == -1)
			_error(args, NULL, 2);
		if (dup2(args->pipe_sec[1], 1) == -1)
			_error(args, NULL, 2);
	}
	_pipe_closer(pipe, pipe_sec);
	if (execve(cmd[0], cmd, args->env) == -1)
		_error(args, NULL, 4);

}

static void	_exec_first(t_args *args, int *pipe, int *pipe_sec)
{
	char	**cmd;
	int		fd;

	_check_file(args, NULL, args->argv[1], 1);
	_check_file(args, NULL, args->argv[2], -1);
	cmd = _pathfinder(args, args->argv[2]);
	if (!cmd)
		_error(args, NULL, -1);
	fd = open (args->argv[1], O_RDONLY);
	if (fd == -1)
		_error(args, NULL, 3);
	if (dup2(fd, 0) == -1)
		_error(args, NULL, 2);
	if (dup2(args->pipe[1], 1) == -1)
		_error(args, NULL, 2);
	_pipe_closer(pipe, pipe_sec);
	close (fd);
	if (execve(cmd[0], cmd, args->env) == -1)
		_error(args, NULL, 4);
}

void	fork_n_exec(t_args *args)
{
	int	i;

	i = 0;
	if (pipe(args->pipe) == -1)
		_error(args, NULL, 0);
	if (pipe(args->pipe_sec) == -1)
		_error(args, NULL, 0);
	while (i < args->num_cmd)
	{
		args->pid[i] = fork();
		if (args->pid[i] == -1)
			_error(args, NULL, 1);
		if (args->pid[i] == 0 && i == 0)
			_exec_first(args, args->pipe, args->pipe_sec);
		else if (args->pid[i] == 0 && i == args->num_cmd - 1)
			_exec_last(args, i + 2, args->pipe, args->pipe_sec);
		else if (args->pid[i] == 0)
			_exec_cmd(args, i + 2, args->pipe, args->pipe_sec);
		++i;
	}
	_pipe_closer(args->pipe, args->pipe_sec);
}
