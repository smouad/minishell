/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:31:44 by msodor            #+#    #+#             */
/*   Updated: 2023/07/10 15:04:28 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * is_option - function that checks if a string is an option
 * @str: The string to check
 * Return: 0 if the string is an option, 1 otherwise
 */
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

/**
 * ft_echo - function that prints the arguments to the standard output
 * @parser: A pointer to the parser structure
 * Return: void
 */
void	ft_echo(t_parser *parser, t_cmd *cmd)
{
	int		i;
	int		trigger;

	i = 0;
	trigger = 0;
	while (cmd->args[i] && is_option(cmd->args[i]) == 0)
	{
		trigger = 1;
		i++;
	}
	while (cmd->args[i])
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		i++;
		if (cmd->args[i] != NULL && cmd->args[i][0])
			write(1, " ", 1);
	}
	if (trigger != 1)
		write(1, "\n", 1);
	parser->exit_s = 0;
}
