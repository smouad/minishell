/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:47:43 by msodor            #+#    #+#             */
/*   Updated: 2023/06/28 18:49:15 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int create_pipe(t_parser *parser)
// {
// 	while (parser->cmds)
// 	{
// 		if (pipe(parser->cmds->fd) == -1)
// 			return (1);
// 		parser->cmds = parser->cmds->next;
// 	}
// 	return (0);
// }
// void    close_pipe(t_parser *parser)
// {
// 	while (parser->cmds)
// 	{
// 		close(parser->cmds->fd[0]);
// 		close(parser->cmds->fd[1]);
// 		parser->cmds = parser->cmds->next;
// 	}
// }

// void	redirect_pipe(t_parser *parser)
// {
// 	t_cmd	*cmds;

// 	cmds = parser->cmds;
// 	while (cmds)
// 	{
// 		if (cmds->next)
// 			dup2(cmds->fd[1], 1);
// 		if (cmds->prev)
// 			dup2(cmds->prev->fd[0], 0);
// 		cmds = cmds->next;
// 	}
// }


// /*
//  * function that will execute the pipe using all the commands in the cmds list
//  * first we create the pipes using the create_pipe function
//  * then we loop through the cmds list and we redirect the pipe using the redirect_pipe function
//  * then we execute the command using the exec_cmd function
//  * then we close the pipes using the close_pipes function
//  * then we rollback the fd using the rollback_fd function
// */
// void	execute_pipe(t_parser *parser)
// {
// 	t_cmd	*cmds;

// 	cmds = parser->cmds;
// 	if (create_pipe(parser))
// 		return ;
// 	while (cmds)
// 	{
// 		redirect_pipe(parser);
// 		exec_cmd(parser);
// 		cmds = cmds->next;
// 	}
// 	close_pipe(parser);
// 	rollback_fd(parser);
// }