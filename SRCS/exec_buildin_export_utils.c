/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_export_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:13:48 by tmouche           #+#    #+#             */
/*   Updated: 2024/06/14 13:00:30 by tmouche          ###   ########.fr       */
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
		++i;
	}
	new_env = ft_stradd(args->env, temp);
	if (!new_env)
	{
		free (temp);
		_lstfree(lst, INDEX_LST);
		_exit_failure(args);
	}
	free (args->env);
	args->env = new_env;
}

inline void	_export_str(t_data *args, t_section *s_cmd, t_index *lst)
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

static inline int	_check_exist(t_index **lst, char **path_cmd, int i_args)
{
	int	i;

	i = 1;
	while (i < i_args)
	{
		if (ft_strncmp(path_cmd[i], path_cmd[i_args],
				ft_strlen(path_cmd[i_args], '=')) == 0)
		{
			while ((*lst) && (*lst)->i != i)
				(*lst) = (*lst)->next;
			if (*lst)
				(*lst)->i = i_args;
			return (0);
		}
		++i;
	}
	return (1);
}

_Bool	_egal_present(t_data *args, t_section *s_cmd, t_index **lst, int i_args)
{
	t_index	*temp;

	temp = NULL;
	if (_check_exist(lst, s_cmd->path_cmd, i_args) == 1)
	{
		temp = _lstnew_index(i_args);
		if (!temp)
		{
			_lstfree(*lst, INDEX_LST);
			_exit_failure(args);
		}
		_lstaddback_index(lst, temp);
	}
	return (1);
}
