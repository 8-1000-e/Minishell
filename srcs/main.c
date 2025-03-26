/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:56:16 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/24 16:57:11 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	print_art(void)
{
	int			fd;
	static char	buf[5000] = {0};

	fd = open("kitty.txt", O_RDONLY);
	if (fd > 2)
	{
		read(fd, buf, 5000);
		printf("%s", buf);
		close(fd);
	}
}

void	do_shell(t_data *data, char *rl)
{
	if (!fill_line_data(data, rl) && !check_pipe(data, rl))
		make_exec(data);
	reset_data(data);
}

int	main(int arg_c, char **arg_v, char **env)
{
	t_data	data;
	char	*rl;

	print_art();
	data = (t_data){0};
	keep_data(&data);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	ms_setup_lst_env(&data, env);
	rl = bt_prompt(&data);
	while (rl && !data.exit)
	{
		if (!rl)
			break ;
		if (*rl)
			do_shell(&data, rl);
		if (!data.exit)
			rl = bt_prompt(&data);
	}
	exit(data.exit_status % 256);
	(void)arg_c;
	(void)arg_v;
}
