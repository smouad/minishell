/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:30:12 by msodor            #+#    #+#             */
/*   Updated: 2023/06/20 14:48:46 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtins(t_cmd *cmds, t_env *env)
{
	if (cmds->cmd != NULL && env)
	{
		if (!ft_strcmp(cmds->cmd, "echo"))
			ft_echo(cmds);
		else if (!ft_strcmp(cmds->cmd, "env"))
			ft_env(cmds, env);
		else if (!ft_strcmp(cmds->cmd, "pwd"))
			ft_pwd(cmds);
		else if (!ft_strcmp(cmds->cmd, "cd"))
			ft_cd(cmds);
		else if (!ft_strcmp(cmds->cmd, "export"))
			ft_export(cmds, env);
		else if (!ft_strcmp(cmds->cmd, "unset"))
			ft_unset(cmds, &env);
		else if (!ft_strcmp(cmds->cmd, "exit"))
			ft_exit();
		else
			exec_cmd(cmds, env);
	}
}
