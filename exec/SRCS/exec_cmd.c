/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:49:18 by thibaud           #+#    #+#             */
/*   Updated: 2024/05/22 12:15:45 by avaldin          ###   ########.fr       */
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

static void	_exec_cmd(t_data *args, t_section *s_cmd, int id)
{
	char	**to_exec;

	sig_quit(1);
	_fd_handler(args, s_cmd, id);
	if (_is_a_buildin(s_cmd) == 1)
	{
		s_cmd->function_ptr(args, s_cmd);
		_on_success(args, s_cmd, ALL);
	}
	if (!ft_strchr(s_cmd->path_cmd[0], '/'))
		_pathfinder(args, s_cmd->path_cmd);
	to_exec = _on_success(args, s_cmd, PARTIAL);
	execve(to_exec[0], to_exec, args->env);
	_exec_failed(to_exec, args->env, to_exec[0], args->exit_status);
}

static void	_open_pipe(t_data *args)
{
	int	index;

	index = 0;
	if (args->count == 1)
		return ;
	args->pipe = ft_calloc(sizeof(int *), args->count - 1);
	if (!args->pipe)
		_exit_failure(args);
	while (index < args->count - 1)
	{
		args->pipe[index] = ft_calloc(sizeof(int), 2);
		if (!args->pipe[index])
			_exit_failure(args);
		++index;
	}
	index = 0;
	while (index < args->count - 1)
	{
		if (pipe(args->pipe[index]) == -1)
		{
			_close_pipe(args);
			_exit_failure(args);
		}
		++index;
	}
}

void	fork_n_exec(t_data *args, t_section *s_cmd)
{
	t_section	*temp;
	int			i;

	i = 0;
	_open_pipe(args);
	temp = s_cmd;
	while (temp)
	{
		args->pid[i] = fork();
		if (args->pid[i] == -1)
		{
			_close_pipe(args);
			_exit_failure(args);
		}
		if (args->pid[i] == 0)
			_exec_cmd(args, temp, i);
		temp = temp->next;
		++i;
	}
}
