/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:27:22 by msodor            #+#    #+#             */
/*   Updated: 2023/06/17 10:54:19 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_cmd *cmd, t_env **env)
{
	int i = 0;

	while (cmd->args[i])
	{
		t_env *tmp = (*env)->next;
		while (tmp)
		{
			if (!ft_strncmp(cmd->args[i], tmp->key, ft_strlen(cmd->args[i]) + 1))
			{
				env_del(env, tmp);
				break;
			}
			tmp = tmp->next;
		}
		i++;
	}
}
