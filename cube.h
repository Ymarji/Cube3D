/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 11:20:18 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/10 12:01:17 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include "./gnl/get_next_line.h"
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# define UP_KEY 126
# define DOWN_KEY 125
# define RIGHT_KEY 124
# define LEFT_KEY 123
# define W_KEY 13
# define S_KEY 1
# define D_KEY 2
# define A_KEY 0
# define WALL 0
# define N 1
# define S 2
# define E 3
# define W 4
# define SP 5
# define NO_ARG 0
# define NOT_ARG -2
# define EXT_ERR 1
# define MAP_ERR 2
# define KEY_ERR -1
# define NUM_ARG 3
# define FILE_ERR 4
# define RES_ERR 5
# define COLOR_ERR 6

typedef struct	s_data
{
	int		*buff;
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img;
	int		*addr;
	int		bpp;
	int		l_len;
	int		endian;

}				t_data;

typedef struct	s_player
{
	double	x_player;
	double	y_player;
	double	radius;
	double	turn_d;
	double	walk_d;
	double	ri_le;
	double	ro_angle;
	double	move_s;
	double	ro_speed;
}				t_player;

typedef struct	s_ray
{
	int		*distw;
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	double	xhit_h;
	double	yhit_h;
	double	xhit_v;
	double	yhit_v;
	double	distence;
	int		washitvertical;
	double	xwallhit;
	double	ywallhit;
	double	rayangel;
	int		facingdown;
	int		facingup;
	int		facingright;
	int		facingleft;
	int		scolor;
}				t_ray;

typedef struct	s_txt
{
	int		*addr;
	int		bpp;
	int		l_len;
	int		endian;
	void	*img;
	int		width;
	int		hight;
}				t_txt;

typedef struct	s_cord
{
	double	x;
	double	y;
}				t_cord;

typedef struct	s_sprite
{
	t_cord	pos;
	double	dist;
	double	angl;
	int		visible;
}				t_sprite;

typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
}				t_color;

typedef struct	s_file
{
	int		widht;
	int		hight;
	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;
	char	*s_text;
	char	*index;
	int		colorf;
	int		colorc;
	int		maplinemax;
	int		maprow;
	char	*map;
	char	**tab;
	int		playerfound;
	int		args;
}				t_file;

typedef struct	s_image
{
	unsigned char	bitmap_type[2];
	int				file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset_bits;
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}				t_image;

typedef struct	s_cube
{
	int			cube_d;
	int			handle;
	int			ident;
	int			s_num;
	double		dto_pl;
	int			end;
	int			s_hight;
	double		fov;
	t_sprite	*sprite;
	t_data		data;
	t_txt		*txt;
	t_player	ply;
	t_ray		ray;
	t_file		file;
}				t_cube;
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			table_free(char **tab);
void			sprite(t_cube *cube);
int				wall_check(t_cube *cube, double newx, double newy);
void			textselect(t_cube *cube);
void			ray_facing(t_cube *cube, double ray);
void			check_vethit(t_cube *cube, int *verhit);
void			verticalcast(t_cube *cube, int *verhit);
void			check_horhit(t_cube *cube, int *horhit);
void			horizentalcast(t_cube *cube, int *horhit);
void			disttowall(t_cube *cube, double hordistence,
				double verdistence);
void			calculdistancetowall(t_cube *cube, int horhit, int verhit);
void			draw_s(t_cube *cube, int x, int s_x, int sp);
void			colorfc(t_cube *cube, double wallhight, int i);
void			player_updat(t_cube *cube);
void			draw_t(t_cube *cube, int hight, int x);
void			drawline(t_cube *cube, int x0, int y0, int x1, int y1);
int				key_press(int key, t_cube *cube);
int				key_release(int key, t_cube *cube);
void			draw(t_cube *cube);
void			raycast(t_cube *cube, double rayangel);
int				its_a_wall(t_cube *cube, int x, int y);
int				update(t_cube *cube);
void			my_mlx_pixel_put(t_cube *cube, int x, int y, int color);
void			bhm_line(t_cube *cube, int x1, int y1, int x0, int y2, int c);
void			renderprojectedwalls(t_cube *cube, int i);
void			colorfloornadceel(t_cube *cube);
double			dist2point(double x1, double y1, double x2, double y2);
void			calcul_x_y_pix_in_textu(t_cube *cube, int *xtext, int side);
void			loadtexttopimage(t_cube *cube, char *filename,
				void	**img, int **addr);
double			normalizeangle(double angle);
void			castingrays(t_cube *cube);
void			numofsprite(t_cube *cube);
void			get_sprite_angel(t_cube *cube);
void			sortsprtis(t_cube *cube);
void			findingsprite(t_cube *cube);
double			sprite_pos_in_screan(t_cube *cube, int i,
				double angle, int hight);
void			drowsprite(t_cube *cube);
void			map_extract(t_cube *cube, char *line, int fd);
void			read_file(t_cube *cube, char *file);
void			data_collector(t_cube *cube, char *line);
void			get_res(t_cube *cube, char *line);
void			textident(t_cube *cube);
void			err_(int err, char *ident);
void			err_print(int err, char *ident);
void			err_handler(int ac, char **av, t_cube *cube);
int				c_split(char const *str, char c);
char			*ft_hex(unsigned int nbr, char c);
char			*ft_revers(char *hexa);
int				count_nbr(unsigned long nbr);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strstr(const char *haystack, const char *needle);
int				countrow(char **tab);
void			spritevisible(t_cube *cube, int x, int y);
void			image_create(t_cube *cube);
void			image_put(t_cube *cube, t_image *image, int file);
void			fill_data(t_image *image, t_cube *cube);
void			disttowall(t_cube *cube, double hordistence,
				double verdistence);
void			textureload(t_cube *cube);
void			playerfacing(t_cube *cube);
void			findplayer(t_cube *cube);
int				mapsearsh(char *line);
char			*complet_line(t_cube *cube, char *line);
int				maplignemax(int fd);
void			maperr(t_cube *cube);
void			mapoutlign(t_cube *cube, char **tab);
char			*ft_strtrim(char const *s1, char const *set);
int				check(char c, char *set);
int				vrf_arg_dg(char *tab, char *set);
void			check_col(char **tab);
int				ft_isdigit(int c);
void			free_thing(t_cube *cube);
int				ft_close_win(t_cube *cube);
int				calc_ocur(char *str, char c);
void			init_file(t_cube *cube);
#endif
