/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:49:18 by thibaud           #+#    #+#             */
/*   Updated: 2024/04/07 18:13:20 by tmouche          ###   ########.fr       */
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
	int	fd_f[2];

	fd_f[0] = 0;
	fd_f[1] = 1;
	_is_a_buildin(args, s_cmd, fd_pw, fd_pr);
	_pathfinder(args, s_cmd->path_cmd);
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	if (fd_f[0] == 0 && s_cmd->prev)
		fd_f[0] = fd_pr[0];
	if (dup2(fd_f[0], 0) == -1)
		_error_exit(args, NULL, 1);
	if (fd_f[1] == 1 && s_cmd->next)
		fd_f[1] = fd_pw[1];
	if (dup2(fd_f[1], 1) == -1)
		_error_exit(args, NULL, 1);
	_pipe_closer(fd_pr, fd_pw, fd_f);
	execve(s_cmd->path_cmd[0], s_cmd->path_cmd, args->env);
	_error_exit(args, s_cmd->path_cmd[0], 1);
}

void	fork_n_exec(t_data *args, t_section *cmd)
{
	int	i;

	i = 0;
	if (pipe(args->pipe) == -1)
		_error_exit(args, NULL, 1);
	if (pipe(args->pipe_sec) == -1)
		_error_exit(args, NULL, 1);
	while (cmd)
	{
		args->pid[i] = fork();
		if (args->pid[i] == -1)
		{
			_pipe_closer(args->pipe, args->pipe_sec, NULL);
			_error_exit(args, NULL, 1);
		}
		if (args->pid[i] == 0 && i % 2 == 0)
			_exec_cmd(args, cmd, args->pipe, args->pipe_sec);
		else if (args->pid[i] == 0)
			_exec_cmd(args, cmd, args->pipe_sec, args->pipe);
		cmd = cmd->next;
		++i;
	}
	_pipe_closer(args->pipe, args->pipe_sec, NULL);
}
