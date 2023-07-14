/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:08:47 by msodor            #+#    #+#             */
/*   Updated: 2023/07/14 11:35:35 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	redirect_output(t_redir *redir)
// {
// 	int	fd;

// 	fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		perror("minishell");
// 		return (-1);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup2");
// 		close(fd);
// 		return (-1);
// 	}
// 	close(fd);
// 	return (0);
// }

int	handle_redirection(t_redir *redir, t_parser *parser)
{
	if (redir->type == REDIR_IN)
		return (redirect_input(redir));
	else if (redir->type == REDIR_OUT)
		return (redirect_output(redir));
	else if (redir->type == AREDIR_OUT)
		return (redirect_append(redir));
	else if (redir->type == HERE_DOC)
		handle_here_document(redir, parser);
	return (0);
}

int	exec_redir(t_cmd *cmd, t_parser *parser)
{
	t_redir	*redir;

	redir = cmd->redir;
	if (!redir)
		return (1);
	while (redir)
	{
		if (handle_redirection(redir, parser) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
