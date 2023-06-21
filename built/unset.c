/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:27:22 by msodor            #+#    #+#             */
/*   Updated: 2023/06/21 12:55:39 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_cmd *cmd, t_env **env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (cmd->args[i])
	{
		tmp = (*env)->next;
		if (!is_correct(cmd->args[i]))
			i++;
		else
		{
			while (tmp)
			{
				if (!ft_strncmp(cmd->args[i], tmp->key, \
				ft_strlen(cmd->args[i]) + 1))
				{
					env_del(env, tmp);
					break ;
				}
				tmp = tmp->next;
			}
			i++;
		}
	}
}
