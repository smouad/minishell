/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:57:02 by msodor            #+#    #+#             */
/*   Updated: 2023/06/08 15:01:37 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * redir_new - function that creates a new redir element
 * @fd: a pointer to the fd string
 * @type: the redir type
 * Return: a pointer to the newly created redir element
 */
t_redir	*redir_new(char *file, t_token type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(file);
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

/**
 * redir_list_add - function that adds a new redir element to a redir list
 * @lst: a pointer to the head of the redir list
 * @new: a pointer to the new redir element
 */
void	redir_add(t_redir **lst, t_redir *new)
{
	t_redir	*ptr;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
	else
		*lst = new;
}

/**
 * redir_del - function that deletes a redir element from a redir list
 * @head: a pointer to the head of the redir list
 * @node: a pointer to the redir element to be deleted
 */
void	redir_del(t_redir **head, t_redir *node)
{
	t_redir	*current;

	current = *head;
	if (*head == NULL)
		return ;
	if (node == *head)
	{
		*head = node->next;
		free(node->file);
		free(node);
		return ;
	}
	while (current->next != NULL && current->next != node)
		current = current->next;
	if (current->next == node)
	{
		current->next = node->next;
		free(node->file);
		free(node);
	}
}

/**
 * redir_list_free - function that frees the memory used by a redir list
 * @list: a pointer to the head of the redir list
 */
// void	redir_list_free(t_redir *head)
// {
// 	t_redir	*current;

// 	current = head;
// 	while (current != NULL)
// 	{
// 		free(current->file);
// 		free(current);
// 		current = current->next;
// 	}
// 	free(head);
// }
