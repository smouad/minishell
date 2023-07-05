/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:31:44 by msodor            #+#    #+#             */
/*   Updated: 2023/07/03 16:33:45 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-' || ft_strlen(str) == 1)
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo(t_parser *parser)
{
	int		i;
	int		trigger;
	t_cmd	*cmd;

	i = 0;
	cmd = parser->cmds;
	trigger = 0;
	while (cmd->args[i] && is_option(cmd->args[i]) == 0)
	{
		trigger = 1;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		i++;
		if (cmd->args[i] != NULL && cmd->args[i][0])
			printf(" ");
	}
	if (trigger != 1)
		printf("\n");
	parser->exit_s = 0;
}
