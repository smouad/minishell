/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 00:01:56 by msodor            #+#    #+#             */
/*   Updated: 2023/06/19 16:34:37 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*turn_env(char *var, t_env *env)
{
	env = env->next;
	while (env)
	{
		if (!ft_strncmp(var, env->key, ft_strlen(var) + 1))
		{
			if (env->value)
				return (env->value);
			else
				break ;
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

void	set_env(t_elems *elems, t_env *env)
{
	char	*value;

	while (elems)
	{
		if (elems->type == VAR)
		{
			value = turn_env(elems->content + 1, env);
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
		i = 0;
		current = current->next;
		cmds->cmd = ft_strdup(current->content);
		cmds->full_cmd[i] = ft_strdup(current->content);
		current = current->next;
		while (i < cmds->argc && current && current->type != PIPE)
		{
			cmds->args[i] = ft_strdup(current->content);
			cmds->full_cmd[i + 1] = ft_strdup(current->content);
			i++;
			current = current->next;
		}
		cmds->args[i] = NULL;
		cmds->full_cmd[i + 1] = NULL;
		cmds = cmds->next;
	}
	token_list_free(elems);
}

t_parser	*init_parser(t_elems *elems)
{
	t_parser	*parser;

	parser = init_cmds(elems);
	set_redir(parser, elems);
	set_cmd_args(parser, elems);
	return (parser);
}
