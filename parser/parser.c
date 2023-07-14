/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 00:01:56 by msodor            #+#    #+#             */
/*   Updated: 2023/07/14 14:09:24 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	insert_in(t_elems **elems, char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0)
		{
			free((*elems)->content);
			(*elems)->content = ft_strdup(str[i]);
			(*elems)->type = WORD;
			i++;
			continue ;
		}
		token_list_insert(elems, token_new(" ", 1, _SPACE, DEFAULT));
		token_list_insert(elems, token_new(str[i], \
		ft_strlen(str[i]), WORD, DEFAULT));
		i++;
		*elems = (*elems)->next;
	}
}

void	set_helper(t_elems *elems, t_parser *parser)
{
	char	**value;

	value = turn_env(elems->content + 1, parser->env);
	if (value)
		insert_in(&elems, value);
	else
	{
		free(elems->content);
		elems->content = ft_strdup("");
	}
	free_array(value);
}

void	set_env(t_elems *elems, t_parser *parser)
{
	while (elems)
	{
		if (elems->type == VAR)
		{
			if (ft_strlen(elems->content) == 1)
				return ;
			if (ft_strcmp(elems->content + 1, "?") == 0)
			{
				free(elems->content);
				elems->content = ft_itoa(parser->exit_s);
			}
			else if (ft_isdigit(elems->content[1]))
			{
				free(elems->content);
				elems->content = ft_strdup("");
			}
			else
				set_helper(elems, parser);
		}
		elems = elems->next;
	}
}

void	set_full_cmd(t_cmd *cmds, t_elems *elems)
{
	int	i;

	while (cmds)
	{
		i = 0;
		elems = elems->next;
		while (i < cmds->argc && elems && elems->type != PIPE)
		{
			cmds->full_cmd[i] = ft_strdup(elems->content);
			i++;
			elems = elems->next;
		}
		cmds->full_cmd[i] = NULL;
		cmds = cmds->next;
	}
}

void	set_cmd_args(t_cmd *cmds, t_elems *elems)
{
	int	i;

	while (cmds)
	{
		i = 0;
		elems = elems->next;
		while (i < cmds->argc && elems && elems->type != PIPE)
		{
			if (i == 0)
			{
				cmds->cmd = ft_strdup(elems->content);
				elems = elems->next;
			}
			if (elems && elems->type != PIPE)
			{
				cmds->args[i] = ft_strdup(elems->content);
				i++;
				elems = elems->next;
			}
		}
		cmds->args[i] = NULL;
		cmds = cmds->next;
	}
}
