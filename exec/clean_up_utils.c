/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:29:24 by msodor            #+#    #+#             */
/*   Updated: 2023/06/24 00:31:13 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_redir(t_redir *redir)
{
	free(redir->file);
	free(redir);
}

void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free_redir(tmp);
	}
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	free(cmd->cmd);
	free_array(cmd->args);
	free_array(cmd->full_cmd);
	free_redir_list(cmd->redir);
	free(cmd);
}
void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_cmd(tmp);
	}
}

void	free_parser(t_parser *parser)
{
	free_env_list(parser->env);
	free_cmd_list(parser->cmds);
	free(parser);
}

