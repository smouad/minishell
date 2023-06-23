/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:43:47 by msodor            #+#    #+#             */
/*   Updated: 2023/06/23 15:18:23 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_path(char *cmd)
{
	if (cmd[0] == '/')
		return (1);
	return (0);
}

char	**get_path(t_env *env)
{
	env = env->next;
	while (env)
	{
		if (!ft_strcmp("PATH", env->key))
		{
			return (ft_split(env->value, ':'));
			break ;
		}
		env = env->next;
	}
	return (NULL);
}

int	list_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**list_to_array(t_env *env)
{
	int		i;
	int		l_size;
	char	**array;

	l_size = list_size(env);
	array = (char **)malloc(l_size * sizeof(char *));
	env = env->next;
	i = 0;
	while (env && i < l_size)
	{
		array[i] = ft_strjoin(env->key, "=");
		array[i] = ft_strjoin(array[i], env->value);
		i++;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}

void	exec_cmd(t_parser *parser)
{
	char	*cmd_path;
	char	**env;
	char	**path;
	int		id;
	int		i;

	env = list_to_array(parser->env);
	path = get_path(parser->env);
	id = fork();
	if (id == 0)
	{
		i = 0;
		while (path[i])
		{
			cmd_path = ft_strjoin(path[i], ft_strjoin("/", parser->cmds->cmd));
			execve(cmd_path, parser->cmds->full_cmd, env);
			i++;
		}
		printf("minishell: %s: command not found\n", parser->cmds->cmd);
		exit(127);
	}
	waitpid(id, NULL, 0);
}
