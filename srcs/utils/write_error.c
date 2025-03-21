/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:46:21 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/21 16:27:05 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	put_exit_code(t_data *data, int i, int msg_code)
{
	if (msg_code == 1)
	{
		ft_printf(2, BOLD RED"/!\\ "
			BOLD BEIGE "Shellokitty: %s: Is a directory\n"
			RESET, data->cmd_list[i].cmd[0]);
		data->exit_status = 126;
	}
}

int	check_for_dir(t_data *data, int i)
{
	struct stat	path_stat;
	int			valid;

	valid = 0;
	if (!stat(data->cmd_list[i].path, &path_stat))
		valid = S_ISDIR(path_stat.st_mode);
	if (valid)
		put_exit_code(data, i, 1);
	else if ((data->cmd_list[i].cmd[0][0] == '/'
		|| (data->cmd_list[i].cmd[0][0] && data->cmd_list[i].cmd[0][1] == '/')))
	{
		if (data->cmd_list[i].path && access(data->cmd_list[i].path, F_OK)
		== -1)
		{
			ft_printf(2, BOLD RED"/!\\ "
				BOLD BEIGE
				"Shellokitty: %s: No such file or directory\n" RESET,
				data->cmd_list[i].cmd[0]);
			valid++;
		}
	}
	return (valid);
}

void	print_error(t_data *data, int code, char *str)
{
	if (code == 0)
	{
		ft_printf(2, BOLD RED"/!\\ "BOLD BEIGE
			"Shellokitty: %s: No such file or directory\n" RESET, str);
		data->exit_status = 127;
	}
	else if (code == 1)
	{
		data->exit_status = 127;
		ft_printf(2, BOLD RED"/!\\ " BOLD BEIGE
			"Shellokitty: %s: command not found\n" RESET, str);
	}
	else if (code == 2)
		ft_printf(2, BOLD RED"/!\\ " BOLD BEIGE
			"Shellokitty: %s permision denied\n" RESET, str);
}

void	check_exec_error(t_data *data)
{
	int	i;

	i = -1;
	while (data->cmd_list[++i].cmd)
	{
		if (data->cmd_list[i].builtin)
			continue ;
		if (check_for_dir(data, i))
			data->exit_status = 126;
		else if (data->cmd_list[i].cmd[0][0] == '|')
			continue ;
		else if (!ft_strncmp("./", data->cmd_list[i].cmd[0], 2) || data->cmd_list[i].cmd[0][0] == '/' || data->cmd_list[i].cmd[0][ft_strlen(data->cmd_list[i].cmd[0]) -1] == '/')
			print_error(data, 0, data->cmd_list[i].cmd[0]);
		else if (!data->cmd_list[i].path
			&& !(ft_strchr("<>", data->cmd_list[i].cmd[0][0])))
			print_error(data, 1, data->cmd_list[i].cmd[0]);
		else if (data->cmd_list[i].path
			&& access(data->cmd_list[i].path, X_OK) == -1
			&& !(ft_strchr("<>", data->cmd_list[i].cmd[0][0])))
			print_error(data, 2, data->cmd_list[i].cmd[0]);
	}
}
