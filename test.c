//
// Created by Oleksandr MYKOLAICHUK on 7/2/18.
//
#include <stdlib.h>
#include "get_next_line/get_next_line.h"
#include "ft_printf/includes/ft_printf.h"
#include "hashtable/hashtable.h"
#include "test.h"

int move_idx;
t_hashtable *line_rooms;
t_ant *cur_rooms;

static void	test_link_rooms(int ant, char *room)
{
	if (ant >= g_farm.ant_count || ant < 0)
		exit_error(ft_sformat("invalid ant (line: %d, ant: %d)", line_idx, ant + 1));

	room = ft_strtrim(room);
	t_room *room1 = cur_rooms[ant].room;
	t_room *room2 = ht_get(g_rooms, room);

	if (cur_rooms[ant].handled)
		exit_error(ft_sformat("duplication of ant (line: %d, ant: %d)", line_idx, ant + 1));
	if (!room2)
		exit_error(ft_sformat("destination room of the move not found (line: %d, move: %d)", line_idx, move_idx));
	if (room2 != g_farm.end && !ht_add(line_rooms, room2->name, room2))
		exit_error(ft_sformat("multiple ants in same room (line: %d, room: %s)", line_idx, room2->name));

	t_list *links = room1->links;

	while (links)
	{
		t_link *l = links->value;

		if (l->next_room == room2)
		{
			++move_idx;
			cur_rooms[ant].room = room2;
			cur_rooms[ant].handled = true;
			return ;
		}
		links = links->next;
	}
	exit_error(ft_sformat("link not found (line: %d, move: %d)", line_idx, move_idx));
}

static bool	test_link(char **line)
{
	char *it1;
	char *it2;
	char *ant;
	char *room;

	if (!ft_strchr(*line, 'L'))
		return false;

	it1 = ft_strchr(*line, 'L') + 1;
	it2 = ft_strchr(it1, '-');
	ant = ft_strsub(it1, 0, it2 - it1);
	it1 = it2 + 1;
	it2 = ft_strchr(it1, 'L') - 1;
	if (it2 == NULL - 1)
		it2 = ft_strchr(it1, '\0');
	room = ft_strsub(it1, 0, it2 - it1);

	test_link_rooms(ft_atoi(ant) - 1, room);

	free(ant);
	free(room);
	*line = it2;

	return true;
}

static void	test_line(char *line)
{
	move_idx = 1;
	++line_idx;
	for (int i = 0; i < g_farm.ant_count; ++i)
		cur_rooms[i].handled = false;

	if (line_rooms)
		ht_destroy(line_rooms, NULL);
	line_rooms = ht_new();

	while (test_link(&line));
}

void	test(int fd)
{
	char	*line;
	int		res;

	line_rooms = NULL;
	cur_rooms = malloc(sizeof(*cur_rooms) * g_farm.ant_count);
	for (int i = 0; i < g_farm.ant_count; ++i)
		cur_rooms[i].room = g_farm.start;

	while ((res = get_next_line(fd, &line) > 0))
		test_line(line);
	for (int j = 0; j < g_farm.ant_count; ++j)
		if (cur_rooms[j].room != g_farm.end)
			exit_error(ft_sformat("ant %d didn't reach the end", j + 1));
	if (res < 0)
		exit_error("file read error");
}
