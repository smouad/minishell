/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:27:23 by msodor            #+#    #+#             */
/*   Updated: 2023/05/22 20:25:22 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_check_command(t_cmdl *cmdl, char *cmd)
{
	if (ft_strncmp(cmdl->command, cmd, ft_strlen(cmdl->command)) == 0)
		return (1);
	return (0);
}

int	ft_check_option(char **command_line)
{
	if (ft_strncmp(command_line[1], "-n", ft_strlen(command_line[1])) == 0)
		return (1);
	return (0);
}

int	main(void)
{
	char	*command;
	char	**command_line;

	while (1)
	{
		command = readline("minishell$>: ");
		if (command == NULL)
			break ;
		if (strlen(command) > 0)
			add_history(command);
		command_line = ft_command_line(command);
		if (ft_check_command(command_line) == 1)
		{
			if (ft_check_option(command_line) == 1)
				ft_echo(ft_strtrim(command_line[2], "\""), 1);
			ft_echo(ft_strtrim(command_line[1], "\""), 0);
		}
	}
}
