/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:27:23 by msodor            #+#    #+#             */
/*   Updated: 2023/06/09 11:27:25 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	char		*command;
	t_elems		*elems;
	t_parser	*parser;

	while (1)
	{
		command = readline(CYAN"minishell"RESET MAGENTA"[$]~>:"RESET);
		if (command == NULL)
			break ;
		if (strlen(command) > 0)
			add_history(command);
		if (analyser(command) != NULL)
		{
			elems = analyser(command);
		}
		parser = init_cmds(elems);
		set_redir(parser, elems);
		set_env(elems);
		set_cmd_args(parser, elems);
		// int i;
		// while (parser->cmds)
		// {
		// 	i = 0;
		// 	printf("command ==========================");
		// 	printf("cmd ====> %s\n", parser->cmds->cmd);
		// 	while(parser->cmds->args[i] && i < parser->cmds->argc)
		// 	{
		// 		printf("arg%d ====> %s\n", i, parser->cmds->args[i]);
		// 		i++;
		// 	}
		// 	parser->cmds = parser->cmds->next;
		// }
		print_table(elems);
	}
}
