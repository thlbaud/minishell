/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:35:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/22 06:05:27 by tmouche          ###   ########.fr       */
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
#include <sys/wait.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../HDRS/parsing.h"
#include "../HDRS/structure.h"
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

int	g_err;

static inline void	_add_history(t_data *args, char *line)
{
	int	fd;

	if (!line || !line[0])
		return ;
	add_history(line);
	fd = open(args->path_history, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		_error_exit(args, NULL, 1);
	if (write(fd, line, ft_strlen(line, '0')) == -1 
		|| write(fd, "\n", 1) == -1)
		_error_exit(args, NULL, 1);
}

static inline int	_get_path_history(t_data *args)
{
	char	*temp;
	char	*path;
	int		i;

	temp = _define_cwd();
	if (!temp)
		return (-1);
	i = 2;
	i += ft_strlen(&temp[i], '/');
	++i;
	i += ft_strlen(&temp[i], '/');
	++i;
	path = ft_calloc(sizeof(char), i + 1);
	if (!path)
		return (-1);
	ft_strlcpy(path, temp, ++i);
	if (!path)
		return (-1);
	args->path_history = ft_strjoin(path, ".minishell-history");
	if (!args->path_history)
		return (-1);
	return (0);
}

static inline int	_how_many_cmd(t_section *cmd)
{
	t_section	*temp;
	int			counter;

	temp = cmd;
	counter = 0;
	while (temp)
	{
		temp = temp->next;
		++counter;
	}
	return (counter);
}

static inline void	_execution(t_data *args)
{
	int	i;
	int	count;

	count = _how_many_cmd(args->head);	
	if (count == 0)
		exit (EXIT_FAILURE);
	args->pid = malloc(sizeof(pid_t) * count);
	if (!args->pid)
		exit (EXIT_FAILURE);
	fork_n_exec(args, args->head);
	i = 0;
	while (i < count)
	{
		waitpid(args->pid[i], NULL, 0);
		++i;
	}
	if (args->pid)
		free (args->pid);
	args->pid = NULL;
}

void	_looper(t_data *args)
{
	char				*pwd;
	char				*temp;
	char				*line;
	
	args->pid = NULL;
	pwd = _define_cwd();
	if (pwd)
	{
		temp = ft_strjoin (pwd, "$ ");
		free (pwd);
		line = readline(temp);
		if (line[0] == 0)
			return ;	
		free (temp);
	}
	else
		return ;
	_add_history(args, line);
	parsing(line, args->env, args);
	if (!args->head->next)
	{
		if (_is_a_buildin(args, args->head, NULL, NULL) == 0)
			_execution(args);
	}
	else
		_execution(args);
	/*_lstfree(args.head, SECTION_LST);
	free (args.pid);*/
}

int	main(int argc, char **argv, char **env)
{
	t_data	args;
	
	(void)argc;
	(void)argv;
	g_err = 0;
	args.env = _map_cpy(env);
	if (!args.env)
		return (-1);
	if (_get_path_history(&args) == -1)
		return (-1);
	sig_int();
	sig_quit();
	while (42)
		_looper(&args);
	return (0);
}
 