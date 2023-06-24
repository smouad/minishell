/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:58:12 by msodor            #+#    #+#             */
/*   Updated: 2023/06/24 13:12:45 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_parser *parser)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024) == NULL)
	{
		printf("minishell: pwd: failed\n");
		parser->exit_s = 1;
	}
	else
	{
		printf("%s\n", cwd);
		parser->exit_s = 0;
	}
}
