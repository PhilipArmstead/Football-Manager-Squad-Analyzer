#include <stdio.h>

#include "analyse.h"
#include "constants.h"
#include "maths.h"
#include "memory.h"
#include "types.h"
#include "./roles/roles.h"


extern const Role roles[ROLE_COUNT];

void printPlayer(
	const unsigned long id,
	const u8 ability[3],
	const u8 attributes[56],
	const u8 personality[8],
	const u8 positions[15]
) {
	const bool canDevelopQuickly =
		attributes[48] < 70 &&
		personality[PERSONALITY_AMBITION] > 10 &&
		personality[PERSONALITY_PROFESSIONALISM] > 10 &&
		attributes[51] > 50;
	const bool isHotProspect = 0; // TODO: depends on age
	char *fastLearnerString = canDevelopQuickly ? "Fast learner  " : "";
	char *hotProspectString = isHotProspect ? "Hot prospect  " : "";

	printf("\n\n\n\n\n\n\n\n");

	// TODO: fix positions
	// TODO: add age
	// TODO: add name
	printf(".------------------------------------------.------------------------------------------.\n");
	printf("| %ld (GK, DL/R, ST)          %s%s\n", id, fastLearnerString, hotProspectString);
	printf("| Ability: %d/%d\n", ability[ABILITY_CA], ability[ABILITY_PA]);
	printf(".------------------------------------------.------------------------------------------.\n");

	printf("| Adaptability:  %2d", personality[PERSONALITY_ADAPTABILITY]);
	printf("  Professionalism:  %2d", personality[PERSONALITY_PROFESSIONALISM]);
	printf("  | Consistency:    %2d", attributes[44]);
	printf("  Injury proneness:  %2d", attributes[48]);
	printf("\n| Ambition:      %2d", personality[PERSONALITY_AMBITION]);
	printf("  Sportsmanship:    %2d", personality[PERSONALITY_SPORTSMANSHIP]);
	printf("  | Determination:  %2d", attributes[51]);
	printf("  Versatility:       %2d", attributes[49]);
	printf("\n| Loyalty:       %2d", personality[PERSONALITY_LOYALTY]);
	printf("  Temperament:      %2d", personality[PERSONALITY_TEMPERAMENT]);
	printf("  | Dirtiness:      %2d", attributes[41]);
	printf("\n| Pressure:      %2d", personality[PERSONALITY_PRESSURE]);
	printf("  Controversy:      %2d", personality[PERSONALITY_CONTROVERSY]);
	printf("  | Imp. Matches:   %2d", attributes[47]);

	printf("\n");
	printf(".------------------------------------------.------------------------------------------.\n");

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
