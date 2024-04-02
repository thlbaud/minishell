/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:31:28 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/02 19:39:29 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

int	_lstsize_index(t_index *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_index	*_lstnew_index(int content)
{
	t_index	*head;

	head = malloc(sizeof(t_index));
	if (!head)
		return (NULL);
	head->i = content;
	head->next = NULL;
	return (head);
}

t_index	*_lstlast_index(t_index *lst)
{
	int	i;

	i = _lstsize_index(lst) - 1;
	while (i > 0)
	{
		lst = lst->next;
		i--;
	}
	return (lst);
}

void	_lstaddback_index(t_index **lst, t_index *new)
{
	if (*lst)
		_lstlast_index(*lst)->next = new;
	else
		*lst = new;
}