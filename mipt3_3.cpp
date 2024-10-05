// mipt3_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <random>
#include <ctime>

using namespace std;

unsigned min(unsigned a, unsigned b) {
	if(a < b) {
		return a;
	} else {
		return b;
	}
}

unsigned max(unsigned a, unsigned b) {
	if(a > b) {
		return a;
	} else {
		return b;
	}
}

class abstractDice {
public:
	abstractDice() :seed(0){}
	virtual unsigned roll(){
		return 0;
	}
private:
	unsigned seed;
};

class Dice: public abstractDice {
public:
    Dice(unsigned max, unsigned seed) :
		max(max), dstr(1, max), reng(seed) { }
	Dice() : Dice(0, 0) {}
	unsigned roll() override{
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

	unsigned roll() override{
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
	DoubleDice(abstractDice& d) : BonusDice(d),PenaltyDice(d) {}

	unsigned bonus_roll() {
		return BonusDice::roll();
	}
	unsigned penalty_roll() {
		return PenaltyDice::roll();
	}

private:
	//abstractDice& d;
};

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



int main() {
	Dice d(6, 2);
	ThreeDicePool td(d);
	BonusDice bd(td);
	PenaltyDice pd(td);
	DoubleDice dd(d);
	cout << dd.bonus_roll();
	for(int i = 1; i < 6; i++) {
		cout << value_probability(i, bd) << ", ";
	}
	cout << "\n";
	for(int i = 1; i < 6; i++) {
		cout << value_probability(i, bd) << ", ";
	}
	

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
/*
class ThreeDicePool : public abstractDice {
public:
	ThreeDicePool(unsigned max,
		unsigned seed_1, unsigned seed_2, unsigned seed_3) :
		max(max), dstr_1(1, max), dstr_2(1, max), dstr_3(1, max),
		reng_1(seed_1), reng_2(seed_2), reng_3(seed_3) { }

	unsigned roll() override {
		return dstr_1(reng_1) + dstr_2(reng_2) + dstr_3(reng_3);
	}
private:
	unsigned max;
	std::uniform_int_distribution<unsigned> dstr_1, dstr_2, dstr_3;
	std::default_random_engine reng_1, reng_2, reng_3;
};*/

/*double expected_value(Dice& d, unsigned number_of_rolls = 1) {
	auto accum = 0llu;
	for(unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
		accum += d.roll();
	return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}*/

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
