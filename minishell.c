/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:27:23 by msodor            #+#    #+#             */
/*   Updated: 2023/05/25 23:02:52 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	char	*command;
	char	**command_line;

	while (1)
	{
		command = readline("minishell$>: ");
		if (command == NULL)
			break ;
		if (strlen(command) > 0)
			add_history(command);
		print_table(lexer(command));
		// closed_quotes(lexer(command));
		// redir_syntax(lexer(command));

	}
}
