/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:26:53 by msodor            #+#    #+#             */
/*   Updated: 2023/06/02 02:16:01 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * quotes_syntax - function that checks for proper quote usage in a token list
 * @elems: a pointer to the head of the token list
 */
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

/**
 * redir_syntax - function that checks for proper redirection usage in a token list
 * @elems: a pointer to the head of the token list
 */
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
		if ((elems->type == REDIR_IN || elems->type == REDIR_OUT \
			|| elems->type == HERE_DOC || elems->type == AREDIR_OUT)
			&& elems->next == NULL)
		{
			printf("syntax error: near unexpected token `\\n'");
			break ;
		}
	}
}

/**
 * pipe_syntax - function that checks for proper pipe usage in a token list
 * @elems: a pointer to the head of the token list
 */
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
		if (elems->next == NULL && elems->type == PIPE)
		{
			printf("syntax error: near unexpected token `\\n'");
			break ;
		}
	}
}
