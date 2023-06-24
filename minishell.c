/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:27:23 by msodor            #+#    #+#             */
/*   Updated: 2023/06/24 22:26:55 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*command;
	t_elems		*elems;
	t_parser	*parser;

	(void)av;
	parser = malloc(sizeof(t_parser));
	if (ac != 1 || !env)
		return (1);
	parser->env = get_env(env);
	while (1)
	{
		command = readline(CYAN"minishell"RESET MAGENTA"[$]~>:"RESET);
		if (command == NULL)
			break ;
		if (ft_strlen(command) > 0)
			add_history(command);
		elems = analyser(command, parser);
		if (!elems || !elems->next)
			continue ;
		init_parser(elems, parser);
		builtins(parser->cmds, parser);
	}
}
