/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:26:53 by msodor            #+#    #+#             */
/*   Updated: 2023/05/27 00:53:03 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	rm_extra_space(t_elems **elems)
{
	t_elems	*head;

	head = *elems;
	while (head != NULL)
	{
		if (head->type == _SPACE && head->state == DEFAULT)
		{
			token_del(elems, head);
		}
	}
}

void	quotes_syntax(t_elems *elems)
{
	int	dcount;
	int	count;

	count = 0;
	dcount = 0;
	while (elems)
	{
		if (elems->type == DQUOTE)
			dcount++;
		else if (elems->type == QUOTE)
			count++;
		elems = elems->next;
	}
	if ((count % 2) != 0 || (dcount % 2) != 0)
		printf("syntax error: unclosed quotes.\n");
}

// void	redir_syntax(t_elems *elems)
// {
// 	while (elems && elems->next)
// 	{
// 		if (elems->type == REDIR_IN || elems->type == REDIR_OUT \
// 		|| elems->type == HERE_DOC || elems->type == AREDIR_OUT)
// 		{
// 			if (elems->next->type != WORD && elems->next->type != _SPACE)
// 				printf("syntax error: near unexpected token\n");
// 		}
// 		elems = elems->next;
// 	}
// }
