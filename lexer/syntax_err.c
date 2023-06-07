/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:26:53 by msodor            #+#    #+#             */
/*   Updated: 2023/06/07 14:36:40 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * quotes_syntax - function that checks for proper quote usage in a token list
 * @elems: a pointer to the head of the token list
 */
int	quotes_syntax(t_elems *elems)
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
	{
		printf("syntax error: unclosed quotes.\n");
		return (1);
	}
	return (0);
}

/**
 * redir_syntax - checks for proper redirection usage in a token list
 * @elems: a pointer to the head of the token list
 */
int	redir_syntax(t_elems *elems)
{
	while (elems && elems->next)
	{
		if ((elems->type == REDIR_IN || elems->type == REDIR_OUT \
			|| elems->type == HERE_DOC || elems->type == AREDIR_OUT)
			&& elems->next->type != WORD)
		{
			printf("syntax error near unexpected token `%s'\n", \
			elems->next->content);
			return (1);
		}
		elems = elems->next;
		if ((elems->type == REDIR_IN || elems->type == REDIR_OUT \
			|| elems->type == HERE_DOC || elems->type == AREDIR_OUT)
			&& elems->next == NULL)
		{
			printf("syntax error near unexpected token `\\n'\n");
			return (1);
		}
	}
	return (0);
}

/**
 * pipe_syntax - function that checks for proper pipe usage in a token list
 * @elems: a pointer to the head of the token list
 */
int	pipe_syntax(t_elems *elems)
{
	t_elems	*head;

	head = elems;
	while (elems && elems->next)
	{
		if (head->next->type == PIPE)
		{
			printf("parse error near `|'\n");
			return (1);
		}
		if (elems->type == PIPE && elems->next->type == PIPE)
		{
			printf("syntax error near unexpected token `%s'\n", \
			elems->next->content);
			return (1);
		}
		elems = elems->next;
		if (elems->next == NULL && elems->type == PIPE)
		{
			printf("syntax error near unexpected token `\\n'\n");
			return (1);
		}
	}
	return (0);
}
