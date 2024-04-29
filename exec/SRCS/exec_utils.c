/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:10 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/29 00:25:43 by thibaud          ###   ########.fr       */
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

void	_pipe_closer(int *fd_pipe_r, int *fd_pipe_w, int *fd_files)
{
	if (fd_files)
	{
		if (fd_files[0] != 0 && fd_files[0] != -1 && !fd_pipe_r)
			close (fd_files[0]);
		else if (fd_pipe_r)
			if (fd_files[0] != 0 && fd_files[0] != fd_pipe_r[0] && fd_files[0] != -1)
				close (fd_files[0]);
		if (fd_files[1] != 1 && fd_files[1] != -1 && !fd_pipe_w)
			close (fd_files[1]);
		else if (fd_pipe_w)
			if (fd_files[1] != 1 && fd_files[1] != fd_pipe_w[1] && fd_files[1] != -1)
				close (fd_files[1]);
	}
	if (fd_pipe_r)
	{
			close (fd_pipe_r[0]);
			close (fd_pipe_r[1]);
	}
	if (fd_pipe_w)
	{
			close (fd_pipe_w[0]);
			close (fd_pipe_w[1]);
	}
}
