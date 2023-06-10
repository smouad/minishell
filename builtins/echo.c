/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:31:44 by msodor            #+#    #+#             */
/*   Updated: 2023/06/10 19:57:53 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
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
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (parser->cmds->args[i] && is_option(parser->cmds->args[i]))
	{
		trigger = 1;
		i++;
	}
	while (parser->cmds->args[i])
	{
		printf("%s", parser->cmds->args[i]);
		i++;
		if (parser->cmds->args[i] != NULL)
			printf(" ");
	}
	if (trigger != 1)
		printf("\n");
}
