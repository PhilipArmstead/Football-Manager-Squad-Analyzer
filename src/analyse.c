#include <stdio.h>

#include "analyse.h"
#include "maths.h"
#include "memory.h"
#include "types.h"
#include "./roles/roles.h"


static inline void padLeft(const unsigned char byte) {
	if (byte < 10) {
		printf(" ");
	}
	printf("%d", byte);
}

unsigned long printPlayer(Context *ctx) {
	openMemory(ctx);

	unsigned char idString[4];
	readFromMemory(ctx->fd, ctx->attributeBase + 0x0C, 4, idString);
	const unsigned long id = hexBytesToInt(idString, 4);
	unsigned char ability[3];
	readFromMemory(ctx->fd, ctx->attributeBase - 0x78, 3, ability);
	unsigned char bytes[8];
	readFromMemory(ctx->fd, ctx->attributeBase + 0x78, 8, bytes);
	unsigned char attributes[56];
	readFromMemory(ctx->fd, ctx->attributeBase - 0x61, 54, attributes);
	unsigned char positions[15];
	readFromMemory(ctx->fd, ctx->attributeBase - 0x70, 15, positions);

	const bool canDevelopQuickly = attributes[48] < 70 && bytes[1] > 10 && bytes[4] > 10 && attributes[51] > 50;
	// TODO: depends on age
	const bool isHotProspect = 0;
	char *fastLearnerString = canDevelopQuickly ? "Fast learner  " : "";
	char *hotProspectString = isHotProspect ? "Hot prospect  " : "";

	printf("\n\n\n\n\n\n\n\n");

	printf(".------------------------------------------.------------------------------------------.\n");
	printf("| %ld (GK, DL/R, ST)          %s%s\n", id, fastLearnerString, hotProspectString);
	printf("| Ability: %d/%d\n", ability[0], ability[2]);
	printf(".------------------------------------------.------------------------------------------.\n");

	printf("| Adaptability:  ");
	padLeft(bytes[0]);
	printf("  Professionalism:  ");
	padLeft(bytes[4]);
	printf("  | Consistency:    ");
	padLeft(attributes[44]);
	printf("  Injury proneness:  ");
	padLeft(attributes[48]);
	printf("\n| Ambition:      ");
	padLeft(bytes[1]);
	printf("  Sportsmanship:    ");
	padLeft(bytes[5]);
	printf("  | Determination:  ");
	padLeft(attributes[51]);
	printf("  Versatility:       ");
	padLeft(attributes[49]);
	printf("\n| Loyalty:       ");
	padLeft(bytes[2]);
	printf("  Temperament:      ");
	padLeft(bytes[6]);
	printf("  | Dirtiness:      ");
	padLeft(attributes[41]);
	printf("\n| Pressure:      ");
	padLeft(bytes[3]);
	printf("  Controversy:      ");
	padLeft(bytes[7]);
	printf("  | Imp. Matches:   ");
	padLeft(attributes[47]);

	printf("\n");
	printf(".------------------------------------------.------------------------------------------.\n");
	// Age
	// Positions

	for (char i = 0; i < ROLE_COUNT; ++i) {
		const short familiarity = positions[roles[i].positionIndex];
		if (familiarity >= 10) {
			double raw = calculateRoleScores(attributes, *roles[i].weights);
			raw -= raw * 0.025 * (20 - familiarity);
			printf("| %s: %.4g%%\n", roles[i].name, raw);
		}
	}

	return id;
}

float calculateRoleScores(const unsigned char attributes[54], const unsigned char weights[54]) {
	float totalScore = 0;
	float totalWeight = 0;
	for (char i = 0; i < 54; ++i) {
		totalScore += (float)(attributes[i] * weights[i]);
		totalWeight += (float)weights[i];
	}

	return totalWeight ? totalScore / totalWeight : 0;
}
