/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_history.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:45:01 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/23 03:27:55 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline int	_get_file_size(char *path)
{
	char	buff[1000];
	int		temp;
	int		size;
	int		fd;	

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	size = 0;
	temp = 1;
	while (temp != 0)
	{
		temp = read(fd, buff, 1000);
		if (temp == -1)
			return (-1);
		size += temp;
	}
	close (fd);
	return (size);
}

static inline _Bool	_write_history(char **history, int limit)
{
	int	i;

	i = 0;
	if (limit != -2)
	{
		while (history[i])
			++i;
		i -= limit;
	}
	while (history[i])
	{
		if (write(1, " ", 1) == -1)
			return (0);
		ft_putnbr_fd(i + 1, 1);
		if (write(1, " ", 1) == -1)
			return (0);
		if (write(1, history[i], ft_strlen(history[i], 0)) == -1)
			return (0);
		if (write(1, "\n", 1) == -1)
			return (0);
		++i;
	}
	return (1);
}

static inline int	_get_history(char *path, int limit)
{
	char	**history;
	char	*buff;
	int		size;
	int		fd;

	size = _get_file_size(path);
	if (size == -1)
		return (0);
	buff = ft_calloc(sizeof(char), size + 1);
	if (!buff)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (free (buff), 0);
	if (read(fd, buff, size) == -1)
		return (close (fd), free (buff), 0);
	history = ft_split(buff, '\n');
	close (fd);
	free (buff);
	if (!history)
		return (0);
	if (_write_history(history, limit) == 0)
		return (_freetab(history), 0);
	return (_freetab(history), 1);
}

void	_bi_history(t_data *args, t_section *s_cmd)
{
	int	res;

	res = _check_args_history(args, s_cmd);
	if (res == -1)
		return ;
	if (_get_history(args->path_history, res) == 0)
		_exit_failure(args);
	args->exit_status = 0;
}
