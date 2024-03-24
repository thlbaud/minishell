/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:49:18 by thibaud           #+#    #+#             */
/*   Updated: 2024/03/23 19:24:36 by thibaud          ###   ########.fr       */
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

static void	_open_file(t_data *args, t_file **file, int *fd_f)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (fd_f[1] != 0 && file[i]->redirect > 0)
			close (fd_f[1]);
		if (fd_f[0] != 0 && file[i]->redirect < 0)
			close (fd_f[0]);
		if (file[i]->redirect == 2)
			fd_f[1] = open(file[i], O_WRONLY | O_CREAT, 0644);
		else if (file[i]->redirect == 1)
			fd_f[1] = open(file[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file[i]->redirect == -1)
			fd_f[0] = open(file[i], O_RDONLY);
		else if (file[i]->redirect == -2)
			fd_f[0] = open(STDIN_FILENO, O_RDONLY);
		if (fd_f[0] == -1 || fd_f[1] == -1)
		{
			perror("Bash :");
			exit (EXIT_FAILURE); //RETOUR ERREUR
		}
		++i;
	}
}

static void	_exec_cmd(t_data *args, t_exec *s_cmd, int *fd_pw, int *fd_pr)
{
	int	fd_f[2];

	fd_f[0] == 0;
	fd_f[1] == 1;
	_pathfinder(args, s_cmd->path_cmd);
	if (s_cmd->file)
		_open_file(args, s_cmd, fd_f);
	if (fd_f[0] == 0 && s_cmd->prev)
		fd_f[0] = fd_pr[0];
	if (dup2(fd_f[0], 0) == -1)
		exit (EXIT_FAILURE); //RETOUR ERREUR
	if (fd_f[1] == 1 && s_cmd->prev)
		fd_f[1] = fd_pr[1];
	if (dup2(fd_f[1], 1) == -1)
		exit (EXIT_FAILURE); //RETOUR ERREUR
	execve(s_cmd->path_cmd[0], s_cmd->path_cmd, args->env);
	perror("Bash :");
	exit (EXIT_FAILURE); //RETOUR ERREUR
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
