COM_COLOR   = \033[1;34m
CLEAN_COLOR	= \033[1;31m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"
CLEAN_STRING = "Cleaning"

NAME=lem-in_test
FLAGS= -Wall -Wextra -Werror -I. -c
LEMINDIR=..
LIBDIR=libft/
LIB=$(LIBDIR)libft.a
PRINTFDIR=ft_printf/
PRINTF=$(PRINTFDIR)libftprintf.a
HASHTABLEDIR=hashtable/
HASHTABLE=$(HASHTABLEDIR)hashtable.a
SRCS=main.c\
	 errors.c\
	 parse_link.c\
	 parse_room.c\
	 read.c\
	 test.c\
	 get_next_line/get_next_line.c
OBJS=$(SRCS:%.c=%.o)

.PHONY: libs all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C $(LEMINDIR)
	@make -s -C $(LIBDIR)
	@make -s -C $(PRINTFDIR)
	@make -s -C $(HASHTABLEDIR)
	@gcc -o $(NAME) $(OBJS) $(LIB) $(PRINTF) $(HASHTABLE)
	@printf "%-20b%-40b%b" "$(COM_COLOR)$(COM_STRING)" "$(OBJ_COLOR)$(NAME)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"

%.o: %.c
	@gcc $(FLAGS) $< -o $@

clean:
	@-rm -f $(OBJS)
	@make -C $(LEMINDIR) fclean
	@make -C $(LIBDIR) fclean
	@make -C $(PRINTFDIR) fclean
	@make -C $(HASHTABLEDIR) fclean
	@printf "%-20b%b" "$(CLEAN_COLOR)$(CLEAN_STRING)" "$(OBJ_COLOR)lem-in$(NO_COLOR)\n"

fclean: clean
	@-rm -f $(NAME)
	@printf "%-20b%b" "$(CLEAN_COLOR)Removing" "$(OBJ_COLOR)$(NAME)$(NO_COLOR)\n"

re: fclean all
