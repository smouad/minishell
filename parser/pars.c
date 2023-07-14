/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:48:29 by msodor            #+#    #+#             */
/*   Updated: 2023/07/14 10:48:52 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_parser(t_elems *elems, t_parser *parser)
{
	init_cmds(elems, parser);
	set_redir(parser, elems);
	set_full_cmd(parser->cmds, elems);
	set_cmd_args(parser->cmds, elems);
}
