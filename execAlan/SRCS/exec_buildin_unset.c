/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:11:54 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/24 04:52:16 by thibaud          ###   ########.fr       */
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

static inline void	_erase_args(t_data *args, int skip)
{
	char	**new_env;
	int		i_new;
	int		i_old;

	new_env = ft_calloc(sizeof(char *), _size_map(args->env));
	if (!new_env)
		_exit_failure(args);
	i_new = 0;
	i_old = 0;
	while (args->env[i_old])
	{
		if (i_old != skip)
		{
			new_env[i_new] = args->env[i_old];
			++i_old;
			++i_new;
		}
		else
			free (args->env[i_old++]);
	}
	free (args->env);
	args->env = new_env;
}

void	_bi_unset(t_data *args, t_section *s_cmd)
{
	int		i_args;
	int		i_env;

	i_args = 1;
	while (s_cmd->path_cmd[i_args])
	{
		i_env = 0;
		if (_unset_args(s_cmd->path_cmd[i_args]) == 0)
			_on_error(args, _give_strerror_id(args, s_cmd->path_cmd[i_args]), 1, WRITE);
		while (args->env[i_env])
		{
			if (ft_strncmp(s_cmd->path_cmd[i_args], args->env[i_env],
					ft_strlen(s_cmd->path_cmd[i_args], 0)) == 0)
			{
				_erase_args(args, i_env);
				break ;
			}
			++i_env;
		}
		++i_args;
	}
	args->exit_status = 0;
}
