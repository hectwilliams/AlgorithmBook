
#include "chapter7.h"

template <typename T>
double average(std::vector<T> numbers)
{
  std::pair<bool, double> result = {false, 0};
  double avg = 0;
  double cnt = 0; 

  for (auto& num : numbers) {
    avg += num;
    cnt++;
  }
  return avg / cnt;
}

template <typename T>
bool balance_point(std::vector<T> &arr, unsigned *point)
{
  int left, right;
  bool result = false;

  for (int i = 0; i < arr.size() - 1; i++) {
		left = 0, right = 0;
	
    /*left sum*/
		for (int l = 0; l <= i; l++) {
      left += arr[l];
		}
    /*right sum*/
		for (int r = i + 1; r < arr.size(); r++) {
      right += arr[r];
		}
    result |= left == right;
    
    if (result)
			*point = i;
  }
  return result;
}

template <typename T>
bool balance_index(std::vector<T> &arr)
{
  unsigned index;
  balance_point(arr, &index);
  std::cout << index;
  return index;
}

template <typename T>
double taco_truck(std::vector<std::array<T, 2>> arr)
{
  double manhattanDistance;
  double result; 
  taco_truck_limits limits;
  int x, y;
  
for (int i = 0; i < arr.size(); i++) {
    x = arr[i][0];
    y = arr[i][1];

    if (i == 0) { 
      limits.minY = y;
      limits.maxY = y;
      limits.minX = x;
      limits.maxX = x;
    } else { 
      if (y < limits.minY)
        limits.minY = y;
      if (y > limits.maxY)
        limits.maxY = y;
      if (x < limits.minX)
        limits.minX = x;
      if (x > limits.maxX)
        limits.maxX = x;
    }
  }
  
  for (int x = limits.minX; x <= limits.maxX; x++) {
    for (int y = limits.minY; y <= limits.maxY; y++) {
      manhattanDistance = 0;
      for (auto& ele: arr) 
        manhattanDistance += std::abs(x - ele[0]) + std::abs(y - ele[1]);
      if ((x == limits.minX  && y == limits.minY) || (manhattanDistance < result))
        result = manhattanDistance;      
    }
  }
  return result;
}

bool binary_search(std::vector<int> arr, int target)
{
  unsigned curr_balance_point = std::floor( arr.size() / 2);
	
	if (arr.size() == 0)
    return false;
  if (target == arr[curr_balance_point])
    return true;
  else if (target < arr[curr_balance_point])
    return binary_search(std::vector<int>(arr.begin(), arr.begin() + curr_balance_point), target);  // vector copy constructor
  else if (target > arr[curr_balance_point])
    return binary_search(std::vector<int>(arr.begin() + curr_balance_point + 1, arr.end()), target);
}

const char* min_of_sorted_rotated(std::vector< const char*> strings)
{
  unsigned curr_balance_point = std::floor(strings.size() / 2);
  
  if (strings.size() ==  1)
    return strings[0];

  if (std::strcmp(strings[curr_balance_point +1 ], strings[curr_balance_point]) < 0 )
    return min_of_sorted_rotated(std::vector<const char*>(strings.begin()+curr_balance_point+1, strings.end()))  ;
  else if (std::strcmp(strings[curr_balance_point - 1], strings[curr_balance_point]) < 0)
    return min_of_sorted_rotated(std::vector<const char*>(strings.begin(), strings.begin() + curr_balance_point));
  else 
    return strings[curr_balance_point];
}

int binary_search_string(std::string str, char character)
{
  unsigned curr_balance_point = std::floor(str.size() / 2); 
  
  if (str.size() == 0)
    return -1;
  
  if(str[curr_balance_point] == character)
    return true;

  if (character < str[curr_balance_point])
    return binary_search_string(str.substr(0, curr_balance_point), character);
  if (character > str[curr_balance_point])
    return binary_search_string(str.substr(curr_balance_point + 1), character);

}

std::vector<int> remove_duplicates(std::vector<int>& collection)
{
  std::vector<int> result;
  std::set<int> sets;
  
	for (auto& ele : collection) {
    if (sets.count(ele) == 0) {
      sets.insert(ele);
      result.insert(result.begin(), ele);
    }
  return result;
  }
}

