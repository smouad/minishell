/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msodor <msodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:10:15 by msodor            #+#    #+#             */
/*   Updated: 2023/07/14 15:02:57 by msodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_UTILS_H
# define HEADER_UTILS_H

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token
{
	QUOTE = '\'',
	DQUOTE = '\"',
	_SPACE = ' ',
	VAR = '$',
	PIPE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	WORD,
	HERE_DOC,
	AREDIR_OUT,
}					t_token;

typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	DEFAULT,
}					t_state;

typedef struct s_elems
{
	char			*content;
	int				len;
	enum e_token	type;
	enum e_state	state;
	struct s_elems	*next;
}					t_elems;

/*parser*/

typedef struct s_redir
{
	char			*file;
	t_token			type;
	struct s_redir	*next;
	int				old_infd;
	int				old_outfd;
}					t_redir;

typedef struct s_cmd
{
	int				index;
	char			*cmd;
	char			**args;
	char			**full_cmd;
	t_redir			*redir;
	int				fd[2];
	int				argc;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_parser
{
	t_env			*env;
	t_cmd			*cmds;
	int				cmd_nbr;
	int				exit_s;
}					t_parser;

#endif
