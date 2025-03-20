# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 11:41:12 by edubois-          #+#    #+#              #
#    Updated: 2025/03/20 11:44:58 by edubois-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	minishell

DIR_LIB 		:= 	lib

PRINTF_DIR		:= $(DIR_LIB)/printf_fd
PRINTF_LIB		:= $(PRINTF_DIR)/libftprintf.a

LIBFT_DIR 		:=	$(DIR_LIB)/libft
LIBFT_LIB 		:= $(LIBFT_DIR)/libft.a

SRCS 			=	srcs/main.c\
					srcs/get_data/collect_data.c\
					srcs/get_data/fill_line_data.c\
					srcs/utils/signal_handler.c\
					srcs/parsing/parsing.c\
					srcs/utils/data_utils.c\
					srcs/exec/make_exec.c\
					srcs/exec/manage_dir/manage_dir.c\
					srcs/utils/ft_split_dir_utils.c\
					srcs/utils/ft_ms_split.c\
					srcs/utils/ft_ms_split_utils.c\
					srcs/utils/write_error.c\
					srcs/exec/manage_dir/manage_here_doc.c\
					srcs/get_data/open_heredoc.c\
					srcs/parsing/check_pipe.c\
					srcs/exec/manage_dir/create_redir.c\
					srcs/parsing/check_all_error.c\
					srcs/utils/clear_data.c\
					srcs/utils/utils.c\
					srcs/exec/manage_dir/manage_here_doc_utils.c\
					srcs/exec/manage_dir/manage_dir_utils.c\
					srcs/exec/manage_builtins.c\
					srcs/cmd/exit.c\
					srcs/cmd/exit_utils.c\
					srcs/utils/exec_utils.c\
					srcs/utils/mn_promp.c\
					srcs/parsing/variable_environment/quote_handler.c\
					srcs/parsing/variable_environment/quote_var_utils.c\
					srcs/parsing/variable_environment/var_handler.c\
					srcs/cmd/echo.c\
					srcs/cmd/cd.c\
					srcs/cmd/pwd.c\
					srcs/cmd/env.c\
					srcs/cmd/export/export_utils.c\
					srcs/cmd/export/export.c\
					srcs/cmd/export/export_check.c\
					srcs/cmd/export/export_lst.c\
					srcs/cmd/export/export_free_array.c\
					srcs/cmd/unset.c\

OBJS 			:= $(SRCS:.c=.o)

CC 				:= @cc

FLAGS 			:= -Wall -Wextra -Werror -g




.SILENT:

all: $(NAME)

$(NAME):	$(LIBFT_LIB) $(PRINTF_LIB) $(OBJS)
	@echo "Compilation de $(NAME)"
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) $(PRINTF_LIB) -lreadline
	sleep 0.7
	clear

$(PRINTF_LIB):
	@echo "Compilation de printf_fd..." 
	make -s -C $(PRINTF_DIR)

$(LIBFT_LIB):
	@echo "Compilation de libft..." 
	make -s -C  $(LIBFT_DIR)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "Suppresion des objets..." 
	make clean -s -C  $(LIBFT_DIR)
	make clean -s -C  $(PRINTF_DIR)
	rm -f $(OBJS)

fclean: clean
	@echo "Suppresion des executables..." 
	make fclean -s -C  $(LIBFT_DIR)
	make fclean -s -C  $(PRINTF_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
