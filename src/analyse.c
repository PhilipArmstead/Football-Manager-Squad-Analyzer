#include <stdio.h>

#include "analyse.h"

#include "club.h"
#include "constants.h"
#include "date-time.h"
#include "memory.h"
#include "player.h"
#include "roles.h"
#include "watch-list.h"


extern const Role roles[ROLE_COUNT];

void showPlayerScreen(const int fd, Club *watchedClub) {
	u8 bytes[5];
	readFromMemory(fd, POINTER_TO_CURRENT_PERSON, 4, bytes);
	unsigned long personAddress = hexBytesToInt(bytes, 4);

	u8 idBytes[8];
	readFromMemory(fd, personAddress + OFFSET_ID, 8, idBytes);

	if (
		!idBytes[3] ||
		idBytes[0] != idBytes[4] ||
		idBytes[1] != idBytes[5] ||
		idBytes[2] != idBytes[6] ||
		idBytes[3] != idBytes[7]
	) {
		readFromMemory(fd, POINTER_TO_CURRENT_PERSON_ADDRESS, 4, bytes);
		readFromMemory(fd, hexBytesToInt(bytes, 4), 4, bytes);
		personAddress = hexBytesToInt(bytes, 4);
	}

	unsigned long playerAddress = personAddress - PLAYER_OFFSET_PERSON;
	readFromMemory(fd, playerAddress, 5, bytes);
	while (bytes[3] != 0x45 || bytes[4] != 0x01) {
		playerAddress -= 16;
		readFromMemory(fd, playerAddress, 5, bytes);
	}
	Player player = getPlayer(fd, personAddress, playerAddress, getDate(fd));
	Club club = getClubFromPerson(fd, player.personAddress);

	bool isWaiting = true;
	while (isWaiting) {
		printPlayer(&player);

		u8 c = '\n';
		if (isPlayerValid(fd, player.personAddress, player.playerAddress)) {
			printf("\nMake (w)onderkid\n");
			printf("Fully (h)eal\n");
			printf("(d)estroy player\n");
			if (watchedClub->address == club.address) {
				printf("Un-watch %s (s)quads\n", club.name);
			} else {
				printf("Watch %s (s)quads\n", club.name);
			}
			printf("Press anything else to return\n");
			c = getchar();
		}

		const u8 a = c;

		// swallow newline
		while (c != '\n') {
			c = getchar();
		}

		switch (a) {
			case 'w':
				makeWonderkid(fd, player.personAddress, player.playerAddress);
				player = getPlayer(fd, player.personAddress, player.playerAddress, getDate(fd));
				break;
			case 'h':
				healPlayer(fd, player.playerAddress);
				break;
			case 'd':
				destroyPlayer(fd, player.personAddress, player.playerAddress);
				player = getPlayer(fd, player.personAddress, player.playerAddress, getDate(fd));
				break;
			case 's':
				if (watchedClub->address == club.address) {
					watchedClub->address = 0;
				} else {
					addToClubList(fd, watchedClub, &club);
				}

				isWaiting = false;
				break;
			default:
				isWaiting = false;
		}
	}
}

void printPlayer(const Player *p) {
	char *fastLearnerString = p->canDevelopQuickly ? "Fast learner  " : "";
	char *hotProspectString = p->isHotProspect ? "Hot prospect  " : "";

	printf(".------------------------------------------.------------------------------------------.\n");
	printf("| %s %s (%d yrs): ", p->forename, p->surname, p->age);
	printPlayerPositions(p);
	printf("\n");

	printf("| Ability: %d/%d  %s%s ", p->ca, p->pa, fastLearnerString, hotProspectString);
	printf("| Value: £%d\n", p->guideValue);
	printf(".------------------------------------------.------------------------------------------.\n");

	printf("| Adaptability:  %2d", p->personality[PERSONALITY_ADAPTABILITY]);
	printf("  Professionalism:  %2d", p->personality[PERSONALITY_PROFESSIONALISM]);
	printf("  | Consistency:    %2d", (p->attributes[44] + 4) / 5);
	printf("  Injury proneness:  %2d", (p->attributes[48] + 4) / 5);
	printf("\n| Ambition:      %2d", p->personality[PERSONALITY_AMBITION]);
	printf("  Sportsmanship:    %2d", p->personality[PERSONALITY_SPORTSMANSHIP]);
	printf("  | Determination:  %2d", (p->attributes[51] + 4) / 5);
	printf("  Versatility:       %2d", (p->attributes[49] + 4) / 5);
	printf("\n| Loyalty:       %2d", p->personality[PERSONALITY_LOYALTY]);
	printf("  Temperament:      %2d", p->personality[PERSONALITY_TEMPERAMENT]);
	printf("  | Dirtiness:      %2d", (p->attributes[41] + 4) / 5);
	printf("\n| Pressure:      %2d", p->personality[PERSONALITY_PRESSURE]);
	printf("  Controversy:      %2d", p->personality[PERSONALITY_CONTROVERSY]);
	printf("  | Imp. Matches:   %2d", (p->attributes[47] + 4) / 5);

	printf("\n");
	printf(".------------------------------------------.------------------------------------------.\n");

	u8 c = 0;
	for (u8 i = 0; i < ROLE_COUNT; ++i) {
		const float rating = p->roles[i];
		if (rating) {
			if (!i) {
				printf("| %s: %.4g%% ", roles[i].name, rating);
			} else {
				printf("| %-9s: %.4g%% ", roles[i].name, rating);
			}
			++c;
		}

		if (c == 3 || i == ROLE_COUNT - 1) {
			printf("\n");
			c = 0;
		}
	}
}
