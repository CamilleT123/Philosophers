NAME	= philo

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g

SRC		= main.c \
		init.c \
		thread.c \
		routine.c \
		activities.c \
		utils.c

OBJ		:= $(SRC:.c=.o)

all		: $(NAME)

%.o		: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME)	: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean	:
	rm -f $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all

# $@ is the name of the target being generated
# $< the first prerequisite
# $^ all the prerequisites