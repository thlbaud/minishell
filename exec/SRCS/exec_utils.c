/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:10 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/13 23:22:49 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"
#include <stdio.h>

inline char	*_get_str(t_data *args, char *base)
{
	char *str_error;

	str_error = ft_strdup(base);
	if (!str_error)
		_exit_failure(args);
	return (str_error);	
}

char	*_getenv(char **env, char *asked)
{
	int	index;

	index = 0;
	while (env[index])
	{
		if (ft_strncmp(env[index], asked, ft_strlen(asked, 0)) == 0)
			return (&env[index][ft_strlen(env[index], '=') + 1]);
		++index;
	}
	return (NULL);
}

_Bool	_str_no_spe_char(char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (str[i] && i < n)
	{
		if ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
			++i;
		else
			return (0);
	}
	return (1);
}

char	**_map_cpy(char **map)
{
	char	**new_map;
	int		i;

	if (!map)
		return (NULL);
	i = 0;
	while (map[i])
		++i;
	new_map = ft_calloc(sizeof(char *), (i + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
			return (_freetab(new_map), NULL);
		++i;
	}
	return (new_map);
}

inline void	_close_file(t_data *args, int *fd, int id)
{
	if (id == 0 && args->count > 1)
	{
		if (fd[0] != 0)  
			close (fd[0]);
		if (fd[1] != 1 && fd[1] != args->pipe[id][1])
			close (fd[1]);
	}
	if (id > 0 && args->count > 1)
	{
		if (fd[0] != 0 && fd[0] != args->pipe[id - 1][0])  
			close (fd[0]);
		if (fd[1] != 1 && fd[1] != args->pipe[id][1])
			close (fd[1]);
	}
	else
	{
		if (fd[0] != 0)  
			close (fd[0]);
		if (fd[1] != 1)
			close (fd[1]);
	}
}

inline void	_close_pipe(t_data *args)
{
	int	index;

	index = 0;
	if (!args->pipe)
		return ;
	while (index < args->count - 1)
	{
		if (args->pipe[index][0] != 0)
			close (args->pipe[index][0]);
		if (args->pipe[index][1] != 0)
			close (args->pipe[index][1]);
		free (args->pipe[index]);
		++index;
	}
	free (args->pipe);
	args->pipe = NULL;
}