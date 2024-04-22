/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:10 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/22 05:33:22 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

int	_str_no_spe_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57) 
			|| !(str[i] >= 65 && str[i] <=90) 
			|| !(str[i] >= 97 && str[i] <= 122))
			return (0);
		++i;
	}
	return (1);
}

char	**_map_cpy(char **map)
{
	char	**new_map;
	int		len;
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
		len = ft_strlen(map[i], 0);
		new_map[i] = ft_calloc(sizeof(char), len + 1);
		if (!new_map)
			return (_freetab(new_map), NULL);
		ft_strlcpy(new_map[i], map[i], len + 1);
		++i;
	}
	return (new_map);
}

void	_pipe_closer(int *fd_pipe_r, int *fd_pipe_w, int *fd_files)
{
	if (fd_files)
	{
		if (fd_files[0] != 0 && fd_files[0] != fd_pipe_r[0] && fd_files[0] != -1)
			close (fd_files[0]);
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

void	_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		++i;
	}
	free (tab);
}
