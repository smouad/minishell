/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:42:00 by msodor            #+#    #+#             */
/*   Updated: 2023/07/11 21:14:14 by msodor           ###   ########.fr       */
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

char	*get_key(char *var)
{
	int		i;
	char	*key;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	key = ft_substr(var, 0, i);
	return (key);
}

char	*get_value(char *var)
{
	int		i;
	char	*value;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] == '=')
		value = ft_substr(var, i + 1, ft_strlen(var) - i);
	else
		value = NULL;
	return (value);
}

/**
 * set_value - function that sets the value of an environment variable
 * @var: The variable string in the format "key=value"
 * @env: A pointer to the head of the environment variable linked list
 * Return: void
 */
int	set_value(char *var, t_env *env)
{
	char	*key;
	char	*value;
	t_env	*tmp;

	key = get_key(var);
	value = get_value(var);
	tmp = env;
	while (tmp && tmp->next && value)
	{
		tmp = tmp->next;
		if (!ft_strcmp(key, tmp->key))
		{
			tmp->value = ft_strdup(value);
			return (free(key), free(value), 1);
		}
	}
	tmp = env;
	while (tmp && tmp->next && !value)
	{
		tmp = tmp->next;
		if (!ft_strcmp(key, tmp->key))
			return (free(key), 1);
	}
	return (env_list_add(&tmp, env_new(var)), free(key), free(value), 1);
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
			while (*env->value)
			{
				if (*env->value == '\"' || *env->value == '$')
					write(1, "\\", 1);
				write(1, env->value, 1);
				env->value++;
			}
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
