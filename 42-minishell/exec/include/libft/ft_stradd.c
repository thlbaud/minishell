/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:11:41 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/02 20:12:54 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	**ft_stradd(char **map, char *add)
{
	char	**new;
	int		i;
	
	i = 0;
	while (map[i])
		++i;
	new = ft_calloc(sizeof(char *), (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (map[i])
	{
		new[i] = map[i];
		++i;
	}
	new[i] = add;
	return (new);
}