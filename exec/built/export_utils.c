/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:12:35 by msodor            #+#    #+#             */
/*   Updated: 2023/07/14 11:41:04 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * get_key - function that gets the key of an environment variable
 * @var: The variable string in the format "key=value"
 * Return: The key string
 */
char	*get_key(char *var)
{
	int		i;
	char	*key;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	key = ft_substr(var, 0, i);
	return (key);
}

/**
 * get_key - function that gets the key of an environment variable
 * @var: The variable string in the format "key=value"
 * Return: The key string
 */
char	*get_value(char *var)
{
	int		i;
	char	*value;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] == '=')
		value = ft_substr(var, i + 1, ft_strlen(var) - i);
	else
		value = NULL;
	return (value);
}

/**
 * set_value - function that sets the value of an environment variable
 * @var: The variable string in the format "key=value"
 * @env: A pointer to the head of the environment variable linked list
 * Return: void
 */
int	set_value(char *var, t_env *env)
{
	char	*key;
	char	*value;
	t_env	*tmp;

	key = get_key(var);
	value = get_value(var);
	tmp = env;
	while (tmp && tmp->next && value)
	{
		tmp = tmp->next;
		if (!ft_strcmp(key, tmp->key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (free(key), free(value), 1);
		}
	}
	tmp = env;
	while (tmp && tmp->next && !value)
	{
		tmp = tmp->next;
		if (!ft_strcmp(key, tmp->key))
			return (free(key), 1);
	}
	return (env_list_add(&tmp, env_new(var)), free(key), free(value), 1);
}
