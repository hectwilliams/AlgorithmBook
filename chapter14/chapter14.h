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

#ifndef CHAPTER14_H
#define CHAPTER14_H


namespace chapter14 {

	template <class T>
	class HashMap {	
		int capacity;

	protected:
		int numKeys;
		 std::vector<std::vector<std::tuple< std::string, T>>> table;

		 virtual const  int& HashCode(std::string key) {
			uint32_t&& result = 0;
			for (auto c : key) {
				result += static_cast<int>(c);
			}
			return result % capacity;
		 }

	public:

		HashMap(int cap) :capacity{ cap }, numKeys{ 0 }, table{} {
			table.resize(cap, {});
		}

		void insertHashTable(std::string key, T val, std::vector<std::tuple< std::string, int>>  & bucket) {
			numKeys++;
			bucket.push_back(std::tuple<std::string, int> (key, val) );
		}

		 HashMap& Add(std::string key, T val) {
			int code = HashCode(key);
			auto& arr = table[code];
			int i = 0;
			
			for (auto tuple : arr) {
				if (std::get<0>(tuple) == key && std::get<1>(tuple) == val) {
					arr[i] = std::make_tuple(key, val);		// " key/value found in table, overwriting ... ";
					return *this;
				}
			}
			insertHashTable(key, val, arr);
			return *this;
		}

		std::tuple<T, bool> find(std::string key) {
			int code = HashCode(key);
			for (auto tuple : table[code]) {
				if (std::get<0>(tuple) == key) {
					return std::make_tuple(std::get<1>(tuple), true);
				}
			}
			return std::make_tuple(NULL, false);
		}

		 std::tuple<T, bool> remove(std::string key) {
			int code = HashCode(key);
			std::vector<std::tuple< std::string, T> >& arr = table[code];
			std::tuple<int, bool> result;

			for (int i = 0; i < arr.size(); i++) {
				if (std::get<0>(arr[i]) == key) {
					result = std::make_tuple(std::get<1>(std::move(arr[i])), true);
					arr.erase(arr.begin() + i);
					numKeys--;
					return result;
				}
			}
			return std::make_tuple(NULL, false);
		}

		std::map<std::string, T> SelectKeys(std::vector<std::string> keyArray) {
			std::map<std::string, T> result;
			T val_buffer;
			bool boolean;
			for (auto key : keyArray) {
				std::tie(val_buffer, boolean) = find(key);
				if (boolean)
					result.insert(std::make_pair(key, val_buffer));
			}

			return result;
		}

		
		void grow(uint32_t newCap = 0) {
			table.resize(newCap == 0 ? (capacity * .5) + capacity : newCap);
			for (auto& array : table) {
				int max = array.size();
				T value;
				std::string key;

				while (max > 0) {
					value = std::get<1>(array.front());
					key = std::get<0>(array.front());
					array.erase(array.begin());
					numKeys--;

					Add(std::move(key), std::move(value));
					max--;
				}
			}
		}

		bool isEmpty() {
			return numKeys == 0;
		}

		void printHashMap() {
			for (int i = 0; i < table.size(); i++) {
				printf(" bucket: %d \n", i);
				for (auto& tuple : table[i]) {
					printf("\t\t %s \t | %d \n\n", std::get<0>(tuple).c_str(), std::get<1>(tuple));
				}
			}
		}

		const double& LoadFactor() {
			return numKeys / static_cast<double>(table.size());
		}

		void SetSize(int cap) {
			grow(cap);
		}


		void addMap(HashMap hashMap_in) {
			std::tuple<std::string, T> tuple_buffer, curr_buffer;
			T internal_val;
			bool internal_bool;

			for (auto &bucket_in : hashMap_in.table) {
				for (auto &tuple_in : bucket_in) {
					std::tie(internal_val, internal_bool) = this->find(std::get<0>(tuple_in));  
					if (internal_bool)  // duplicate key   remove current key pair
						this->remove(std::get<0>(tuple_in));
					this->Add(std::get<0>(tuple_in), std::get<1>(tuple_in));
				}
			}
		}
		

	};

