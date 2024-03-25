/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:55:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/25 13:48:47 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	STRUCTURE_H
# define STRUCTURE_H
#include "structure.h"
#include <fcntl.h>

typedef struct s_file
{
	int				redirect;
	char			*name;
	char			*part_env;
	struct s_file	*next;
}				t_file;

typedef struct	s_section
{
	char 				**path_cmd;
	t_file				*file;
	struct s_section	*prev;
	struct s_section	*next;
}				t_section;

typedef struct s_data
{
	char		**env;
	pid_t		*pid;
	int			pipe[2];
	int			pipe_sec[2];
	t_section	*head;
}				t_data;

#endif