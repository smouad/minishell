NAME = mini_shell

CC = cc

FLAGS =  -lreadline

SRC = mini_shell.c \

all : $(NAME)

$(NAME) : $(SRC)
	$(CC)  $(SRC) -o $(NAME) $(FLAGS)