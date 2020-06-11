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

#ifndef CHAPTER3_H
#define CHAPTER3_H

namespace chapter3
{
	template<class T>
	class Arrays {

	private:
		std::vector<T>* collection;

	public:

		Arrays(Arrays&& arr) noexcept {
			collection = arr.collection;
			arr.collection = nullptr;
		}

		Arrays *operator = (Arrays&& arr) {
			collection = arr.collection;
			arr.collection = nullptr;
			return this;
		}

		Arrays () {
			collection = new std::vector<T>;
		}
		~Arrays() {
			delete collection;
		}
		
		Arrays(const Arrays& arr) = delete;
		Arrays operator = (const Arrays& arr) = delete;
		void push_front(std::vector<T>& arr, const T& data);
		T pop_front(std::vector<T>& arr);
		void insert_at(std::vector<T>& arr, unsigned pos, T value);
		void remove_at(std::vector<T>& arr, unsigned pos, T value);
		void swap_pairs(std::vector<T> & arr);
		void remove_duplicates(std::vector<T>& arr);
		void min_to_front( std::vector<T>& arr);
		void reverse(std::vector<T>& arr);
		void rotate(std::vector<T>& arr, unsigned shiftBy);
		void filter_range(std::vector<T>& arr, unsigned min, unsigned max);
		void print(std::vector<T> arr);
		std::vector<T> concat(const std::vector<T>& a, const std::vector<T> &b);
		std::vector<T> skyline_heights(const std::vector<T> &arr);
		bool credit_card_validation(const std::vector<T> arr);
		void shuffle(std::vector<T>& arr); 
		void remove_range(std::vector<T>& arr, unsigned start, unsigned end);
		void intermediate_sum(std::vector<T>& arr);
		std::vector<T> zip_it(const std::vector<T>& a, const std::vector<T>& b);
		void double_trouble(std::vector<T>& arr);
	};

};

#endif