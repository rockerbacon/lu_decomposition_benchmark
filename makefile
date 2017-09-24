CC = gcc
OBJS = main.o matriz.o lu.o
NAME = lu
FLAGS = -I/usr/local/include /usr/local/lib/libpapi.a

all: $(NAME) clean

%.o: %.c
	$(CC) -I. -c $<

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(FLAGS)

clean:
	rm -f $(OBJS)
