/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:27:23 by msodor            #+#    #+#             */
/*   Updated: 2023/07/14 16:16:37 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_parser	g_parser;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_parser.exit_s = 1;
	}
}

void	ctrl_d(t_parser *parser)
{
	write(1, "\n", 1);
	exit(parser->exit_s);
}

void	prinsipal(t_parser *parser)
{
	t_elems		*elems;
	char		*command;

	while (1)
	{
		command = readline("minishell[$]~>: ");
		if (command == NULL)
			ctrl_d(parser);
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
		exec_commands(parser, parser->cmds);
		free_cmd_list(parser->cmds);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1 || !env)
		return (1);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	g_parser.env = get_env(env);
	g_parser.exit_s = 0;
	prinsipal(&g_parser);
	free_env_list(g_parser.env);
}
