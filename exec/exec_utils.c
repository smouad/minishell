/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:43:47 by msodor            #+#    #+#             */
/*   Updated: 2023/07/05 13:09:30 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * is_file - checks if a command is a file path
 * @cmd: The command to check
 * Return: 1 if the command is a file path, 0 otherwise
 */
int	is_file(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
		return (1);
	return (0);
}

/**
 * get_path - retrieves the value of the PATH and splits it into an array
 * @env: The environment variable linked list
 * Return: An array containing the directories in the PATH,
 * or NULL if PATH is not found
 */
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

/**
 * list_size - calculates the size of an environment variable linked list
 * @env: The environment variable linked list
 * Return: The size of the linked list
 */
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

/**
 * list_to_array - converts an environment variable linked list to an array
 * @env: The environment variable linked list
 * Return: An array containing the environment variables in "key=value" format
 */
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
