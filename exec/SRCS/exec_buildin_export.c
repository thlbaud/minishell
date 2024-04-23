/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:19:58 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/24 01:00:07 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline void	_search_n_replace(t_data *args, t_index *lst, char *temp)
{
	char	**new_env;
	int		i;

	i = 0;
	while (args->env[i])
	{
		if (ft_strncmp(args->env[i], temp, ft_strlen(temp, '=')) == 0)
		{
			free (args->env[i]);
			args->env[i] = temp;
			return ;
		}
		if (!args->env[++i])
		{
			new_env = ft_stradd(args->env, temp);
			if (!new_env)
			{
				free (temp);
				_lstfree(lst, INDEX_LST);
				_exit_failure(args);
			}
			args->env = new_env;
			return ;
		}
	}
}

static inline void	_export_str(t_data *args, t_section *s_cmd, t_index *lst)
{
	t_index	*to_free;
	char	*temp;
	size_t	len;

	while (lst)
	{
		len = ft_strlen(s_cmd->path_cmd[lst->i], 0);
		temp = ft_calloc(sizeof(char), len + 1);
		if (!temp)
		{
			_lstfree(lst, INDEX_LST);
			_exit_failure(args);
		}
		ft_strlcpy(temp, s_cmd->path_cmd[lst->i], len + 1);
		_search_n_replace(args, lst, temp);
		to_free = lst->next;
		free(lst);
		lst = to_free;
	}
	_on_success(args, s_cmd, BUILDIN);
}

static inline void	_set_export(t_data *args, t_section *s_cmd)
{
	t_index	*lst;
	int		i_args;

	i_args = 1;
	lst = NULL;
	while (s_cmd->path_cmd[i_args])
	{
		if (ft_strrchr(s_cmd->path_cmd[i_args], '='))
		{
			if (_egal_present(args, s_cmd, lst, i_args) == 0)
				return ;
		}
		else
			if (_egal_notpresent(args, s_cmd, lst, i_args) == 0)
				return ;
		++i_args;
	}
	_export_str(args, s_cmd, lst);
}

void	_bi_export(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	int		fd_f[2];
	int		res;

	fd_f[0] = 0;
	fd_f[1] = 1;
	res = 2;
	if (s_cmd->file)
		if (_open_file(args, s_cmd->file, fd_f) == 0)
			return ;
	if (!s_cmd->path_cmd[1])
	{
	 	res = _write_env(args->env, "declare -x", fd_f[1]);
		_pipe_closer(fd_pr, fd_pw, fd_f);
		if (res == 0)
			_exit_failure(args);
		_on_success(args, s_cmd, BUILDIN);
	}
	_set_export(args, s_cmd);
}
