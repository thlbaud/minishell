/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:55:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/05/22 12:46:22 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include "structure.h"
# define EXIT_ERROR 360

extern int	g_sig;

typedef struct s_index
{
	int					i;
	struct s_index		*next;	
}				t_index;

typedef struct s_file
{
	int					tmp_len;
	int					redirect;
	int					*protection;
	char				**name;
	char				**temp;
	struct s_file		*next;

}				t_file;

typedef struct s_data
{
	int					**pipe;
	int					count;
	int					exit_status;
	char				*path_history;
	char				**env;
	char				**env_history;
	pid_t				*pid;
	struct s_section	*head;
}				t_data;

typedef struct s_section
{
	int					fd_f[2];
	char				**path_cmd;
	int					heredoc_protec;
	char				*pipe;
	t_file				*file;
	void				(*function_ptr)(t_data *, struct s_section *);
	struct s_data		*data;
	struct s_section	*prev;
	struct s_section	*next;
}				t_section;

typedef enum
{
	INDEX_LST,
	FILE_LST,
	SECTION_LST
}		e_type;

typedef enum
{
	WRITE,
	AUTO	
}				e_write;

typedef enum
{
	ALL,
	PARTIAL	
}				e_from;

typedef enum
{
	TOO_MANY,
	NOT_NUMERIC
}				e_err;

typedef enum
{
	HOME,
	OLDPWD
}				e_cdenv;

void	sig_int(int mode);
void	sig_quit(int mode);

void	_looper(t_data *args);

void	_freetab(char **tab);
void	_freeint(int **tab, int size);
void	_lstfree(void *lst, e_type typelst);
void	_exit_failure(t_data *args);

#endif