/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:32:03 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/27 10:33:36 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../HDRS/parsing.h"
#include "../include/libft/libft.h"

inline int	_size_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (i);
	while (map[i])
		++i;
	return (i);
}
