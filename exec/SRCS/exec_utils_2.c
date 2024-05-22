/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:32:03 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/14 23:59:35 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
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
