
#include <iostream>
#include <math.h>
#include <set>
#include <vector>
#include <array>
#include <algorithm>
#include <string.h>
#include <cstdlib>
#include <numeric> // accumulate
#include <stdio.h> 
#include <stdlib.h>
#include <sstream>
#include <tuple>
#include <deque>
#include <exception>
#include <memory>
#include <chrono>
#include <mutex>
#include <future>
#include <iomanip>
#include <errno.h>
#include <string.h>
#include "chapter18.h"

extern int errno;

namespace chapter18 {
  
	std::string  Octal::dec_to_oct_string(int num) {
		std::string result = "0o_";
		while (num > 0) {
			result.insert(result.begin() + 3, static_cast<char>( 48 + (num % system)) );
			num = num / system ;
		}
		return result;
	
	}

	std::string Octal::oct_to_dec_string(std::string str) {
		std::string head = "0o";
		int data = 0; 
		int pos;
		int power;
		try {
			
			if (str.find(head) != std::string::npos) 
				pos = str.find(head) + 2;
			
			for (char ch : str.substr(pos, str.length())) {
				if (!std::isdigit(ch)) {
					throw " not a number";
				}
			}

			power = str.length() - pos - 1;

			for (int i = pos; i < str.length(); i++ ) {
				data += (static_cast<int>(str[i]) - 48) * std::pow(system, power--);
			}

			return  std::to_string(data);

		} catch (...) {

			return "";
		}

	}

	std::string Hexadecimal::dec_to_hex_string(int num, bool uppercase) {
		std::string result = "0x";
		int hex_value;
		char ch;

		try {
			while (num > 0) {
				hex_value = (num % system);
				switch (hex_value) {
				case 10:
					ch = uppercase ? 'A' : 'a';
					break;
				case 11:
					ch = uppercase ? 'B' : 'b';
					break;
				case 12:
					ch = uppercase ? 'C' : 'c';
					break;
				case 13:
					ch = uppercase ? 'D' : 'd';
					break;
				case 14:
					ch = uppercase ? 'E' : 'e';
					break;
				case 15:
					ch = uppercase ? 'F' : 'f';
					break;
				default:
					ch = static_cast<char>(48 + hex_value);
				}
				
				result.insert(result.begin() + 2, ch);
				num /= system;
			}
			return result;
		} catch (...) {
			return "";
		}
	}


	std::string Hexadecimal::hex_to_dec_string(std::string str) {
		std::string headers[] = { "0x", "0X" };
		std::string hex_chars = "abcdefABCDEF0123456789";
		int pos = 0;
		int data = 0, power = 0, buffer = 0;
		std::string result; 
		char ch;

		try {
			
			// search for headers 
			for (auto header : headers) {
				if (str.find(header) != std::string::npos) {
					pos += 2;
				}
			}
			
			//validate string input
			for (int i = pos; i < str.length(); i++) {
				if (hex_chars.find(str[i]) == std::string::npos)
					throw "error in hexadecimal value";
			}


			power = str.length() - pos - 1;
			
			//compute
			for ( ; pos < str.length(); pos++) {
				ch = str[pos];

				if (ch == 'A' || ch =='a')
					buffer = 10;
				else if (ch == 'B' || ch == 'b')
					buffer = 11;
				else if (ch == 'C' || ch == 'c')
					buffer = 12;
				else if (ch == 'D' || ch == 'd')
					buffer = 13;
				else if (ch == 'E' || ch == 'e')
					buffer = 14;
				else if (ch == 'F' || ch == 'f')
					buffer = 15;
				else
					buffer = static_cast<int>(ch) - 48;
				
				data += buffer * std::pow(system, power--);
			}

			return std::to_string(data);

		} catch (...) {
			
			return "";
		
		}

	}

	std::string Binary::dec_to_bin_string(int num) {
		std::string result = "0b";
		int counter = 0; 
		while (num > 0) {
			result.insert(result.begin() + 2, static_cast<char>(48 + (num % system)));
			num /= system;
		}
		return result;
	}

	std::string Binary::bin_to_dec_string(std::string str) {
		std::string header = "0b";
		int pos = 0, power = 0, data = 0; 
		
		try {
			
			if (str.find(header) != std::string::npos)
				pos += 2;
			
			for (int i = pos; i < str.length(); i++) {
				if (str[i] != '1' && str[i] != '0')
					throw "binary string not valid";
			}

			power = str.length() - pos - 1;

			for ( ; pos < str.length(); pos++) {
				data += (static_cast<int>(str[pos]) - 48) * std::pow(system, power--);
			}

			return std::to_string(data);
		
		} catch (...) {
			
			return "";
		
		}
	
	}

