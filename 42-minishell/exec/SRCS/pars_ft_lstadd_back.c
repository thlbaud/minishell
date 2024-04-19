/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_ft_lstadd_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:54:00 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/17 14:17:59 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/parsing.h"

static t_section	*ft_sectlast(t_section *lst)
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
		new->prev = t;
		new->next = NULL;
	}
	else if (!lst)
	{
		lst = new;
		new->prev = NULL;
		new->next = NULL;
	}
	return (lst);
}

static t_file	*ft_redlast(t_file *lst)
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
		new->next = NULL;
	}
	else if (!lst)
		lst = new;
	return (lst);
}