void remove_duplicates_second(std::vector<int>& collection)
{
	int index;

	/**align like members */
	for (int i = 0; i < collection.size() - 1; i++) {
		index = i;
		for (int j = i; j < collection.size(); j++) {
			if (collection[i] == collection[j]) {
				std::swap(collection[j], collection[index++]);
			}
		}
	}

	/* remove dups*/
	index = 0;
	while (index < collection.size() - 1) {
		if (collection[index] == collection[index + 1]) {
			collection.erase(collection.begin() + index + 1);
		} else {
			index++;
		}
	}
}

void remove_duplicates_third(std::vector<int>& collection) {
	int index;
	std::set<int> sets;

	for (int i = 0; i < collection.size(); i++) {
		if (sets.count(collection[i]) == 0) {
			sets.insert(collection[i]);
		} else {
			collection.erase(collection.begin() + i);
			i--;
		}
	}
}

mode_struct mode(std::vector<int> collection)
{
	std::map<int, int> histo;
	mode_struct obj = {NULL, 0};

	for (auto &ele: collection) {
		if (histo.count(ele) == 0)
			histo.insert(std::make_pair(ele, 0));
		histo.at(ele)++;
	}

	for (auto& map_meta : histo) {
		if (obj.valid == NULL) {
			obj.valid = true;
			obj.max = map_meta.first;
		}

		if (map_meta.second > obj.max)
			obj.max = map_meta.first;
	}
	return obj;
}



void arr_buffer_copy(std::vector<int> source, std::vector<int> dest, unsigned source_start_index, unsigned dest_start_index, unsigned numVals)
{
	while (numVals > 0) {
		source[source_start_index++] = dest[dest_start_index++];
		numVals--;

		if (dest_start_index >= dest.size())
			dest_start_index = 0;

		if (source_start_index >= source.size())
			source_start_index = 0;
	}
}

unsigned int smarter_sum(unsigned int num) {
	unsigned int result = 0;
	for (int i = 0; i < num; i++)
		result += i;
	return result;
}

unsigned int faster_factorial(unsigned int num) {
	unsigned int result = 0;
	for (int i = 0; i < num; i++)
		result *= i;
	return result; 
}

unsigned iFib(unsigned int num) {
	unsigned int regs[2] = { 0, 1 };
	unsigned int tmp;

	if (num == 0)
		return num;
	
	if (num == 1)
		return num;

	for (int i = 2; i <= num; i++) {
		tmp = regs[0] + regs[1];
		regs[0] = regs[1];
		regs[1] = tmp;
	}

	return regs[1];
}

unsigned int iTrib(unsigned int num) {
	unsigned int regs[3] = { 0, 0, 1 };
	unsigned int sum;

	if (num == 0)
		return regs[0];

	if (num == 1)
		return regs[1];
	
	if (num == 2)
		return regs[2];

	for (int i = 2; i <= num; i++) {
		sum = 0;
		for (int j = 3; j--; ) {
			sum += regs[j];
		}
		regs[0] = regs[1];
		regs[1] = regs[2];
		regs[2] = sum;
	}

	return regs[2];
}

double median_sorted_arrays(std::vector<int> a, std::vector<int> b ) {
	unsigned int idx_a = 0, idx_b = 0;
	unsigned int pivot = std::floor((a.size() + b.size()) / 2);
	std::vector<float> buffer;
	double i = 0;
	double avg = 0;

	while ( idx_a + idx_b <= pivot ) {
		if (idx_a >= a.size())
			buffer.push_back(b[idx_b++]);
		else if (idx_b >= b.size())
			buffer.push_back(a[idx_a++]);
		else if (a[idx_a] <= b[idx_b])
			buffer.push_back(a[idx_a++]);
		else if (b[idx_b] <= a[idx_a])
			buffer.push_back(b[idx_b++]);
		i++;
	}

	if ((a.size() + b.size()) % 2 == 0) {
		return (buffer[i - 2] + buffer[i - 1]) / 2;
	} else {
		return buffer[i-1];
	}

}

