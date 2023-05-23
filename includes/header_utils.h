/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:10:15 by msodor            #+#    #+#             */
/*   Updated: 2023/05/23 17:28:01 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_UTILS_H
# define HEADER_UTILS_H

# include "libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token
{
	SPACE = ' ',
	NEW_LINE = '\n',
	QUOTE = '\'',
	DQUOTE = '\"',
	VAR = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	WORD,
	HERE_DOC,
	REDIR_OUT,
}	t_token;
	// _NULL = '0',
	// ESCAPE = '\\',

typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	DEFAULT,
	UNOWN,
}	t_state;

typedef struct s_token
{
	t_token			*prev;
	char			*content;
	int				len;
	enum e_token	type;
	enum e_state	state;
	t_token			*next;
}	t_token;

#endif
