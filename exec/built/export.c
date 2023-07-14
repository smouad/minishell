/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:42:00 by msodor            #+#    #+#             */
/*   Updated: 2023/07/14 13:25:57 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * is_correct - checks if a word is a valid identifier for the export command
 * @word: The word to be checked
 * Return: 1 if the word is a valid identifier, 0 otherwise
 */
int	is_correct(char *word)
{
	int	i;

	i = 0;
	if (!ft_isalpha(word[i]) && word[i] != '_')
	{
		write(2, "minishell: `", 12);
		write(2, word, ft_strlen(word));
		write(2, "': not a valid identifier\n", 26);
		return (0);
	}
	i++;
	while (word[i] && word[i] != '=')
	{
		if (!ft_isalnum(word[i]) && word[i] != '_')
		{
			write(2, "minishell: `", 12);
			write(2, word, ft_strlen(word));
			write(2, "': not a valid identifier\n", 26);
			return (0);
		}
		i++;
	}
	return (1);
}

void	print_value(char *value)
{
	int		i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\"' || value[i] == '$')
			write(1, "\\", 1);
		write(1, &value[i], 1);
		i++;
	}
}

/**
 * print_export - prints the export command for each environment variable
 * @env: A pointer to the head of the environment variable linked list
 * Return: void
 */
void	print_export(t_env *env)
{
	while (env && env->next)
	{
		env = env->next;
		if (env->value)
		{
			write(1, "declare -x ", 11);
			write(1, env->key, ft_strlen(env->key));
			write(1, "=\"", 2);
			print_value(env->value);
			write(1, "\"\n", 2);
		}
		else
		{
			write(1, "declare -x ", 11);
			write(1, env->key, ft_strlen(env->key));
			write(1, "\n", 1);
		}
	}
}

/**
 * ft_export - function that handles the export command
 * @cmd: A pointer to the command structure
 * @parser: A pointer to the parser structure
 * Return: void
 */
void	ft_export(t_cmd *cmd, t_parser *parser)
{
	int		i;
	int		trig;

	trig = 0;
	if (!cmd->args[0])
	{
		print_export(parser->env);
		parser->exit_s = 0;
	}
	i = 0;
	while (cmd->args[i])
	{
		if (!is_correct(cmd->args[i]))
		{
			trig = 1;
			i++;
		}
		else
		{
			set_value(cmd->args[i], parser->env);
			i++;
		}
		parser->exit_s = trig;
	}
}
