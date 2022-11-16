/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:35:53 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/16 15:40:05 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "../ft_printf/includes/ft_printf.h"

typedef struct s_node
{
	void			*content;
	char			type;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_shell
{
	char			*cmd;
	t_node			*head;
	t_node			*tail;
	t_node			**tab_infile;
	t_node			**tab_outfile;
	int				quote;
	int				dquote;
	int				nbr_pipe;
	int				nbr_infile;
	int				nbr_outfile;
	int				nbr_appendin;
	int				nbr_appendout;
	int				nbr_dollars;
	int				nbr_dquote;
	int				nbr_squote;
	int				mod;
	int				i;
	int				j;
	int				tab;
	char			*strp;
	char			*tmpp;
	int				pipe;
	int				error;
	char			**envp;
	char			*var_search;
	char			*value;
	int				last_pipe;
	unsigned int	list_size;
	char			**env_search;
	int				env_size;
	char			*home_path;
	char			*tmp_lnospace;
	int				infile_size;
	int				outfile_size;
	int				file_search;
	int				synt_err;
}	t_shell;

void	init_dlist_var(t_shell *minishell);

/*DEBUG*/
void	print_dlist(t_node **list, t_node ***tab_infile, t_node ***tab_outfile,
			t_shell *minishell);

/*----*PARSING*----*/
int		parsing(char **env, t_shell *minishell);
void	first_parse(t_shell *minishell, char *str);

/*PIPE*/
int		parse_pipe(t_shell *minishell, int j, int i);
int		check_quote_pipe(t_shell *minishell, char *str, int len);
char	*cmd_cpy(char *dest, char *src, int size);
void	delist(t_node **list);
void	ft_incr_var_pipe(int *j, int *i);
int		check_syntax(t_shell *minishell, char *str, int i);
void	add_last_list_pipe(char *str, int i, int j, t_shell *minishell);
char	*ft_prev_for_pipe(char *tmp, char *str, int j, int i);
void	add_last_arg(t_shell *minishell, t_node **list_cpy, int *i, int j);

/*QUOTE*/
int		check_quote(t_shell *minishell, char *str, int i, char c);
void	parse_quote(char *str, t_shell *minishell);
char	*ft_copy_string_without_quote(t_shell *minishell,
			char *str, char quote);
void	list_nospace_quote(t_shell *minishell, t_node **list, char *tmp, int j);
char	**ft_split_minishell(t_shell *minishell, char *str, char c);
int		ft_nbr_words_split_minishell(t_shell *minishell,
			char const	*str, char charset);
void	parse_space_quote(t_shell *minishell);
int		ft_split_minishell_malloc_ws(char const *str, char charset, char **tab);
char	**ft_split_minishell_get_filling(char *str,
			char **tab, t_shell *minishell);
void	parse_quote_tab(t_shell *minishell, t_node ***tab_infile,
			t_node ***tab_outfile);
void	ft_parse_quote_outab(t_shell *minishell, t_node ***tab_outfile);
void	include_parse_quote_outab(t_shell *minishell, t_node *list_cpy);
void	replace_list_quote_outab(t_node *tmp, t_node **list_cpy,
			t_shell *minishell, int i);
void	replace_list_quote_intab(t_node *tmp, t_node **list_cpy,
			t_shell *minishell, int i);
void	include_parse_quote_intab(t_shell *minishell, t_node **list_cpy, int i);

/*REDIRECTIONS*/
int		parse_redirections(t_shell *minishell);
int		search_infile(t_shell *minishell, char *str, t_node **tab_infile,
			t_node **list);
int		search_heredoc(t_shell *minishell, char *str, t_node **tab_infile,
			t_node **list);
int		search_outfile(t_shell *minishell, char *str, t_node **tab_outfile,
			t_node **list);
int		search_append(t_shell *minishell, char *str, t_node **tab_outfile,
			t_node **list);
void	init_var_redirection(t_shell *minishell);
int		check_quote_infile(t_shell *minishell, char *str, int len);
int		check_quote_append(t_shell *minishell, char *str, int len);
int		check_quote_heredoc(t_shell *minishell, char *str, int len);
int		check_quote_outfile(t_shell *minishell, char *str, int len);
void	add_back_file_list(t_node **tab_list, t_node *new);
int		check_syntax_infile(t_shell *minishell, char *str, int i);
int		check_syntax_outfile(t_shell *minishell, char *str, int i);
int		check_syntax_heredoc(t_shell *minishell, char *str, int i);
int		check_syntax_append(t_shell *minishell, char *str, int i);
int		check_syntax_after_append(t_shell *minishell, char *str, int i);
int		check_syntax_after_heredoc(t_shell *minishell, char *str, int i);
int		check_syntax_after_infile(t_shell *minishell, char *str, int i);
int		check_syntax_after_outfile(t_shell *minishell, char *str, int i);
int		new_value_mod2_and3(t_shell *minishell, char *str, int i);
int		new_value5(t_shell *minishell, char *str, int i);
int		new_value4(t_shell *minishell, char *str);
int		if_only_space(char *str);
void	unstack_list(t_shell *minishell, t_node **list);
void	search_outfile_malloc(t_shell *minishell,
			char *str, char **tmp, char **cpy);
void	search_return_exit(t_shell *minishell,
			char *cpy, char **tmp);
int		tab_null_parse_quote(t_shell *minishell,
			t_node **list_cpy, char **tab);
void	return_malloc_change_var(t_shell *minishell,
			char *tmp, char *cpy);

/*DOLLARS*/
void	parse_dollars(t_shell *minishell);
int		dollars_specific(t_shell *minishell);
int		check_quote_dollars(char *str);
int		check_and_print_var_parsing(t_shell *minishell, char *str);
void	print_var_parsing(t_shell *minishell);
int		var_exists_parsing(t_shell *minishell);
int		check_var_parsing(char *str, char *var_name);
char	*dollars_mod(char *str, int i, t_shell *minishell, t_node **list);
void	change_var_to_value(char *str, int i,
			t_shell *minishell, t_node **list);
char	*replace_quote_dollars(t_shell *minishell, char *tmp, int j);
void	include_dollar_list(t_shell *minishell, t_node **list, char *tmp);
void	find_position_of_dollars(char *position, int i, int *size);
void	replace_value_and_after(t_shell *minishell, int *j, char **tmp);
void	check_dquote_dollars(char *str, int *dquote, int i, int *quote);
int		check_quote_in_quote_dollars(char *str);
void	write_newvalue(t_shell *minishell, char *str, int mod, int i);
char	*mini_getenv_parsing(char *envp[], int env_size, char *var_name,
			t_shell *minishell);
char	*check_and_return_var_parsing(char *home_path, char **envp,
			char *var, int i);
int		check_dollars_mod(char *str);
int		check_dollar_export(char *str, int i);
int		check_heredoc_dollar_mod(char *str, int i);
int		check_heredoc_dollar_mod_1(char *str, int i);
int		check_heredoc_dollar_mod_2_3(char *str, int i);
void	change_value_mod2_and_3(char *str, int i,
			t_shell *minishell, t_node **list);
int		interpret_dollars(char *str, int i,
			t_shell *minishell, t_node **list);
void	change_value_mod1(char *str, int i,
			t_shell *minishell, t_node **list);
int		check_quote_mod(char *str, int i);
int		check_dquote_mod(char *str, int i);
void	value_quote_mod_1(t_shell *minishell, char *str, int i);

/*MINISHELL*/
void	init_variable(t_shell *minishell, int envp_size, char **env);
void	parse_quote(char *str, t_shell *minishell);
char	*ft_copy_string_without_quote(t_shell *minishell,
			char *str, char quote);
void	parse_space(t_shell *minishell);
void	list_nospace(t_shell *minishell, t_node **list, char *tmp, int j);
void	list_no_space_else(t_shell *minishell, t_node *list_cpy,
			t_node *tmp_list, t_node *new_node);
void	last_verif(t_node *tmp, t_node *list_cpy, t_shell *minishell, int j);
void	copy_value_parsing(t_shell *minishell, int j, int i, char *var);
int		check_and_print_var_parsing(t_shell *minishell, char *str);
int		main_loop_search_outfile(t_shell *s, char *str, int i);
int		main_loop_search_infile(char *str, int i, int file);
int		dl_fl_search_infile(char *str, int i);
int		main_loop_search_heredoc(char *str, int i, int file);
int		dl_fl_search_heredoc(char *str, int i);
int		main_loop_search_append(char *str, int i, int file);
int		dl_fl_search_append(char *str, int i);
int		sorting_loop(t_shell *minishell, char *str, t_node **list_cpy, int j);

/*LIST*/
t_shell	*set_dlist(t_shell *minishell, int size, char **env);
void	ft_free_list(t_shell *minishell);
int		test_free(void *tmp);

int		tokenizers_arg(t_shell *minishell);

/*ERROR*/
void	exit_error(t_shell *minishell);
void	exit_perror(t_shell *minishell, char *error);
void	exit_strerror(t_shell *minishell, char *error);
int		free_exit(t_shell *minishell);

void	free_all(t_shell *minishell);
void	count_ope(t_shell *minishell);
void	nbr_ope(t_shell *minishell, char *str, int *i);

void	free_all(t_shell *minishell);
t_node	*ft_dlstnew(void *content);
int		ft_dlstadd_back(t_shell **alst, t_node *new);
int		ft_dlstadd_front(t_shell **alst, t_node *new);
t_node	*ft_dlstlast(t_shell *alst);
void	free_all_exit(t_shell *minishell);
void	free_tab_parse_exit(t_shell *minishell);
void	free_outab_exit(t_shell *minishell);
int		test_free_exit(void *tmp);
#endif
