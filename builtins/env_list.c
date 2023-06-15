/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:58:54 by msodor            #+#    #+#             */
/*   Updated: 2023/06/15 15:07:34 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*env_new(char *line)
{
	t_env	*env;
	int		index;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	index = ft_strchr(line, '=');
	if (index != -1)
	{
		env->key = ft_substr(line, 0, index);
		env->value = ft_substr(line, index + 1, ft_strlen(line) - index);
	}
	else
	{
		env->key = ft_strdup(line);
		env->value = NULL;
	}
	env->next = NULL;
	return (env);
}

void	env_list_add(t_env **env, t_env *new)
{
	t_env	*ptr;

	if (!env || !new)
		return ;
	if (*env)
	{
		ptr = *env;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
	else
		*env = new;
}