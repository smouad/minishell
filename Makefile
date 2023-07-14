NAME = minishell
CC = cc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror

# Include paths and libraries
LDFLAGS = -lreadline -L/goinfre/msodor/homebrew/opt/readline/lib -I/goinfre/msodor/homebrew/opt/readline/include

# List of source files
TOOLS = $(addprefix tools/, ft_split.c ft_strjoin.c ft_strncmp.c ft_strlen.c ft_strchr.c ft_strdup.c ft_substr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_itoa.c ft_atoi.c)
LEXER = $(addprefix lexer/, lexer.c list.c lexer_utils.c state.c syntax_err.c analyser.c analyser_utils.c)
PARSER = $(addprefix parser/, parser.c cmd_list.c redir_list.c parser_utils.c pars.c)
EXEC = $(addprefix exec/, clean_up.c execute_cmd.c exec.c exec_utils.c pipe.c pipe_utils.c redir.c redir_utils.c)
BUILT = $(addprefix exec/built/, echo.c env.c pwd.c cd.c env_list.c export.c export_utils.c unset.c exit.c)

SRC = minishell.c $(LEXER) $(PARSER) $(BUILT) $(TOOLS) $(EXEC)
OBJ = $(SRC:.c=.o)

# Rule to compile each .c file into corresponding .o file
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
