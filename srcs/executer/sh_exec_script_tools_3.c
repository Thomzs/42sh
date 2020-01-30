/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/01/30 04:45:54 by ede-ram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_tokenizer.h"
#include "sh_executer.h"
#include "sh_redirections.h"
#include "sh.h"
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include "sh_exitpoint.h"

void	exec_pipeline(t_sh *p, t_token *token_begin, t_token *token_end)
{
	int		bang;
	t_token	*next_sep;

	if (token_begin == token_end)
		return ;
	setup_pipeline_handle_bang(p, &token_begin, token_end, &bang);
	if ((next_sep = find_token_by_key_until(token_begin, token_end, &p->type,
					&p->pipeline_separators)) && next_sep->type == SH_OR)
	{
		if (!exec_pipeline_core(token_begin, token_end))
			return ;
	}
	else
		p->last_cmd_result = exec_command(p, token_begin, token_end);
	if (bang)
		p->last_cmd_result = !p->last_cmd_result;
}

void	exec_and_or(t_sh *p, t_token *token_begin, t_token *token_end)
{
	t_token		*next_separator;
	t_toktype	prev_separator;
	t_toktype	tmp;

	prev_separator = 0;
	while (token_begin && token_begin != token_end && !p->abort_cmd)
	{
		next_separator = find_token_by_key_until(token_begin, token_end,
				&p->type, &p->and_or_separators);
		tmp = p->type;
		if (!prev_separator || (prev_separator == SH_AND_IF &&
					!p->last_cmd_result)
				|| (prev_separator == SH_OR_IF && p->last_cmd_result))
			exec_pipeline(p, token_begin, next_separator);
		prev_separator = tmp;
		if (next_separator == token_end)
			return ;
		token_begin = (next_separator) ? next_separator->next : 0;
		while (token_begin && token_begin->type == SH_NEWLINE && token_begin != token_end)
			token_begin = token_begin->next;
	}
}

void	close_cpy_std_fds(t_sh *p)
{
	close(p->cpy_std_fds[0]);
	close(p->cpy_std_fds[1]);
	close(p->cpy_std_fds[2]);
	p->cpy_std_fds[0] = -1;
	p->cpy_std_fds[1] = -1;
	p->cpy_std_fds[2] = -1;
}

void	del_all_group_processes(t_process_group *tmp)
{
	if (!tmp)
		return ;
	if (tmp->next)
		del_all_group_processes(tmp->next);
	waitpid(-tmp->pgid, 0, WNOHANG);
	free(tmp);
}

void	del_existing_process_group(t_sh *p, pid_t pgid)
{
	t_process_group	**pgroup;
	t_process_group	*tmp;

	pgroup = &p->existing_process_groups;
	if (*pgroup && (*pgroup)->pgid == pgid)
	{
		tmp = *pgroup;
		p->existing_process_groups = tmp->next;
		printf("del pgrp %i\n", tmp->pgid);
		free(tmp);
		return ;
	}
	while (*pgroup && (*pgroup)->next->pgid != pgid)
		pgroup = &((*pgroup)->next);
	if (*pgroup && (*pgroup)->next->pgid == pgid)
	{
		tmp = (*pgroup)->next;
		(*pgroup)->next = tmp->next;
		printf("del pgrp %i\n", tmp->pgid);
		free(tmp);
	}
}

void	wait_for_zombies(void)
{
	t_process_group	*pgroup;

	pgroup = sh()->existing_process_groups;
	while (pgroup)
	{
		if (waitpid(-pgroup->pgid, 0, WNOHANG) < 0)
			del_existing_process_group(sh(), pgroup->pgid);
		pgroup = pgroup->next;
	}
}

void	store_existing_group_process(t_sh *p, pid_t pgid)
{
	t_process_group	**pgroup;

	pgroup = &p->existing_process_groups;
	while (*pgroup)
		pgroup = &((*pgroup)->next);
	if (!(*pgroup = (t_process_group*)malloc(sizeof(t_process_group))))
		destructor(43);
	(*pgroup)->pgid = pgid;
	(*pgroup)->next = 0;
	printf("CREATE PGRP %i\n", pgid);
}

void	create_process_group_give_terminal_access(t_sh *p, pid_t pid,
		int foreground)
{
	pid_t	new_pgid;

	if (p->pgid_current_pipeline)
		new_pgid = p->pgid_current_pipeline;
	else
		new_pgid = pid;
	setpgid(pid, new_pgid);
	if (p->pid_main_process == getpid())
		store_existing_group_process(p, new_pgid);
	if (foreground || (p->force_setpgrp_setattr))
	{
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp((p->cpy_std_fds[0] > -1) ? p->cpy_std_fds[0] : 0, pid);
		tcsetattr((p->cpy_std_fds[0] > -1) ? p->cpy_std_fds[0] : 0,
				TCSANOW, &p->extern_termios);
		signal(SIGTTOU, SIG_DFL);
	}
}

void	sig_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}
