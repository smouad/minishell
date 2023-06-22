/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:37:40 by msodor            #+#    #+#             */
/*   Updated: 2023/06/22 23:41:52 by msodor           ###   ########.fr       */
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

void	ft_cd(t_cmd *cmd, t_parser *parser)
{
	char	cwd[1024];
	char	*owd;
	char	*env_cwd;

	getcwd(cwd, 1024);
	owd = ft_strjoin("OLDPWD=", cwd);
	if (!cmd->args[0])
		go_home(parser->env);
	else if (cmd->args[0] && !cmd->args[1])
	{
		if (chdir(cmd->args[0]) == 0)
		{
			env_cwd = get_wd_env();
			set_value(env_cwd, parser->env);
			set_value(owd, parser->env);
			free(env_cwd);
			parser->exit_s = 0;
		}
		else
		{
			printf("cd: no such file or directory: %s\n", cmd->args[0]);
			parser->exit_s = 1;
		}
		free(owd);
	}
	else
	{
		printf("cd: too many arguments\n");
		parser->exit_s = 1;
	}
}
