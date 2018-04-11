/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:20:50 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/11 13:03:13 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"

typedef struct s_shell	t_shell;
typedef struct s_av		t_av;
typedef struct s_exec	t_exec;

int		is_numeric_string(char *str);
char	**add_element_to_char_array(char **array, char *string);
char	**create_char_array_copy(char **src, int extra);
char	**history_array(t_shell *sh);
char	*basename(char *str);
char	*builtin_cd_get_kv(t_shell *sh, char *variable);
char	*builtin_cd_get_path(t_shell *sh);
char	*create_kv_string(char *key, char *value);
char	*dir_slash_exec(char *dir, char *cmd);
char	*file_get_contents(char *filename);
char	*find_command_path(t_shell *sh, char *cmd);
char	*history_file_name(t_shell *sh);
char	*history_get_item(t_shell *sh, int index);
char	*kv_array_get_key_value(char **array, char *key);
int		build_child_argv_list(t_shell *sh, int *i, int k, int sub_op);
int		builtin_cmd_index(char *cmd);
int		count_char_array(char **array);
int		is_valid_executable_file(char *filename);
int		kv_array_get_key_index(char **array, char *key);
int		main(int argc, char **argv, char **envp);
int		mini_parse(t_shell *sh, t_av *av, int *i, int *k);
int		path_has_executable(char *path, char *cmd);
int		tab_all_commands_longer(t_shell *sh, t_exec **a);
int		tab_all_commands_share_letter(t_exec **a, int index, char c);
int		tab_count_matches(t_shell *sh);
int		tab_max_length(t_exec **array);
int		tab_mini_complete(t_shell *sh, t_exec **a);
int		ft_isalnum2(int c);
int		handle_dollar_sign(t_av *av, t_shell *sh, int *i, int *k);
int		handle_strong_quote(t_av *av, int *i, int *k);
int		handle_weak_quote(t_av *av, t_shell *sh, int *i, int *k);
int		is_alphanumeric_string(char *str);
int		string_has_whitespace(char *str);
int		unmatched_quote_error(t_av *av, char quote);
t_shell	*init_shell(int argc, char **argv, char **envp);
t_av	*init_av_buffers(t_shell *sh);
void	add_string_to_child_argv(t_shell *sh, char *str, int *k);
void	add_to_list_of_executables(t_shell *sh, char *cmd);
void	build_list_of_executables(t_shell *sh, char **folders);
int		builtin_cd(t_shell *sh);
int		builtin_cd_save_cwd(t_shell *sh, char *variable);
int		builtin_echo(t_shell *sh);
int		builtin_env(t_shell *sh);
int		builtin_exit(t_shell *sh);
int		builtin_help(t_shell *sh);
int		builtin_setenv(t_shell *sh);
int		builtin_setenv_kv(t_shell *sh, int arg_count);
int		builtin_unsetenv(t_shell *sh);
void	check_special_keys(t_shell *sh);
void	clean_up(t_shell *sh);
void	cleanup_av_buffers(t_av *av);
void	clear_input_buffers(t_shell *sh);
void	destroy_char_array(char **array);
void	destroy_list_of_executables(t_shell *sh);
void	display_shell_prompt(void);
void	end_of_input(t_shell *sh);
void	execute(t_shell *sh);
int		execute_external_cmd(t_shell *sh);
void	fatal_error(t_shell *sh);
void	fatal_error_message(t_shell *sh, char *msg);
int		fork_exec_wait(t_shell *sh, char *fullpath);
void	history_append_to_file(t_shell *sh);
void	increase_buffer(t_shell *sh);
void	init_input_buffer(t_shell *sh);
void	insert_key_into_buffer(t_shell *sh);
void	key_backspace_function(t_shell *sh);
void	key_ctrl_a_function(t_shell *sh);
void	key_ctrl_e_function(t_shell *sh);
void	key_ctrl_k_function(t_shell *sh);
void	key_ctrl_l_function(t_shell *sh);
void	key_delete_function(t_shell *sh);
void	key_down_arrow_function(t_shell *sh);
void	key_left_arrow_function(t_shell *sh);
void	key_right_arrow_function(t_shell *sh);
void	key_tab_function(t_shell *sh);
void	key_up_arrow_function(t_shell *sh);
void	kv_array_remove_key(char **array, char *key);
void	kv_array_set_key_value(char ***array, char *key, char *value);
void	raw_read(t_shell *sh);
void	reprint_input(t_shell *sh);
void	restore_partial_input(t_shell *sh);
void	sigint_handler(int signo);
void	tab_bubble_sort(t_exec **a, int count);
void	tab_print_columns(t_exec **array, int count);
void	tab_remove_duplicates(t_exec **array, int *count);
void	terminal_init(t_shell *sh);
void	termios_restore_settings(t_shell *sh);
void	termios_save_settings(t_shell *sh);

#endif
