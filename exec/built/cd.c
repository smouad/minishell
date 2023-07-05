/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:37:40 by msodor            #+#    #+#             */
/*   Updated: 2023/07/05 12:50:22 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * get_wd_env - retrieves the current working directory and
 * creates an environment variable string
 * Return: The environment variable string representing
 * the current working directory (PWD=cwd)
 */
char	*get_wd_env(void)
{
	char	*cwd_env;
	char	cwd[1024];

	getcwd(cwd, 1024);
	cwd_env = ft_strjoin("PWD=", cwd);
	return (cwd_env);
}

/**
 * go_home - function that changes the current directory to the home directory
 * and updates the environment variables (PWD and OLDPWD)
 * @env: A pointer to the environment structure
 * Return: void
 */
void	go_home(t_env *env)
{
	char	cwd[1024];
	char	*owd;
	char	**home;
	char	*env_cwd;

	getcwd(cwd, 1024);
	owd = ft_strjoin("OLDPWD=", cwd);
	home = turn_env("HOME", env);
	if (chdir(home[0]) == 0)
	{
		env_cwd = get_wd_env();
		set_value(env_cwd, env);
		set_value(owd, env);
		free(env_cwd);
	}
	free(owd);
	free_array(home);
}

/**
 * cd_put_error - function that outputs an error message for the cd command
 * @str: The argument that caused the error
 * @parser: A pointer to the parser structure
 * Return: void
 */
void	cd_put_error(char *str, t_parser *parser)
{
	write(2, "cd: ", 4);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, "No such file or directory\n", 26);
	parser->exit_s = 1;
}

/**
 * ft_cd - function that handles the "cd" command to change the current directory
 * @cmd: A pointer to the command structure containing the command arguments
 * @parser: A pointer to the parser structure
 */
void	ft_cd(t_cmd *cmd, t_parser *parser)
{
	char	cwd[1024];
	char	*owd;
	char	*env_cwd;

	getcwd(cwd, 1024);
	owd = ft_strjoin("OLDPWD=", cwd);
	if (!cmd->args[0])
		go_home(parser->env);
	else
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
			cd_put_error(cmd->args[0], parser);
		free(owd);
	}
}
