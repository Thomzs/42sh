# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utester_tools.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/28 09:09:16 by thdelmas          #+#    #+#              #
#    Updated: 2019/08/13 15:58:36 by thdelmas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/sh

ask_for_out () {
	while true ; do
		echo '\033[0;31;40m[\o/] [ SELECT DISPLAY ]\033[0;0m'
		echo '[ 0 ] [ Exit / None ]'
		echo '[ 1 ] [ Stdout Tgt Shell ]'
		echo '[ 2 ] [ Stdout Ref Shell ]'
		echo '[ 3 ] [ Stdout Diff ]'
		echo '[ 4 ] [ Stderr Tgt Shell ]'
		echo '[ 5 ] [ Stderr Ref Shell ]'
		echo '[ 6 ] [ Stderr Diff ]'
		echo '[ 7 ] [ Next ]'
		printf '\033[0;31;40m[/o\] [ Choose wisely: \033[0;0m'
		read user_in
		case $user_in in
			0)
				clear
				exit;;
			1)
				clear
				echo "[ 1 ] [ Stdout Tgt Shell: $out_file_tgt ]"
				cat "$out_file_tgt";;
			2)
				clear
				echo "[ 2 ] [ Stdout Ref Shell: $out_file_ref ]"
				cat "$out_file_ref";;
			3)
				clear
				echo "[ 3 ] [ Stdout Diff: $out_file_diff ]"
				cat "$out_file_diff";;
			4)
				clear
				echo "[ 4 ] [ Stderr Tgt Shell: $err_file_tgt ]"
				cat "$err_file_tgt";;
			5)
				clear
				echo "[ 5 ] [ Stderr Ref Shell: $err_file_ref ]"
				cat "$err_file_ref";;
			6)
				clear
				echo "[ 6 ] [ Stderr Diff: $err_file_diff ]"
				cat "$err_file_diff";;
			*)
				break ;
		esac
	done
}

print_kook () {
	if [ "$1" = 'ok' ]
	then
		echo "\033[0;36;40m[ Testing: $2 ] \033[0;32;40m[ OK ]\033[0;0m"
	elif [ "$1" = 'ko' ]
	then
		echo "\033[0;36;40m[ Testing: $2 ] \033[0;31;40m[ KO ]\033[0;0m"
		echo "[ Stdout REPORT ]\nYour shell: $UT_sh_tgt\nRef shell: $UT_sh_ref"
		cat "$UT_out_file_diff"
		echo "[ Stderr REPORT ]\nYour shell: $UT_sh_tgt\nRef shell: $UT_sh_ref"
		cat "$UT_err_file_diff"
	fi
}
