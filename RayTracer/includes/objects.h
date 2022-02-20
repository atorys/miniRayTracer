//
// Created by atory on 19.01.2022.
//

#ifndef OBJECTS_H
#define OBJECTS_H

#include "tuple.h"

typedef struct s_object_base_interface	t_object;

typedef t_pair (*t_intersection_func)(void *, void *);
typedef t_vector (*t_normal_func)(void * , void *);

struct	s_object_base_interface
{
	int					ident;
	t_point				center;
	t_color				color;
	double 				reflective;
	double 				specular;

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
	double	ratio; // не используется
	t_color	color; // не используется
	t_color effective_color; // color * ratio
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
	t_color		color; // не используется
	double		bright;// не используется
	t_color		effective_color; // color * brightness

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
	double 		squared_radius;
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
	double 		squared_radius;
};

/*
 * NORMAL.C
 */
t_vector	normal_at(t_object* this, void *computations);
t_vector	normal_at_sphere(void *this, void *computations);
t_vector	normal_at_plane(void *this, void *computations);
t_vector	normal_at_cylinder(void *this, void *computations);

/*
 * INTERSECTIONS.C
 */
t_pair		intersect(t_object*	this, void *ray);
t_pair		intersect_sp(void *this, void *ray);
t_pair		intersect_pl(void *this, void *ray);
t_pair		intersect_cy(void *this, void *ray);


#endif
