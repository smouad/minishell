/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:30:12 by msodor            #+#    #+#             */
/*   Updated: 2023/06/23 00:12:13 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtins(t_cmd *cmd, t_parser *parser)
{
	if (cmd->cmd != NULL && parser->env)
	{
		if (!ft_strcmp(cmd->cmd, "echo"))
			ft_echo(parser);
		else if (!ft_strcmp(cmd->cmd, "env"))
			ft_env(cmd, parser);
		else if (!ft_strcmp(cmd->cmd, "pwd"))
			ft_pwd(parser);
		else if (!ft_strcmp(cmd->cmd, "cd"))
			ft_cd(cmd, parser);
		else if (!ft_strcmp(cmd->cmd, "export"))
			ft_export(cmd, parser);
		else if (!ft_strcmp(cmd->cmd, "unset"))
			ft_unset(cmd, parser);
		// else if (!ft_strcmp(cmd->cmd, "exit"))
		// 	ft_exit(cmd);
		// else
		// 	exec_cmd(cmd, parser);
	}
}
