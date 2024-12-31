#include <stdio.h>

#include "analyse.h"
#include "constants.h"
#include "maths.h"
#include "memory.h"
#include "types.h"
#include "./roles/roles.h"


extern const Role roles[ROLE_COUNT];

static inline bool getIsHotProspect(const u8 age, const u8 currentAbility) {
	if (age <= 19) {
		return currentAbility >= 80 + 5 * (age - 15);
	}
	if (age <= 23) {
		return currentAbility >= 140;
	}
	return false;
}

static inline bool getCanDevelopQuickly(
	const u8 age,
	const u8 injuryProneness,
	const u8 ambition,
	const u8 professionalism,
	const u8 determination
) {
	return age <= 23 &&
		injuryProneness < 70 &&
		ambition > 10 &&
		professionalism > 10 &&
		determination > 50;
}

void printPlayer(
	const u8 ability[3],
	const u8 attributes[56],
	const u8 personality[8],
	const u8 positions[15],
	const u8 forename[32],
	const u8 surname[32],
	const u8 age
) {
	const bool canDevelopQuickly = getCanDevelopQuickly(
		age,
		attributes[ATTRIBUTES_INJURY_PRONENESS],
		personality[PERSONALITY_AMBITION],
		personality[PERSONALITY_PROFESSIONALISM],
		attributes[ATTRIBUTES_DETERMINATION]
	);
	const bool isHotProspect = getIsHotProspect(age, ability[ABILITY_CA]);
	char *fastLearnerString = canDevelopQuickly ? "Fast learner  " : "";
	char *hotProspectString = isHotProspect ? "Hot prospect  " : "";

	printf("\n\n\n\n\n\n\n\n");

	// TODO: fix positions
	printf(".------------------------------------------.------------------------------------------.\n");
	printf("| %s %s (%d yrs): GK, DL/R, ST\n", forename, surname, age);
	printf("| Ability: %d/%d  %s%s\n", ability[ABILITY_CA], ability[ABILITY_PA], fastLearnerString, hotProspectString);
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
			double raw = calculateRoleScores(attributes, roles[i].weights);
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
