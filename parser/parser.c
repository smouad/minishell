/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 00:01:56 by msodor            #+#    #+#             */
/*   Updated: 2023/06/04 22:00:24 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_nbr(t_elems *elems)
{
	t_parser *parser = malloc(sizeof(t_parser));
	parser->cmd_nbr = 1;
	while (elems)
	{
		if (elems->type == PIPE)
			parser->cmd_nbr++;
		elems = elems->next;
	}
}

void	args_nbr(t_elems *elems, int i)
{
	int	j;

	j = 0;
	parser.cmds[i]->argc = 0;
	while (elems && elems->type != PIPE)
	{
		if (elems->type == REDIR_IN || elems->type == REDIR_OUT 
		|| elems->type == AREDIR_OUT || elems->type == HERE_DOC)
		{
			if (elems->type == REDIR_IN)
				parser.redir[j]->type = REDIR_IN;
			if (elems->type == REDIR_OUT)
				parser.redir[j]->type = REDIR_OUT;
			if (elems->type == HERE_DOC)
				parser.redir[j]->type = HERE_DOC;
			if (elems->type == AREDIR_OUT)
				parser.redir[j]->type = AREDIR_OUT;
			else
				parser.redir[j]->fd = ft_strdup(elems->next->content);
			elems = elems->next;
			j++;
		}
		else
			parser.cmds[i]->argc++;
		elems = elems->next;
	}
}

void	fill_cmds(t_elems *elems, t_parser *parser)
{
	while (i < parser->cmd_nbr)
	{
		elems = elems->next;
		while (elems->type != PIPE)
		{
			if 
		}
	}
}

t_parser	*parser(t_elems *elems)
{
	t_parser	parser[1];
	t_cmd		*cmds;

	cmd_nbr(elems);
	cmds = malloc(sizeof(t_cmd) * parser->cmd_nbr);

}