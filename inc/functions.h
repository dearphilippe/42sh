/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:20:50 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/08 01:44:10 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <dirent.h>
# include "ft.h"
# include "parse.h"

typedef struct s_shell		t_shell;
typedef struct s_av			t_av;
typedef struct s_process	t_process;
typedef struct s_exec		t_exec;
typedef	t_process			t_proc;
typedef t_autocomplet		t_autoc;

int		word_length_backwards(char *right, char *boundary);
void	tab_files_show_columns(t_shell *sh, char *path, char *search);

char	*insert_character(char *dst, char c);
int		tab_max_lengthf(char **array);
void	tab_bubble_sortf(char **a, int count);
void	col_print_loopf(int cw, int nc, int count, char **a);
void	tab_print_columnsf(char **array, int count);
int		tab_files_valid_directory(char *path);
int		tab_files_count_match_in_dir(char *path, char *search);
char	**tab_files_array_of_matches(char *path, char *search);
int		tab_files_array_of_matches_help1(char ***a, char *search, int *len);
void	tab_files_array_of_matches_1(t_shell *sh, char **a, int i);
void	tab_files_array_of_matches_2(t_shell *sh);
void	tab_files_array_of_matches_3(t_shell *sh, char **a, int *i);
int		tab_files_mini_complete(t_shell *sh, char **a);
char	*key_tab_part_str(t_shell *sh);
char	*key_tab_last_word(char *str);
t_exec	**tab_array_of_matches(t_shell *sh, char *str);
char	**tab_files_array_of_matches_help2(char **a, DIR *dirp, int i);
t_autoc	type_to_complet(char *str);
int		builtin_export_kv(t_shell *sh, char **argv, int arg_count);
int		builtin_export(t_shell *sh, char **argv);
int		builtin_unexport(t_shell *sh, char **argv);
int		builtin_printlocal(t_shell *sh, char **argv);
char	**add_element_to_char_array(char **array, char *string);
char	**build_child_argv_list(t_shell *sh, char *cmd);
char	**create_char_array_copy(char **src, int extra);
char	**history_array(t_shell *sh);
char	*basename(char *str);
char	*builtin_cd_get_kv(t_shell *sh, char *variable);
char	*builtin_cd_get_path(t_shell *sh, char **argv);
char	*create_kv_string(char *key, char *value);
char	*delete_backslash_in_double_quote(char *str);
char	*delete_start_space(char *str);
char	*dir_slash_exec(char *dir, char *cmd);
char	*file_get_contents(char *filename);
char	*find_command_path(t_shell *sh, char *cmd);
char	*get_type_string(char *str);
char	*history_file_name(t_shell *sh);
char	*history_get_item(t_shell *sh, int index);
char	*kv_array_get_key_value(char **array, char *key);
char	*remove_start_space(char *str);
int		ast_len(t_ast *head);
int		main(int argc, char **argv, char **envp);
int		process_execute(t_shell *sh, t_process *p);
int		ast_ambiguous_error(char *msg);
int		ast_is_ambiguous(t_ast *ast);
int		ast_main(void);
int		builtin_cd(t_shell *sh, char **argv);
int		builtin_cd_save_cwd(t_shell *sh, char *variable);
int		builtin_cmd_index(char *cmd);
int		builtin_echo(t_shell *sh, char **argv);
int		builtin_env(t_shell *sh, char **argv);
int		builtin_exit(t_shell *sh, char **argv);
int		builtin_help(t_shell *sh, char **argv);
int		builtin_setenv(t_shell *sh, char **argv);
int		builtin_setenv_kv(t_shell *sh, char **argv, int arg_count);
int		builtin_unsetenv(t_shell *sh, char **argv);
int		col_print_cmd(char *s, int j, int cw, int nc);
int		copy_str(int i, int res, char **word, char *cpy);
int		count_char_array(char **array);
int		execute_external_cmd(t_shell *sh, t_process *p);
int		fork_exec_wait(t_shell *sh, t_process *p, char *fullpath);
int		get_nbr_instructions(t_ast *lex);
int		get_nbr_redirection(char *str);
int		group_process_execute(t_shell *sh, t_process **group, int i);
int		group_process_fix_path(t_process **group, int i);
int		group_process_wait(t_process **group);
int		has_paire_quote(t_shell *sh);
int		is_end_of_argument(char c);
int		is_valid_executable_file(char *filename);
int		kv_array_get_key_index(char **array, char *key);
int		mini_parse(t_shell *sh, t_av *av, int *i, int *k);
int		parse_help(t_ast **lex, t_ast **node, char **word, char **term);
int		parse_quote(char **word, char *str);
int		parse_quote_double(char **word, char *str);
int		parse_quote_single(char **word, char *str);
int		path_has_executable(char *path, char *cmd);
int		set_backslash(char *dest, char *str, int i);
int		tab_all_commands_longer(t_shell *sh, t_exec **a);
int		tab_all_commands_share_letter(t_exec **a, int index, char c);
int		tab_count_matches(t_shell *sh, char *str);
int		tab_max_length(t_exec **array);
int		tab_mini_complete(t_shell *sh, t_exec **a);
int		close_pipes(t_process **group);
int		ft_isalnum2(int c);
int		handle_dollar_sign(t_av *av, t_shell *sh, int *i, int *k);
int		handle_strong_quote(t_av *av, int *i, int *k);
int		handle_tilde(t_av *av, t_shell *sh, int *i, int *k);
int		handle_weak_quote(t_av *av, t_shell *sh, int *i, int *k);
int		is_alphanumeric_string(char *str);
int		is_numeric_string(char *str);
int		string_has_whitespace(char *str);
int		unmatched_quote_error(t_av *av, char quote);
size_t	free_parse_ast(char **term);
t_ast	*ast_new(char *name, t_type type);
t_ast	**ast_create_tree(char *str);
t_ast	*cpy_ast(char *word, t_ast *lex, t_ast *node);
t_ast	*parse_lexer(char *str);
t_av	*init_av_buffers(char *cmd);
t_shell	*init_shell(int argc, char **argv, char **envp);
t_type	get_type(char *str);
t_proc	*process_prepare(t_shell *sh, t_ast *ast);
void	execute(t_shell *sh, char *cmd);
void	main_helper(t_shell *sh, int *ec);
void	main_ptr(t_shell *sh, t_ast **ptr, t_process **p, int *ec);
void	process_destroy(t_process *p);
void	ptr_not_null(t_shell *sh, t_ast **ptr, t_process **p, int *ec);
void	ptr_null(t_shell *sh, t_ast **ptr);
void	add_string_to_child_argv(t_av *av, char *str, int *k);
void	add_to_list_of_executables(t_shell *sh, char *cmd);
void	build_list_of_executables(t_shell *sh, char **folders);
void	check_special_keys(t_shell *sh);
void	clean_up(t_shell *sh);
void	cleanup_av_buffers(t_av *av);
void	clear_input_buffers(t_shell *sh);
void	close_quotes(t_shell *sh);
void	cmd_title(void);
void	col_if_flag_print_newline(int *f);
void	col_print_loop(int cw, int nc, int count, t_exec **a);
void	destroy_char_array(char **array);
void	destroy_list_of_executables(t_shell *sh);
void	display_shell_prompt(t_shell *sh);
void	end_of_input(t_shell *sh);
void	fatal_error(t_shell *sh);
void	fatal_error_message(t_shell *sh, char *msg);
void	free_ast(t_ast *ast);
void	free_trees(t_ast **ast);
void	group_fix_pipes(t_process **group, int i);
void	group_fix_redirect(t_process **group, int i);
void	group_fork_exec(t_process **group, int i);
void	group_process_destroy(t_process **group);
void	header_42(void);
void	header_sh(void);
void	help_list(void);
void	help_selection(char *cmd);
void	history_append_to_file(t_shell *sh);
void	increase_buffer(t_shell *sh);
void	init_input_buffer(t_shell *sh);
void	init_parse_lexer(t_ast **lex, t_ast **node, char **word, char **term);
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
void	print_ast(t_ast *node);
void	print_error_ast(void);
void	print_error_lexer(void);
void	print_trees(t_ast **ast);
void	process_redirects(t_process **group, int i);
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
void	insert_character_1(t_shell *sh, char *s, char c);
void	tab_print_columns_1(t_shell *sh, t_exec	**matches, int i);
int		key_tab_function_1(t_shell *sh, int f);
void	key_tab_function_2(t_shell *sh, char *str);
int		key_tab_function_3(t_shell *sh, char *str);

#endif
