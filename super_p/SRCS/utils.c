/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:49:10 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/19 19:11:07 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/pipex.h"
#include "../include/libft/libft.h"

void	_write_error(char *str, char *file)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(file, 2);
	write(2, "\n", 1);
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

void	_error(char **args, int err, int *fd)
{
	if (err > -1)
		ft_putstr_fd("Error : ", 2);
	if (err == 0)
		ft_putstr_fd("Pipe\n", 2);
	else if (err == 1)
		ft_putstr_fd("Fork\n", 2);
	else if (err == 2)
		ft_putstr_fd("Dup2\n", 2);
	else if (err == 3)
		ft_putstr_fd("Open\n", 2);
	else if (err == 4)
		ft_putstr_fd("Execution\n", 2);
	if (args)
		_freetab(args);
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	exit (EXIT_FAILURE);
}
