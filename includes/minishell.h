/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:47:06 by ekuchel           #+#    #+#             */
/*   Updated: 2023/10/05 10:15:22 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <fcntl.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define MAX_COMMAND_LENGTH 1024

typedef struct s_main
{
	char	*cmd;
	char	*options;
	char	**args;
	int		fd[2];
	pid_t	pid;
}			t_main;

typedef struct s_env
{
	char	**env_var;
	int		status;
}			t_env;

typedef struct s_data
{
	int	x;
	int	y;
}			t_data;

//Built-ins
int		cd_func_helper(t_main *ptr, char *home);
int		cd_func(t_env *env, t_main ptr);
int		echo_func_helper(t_main *ptr, int *new_line);
int		echo_func(t_main ptr);
int		env_func(t_env *env);
int		exit_func(t_env *env, t_main ptr);
int		export_func(t_env *env, t_main ptr);
int		pwd_func(t_env *env);
int		unset_func(t_env *env, t_main ptr);

//Execution
int		ft_execute(t_main *cmd_tab, t_env *env);
int		ft_check4builtin(t_main cmd_tab, t_env *env);
int		ft_exe_cmd(t_main cmd_tab, t_env *env);
int		ft_exe_path(char *path, t_env *env, t_main cmd_tab);
int		ft_wait4child(t_main *cmd_tab, t_env *env);
int		ft_binary_path(t_main cmdtb, char *expath, char **path,
			t_env *env);
int		ft_check4permision(struct stat file);
size_t	str_len2char(const char *str, char c);
size_t	ft_2darray_size(char **db_array);
char	*ft_find_env_val(char *var, char **env);
char	**ft_cmd2arglist(t_main cmd_tab, t_env *env);
char	*ft_check4script(char *cmd, t_env *env);
void	ft_pipecmds(t_main *cmd_tab, t_env *env);
void	ft_close_fd(t_main *cmd_tab, int index);
void	ft_close_fds_main(t_main *cmd_tab);
void	ft_fork_this(t_main *cmd_tab, t_env *env, int index);
void	ft_redir_stdout(t_main *cmd_tab, int i, size_t size);
void	ft_redir_stdin(t_main *cmd_tab, int i, size_t size);
void	ft_redir_heredoc(t_main *cmd, int i, int cmd_idx, size_t size);
void	ft_rearrange(char **strarray, int size, int freed_idx);
void	ft_check4redirections(t_main *cmd_tab, int cmd_tab_idx);
void	ft_check4tmp(t_main *cmd_tab);
void	ft_str2lowercase(char *str);

//Parsing
t_main	*comm_tbl(char **input);
void	get_comm(char *str, t_main *ptr);
void	update_comm(char *str, t_main *ptr, int i);
void	get_flag(char *str, t_main *ptr, int i, int *j);
int		quoted_arg(t_main *ptr, char *str, int i, int *k);
char	**is_valid_input(char **inp);
void	ignore_pipe(char **inp);
char	**add_pipe(char **inp);
int		num_of_args(char *str, int i);
void	add_args(t_main *command, int *k, char *arg);
void	quote_checker(char **inp, int i, char *quote);
void	trimmer(char **inp, char *quote, char	**res);
int		trim_char(char c);
int		is_a_quote(char c);
int		is_quote_closed(char *str, int n);
void	inp_trim(char **inp);
void	vars_to_inp(t_env *env, char **inp, char **res, t_data *data);
void	parsing_vars(t_env *env, char **inp, char **res);
void	parse_vars(t_env *env, char **inp);
t_main	*parse(t_env *env, char **inp);

//Utils
void	clear_env(t_env *env);
void	clear_arr(char **arr);
void	quit_func(t_env *env, char *msg, int fail);
void	cp_env_var(t_env *env, char **env_var);
char	*get_env_var(t_env *env, char *name);
void	add_env_var(t_env *env, char *name, char *val);
void	rem_env_var(t_env *env, char *name);
int		is_alpha(int c);
int		word_count(char *str, char c);
int		is_digit(int c);
int		is_num(char *str);
void	print_arr(char **arr);
void	putchar_fd(char c, int fd);
void	putstr_fd(char *s, int fd);
size_t	str_len(char *str);
int		str_ncmp(char *str1, char *str2, size_t n);
char	*str_dup(char *str);
int		str_chrn(char *str, int c);
char	*sub_str(char *str, unsigned int start, size_t len);
void	putendl_fd(char *s, int fd);
int		ft_tolower(int c);

//Libft

int		ft_atoi(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
int		valid_char(int c);

//Signals
void	sigint_handler(int signal);
void	sigquit_handler(int signal);
void	signal_func(void);
void	signal_handler(void);

#endif
