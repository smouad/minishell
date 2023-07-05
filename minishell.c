/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:27:23 by msodor            #+#    #+#             */
/*   Updated: 2023/07/05 13:55:20 by msodor           ###   ########.fr       */
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
		if (ft_strlen(command) > 0)
			add_history(command);
		elems = analyser(command, parser);
		free(command);
		if (!elems || !elems->next)
			continue ;
		init_parser(elems, parser);
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
}
