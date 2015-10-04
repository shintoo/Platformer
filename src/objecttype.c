/* objecttype.c - implementation for type ObjectType
 *
 * See objecttype.h for details.
 */

#include <SDL2/SDL.h>
#include "objecttype.h"
#include "texture.h"

/* Create a new Object, with a spritesheet already created */
ObjectType * New_ObjectType(
	Spritesheet *spritesheet,
	bool collision,
	int w,
	int h) {

	ObjectType *ret = malloc(sizeof(ObjectType));
	if (!ret) {
		fprintf(stderr, "Error creating object\n");
		return NULL;
	}

	/* Assign the passed values */
	ret->spritesheet = spritesheet;

	/* Create the animations for the object */
	/* Make the animations list */
	ret->animations = malloc(spritesheet->animation_count * sizeof(SDL_Rect *));
	for (int i = 0; i < spritesheet->animation_count; i++) {
		/* Make the list of sprites in the animation */
		ret->animations[i] = malloc(spritesheet->frames_in_animation[i] * sizeof(SDL_Rect));
		for (int k = 0; k < spritesheet->frames_in_animation[i]; k++) {
			ret->animations[i][k].x = w * k;
			ret->animations[i][k].y = h * i;
			ret->animations[i][k].w = w;
			ret->animations[i][k].h = h;
		}
	}

	ret->instance_count = 0;
	ret->instances_size = 2;
	ret->instances = malloc(sizeof(Object) * 2);
	return ret;
}

/* Create a new object of an ObjectType ot */
void ObjectType_AddObject(ObjectType *ot, int x, int y, int default_animation, int default_sprite) {
	/* Make sure ot->instances is large enough to have another object */
	if (ot->instance_count >= ot->instances_size - 1) {
		/* Double the size of ot->instances */
		ot->instances = realloc(ot->instances, ot->instances_size * 2);
		ot->instances_size *= 2;
	}
	/* Copy the passed initial position */
	ot->instances[ot->instance_count].dstrect.x = x;
	ot->instances[ot->instance_count].dstrect.y = y;

	/* Copy the passed initial animation and initial sprite */
	ot->instances[ot->instance_count].animation = default_animation;
	ot->instances[ot->instance_count].sprite_index = default_sprite;
}

/* Set the animation for an object */
void ObjectType_SetObjectAnimation(ObjectType *ot, int instance_index, int animation) {
	ot->instances[instance_index].animation = animation;
}

/* Change the object's sprite to the following sprite in the animation */
void ObjectType_ObjectNextSprite(ObjectType *o, int instance_index) {
	/* Increment the instance's sprite index */
	o->instances[instance_index].sprite_index++;

	/* If the sprite index of the instance is greater than the instance's current animation's size, restart the animation */
	if (o->instances[instance_index].sprite_index > o->spritesheet->frames_in_animation[o->instances[instance_index].animation]) {
		o->instances[instance_index].sprite_index = 0;
	}
}

/* Render an instance of ObjectType */
void ObjectType_RenderObject(ObjectType *ot, SDL_Renderer *renderer, int instance_index) {
	SDL_RenderCopy(
		renderer,
		ot->spritesheet->texture->texture,
		&ot->animations[ot->instances[instance_index].animation][ot->instances[instance_index].sprite_index],
		&ot->instances[instance_index].dstrect
	);
}

/* Destroy an ObjectType and all of its sub parts */
void Destroy_ObjectType(ObjectType *ot) {
	for (int i = 0; i < ot->spritesheet->animation_count; i++) {
		free(ot->animations[i]);
	}
	free(ot->animations);

	free(ot->instances);

	Destroy_Spritesheet(ot->spritesheet);
	free(ot);
	ot = NULL;
}
