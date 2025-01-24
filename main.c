/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 23:05:39 by kforfoli          #+#    #+#             */
/*   Updated: 2025/01/24 14:55:47 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_execute_external_running;

void	clear_buffer(void)
{
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	update_exit_status(t_command *commands, t_shell_status *e_status)
{
	t_command	*current;

	current = commands;
	if (!current->next)
		e_status->last_exit_status = current->exit_status;
}

void	calc_stat(int *status)
{
	if (*status == 400)
		exit(0);
	if (*status == 500)
		exit(2);
}

void	ft_run_shell(t_envvar *env_list, t_builtin_cmd *builtins,
		t_command *commands, t_token *tokens)
{
	char			*input;
	int				status;
	t_shell_status	e_status;
	int				input_status;

	input = NULL;
	status = 0;
	initialize_shell(&env_list, builtins, &e_status);
	while (status == 0)
	{
		input_status = read_and_tokenize_input(&input, &tokens);
		if (check_input_status(input_status, &e_status) == 2)
			continue ;
		else if (check_input_status(input_status, &e_status) == -1)
			break ;
		commands = parse_commands(&tokens, &env_list, &e_status);
		status = ft_execute_parsed_commands(commands, builtins, &env_list,
				&e_status);
		update_exit_status(commands, &e_status);
		cleanup_iteration(&input, tokens, commands);
	}
	cleanup_shell(&env_list, builtins);
	g_execute_external_running = 0;
	calc_stat(&status);
}

int	main(void)
{
	t_envvar		*env_list;
	t_token			*tokens;
	t_command		*commands;
	t_builtin_cmd	builtins[NUM_BUILTINS];

	env_list = NULL;
	tokens = NULL;
	commands = NULL;
	ft_run_shell(env_list, builtins, commands, tokens);
	return (0);
}