	template <class T> 
	class HashMultiMap : public HashMap<T> {
	
	public:

		HashMultiMap(int cap) : HashMap<T>(cap) {}

		  HashMultiMap& Add(std::string key, T val)   {
			int code = this->HashCode(key);
			auto &arr = this->table[code];
			for (auto curr_tuple : arr) {
				if (std::get<0>(curr_tuple) == key && std::get<1>(curr_tuple) == val)
					return *this;
			}
			this->insertHashTable(key, val, arr);
			return *this;
		}

		std::tuple< std::vector<T>, bool> find(std::string key) {
			int code = this->HashCode(key);
			auto& arr = this->table[code];
			std::vector<T> valueList;

			for (auto curr_tuple : arr) {
				if (std::get<0>(curr_tuple) == key) {
					valueList.push_back(std::get<1>(curr_tuple));
				}
			}
			 
			if (valueList.empty())
				return std::make_tuple(valueList, false);
			else
				return std::make_tuple(valueList, true);
		}

		std::tuple<std::vector<T>, bool> remove(std::string key) {
			int code = this->HashCode(key);
			auto& arr = this->table[code];
			std::vector<T> listValues;
			uint32_t start = -1;
			 
			for (int i = 0; i < arr.size(); i++) {
				 
				if (std::get<0>(arr[i]) == key) {
					if (start == -1)
						start = i;
					listValues.push_back(std::get<1>(arr[i]));
				}
			}
			 
			if (listValues.size()) {
				arr.erase(arr.begin() + start, arr.begin() + start + listValues.size());
				return std::make_tuple(listValues, true);
			} else {
				return std::make_tuple(listValues, false);
			}
		  
		}
	};

	template <class T>
	class HashSet : public HashMap<T> {
	public:
		HashSet(int cap) : HashMap<T>(cap)  {}

		HashSet& Add(std::string key)   {
			int code = this->HashCode(key);
			auto& arr = this->table[code];
			 
			for (int i = 0; i < arr.size(); i++) {
				if (key == std::get<0>(arr[i]))
					return *this;
			}

			this->insertHashTable(key, 1, arr);
			return *this;
		}
		   
		bool find(std::string key) {
			for (auto& tuple : this->table[this->HashCode(key)]) {
				if (std::get<0>(tuple) == key) {
					return true;
				}
			}
			return false;
		}

		 bool  remove(std::string key) {
			 int code = this->HashCode(key);
			 auto& arr = this->table[code];
			 
			 if (!arr.empty()) {
				 for (int i = 0; i < arr.size() ; i++) {
					 if (key == std::get<0>(arr[i])) {
						 arr.erase(arr.begin() + i);
						 return true;
					 }
				 }
			 } 
			 
			 return false;
		 }

	};


	template <class T>
	class HashMultiSet : public HashSet<T> {

	public:
		HashMultiSet (int cap) : HashSet<T>(cap) {}

		 HashMultiSet& Add(std::string key) {
			int code = this->HashCode(key);
			auto& arr = this->table[code];
			for (auto& tuple : arr) {
				if (std::get<0>(tuple) == key) {
					++std::get<1>(tuple);
					return *this;
				}
			}
			this->insertHashTable(key, 1, arr);
			return *this;
		}


		 int find(std::string key) {
			 for (auto& tuple : this->table[this->HashCode(key)]) {
				 if (std::get<0>(tuple) == key) {
					 return std::get<1>(tuple);
				 }
			 }
			 return 0;
		 }

		 bool remove(std::string key) {
			 for (auto& tuple : this->table[this->HashCode(key)]) {
				if (std::get<0>(tuple) == key) {
					--std::get<1>(tuple);
					return true;
				}
			 }
			 return false; 
		 }

	};
}
#endif