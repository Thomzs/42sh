/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/20 05:09:11 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_word_expansion.h"
#include "sh_tokenizer.h"
#include "sh_env.h"
#include "sh_tokens.h"

int		sh_in_expansion(t_exp *exp, int i)
{
	if (exp->content[exp->i] == '{')
	{
		sh_parameter_expansion(exp);
		if (exp->opt == ERROR)
			return (sh_word_error(exp));
	}
	else if (exp->content[exp->i] == '(' || exp->content[exp->i] == '`')
	{
		if (exp->content[exp->i + 1] == '(')
			sh_arithmetic_expansion(exp);
		else
			sh_subsh_expansion(exp);
	}
	else
		sh_simple_expansion(exp);
	if (sh()->exp_rec == 1)
	{
		exp->first_i = i;
		sh_sub_token(exp);
		free(exp->content);
		exp->i = sh_calcul_exp_i(i, ft_strlen(exp->value));
		exp->content = ft_strdup(exp->tok->content);
		ft_memdel((void**)&exp->value);
	}
	return (0);
}

int		sh_expansion_quote(t_exp *exp)
{
	if (exp->quote == SH_BQUOTE || (exp->quote - SH_DQUOTE) == SH_BQUOTE)
	{
		exp->quote = exp->quote - SH_BQUOTE;
		return (0);
	}
	if (exp->quote != SH_DQUOTE && exp->content[exp->i] == '\'')
	{
		if (exp->quote == SH_QUOTE)
			exp->quote = 0;
		else
			exp->quote = SH_QUOTE;
	}
	else if (exp->quote != SH_QUOTE && exp->content[exp->i] == '"')
	{
		if (exp->quote == SH_DQUOTE)
			exp->quote = 0;
		else
			exp->quote = SH_DQUOTE;
	}
	else if (exp->quote != SH_QUOTE && exp->content[exp->i] == '\\')
		exp->quote = exp->quote + SH_BQUOTE;
	return (1);
}

int		sh_word_expansion(t_exp *exp)
{
	int		i;

	sh()->exp_rec++;
	i = 0;
	while (exp->content && (exp->content)[exp->i])
	{
		i = exp->i;
		if (sh_expansion_quote(exp) && exp->quote != SH_QUOTE
			&& exp->quote != SH_BQUOTE && (exp->quote - SH_DQUOTE) != SH_BQUOTE
			&& exp->content[exp->i + 1]
			&& (exp->content[exp->i] == '$' || exp->content[exp->i] == '`'))
		{
			if (exp->content[exp->i] == '$')
				exp->i++;
			if (sh_in_expansion(exp, i))
				return (1);
		}
		else
			exp->i++;
	}
	sh()->exp_rec--;
	return (0);
}

void	sh_del_all_blank_tok(t_token **tok)
{
	t_token		*cpy;

	cpy = *tok;
	while (*tok && (*tok)->content && !(*tok)->content[0])
	{
		cpy = *tok;
		(*tok) = (*tok)->next;
		ft_memdel((void**)&(cpy->content));
		free(cpy);
	}
}

t_token	*sh_expansion(char *tok_content, t_env **env, short ifs)
{
	t_exp	exp;
	t_token	*new_tok;

	tok_content = ft_strdup(tok_content);
	sh_tilde_expansion(&tok_content, sh()->params);
	sh_init_exp(env, &exp, tok_content);
	exp.tok->sub = NULL;
	exp.tok->next = NULL;
	sh_word_expansion(&exp);
	new_tok = sh_quote_removal(exp.tok, sh_getev_value("IFS"), ifs);
	sh_del_all_blank_tok(&new_tok);
	sh_free_exp(&exp, &tok_content);
	return (new_tok);
}
