#include "roles.h"
#include "afa.h"
#include "ama.h"
#include "bpd.h"
#include "dm.h"
#include "fba.h"
#include "ifa.h"
#include "ifs.h"
#include "pfa.h"
#include "skd.h"


const Role roles[ROLE_COUNT] = {
	{"GK", 2, 0, sweeperKeeperDefend},
	{"DL (FBA)", 8, 2, fullBackAttack},
	{"DC (BPD)", 8, 3, ballPlayingDefender},
	{"DR (FBA)", 8, 4, fullBackAttack},
	{"DM", 2, 5, defensiveMidfielder},
	{"AML (IFA)", 9, 9, insideForwardAttack},
	{"AML (IFS)", 9, 9, insideForwardSupport},
	{"AMC (AMA)", 9, 10, attackingMidfielderAttack},
	{"AMR (IFA)", 9, 11, insideForwardAttack},
	{"AMR (IFS)", 9, 11, insideForwardSupport},
	{"ST (AFA)", 8, 12, advancedForwardAttack},
	{"ST (PFA)", 8, 12, pressingForwardAttack},
};
