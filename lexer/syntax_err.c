/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:26:53 by msodor            #+#    #+#             */
/*   Updated: 2023/07/13 17:44:38 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * put_syntax_err - function that prints a syntax error message
 * @elem: a pointer to the token
 */
void	put_syntax_err(char *elem)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, elem, ft_strlen(elem));
	write(2, "'\n", 2);
}

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
		write(2, "minishell: ", 11);
		write(2, "unexpected EOF while looking for matching.\n", 43);
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
			put_syntax_err(elems->next->content);
			return (parser->exit_s = 2, 1);
		}
		elems = elems->next;
		if (is_redir(elems) && elems->next == NULL)
		{
			write(2, "minishell: ", 11);
			write(2, "syntax error near unexpected token `newline'\n", 45);
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
	if (elems->next && elems->next->type == PIPE)
	{
		put_syntax_err(elems->next->content);
		return (parser->exit_s = 2, 1);
	}
	while (elems && elems->next)
	{
		if (elems->type == PIPE && elems->next->type == PIPE)
		{
			put_syntax_err(elems->next->content);
			return (parser->exit_s = 2, 1);
		}
		elems = elems->next;
		if (elems->next == NULL && elems->type == PIPE)
		{
			put_syntax_err(elems->content);
			return (parser->exit_s = 2, 1);
		}
	}
	return (0);
}
