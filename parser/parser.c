/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 00:01:56 by msodor            #+#    #+#             */
/*   Updated: 2023/06/08 19:50:18 by msodor           ###   ########.fr       */
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

t_parser	*init_cmds(t_elems *elems)
{
	t_parser	*parser;
	int			i;
	int			argc;
	t_cmd		**cms;

	parser = malloc(sizeof(t_parser));
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
		cmd_list_add(cms, cmd_new(NULL, NULL, NULL, argc));
	}
	return (parser);
}

void set_redir(t_parser *parser, t_elems *elems)
{
	t_elems *current = elems;
	t_redir *new_redir;
	t_cmd *cmds;

	cmds = parser->cmds;
	while (cmds)
	{
		while (current && current->next && current->type != PIPE)
		{
			if (is_redir(current))
			{
				new_redir = redir_new(current->next->content, current->type);
				redir_add(&cmds->redir, new_redir);
				current = current->next->next;
			}
				printf("%s\n", cmds->redir->file);
			current = current->next;
		}
		current = current->next;
		cmds = cmds->next;
		printf("---------------\n");
	}
}


