#pragma once

typedef struct {
	char name[16];
	unsigned char positionIndex;
	unsigned char *weights[54];
} Role;

unsigned char sweeperKeeperDefend[54] = {
	0, // Cro
	0, // Dri
	0, // Fin
	0, // Hea
	0, // Lon
	0, // Mar
	0, // OtB
	1, // Pas
	0, // Pen
	0, // Tackling
	1, // Vis
	1, // Han
	1, // Aer
	3, // Cmd
	0, // Communication
	3, // Kic
	0, // Throwing
	3, // Ant
	1, // Dec
	3, // 1v1
	3, // Pos
	5, // Ref
	1, // Fir
	0, // Tec
	0, // Left foot
	0, // Right foot
	0, // Fla
	0, // Cor
	0, // Teamwork
	0, // Wor
	0, // Long throws
	0, // Eccentricity
	1, // TRO
	0, // TtP
	1, // Acc
	0, // FK
	0, // Str
	0, // Sta
	0, // Pac
	0, // Jum
	0, // Ldr
	0, // Dirtiness
	0, // Bal
	0, // Bra
	0, // Consistency
	0, // Agg
	5, // Agi
	0, // Important Matches
	0, // Injury Proneness
	0, // Versatility
	0, // Natural Fitness
	0, // Det
	0, // Cmp
	3, // Cnt
};

unsigned char fullBackAttack[54] = {
	3, // Cro
	1, // Dri
	0, // Fin
	0, // Hea
	0, // Lon
	3, // Mar
	1, // OtB
	1, // Pas
	0, // Pen
	3, // Tackling
	0, // Vis
	0, // Han
	0, // Aer
	0, // Cmd
	0, // Communication
	0, // Kic
	0, // Throwing
	3, // Ant
	1, // Dec
	0, // 1v1
	3, // Pos
	0, // Ref
	1, // Fir
	1, // Tec
	0, // Left foot
	0, // Right foot
	0, // Fla
	0, // Cor
	3, // Teamwork
	5, // Wor
	0, // Long throws
	0, // Eccentricity
	0, // TRO
	0, // TtP
	5, // Acc
	0, // FK
	0, // Str
	5, // Sta
	5, // Pac
	0, // Jum
	0, // Ldr
	0, // Dirtiness
	0, // Bal
	0, // Bra
	0, // Consistency
	0, // Agg
	1, // Agi
	0, // Important Matches
	0, // Injury Proneness
	0, // Versatility
	0, // Natural Fitness
	0, // Det
	0, // Cmp
	1, // Cnt
};

unsigned char ballPlayingDefender[54] = {
	0, // Cro
	0, // Dri
	0, // Fin
	3, // Hea
	0, // Lon
	3, // Mar
	0, // OtB
	3, // Pas
	0, // Pen
	3, // Tackling
	1, // Vis
	0, // Han
	0, // Aer
	0, // Cmd
	0, // Communication
	0, // Kic
	0, // Throwing
	1, // Ant
	1, // Dec
	0, // 1v1
	3, // Pos
	0, // Ref
	1, // Fir
	1, // Tec
	0, // Left foot
	0, // Right foot
	0, // Fla
	0, // Cor
	0, // Teamwork
	0, // Wor
	0, // Long throws
	0, // Eccentricity
	0, // TRO
	0, // TtP
	5, // Acc
	0, // FK
	3, // Str
	0, // Sta
	5, // Pac
	5, // Jum
	0, // Ldr
	0, // Dirtiness
	0, // Bal
	1, // Bra
	0, // Consistency
	1, // Agg
	0, // Agi
	0, // Important Matches
	0, // Injury Proneness
	0, // Versatility
	0, // Natural Fitness
	0, // Det
	5, // Cmp
	1, // Cnt
};

