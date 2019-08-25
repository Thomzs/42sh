# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 19:40:02 by thdelmas          #+#    #+#              #
#    Updated: 2019/08/25 19:27:41 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### MAIN FILES ###
C_FILES = \
	main.c \
	sh.c

C_FILES_entrypoint = \
	sh_entrypoint.c \
	sh_loop.c \
	sh_init.c

C_FILES_exitpoint = \
	sh_exitpoint.c \
	sh_free_opts.c \
	sh_free_params.c \

C_FILES_parameters = \
	sh_create_param.c \
	sh_env_params.c \
	sh_putparams.c \
	sh_setenv.c \
	sh_getenv.c \
	sh_unsetenv.c \
	sh_set_pwd.c \
	sh_isset.c \
	#sh_init_var.c \
	#sh_get_env.c \
	#sh_set_env.c \
	#sh_set_value.c \
	#sh_get_value.c \
	#sh_set_shlvl.c \
	#sh_print_env.c \
	#sh_fill_env.c \

C_FILES_command_edition = \
	sh_command_functions.c \
	sh_reader.c \
	sh_cursor_motion.c \
	sh_cursor_motion2.c \
	sh_cursor_motion_word.c \
	sh_cursor_motion_line.c \
	sh_copy_option.c

C_FILES_command_line = \
	sh_prompt.c \
	sh_free_all_ln.c \
	sh_free_one_ln.c \
	sh_command_line.c \
	sh_init_ln.c \
	sh_command_parse.c \
	sh_command_parse2.c \
	sh_strsplit_m.c \

C_FILES_history = \
	sh_get_next_line.c \
	sh_21_history.c \
	sh_cursor_history.c \
	sh_strnjoin.c

C_FILES_signals = \
	
	#signals_handler.c

C_FILES_tokenizer = \
	t_token.c \
	tokenize_input.c \
	compound_tokenizer.c \
	word_interpreter.c \
	operator_interpreter.c \
	opening_chars_handling.c

C_FILES_executer = \
	sh_exec_file.c \
	sh_exec_stdin.c \
	sh_exec_arg.c \
	exec_script.c \
	exec_compound.c \
	exec_simple_command.c \
	redirections_handler.c

C_FILES_debug_mode = \
	debug_mode.c


C_FILES_builtins = \
	sh_cd.c \
	sh_echo.c \
	sh_env.c \
	sh_export.c \
	sh_readonly.c \
	sh_false.c \
	sh_unset.c \
	sh_set.c \
	sh_test.c \
	sh_true.c \
	sh_alias.c \
	sh_unalias.c

C_FILES_tools = \
	sh_tab_fusion.c \
	sh_are_you_sur.c \
	sh_check_path.c \
	sh_error_path.c \
	#sh_find_law.c
	#sh_add_to_path.c

# SUPPA concat loop
C_FILES += $(foreach SUB_DIR,$(SUB_DIRS),$(addprefix $(SUB_DIR)/,$(C_FILES_$(SUB_DIR))))
