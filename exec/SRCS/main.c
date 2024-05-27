/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:35:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/24 18:12:14 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/structure.h"
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

int	g_sig = 0;

static inline int	_get_path_history(t_data *args)
{
	char	*temp;
	char	*path;
	int		i;

	temp = _define_cwd();
	if (!temp)
		return (_write_cwd_error());
	i = 2;
	i += ft_strlen(&temp[i], '/');
	++i;
	i += ft_strlen(&temp[i], '/');
	++i;
	path = ft_calloc(sizeof(char), i + 1);
	if (!path)
		return (free (temp), -1);
	ft_strlcpy(path, temp, ++i);
	if (!path)
		return (-1);
	free (temp);
	args->path_history = ft_strjoin(path, ".minishell-history");
	free (path);
	if (!args->path_history)
		return (-1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	args;
	int		i;

	(void)argc;
	(void)argv;
	args.exit_status = 0;
	args.pipe = NULL;
	args.env_history = NULL;
	if (_get_path_history(&args) == -1)
		return (-1);
	args.env = _set_env(env);
	if (!args.env)
		return (-1);
	i = 0;
	while (args.env[i])
	{
		_add_to_env_history(&args, args.env[i]);
		++i;
	}
	while (42)
		_looper(&args);
	return (0);
}
