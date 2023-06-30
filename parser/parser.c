/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 00:01:56 by msodor            #+#    #+#             */
/*   Updated: 2023/06/30 13:45:48 by msodor           ###   ########.fr       */
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
				return (ft_strdup(env->value));
			else
				break ;
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

void	set_env(t_elems *elems, t_parser *parser)
{
	char	*value;

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
			else
			{
				value = turn_env(elems->content + 1, parser->env);
				free(elems->content);
				if (value)
					elems->content = ft_strdup(value);
				else
					elems->content = ft_strdup("");
			}
		}
		elems = elems->next;
	}
}


void	set_cmd_args(t_parser *parser, t_elems *elems)
{
	t_cmd	*cmds;

	cmds = parser->cmds;
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
				cmds->full_cmd[i] = ft_strdup(elems->content);
				elems = elems->next;
			}
			if (elems && elems->type != PIPE)
			{
				cmds->args[i] = ft_strdup(elems->content);
				cmds->full_cmd[++i] = ft_strdup(elems->content);
				elems = elems->next;
			}
		}
		cmds->args[i] = NULL;
		cmds->full_cmd[i + 1] = NULL;
		cmds = cmds->next;
	}
	token_list_free(elems);
}

void	init_parser(t_elems *elems, t_parser *parser)
{
	init_cmds(elems, parser);
	set_redir(parser, elems);
	set_cmd_args(parser, elems);
}
