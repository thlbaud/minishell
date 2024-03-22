/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:17:43 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/22 19:14:54 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_file
{
	int		redirect;
	char	*name;
}				t_file;

typedef struct	s_exec
{
	char 			**path_cmd;
	t_file			**file;
	struct s_exec	*next;
}				t_exec;

typedef struct s_data
{
	char	**env;
	char	**argv;
	pid_t	*pid;
	int		pipe[2];
	int		pipe_sec[2];
	t_exec	**all_pipe;
}				t_data;

void	fork_n_exec(t_data *args, t_exec *cmd);

char	**_pathfinder(t_data *args, char *full_cmd);
void	_check_file(t_exec *actual, char source);

void	_pipe_closer(int *pipe, int	*pipe_sec);
void	_error(t_data *args, char **cmd, int err);
void	_write_error(char *str, char *file);
void	_freetab(char **tab);

#endif