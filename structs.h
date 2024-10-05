#ifndef FCH
#define FCH

#include <iostream>
#include <random>
#include "func_s.h"

class abstractDice {
public:
	abstractDice() :seed(0) {}
	virtual unsigned roll() {
		return 0;
	}
private:
	unsigned seed;
};

class Dice : public abstractDice {
public:
	Dice(unsigned max, unsigned seed) :
		max(max), dstr(1, max), reng(seed) { }
	Dice() : Dice(0, 0) {}
	unsigned roll() override {
		return dstr(reng);

	}

private:
	unsigned max;
	std::uniform_int_distribution<unsigned> dstr;
	std::default_random_engine reng;
};


class ThreeDicePool1 : public Dice {
public:
	ThreeDicePool1(unsigned max, unsigned seed) : Dice(max, seed) { }

	unsigned roll() override {
		unsigned ans = 0;
		for(int i = 0; i < 3; i++) {
			ans += roll();
		}
		return ans;
	}
};

class ThreeDicePool : public abstractDice {
public:
	ThreeDicePool(abstractDice& d) : d(d) { }

	unsigned roll() override {
		unsigned ans = 0;
		for(int i = 0; i < 3; i++) {
			ans += d.roll();
		}
		return ans;
	}
private:
	abstractDice& d;
};


class PenaltyDice : public abstractDice {
public:
	PenaltyDice(abstractDice& d) : d(d) {}

	unsigned roll() override {
		return min(d.roll(), d.roll());
	}
private:
	abstractDice& d;
};

class BonusDice : public abstractDice {
public:
	BonusDice(abstractDice& d) : d(d) {}
	unsigned roll() override {
		return max(d.roll(), d.roll());
	}
private:
	abstractDice& d;
};

class DoubleDice :public BonusDice, public PenaltyDice {
public:
	DoubleDice(abstractDice& d) : BonusDice(d), PenaltyDice(d) {}

	unsigned bonus_roll() {
		return BonusDice::roll();
	}
	unsigned penalty_roll() {
		return PenaltyDice::roll();
	}

private:
	//abstractDice& d;
};

#endif