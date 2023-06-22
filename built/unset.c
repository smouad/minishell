/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:27:22 by msodor            #+#    #+#             */
/*   Updated: 2023/06/23 00:44:09 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// make it one line less

void	ft_unset(t_cmd *cmd, t_parser *parser)
{
	int		i;
	int		trig;
	t_env	*tmp;

	i = 0;
	trig = 0;
	while (cmd->args[i])
	{
		tmp = parser->env->next;
		if (!is_correct(cmd->args[i]))
			trig = 1;
		else
		{
			while (tmp)
			{
				if (!ft_strcmp(cmd->args[i], tmp->key))
				{
					env_del(&parser->env, tmp);
					break ;
				}
				tmp = tmp->next;
			}
		}
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
