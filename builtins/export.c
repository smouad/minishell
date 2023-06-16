/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:42:00 by msodor            #+#    #+#             */
/*   Updated: 2023/06/16 13:11:52 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_value(char *var, t_env *env)
{
	int		index;
	char	*key;
	
	index = ft_strchr(var, '=');
	if (index != -1)
	{
		key = ft_substr(var, 0, index);
		while (env)
		{
			env = env->next;
			if (!ft_strncmp(key, env->key, ft_strlen(env->key)))
			{
				free(env->value);
				env->value = ft_substr(key, index + 1, ft_strlen(var) - index);
				return (1);
			}
		}
		return (-1);
	}
	else
	{
		while (env)
		{
			env = env->next;
			if (!ft_strncmp(var, env->key, ft_strlen(env->key)))
				return (1);
		}
		return (-1);
	}
		
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
	else
	{
		while (cmd->args[i])
		{
			if (set_value(cmd->args[i], env) == -1)
				env_list_add(&env, env_new(cmd->args[i]));
			i++;
		}
	}
}
