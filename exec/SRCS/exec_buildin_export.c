/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:19:58 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/28 17:20:07 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

/*t_index	*_lstnew(int content)
{
	t_index	*new;

	new = malloc(sizeof(t_index));
	if (!new)
		return (NULL);
	new->i = content;
	new->next = NULL;
	return (new);
}

t_index	*_lstlast(t_index *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	_lstadd_back(t_index **lst, t_index *new)
{
	if (*lst)
		_lstlast(*lst)->next = new;
	else
		*lst = new;
}*/

void	_bi_export(t_data *args, t_section *s_cmd, int *fd_pw, int *fd_pr)
{
	t_list	*lst;
	t_list	*temp;
	int		fd_f[2];
	int		i_args;

	fd_f[0] = 0;
	fd_f[1] = 1;
	if (s_cmd->file)
		_open_file(args, s_cmd->file, fd_f);
	_pipe_closer(fd_pr, fd_pw, fd_f);
	i_args = 1;
	lst = NULL;
	while (s_cmd->path_cmd[i_args])
	{
		if (ft_strrchr(s_cmd->path_cmd[i_args], '='))
		{
			temp = ft_lstnew((int)i_args);
			if (!temp)
			{
				_free_lst(lst);
				_error_exit(args, NULL);
			}
			ft_lstadd_back(&lst, temp);
		}
		++i_args;
	}
}
