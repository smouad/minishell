/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:43:47 by msodor            #+#    #+#             */
/*   Updated: 2023/06/18 15:01:54 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_path(char *cmd)
{
	if (cmd[0] == '/')
		return (1);
	return (0);
}

char	**get_path(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp("PATH", env->key, 5))
		{
			return (ft_split(env->value, ':'));
			break ;
		}
		env = env->next;
	}
	return (NULL);
}

int	list_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**list_to_array(t_env *env)
{
	int		i;
	int		l_size;
	char	**array;

	l_size = list_size(env);
	array = (char **)malloc(l_size * sizeof(char *));
	env = env->next;
	while (env && i < l_size)
	{
		array[i] = ft_strjoin(env->key, "=");
		array[i] = ft_strjoin(array[i], env->value);
		i++;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}

void	exec_cmd(t_cmd *cmd)
{
	
}
