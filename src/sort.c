#include "sort.h"

#include "types.h"


void swap(Player *values, const i8 i, const i8 j) {
	const Player temp = values[i];
	values[i] = values[j];
	values[j] = temp;
}

i8 partition(Player *values, const i8 low, const i8 high, bool (*compare)(Player, Player)) {
	const Player pivot = values[high];
	i8 i = low - 1;

	for (i8 j = low; j <= high; ++j) {
		if (compare(values[j], pivot)) {
			++i;

			if (i != j) {
				swap(values, i, j);
			}
		}
	}

	swap(values, i + 1, high);
	return i + 1;
}

void quickSort(Player *values, const i8 low, const i8 high, bool (*compare)(Player, Player)) {
	if (low >= high) {
		return;
	}

	const i8 pivot = partition(values, low, high, compare);
	quickSort(values, low, pivot - 1, compare);
	quickSort(values, pivot + 1, high, compare);
}


bool sortByAge(const Player a, const Player b) {
	return a.age < b.age;
}

bool sortByCurrentAbility(const Player a, const Player b) {
	return a.ca > b.ca;
}

bool sortByPotentialAbility(const Player a, const Player b) {
	return a.pa > b.pa;
}

bool sortByRoleGoalkeeper(const Player a, const Player b) {
	return a.roles[0] > b.roles[0];
}

bool sortByRoleDefenderLeft(const Player a, const Player b) {
	return a.roles[1] > b.roles[1];
}

bool sortByRoleDefenderCentre(const Player a, const Player b) {
	return a.roles[2] > b.roles[2];
}

bool sortByRoleDefenderRight(const Player a, const Player b) {
	return a.roles[3] > b.roles[3];
}

bool sortByRoleDefensiveMidfielder(const Player a, const Player b) {
	return a.roles[4] > b.roles[4];
}

bool sortByRoleAttackingMidfielderLeftSupport(const Player a, const Player b) {
	return a.roles[5] > b.roles[5];
}

bool sortByRoleAttackingMidfielderLeftAttack(const Player a, const Player b) {
	return a.roles[6] > b.roles[6];
}

bool sortByRoleAttackingMidfielderCentre(const Player a, const Player b) {
	return a.roles[7] > b.roles[7];
}

bool sortByRoleAttackingMidfielderRightSupport(const Player a, const Player b) {
	return a.roles[8] > b.roles[8];
}

bool sortByRoleAttackingMidfielderRightAttack(const Player a, const Player b) {
	return a.roles[9] > b.roles[9];
}

bool sortByRoleStrikerAttackingForward(const Player a, const Player b) {
	return a.roles[10] > b.roles[10];
}

bool sortByRoleStrikerPressingForward(const Player a, const Player b) {
	return a.roles[11] > b.roles[11];
}
