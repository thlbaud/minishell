/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:44:49 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/14 16:42:16 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = -1;
	while (s[++i])
		if (s[i] == (unsigned char)c)
			return (&((char *)s)[i]);
	if (s[i] == (unsigned char)c)
		return (&((char *)s)[i]);
	return (0);
}
