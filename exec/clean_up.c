/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:07:37 by msodor            #+#    #+#             */
/*   Updated: 2023/07/14 13:15:51 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * free_array - frees the memory allocated for an array of strings
 * @array: The array to be freed
 * Return: void
 */
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/**
 * free_redir_list - frees the memory allocated for a redirection list
 * @redir: A pointer to the head of the redirection list
 * Return: void
 */
void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->file);
		free(tmp);
	}
}

/**
 * free_env_list - frees the memory allocated for an environment variable list
 * @env: A pointer to the head of the environment variable list
 * Return: void
 */
void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

/**
 * free_cmd_list - frees the memory allocated for a command linked list
 * @cmd: A pointer to the head of the command list
 * Return: void
 */
void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->cmd)
			free(tmp->cmd);
		free_array(tmp->args);
		free_array(tmp->full_cmd);
		free_redir_list(tmp->redir);
		free(tmp);
	}
}

/**
 * free_parser - function that frees the memory allocated for a parser structure
 * @parser: A pointer to the parser structure
 * Return: void
 */
void	free_parser(t_parser *parser)
{
	free_env_list(parser->env);
	free_cmd_list(parser->cmds);
	free(parser);
}
