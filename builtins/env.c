/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:30:40 by msodor            #+#    #+#             */
/*   Updated: 2023/06/15 17:00:02 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_env(char **env)
{
	int		i;
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	lst->next = NULL;
	i = 0;
	while (env[i])
		env_list_add(&lst, env_new(env[i++]));
	return (lst);
}

void	ft_env(t_cmd *cmd, t_env *env)
{
	if (!cmd->args[0])
	{
		while (env && env->next)
		{
			env = env->next;
			if (env->value)
				printf("%s=%s\n", env->key, env->value);
		}
	}
	else
		printf("env: incorrect number of argumments\n");
}