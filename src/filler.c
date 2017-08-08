#include "my_filler.h"
#include "libft/libft.h"

// void	read_elem(t_fill *fill, char *str, int y)
// {
// 	int i;
// 	int x;
//
// 	i = -1;
// 	x = -1;
// 	while (str[++i])
// 	{
// 		fill->elem[++fill->count].x = ++x;
// 		fill->elem[++fill->count].y = y;
// 		fill->elem[++fill->count].val = str[i];
// 	}
// }
//
// void	read_map(t_fill *fill, char *str, int y)
// {
// 	int		i;
// 	int		x;
//
// 	x = -1;
// 	i = -1;
// 	while (str[++i])
// 	{
// 		fill->map[++fill->count].x = ++x;
// 		fill->map[++fill->count].y = y;
// 		fill->map[++fill->count].val = str[i];
// 	}
// }
//
// void	read_fill(t_fill *fill)
// {
// 	char *str;
// 	int count;
// 	int y_m;
// 	int y_e;
//   char **tmp;
// //  int a;
//
// 	y_m = -1;
// 	y_e = -1;
// 	count = -1;
//   while (42)
// 	{
//     get_next_line(STDIN, &str);
//     printf("str = %s\n", str);
//     ++count;
// 		if (count == 0)
// 			fill->my_symb = str[0];
// 		else if (count == 1)
// 		{
//       		tmp = ft_strsplit(str, ' ');
// 			fill->m_h = ft_atoi(tmp[0]);
// 			fill->m_w = ft_atoi(tmp[1]);
// 			fill->map = (t_map *)malloc(sizeof(t_map) * (fill->m_h * fill->m_w));
// 			fill->count = -1;
// 		 	a = -1;
// 			while (tmp[++a] != NULL)
// 		   		free(tmp[a]);
// 		 	free(tmp);
// 		}
// 		else if (fill->m_h >= (count - 2))
// 			read_map(fill, str, ++y_m);
// 		else if (count == (fill->m_h + 3))
// 		{
//       		tmp = ft_strsplit(str, ' ');
// 			fill->e_h = ft_atoi(tmp[0]);
// 			fill->e_w = ft_atoi(tmp[0]);
// 			fill->elem = (t_elem *)malloc(sizeof(t_elem) * (fill->e_h * fill->e_w));
// 			fill->count = -1;
//      a = -1;
//      while (tmp[++a] != NULL)
//        free(tmp[a]);
//      free(tmp);
//     }
// 		else
// 			read_elem(fill, str, ++y_e);
// 	  free(str);
//   }
// }

int		main()
{
	t_fill *fill;

	fill = (t_fill *)malloc(sizeof(t_fill));
	read_all(fill);
	return (0);
}
