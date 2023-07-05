/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:58:54 by msodor            #+#    #+#             */
/*   Updated: 2023/07/05 12:54:56 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * env_new - function that creates a new environment variable node
 * @line: The line containing the environment variable (key=value)
 * Return: A pointer to the newly created t_env node
 */
t_env	*env_new(char *line)
{
	t_env	*env;
	int		index;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	index = ft_strchr(line, '=');
	if (index != -1)
	{
		env->key = ft_substr(line, 0, index);
		env->value = ft_substr(line, index + 1, ft_strlen(line) - index);
	}
	else
	{
		env->key = ft_strdup(line);
		env->value = NULL;
	}
	env->next = NULL;
	return (env);
}

/**
 * env_del - deletes an environment variable node from the linked list
 * @head: A pointer to the head of the linked list
 * @node: The node to be deleted
 * Return: void
 */
void	env_del(t_env **head, t_env *node)
{
	t_env	*current;

	current = *head;
	if (*head == NULL)
		return ;
	if (node == *head)
	{
		*head = node->next;
		free(node->key);
		if (node->value)
			free(node->value);
		free(node);
		return ;
	}
	while (current->next != NULL && current->next != node)
		current = current->next;
	if (current->next == node)
	{
		current->next = node->next;
		free(node->key);
		if (node->value)
			free(node->value);
		free(node);
	}
}

/**
 * env_list_add - adds a new environment variable node to the end of the list
 * @env: A pointer to the head of the linked list
 * @new: The new node to be added
 * Return: void
 */
void	env_list_add(t_env **env, t_env *new)
{
	t_env	*ptr;

	if (!env || !new)
		return ;
	if (*env)
	{
		ptr = *env;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
	else
		*env = new;
}
