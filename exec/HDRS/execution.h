/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:17:43 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/22 04:33:33 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
#include "../HDRS/structure.h"

void	_open_file(t_data *args, t_file *file, int *fd_f);
void	fork_n_exec(t_data *args, t_section *cmd);
int     _write_env(char **env, char *pre_str, int fd);

void	_pathfinder(t_data *args, char **cmd);

void	_pipe_closer(int *fd_pipe_r, int *fd_pipe_w, int *fd_files);
void	_error_exit(t_data *args, char *str, int error);
void	_lstfree(void *lst, e_type typelst);
int	    _str_no_spe_char(char *str);
char	**_map_cpy(char **map);
void	_freetab(char **tab);

int		_is_a_buildin(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_history(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_export(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_unset(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_exit(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_echo(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_pwd(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_env(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_cd(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);

void	_lstaddback_index(t_index **lst, t_index *new);
t_index	*_lstlast_index(t_index *lst);
int		_lstsize_index(t_index *lst);
t_index	*_lstnew_index(int content);
char 	*_define_cwd(void);

#endif