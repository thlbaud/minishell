/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:54:00 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/24 19:44:14 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/parsing.h"

t_section	*ft_sectlast(t_section *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_section	*ft_sectadd_back(t_section *lst, t_section *new)
{
	t_section	*t;

	if (lst && new)
	{
		t = ft_sectlast(lst);
		t->next = new;
	}
	else if (!lst)
		lst = new;
	return (lst);
}

t_file	*ft_redlast(t_file *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_file	*ft_redadd_back(t_file *lst, t_file *new)
{
	t_file	*t;

	if (lst && new)
	{
		t = ft_redlast(lst);
		t->next = new;
	}
	else if (!lst)
		lst = new;
	return (lst);
}
