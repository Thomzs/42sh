/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/20 02:24:16 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_tokenizer.h"
#include "libft.h"
#include "sh_error.h"
#include "sh.h"

t_toktype	protect_pipe(t_toktool *t)
{
	int	tmp;

	tmp = t->i;
	forward_blanks_newline(t);
	if (t->input[t->i] == '&' || t->input[t->i] == ';' || t->input[t->i] == '!')
	{
		sh_dprintf(2, "42sh : %c not valid after '|'\n", t->input[t->i]);
		return (SH_SYNTAX_ERROR);
	}
	t->i = tmp;
	return (SH_NULL);
}

t_toktype	handle_redirections_operators(t_toktool *t, t_toktype type,
		t_token **p_actual)
{
	if (t->word_nb == 1 && operator_cant_be_first(type))
	{
		sh_dprintf(2, "Syntax error: operator cant be first in command \
		-%s\n", t->input + ((t->i > 2) ? t->i - 2 : 0));
		return (SH_SYNTAX_ERROR);
	}
	if (is_newline_separator(type))
		t->word_nb = 1;
	if (is_redirection_operator(type))
		return (fill_redirection(t, p_actual, type));
	if (type == SH_OR || type == SH_AND_IF || type == SH_OR_IF)
	{
		if (type == SH_OR && protect_pipe(t) == SH_SYNTAX_ERROR)
			return (SH_SYNTAX_ERROR);
		if (sh_record_here_doc(t, sh()->here) == SH_SYNTAX_ERROR)
		{
			sh_dprintf(2, "parse error\n");
			return (SH_SYNTAX_ERROR);
		}
		return (input_finish_cmd(t));
	}
	return (0);
}

t_toktype	treat_operator(t_toktool *t, t_token **p_actual,
		t_toktype actual_compound)
{
	t_toktype	type;
	int			op_begin;

	op_begin = t->i;
	if ((type = read_n_skip_operator(t)))
	{
		if (type == SH_AND && (t->input[t->i] == '<' || t->input[t->i] == '>'))
		{
			t->i--;
			return (treat_redirection(t, p_actual, 1));
		}
		if (type == SH_DSEMI)
		{
			if (actual_compound == SH_CASE)
				return (SH_DSEMI);
			type = SH_SEMI;
		}
		(*p_actual)->next = create_token(type, op_begin, 0);
		*p_actual = (*p_actual)->next;
		return (handle_redirections_operators(t, type, p_actual));
	}
	return (0);
}
