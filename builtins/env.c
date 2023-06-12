/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:30:40 by msodor            #+#    #+#             */
/*   Updated: 2023/06/12 20:50:39 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_cmd *cmd, char **env)
{
	int	i;

	i = 0;
	if (cmd->args[0] == NULL)
	{
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
	else
		printf("minishell: env: Too many arguments.\n");
}