	std::vector<std::string> ReOrderWordFragments(std::vector<std::string> words) {
		unsigned  word_length, index = 0;
		std::vector<std::string> arr = words; 
		unsigned ;
		char earliestChar = 'A';
		int comp_substring_value;
		int comp_char_value;

		try {
			
			word_length = words[0].length();

			while (index < word_length) { 

				for (int n = 0; n < words.size(); n++) {

					if (index == 0)
						earliestChar = 'A';
					
					if (words[n][index] == '?') 
						words[n][index] = earliestChar;
					
					// possible move word up list to order 
					for (int i = n; i > 0 && n > 0; i--) {
						comp_substring_value = words[i].substr(0, index + 1).compare(words[i - 1].substr(0, index + 1));
						comp_char_value = std::string(1, words[i][index]).compare(std::string(1, words[i - 1][index]));
					
						if (comp_substring_value == -1 && comp_char_value == -1)  // x[n] < x[n-1]
							std::swap(words[i], words[i - 1]);
						if (comp_substring_value == 1 && comp_char_value == -1) 
							throw " ordering is impossible";
						if (comp_substring_value == -1 && comp_char_value == 1) 
							throw " ordering is impossible";
						
						earliestChar = words[i][index];
					}
				}
				index++;
			}

			for (auto w : words) {
				printf("%s \n", w.c_str());
			}
			return words;
		} catch (...) {
			return {};
		}

	}

	unsigned Bits::count_set_bits(int number) {
		unsigned count = 0;
		unsigned const_two = 2;

		while (number > 0) {
			count += number % const_two;
			number /= const_two;
		}
		return count;
	}

	unsigned Bits::reverse_bits(unsigned num_32) {
		unsigned data = 0;
		unsigned bit, pos = 0;

		for (unsigned i = std::ceil(std::log2(num_32)); i--; ) {
			bit = (num_32 & (1 << i)) >> i; // find bit and move to right
			data += (bit << pos++);
		}
		return data;
	}

	unsigned Bits::encodeByte32(std::array<unsigned, 4> bytes) {
		unsigned result = 0 ;
		for (int i = 1; i <= bytes.size(); i++) {
			result += (bytes[i- 1] << (32 - 8 * i));
		}
		return result;
	}

	std::array<unsigned, 4> Bits::decodeByte32(unsigned num_32) {
		unsigned mask = UINT8_MAX;
		std::array<unsigned, 4> result; 
		uint8_t pos = 0, shift;

		for (int i = 4; i--; ) {
			shift = 8 * i;
			result[pos++] = ((mask << shift) & num_32) >> shift;
		}

		//for (auto byte : result) {
		//	std::cout << Hexadecimal().dec_to_hex_string(byte) << '\n';
		//}
		return result;
	}


	bool ByteArray::set(const unsigned& index, const unsigned& value) {
		unsigned lane, dword;
		std::array<unsigned, 4> bytes;

		try {

			if (index >= bytes_per_lane * dword_lanes)
				throw "invalid index";

			lane = std::floor(index / dword_lanes);

			dword = array[lane]; // get 32 bit word

			bytes = Bits().decodeByte32(dword); // get 32 bit byte array
			bytes[index % bytes_per_lane] = value; // update bytes
			array[lane] = Bits().encodeByte32(bytes);//update dword lane


			return true;
		} catch (...) {

			return false;
		}
	}

	

	std::tuple<unsigned, bool> ByteArray::get(const unsigned& index) {
		unsigned lane; 
		std::array<unsigned, 4> bytes;

		try {
			if (index >= bytes_per_lane * dword_lanes)
				throw "invalid index";

			lane = std::floor(index / dword_lanes);
			bytes = Bits().decodeByte32(array[lane]);
			return { bytes[index % bytes_per_lane], true };
		} catch (...) {
			return { NULL, false };
		}
	}

	void ByteArray::printByteArray() {
		for (auto dword : array) {
			printf("[ ");
			for (auto byte : Bits().decodeByte32(dword)) {
				printf("\t%d", byte);
			}
			printf("] \n");
		}

	}

	unsigned Bits::encode_bit_num(bool bit, unsigned bit_pos, unsigned value) {
	
		try {

			if (bit_pos >= 32)
				throw "invalid bit position";
			
			if (bit) {
				value =  value | (1 << bit_pos);
			} else if (!bit) {
				value = value & ~(value & (1 << bit_pos));
			}

			return value;

		} catch (...) {

			return value;

		}

	}

