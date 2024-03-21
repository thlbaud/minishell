/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:49:18 by thibaud           #+#    #+#             */
/*   Updated: 2024/03/21 16:03:42 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../HDRS/pipex.h"
#include "../include/libft/libft.h"
#include <stdio.h>

/*static void	_exec_last(t_args *args, int num_cmd, int *pipe, int *pipe_nused)
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
	if (dup2(pipe[0], 0) == -1)
		_error(args, NULL, 2);
	if (dup2(fd, 1) == -1)
		_error(args, NULL, 2);
	_pipe_closer(pipe, pipe_nused);
	close (fd);
	if (execve(cmd[0], cmd, args->env) == -1)
		_error(args, NULL, 4);

}
static void	_exec_cmd(t_data *args, int num_cmd, int *pipe_in, int *pipe_out)
{
	char	**cmd;

	_check_file(args, NULL, args->argv[num_cmd], -1);
	cmd = _pathfinder(args, args->argv[num_cmd]);
	if (!cmd)
		_error(args, NULL, -1);
	if (dup2(pipe_in[0], 0) == -1)
		_error(args, NULL, 2);
	if (dup2(pipe_out[1], 1) == -1)
		_error(args, NULL, 2);
	_pipe_closer(pipe_in, pipe_out);
	if (execve(cmd[0], cmd, args->env) == -1)
		_error(args, NULL, 4);

}

static void	_exec_first(t_data *args, t_exec *cmd, int *pipe, int *pipe_nused)
{
	char	**cmd;
	int		fd;
	
	if (cmd->next == NULL)
		_check_file(cmd->file, "Bash: ");
	else
		_check_file(cmd->file, cmd->path_cmd[0]);
	cmd = _pathfinder(args, cmd);
	if (!cmd)
		_error(args, NULL, -1);
	fd = open (args->argv[1], O_RDONLY);
	if (fd == -1)
		_error(args, NULL, 3);
	if (dup2(fd, 0) == -1)
		_error(args, NULL, 2);
	if (dup2(pipe[1], 1) == -1)
		_error(args, NULL, 2);
	_pipe_closer(pipe, pipe_nused);
	close (fd);
	if (execve(cmd[0], cmd, args->env) == -1)
		_error(args, NULL, 4);
}*/

static void	_exec_cmd(t_data *args, t_exec *cmd, int *pipe_w, int *pipe_r)
{
	if (args->num_cmd == 1)
		_check_file(cmd, cmd->path_cmd[0]);
	else
		_check_file(cmd, "Bash :");
	_pathfinder(args, cmd->path_cmd);
	
}

void	fork_n_exec(t_data *args, t_exec *cmd)
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
		else if (args->pid[i] == 0 && i == args->num_cmd - 1 && (i + 2) % 2 == 0)
			_exec_last(args, i + 2, args->pipe_sec, args->pipe);
		else if (args->pid[i] == 0 && i == args->num_cmd - 1)
			_exec_last(args, i + 2, args->pipe, args->pipe_sec);
		else if (args->pid[i] == 0 && (i + 2) % 2 == 0)
			_exec_cmd(args, i + 2, args->pipe_sec, args->pipe);
		else if (args->pid[i] == 0)
			_exec_cmd(args, i + 2, args->pipe, args->pipe_sec);
		++i;
	}
	_pipe_closer(args->pipe, args->pipe_sec);
}
