/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:27:23 by msodor            #+#    #+#             */
/*   Updated: 2023/06/14 20:10:20 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*command;
	t_elems		*elems;
	t_parser	*parser;

	(void)av;
	if (ac != 1 || !env)
		return (1);
	while (1)
	{
		command = readline(CYAN"minishell"RESET MAGENTA"[$]~>:"RESET);
		if (command == NULL)
			break ;
		if (strlen(command) > 0)
			add_history(command);
		elems = analyser(command);
		if (elems == NULL)
			continue ;
		parser = init_parser(elems);
		t_env *env_list = get_env(env);
		while (env_list && env_list->next)
		{
			env_list = env_list->next;
			printf("%s=%s\n", env_list->key, env_list->value);
		}
		// builtins(parser->cmds, env_list);
	}
}
