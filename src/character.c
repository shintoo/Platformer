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
