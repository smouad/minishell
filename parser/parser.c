/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 00:01:56 by msodor            #+#    #+#             */
/*   Updated: 2023/06/10 01:08:29 by msodor           ###   ########.fr       */
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

void	set_env(t_elems *elems)
{
	char	*value;

	while (elems)
	{
		if (elems->type == VAR)
		{
			value = getenv(elems->content + 1);
			free(elems->content);
			elems->content = NULL;
			if (value)
				elems->content = ft_strdup(value);
			else
				elems->content = ft_strdup("");
		}
		elems = elems->next;
	}
}

void	set_cmd_args(t_parser *parser, t_elems *elems)
{
	t_elems	*current;
	t_cmd	*cmds;
	int		i;

	current = elems;
	cmds = parser->cmds;
	while (cmds)
	{
		current = current->next;
		cmds->cmd = ft_strdup(current->content);
			printf(" +++++ %s ++++++\n"/**/,cmds->cmd);
		current = current->next;
		i = 0;
		while (i < cmds->argc && current && current->type != PIPE)
		{
			printf("========= %d\n", cmds->argc );
			char *mouad = ft_strdup(current->content);
			printf("arg%d ====> %s\n", i/**/,mouad);
			i++;
			current = current->next;
		}
		cmds = cmds->next;
	}
}
