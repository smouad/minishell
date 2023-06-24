/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:26:53 by msodor            #+#    #+#             */
/*   Updated: 2023/06/24 15:39:18 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * is_redir - checks if a token is a redirection
 * @elems: a pointer to the token
 * Return: 1 if it is a redirection, 0 otherwise
 */
int	is_redir(t_elems *elems)
{
	if (elems->type == REDIR_IN || elems->type == REDIR_OUT \
	|| elems->type == HERE_DOC || elems->type == AREDIR_OUT)
		return (1);
	return (0);
}

/**
 * quotes_syntax - function that checks for proper quote usage in a token list
 * @elems: a pointer to the head of the token list
 */
int	quotes_syntax(t_elems *elems, t_parser *parser)
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
		return (parser->exit_s = 2, 1);
	}
	return (0);
}

/**
 * redir_syntax - checks for proper redirection usage in a token list
 * @elems: a pointer to the head of the token list
 */
int	redir_syntax(t_elems *elems, t_parser *parser)
{
	while (elems && elems->next)
	{
		if (is_redir(elems) && elems->next->type != WORD \
		&& elems->next->type != VAR)
		{
			write(2, " syntax error near unexpected token \n", 37);
			write(2, "`", 1);
			write(2, elems->next->content, ft_strlen(elems->next->content));
			write(2, "\'\n", 2);
			return (parser->exit_s = 2, 1);
		}
		elems = elems->next;
		if (is_redir(elems) && elems->next == NULL)
		{
			write(2, " syntax error near unexpected token `newline'\n", 46);
			return (parser->exit_s = 2, 1);
		}
	}
	return (0);
}

/**
 * pipe_syntax - function that checks for proper pipe usage in a token list
 * @elems: a pointer to the head of the token list
 */
int	pipe_syntax(t_elems *elems, t_parser *parser)
{
	while (elems && elems->next)
	{
		if (elems->next->type == PIPE)
		{
			write(2, " syntax error near unexpected token `|'\n", 40);
			return (parser->exit_s = 2, 1);
		}
		if (elems->type == PIPE && elems->next->type == PIPE)
		{
			write(2, "syntax error near unexpected token \n", 40);
			write(2, "`", 1);
			write(2, elems->next->content, ft_strlen(elems->next->content));
			write(2, "\'\n", 2);
			return (parser->exit_s = 2, 1);
		}
		elems = elems->next;
		if (elems->next == NULL && elems->type == PIPE)
		{
			write(2, "syntax error near unexpected token `newline'\n", 45);
			return (parser->exit_s = 2, 1);
		}
	}
	return (0);
}
