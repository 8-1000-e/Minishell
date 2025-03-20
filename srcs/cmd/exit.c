/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:03:03 by edubois-          #+#    #+#             */
/*   Updated: 2025/03/20 14:47:37 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_exit_message_only(t_data *data, int i)
{
	int	arraylen;
	int	error[2];
	int	exit_code[2];

	arraylen = ft_arraylen(data->cmd_list[i].cmd);
	error[0] = 0;
	error[1] = 0;
	if (arraylen > 1)
	{
		exit_code[0] = str_to_long(data->cmd_list[i].cmd[1], &error[0]);
		if (arraylen == 3)
			exit_code[1] = str_to_long(data->cmd_list[i].cmd[2], &error[1]);
	}
	else
		return ;
	if (arraylen >= 3 && !error[0])
		ft_printf(2, BOLD BEIGE
			"Shellokitty: exit: too many arguments\n" RESET);
	else if (error[0])
		ft_printf(2, BOLD RED "/!\\ "
			BOLD BEIGE "Shellokitty: exit: %s: numeric argument required\n"
			RESET, data->cmd_list[i].cmd[1]);
	if (!error[0])
		data->exit_status = exit_code[0];
}

void	init_exit(t_data *data, int (*error)[2], int (*exit_code)[2], int type)
{
	if (type == 1)
	{
		*exit_code[0] = str_to_long(data->cmd_list[0].cmd[1], error[0]);
		if (data->cmd_list[0].cmd[2])
			*exit_code[1] = str_to_long(data->cmd_list[0].cmd[2], error[1]);
	}
	else if (type == 2)
	{
		data->exit = 1;
		printf(BOLD RED "Exit\n" RESET);
		return ;
	}
}

void	make_exit(t_data *data, int msg_code)
{
	if (msg_code == 1)
	{
		ft_printf(2, BOLD RED "Exit\n/!\\ "
			BOLD BEIGE "Shellokitty: exit: too many arguments\n" RESET);
		return ;
	}
	else if (msg_code == 2)
	{
		data->exit = 1;
		printf(BOLD RED "Exit\n" RESET);
	}
	else if (msg_code == 3)
	{
		printf(RED "Exit\n" RESET);
		ft_printf(2, BOLD RED "/!\\ "
			BOLD BEIGE "Shellokitty: exit: %s: numeric argument required\n"
			RESET, data->cmd_list[0].cmd[1]);
		data->exit = 1;
		data->exit_status = 2;
	}
}

void	make_all_exit(t_data *data, int msg_code, int exit_code[2])
{
	if (msg_code == 4)
	{
		ft_printf(2, BOLD RED "Exit\n/!\\ "
			BOLD BEIGE "Shellokitty: exit: too many arguments\n" RESET);
		return ;
	}
	else if (msg_code == 5)
	{
		printf(RED "Exit\n" RESET);
		data->exit = 1;
		data->exit_status = exit_code[0];
		return ;
	}
	else if (msg_code == 6)
	{
		ft_printf(2, BOLD RED "Exit\n/!\\ "
			BOLD BEIGE "Shellokitty: exit: too many arguments\n" RESET);
		data->exit = 1;
		data->exit_status = 1;
		return ;
	}
	ft_printf(2, BOLD RED "Exit\n/!\\ "
		BOLD BEIGE "Shellokitty: exit: too many arguments\n" RESET);
	data->exit_status = 1;
}

void	ft_exit(t_data *data, int i)
{
	int	exit_code[2];
	int	error[2];
	int	arraylen;

	if (i || nb_cmd(*data) > 1)
		return (ft_exit_message_only(data, i));
	arraylen = ft_arraylen(data->cmd_list[0].cmd);
	error[0] = 0;
	error[1] = 0;
	if (arraylen > 3)
		return (make_exit(data, 1));
	if (arraylen > 1)
		init_exit(data, &error, &exit_code, 1);
	else
		return (init_exit(data, &error, &exit_code, 2));
	if (error[0])
		make_exit(data, 3);
	else if (!error[0] && error[1])
		return (make_all_exit(data, 4, exit_code));
	else if (!error[0] && arraylen == 2)
		return (make_all_exit(data, 5, exit_code));
	else if (arraylen >= 3 && !error[0] && error[1])
		return (make_all_exit(data, 6, exit_code));
	else if (arraylen >= 3 && !error[0] && !error[1])
		make_all_exit(data, 0, exit_code);
}
