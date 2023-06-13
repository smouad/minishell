/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:42:00 by msodor            #+#    #+#             */
/*   Updated: 2023/06/13 13:25:49 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	array_sise(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**resize_env(char **env)
{
	char	**new_env;
	int		size;
	int		i;

	size = array_sise(env) + 1;
	new_env = (char **)malloc(size * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while(env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (new_env);
}

int	exist(char *var, char **env)
{
	int len;
	int i;

	len = 0;
	while (var[len] && var[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], len) == 0)
		return (i);
		i++;
	}
	return 0;
}
void	ft_export(t_cmd *cmd, char **env)
{
	int pos;
	int	i;

	if (cmd->args[0] && !cmd->args[1])
	{
		pos = exist(cmd->args[0], env);
		if (pos)
		{
			free(env[pos]);
			env[pos] = ft_strdup(cmd->args[0]);
		}
		else
		{
			while (env[i])
				free(env[i++]);
			free(env);
			env = resize_env
		}
	}
}
