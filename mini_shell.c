/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:27:23 by msodor            #+#    #+#             */
/*   Updated: 2023/05/19 22:49:33 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	signal_hundler(int sig)
{
	printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int	main()
{
		char *command;

	while (1)
	{
		signal(SIGINT, signal_hundler);
		command = readline("mini_shell$>: ");
		if (command == NULL)
		{
			// printf("\n");
			break;
		}
		if (strlen(command) > 0)
			add_history(command);
	}
}