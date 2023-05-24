/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:00:40 by msodor            #+#    #+#             */
/*   Updated: 2023/05/24 17:34:31 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quote_state(t_elems **ptr)
{
	(*ptr)->state = IN_QUOTE;
	*ptr = (*ptr)->next;
	while ((*ptr)->type != QUOTE)
	{
		(*ptr)->state = IN_QUOTE;
		*ptr = (*ptr)->next;
		(*ptr)->state = IN_QUOTE;
	}
}

void	dquote_state(t_elems **ptr)
{
	(*ptr)->state = IN_DQUOTE;
	*ptr = (*ptr)->next;
	while ((*ptr)->type != DQUOTE)
	{
		(*ptr)->state = IN_DQUOTE;
		*ptr = (*ptr)->next;
		(*ptr)->state = IN_DQUOTE;
	}
}

void	set_state(t_elems *elems)
{
	t_elems	*ptr;

	ptr = elems->next;
	while (ptr != NULL)
	{
		if (ptr->type == DQUOTE)
			dquote_state(&ptr);
		else if (ptr->type == QUOTE)
			quote_state(&ptr);
		ptr = ptr->next;
	}
}
