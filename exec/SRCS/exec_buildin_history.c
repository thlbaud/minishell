/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_history.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:45:01 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/22 06:06:18 by tmouche          ###   ########.fr       */
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
static inline int   _write_history(int fd_out, char *history)
{
    int count;
    int size;
    int i;
    
    i = 0;
    count = 1;
    while (history[i])
    {
        if (write(fd_out, " ", 1) == -1)
			return (-1);
		ft_putnbr_fd(count, fd_out);
		if (write(fd_out, " ", 1) == -1)
            return (-1);
        size = ft_strlen(&history[i], '\n');
        if (write(fd_out, &history[i], size + 1) == -1)
            return (-1);
        i += size + 1;
		++count;
    }
    return (1);
}

static inline int   _get_history(int fd_out, char *path)
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
    if (_write_history(fd_out, buff) == -1)
        return (close (fd), free (buff), 0);
    return (close (fd), free (buff), 1);
}

void	_bi_history(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
    int fd_f[2];

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	_get_history(fd_f[1], args->path_history);
	_pipe_closer(fd_pr, fd_pw, fd_f);
}