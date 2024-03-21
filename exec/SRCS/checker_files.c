/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:28:46 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/21 14:04:37 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "../HDRS/pipex.h"
#include "../include/libft/libft.h"

static inline void	_w_err(char *str, char *file, char *source)
{
	ft_putstr_fd(source, 2);
	write(2, ": ", 1);
	ft_putstr_fd(file, 2);
	write(2, ": ", 1);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	exit (EXIT_FAILURE);
}

void	_check_file(t_exec *actual, char source)
{
	int		i;

	i = 0;
	while (actual->file[i])
	{
		if (actual->file[i]->redirect > 0)
		{
			if (access(actual->file[i]->name, F_OK) == -1)
				_w_err("No such file or directory", actual->file[i]->name, source);
			else if (access(actual->file[i]->name, R_OK) == -1)
				_w_err("Permission denied", actual->file[i]->name, source);
		}
		else
		{
			if (access(actual->file[i]->name, F_OK) < 0)
			{
				if (access(actual->file[i]->name, W_OK) == -1)
					_w_err("Permission denied", actual->file[i]->name, source);
			}
		}
		++i;
	}
}