std::string time_to_english(unsigned int num)
{
	std::string msg;
	unsigned int hour, minute, next_hour;
	std::string h_curr, h_next, tail;
	minute = num % 60;
	hour = (static_cast<int>(std::floor(num / 60)) % 24 );
	
	if (hour == 0) {
		h_curr = "midnight";
		h_next = "1am";
	} else if (hour == 12) {
		h_curr = "noon";
		h_next = "1pm";
	} else {
		tail = (hour >= 12) ? "pm" : "am";
		h_curr = std::to_string(hour) + tail;
		next_hour = (hour + 1) % 24;
		tail = std::to_string(next_hour);  // reassign  
		h_next = (next_hour == 12)? "noon" : (next_hour == 0) ? "midnight": (next_hour >12) ? tail + "pm" : tail + "am";
	}

	if (minute == 15)
		msg = "quarter past ";
	else if (minute <= 30)
		msg = (minute == 30) ?  "half past" : std::to_string(minute)  + "past";
	else if (minute == 45)
		msg = "quarter till";
	else if (minute > 30)
		msg += std::to_string(60 - minute) + " " + "until";
	
	if (msg.find("past") != std::string::npos) {
			msg +=  " " + h_curr;
	} else {
		msg += " "  +  h_next;
	}
	return msg;
}

/* sum of consercutive integers

	 = (n / 2 ) *  (x[0] - x[n-1])

*/

int missing_value(std::vector<int> numbers)
{
	int missing_sum = 0;
	int curr = 0;
	int min = 0;
	int max = 0;
	int i = 0;
	
	for (i = 0; i < numbers.size(); i++) {
		curr = numbers[i];
		missing_sum += curr;

		if (i == 0) {
			min = curr;
			max = curr;
		} 
		
		if (curr < min) {
			min = curr;
		} 
		
		if (curr > max) {
			max = curr;
		}
	}

	curr = 0.5 * ((max + min) * ( (i + 2) ));
	return curr - missing_sum;
}

unsigned  int rain_terraces(std::vector<int> heights)
{
  std::vector<int> stack;
	unsigned int curr, max;
  unsigned int  sum = 0;

  for (int i = 0; i < heights.size(); i++) {
    curr = heights[i];

    if (i == 0) 
      max = curr;
		
    if (curr < max) 
      stack.push_back(max - curr);
		
    if (curr > max) {
      while (!stack.empty()) {
        sum += stack[stack.size() - 1];
        stack.pop_back();
      }
			max = curr;
    }
  }
  return sum;
}

unsigned int last_digit_a_to_b(unsigned int a, unsigned int b)
{
	unsigned int cyclic_count = 0;
	unsigned start = b % 10;
	unsigned end = NULL;
	std::vector<int> cycle_list; 

	while (1) {
		end = (int)std::pow(b, cyclic_count + 1) % 10;
		cycle_list.push_back(end);
		if (cycle_list[cycle_list.size() - 1] == start &&  (cyclic_count+1) > 1)
			break;
		cyclic_count++;
	}
	return cycle_list[a % cyclic_count];
}

bool matrix_search(std::vector<std::vector<int>> image, std::vector<std::vector<int>> sub_image)
{
	bool match_found = false;

	for (int row = 0; row < image.size(); row++) {
		for (int col = 0; col < image[row].size(); col++) {
			match_found = true;
			
			if (image[row][col] == sub_image[0][0]) { /* matching  bit at left-top pixel*/
				for (int walk_row = 0; walk_row < sub_image.size(); walk_row++) {
					if (row + walk_row >= image.size())  /* walk past row boundary*/
						break;
					for (int walk_col = 0; walk_col < sub_image[walk_row].size(); walk_col++) {
						if (col + walk_col >= image[walk_col].size())  /* walk past col boundary*/
							break;
						match_found &=  (image[row + walk_row][col + walk_col] == sub_image[walk_row][walk_col]);
					}
				}

				if (match_found) {
					return true;
				}

			}
		}
	}

	return false;
}

std::string max_subarray(std::vector<int> numbers)
{
	int start_index = 0, end_index = 0;
	int curr_sum = 0;
	int data; 
	int index = 0;
	int b0, b1;
	std::string result[3] = { "[" , "", "]" };

	while (index < numbers.size()) {
		data = numbers[index];

		if (data >= curr_sum) {
			end_index = index;
			curr_sum += data;
		} else if (index + 1 < numbers.size()) {
			b0 = curr_sum + data + numbers[index + 1];
			b1 = numbers[index + 1];
			if (b1 > b0) {
				curr_sum = b1;
				index += 1;
				start_index = index;
			} else {
				curr_sum = b0;
				end_index = index;
			}
		}
		index++;
	}

	for (int i = start_index; i <= end_index; i++) {
		result[1] += std::to_string(numbers[i]) + ((i != end_index) ? ",": "");
	}

	return result[0] + result[1] + result[2];
}

 int main() {
	std::cout << max_subarray({1, 2, -4, 3, -2, 3, -1});
	 
	// std::vector<int> max_subarray(std::vector<int> numbers)
}
