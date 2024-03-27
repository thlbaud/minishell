/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:17:43 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/27 22:25:08 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
#include "../HDRS/structure.h"

void	_open_file(t_data *args, t_file *file, int *fd_f);
void	fork_n_exec(t_data *args, t_section *cmd);

void	_check_alias(t_data *args, char *name);

void	_pathfinder(t_data *args, char **cmd);

void	_pipe_closer(int *fd_pipe_r, int *fd_pipe_w, int *fd_files);
void	_error_exit(t_data *args, char *str);
void	_freetab(char **tab);

void	_is_a_buildin(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_echo(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_pwd(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);

#endif