/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:31:44 by msodor            #+#    #+#             */
/*   Updated: 2023/06/12 12:59:47 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	ft_echo(t_cmd *cmds)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (cmds->args[i] && is_option(cmds->args[i]) == 0)
	{
		trigger = 1;
		i++;
	}
	while (cmds->args[i])
	{
		printf("%s", cmds->args[i]);
		i++;
		if (cmds->args[i] != NULL && cmds->args[i][0])
			printf(" ");
	}
	if (trigger != 1)
		printf("\n");
}
