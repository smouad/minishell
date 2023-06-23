/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:00:00 by msodor            #+#    #+#             */
/*   Updated: 2023/06/23 21:36:52 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * is_joinable - function that checks if two adjacent elements
 * in the token list can be concatenated
 * @elems: a pointer to a pointer to the head element of the token list
 *
 * Return: 1 if the two elements can be concatenated, otherwise it returns 0.
 */
int	is_joinable(t_elems *elems)
{
	if ((elems->state == IN_DQUOTE && elems->next->state == IN_DQUOTE \
		&& elems->next->type != VAR && elems->type != VAR) || \
		(elems->state == IN_QUOTE && elems->next->state == IN_QUOTE))
		return (1);
	return (0);
}
/**
 * join_in_quote - function that concatenates elements in the token list
 * that are in a quote state
 * @elems: a pointer to a pointer to the head element of the token list
 */
void	join_in_quote(t_elems **elems)
{
	t_elems	*head;
	char	*new;

	head = *elems;
	while (head && head->next)
	{
		if (is_joinable(head))
		{
			new = ft_strjoin(head->content, head->next->content);
			free(head->content);
			head->content = new;
			head->len += head->next->len;
			head->type = WORD;
			token_del(elems, head->next);
			join_in_quote(&head);
		}
		head = head->next;
	}
}

/**
 * rm_quotes - removes quote and double-quote elements from the token list
 * @elems: a pointer to a pointer to the head element of the token list
 */
void	rm_quotes(t_elems **elems)
{
	t_elems	*current;
	t_elems	*temp;

	current = *elems;
	temp = NULL;
	while (current != NULL)
	{
		if ((current->type == DQUOTE || current->type == QUOTE) \
		&& current->state == DEFAULT)
		{
			temp = current->next;
			token_del(elems, current);
			current = temp;
		}
		else
			current = current->next;
	}
}

/**
 * rm_spaces - function that removes space elements from the token list
 * @elems: a pointer to a pointer to the head element of the token list
 */
void	rm_spaces(t_elems **elems)
{
	t_elems	*current;
	t_elems	*temp;

	current = *elems;
	temp = NULL;
	while (current != NULL)
	{
		if (current->type == _SPACE)
		{
			temp = current->next;
			token_del(elems, current);
			current = temp;
		}
		else
			current = current->next;
	}
}

/**
 * join_cmd - function that concatenates adjacent elements
 * in the token list that are of type WORD
 * @elems: a pointer to a pointer to the head element of the token list
 */
void	join_cmd(t_elems **elems)
{
	t_elems	*current;
	char	*new_content;

	current = *elems;
	type_cast(elems);
	rm_quotes(elems);
	current = current->next;
	while (current && current->next)
	{
		if ((current->type == WORD || current->type == VAR) &&\
		(current->next->type == WORD || current->next->type == VAR))
		{
			new_content = ft_strjoin(current->content, current->next->content);
			free(current->content);
			current->content = new_content;
			current->len = ft_strlen(new_content);
			token_del(elems, current->next);
		}
		else
			current = current->next;
	}
}

/**
 * type_cast - function that sets the type of elements in a token list
 * @elems: a pointer to the head of the token list
 */
void	type_cast(t_elems **elems)
{
	t_elems	*head;

	head = *elems;
	while (head)
	{
		if ((head->state == IN_DQUOTE && head->type != VAR) \
		|| head->state == IN_QUOTE)
			head->type = WORD;
		head = head->next;
	}
}
