/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:06:07 by msodor            #+#    #+#             */
/*   Updated: 2023/05/23 17:28:25 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f' || c == '\n')
		return (1);
	return (0);
}

int	special_char(char c)
{
	return (c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|'
		|| c == '$' || ft_isspace(c) || c == '\n' || c == '\0');
}

void	set_token_word(char *line, int *i)
{
	int		j;
	char	*word;

	j = 0;
	while (!special_char(line[i + j]))
		j++;
	word = ft_substr(line, i, (i + j) + 1);
	list_add_back(&elem, token_new(word, ft_strlen(word), WORD, UNOWN));
	free(word);
	*(i) += ft_strlen(word);
}

void	set_token_var(char *line, int *i)
{
	int		j;
	char	*var;

	j = 0;
	while (!special_char(line[i + j]))
		j++;
	var = ft_substr(line, i, (i + j) + 1);
	list_add_back(&elem, token_new(var, ft_strlen(var), VAR, UNOWN));
	free(var);
	*(i) += ft_strlen(var);
}

void	*set_token_redir(char *line, int *i)
{
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			token_list_add(&elem, token_new("<<", 2, HERE_DOC, UNOWN));
		else
			token_list_add(&elem, token_new("<", 1, REDIR_IN, UNOWN));
		*(i) += 1;
	}
	if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			token_list_add(&elem, token_new(">>", 2, HERE_DOC, UNOWN));
		else
			token_list_add(&elem, token_new(">", 1, REDIR_OUT, UNOWN));
		*(i) += 1;
	}
}

t_token	*lexer(char *line)
{
	int		i;
	t_token	*elem;


	i = 0;
	elem = malloc(sizeof(t_token));
	while (line[i])
	{
		if (!special_char(line[i]))
			set_token_word(line, &i);
		else if (line[i] == '>' || line[i] '<')
			set_token_redir(line, &i);
		else if (line[i] == '$')
			set_tocken_var(line)
		else if (line[i] == '\'')
			token_list_add(&elem, token_new("\'", 1, QUOTE, UNOWN));
	}
}
