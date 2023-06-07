/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 00:01:56 by msodor            #+#    #+#             */
/*   Updated: 2023/06/08 00:34:45 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_nbr(t_elems *elems, t_parser *parser)
{
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

	parser = malloc(sizeof(t_parser));
	cmd_nbr(elems, parser);
	i = 0;
	while (i < parser->cmd_nbr)
	{
		argc = 0;
		elems = elems->next;
		while (elems && elems->type != PIPE)
		{
			if (is_redir(elems))
			{
				elems = elems->next->next;
				continue ;
			}
			elems = elems->next;
			argc++;
		}
		cmd_list_add(&parser->cmds, cmd_new(NULL, NULL, NULL, argc));
		printf("%d\n", argc);
		i++;
	}
	return (parser);
}
