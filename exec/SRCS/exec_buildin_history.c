/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_history.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:45:01 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/30 20:14:20 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static inline int   _get_file_size(char *path)
{
    char    buff[1000];
    int     temp;
    int     size;
    int     fd;

	
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
static inline _Bool   _write_history(char *history, int limit)
{
    int count;
    int size;
    int i;
    
    count = 1;
	size = -1;
	while (history[++size])
		++count;
    i = size - limit;
	if (i < 0)
		i = 0;
	count = i + 1;
    while (history[i])
    {
        if (write(1, " ", 1) == -1)
			return (0);
		ft_putnbr_fd(count, 1);
		if (write(1, " ", 1) == -1)
            return (0);
        size = ft_strlen(&history[i], '\n');
        if (write(1, &history[i], size + 1) == -1)
            return (0);
        i += size + 1;
		++count;
    }
    return (1);
}

static inline int   _get_history(char *path, int limit)
{
    char	*buff;
    int     size;
    int     fd;
    
    size = _get_file_size(path);
    if  (size == -1)
        return (0);
    buff = ft_calloc(sizeof(char), size + 1);
    if (!buff)
        return (0);
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (free (buff), 0);
    if (read(fd, buff, size) == -1)
        return (close (fd), free (buff), 0);
    if (_write_history(buff, limit) == 0)
        return (close (fd), free (buff), 0);
    return (close (fd), free (buff), 1);
}

void	_bi_history(t_data *args, t_section *s_cmd)
{
	int	res;
	
	res = _get_history(args->path_history, ft_atoi(s_cmd->path_cmd[1]));
	if (res == 0)
		_exit_failure(args);
}