	unsigned Bits::decode_bit_num(unsigned bit_pos, unsigned value) {

		try {

			if (bit_pos >= 32)
				throw "invalid bit position";

			return (value & (1 << bit_pos)) >>  bit_pos;

		} catch (...) {

			return -1;

		}
	
	}

	bool BitArray::set(unsigned index, bool val) {
		try {
			if (index >= 32)
				throw "invalid bit position";

			if (val)
				data = (1 << index) | data;

			if (!val)
				data = data & ~(1 << index);

			std::cout << Hexadecimal().dec_to_hex_string(data) << '\n';
			return true;
		} catch (...) {
			return false;
		}
	}

	bool BitArray::get(unsigned index) {
		return true;
	}

	void RadixSort_remove(std::vector<std::vector<unsigned>*> &array,const unsigned &bit_pos, const unsigned& target) {
		std::vector<unsigned>* lane; 

	
	}
	void RadixSort(std::vector<unsigned>& array) {

		const unsigned SIZE = 32;
		unsigned pos;
		std::vector<std::vector<unsigned>*> garage;
		std::vector<unsigned> *lane;
		unsigned len_curr_lane;
		unsigned element; 

		for (int i = 0; i < 32; i++) {
			garage.push_back(new std::vector<unsigned>);
			for (int k = 0; k < array.size() && i == 0 ; k++) {
				garage[i]->push_back(array[k]);
			}
		}

		for (int curr_bit = 0; curr_bit < SIZE; curr_bit++) {  // N

			for (int lane_index = 0; lane_index < curr_bit + 1; lane_index++) {  // range of lanes
				lane = garage[lane_index];
				len_curr_lane = lane->size();
				
				for (int i = 0; i < len_curr_lane; i++) {  //subset of lane elements 
					element = lane->front();
					lane->erase(lane->begin());
					
					if (element & (1 << curr_bit))
						garage[curr_bit]->push_back(element);
					else 
						lane->push_back(element);
				}
			}
		}

		pos = pos = array.size() - 1;

		for (int n = 32; n--;) { // reverse  iterator -overrwrite input array
			lane = garage[n];
			for (int i = lane->size(); i--;)
				array[pos--] = lane->at(i);
		}
	
		for (int i = pos; i > 0; i--)  // insert zeros
			array[pos--] = 0;
		
		for (auto ele : array) {
			std::cout << ele << '\n';
		}

		//delete dyn vectors
		for (auto ele : garage)
			delete ele;
	}


	 void Sprinklers::randomToggleBit() {
		 std::string tmp;
		 while (true) {
			 std::this_thread::sleep_for(std::chrono::seconds(1));
			 sprinkler_system = sprinkler_system & ~(1 << on_pos);
			 on_pos = std::rand() % 28;
			 sprinkler_system = sprinkler_system | ( 1 <<  on_pos);
			 std::cout << *this;
		 }
	}
	 
	void Sprinklers::tasks_run() {
		std::thread th1( &Sprinklers::randomToggleBit, this);
		th1.join();
	}

	std::ostream& operator <<(std::ostream& out, const Sprinklers& obj) {
		for (int i = 0; i < obj.sprinkler_count; i++) {
			if (! (obj.sprinkler_system & (1 << i)) )
				out << ("|_");
			else
				out << ("|^");
		}
		out << ("|");

		printf("\n");
		return out;
	}

	std::string LEDEncoding::led_to_numeral(uint8_t byte) {
		std::string code;
		try {
			
			for (int i = 0; i < 8; i++) {
				if (byte % 2) {
					code += static_cast<char>(48 + i);
				}
			}
			
			if (numeral_code.count(code))
				return static_cast<char>(48 + numeral_code.at(code)) + "";
			
			throw "invalid code";
		} catch (...) {
			return "";
		}
	}

	std::array<unsigned, 5> LEDEncoding::int_to_led(unsigned value) {
		std::array<unsigned, 5> result; 
		unsigned tmp;
		for (int i = 0; i < 5; i++) {
			result[i] = 0;
			for (auto obj : numeral_code) {
				if (value % 10 == obj.second) {
					for (auto c : obj.first) {
						result[i] |= (1 <<  (static_cast<int>(c) - 48 ));
					}
					break;
				}
			}
			value /= 10;
		}
		return result;
	}
}