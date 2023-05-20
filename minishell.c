/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:27:23 by msodor            #+#    #+#             */
/*   Updated: 2023/05/20 20:14:45 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_hundler(int sig)
{
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

char	*ft_get_command(char *str, t_command *cmd)
{
	int	single_quote_counter;
	int	double_quote_counter;
	int	len;
	int i = 0;
	int j = 0;

	single_quote_counter = 0;
	double_quote_counter = 0;
	while (*str)
	{
		if (*str == '\"')
			double_quote_counter++;
		if (*str == '\'')
			single_quote_counter++;
		*str++;
	}
	if (double_quote_counter % 2 != 0 || single_quote_counter % 2 != 0)
		return (NULL);
	len = ft_strlen(str) - (single_quote_counter + double_quote_counter) + 1;
	cmd->command = malloc(len);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			cmd->command[j] = str[i];
			j++;
		}
		i++;
	}
}

char	**ft_command_line(char *line, t_command *cmd)
{
	char	**cmd_line;

	cmd_line = ft_split(line, 32)
	ft_get_command()
	return ();
}

int	ft_check_command(char **command_line)
{
	if (ft_strncmp(command_line[0], "echo", ft_strlen(command_line[0])) == 0)
		return (1);
	return (0);
}

int	ft_check_option(char **command_line)
{
	if (ft_strncmp(command_line[1], "-n", ft_strlen(command_line[1])) == 0)
		return (1);
	return (0);
}

int	main(void)
{
	char	*command;
	char	**command_line;

	while (1)
	{
		signal(SIGINT, signal_hundler);
		command = readline("minishell$>: ");
		if (command == NULL)
			break ;
		if (strlen(command) > 0)
			add_history(command);
		command_line = ft_command_line(command);
		if (ft_check_command(command_line) == 1)
		{
			if (ft_check_option(command_line) == 1)
				ft_echo(ft_strtrim(command_line[2], "\""), 1);
			ft_echo(ft_strtrim(command_line[1], "\""), 0);
		}
	}
}
