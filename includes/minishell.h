/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:29:40 by msodor            #+#    #+#             */
/*   Updated: 2023/05/23 16:47:16 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "header_utils.h"

/* ******************************************* */
/* ----------------:> LEXER <:---------------- */
/* ******************************************* */

/* -----:> LIST <:-----*/

t_token	*token_new(char *content, int len, t_token type, t_state state);
void	token_list_add(t_token **lst, t_token *new);
void	token_list_free(t_token *list);

/* -----:> LEXER <:-----*/

int		is_space(char c);
void	set_token_word(char *line, int *i);
void	*set_token_redir(char *line, int *i);
t_token	*lexer(char *line);


#endif