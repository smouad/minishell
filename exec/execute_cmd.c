/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:30:12 by msodor            #+#    #+#             */
/*   Updated: 2023/07/14 13:03:38 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipes(int (*fd)[2], t_parser *parser)
{
	int	i;

	i = 0;
	while (i < parser->cmd_nbr - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	redirect_to_pipe(t_cmd *cmd, t_parser *parser, int (*fd)[2])
{
	if (cmd->index == 0)
	{
		if (cmd->redir && cmd->redir->old_outfd != -1)
			return ;
		if (dup2(fd[cmd->index][1], 1) == -1)
			perror("dup2 error");
	}
	else
	{
		if (cmd->index == parser->cmd_nbr - 1)
		{
			if (cmd->redir && cmd->redir->old_infd != -1)
				return ;
			dup2(fd[cmd->index - 1][0], 0);
		}
		else
		{
			if (!cmd->redir || cmd->redir->old_infd == -1)
				dup2(fd[cmd->index - 1][0], 0);
			if (!cmd->redir || cmd->redir->old_outfd == -1)
				dup2(fd[cmd->index][1], 1);
		}
	}
	close_pipes(fd, parser);
}

void	builtins(t_cmd *cmd, t_parser *parser, int (*fd)[2])
{
	if (cmd->cmd != NULL && parser->env)
	{
		if (parser->cmd_nbr > 1)
			redirect_to_pipe(cmd, parser, fd);
		if (!ft_strcmp(cmd->cmd, "echo"))
			ft_echo(parser, cmd);
		else if (!ft_strcmp(cmd->cmd, "env"))
			ft_env(cmd, parser);
		else if (!ft_strcmp(cmd->cmd, "pwd"))
			ft_pwd(parser);
		else if (!ft_strcmp(cmd->cmd, "cd"))
			ft_cd(cmd, parser);
		else if (!ft_strcmp(cmd->cmd, "export"))
			ft_export(cmd, parser);
		else if (!ft_strcmp(cmd->cmd, "unset"))
			ft_unset(cmd, parser);
		else if (!ft_strcmp(cmd->cmd, "exit"))
			ft_exit(parser);
		else
			exec_cmd(parser, cmd);
		if (parser->cmd_nbr > 1)
			exit(parser->exit_s);
	}
}
