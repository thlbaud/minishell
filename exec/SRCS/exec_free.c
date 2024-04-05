/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:47:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/05 19:09:22 by tmouche          ###   ########.fr       */
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

void	_error_exit(t_data *args, char *str, _Bool error)
{
	if (error == 1)
		perror(str);
	else
		write(2, str, ft_strlen(str, 0));
	_freetab(args->env);
	_lstfree(args->head, SECTION_LST);
	exit (EXIT_FAILURE);
}
