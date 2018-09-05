/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:40:59 by omykolai          #+#    #+#             */
/*   Updated: 2018/09/05 17:48:59 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft/libft.h"
# include "hashtable/hashtable.h"

typedef struct	s_room
{
	t_list		*links;
	char		*name;
	int			x;
	int			y;
}				t_room;

typedef struct	s_link
{
	t_room		*next_room;
	t_queue		*in_paths;
	t_queue		*out_paths;
	t_queue		*finished_paths;
	bool		headed_to_start;
}				t_link;

typedef struct	s_result
{
	t_list		*paths;
	int			steps;
}				t_result;

typedef struct	s_farm
{
	int			ant_count;
	t_room		*start;
	t_room		*end;
	int			max_path_count;
	t_result	result;
}				t_farm;

t_farm			g_farm;
t_hashtable		*g_rooms;
t_hashtable		*g_positions;
int				g_links;
bool			g_error_color;

int 			line_idx;

t_queue			*read_farm(int fd);
bool			find_paths(void);
void			print_path(void);
void			test(int fd);
void			exit_error(char *message);

#endif
