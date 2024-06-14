/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfull.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:26:01 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/14 17:30:34 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfull(const char *s, int c)
{
	size_t	i;

	i = -1;
	while (s[++i])
		if (s[i] != (unsigned char)c)
			return (&((char *)s)[i]);
	return (0);
}
