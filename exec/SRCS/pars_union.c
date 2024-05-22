/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_union.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:41:44 by avaldin           #+#    #+#             */
/*   Updated: 2024/04/17 18:03:03 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/parsing.h"
#include "../include/libft/libft.h"

int	null_red(t_file *red)
{
	int	i;

	i = 0;
	while (i < red->tmp_len)
	{
		if (red->temp[i] && red->temp[i][0])
			return (0);
		i++;
	}
	i = 0;
	while (i < red->tmp_len)
	{
		if (red->protection[i])
		{
			red->name[1] = ft_calloc(1, sizeof(char));
			return (1);
		}
		i++;
	}
	red->name[1] = NULL;
	return (1);
}

char	*temp_join(t_file *red)
{
	int		i;
	char	*file;

	i = 0;
	file = NULL;
	while (i < red->tmp_len && !file)
	{
		if (!red->temp[i] || !red->temp[i][0])
			i++;
		else
			file = _strdup(red->temp[i++], 0, -1);
	}
	while (i < red->tmp_len)
	{
		if (red->temp[i] && red->temp[i][0])
		{
			file = str_modify(file, (int) ft_strlen(file, 0), 0,
					_strdup(red->temp[i], 0, -1));
		}
		i++;
	}
	return (file);
}

void	red_union(t_section *sect)
{
	t_file	*red;

	red = sect->file;
	while (red)
	{
		if (red->temp && !null_red(red))
		{
			red->name[1] = temp_join(red);
		}
		red = red->next;
	}
}
