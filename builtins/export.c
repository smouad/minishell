/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:42:00 by msodor            #+#    #+#             */
/*   Updated: 2023/06/16 19:31:35 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_value(char *var, t_env *env)
{
	t_env *new_env;
	t_env *tmp;

	new_env = env_new(var);
	tmp = env;
	while (tmp && tmp->next && new_env->value)
	{
		tmp = tmp->next;
		if (!ft_strncmp(new_env->key, tmp->key, ft_strlen(tmp->key)))
		{
			free(tmp->value);
			tmp->value = new_env->value;
			return ;
		}
	}
	tmp = env;
	while (tmp && tmp->next && !new_env->value)
	{
		tmp = tmp->next;
		if (!ft_strncmp(new_env->key, tmp->key, ft_strlen(tmp->key)))
			return ;
	}
	env_list_add(&tmp, new_env);
	return ;
}

void	ft_export(t_cmd *cmd, t_env *env)
{
	int	i = 0;

	if (!cmd->args[0])
	{
		while (env && env->next)
		{
			env = env->next;
			if (env->value)
				printf("declare -x %s=\"%s\"\n", env->key, env->value);
			else
				printf("declare -x %s\n", env->key);
				
		}
	}
	while (cmd->args[i])
	{
		set_value(cmd->args[i], env);
		i++;
	}
}
