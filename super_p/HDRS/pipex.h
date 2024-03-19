/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:17:43 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/19 20:36:02 by thibaud          ###   ########.fr       */
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
	int		fd_pipe[2];
}				t_args;

void	fork_n_exec(t_args *args);

char	**_pathfinder(char **env, char *full_cmd, int	*fd);
void	_check_file(char **cmd_path, char *file, int *fd, int cmd_num);

void	_error(char **args, int err, int *fd);
void	_write_error(char *str, char *file);
void	_freetab(char **tab);

#endif