NAME =		philo
SRCS =		checks.c init.c main.c philo_actions.c time_print.c
LIBFT =		libft
LIBS = 		./libft/libft.a	
OBJS =		$(SRCS:.c=.o)
HEADER = 	philo.h
%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror -pthread
RM =		rm -f
all :		$(NAME)
			@echo "\033[32mPHILO IS READY \033[0m"

$(NAME) :	$(OBJS) $(LIBFT)
			$(MAKE) -C $(LIBFT) all
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I. $(LIBS) 

$(LIBFT) :  libft/*.c libft/*.h
			$(MAKE) -C $(LIBFT) all
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I. $(LIBS)


clean :		
			$(MAKE) -C $(LIBFT) clean
			$(RM) $(OBJS)

fclean 	:	clean
			$(MAKE) -C $(LIBFT) fclean
			$(RM) $(NAME)

re :		fclean all

norm:
			norminette *.c philo.h libft/*.c libft/libft.h

.PHONY :	all clean fclean re norm