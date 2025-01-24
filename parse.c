/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 23:06:03 by kforfoli          #+#    #+#             */
/*   Updated: 2025/01/24 15:06:29 by kforfoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	the_loop(t_token *token, t_command *cmd, t_envvar **env_list,
		t_shell_status *e_status)
{
	t_token		*c_t;
	t_command	*current_cmd;
	char		*merged_arg;
	t_token		*new_token;
	char		*temp;

	c_t = token;
	current_cmd = cmd;
	while (c_t->next && c_t->next->type == TOKEN_MERGE_FLAG && c_t->next->next)
	{
		merged_arg = ft_strdup(c_t->value);
		new_token = c_t;
		c_t = c_t->next->next;
		if (c_t->type == TOKEN_EXIT_STATUS)
			handle_exit_status_token(c_t, e_status);
		if (c_t->type == TOKEN_ENV_VAR)
			handle_token_env_var(env_list, c_t, current_cmd);
		temp = merged_arg;
		merged_arg = ft_strjoin(temp, c_t->value);
		free(temp);
		c_t->value = ft_strdup(merged_arg);
		c_t->type = TOKEN_WORD;
		*token = *c_t;
		free(merged_arg);
	}
}

int	handle_redirection_or_pipe(t_token **current_token, t_command **current_cmd,
		t_command **head, t_command **tail)
{
	if ((*current_token)->type == TOKEN_PIPE)
	{
		if (handle_token_pipe(current_token, current_cmd, tail) == 1)
			return (1);
	}
	else if ((*current_token)->type == TOKEN_INPUT_REDIRECT)
	{
		if (handle_token_input_redirect(current_cmd, current_token) == 1)
			return (1);
	}
	else if ((*current_token)->type == TOKEN_OUTPUT_REDIRECT
		|| (*current_token)->type == TOKEN_APPEND_REDIRECT)
	{
		if (handle_token_output_append(current_cmd, current_token, head,
				tail) == 1)
			return (1);
	}
	else if ((*current_token)->type == TOKEN_HEREDOC)
	{
		if (handle_token_heredoc(current_token, current_cmd, head, tail) == 1)
			return (1);
	}
	return (0);
}

static void	initialize_pipeline_context(t_parse_pipeline_context *context,
		t_token **tokens, t_envvar **env_list, t_shell_status *e_status)
{
	context->current_token = *tokens;
	context->head = NULL;
	context->tail = NULL;
	context->current_cmd = NULL;
	context->env_list = env_list;
	context->e_status = e_status;
}

static int	process_token(t_parse_pipeline_context *context)
{
	t_token	*current_token;

	current_token = context->current_token;
	if (current_token->type == TOKEN_WORD || current_token->type == TOKEN_QUOTE
		|| current_token->type == TOKEN_ENV_VAR
		|| current_token->type == TOKEN_EXIT_STATUS)
	{
		if (!context->current_cmd)
			initialize_new_command(&context->current_cmd, &context->head,
				&context->tail);
		if (current_token->type == TOKEN_ENV_VAR)
			handle_token_env_var(context->env_list, current_token,
				context->current_cmd);
		if (current_token->type == TOKEN_EXIT_STATUS)
			handle_exit_status_token(current_token, context->e_status);
		the_loop(current_token, context->current_cmd, context->env_list,
			context->e_status);
		if (ft_strcmp(current_token->value, "dontadd") != 0)
			add_argument(context->current_cmd, current_token->value);
	}
	return (0);
}

t_command	*parse_pipeline(t_token **tokens, t_envvar **env_list,
		t_shell_status *e_status)
{
	t_parse_pipeline_context	context;

	initialize_pipeline_context(&context, tokens, env_list, e_status);
	*tokens = context.current_token;
	while (context.current_token)
	{
		if (process_token(&context) == 1)
			return (context.current_cmd);
		if (handle_redirection_or_pipe(&context.current_token,
				&context.current_cmd, &context.head, &context.tail) == 1)
			return (context.current_cmd);
		context.current_token = context.current_token->next;
	}
	return (context.head);
}
