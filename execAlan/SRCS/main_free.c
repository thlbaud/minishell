/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:06:50 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/21 19:12:43 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "../HDRS/execution.h"
#include "../HDRS/structure.h"
#include "../include/libft/libft.h"

static void	_stctfree(void *stct, e_type typelst)
{
	if (typelst == SECTION_LST && stct)
	{
		if (((t_section *)stct)->path_cmd)
			_freetab(((t_section *)stct)->path_cmd);
		if (((t_section *)stct)->pipe)
			free(((t_section *)stct)->pipe);
		if (((t_section *)stct)->file)
			_lstfree(((t_section *)stct)->file, FILE_LST);
	}
	else if (typelst == FILE_LST && stct)
	{
		if (((t_file *)stct)->protection)
			free (((t_file *)stct)->protection);
		if (((t_file *)stct)->name)
			_freetab(((t_file *)stct)->name);
		if (((t_file *)stct)->temp)
			_freetab(((t_file *)stct)->temp);
	}
}

void	_freetab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		if (tab[i][0])
			free (tab[i]);
		++i;
	}
	free (tab);
}

void	_lstfree(void *lst, e_type typelst)
{
	void	*temp;

	while (lst)
	{
		temp = lst;
		if (typelst == INDEX_LST)
			lst = ((t_index *)lst)->next;
		else if (typelst == FILE_LST)
		{
			_stctfree((t_file *)lst, FILE_LST);
			lst = ((t_file *)lst)->next;
		}
		else if (typelst == SECTION_LST)
		{
			_stctfree((t_section *)lst, SECTION_LST);
			lst = ((t_section *)lst)->next;
		}
		free (temp);
	}
}

void	_exit_failure(t_data *args)
{
	if (args->pid)
		free (args->pid);
	if (args->head)
		_lstfree(args->head, SECTION_LST);
	if (args->path_history)
		free (args->path_history);
	if (args->env)
		_freetab(args->env);
	if (args->env_history)
		_freetab(args->env_history);
	if (args->pipe)
		_freeint(args->pipe, args->count);
	if (errno != EINTR)
		perror(NULL);
	exit(EXIT_FAILURE);
}
