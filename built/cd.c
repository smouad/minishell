/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:37:40 by msodor            #+#    #+#             */
/*   Updated: 2023/06/21 16:46:21 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_wd_env(void)
{
	char	*cwd_env;
	char	cwd[1024];

	getcwd(cwd, 1024);
	cwd_env = ft_strjoin("PWD=", cwd);
	return (cwd_env);
}

void	go_home(t_env *env)
{
	char	cwd[1024];
	char	*owd;
	char	*home;
	char	*env_cwd;

	getcwd(cwd, 1024);
	owd = ft_strjoin("OLDPWD=", cwd);
	home = turn_env("HOME", env);
	if (chdir(home) == 0)
	{
		env_cwd = get_wd_env();
		set_value(env_cwd, env);
		set_value(owd, env);
		free(env_cwd);
	}
	free(owd);
	free(home);
}

void	ft_cd(t_cmd *cmd, t_env *env)
{
	char	cwd[1024];
	char	*owd;
	char	*env_cwd;

	getcwd(cwd, 1024);
	owd = ft_strjoin("OLDPWD=", cwd);
	if (!cmd->args[0])
		go_home(env);
	else if (cmd->args[0] && !cmd->args[1])
	{
		if (chdir(cmd->args[0]) == 0)
		{
			env_cwd = get_wd_env();
			set_value(env_cwd, env);
			set_value(owd, env);
			free(env_cwd);
		}
		else
			printf("minishell: cd: no such file or directory: \
			%s\n", cmd->args[0]);
		free(owd);
	}
	else
		printf("minishell: cd: string not in pwd: %s\n", cmd->args[0]);
}
