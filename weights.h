#pragma once

#include "./roles/afa.h"
#include "./roles/ama.h"
#include "./roles/bpd.h"
#include "./roles/dm.h"
#include "./roles/fba.h"
#include "./roles/ifa.h"
#include "./roles/ifs.h"
#include "./roles/pfa.h"
#include "./roles/skd.h"

typedef struct {
	char name[16];
	unsigned char positionIndex;
	unsigned char *weights[54];
} Role;


Role roles[12] = {
	{ "GK", 0, sweeperKeeperDefend },
	{ "DL (FBA) ", 2, fullBackAttack },
	{ "DC (BPD) ", 3, ballPlayingDefender },
	{ "DR (FBA) ", 4, fullBackAttack },
	{ "DM       ", 5, defensiveMidfielder },
	{ "AML (IFA)", 9, insideForwardAttack },
	{ "AML (IFS)", 9, insideForwardSupport },
	{ "AMC (AMA)", 10, attackingMidfielderAttack },
	{ "AMR (IFA)", 11, insideForwardAttack },
	{ "AMR (IFS)", 11, insideForwardSupport },
	{ "ST (AFA) ", 12, advancedForwardAttack },
	{ "ST (PFA) ", 12, pressingForwardAttack },
};


// unsigned char defensiveMidfielder[54] = {
// 	0, // Cro
// 	0, // Dri
// 	0, // Fin
// 	0, // Hea
// 	0, // Lon
// 	0, // Mar
// 	0, // OtB
// 	0, // Pas
// 	0, // Pen
// 	0, // Tackling
// 	0, // Vis
// 	0, // Han
// 	0, // Aer
// 	0, // Cmd
// 	0, // Communication
// 	0, // Kic
// 	0, // Throwing
// 	0, // Ant
// 	0, // Dec
// 	0, // 1v1
// 	0, // Pos
// 	0, // Ref
// 	0, // Fir
// 	0, // Tec
// 	0, // Left foot
// 	0, // Right foot
// 	0, // Fla
// 	0, // Cor
// 	0, // Teamwork
// 	0, // Work Rate
// 	0, // Long throws
// 	0, // Eccentricity
// 	0, // TRO
// 	0, // TtP
// 	0, // Acc
// 	0, // FK
// 	0, // Str
// 	0, // Sta
// 	0, // Pac
// 	0, // Jum
// 	0, // Ldr
// 	0, // Dirtiness
// 	0, // Bal
// 	0, // Bra
// 	0, // Consistency
// 	0, // Agg
// 	0, // Agi
// 	0, // Important Matches
// 	0, // Injury Proneness
// 	0, // Versatility
// 	0, // Natural Fitness
// 	0, // Det
// 	0, // Cmp
// 	0, // Cnt
// };
