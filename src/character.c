/* character.c - Implementation for CharacterType
 *
 * See character.h for details
 */

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "character.h"
#include "object.h"

/* Create a new CharacterType */
CharacterType * New_CharacterType(ObjectType *ot, bool affected_by_gravity) {
	CharacterType *ret = malloc(sizeof(CharacterType));
	if (!ret) {
		fprintf(stderr, "Error creating CharacterType\n");
		return NULL;
	}

	/* Copy the passed values */
	ret->object_type = ot;
	ret->affected_by_gravity = affected_by_gravity;

	/* There's not much to do here, most of everything is in the ObjectType */
	return ret;
}

/* Destroy a CharacterType and each instance */
void Destroy_CharacterType(CharacterType *ct) {
	/* The only dynamically allocated aspect of CharacterType is the list of traits */
	for (int i = 0; i < ct->object_type->instance_count; i++) {
		free(ct->character_traits);
	}
	/* This will take care of everything else */
	Destroy_ObjectType(ct->object_type);

	ct = NULL;
}

/* temporary */
void CharacterType_MoveCharacter(CharacterType *ct, int instance_index, const uint8_t *KeyboardState) {
	CharacterTraits *ch = &ct->character_traits[instance_index];
	if (KeyboardState[SDL_SCANCODE_W]) {
		ch->velocity.y -= 5;
	}
	if (KeyboardState[SDL_SCANCODE_S]) {
		ch->velocity.y += 5;
	}
	if (KeyboardState[SDL_SCANCODE_A]) {
		ch->velocity.x -= 5;
	}
	if (KeyboardState[SDL_SCANCODE_D]) {
		ch->velocity.x += 5;
	}
}

void CharacterType_UpdateCharacter(CharacterType *ct, int instance_index, int frame) {
	/* ch_object is the physical object of the character instance */
	Object *ch_object = &ct->object_type->instances[instance_index];
	/* ch_traits are the traits of the character instance */
	CharacterTraits *ch_traits = &ct->character_traits[instance_index];

	/* Cap velocities at +-5 */
	if (ch_traits->velocity.x > 5) {
		ch_traits->velocity.x = 5;
	}
	if (ch_traits->velocity.y > 5) {
		ch_traits->velocity.y = 5;
	}
	if (ch_traits->velocity.x < -5) {
		ch_traits->velocity.x = -5;
	}
	if (ch_traits->velocity.y < -5) {
		ch_traits->velocity.y = -5;
	}

	/* Update animation for direction */
	if (ch_traits->velocity.x < 0) {
		ObjectType_SetObjectAnimation(ct->object_type, instance_index, 1);
	} else if (ch_traits->velocity.x > 0) {
		ObjectType_SetObjectAnimation(ct->object_type, instance_index, 2);
	}

	if (frame % 7 == 0) {
		if (ch_traits->velocity.x != 0) {
			/* Update sprite */
			ObjectType_ObjectNextSprite(ct->object_type, instance_index);
		} else {
			ct->object_type->instances[instance_index].sprite_index = 0;
		}
	}

	/* Apply acceleration */
	ch_traits->velocity.y *= 0.9;
	ch_traits->velocity.x *= 0.9;

	/* Apply velocities to the position */
	ch_object->dstrect.x += ch_traits->velocity.x;
	ch_object->dstrect.y += ch_traits->velocity.y;

}
