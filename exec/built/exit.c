/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:44:03 by msodor            #+#    #+#             */
/*   Updated: 2023/07/05 12:57:50 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * arg_not_digit - function that checks if an argument is not a numeric digit
 * @arg: The argument to be checked
 * Return: 1 if the argument is not a numeric digit, 0 otherwise
 */
int	arg_not_digit(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			printf("exit\n");
			write(2, "exit: ", 6);
			write(2, arg, ft_strlen(arg));
			write(2, ": numeric argument required\n", 28);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * ft_exit - function that handles the exit command
 * @parser: A pointer to the parser structure
 * Return: void
 */
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
			write(2, "exit: ", 6);
			write(2, "too many arguments\n", 19);
			parser->exit_s = 1;
			return ;
		}
		else
			parser->exit_s = ft_atoi(parser->cmds->args[0]);
	}
	free_parser(parser);
	exit(parser->exit_s);
}
