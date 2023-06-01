NAME = minishell

LIBFT = libft/libft.a

CC = cc

RM = rm -rf

FLAGS =  -Wall -Wextra -Werror -lreadline

# BUILT = $(addprefix builtins/,)
LEXER = $(addprefix lexer/, lexer.c \
							list.c \
							lexer_utils.c \
							state.c \
							print_table.c \
							analyser.c \
							analyser_utils.c \
							syntax_err.c)

PARSER = $(addprefix parser/,  \
							parser.c\
							)

SRC = minishell.c $(LEXER) $(PARSER)\

all : $(NAME) 

$(NAME) : $(SRC) $(LIBFT)
	$(CC)  $(SRC) -o $(NAME) $(LIBFT) $(FLAGS) -fsanitize=address -g

%.o : %.c
			${CC} ${CFLAGS} -c $< -o $@

$(LIBFT) :
	make -C libft
clean :
	$(RM) $(NAME)
re : clean all