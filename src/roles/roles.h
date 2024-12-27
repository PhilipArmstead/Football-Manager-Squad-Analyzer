#pragma once

#include "./afa.h"
#include "./ama.h"
#include "./bpd.h"
#include "./dm.h"
#include "./fba.h"
#include "./ifa.h"
#include "./ifs.h"
#include "./pfa.h"
#include "./skd.h"

typedef struct {
	char name[16];
	unsigned char positionIndex;
	unsigned char *weights[54];
} Role;


Role roles[12] = {
	{"GK", 0, sweeperKeeperDefend},
	{"DL (FBA) ", 2, fullBackAttack},
	{"DC (BPD) ", 3, ballPlayingDefender},
	{"DR (FBA) ", 4, fullBackAttack},
	{"DM       ", 5, defensiveMidfielder},
	{"AML (IFA)", 9, insideForwardAttack},
	{"AML (IFS)", 9, insideForwardSupport},
	{"AMC (AMA)", 10, attackingMidfielderAttack},
	{"AMR (IFA)", 11, insideForwardAttack},
	{"AMR (IFS)", 11, insideForwardSupport},
	{"ST (AFA) ", 12, advancedForwardAttack},
	{"ST (PFA) ", 12, pressingForwardAttack},
};
