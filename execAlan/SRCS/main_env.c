/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:46:14 by thibaud           #+#    #+#             */
/*   Updated: 2024/05/24 04:10:04 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../HDRS/execution.h"
#include "../include/libft/libft.h"

static char	*_define_shlvl(char *target)
{
	char	*line_shlvl;
	char	*temp;
	int		shlvl;

	shlvl = 0;
	if (target)
		shlvl = ft_atoi(&target[ft_strlen(target, '=') + 1]);
	if (shlvl <= 0)
		shlvl = 1;
	else
		++shlvl;
	temp = ft_itoa(shlvl);
	if (!temp)
		return (NULL);
	line_shlvl = ft_strjoin("SHLVL=", temp);
	free (temp);
	if (!line_shlvl)
		return (NULL);
	return (line_shlvl);
}

static char	**_create_env(void)
{
	char	**new_env;
	char	*pwd;
	
	new_env = ft_calloc(sizeof(char *), 4);
	if (!new_env)
		return(NULL);
	pwd = _define_cwd();
	if (!pwd)
		return (free (new_env), NULL);
	new_env[0] = ft_strjoin("PWD=", pwd);
	if (new_env[0])
	{
		new_env[1] = _define_shlvl(NULL);
		if (new_env[1])
		{
			new_env[2] = ft_strjoin("_=", pwd);
			if (new_env[2])
				return (free (pwd), new_env);
		}
	}
	return (free (pwd), _freetab(new_env), NULL);
}

char	**_set_env(char **env)
{
	char	**new_env;
	char	**temp;
	char	*shlvl;
	int		i;
	
	if (!env || !env[0])
	 	return (_create_env());
	new_env = _map_cpy(env);
	if (!new_env)
		return (NULL);
	i = -1;
	while (new_env[++i])
		if (ft_strncmp(new_env[i], "SHLVL=", 6) == 0)
			break;
	shlvl = _define_shlvl(new_env[i]);
	if (!shlvl)
		return (_freetab(new_env), NULL);
	if (new_env[i])
	{
		free (new_env[i]);
		new_env[i] = shlvl;
	}
	else
	{
		temp = new_env;
		new_env = ft_stradd(new_env, shlvl);
		_freetab(temp);
		if (!new_env)
			free (shlvl);
	}
	return (new_env);
}