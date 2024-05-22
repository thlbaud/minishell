/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:19:58 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/16 20:28:23 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline _Bool	_export_args(char *str, size_t n)
{
	size_t	index;

	index = 0;
	while (str[index] && index < n)
	{
		if ((str[index] >= 48 && str[index] <= 57)
			|| (str[index] >= 65 && str[index] <= 90)
			|| (str[index] >= 97 && str[index] <= 122)
			|| str[index] == 95)
			++index;
		else
			return (0);
	}
	return (1);
}

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
	char	*str_err;
	int		i_args;

	i_args = 1;
	lst = NULL;
	while (s_cmd->path_cmd[i_args])
	{
		if (_export_args(s_cmd->path_cmd[i_args],
				ft_strlen(s_cmd->path_cmd[i_args], '=')) == 0
			|| s_cmd->path_cmd[i_args][0] == '='
			|| (s_cmd->path_cmd[i_args][0] >= '0'
			&& s_cmd->path_cmd[i_args][0] <= '9')
			|| s_cmd->path_cmd[i_args][0] == 0)
		{
			str_err = _give_strerror_identifier(args, lst,
					s_cmd->path_cmd[i_args]);
			_on_error(args, str_err, 1, WRITE);
		}
		else if (ft_strrchr(s_cmd->path_cmd[i_args], '='))
		{
			if (_egal_present(args, s_cmd, &lst, i_args) == 0)
				return ;
			_add_to_env_history(args, s_cmd->path_cmd[i_args]);
		}
		else
			_add_to_env_history(args, s_cmd->path_cmd[i_args]);
		++i_args;
	}
	_export_str(args, s_cmd, lst);
}

void	_bi_export(t_data *args, t_section *s_cmd)
{
	if (!s_cmd->path_cmd[1])
		if (_write_env(args->env_history, NULL) == 0)
			_exit_failure(args);
	_set_export(args, s_cmd);
}
