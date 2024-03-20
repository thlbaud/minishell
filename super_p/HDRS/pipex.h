/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:17:43 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/20 14:13:33 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_args
{
	char	**env;
	char	**argv;
	int		num_cmd;
	pid_t	*pid;
	int		pipe[2];
	int		pipe_sec[2];
}				t_args;

void	fork_n_exec(t_args *args);

char	**_pathfinder(t_args *args, char *full_cmd);
void	_check_file(t_args *args, char **cmd_path, char *file, int cmd_num);

void	_pipe_closer(int *pipe, int	*pipe_sec);
void	_error(t_args *args, char **cmd, int err);
void	_write_error(char *str, char *file);
void	_freetab(char **tab);

#endif