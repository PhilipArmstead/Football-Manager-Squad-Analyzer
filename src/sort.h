#pragma once

#include "types.h"


void swap(Player *values, i8 i, i8 j);
i8 partition(Player *values, i8 low, i8 high, bool (*compare)(Player, Player));
void quickSort(Player *values, i8 low, i8 high, bool (*compare)(Player, Player));

bool sortByAge(Player a, Player b);
bool sortByPotentialAbility(Player a, Player b);
bool sortByCurrentAbility(Player a, Player b);
bool sortByRoleGoalkeeper(Player a, Player b);
bool sortByRoleDefenderLeft(Player a, Player b);
bool sortByRoleDefenderCentre(Player a, Player b);
bool sortByRoleDefenderRight(Player a, Player b);
bool sortByRoleDefensiveMidfielder(Player a, Player b);
bool sortByRoleAttackingMidfielderLeftSupport(Player a, Player b);
bool sortByRoleAttackingMidfielderLeftAttack(Player a, Player b);
bool sortByRoleAttackingMidfielderCentre(Player a, Player b);
bool sortByRoleAttackingMidfielderRightSupport(Player a, Player b);
bool sortByRoleAttackingMidfielderRightAttack(Player a, Player b);
bool sortByRoleStrikerAttackingForward(Player a, Player b);
bool sortByRoleStrikerPressingForward(Player a, Player b);
