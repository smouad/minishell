/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:26:53 by msodor            #+#    #+#             */
/*   Updated: 2023/06/01 20:13:09 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	redir_syntax(t_elems *elems)
{
	while (elems && elems->next)
	{
		if ((elems->type == REDIR_IN || elems->type == REDIR_OUT \
			|| elems->type == HERE_DOC || elems->type == AREDIR_OUT)
			&& elems->next->type != WORD)
		{
			printf("syntax error: near unexpected token `%s'\n", \
			elems->next->content);
			break ;
		}
		elems = elems->next;
	}
}

void	pipe_syntax(t_elems *elems)
{
	while (elems && elems->next)
	{
		if (elems->type == PIPE && elems->next->type == PIPE)
		{
			printf("syntax error: near unexpected token `%s'\n", \
			elems->next->content);
			break ;
		}
		elems = elems->next;
	}
}
