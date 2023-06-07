/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:14:38 by msodor            #+#    #+#             */
/*   Updated: 2023/06/07 14:11:28 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * token_new - function that creates a new token element
 * @content: a pointer to the content string
 * @len: the length of the content
 * @type: the token type
 * @state: the token state
 * Return: a pointer to the newly created token element
 */
t_elems	*token_new(char *content, int len, t_token type, t_state state)
{
	t_elems	*elems;

	elems = malloc(sizeof(t_elems));
	if (!elems)
		return (NULL);
	elems->content = ft_strdup(content);
	elems->len = len;
	elems->type = type;
	elems->state = state;
	elems->next = NULL;
	return (elems);
}

/**
 * token_list_add - function that adds a new token element to a token list
 * @lst: a pointer to the head of the token list
 * @new: a pointer to the new token element
 */
void	token_list_add(t_elems **lst, t_elems *new)
{
	t_elems	*ptr;

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
 * token_del - function that deletes a token element from a token list
 * @head: a pointer to the head of the token list
 * @node: a pointer to the token element to be deleted
 */
void	token_del(t_elems **head, t_elems *node)
{
	t_elems	*current;

	current = *head;
	if (*head == NULL)
		return ;
	if (node == *head)
	{
		*head = node->next;
		free(node->content);
		free(node);
		return ;
	}
	while (current->next != NULL && current->next != node)
		current = current->next;
	if (current->next == node)
	{
		current->next = node->next;
		free(node->content);
		free(node);
	}
}

/**
 * token_list_free - function that frees the memory used by a token list
 * @list: a pointer to the head of the token list
 */
void	token_list_free(t_elems *head)
{
	t_elems	*current;

	current = head;
	while (current != NULL)
	{
		free(current->content);
		free(current);
		current = current->next;
	}
	free(head);
}
