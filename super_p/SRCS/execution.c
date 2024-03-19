/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:49:18 by thibaud           #+#    #+#             */
/*   Updated: 2024/03/19 21:02:39 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../HDRS/pipex.h"
#include "../include/libft/libft.h"

static void	_exec_last(char **argv, int *fd_pipe, char **env, int num_cmd)
{
	char	**args;
	int		fd;

	_check_file(NULL, argv[num_cmd + 1], fd_pipe, 2);
	_check_file(NULL, argv[num_cmd], fd_pipe, -1);
	args = _pathfinder(env, argv[num_cmd], fd_pipe);
	if (!args)
		_error(NULL, -2, fd_pipe);
	fd = open (argv[num_cmd + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		_error(args, 3, fd_pipe);
	if (dup2(fd_pipe[0], 0) == -1)
		_error(args, 2, fd_pipe);
	if (dup2(fd, 1) == -1)
		_error(args, 2, fd_pipe);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close (fd);
	if (execve(args[0], args, env) == -1)
		_error(args, 4, NULL);
}
static void	_exec_cmd(char **argv, int *fd_pipe, char **env, int num_cmd)
{
	char	**args;

	_check_file(NULL, argv[num_cmd], fd_pipe, -1);
	args = _pathfinder(env, argv[num_cmd], fd_pipe);
	if (!args)
		_error(NULL, -2, fd_pipe);
	if (dup2(fd_pipe[0], 0) == -1)
		_error(args, 2, fd_pipe);
	if (dup2(fd_pipe[1], 1) == -1)
		_error(args, 2, fd_pipe);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	if (execve(args[0], args, env) == -1)
		_error(args, 4, NULL);
}

static void	_exec_first(char **argv, int *fd_pipe, char **env)
{
	char	**args;
	int		fd;

	_check_file(NULL, argv[1], fd_pipe, 1);
	_check_file(NULL, argv[2], fd_pipe, -1);
	args = _pathfinder(env, argv[2], fd_pipe);
	if (!args)
		_error(NULL, -1, fd_pipe);
	fd = open (argv[1], O_RDONLY);
	if (fd == -1)
		_error(args, 3, fd_pipe);
	if (dup2(fd_pipe[1], 1) == -1)
		_error(args, 2, fd_pipe);
	if (dup2(fd, 0) == -1)
		_error(args, 2, fd_pipe);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close (fd);
	if (execve(args[0], args, env) == -1)
		_error(args, 4, NULL);
}

void	fork_n_exec(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_cmd)
	{
		args->pid[i] = fork();
		if (args->pid[i] == -1)
			_error(NULL, 1, args->fd_pipe);
		if (args->pid[i] == 0 && i == 0)
			_exec_first(args->argv, args->fd_pipe, args->env);
		else if (args->pid[i] == 0 && i == args->num_cmd - 1)
			_exec_last(args->argv, args->fd_pipe, args->env, i + 2);
		else if (args->pid[i] == 0)
			_exec_cmd(args->argv, args->fd_pipe, args->env, i + 2);
		++i;
	}
}
