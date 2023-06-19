/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:30:12 by msodor            #+#    #+#             */
/*   Updated: 2023/06/19 18:33:14 by khaimer          ###   ########.fr       */
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
		else
			exec_cmd(cmds, env);
	}
}
