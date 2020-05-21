#include <vector>
#include <string>
#include <map>
#include <set>
#include <deque>
#include <array>
#include <string_view>
#include <tuple>
#include <memory>
//#include <thread>
#include <mutex>
#include <future>

#ifndef CHAPTER2_H
#define CHAPTER2_H

namespace chapter2
{
	unsigned sigma(unsigned num);
	unsigned factorial(unsigned num);
	
	class Star_Art {
	private:
		unsigned max_len = 75;
	public:
		void drawLeftStars(unsigned count, const char &c = '*');
		void drawRightStars(unsigned count, const char & c= '*');
		void drawCenteredStars(unsigned count, const char & c= '*');
		void drawLeftChars(unsigned count, const char& c = '*');
		void drawRightChars(unsigned count, const char& c = '*');
		void drawCenteredChars(unsigned count, const char& c = '*');
	};
	unsigned threes_and_fives();
	unsigned better_threes_and_fives(unsigned start, unsigned end);
	void generate_coin_chnage(unsigned cents);
	double messy_math_mashup(double num);
	void twelve_bar_blues();
	unsigned fibonacci(unsigned index);
	unsigned sumToOne(unsigned num);
	void clock_handle_angles(unsigned seconds);
	bool isPrime(int number);
	double rockin_the_dojo_sweatshirt(unsigned number);
	unsigned extract_o_matic(double num, signed digitNum);
	unsigned most_significant_digit(double number);

	class GamingFundamentals {
	public:
		unsigned rollOne();
		void playFives(unsigned num);
		void playStatistics();
		void playStatistics2();
		void playStatistics4(unsigned num);
		void statistics_until_doubles();
	};

	class WhereIsClaire {
		signed pos[2] = { 0, 0 };
	public:
		WhereIsClaire reset();
		WhereIsClaire moveBy(signed x, signed y);
		signed xLocation();
		signed yLocation();
	};

	class Date_on_Deserted_Island {
		std::array< std::tuple<unsigned, const char*, unsigned>, 12> days_in_month_map = {
		/* tuple {days_int_month, month, offset} */
			 std::make_tuple(31, "January", 0),
			 std::make_tuple(28, "Febuary", 3),
			 std::make_tuple(31, "March", 3),
			 std::make_tuple(30, "April", 6),
			 std::make_tuple(31, "May", 1),
			 std::make_tuple(30, "June", 4),
			 std::make_tuple(31, "July", 6),
			 std::make_tuple(31, "August", 2),
			 std::make_tuple(30, "September", 5),
			 std::make_tuple(31, "October", 0),
			 std::make_tuple(30, "November", 3),
			 std::make_tuple(31, "December",5)
		};
		std::vector <const char*> days_of_week = { "Sat", "Sun", "Mon", "Tue", "Wed", "Thu","Fri"};

		unsigned  year = 2017;
		const char* curr_calendar[6][7];
		void fill_calendar(unsigned month = 1);
		void clear_calendar();
		void reset_map();
		void offset_calendar(unsigned val, std::tuple<unsigned, const char*, unsigned> &tuple);

	public:
		std::string weekdayName(unsigned weekdayNum);
		const char* monthName(unsigned monthNum);
		unsigned month_to_day_in_2017(unsigned monthNum);
		const char* day_to_month(unsigned dayNum);
		std::string full_data(unsigned dayNum);
		std::string full_data2(unsigned dayNum); // since dec 31, 2016 
		void someDays();
		void view_calendar_month(unsigned month = 1);
	};

};

#endif