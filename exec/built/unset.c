/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:27:22 by msodor            #+#    #+#             */
/*   Updated: 2023/06/26 13:59:09 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// void	ft_unset(t_cmd *cmd, t_env **env)
// {
// 	int		i;
// 	t_env	*tmp;

// 	i = 0;
// 	while (cmd->args[i])
// 	{
// 		tmp = (*env)->next;
// 		if (!is_correct(cmd->args[i]))
// 			i++;
// 		else
// 		{
// 			while (tmp)
// 			{
// 				if (!ft_strncmp(cmd->args[i], tmp->key, 
// 				ft_strlen(cmd->args[i]) + 1))
// 				{
// 					env_del(env, tmp);
// 					break ;
// 				}
// 				tmp = tmp->next;
// 			}
// 			i++;
// 		}
// 	}
// }
