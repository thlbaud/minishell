/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:17:43 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/26 15:52:05 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
#include "../HDRS/structure.h"

void	fork_n_exec(t_data *args, t_section *cmd);

void	_check_alias(t_data *args, char *name);

void	_pathfinder(t_data *args, char **cmd);

void	_pipe_closer(int *fd_pipe_r, int *fd_pipe_w, int *fd_files);
void	_error_exit(t_data *args);
void	_freetab(char **tab);

#endif