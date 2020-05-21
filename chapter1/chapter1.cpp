#include <string.h>
#include <math.h>
#include <vector>
#include <stdio.h> 
#include <stdlib.h>
#include "chapter1.h"


bool isPrime(const int& num) {
	for (int i = 2; i <= std::floor(std::sqrt(num)); i++)
		if (num % i == 0) return false;
	return true;
}


namespace chapter1
{
	void setting_swapping() 
	{
		std::string myNumber = "42";
		std::string myName = "Zod";
		auto tmp = myName;
		
		myName = myNumber;
		myNumber = tmp;
	}

	void print_and_count() 
	{
		unsigned count = 0;
		for (unsigned i = 512; i = 4096; i++) {
			if (i % 5 == 0)
				printf("[%d]  %d\n", count++, i);
		}
	}

	void print_neg52_1066()
	{
		for (int i = -52; i <= 1066; i++)
			printf("%d\n",i);
	}

	void mult_of_6()
	{
		unsigned count = 6;
		while (count++ <= 60000) {
			if (count % 6 == 0) {
				printf("%d\n", count);
			}
		}
	}

	void dont_worry_be_happy()
	{
		for (int i = 98; i--; ) {
			printf("good morning!");
		}
	}

	void counting_dojo_way()
	{
		for (int i = 1; i <= 100; i++) {
			if (i % 5 == 0)
				printf("Coding\n");
			if (i % 10 == 0)
				printf("Dojo\n");
		}
	}

	void mult_of_three_but_not_all()
	{
		for (int i = -300; i <= 0; i++) {
			if ((i != -3 && i != -6) && (i % 3 == 0)) {
				printf("[%d]-", i);
			}
		}
	}

	void print_int_with_while()
	{
		unsigned count = 0;
		while (count++ <= 5280) {
			printf("[%d]-", count);
		}
	}

	bool leap_year(unsigned year)
	{ 
		
		if (year % 400 == 0)
			return true;
		if (year % 100 == 0)
			return false;
		if (year % 4 == 0)
			return true;
	
		return false;
	}

	void flexible_countdown(int lowNum, int highNum, int mult) 
	{
		for (; highNum >= lowNum ; highNum--) {
			if (highNum % mult == 0) {
				printf("[%d]", highNum);
			}
		}
	}

	void final_countdown(int param1, int param2, int param3, int param4)
	{
		while (param3-- >= param2) {
			if (param3 % param1 == 0 && param3 != param4) {
				printf("[%d]", param3);
			}
		}
	}

	void swap_toward_the_center(std::vector<unsigned> &arr) 
	{
		unsigned tmp;
		for (int i = 0; i < std::ceil(arr.size() / 2 ); i++) {
			tmp = arr[i];
			arr[i] = arr[arr.size() - 1 - i];
			arr[arr.size() - 1 - i] = tmp;
		}
	}

	double math_help(double M, double B)
	{
		return  -B / M;
	}

	void whatHappensToday()
	{
		unsigned num = std::rand() % 100;

		if (num <= 10) {
			printf("VOLCANO!\n", num);
		} else if (num >10 && num <= 25) {
			printf("TSUNAMI!\n", num);
		}	else if (num > 25 && num <= 45) {
			printf("EARHTQUAKE!\n", num);
		} else if (num > 45 && num <= 70) {
			printf("BLIZZARD!\n", num);
		} else if (num > 70 && num <= 100) {
			printf("METOER SHOWER !\n", num);
		}
	}

	void what_really_happened_today()
	{
		unsigned v = std::rand() % 100, t =std::rand() % 100, e = std::rand() % 100, b = std::rand() % 100, m= std::rand() % 100;

		printf("volcano[%d]  tsunami[%d]  earthquake[%d] blizzard[%d] meteor[%d]",
			(v <= 10),
			(t > 10 && t <= 25),
			(e > 25 && e <= 45),
			(b > 45 && b <= 70),
			(m > 70 && m <= 100)
		);
	}

	double soaring_IQ(double IQ)
	{
		for (int acc = 0.1; acc <= 0.98;  acc += 0.1) {
			IQ += acc;
		}
		return IQ;
	}

	std::string letter_grade(unsigned grade)
	{
		if (grade < 60)
			return "Score: " + std::to_string(grade) + " Grade: F";
		if (grade >= 60 && grade < 70)
			return "Score: " + std::to_string(grade) + " Grade:D";
		if (grade >= 70 && grade < 80)
			return "Score: " + std::to_string(grade) + " Grade: C";
		if (grade >= 80 && grade < 90)
			return "Score: " + std::to_string(grade) + " Grade: B";
		if (grade >= 90)
			return "Score: " + std::to_string(grade) + " Grade: A";

	}

	std::string more_acccurate_letter_grade(unsigned grade) {
		std::string grade_data = letter_grade(grade);
		unsigned mod;

		if (grade >= 60 && grade < 95) {
			mod = grade % 10;
		
			if (mod <= 1)
				grade_data += '-';
			if (mod >= 8)
				grade_data += '+';
		}

		return grade_data;
	}
};