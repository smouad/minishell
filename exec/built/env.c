/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:30:40 by msodor            #+#    #+#             */
/*   Updated: 2023/07/13 16:39:47 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * get_env - function that creates a linked list of environment variable nodes
 * from an array of strings
 * @env: The array of strings representing the environment variables
 * Return: A pointer to the head of the linked list
 */
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

/**
 * ft_env - function that displays the environment variables
 * @cmd: A pointer to the command structure
 * @parser: A pointer to the parser structure
 * Return: void
 */
void	ft_env(t_cmd *cmd, t_parser *parser)
{
	t_env	*env;

	env = parser->env;
	if (!cmd->args[0])
	{
		while (env && env->next)
		{
			env = env->next;
			if (env->value)
				printf("%s=%s\n", env->key, env->value);
		}
		parser->exit_s = 0;
	}
	else
	{
		printf("env: incorrect number of argumments\n");
		parser->exit_s = 1;
	}
}
