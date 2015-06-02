/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 15:57:19 by rbenjami          #+#    #+#             */
/*   Updated: 2015/06/02 16:34:33 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

static void	init_light2(t_scop *scop)
{
	t_light	*light;

	light = new_light(scop->prog, "lights[2]");
	light->ambient = vector3f(0.0f, 0.0f, 0.5f);
	light->diffuse = vector3f(0.0f, 0.0f, 0.5f);
	light->specular = vector3f(0.0f, 0.0f, 0.2f);
	light->position = vector3f(7.0f, 10.0f, -7.0f);
	add_elem(&scop->light_list, light);
	light = new_light(scop->prog, "lights[3]");
	light->ambient = vector3f(0.1f, 0.5f, 0.0f);
	light->diffuse = vector3f(0.1f, 0.5f, 0.0f);
	light->specular = vector3f(0.05f, 0.2f, 0.0f);
	light->position = vector3f(-7.0f, 10.0f, 7.0f);
	add_elem(&scop->light_list, light);
}

static void	init_light(t_scop *scop)
{
	t_light	*light;

	light = new_light(scop->prog, "lights[0]");
	light->ambient = vector3f(0.3f, 0.0f, 0.0f);
	light->diffuse = vector3f(0.8f, 0.0f, 0.0f);
	light->specular = vector3f(0.4f, 0.0f, 0.0f);
	light->position = vector3f(7.0f, 10.0f, 7.0f);
	add_elem(&scop->light_list, light);
	light = new_light(scop->prog, "lights[1]");
	light->ambient = vector3f(0.5f, 0.5f, 0.0f);
	light->diffuse = vector3f(0.5f, 0.5f, 0.0f);
	light->specular = vector3f(0.2f, 0.2f, 0.0f);
	light->position = vector3f(-7.0f, 10.0f, -7.0f);
	add_elem(&scop->light_list, light);
	init_light2(scop);
}

void		init_scene(t_scop *scop, const char **argv)
{
	t_object	*cube;
	t_object	*teapot;
	VEC3		pos;

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	scop->view = new_transform();
	scop->view->pos.x = 0;
	scop->view->pos.y = -3;
	scop->view->pos.z = 8;
	scop->projection = init_perspective(to_radians(70.0f), 850.0f / 550.0f, \
		0.01f, 1000.0f);
	cube = new_object("inv_cube.obj");
	cube->transform->scale.x = 15;
	cube->transform->scale.y = 15;
	cube->transform->scale.z = 15;
	cube->transform->pos.y = 1;
	teapot = new_object(argv[1]);
	add_elem(&scop->object_list, teapot);
	add_elem(&scop->object_list, cube);
	init_light(scop);
}

void		update_scene(t_scop *scop)
{
	VEC3		*v;
	QUAT		*quat;
	t_object	*object;
	t_elem		*elem;
	int			i;

	i = 0;
	elem = scop->object_list.first;
	while (elem)
	{
		object = (t_object *)elem->data;
		if (i == 0)
		{
			v = rotate3q(new_vector3f(0, 1, 0), &object->transform->rot);
			quat = new_quaternion4vf(v, to_radians(20));
			quat = normalized4(mul4q(quat, &object->transform->rot));
			object->transform->rot = *quat;
			ft_memdel((void **)&quat);
		}
		elem = elem->next;
		i++;
	}
}