NAME = minishell

CC = cc

RM = rm -rf

FLAGS =  -Wall -Wextra -Werror -lreadline -fsanitize=address -g

TOOLS	= $(addprefix tools/,	ft_split.c ft_strjoin.c ft_strncmp.c ft_strlen.c ft_strchr.c ft_strdup.c\
								ft_substr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_itoa.c)
LEXER	= $(addprefix lexer/,	lexer.c list.c lexer_utils.c state.c print_table.c analyser.c analyser_utils.c syntax_err.c)
PARSER	= $(addprefix parser/,	parser.c cmd_list.c redir_list.c parser_utils.c)
EXEC	= $(addprefix exec/,	path.c)
BUILT	= $(addprefix built/,	echo.c builtins.c env.c pwd.c cd.c env_list.c export.c unset.c exit.c)

SRC = minishell.c $(LEXER) $(PARSER) $(BUILT) $(TOOLS) $(EXEC)\

OBJ	= ${SRC:.c=.o}

%.o : %.c
			${CC} ${CFLAGS} -c $< -o $@

$(NAME) : $(SRC) $(OBJ)
	$(CC)  $(SRC) -o $(NAME) $(FLAGS)

all : $(NAME)

run : all
	./minishell
clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all