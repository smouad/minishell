/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:58:12 by msodor            #+#    #+#             */
/*   Updated: 2023/07/10 15:40:59 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ft_pwd - function that prints the current working directory
 * @parser: A pointer to the parser structure
 * Return: void
 */
void	ft_pwd(t_parser *parser)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		write(2, "minishell: pwd: failed\n", 23);
		parser->exit_s = 1;
	}
	else
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		parser->exit_s = 0;
	}
}
