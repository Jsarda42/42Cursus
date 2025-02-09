/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliensarda <juliensarda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:35:53 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/24 13:11:16 by juliensarda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/random.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

/*			DEBUG			*/

void					debug_print_block(t_data **list);

/*          BUILTINS        */
unsigned long long int	ft_atoll(const char *str, int *overflow);
void					ft_pwd(t_data *data, t_shell *shell, char **args);
void					ft_env(t_data *data, t_shell *shell, char **args);
void					ft_export(t_data *data, t_shell *shell, char **args);
void					ft_echo(t_data *data, t_shell *shell, char **args);
void					ft_exit(t_data *data, t_shell *shell, char **args);
void					ft_cd(t_data *data, t_shell *shell, char **args);
void					ft_unset(t_data *data, t_shell *shell, char **args);
int						handle_redir_builtins(t_data *data, t_shell *shell,
							int i);
int						is_valid_identifier(const char *name);

/*          EXEC / EXEC UTILS       */
void					exec_pipe(t_shell *shell, int num_cmd);
void					manage_no_path(t_data *head, t_shell *shell, int mod);
void					last_exec(t_shell *shell, t_data *data);
void					middle_exec(t_shell *shell, t_data *data, int fd_tmp);
void					first_exec(t_shell *shell, t_data *data, char *path);
void					ft_wait(t_data *data);
int						get_tmp_file(t_data *datas);
void					manage_sig(void);
void					execve_fail(void);
int						exec(t_shell *datas);
void					heredoc(t_data *data, t_shell *shell, char *eof,
							char *file_name);
int						is_built_in(t_data *data);
void					exec_built_in(t_data *datas, t_shell *shell);
int						check_if_redir(t_data *datas);
void					exec_simple_cmd(t_data *data, t_shell *shell);
void					handle_redir(t_shell *shell, t_data *datas);
char					*get_cmd_path(t_data *data, t_shell *shell);
char					*get_path_value(t_shell *datas, char *key);
char					*get_key_value(t_env *env, char *key);
int						check_key(t_env *env, char *key);
void					ft_dup(t_data *datas);
void					handle_heredoc(t_shell *shell, t_data *data);
void					readline_loop(t_data *data, t_shell *shell, char *eof,
							int fd);
void					manager_mid(t_data *data, t_shell *shell, int fd_tmp);
void					exit_other_child(t_data *data, t_shell *shell);
void					exit_first_child(t_data *data, t_shell *shell);
void					handler_sig_cmd(int sig);
void					close_fd(t_data *data);
void					ft_recup(t_shell *shell);
void					ft_wait_hd(t_data *data);

/*			PARSING / PARSING UTILS			*/

char					*expander(char *str, t_env **env, int i, char *res);
int						parse_input(char *input, t_shell *shell);
int						create_list(char *input, t_data **datas,
							t_shell *shell);
t_data					*parse_block(char *str, t_data *datas, t_shell *shell,
							int flag);
char					**erase_split_parse_block(char **split, t_shell *shell,
							char *s, int *i);
t_data					*pre_init_block(void);
t_data					*ft_lstlast_block(t_data *lst);
int						block_add_back(t_data **alst, t_data *new);
char					*ft_recreate_input(char *str, char **tab, char *s,
							t_shell *shell);
int						init_redir_arrays(t_data *datas, char *tmp_str);
t_data					*end_init_one_block(t_data *datas, char **tab, char *s,
							t_shell *shell);
int						cut_parse_block_loop_1(char **split, int i,
							t_data *datas, t_shell *shell);
int						ccut_parse_block_loop_1(char **split, int i,
							t_data *datas, t_shell *shell);
int						cut_parse_block_loop_2(char **split, int i,
							t_data *datas, t_shell *shell);
int						ccut_parse_block_loop_2(char **split, int i,
							t_data *datas, t_shell *shell);
int						check_syntaxes(char *str);
int						count_operators(char *input);
int						cut_delete_quote_loop(char *str, int i, int *dq,
							int *sq);
int						recup_second_quote(char *str, int i, int mode);
char					*cut_delete_quote(char *str, int pos1, int pos2);
char					*delete_extra_quotes(char *str, int i, int dq, int sq);
int						count_redir_operator(char *str, int mode);
int						count_hd_operator(char *str);
int						open_files(t_data **datas);
char					*get_content_env(t_env **env, char *find);
int						valid_name(char c);
char					*reallocator(char *res, char c, int i);
char					*recup_dq_sq_expander(char *str, int i, int *sq,
							int *dq);
char					*add_space(char *input);
int						check_valid_quotes(char *str);
int						is_white_space(char c);

/*			UTILS ENV			*/
int						env_init(t_env **env, char **envp);
char					**create_char_env(t_env *env, int env_size);
void					print_env(t_env *list, t_data *data);
int						get_env_list_size(t_env *list);
char					*get_content_env(t_env **env, char *find);
void					ft_print_exp(t_env *exp, t_data *data);
char					*ft_erase(char *str, int pos, int len);

/*			UTILS	STR/TAB		*/

char					**ft_split_quotes(char *s, char c);
int						ft_strslen_tab_until(char **tab, int pos);
char					**ft_erase_in_tab(char **tab, int pos, int pos2);
int						ft_tablen(char **tab);
size_t					count_args(char **args);
void					ft_lstadd_back_env(t_env **alst, t_env *new);
t_env					*ft_lstnew_env(char *line, char *name, char *value);
char					*ft_wildcards(char *str);
int						ft_lstsize_cmd(t_data *lst);
void					init_syntax_struct(t_s *s);
void					check_sq_dq(t_s *s_s, char c);

/*			ERRORS			*/
void					ft_errors_parsing(int err, char *msg, t_shell *shell,
							char *supp);
void					ft_errors_exec(int err, char *msg, char *supp,
							int err_status);

/*			FREE			*/

void					ft_clear_datas(t_data **datas);
void					ft_free_env_list(t_env **env);
void					free_child(t_data *data, t_shell *shell,
							int exit_status);
void					free_hd_file(t_data **data, int mode);
void					freetab(char **tab);
extern int				g_return_satus;

#endif
