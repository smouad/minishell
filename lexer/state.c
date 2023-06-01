/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:00:40 by msodor            #+#    #+#             */
/*   Updated: 2023/06/01 22:04:31 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * quote_state - function that updates the state of the elements between the current element and the next quote element to be in the IN_QUOTE state
 * @ptr: a pointer to a pointer to the current element of the token list
 */
void	quote_state(t_elems **ptr)
{
	*ptr = (*ptr)->next;
	while ((*ptr)->type != QUOTE && (*ptr)->next != NULL)
	{
		(*ptr)->state = IN_QUOTE;
		*ptr = (*ptr)->next;
	}
}

/**
 * dquote_state - function that updates the state of the elements between the current element and the next double-quote element to be in the IN_DQUOTE state
 * @ptr: a pointer to a pointer to the current element of the token list
 */
void	dquote_state(t_elems **ptr)
{
	*ptr = (*ptr)->next;
	while ((*ptr)->type != DQUOTE && (*ptr)->next != NULL)
	{
		(*ptr)->state = IN_DQUOTE;
		*ptr = (*ptr)->next;
	}
}

/**
 * set_state - function that updates the state of the elements of the token list to be in the IN_QUOTE or IN_DQUOTE state
 * @elems: a pointer to the head element of the token list
 */
void	set_state(t_elems *elems)
{
	t_elems	*ptr;

	ptr = elems->next;
	while (ptr != NULL && ptr->next != NULL)
	{
		if (ptr->type == DQUOTE)
			dquote_state(&ptr);
		else if (ptr->type == QUOTE)
			quote_state(&ptr);
		ptr = ptr->next;
	}
}
