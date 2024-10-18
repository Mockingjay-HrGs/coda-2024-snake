# Makefile

NAME = snake

CC = gcc
CFLAGS = `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lSDL2_image

SRCS = main.c snake_game.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS) $(LIBS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

