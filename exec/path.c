/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:43:47 by msodor            #+#    #+#             */
/*   Updated: 2023/06/21 17:09:45 by msodor           ###   ########.fr       */
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

void	exec_cmd(t_cmd *cmd, t_env *env_list)
{
	char	*cmd_path;
	char	**env;
	char	**path;
	int		id;
	int		i;

	env = list_to_array(env_list);
	path = get_path(env_list);
	id = fork();
	if (id == 0)
	{
		i = 0;
		while (path[i])
		{
			cmd_path = ft_strjoin(path[i], ft_strjoin("/", cmd->cmd));
			execve(cmd_path, cmd->full_cmd, env);
			i++;
		}
		printf("minishell: %s: command not found\n", cmd->cmd);
		exit(127);
	}
	waitpid(id, NULL, 0);
}
