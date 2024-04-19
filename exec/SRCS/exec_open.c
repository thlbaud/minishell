/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:12:53 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/19 04:47:26 by thibaud          ###   ########.fr       */
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
#include <stdio.h>

static	int	_heredoc_handling(char **name)
{
	char	*line;
	int		name_len;
	int		pipe_heredoc[2];

	if (pipe(pipe_heredoc) == -1)
		return (-1);
	name_len = ft_strlen(name[1], 0);
	while (42)
	{
		line = readline("> ");
		if (ft_strncmp(line, name[1], name_len) == 0)
			break ;
		if (write(pipe_heredoc[1], line, ft_strlen(line, 0)) == -1 
			|| write(pipe_heredoc[1], "\n", 1) == -1)
		{
			close (pipe_heredoc[0]);
			close (pipe_heredoc[1]);
			return (-1);
		}
	}
	close (pipe_heredoc[1]);
	return (pipe_heredoc[0]);
}

static	void	_check_redirect(t_data *args, char **name, int *fd_f)
{
	char	*str_error;
	char	*str_final;

	if (name[1])
		return ;
	_pipe_closer(args->pipe, args->pipe_sec, fd_f);
	str_error = ft_strjoin("bash : ", name[0]);
	if (!str_error)
		_error_exit(args, NULL, 1);
	if (!name[0])
		str_final = ft_strjoin(str_error, ": No such file directory\n");
	else
		str_final = ft_strjoin(str_error, ": ambiguous redirect\n");
	free (str_error);
	if (!str_final)
		_error_exit(args, NULL, 1);
	write (2, str_final, ft_strlen(str_final, 0));
	free (str_final);
	_error_exit(args, NULL, 0);
}

void	_open_file(t_data *args, t_file *file, int *fd_f)
{
	while (file)
	{
		if (fd_f[1] != 1 && file->redirect > 0)
			close (fd_f[1]);
		if (fd_f[0] != 0 && file->redirect < 0)
			close (fd_f[0]);
		_check_redirect(args, file->name, fd_f);
		if (file->redirect == 2)
			fd_f[1] = open(file->name[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (file->redirect == 1)
			fd_f[1] = open(file->name[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->redirect == -1)
			fd_f[0] = open(file->name[1], O_RDONLY);
		else if (file->redirect == -2)
			fd_f[0] = _heredoc_handling(file->name);
		if (fd_f[0] == -1 || fd_f[1] == -1)
		{
			_pipe_closer(args->pipe, args->pipe_sec, fd_f);
			_error_exit(args, ft_strjoin("Bash: ", file->name[1]), 1);
		}
		file = file->next;
	}
}
