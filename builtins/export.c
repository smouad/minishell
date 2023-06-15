/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:42:00 by msodor            #+#    #+#             */
/*   Updated: 2023/06/15 17:26:00 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exist(char *var, t_env *env)
{
	int	i;
	int	index;

	index = ft_strchr(var, '=');
	if (index != -1)
	{
		i = 0;
		while (env)
		{
			if (ft_strncmp(env->key, var, index) == 0)
				return (i);
			env = env->next;
			i++;
		}
	}
	else
	{
		i = 0;
		while (env)
		{
			if (!ft_strncmp(env->key, var, ft_strlen(env->key)))
				return (i);
			env = env->next;
			i++;
		}
	}
	return (-1);
}

void	ft_export(t_cmd *cmd, t_env *env)
{
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
	else if (cmd->args[0] && !cmd->args[1])
	{
		env_list_add(&env, env_new(cmd->args[0]));
	}
	else
		printf("export: incorrect number of argumments\n");
}
