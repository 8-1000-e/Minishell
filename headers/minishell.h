/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:49:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/20 15:00:48 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_PWD 200

# define RDM_NAME	"abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTU"

# define BOLD      "\033[1m"

# define RED     "\033[31m"
# define BEIGE      "\033[38;5;180m"
# define BLUE "\033[38;5;153m"
# define PINK  "\033[35m"
# define LIGHT_GRAY "\033[38;5;250m"
# define RESET   "\033[0m"

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"
# include "../lib/printf_fd/ft_printf.h"
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*str;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	int		error;
	int		builtin;
}	t_cmd;

typedef struct s_data
{
	char	**env;
	char	*line;
	char	*pwd;
	char	**paths;
	t_env	*env_list;
	t_cmd	*cmd_list;
	int		exit;
	int		exit_status;
	int		*pids;
	int		fd_in;
	int		fd_out;
	char	**here_doc_name;	
	int		redir_fd[2];
}	t_data;

char	**create_tpwd(char *pwd);
int		reload_pwd(t_data *data);
void	collect_data(t_data *data);
void	clear_data(t_data data);
int		fill_line_data(t_data *data, char *line);
void	signal_handler(int sig);
int		nb_cmd(t_data data);
void	add_to_file(t_cmd cmd, int fd);
void	delete_cmd(t_data *data, int i);
void	make_exec(t_data *data);
void	check_exec_error(t_data *data);
int		check_quote(char *str);
void	add_quoted_word(char **word, char **str, int *idq, int *iq);
void	add_simple_word(char **word, char **str);
void	make_split(char **t, int i[2], int index[2], char ***tab);
char	**make_dir_split(char **t, int i[2], int index[2], int iq[2]);
char	**manage_dir(char **t, int c);
void	next_w(char **str, int *iq, int *idq);
char	**split(char *word, int idq, int iq, char *str);
char	*dup_char(char c, int size);
char	**ft_ms_split(char *str, int *quote_pb);
void	manage_exec_dir(t_data *data, int i);
char	*start_here_doc(t_data *data, char *lim);
void	manage_pipe(t_data *data, int pipe_fd[2]);
void	fill_data(t_data *data, char **full_line, char *line);
void	fill_command(t_data *data, char **line);
void	fill_paths(t_data *data);
int		destroy_here_doc(t_data *data);
int		check_error(t_data *data, int i, int j, char *redir);
int		create_here_doc(t_data *data);
int		check_pipe(t_data *data, char *line);
int		create_redir(t_data *data);
void	check_all_error(t_data *data, int i, int j, int error);
int		add_error(t_data *data, int i, int *error, int error_code);
void	reset_data(t_data *data);
void	reset_data_here(t_data *data);
void	sort_cmd(t_data *data);
void	ft_strapp_off(char ***tab, char *str, int offsett);
int		check_for_cmd(t_data *data, int i);
void	child_fork(t_data *data, char *rdm_name, char *lim);
void	write_fd(int fd, char *line, char *lim, t_data *data);
char	*random_name(void);
int		keep_fd(int new_fd);
void	handle_input_redirection(t_data *data, int i, int j);
void	handle_heredoc_redirection(t_data *data, int i, int j);
void	handle_output_redirection(t_data *data, int i, int j);
void	handle_append_redirection(t_data *data, int i, int j);
void	ft_exit(t_data *data, int i);
int		make_builtin(t_data *data, int i);
char	*absolute_path(t_data *data, int j);
char	*find_valid_path(char **paths, char *cmd);
void	assign_absolute_path(t_data *data, int j);
int		make_conversion(long *num, char **num_str, int *error);
long	str_to_long(char *num_str, int *error);
void	close_all(t_data *data, int pipe_fd[2]);
void	exit_error(t_data *data, char *msg);
void	manage_exit_code(t_data *data);
char	*bt_prompt(t_data *data);
int		reload_pwd(t_data *data);
int		cd(t_data *data, char **cmd);
void	collect_data(t_data *data);
void	clear_data(t_data data);
int		error_exit(t_data data, int sig, char *name);
int		fill_line_data(t_data *data, char *line);
void	signal_handler(int sig);
void	cmd_env(t_data *data);
void	echo(char **cmd);
char	*replace_var_env(char *str, t_data data);
t_data	*keep_data(t_data *data);
char	**ft_arraydupe(char **tab);
char	*build_var_env(char *str, t_data data);
char	**ms_split_env(char *str);
t_env	*ms_new_var(t_env *list, char *key, char *value, char *str);
int		ms_build_array_env(t_data *data);
t_env	*ms_setup_lst_env(t_data *data, char **env);
t_env	*ms_get_node_by_key(t_data *data, char *key);
int		ms_edit_env_lst(t_data *data, char *key, char *value, char *str);
int		ms_size_lst_env(t_data *data, int is_export);
t_env	**ms_build_array_export(t_data data);
int		export(t_data *data, char **cmds);
void	ms_free_all_env(t_data *data);
void	ms_remove_env(t_data *data, char *key);
int		cmd_unset(t_data *data, char **cmds);
char	*ms_get_env(t_data data, char *key);
void	ms_swap_node(char **char1, char **char2);
t_env	*ms_create_node_ifno(t_data *data, char *char1);
int		is_valid_char(char c);
int		is_valid_key(char *str);
int		get_bigger(char *str1, char *str2);
int		ms_print_export(t_data data);
void	ms_swap_env(t_env **a, t_env **b);
void	ms_free_lst_env(t_data *data);
void	ms_free_env(t_env *env);
int		is_env_char(char c);
void	check_quotes(char *str, int i, int *dquote, int *quote);
char	*get_env(char *str, t_data data);
char	*epurstr(char *str);
int		pwd(void);

#endif