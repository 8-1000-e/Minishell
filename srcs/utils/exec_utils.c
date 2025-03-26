/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:03:31 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/25 17:48:40 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	manage_exit_code(t_data *data)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (data->cmd_list[i].cmd)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(data->pids[i], &exit_status, 0);
		signal(SIGINT, signal_handler);
		i++;
	}
	if (!data->cmd_list[nb_cmd(*data) - 1].builtin)
	{
		data->exit_status = WEXITSTATUS(exit_status);
		if (WIFSIGNALED(exit_status))
		{
			data->exit_status = 128 + WTERMSIG(exit_status);
			if (data->exit_status == 130)
				ft_printf(2, "\n");
			else if (data->exit_status == 131)
				ft_printf(2, BOLD BEIGE"Quit\n" RESET);
		}
	}
}

void	close_all(t_data *data, int pipe_fd[2])
{
	if (data->redir_fd[0] > 2)
		close(data->redir_fd[0]);
	if (data->redir_fd[01] > 2)
		close(data->redir_fd[1]);
	if (pipe_fd[0] > 2)
		close(pipe_fd[0]);
	if (pipe_fd[1] > 2)
		close(pipe_fd[1]);
	if (data->fd_in > 2)
		close(data->fd_in);
	if (data->fd_out > 2)
		close(data->fd_out);
}

void	manage_pipe(t_data *data, int pipe_fd[2])
{
	int	fd_in;
	int	fd_out;

	fd_out = pipe_fd[1];
	if (data->redir_fd[1] > 2)
		fd_out = data->redir_fd[1];
	fd_in = data->fd_in;
	if (data->redir_fd[0] > 2)
		fd_in = data->redir_fd[0];
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close_all(data, pipe_fd);
		return ;
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		close_all(data, pipe_fd);
		return ;
	}
	close_all(data, pipe_fd);
}

int	nb_cmd(t_data data)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (data.cmd_list[i++].cmd)
		c++;
	return (c);
}

int	in_builtin(char *cmd)
{
	static char	*builtin[7] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	int			i;

	i = 0;
	while (builtin[i] && !ft_strcmp(builtin[i], cmd))
		i++;
	if (builtin[i])
		return (1);
	return (0);
}
