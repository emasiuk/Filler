NAME = filler

VPATH = src:includes

FLAGS = -Wall -Wextra -Werror -I$(IDIR) -g

BIN_DIR = src/

BINS = $(SRCS:.c=.o)

LIB = libft/libft.a

SRCS = filler.c			\
		read.c			\
		my_string.c


BINS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: lib $(NAME)

lib:
	make -C libft/

libclean:
	make -C libft/ clean

libfclean:
	make -C libft/ fclean

$(NAME): $(BINS)
	gcc -o $(NAME) $(BINS) $(FLAGS)  $(LIB)
$(BIN_DIR)%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean: libclean
	/bin/rm -f $(BINS)

fclean: libfclean clean
	/bin/rm -f $(NAME)

re: fclean all
