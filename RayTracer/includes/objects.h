//
// Created by atory on 19.01.2022.
//

#ifndef OBJECTS_H
#define OBJECTS_H

#include "tuple.h"

typedef struct s_object_base_interface	t_object;
typedef	void (*t_print_func)(void *);
typedef t_pair (*t_intersection_func)(void *, void *);
typedef t_vector (*t_normal_func)(void * , void *);

struct	s_object_base_interface
{
	int					ident;
	t_point				center;
	t_color				color;
	double 				reflective;
	double 				specular;

	t_print_func 		print_func;
	t_intersection_func	intersection_func;
	t_normal_func 		normal_func;

	t_object 			*next;
};

enum e_identifiers
{
	A = 1,
	C,
	L,
	sp,
	pl,
	cy,
};

typedef struct s_ambient	t_ambient;
typedef struct s_light		t_light;
typedef struct s_camera		t_camera;

typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;

/*
 * Ambient lightning:	A 0.2 255,255,255
 * identifier: A
 ∗ ratio in range [0.0,1.0]
 ∗ R,G,B colors in range [0-255]
 */
struct	s_ambient
{
	int		ident;
	double	ratio;
	t_color	color;
};

/*
 *  CAMERA:			C -50.0,0,20 0,0,1 70
 *  OBJECT BASE :	identifier && view point
 *  orientation vector
 *  FOV : view in degrees in range [0,180]
 */
struct	s_camera
{
	int			ident;
	t_point		center;
	t_vector	orientation;
	double		view_degree;
};

/*
 *  Light:			L -40.0,50.0,0.0 0.6 10,0,255
 *  OBJECT BASE :	identifier && view point
 *  brightness ratio in range [0.0,1.0]
 *  R,G,B colors in range [0-255]
 */
struct	s_light
{
	int			ident;
	t_point		center;
	t_color		color;
	double		bright;

	t_light 	*next;
};

/*
 *  Sphere:			sp 0.0,0.0,20.6 12.6 10,0,255
 *  OBJECT BASE :	identifier && view point
 *  the sphere diameter
 *  R,G,B colors in range [0-255]
 */
struct s_sphere
{
	t_object	object;
	double		diameter;
};

/*
 *  Plane:			pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
 *  OBJECT BASE :	identifier && view point
 *  normalized orientation vector
 *  R,G,B colors in range [0-255]
 */
struct	s_plane
{
	t_object	object;
	t_vector	orientation;
};

/*
 *  Cylinder:		cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
 *  OBJECT BASE :	identifier && view point
 *  normalized orientation vector
 *  diameter
 *  height
 *  R,G,B colors in range [0,255]
 */
struct	s_cylinder
{
	t_object	object;
	t_vector	orientation;
	double		diameter;
	double		height;
};

void		print_object(t_object*	this);

void		print_object_default(void * this_ptr);
void		print_sphere(void * this_ptr);
void		print_plane(void * this_ptr);
void		print_cylinder(void * this_ptr);
void		print_camera(void * this_ptr);

t_vector	normal_at(t_object* this, t_point *point);
t_vector	normal_at_sphere(t_sphere *sphere, const t_point *point);

t_pair		intersect(t_object*	this, void *ray);
t_pair		intersect_sp(void *this, void *ray);

#endif
