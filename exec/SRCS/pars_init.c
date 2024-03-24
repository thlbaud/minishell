/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:58:26 by avaldin           #+#    #+#             */
/*   Updated: 2024/03/24 20:24:43 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/parsing.h"
#include "../include/libft/libft.h"

char	*pars_section(char *line, t_section **first)
{
	t_section	*new_sect;

	new_sect = ft_calloc(1, sizeof(t_section));
	if (!new_sect)
		return (NULL);  // pas ok
	line = pars_red(line, new_sect);
	cleaning_cmd(new_sect, line);
	*first = ft_sectadd_back(*first, new_sect);
	return (line);
}



t_section *parsing(char *line)
{
	t_section *first;
	int i;

	first = NULL;
	while (line)
	{
		line = pars_section(line, &first);     //calloc
		i = 0;
		while (line && line[i] != '|')
		{
			if (!line[i])
			{
				free(line);
				line = NULL;
			}
			else if (line[i] == '"' || line[i] == 39)
				i += skip_quote(&line[i]) + 2;
			else
				i++;
		}
		if (line)
			line = str_cut(line, 0, i);
	}
	return (first);
}
