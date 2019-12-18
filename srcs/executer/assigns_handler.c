/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigns_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:21:28 by ede-ram           #+#    #+#             */
/*   Updated: 2019/12/13 05:20:04 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sh_executer.h"
#include "sh_word_expansion.h"
#include "sh_tokenizer.h"

void	handle_assigns(t_sh *p)
{
	t_env	*assign;
	t_env	*tmp;

	assign = p->assign_lst;
	while (assign)
	{
		if (sh_isset(assign->key))
		{
			tmp = p->tmp_assign_lst;
			p->tmp_assign_lst = sh_create_param(assign->key);
			p->tmp_assign_lst->value = ft_strdup(sh_getev_value(assign->key));
			p->tmp_assign_lst->next = tmp;
		}
		sh_setev(assign->key, assign->value);
		assign = assign->next;
	}
}

void	restore_before_assigns(t_sh *p)
{
	t_env	*assign;
	t_env	*tmp;

	assign = p->assign_lst;
	while (assign)
	{
		sh_unsetev(assign->key, &(sh()->params));
		assign = assign->next;
	}
	assign = p->tmp_assign_lst;
	while (assign)
	{
		sh_setev(assign->key, assign->value);
		tmp = assign;
		assign = assign->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	p->tmp_assign_lst = 0;
}

int		handle_no_cmd_name(t_sh *p, char **child_argv)
{
	t_env	*assign;

	assign = p->assign_lst;
	while (assign)
	{
		sh_setev(assign->key, assign->value);
		assign = assign->next;
	}
	ft_free_tabstr(child_argv);
	sh_del_all_env(p->assign_lst);
	p->assign_lst = 0;
	delete_close_all_pipe_lst(p->pipe_lst);
	p->pipe_lst = 0;
	//close open files
	return (0);
}

void	stock_assign(t_sh *p, t_token *token, int *nb_assign)
{
	t_env	*tmp;
	char	*equal;
	t_token	*tmpt;

	(*nb_assign)++;
	tmp = p->assign_lst;
	equal = ft_strchr(token->content, '=');
	*equal = 0;
	//if (is_not_valid_assign_name(token->content))
	//	print error
	//	return;
	p->assign_lst = sh_create_param(token->content);
	*equal = '=';
	p->assign_lst->value = ft_strdup(equal + 1);
	if ((tmpt = sh_expansion(p->assign_lst->value, &(p->params), 0)))
	{
		free(p->assign_lst->value);
		p->assign_lst->value = ft_strdup(tmpt->content);
		free_ast(tmpt);
	}
	else
	{
		free(p->assign_lst->value);
		p->assign_lst->value = ft_strdup("");
	}
	p->assign_lst->next = tmp;
}

void	del_n_assign_lst(t_sh *p, int n)
{
	t_env	*tmp;

	while (n-- && p->assign_lst)
	{
		free(p->assign_lst->key);
		free(p->assign_lst->value);
		tmp = p->assign_lst->next;
		free(p->assign_lst);
		p->assign_lst = tmp;
	}
}
