/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:27:23 by msodor            #+#    #+#             */
/*   Updated: 2023/06/21 19:48:02 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*command;
	t_elems		*elems;
	t_parser	*parser;
	t_env		*env_lst;

	(void)av;
	parser = malloc(sizeof(t_parser));
	if (ac != 1 || !env)
		return (1);
	env_lst = get_env(env);
	while (1)
	{
		command = readline(CYAN"minishell"RESET MAGENTA"[$]~>:"RESET);
		if (command == NULL)
			break ;
		if (ft_strlen(command) > 0)
			add_history(command);
		elems = analyser(command, env_lst);
		if (!elems || !elems->next)
			continue ;
		init_parser(elems, parser);
		builtins(parser->cmds, env_lst);
	}
}
