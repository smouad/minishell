/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:47:43 by msodor            #+#    #+#             */
/*   Updated: 2023/07/07 18:39:17 by msodor           ###   ########.fr       */
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

void	wait_for_childs(int *arra, t_parser *parser)
{
	int	i;
	int	status;

	i = 0;
	while (i < parser->cmd_nbr)
	{
		waitpid(arra[i], &status, 0);
		i++;
	}
	parser->exit_s = WEXITSTATUS(status);
}

void	exec_commands(t_parser *parser)
{
	t_cmd	*cmds;
	int		fd[parser->cmd_nbr][2];
	int		arra[parser->cmd_nbr];
	int		id;

	cmds = parser->cmds;
	if (parser->cmd_nbr > 1)
		create_pipes(fd, parser);
	if (parser->cmd_nbr == 1)
		builtins(cmds, parser, fd);
	else
	{
		while (cmds)
		{
			id = fork();
			if (id == 0)
				builtins(cmds, parser, fd);
			else
				arra[cmds->index] = id;
			cmds = cmds->next;
		}
		close_pipes(fd, parser);
		wait_for_childs(arra, parser);
	}
}
