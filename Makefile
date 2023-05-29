NAME = minishell

LIBFT = libft/libft.a

CC = cc

RM = rm -rf

FLAGS =  -lreadline

# BUILT = $(addprefix builtins/,)
LEXER = $(addprefix lexer/, lexer.c \
							list.c \
							lexer_utils.c \
							state.c \
							print_table.c)

PARSER = $(addprefix parser/, syntax_err.c \
							parser.c\
							)

SRC = minishell.c $(LEXER) $(PARSER)\

all : $(NAME) 

$(NAME) : $(SRC) $(LIBFT)
	$(CC)  $(SRC) -o $(NAME) $(LIBFT) $(FLAGS) -fsanitize=address

%.o : %.c
			${CC} ${CFLAGS} -c $< -o $@

$(LIBFT) :
	make -C libft
clean : 
	$(RM) $(NAME)