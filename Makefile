# Makefile

NAME = snake

SRCS = main.c\
       list.c

all :  $(NAME)

$(NAME): $(SRCS)
	gcc $(SRCS) -o $(NAME) -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_image

fclean:
	rm -f $(NAME)

re: fclean all
