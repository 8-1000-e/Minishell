/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:32:17 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/20 14:47:19 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	g_sigint;

int	keep_fd(int new_fd)
{
	static int	fd = 0;

	if (new_fd)
		fd = new_fd;
	return (fd);
}

void	sigheredoc(int sig)
{
	int	fd;

	if (sig && !g_sigint)
	{
		printf("\n");
		rl_replace_line("", 1);
		g_sigint = sig;
		fd = keep_fd(0);
		if (fd > 2)
			close(fd);
		exit(g_sigint + 128);
	}
}

void	clean_exit_here_doc(t_data *data, char *lim, int fd)
{
	ft_printf(2, BOLD RED "/!\\ " BOLD BEIGE "Shellokitty: warning: he"
		"re-document delimited by end-of-file "
		"(wanted `%s')\n" RESET, lim);
	close(fd);
	reset_data_here(data);
	exit(0);
}

void	write_fd(int fd, char *line, char *lim, t_data *data)
{
	while (fd > 0 && lim)
	{
		line = readline("heredoc: ");
		if (line && !ft_strcmp(line, lim))
		{
			line = build_var_env(line, *data);
			line = ft_strjoinfree(line, "\n", 1);
			ft_putstr_fd(line, fd);
			dh_free(line);
		}
		else if (!line)
			clean_exit_here_doc(data, lim, fd);
		else
		{
			close(fd);
			reset_data_here(data);
			exit(0);
		}
	}
}

char	*start_here_doc(t_data *data, char *lim)
{
	char	*line;
	char	*rdm_name;
	int		pid;
	int		e;

	g_sigint = 0;
	signal(SIGINT, sigheredoc);
	rdm_name = random_name();
	ft_strapp(&data->here_doc_name, rdm_name);
	if (!&random_name || !data->here_doc_name)
		exit_error(data, "failed malloc");
	line = NULL;
	pid = fork();
	if (!pid)
		child_fork(data, rdm_name, lim);
	e = 0;
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &e, 0);
	signal(SIGINT, signal_handler);
	data->exit_status = WEXITSTATUS(e);
	if (data->exit_status)
		g_sigint = 130;
	if (g_sigint)
		rdm_name = NULL;
	return (rdm_name);
}
