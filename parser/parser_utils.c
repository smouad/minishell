/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:53:37 by msodor            #+#    #+#             */
/*   Updated: 2023/06/21 19:47:25 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_nbr(t_elems *elems, t_parser *parser)
{
	parser->cmds = NULL;
	parser->cmd_nbr = 1;
	while (elems)
	{
		if (elems->type == PIPE)
			parser->cmd_nbr++;
		elems = elems->next;
	}
}

void	init_cmds(t_elems *elems, t_parser *parser)
{
	int			i;
	int			argc;
	t_cmd		**cms;

	cmd_nbr(elems, parser);
	i = 0;
	while (i++ < parser->cmd_nbr)
	{
		argc = 0;
		elems = elems->next;
		while (elems && elems->type != PIPE && argc++ >= 0)
		{
			if (is_redir(elems))
			{
				elems = elems->next->next;
				continue ;
			}
			elems = elems->next;
		}
		cms = &parser->cmds;
		cmd_list_add(cms, cmd_new(NULL, argc));
	}
}

void	rm_redir(t_elems **elems)
{
	t_elems	*current;
	t_elems	*tmp;

	current = *elems;
	tmp = NULL;
	while (current)
	{
		if (is_redir(current))
		{
			tmp = current->next->next;
			token_del(elems, current->next);
			token_del(elems, current);
			current = tmp;
		}
		else
			current = current->next;
	}
}

void	set_redir(t_parser *parser, t_elems *elems)
{
	t_elems	*current;
	t_redir	*new_redir;
	t_cmd	*cmds;

	current = elems;
	cmds = parser->cmds;
	while (cmds)
	{
		current = current->next;
		while (current && current->type != PIPE)
		{
			if (is_redir(current))
			{
				new_redir = redir_new(current->next->content, current->type);
				redir_add(&cmds->redir, new_redir);
				current = current->next->next;
				continue ;
			}
			current = current->next;
		}
		cmds = cmds->next;
	}
	rm_redir(&elems);
}
