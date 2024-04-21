/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:47:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/21 05:24:28 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

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
			free (((t_file *)lst)->name);
			lst = ((t_file *)lst)->next;
		}
		else if (typelst == SECTION_LST)
		{
			_freetab (((t_section *)lst)->path_cmd);
			_lstfree(((t_section *)lst)->file, FILE_LST);
			lst = ((t_section *)lst)->next;
		}
		free (temp);
	}
}

void	_error_exit(t_data *args, t_section *s_cmd, char *str, int error)
{
	if (error >= 1)
		perror(str);
	else
		write(2, str, ft_strlen(str, 0));
	_freetab(args->env);
	_lstfree(args->head, SECTION_LST);
	if (error == 2)
		exit (EXIT_FAILURE);
	if (s_cmd->next || s_cmd->prev)
		exit (EXIT_FAILURE);
	else
		_looper(args);
}
