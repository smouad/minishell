NAME = minishell

CC = cc

RM = rm -rf

FLAGS =  -Wall -Wextra -Werror -lreadline


TOOLS = $(addprefix tools/, ft_split.c\
							ft_strjoin.c\
							ft_strncmp.c\
							ft_strlen.c\
							ft_strchr.c\
							ft_strdup.c\
							ft_substr.c\
							ft_isalpha.c\
							ft_isdigit.c\
							ft_isalnum.c) 
							# ft_itoa.c ft_strmapi.c ft_striteri.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_strtrim.c ft_calloc.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_bzero.c ft_atoi.c ft_strlcat.c ft_strnstr.c ft_strrchr.c ft_strlcpy.c ft_toupper.c ft_tolower.c ft_memset.c ft_isprint.c ft_isascii.c

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
							cmd_list.c\
							redir_list.c\
							)
BUILT = $(addprefix builtins/,  \
							echo.c\
							builtins.c\
							env.c\
							pwd.c\
							cd.c\
							env_list.c\
							export.c\
							)

SRC = minishell.c $(LEXER) $(PARSER) $(BUILT) $(TOOLS)\

OBJ	= ${SRC:.c=.o}

%.o : %.c
			${CC} ${CFLAGS} -c $< -o $@

$(NAME) : $(SRC) $(OBJ)
	$(CC)  $(SRC) -o $(NAME) $(FLAGS) -fsanitize=address -g

all : $(NAME)


run : all
	./minishell
clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all