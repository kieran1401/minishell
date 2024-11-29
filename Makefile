# Color Definitions
C_DEF   = \033[0;39m
C_GREEN = \033[0;92m
C_RED = \033[0;31m
C_YELLOW = \033[0;93m
C_PINK = \033[0;95m

# Project Name
NAME = minishell

# Compiler and Flags
CC = cc

# Default CFLAGS without ASan
CFLAGS = -Wall -Wextra -Werror -g 

# ASan CFLAGS
ASAN_CFLAGS = -fsanitize=address -Wall -Wextra -Werror -g 

# Other Makefile Variables
RM = rm -f
MAKE = make --no-print-directory -C
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source Files
SRCS = srcs/main.c \
	srcs/initialize_minishell.c \
	srcs/handle_input.c \
	srcs/lexer/lexer.c \
	srcs/lexer/lexer_utils.c \
	srcs/lexer/lexer_token.c \
	srcs/lexer/lexer_quotes.c \
	srcs/lexer/lexer_variable.c \
	srcs/lexer/lexer_word_dispatcher.c \
	srcs/lexer/lexer_token_utils.c \
	srcs/parser/parser.c \
	srcs/parser/ast.c \
	srcs/parser/parser_redirections.c \
	srcs/parser/parser_command.c \
	srcs/executor/executor.c \
	srcs/executor/executor_io.c \
	srcs/executor/executor_command.c \
	srcs/executor/executor_utils.c \
	srcs/executor/executor_process.c \
	srcs/executor/executor_pipe.c \
	srcs/executor/builtins.c \
	srcs/executor/builtins2.c \
	srcs/executor/redirections.c \
	srcs/executor/redirections_utils.c \
	srcs/executor/builtin_utils.c \
	srcs/executor/builtin_cd.c \
	srcs/executor/builtin_export.c \
	srcs/executor/builtin_unset.c \
	srcs/signals/signals.c \
	srcs/environment/environment.c \
	srcs/environment/environment2.c \
	srcs/utils/utils.c \
	srcs/utils/utils2.c \
	srcs/utils/memory.c \

# Object Files
OBJS = ${SRCS:.c=.o}

# Compilation Rule
%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@ -Iinclude

# Link the Executable
$(NAME): $(OBJS)
	$(MAKE) $(LIBFT_DIR)
	${CC} $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "${C_GREEN}[MINISHELL COMPILED]${C_DEF}"

# Default Target
all: ${NAME}

# Clean Targets
clean:
	${RM} ${OBJS}
	$(MAKE) ${LIBFT_DIR} clean
	@echo "${C_YELLOW}[MINISHELL CLEANED]${C_DEF}"

fclean:
	${RM} ${OBJS}
	$(MAKE) ${LIBFT_DIR} fclean
	$(RM) $(NAME)
	@echo "${C_RED}[MINISHELL FULLY CLEANED]${C_DEF}"

re: fclean all
	@echo "${C_GREEN}[MINISHELL REBUILT]${C_DEF}"

# Valgrind Target
valgrind: CFLAGS = -Wall -Wextra -Werror -g
valgrind: fclean $(NAME)
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes --log-file=output.log ./minishell

# ASan Target
asan: CFLAGS = $(ASAN_CFLAGS)
asan: fclean $(NAME)	
	./minishell

# Phony Targets
.PHONY: all clean fclean re valgrind asan

.SILENT:
