/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:54:58 by msodor            #+#    #+#             */
/*   Updated: 2023/07/03 15:58:46 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	put_error(char *cmd, char *error)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

char	*get_cmd_path(t_parser *parser)
{
	t_cmd		*cmd;
	struct stat	buf;

	cmd = parser->cmds;
	if (is_file(cmd->cmd))
	{
		if (access(cmd->cmd, F_OK) == 0 && stat(cmd->cmd, &buf) == 0)
		{
			if (access(cmd->cmd, X_OK) == -1)
			{
				put_error(cmd->cmd, ": Permission denied");
				return (parser->exit_s = 126, NULL);
			}
			if (S_ISDIR(buf.st_mode))
			{
				put_error(cmd->cmd, ": is a directory");
				return (parser->exit_s = 126, NULL);
			}
			return (cmd->cmd);
		}
		put_error(cmd->cmd, ": No such file or directory");
		return (parser->exit_s = 127, NULL);
	}
	return (if_not_path(parser));
}

char	*if_not_path(t_parser *parser)
{
	char	*cmd_path;
	char	**path;
	char	*cmd_file;
	int		i;

	path = get_path(parser->env);
	i = 0;
	while (path[i])
	{
		cmd_file = ft_strjoin("/", parser->cmds->cmd);
		cmd_path = ft_strjoin(path[i], cmd_file);
		free(cmd_file);
		if (access(cmd_path, F_OK) == 0)
		{
			free_array(path);
			free(cmd_path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_array(path);
	put_error(parser->cmds->cmd, ": command not found");
	parser->exit_s = 127;
	return (NULL);
}

void	exec_cmd(t_parser *parser)
{
	char	**env;
	int		status;
	int		id;

	env = list_to_array(parser->env);
	if (!get_cmd_path(parser))
	{
		free_array(env);
		return ;
	}
	id = fork();
	if (id == 0)
	{
		execve(get_cmd_path(parser), parser->cmds->full_cmd, env);
		free_array(env);
		parser->exit_s = 0;
		exit(parser->exit_s);
	}
	waitpid(id, &status, 0);
	parser->exit_s = WEXITSTATUS(status);
	if (id == 0)
		exit(parser->exit_s);
	free_array(env);
}
