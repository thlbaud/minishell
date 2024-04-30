/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:19:58 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/30 19:33:25 by tmouche          ###   ########.fr       */
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
		if (ft_strncmp(args->env[i], temp, ft_strlen(temp, '=') + 1) == 0)
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

	while (lst)
	{
		temp = ft_strdup(s_cmd->path_cmd[lst->i]);
		if (!temp)
		{
			_lstfree(lst, INDEX_LST);
			_exit_failure(args);
		}
		_search_n_replace(args, lst, temp);
		to_free = lst->next;
		free(lst);
		lst = to_free;
	}
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
			if (_egal_present(args, s_cmd, &lst, i_args) == 0)
				return ;
		}
		else
			if (_egal_notpresent(args, s_cmd, lst, i_args) == 0)
				return ;
		++i_args;
	}
	_export_str(args, s_cmd, lst);
}

void	_bi_export(t_data *args, t_section *s_cmd)
{
	int		res;

	res = 2;
	if (!s_cmd->path_cmd[1])
	{
	 	res = _write_env(args->env, "declare -x");
		_close_pipe(args);
		if (res == 0)
			_exit_failure(args);
	}
	_set_export(args, s_cmd);
}
