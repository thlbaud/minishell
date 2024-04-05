/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:55:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/04/05 18:11:31 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	STRUCTURE_H
# define STRUCTURE_H
#include <fcntl.h>

typedef struct s_index
{
	int				i;
	struct s_index	*next;	
}				t_index;

typedef struct s_file
{
	int				redirect;
	char			**name;
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

typedef enum 
{
	INDEX_LST,
	FILE_LST, 
	SECTION_LST 
} 				e_type;

#endif