/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:16:17 by msodor            #+#    #+#             */
/*   Updated: 2023/06/01 20:16:55 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_elems	*analyser(char *line)
{
	t_elems	*elems;

	elems = lexer(line);
	quotes_syntax(elems);
	join_cmd(&elems);
	rm_spaces(&elems);
	redir_syntax(elems);
	pipe_syntax(elems);
	return (elems);
}
