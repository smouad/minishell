/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:25:27 by msodor            #+#    #+#             */
/*   Updated: 2023/07/14 16:32:06 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_input(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	redir->old_infd = dup(STDIN_FILENO);
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

t_elems	set_tmp(char *line)
{
	t_elems	tmp;

	tmp.content = line;
	tmp.next = NULL;
	tmp.len = ft_strlen(line);
	tmp.type = VAR;
	tmp.state = 0;
	return (tmp);
}

void	exec_her(t_redir *redir, t_parser *parser, int fd[2])
{
	char	*line;
	t_elems	tmp;

	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(redir->file, line))
		{
			if (line)
				free(line);
			break ;
		}
		if (line && ft_strchr(line, '$') >= 0)
		{
			tmp = set_tmp(line);
			set_env(&tmp, parser);
			line = ft_strdup(tmp.content);
			free(tmp.content);
		}
		if (!line)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

int	handle_here_document(t_redir *redir, t_parser *parser)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("minishell");
		return (-1);
	}
	exec_her(redir, parser, fd);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}
