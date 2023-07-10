/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:19:56 by msodor            #+#    #+#             */
/*   Updated: 2023/07/10 16:21:39 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_for_childs(int *arra, t_parser *parser)
{
	int	i;
	int	status;

	i = 0;
	while (i < parser->cmd_nbr)
	{
		waitpid(arra[i], &status, 0);
		i++;
	}
	parser->exit_s = WEXITSTATUS(status);
}

int	check_in(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_out(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT || tmp->type == AREDIR_OUT)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
