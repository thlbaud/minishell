/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:17:43 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/24 19:14:21 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "../HDRS/structure.h"

int		_write_cwd_error(void);
char	*_give_strerror_dir(t_data *args, char *str);
char	*_give_strerror_cmd(t_data *args, char *str);
char	*_give_strerror_identifier(t_data *args, t_index *lst, char *str);

void	_export_str(t_data *args, t_section *s_cmd, t_index *lst);
_Bool	_egal_present(t_data *args, t_section *s_cmd, t_index **lst,
			int i_args);

_Bool	_fd_handler(t_data *args, t_section *s_cmd, int id);
void	fork_n_exec(t_data *args, t_section *cmd);
_Bool	_write_env(char **env, char *pre_str);

char	*_pars_heredoc(t_data *args, t_file *file, char *line);

void	_add_to_env_history(t_data *args, char *new_cmd);
void	_pathfinder(t_data *args, char **cmd);

void	_on_error(t_data *args, char *str, int err, t_write write_id);
char	**_on_success(t_data *args, t_section *s_cmd, t_from from_id);
char	**_map_cpy(char **map);
int		_size_map(char **map);
void	_exec_failed(char **cmd, char **env, char *not_found, int exit_status);
char	*_getenv(char **env, char *asked);
char	*_get_str(t_data *args, char *base);

int		_is_a_buildin(t_section *s_cmd);
void	_bi_history(t_data *args, t_section *s_cmd);
void	_bi_export(t_data *args, t_section *s_cmd);
void	_bi_unset(t_data *args, t_section *s_cmd);
void	_bi_exit(t_data *args, t_section *s_cmd);
void	_bi_echo(t_data *args, t_section *s_cmd);
void	_bi_pwd(t_data *args, t_section *s_cmd);
void	_bi_env(t_data *args, t_section *s_cmd);
void	_bi_cd(t_data *args, t_section *s_cmd);

void	_change_dir(t_data *args, t_section *s_cmd, char *old_pwd);
void	_export_pwd(t_data *args, char *old_pwd);

void	_lstaddback_index(t_index **lst, t_index *new);
t_index	*_lstlast_index(t_index *lst);
int		_lstsize_index(t_index *lst);
t_index	*_lstnew_index(int content);
char	*_define_cwd(void);

void	_close_pipe(t_data *args);
void	_close_file(t_data *args, int *fd, int id);

int		_check_args_history(t_data *args, t_section *s_cmd);

char	**_set_env(char **env);

char	*prompt(char *pwd, t_data *args);
void	_looper(t_data *args);

#endif