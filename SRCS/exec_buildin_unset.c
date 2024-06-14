/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:11:54 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/24 18:36:58 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline char	*_give_strerror_id(t_data *args, char *str)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin("bash: unset: '", str);
	if (!temp)
		_exit_failure(args);
	res = ft_strjoin(temp, "': not a valid identifier\n");
	free (temp);
	if (!res)
		_exit_failure(args);
	return (res);
}

static inline _Bool	_unset_args(char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
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

static inline char	**_erase_args(t_data *args, char **map, int skip)
{
	char	**new_env;
	int		i_new;
	int		i_old;

	if (skip < 0)
		return (map);
	new_env = ft_calloc(sizeof(char *), _size_map(map));
	if (!new_env)
		_exit_failure(args);
	i_new = 0;
	i_old = 0;
	while (map[i_old])
	{
		if (i_old != skip)
		{
			new_env[i_new] = map[i_old];
			++i_old;
			++i_new;
		}
		else
			free (map[i_old++]);
	}
	free (map);
	return (new_env);
}

static inline int	_search_env(char **env, char *search, t_senv from)
{
	int	i_env;

	i_env = 0;
	while (env[i_env])
	{
		if (from == ENV)
			if (ft_strncmp(search, env[i_env], ft_strlen(search, 0)) == 0)
				return (i_env);
		if (from == HISTORY)
			if (ft_strncmp(search, &env[i_env][ft_strlen(env[i_env], ' ') + 1]
				, ft_strlen(search, 0)) == 0)
				return (i_env);
		++i_env;
	}
	return (-1);
}

void	_bi_unset(t_data *args, t_section *s_cmd)
{
	int		i_args;

	i_args = 1;
	while (s_cmd->path_cmd[i_args])
	{
		if (_unset_args(s_cmd->path_cmd[i_args]) == 0)
			_on_error(args, _give_strerror_id(args, s_cmd->path_cmd[i_args]),
				1, WRITE);
		args->env = _erase_args(args, args->env, _search_env(args->env,
					s_cmd->path_cmd[i_args], ENV));
		args->env_history = _erase_args(args, args->env_history,
				_search_env(args->env_history,
					s_cmd->path_cmd[i_args], HISTORY));
		++i_args;
	}
	args->exit_status = 0;
}
