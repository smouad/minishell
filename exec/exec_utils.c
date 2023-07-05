/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:43:47 by msodor            #+#    #+#             */
/*   Updated: 2023/07/04 13:15:27 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_file(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
		return (1);
	return (0);
}

char	**get_path(t_env *env)
{
	env = env->next;
	while (env)
	{
		if (!ft_strcmp("PATH", env->key))
		{
			return (ft_split(env->value, ":"));
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
	char	*str;
	char	**array;

	l_size = list_size(env);
	array = (char **)malloc(l_size * sizeof(char *));
	env = env->next;
	i = 0;
	while (env && i < l_size)
	{
		str = ft_strjoin(env->key, "=");
		array[i] = ft_strjoin(str, env->value);
		free(str);
		i++;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}
