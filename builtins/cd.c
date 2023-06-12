/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:37:40 by msodor            #+#    #+#             */
/*   Updated: 2023/06/12 22:30:21 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_cmd *cmd)
{
	if (!cmd->args[0])
		return ;
	if (cmd->args[0] && !cmd->args[1])
	{
		if (chdir(cmd->args[0]) != 0)
			printf("cd: no such file or directory: %s\n", cmd->args[0]);
	}
	else
		printf("cd: string not in pwd: %s\n", cmd->args[0]);
}
