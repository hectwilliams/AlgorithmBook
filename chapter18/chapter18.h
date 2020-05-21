

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

#ifndef CHAPTER18_H
#define CHAPTER18_H



namespace chapter18 {
	
	class Octal {
	private:
		int system = 8;
	public:
		std::string dec_to_oct_string(int num);
		std::string oct_to_dec_string(std::string str);
	};

	class Hexadecimal {
	private:
		int system = 16;
	public:
		std::string dec_to_hex_string(int num, bool uppercase = false);
		std::string hex_to_dec_string(std::string str);
	};

	class Binary {
	private:
		int system = 2;
	public:
		std::string dec_to_bin_string(int num);
		std::string bin_to_dec_string(std::string str);
	};

	// fun problem 
	std::vector <std::string> ReOrderWordFragments(std::vector<std::string> words);

	class Bits {
	public:
		unsigned count_set_bits(int number);
		unsigned reverse_bits(unsigned num_32);
		unsigned encodeByte32(std::array<unsigned, 4> bytes);
		std::array<unsigned, 4> decodeByte32(unsigned num_32);
		unsigned encode_bit_num(bool bit, unsigned bit_pos, unsigned value);
		unsigned decode_bit_num(unsigned bit_pos, unsigned value);
	};

	class ByteArray {
		std::vector<unsigned> array;
		unsigned dword_lanes = 4;
		unsigned bytes_per_lane = 4; 
	public:
		ByteArray() {
			array.resize(dword_lanes);
		}

		bool set(const unsigned& index, const unsigned& value);
		std::tuple<unsigned, bool> get(const unsigned& index);
		void printByteArray();
	};

	class BitArray {
	unsigned data;
	
	public:
		bool set(unsigned index, bool val);
		bool get(unsigned index);
	};

	void RadixSort(std::vector<unsigned>& array);

	class Sprinklers {
	private:
		const unsigned sprinkler_count = 28;
		unsigned sprinkler_system;
		unsigned on_pos = 0;
	public:
		Sprinklers() :sprinkler_system{}
		{}
		void randomToggleBit();
		void tasks_run();
		friend std::ostream& operator <<(std::ostream &op, const Sprinklers& obj);
	};

	class LEDEncoding {
	private:
		std::map<std::string, unsigned> numeral_code = {
			{"012456", 0},
			{"25", 1},
			{"02346",2},
			{"02356", 3},
			{"1235", 4},
			{"01356", 5},
			{"013456", 6},
			{"025", 7}, 
			{"0123456", 8},
			{"01235", 9}
		};

	public:
		std::string led_to_numeral( uint8_t byte);
		std::array<unsigned, 5> int_to_led(unsigned value);
	};
}



#endif
