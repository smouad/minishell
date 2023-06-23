/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:44:03 by msodor            #+#    #+#             */
/*   Updated: 2023/06/23 13:42:37 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_cmd *cmd, t_parser *parser)
{
	int	i;
	int	trig;

	i = 0;
	trig = 0;
	if (cmd->args[1] != NULL)
	{
		if (cmd->args[2] != NULL)
		{
			printf("exit\n");
			printf("minishell: exit: too many arguments\n");
			parser->exit_s = 1;
			return ;
		}
		while (cmd->args[1][i++])
			if (!ft_isdigit(cmd->args[1][i]))
				trig = 1;
		if (trig == 1)
			printf("minishell: exit: numeric argument required\n");
		else
			parser->exit_s = ft_atoi(cmd->args[1]);
	}
	else
		parser->exit_s = 0;
}
