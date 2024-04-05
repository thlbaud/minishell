/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:04:53 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/05 18:58:44 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

/*static inline void	_erase_alias(t_data *args, char *name, int i_name)
{
	char	*new;
	int		name_len;
	int		i;
	
	name_len = ft_strlen(name, 0);
	i = -1;
	while(++i && name[i_name + i] && (name[i_name + i] != '$' || i == 0))
		name[i_name + i] = 0;
	new = malloc(sizeof(char) * (name_len - i));
	if (!new)
		_error_exit(args, NULL);
	i_name = 0;
	name_len -= i;
	i = 0;
	while (i < name_len)
	{
		if (name[i_name] != 0)
		{
			new[i] = name[i_name];
			++i;
		}
		++i_name;
	}
	free(name);
	name = new;
}

static inline void	_replace_alias(t_data *args, char *name, int *i)
{
	int		index;
	int		i_off;
	char	*new;
	
	_erase_alias(args, name, i[0]);
	new = malloc(sizeof(char) * (ft_strlen(name, 0) +
		ft_strlen(&(args->env[i[1]][ft_strlen(args->env[i[1]], '=')]), 0) + 1));
	if (!new)
		_error_exit(args, NULL);
	index = -1;
	while (++index != i[0])
		new[index] = name[index];
	i_off = ft_strlen(args->env[i[1]], '=');
	while (args->env[i[1]][i_off])
	{
		new[index] = args->env[i[1]][i_off];
		++i_off;
		++index;
	}
	while (name[index])
	{
		new[index] = name[index];
		++index;
	}
	free(name);
	name = new;
}

void	_check_alias(t_data *args, char *name)
{
	int		i[2];

	i[0] = 0;
	while (name[i[0]])
	{
		while (name[i[0]] != '$' && name[i[0]])
			++i[0];
		if (!name[i[0]] || !name[i[0] + 1])
			return ;
		i[1] = 0;
		while (args->env[i[1]] && ft_strncmp(&name[i[0] + 1], args->env[i[1]],
				ft_strlen(&name[i[0] + 1], '$')))
			++i[1];
		if (!args->env[i[1]])
			return ;
		if (ft_strchr(args->env[i[1]], ' '))
			_error_exit(args, "bash: : ambiguous redirect\n");
	}
}
*/