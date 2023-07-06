/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:27:23 by msodor            #+#    #+#             */
/*   Updated: 2023/07/06 15:48:58 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	prinsipal(t_parser *parser)
{
	t_elems		*elems;
	char		*command;

	while (1)
	{
		command = readline(CYAN"minishell"RESET MAGENTA"[$]~>:"RESET);
		if (command == NULL)
			break ;
		if (command[0] == 0)
		{
			free(command);
			continue ;
		}
		if (ft_strlen(command) > 0)
			add_history(command);
		elems = analyser(command, parser);
		free(command);
		if (!elems || !elems->next)
			continue ;
		init_parser(elems, parser);
		token_list_free(elems);
		builtins(parser->cmds, parser);
		free_cmd_list(parser->cmds);
	}
}

int	main(int ac, char **av, char **env)
{
	t_parser	*parser;

	(void)av;
	parser = malloc(sizeof(t_parser));
	if (ac != 1 || !env)
		return (1);
	parser->env = get_env(env);
	prinsipal(parser);
	free_env_list(parser->env);
	free(parser);
}
