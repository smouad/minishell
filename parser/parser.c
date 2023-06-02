/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 00:01:56 by msodor            #+#    #+#             */
/*   Updated: 2023/06/02 01:51:06 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_nbr(t_elems *elems)
{
	t_parser parser;
	parser.cmd_nbr = 1;
	while (elems)
	{
		if (elems->type == PIPE)
			parser.cmd_nbr++;
		elems = elems->next;
	}
	// parser.cmds = malloc(sizeof(t_cmd) * parser.cmd_nbr);
	printf("%d\n", parser.cmd_nbr);
}

// t_parser	*parser(t_elems *elems)
// {
// 	cmd_nbr()
// }