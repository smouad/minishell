/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:16:17 by msodor            #+#    #+#             */
/*   Updated: 2023/06/21 19:47:27 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * analyser - processes a given input string and returns a token list
 * @line: a pointer to the input string to be processed
 *
 * This function uses the `lexer` function to tokenize the input string
 * and then applies various syntax checks and modifications to the token list.
 * These include checking for quotes syntax, joining commands, removing spaces,
 * checking for redirection syntax, and checking for pipe syntax.
 * Return: returns a token list that represents the modified input string.
 */
t_elems	*analyser(char *line, t_env *env)
{
	t_elems	*elems;

	elems = lexer(line);
	if (quotes_syntax(elems))
		return (NULL);
	set_env(elems, env);
	join_cmd(&elems);
	rm_spaces(&elems);
	if (redir_syntax(elems))
		return (NULL);
	if (pipe_syntax(elems))
		return (NULL);
	return (elems);
}

