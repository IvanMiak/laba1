#ifndef STRUCTS_H
#define STRUCTS_H


#include "structs.h"

double value_probability(unsigned value, abstractDice& d, unsigned number_of_rolls = 100000) {
	auto ans = 0llu;
	for(unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
		if(d.roll() == value) {
			ans++;
		}
	return static_cast<double>(ans) / static_cast<double>(number_of_rolls);
}
double expected_value(abstractDice& d, unsigned number_of_rolls = 100000) {
	auto accum = 0llu;
	for(unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
		accum += d.roll();
	return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

#endif // !STRUCTS_H




