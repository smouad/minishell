/* ************************************************************************** */
/*	                                                                    */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:47:43 by msodor            #+#    #+#             */
/*   Updated: 2023/07/10 16:00:14 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_pipes(int (*fd)[2], t_parser *parser)
{
	int	i;

	i = 0;
	while (i < parser->cmd_nbr - 1)
	{
		if (pipe(fd[i]))
			return ;
		i++;
	}
}

void	rd_reset(t_cmd *cmds)
{
	if (cmds->redir && cmds->redir->old_infd != -1)
		dup2(cmds->redir->old_infd, STDIN_FILENO);
	if (cmds->redir && cmds->redir->old_outfd != -1)
		dup2(cmds->redir->old_outfd, STDOUT_FILENO);
}

void	exec_util(t_cmd *cmds, t_parser *parser, int (*fd)[2], int *arra)
{
	int	id;

	id = 0;
	while (cmds)
	{
		id = fork();
		if (id == 0)
		{
			if (exec_redir(cmds, parser) != -1)
			{
				if (check_in(cmds->redir))
					cmds->redir->old_infd = dup(STDIN_FILENO);
				if (check_out(cmds->redir))
					cmds->redir->old_outfd = dup(STDOUT_FILENO);
				builtins(cmds, parser, fd);
				rd_reset(cmds);
			}
			exit(1);
		}
		else
			arra[cmds->index] = id;
		cmds = cmds->next;
	}
	close_pipes(fd, parser);
	wait_for_childs(arra, parser);
}

void	extention(t_cmd *cmds)
{
	cmds->redir->old_outfd = dup(STDOUT_FILENO);
	cmds->redir->old_infd = dup(STDIN_FILENO);
}

void	exec_commands(t_parser *parser, t_cmd *cmds)
{
	int	(*fd)[2];
	int	*arra;

	fd = malloc(sizeof(int) * (parser->cmd_nbr * 2));
	arra = malloc(sizeof(int) * parser->cmd_nbr);
	if (parser->cmd_nbr > 1)
		create_pipes(fd, parser);
	if (parser->cmd_nbr == 1)
	{
		if (cmds->redir)
			extention(cmds);
		if (exec_redir(cmds, parser) == -1)
		{
			parser->exit_s = 1;
			rd_reset(cmds);
			return ;
		}
		builtins(cmds, parser, fd);
		rd_reset(cmds);
	}
	else
		exec_util(cmds, parser, fd, arra);
	free(fd);
	free(arra);
}
