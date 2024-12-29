#include <stdio.h>

#include "analyse.h"
#include "constants.h"
#include "maths.h"
#include "memory.h"
#include "types.h"
#include "./roles/roles.h"


extern const Role roles[ROLE_COUNT];

static inline void padLeft(const u8 byte) {
	if (byte < 10) {
		printf(" ");
	}
	printf("%d", byte);
}

void printPlayer(const Context *ctx, const unsigned long attributeBase) {
	u8 idString[4];
	readFromMemory(ctx->fd, attributeBase + OFFSET_ID, 4, idString);
	const unsigned long id = hexBytesToInt(idString, 4);
	u8 ability[4];
	readFromMemory(ctx->fd, attributeBase + OFFSET_ABILITY, 3, ability);
	u8 personality[8];
	readFromMemory(ctx->fd, attributeBase + OFFSET_PERSONALITY, 8, personality);
	u8 attributes[56];
	readFromMemory(ctx->fd, attributeBase + OFFSET_ATTRIBUTES, 54, attributes);

	const bool canDevelopQuickly =
		attributes[48] < 70 &&
		personality[PERSONALITY_AMBITION] > 10 &&
		personality[PERSONALITY_PROFESSIONALISM] > 10 &&
		attributes[51] > 50;
	const bool isHotProspect = 0; // TODO: depends on age
	char *fastLearnerString = canDevelopQuickly ? "Fast learner  " : "";
	char *hotProspectString = isHotProspect ? "Hot prospect  " : "";

	printf("\n\n\n\n\n\n\n\n");

	printf(".------------------------------------------.------------------------------------------.\n");
	printf("| %ld (GK, DL/R, ST)          %s%s\n", id, fastLearnerString, hotProspectString);
	printf("| Ability: %d/%d\n", ability[ABILITY_CA], ability[ABILITY_PA]);
	printf(".------------------------------------------.------------------------------------------.\n");

	printf("| Adaptability:  ");
	padLeft(personality[PERSONALITY_ADAPTABILITY]);
	printf("  Professionalism:  ");
	padLeft(personality[PERSONALITY_PROFESSIONALISM]);
	printf("  | Consistency:    ");
	padLeft(attributes[44]);
	printf("  In4jury proneness:  ");
	padLeft(attributes[48]);
	printf("\n| Ambition:      ");
	padLeft(personality[PERSONALITY_AMBITION]);
	printf("  Sportsmanship:    ");
	padLeft(personality[PERSONALITY_SPORTSMANSHIP]);
	printf("  | Determination:  ");
	padLeft(attributes[51]);
	printf("  Versatility:       ");
	padLeft(attributes[49]);
	printf("\n| Loyalty:       ");
	padLeft(personality[PERSONALITY_LOYALTY]);
	printf("  Temperament:      ");
	padLeft(personality[PERSONALITY_TEMPERAMENT]);
	printf("  | Dirtiness:      ");
	padLeft(attributes[41]);
	printf("\n| Pressure:      ");
	padLeft(personality[PERSONALITY_PRESSURE]);
	printf("  Controversy:      ");
	padLeft(personality[PERSONALITY_CONTROVERSY]);
	printf("  | Imp. Matches:   ");
	padLeft(attributes[47]);

	printf("\n");
	printf(".------------------------------------------.------------------------------------------.\n");
	// Age

	u8 positions[15];
	readFromMemory(ctx->fd, attributeBase + OFFSET_POSITIONS, 15, positions);
	for (u8 i = 0; i < ROLE_COUNT; ++i) {
		const short familiarity = positions[roles[i].positionIndex];
		if (familiarity >= 10) {
			double raw = calculateRoleScores(attributes, *roles[i].weights);
			raw -= raw * 0.025 * (20 - familiarity);
			printf("| %s: %.4g%%\n", roles[i].name, raw);
		}
	}
}

float calculateRoleScores(const u8 attributes[54], const u8 weights[54]) {
	float totalScore = 0;
	float totalWeight = 0;
	for (u8 i = 0; i < 54; ++i) {
		totalScore += (float)(attributes[i] * weights[i]);
		totalWeight += (float)weights[i];
	}

	return totalWeight ? totalScore / totalWeight : 0;
}
