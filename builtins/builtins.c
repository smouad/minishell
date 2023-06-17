/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:30:12 by msodor            #+#    #+#             */
/*   Updated: 2023/06/17 17:57:01 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtins(t_cmd *cmds, t_env *env)
{
	if (cmds->cmd[0] && env)
	{
		if (!ft_strncmp(cmds->cmd, "echo", ft_strlen(cmds->cmd) + 1))
			ft_echo(cmds);
		else if (!ft_strncmp(cmds->cmd, "env", ft_strlen(cmds->cmd) + 1))
			ft_env(cmds, env);
		else if (!ft_strncmp(cmds->cmd, "pwd", ft_strlen(cmds->cmd) + 1))
			ft_pwd(cmds);
		else if (!ft_strncmp(cmds->cmd, "cd", ft_strlen(cmds->cmd) + 1))
			ft_cd(cmds);
		else if (!ft_strncmp(cmds->cmd, "export", ft_strlen(cmds->cmd) + 1))
			ft_export(cmds, env);
		else if (!ft_strncmp(cmds->cmd, "unset", ft_strlen(cmds->cmd) + 1))
			ft_unset(cmds, &env);
	}
}
