/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:27:22 by msodor            #+#    #+#             */
/*   Updated: 2023/07/05 13:00:34 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * do_unset - function that removes an environment variable from the list
 * @arg: The name of the variable to unset
 * @env: A pointer to the head of the environment variable linked list
 * Return: void
 */
void	do_unset(char *arg, t_env *env)
{
	t_env	*tmp;

	tmp = env->next;
	while (tmp)
	{
		if (!ft_strcmp(arg, tmp->key))
		{
			env_del(&env, tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

/**
 * ft_unset - function that handles the unset command
 * @cmd: A pointer to the command structure
 * @parser: A pointer to the parser structure
 * Return: void
 */
void	ft_unset(t_cmd *cmd, t_parser *parser)
{
	int		i;
	int		trig;

	i = 0;
	trig = 0;
	while (cmd->args[i])
	{
		if (!is_correct(cmd->args[i]))
			trig = 1;
		else
			do_unset(cmd->args[i], parser->env);
		i++;
	}
	parser->exit_s = trig;
}
