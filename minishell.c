/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:27:23 by msodor            #+#    #+#             */
/*   Updated: 2023/06/08 19:46:31 by msodor           ###   ########.fr       */
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
			print_table(elems);
		}
		parser = init_cmds(elems);
		set_redir(parser, elems);
		// t_redir *redir = parser->cmds->redir;
		// while (khalil)
		// {
		// printf("%s", parser->cmds->next->redir->file);
			// while (khalil->redir)
			// {
			// 	printf("|%d| |%s|\n", khalil->redir->type, khalil->redir->file);
			// 	khalil->redir = khalil->redir->next;
			// }
			// khalil = khalil->next;
		// }
		// while (khalil)
		// {
		// 	printf("%s", khalil->redir->file);
		// 	khalil = khalil->next;
		// }
	}
}
