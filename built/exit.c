/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:44:03 by msodor            #+#    #+#             */
/*   Updated: 2023/06/20 15:16:20 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_cmd *cmd)
{
	if (!cmd->args[0])
	{
		printf("exit\n");
		exit(0);
	}
	printf("exit: too many arguments\n");
}
