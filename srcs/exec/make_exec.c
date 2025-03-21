/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:50:29 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/21 14:13:29 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	init_dir(t_data *data, int *i)
{
	*i = 0;
	if (create_here_doc(data) && create_redir(data))
		return (1);
	return (0);
}

int	*init_pids(t_data *data)
{
	int	*pids;

	pids = ft_calloc(4, nb_cmd(*data) + 1);
	if (!pids)
		exit_error(data, "failed malloc");
	data->pids = pids;
	data->fd_in = STDIN_FILENO;
	return (pids);
}

void	process_exec(t_data *data, int i, int *pids, int pipe_fd[2])
{
	if (!make_builtin(data, i))
	{
		if (data->cmd_list[i].path == NULL)
			return ;
		pids[i] = fork();
		if (pids[i] == 0)
		{
			dh_free(pids);
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			manage_exec_dir(data, i);
			if (!data->cmd_list[i + 1].cmd)
			{
				if (pipe_fd[0] > 2)
					close(pipe_fd[0]);
				pipe_fd[1] = STDOUT_FILENO;
			}
			manage_pipe(data, pipe_fd);
			if (!data->cmd_list[i].error && data->cmd_list[i].path)
				execve(data->cmd_list[i].path,
					data->cmd_list[i].cmd, data->env);
			exit(127);
		}
	}
}

void	handle_all_cmd(t_data *data, int pipe_fd[2], int *pids, int *i)
{
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (data->cmd_list[*i].cmd && data->cmd_list[*i + 1].cmd
		&& data->cmd_list[*i + 1].cmd[0][0] == '|'
		&& data->cmd_list[*i + 1].cmd && pipe(pipe_fd) == -1)
		exit_error(data, "failed pipe");
	process_exec(data, *i, pids, pipe_fd);
	if (data->fd_in > 2)
		close(data->fd_in);
	if (pipe_fd[1] > 2)
		close(pipe_fd[1]);
	data->fd_in = pipe_fd[0];
	(*i)++;
	if (data->cmd_list[*i].cmd && data->cmd_list[*i].cmd[0]
		&& data->cmd_list[*i].cmd[0][0] == '|'
		&& (*i)++ && !data->cmd_list[*i].cmd)
		ft_printf(2, BOLD RED"/!\\ " BOLD BEIGE
			"Shellokitty: syntax error near \"|\"\n" RESET, NULL);
}

void	make_exec(t_data *data)
{
	int	*pids;
	int	i;
	int	pipe_fd[2];

	if (init_dir(data, &i))
	{
		pids = init_pids(data);
		while (data->cmd_list[i].cmd)
			handle_all_cmd(data, pipe_fd, pids, &i);
		manage_exit_code(data);
		check_exec_error(data);
		dh_free(pids);
	}
	destroy_here_doc(data);
}