unsigned char defensiveMidfielder[54] = {
	0, // Cro
	0, // Dri
	0, // Fin
	0, // Hea
	0, // Lon
	1, // Mar
	0, // OtB
	1, // Pas
	0, // Pen
	3, // Tackling
	0, // Vis
	0, // Han
	0, // Aer
	0, // Cmd
	0, // Communication
	0, // Kic
	0, // Throwing
	3, // Ant
	1, // Dec
	0, // 1v1
	3, // Pos
	0, // Ref
	1, // Fir
	0, // Tec
	0, // Left foot
	0, // Right foot
	0, // Fla
	0, // Cor
	3, // Teamwork
	5, // Wor
	0, // Long throws
	0, // Eccentricity
	0, // TRO
	0, // TtP
	5, // Acc
	0, // FK
	1, // Str
	5, // Sta
	5, // Pac
	0, // Jum
	0, // Ldr
	0, // Dirtiness
	0, // Bal
	0, // Bra
	0, // Consistency
	1, // Agg
	0, // Agi
	0, // Important Matches
	0, // Injury Proneness
	0, // Versatility
	0, // Natural Fitness
	0, // Det
	1, // Cmp
	3, // Cnt
};

unsigned char insideForwardAttack[54] = {
	0, // Cro
	3, // Dri
	3, // Fin
	0, // Hea
	1, // Lon
	0, // Mar
	4, // OtB
	1, // Pas
	0, // Pen
	0, // Tackling
	0, // Vis
	0, // Han
	0, // Aer
	0, // Cmd
	0, // Communication
	0, // Kic
	0, // Throwing
	3, // Ant
	0, // Dec
	0, // 1v1
	0, // Pos
	0, // Ref
	3, // Fir
	3, // Tec
	0, // Left foot
	0, // Right foot
	1, // Fla
	0, // Cor
	0, // Teamwork
	5, // Wor
	0, // Long throws
	0, // Eccentricity
	0, // TRO
	0, // TtP
	5, // Acc
	0, // FK
	0, // Str
	5, // Sta
	5, // Pac
	0, // Jum
	0, // Ldr
	0, // Dirtiness
	1, // Bal
	0, // Bra
	0, // Consistency
	0, // Agg
	3, // Agi
	0, // Important Matches
	0, // Injury Proneness
	0, // Versatility
	0, // Natural Fitness
	0, // Det
	1, // Cmp
	0, // Cnt
};

unsigned char insideForwardSupport[54] = {
	0, // Cro
	3, // Dri
	3, // Fin
	0, // Hea
	1, // Lon
	0, // Mar
	3, // OtB
	1, // Pas
	0, // Pen
	0, // Tackling
	1, // Vis
	0, // Han
	0, // Aer
	0, // Cmd
	0, // Communication
	0, // Kic
	0, // Throwing
	1, // Ant
	0, // Dec
	0, // 1v1
	0, // Pos
	0, // Ref
	3, // Fir
	3, // Tec
	0, // Left foot
	0, // Right foot
	1, // Fla
	0, // Cor
	0, // Teamwork
	5, // Wor
	0, // Long throws
	0, // Eccentricity
	0, // TRO
	0, // TtP
	5, // Acc
	0, // FK
	0, // Str
	5, // Sta
	5, // Pac
	0, // Jum
	0, // Ldr
	0, // Dirtiness
	1, // Bal
	0, // Bra
	0, // Consistency
	0, // Agg
	3, // Agi
	0, // Important Matches
	0, // Injury Proneness
	0, // Versatility
	0, // Natural Fitness
	0, // Det
	1, // Cmp
	0, // Cnt
};


Role roles[12] = {
	{ "GK", 0, sweeperKeeperDefend },
	{ "DL (FBA) ", 2, fullBackAttack },
	{ "DC (BPD) ", 3, ballPlayingDefender },
	{ "DR (FBA) ", 4, fullBackAttack },
	{ "DM       ", 5, defensiveMidfielder },
	{ "AML (IFA)", 9, insideForwardAttack },
	{ "AML (IFS)", 9, insideForwardSupport },
	// { "AMC (AMA)", 10, defensiveMidfielder },
	{ "AMR (IFA)", 11, insideForwardAttack },
	{ "AMR (IFS)", 11, insideForwardSupport },
	// { "ST (AFA) ", 12, defensiveMidfielder },
	// { "ST (PFA) ", 12, defensiveMidfielder },
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
// 	0, // Wor
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
