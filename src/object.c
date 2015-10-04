/* object.c - implementation for type Object
 *
 * See object.h for details.
 */

#include <SDL2/SDL.h>
#include "object.h"
#include "texture.h"

/* Create a new Object, with a spritesheet already created */
Object * New_Object(
	Spritesheet *spritesheet,
	int x,
	int y,
	int w,
	int h,
	bool collision,
	int default_sprite) {
	Object *ret = malloc(sizeof(Object));
	if (!ret) {
		fprintf(stderr, "Error creating object\n");
		return NULL;
	}

	/* Assign the passed values */
	ret->spritesheet = spritesheet;
	ret->dstrect.x = x;
	ret->dstrect.y = y;
	ret->dstrect.w = w;
	ret->dstrect.h = h;
	ret->sprite_index = default_sprite;

	/* Create the animations for the object */
	/* Make the animations list */
	ret->animations = malloc(spritesheet->animation_count * sizeof(SDL_Rect *));
	for (int i = 0; i < spritesheet->animation_count; i++) {
		/* Make the list of sprites in the animation */
		ret->animations[i] = malloc(spritesheet->frames_in_animation[i] * sizeof(SDL_Rect));
		for (int k = 0; k < spritesheet->frames_in_animation[i]; k++) {
			ret->animations[i][k].x = ret->dstrect.w * k;
			ret->animations[i][k].y = ret->dstrect.h * i;
			ret->animations[i][k].w = ret->dstrect.w;
			ret->animations[i][k].h = ret->dstrect.h;
		}
	}

	return ret;
}

/* Set the animation for an object */
void Object_SetAnimation(Object *o, int animation) {
	o->animation = animation;
}

/* Change the object's sprite to the following sprite in the animation */
void Object_NextSprite(Object *o) {
	o->sprite_index++;
	if (o->sprite_index >= o->spritesheet->frames_in_animation[o->animation]) {
		o->sprite_index = 0;
	}
}

/* Render an object */
void Object_Render(Object *object, SDL_Renderer *renderer) {
	SDL_Rect srcrect = object->animations[object->animation][object->sprite_index];
	SDL_RenderCopy(
		renderer,
		object->spritesheet->texture->texture,
		&srcrect,
		&object->dstrect
	);
}

/* Destroy an object and all of it's sub parts */
void Destroy_Object(Object *o) {
	for (int i = 0; i < o->spritesheet->animation_count; i++) {
		free(o->animations[i]);
	}
	free(o->animations);

	Destroy_Spritesheet(o->spritesheet);
	free(o);
	o = NULL;
}
