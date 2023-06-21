/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:58:12 by msodor            #+#    #+#             */
/*   Updated: 2023/06/17 17:59:01 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	char	cwd[1024];

	if (cmd->args[0] == NULL)
	{
		if (getcwd(cwd, 1024) == NULL)
			printf("pwd: failed\n");
		printf("%s\n", cwd);
	}
	else
		printf("minishell: pwd: Too many arguments.\n");
}
