/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:44:03 by msodor            #+#    #+#             */
/*   Updated: 2023/06/23 17:35:52 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	arg_not_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			printf("exit\n");
			printf("minishell: exit: numeric argument required\n");
			return (1);	
		}
		i++;
	}
	return (0);
}

void	ft_exit(t_parser *parser)
{
	if (!parser->cmds->args[0])
	{
		printf("exit\n");
		parser->exit_s = 0;
	}
	else
	{
		if (arg_not_digit(parser->cmds->args[0]))
			parser->exit_s = 255;
		else if (parser->cmds->args[1])
		{
			printf("exit\n");
			printf("minishell: exit: too many arguments\n");
			parser->exit_s = 1;
			return ;
		}
		else
			parser->exit_s = ft_atoi(parser->cmds->args[0]);
	}
	exit(parser->exit_s);
}
