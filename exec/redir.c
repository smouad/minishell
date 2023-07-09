/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:08:47 by msodor            #+#    #+#             */
/*   Updated: 2023/07/09 18:25:50 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_redirection(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (redirect_input(redir));
	else if (redir->type == REDIR_OUT)
		return (redirect_output(redir));
	else if (redir->type == AREDIR_OUT)
		return (redirect_append(redir));
	else if (redir->type == HERE_DOC)
		handle_here_document(redir);
	return (0);
}

int	exec_redir(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	if (!redir)
		return (1);
	redir->old_infd = -1;
	redir->old_outfd = -1;
	while (redir)
	{
		if (handle_redirection(redir) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
