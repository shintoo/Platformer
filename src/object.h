/* object.h - type definition for an object
 *
 * An object is the basic building block for anything that will be
 * part of the world. Every block, wall, character, and the player
 * all have Objects in them. However, blocks are JUST an object,
 * while something like a character CONTAINS a block.
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "texture.h"

/* The Object struct */
typedef struct {
	Texture *spritesheet; /* Each type of object has a spritesheet, all objects
	                       * of the same type have their spritesheet member set
	                       * to the same value.
	                       */

	SDL_Rect rect;        /* .x, .y: The position/location of the object;
	                       * .w, .h: The dimensions (width and height) of the
	                       * object
	                       */

	bool collision;       /* collision can either be true or false. If true,
	                       * the entire area encapsulated by the object is
	                       * impermeable. This will only be used for objects
	                       * such as level blocks, walls, etc.
	                       */

} Object;

/* Create a new object from a spritesheet with an initial location,
 * width, and height.
 */
Object * New_Object(
	Texture *spritesheet, /* A spritesheet already created. See "texture.h" */
	int x,                /* The original x-position of the object.         */
	int y,                /* The original y-location of the object.         */
	int w,                /* The width of the object.                       */
	int h                 /* The height of the object.                      */
);

/* Draw the object onto the renderer using the object's location,
 * size, and spritesheet. If sprite_index is greater than 0, this function
 * will traverse the sprite sheet and render the appropriate sprite. For
 * instance, an object with a spritesheet that has 4 sprites on it can
 * be rendered using the last sprite with a sprite_index equal to 3.
 */
void Object_Render(SDL_Renderer *renderer, Object *object, int sprite_index);


