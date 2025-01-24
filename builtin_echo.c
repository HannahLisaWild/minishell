/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:13:13 by hawild            #+#    #+#             */
/*   Updated: 2025/01/23 23:02:58 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_echo(t_command *cmd, t_envvar **env_list)
{
	int	i;
	int	fd;
	int	newline;

	(void)env_list;
	i = 1;
	newline = handle_newline_option(cmd, &i);
	echo_input_file(cmd);
	fd = open_output_file(cmd);
	if (fd == -1)
		return (1);
	write_args_to_output(cmd, fd, i);
	handle_newline_write(newline, fd);
	if (fd != STDOUT_FILENO)
		close(fd);
	if (cmd->exit_status != 1)
		cmd->exit_status = 0;
	return (0);
}
