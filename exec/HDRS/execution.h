/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:17:43 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/29 04:46:02 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
#include "../HDRS/structure.h"

_Bool	_egal_notpresent(t_data *args, t_section *s_cmd, t_index *lst, int i_args);
_Bool	_egal_present(t_data *args, t_section *s_cmd, t_index **lst, int i_args);

_Bool	_open_file(t_data *args, t_file *file, int *fd_f);
void	fork_n_exec(t_data *args, t_section *cmd);
_Bool	_write_env(char **env, char *pre_str, int fd);

void	_pathfinder(t_data *args, char **cmd);

void	_pipe_closer(int *fd_pipe_r, int *fd_pipe_w, int *fd_files);
void	_on_error(t_data *args, char *str, int err, e_write write_id);
char	**_on_success(t_data *args, t_section *s_cmd, e_from from_id);
_Bool	_str_no_spe_char(char *str, size_t n);
char	**_map_cpy(char **map);
void	_exec_failed(char **cmd, char **env);
char	*_getenv(char **env, char *asked);
char	*_get_str(t_data *args, char *base);

int		_is_a_buildin(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_history(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_export(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_unset(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_exit(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_echo(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_pwd(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_env(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);
void	_bi_cd(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr);

void	_change_dir(t_data *args, t_section *s_cmd, char *old_pwd);
void	_export_oldpwd(t_data *args, char *old_pwd);

void	_lstaddback_index(t_index **lst, t_index *new);
t_index	*_lstlast_index(t_index *lst);
int		_lstsize_index(t_index *lst);
t_index	*_lstnew_index(int content);
char 	*_define_cwd(void);

#endif