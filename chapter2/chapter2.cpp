#include <iostream>
#include <math.h>
#include <vector>
#include <array>
#include <algorithm>
#include <cstdlib>
#include <stdio.h> 
#include <stdlib.h>
#include <tuple>
#include <exception>
#include <memory>
#include <chrono>
#include <mutex>
#include <future>
#include <iomanip>
#include <string.h>
#include "chapter2.h"


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
	
	
namespace chapter2
{
	
unsigned sigma(unsigned num)
{
  unsigned sum = num;
  for ( ; num-- ; ) {
    sum += num;
  }
  return sum;
}
	
unsigned factorial(unsigned num) 
{
  unsigned result = 1; 
  for (; num > 0 ; num--) {
    result *= num;
  }
  return result; 
}
	
void Star_Art::drawLeftStars(unsigned count, const char & c)
{
  for (int i = 0; (i < max_len); i++) {
    if (count-- > 0) {
      printf("%c", c);
    }
  }
}

void Star_Art::drawRightStars(unsigned count, const char &c)
{
  for (int i = max_len; i > 0; i--) {
    if (i > count)
      printf(" ");
    else
      printf("%c", c);
    }
}

void Star_Art:: drawCenteredStars(unsigned count, const char &c)
{
  std::vector<char> data;
  int l = std::floor(max_len / 2);
  int r = std::floor(max_len / 2) + 1;
  data.resize(max_len, '\0');

  while ( count-- > 0) {
    if (l-- >= 0)
      data[l] = c;
    if (r++ >= 75)
      data[r] = c;
  }

  for (auto x : data) {
    std::cout << x;
  }
}

void Star_Art::drawLeftChars(unsigned count, const char& c) 
{
  drawLeftStars(count, c);
}
void Star_Art::drawRightChars(unsigned count, const char& c) 
{
  drawRightStars(count, c);
}
void Star_Art::drawCenteredChars(unsigned count, const char& c) 
{
  drawCenteredStars(count, c);
}

unsigned threes_and_fives() 
{
  unsigned sum = 0;
  for (int i = 100; i <= 4000000; i++) {
    if ((i % 3 == 0) ^ (i % 5 == 0)) {
      sum += i;
    }
  }
  return sum;
}

unsigned better_threes_and_fives(unsigned start, unsigned end)
{
  unsigned sum = 0;
  for (int i = start; i <= end; i++) {
    if ((i % 3 == 0) ^ (i % 5 == 0)) {
      sum += i;
    }
  }
  return sum;
}

void generate_coin_chnage(unsigned cents)
{
  unsigned quarters = 0, dimes = 0, nickels = 0, pennies = 0;
  while (cents > 0) {
    if (cents >= 25) {
      cents -= 25;
      quarters++;
    } else if (cents >= 10) {
      cents -= 10;
      dimes++;
    } else if (cents >= 5) {
      cents -= 5;
      nickels++;
    } else if (cents >= 1) {
      cents -= 1;
      pennies++;
    }
  }

  printf("quarters-[%d]  dimes-[%d]  nickels-[%d]  pennies-[%d]",
  quarters,
  dimes,
  nickels,
  pennies);
}

double messy_math_mashup(double num) {
  double sum = 0;
  for (int count = 0; count <= num; count++) {
    if (count % 3 == 0)
      continue;
    else if (count % 7 == 0)
      sum += static_cast<double>(2*count);
    else if (count == num / 3)
      return -1;
    else
      sum += count;
  }
  return sum;
}

void twelve_bar_blues() {
  for (int i = 12; i--; ) {
    printf("[%d] chick bool chick\n", i);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

unsigned fibonacci(unsigned index) 
{
  unsigned reg[2] = { 0, 1 };
  unsigned tmp;

  for (int i = 0; i <= index; i++) {
    if (i > 1) {
      tmp = reg[1];
      reg[1] = reg[1] + reg[0];
      reg[0] = tmp;
    }
  }
  return reg[+(index > 0)];
}

unsigned sumToOne(unsigned num)
{
  unsigned sum = 0;
  while (num > 0) {
    sum += num % 10;
    num /= 10;
  }

  if (sum >= 10) {
    return sumToOne(sum);
  }
}

void clock_handle_angles(unsigned seconds)
{
/*
  60 sec = 1min = 6 degs
  1 hour = 30 degs
*/

  double sec = seconds % 60;
  double min = (seconds / 60) % 60;
  double hours = (seconds/ 3600) % 12 ;
  double extra_sec;
  double extra_min;

  double angle_sec, angle_hour, angle_min;

  extra_sec = 6.0 * (sec / 60.0); /*  calc extra seconds in current minute */
  extra_min = 30.0 * (min / 60.0); // /* calc extra minutes in current hour */

/* conversion from time to angle */
  angle_sec = (sec / 60) * 360.0; 
  angle_min = ((min / 60) * 360) + extra_sec;
  angle_hour = ((hours / 12) * 360) + extra_min;;

  printf(" Hour_Hand %f degs  Min_Hand %f degs  Second_Hand %f degs \n", angle_hour, angle_min, angle_sec);
}

bool isPrime(int number) {
  for (int i = 2; i <= std::floor(std::sqrt(number)); i++) {
    if (number % i == 0) {
      return false; 
    }
  }
  return true;
}

double rockin_the_dojo_sweatshirt(unsigned number)
{
  double cost = 20;

  if (number < 2)
    return cost;

  switch (number) {
    case 2:
      return 0.09 * 20;
    case 3:
      return 0.19 * 20;
    default:
      return 0.35 * 20;
  }
}

unsigned extract_o_matic(double num, signed digitNum)
{
  unsigned digit = 0;

  if (digitNum < 0) {
    for (int i = digitNum; i++; ) {
      num *= 10.0;
      printf("num %f \n", num);
    }
  }

  if (digitNum >= 0) {
    for (int i = digitNum; i--; ) {
      num /= 10.0;
      printf("num %f \n", num);
    }
  }

  digit = static_cast<int>(std::abs(num)) % 10;
  return digit;
}

unsigned most_significant_digit(double number)
{
  unsigned digit = 0;
  while (std::abs(number) > 10) {
    number = number / std::pow(10, 1);
    digit = static_cast<int>(std::abs(number)) % 10;
  }
  return digit;
}

unsigned GamingFundamentals::rollOne()
{
  return std::rand() % 6 + 1;
}

void GamingFundamentals::playFives(unsigned num)
{
  unsigned data; 

for (; num--;) {
  data = rollOne();
  printf("rolled value %d \n", data);
  if (data == 5)
    printf("\t That's good luck\n");
  }
}

void GamingFundamentals::playStatistics()
{
  unsigned min = 7, max = 0, data = 0;
  for (int i = 8; i--; ) {
    data = rollOne();
  if (data > max)
    max = data; 
  if (data < min)
    min = data;
  }
	
  printf("min {%d}  max {%d}", min, max);
}

void GamingFundamentals::playStatistics2()
{
  unsigned min = 7, max = 0, data = 0, sum = 0;
  for (int i = 8; i--; ) {
    data = rollOne();
    if (data > max)
      max = data;
    if (data < min)
      min = data;
    sum += data;
  }
  printf("min {%d}  max {%d}  total-sum {%d}", min, max, sum);
}

void GamingFundamentals::playStatistics4(unsigned num)
{
  unsigned min = 7, max = 0, data = 0, sum = 0, average = 0;
	
  for (int i = num; i--; ) {
    data = rollOne();
    if (data > max)
      max = data;
    if (data < min)
      min = data;
    sum += data;
  }
	
  if (num) {
    average = sum / num;
  }
	
  printf("min {%d}  max {%d}  total-sum {%d}  avg {%d}", min, max, sum, average);
}

void GamingFundamentals::statistics_until_doubles()
{
  unsigned min = 7, max = 0, data = 0, sum = 0, average = 0;
  std::map<unsigned, unsigned> stat;
  int i = 1;

  for (;;i++) {
    data = rollOne();
	  
    if (stat.find(data) == stat.end()  ) {
      stat.insert({data, 1});
    } else {
      break;
    }
	  
    if (data > max)
      max = data;
    
    if (data < min)
      min = data;

    sum += data;
  }
  average = sum / i;
  printf("min {%d}  max {%d}  total-sum {%d}  avg {%d} tick {%d}", min, max, sum, average, i);
}

WhereIsClaire WhereIsClaire::reset()
{
  pos[0] = 1;
  pos[1] = 1;
  return *this;
}

WhereIsClaire WhereIsClaire::moveBy(signed x, signed y)
{
  pos[0] += x;
  pos[1] += y;
  return *this;
}

signed WhereIsClaire::xLocation()
{
  return pos[0];
}

signed WhereIsClaire::yLocation()
{
  return pos[1];
}


std::string  Date_on_Deserted_Island::weekdayName(unsigned weekdayNum)
{
  std::string day{};

  if ((weekdayNum < 1) || (weekdayNum > 365))
    return day; 

  switch (weekdayNum % 7) {
  case 1:
    day = "Sunday";
    break;
  case 2:
    day = "Monday";
    break;
  case 3:
    day =  "Tuesday";
    break;
  case 4:
    day = "Wednesday";
    break;
  case 5:
    day =  "Thurday";
    break;
  case 6:
    day = "Friday";
    break;
  case 0:
    day = "Saturday";
    break;
  }
	
  return day; 
}

void Date_on_Deserted_Island::someDays ()
{
  std::string day;

  for (int i = 17; i--; ) {
    day = weekdayName( (rand() % 7) + 1);
    printf("%s\n", day.c_str());
    if (day != "Sunday" && day != "Saturday") {
      printf("\t WORK HARD\n");
    }
  }
}

const char* Date_on_Deserted_Island::monthName(unsigned monthNum)
{
  try {
    if (monthNum > 12 || monthNum < 1)
      throw "invalid month";
    return std::get<1> (days_in_month_map[monthNum - 1]);
  } catch (...) {
    return "";
  }
}

unsigned Date_on_Deserted_Island::month_to_day_in_2017(unsigned monthNum)
{
try {
   if ((monthNum < 1 || monthNum > 12))
    throw "invalid month";
  return std::get<0>(days_in_month_map[monthNum - 1]);
  } catch (...) {
    return 0;
  }
}

const char * Date_on_Deserted_Island::day_to_month(unsigned dayNum)
{
  unsigned start = 0, end = 0;
  
  if ((dayNum < 0 || dayNum> 365))
    return "";
  
  for (int i = 0; i < days_in_month_map.size(); i++) {
    end += std::get<0> (days_in_month_map[i]);
    if (dayNum > start && dayNum <= end) {
      return std::get<1>(days_in_month_map[i]);;
    }
    start = end;
  }
  return "";
}

void Date_on_Deserted_Island::reset_map()
{
  const std::array<std::tuple<int, int>, 12> data = {
    std::make_pair(31, 0),
    std::make_pair(28, 3),
    std::make_pair(31, 3),
    std::make_pair(30, 6),
    std::make_pair(31, 1),
    std::make_pair(30, 4),
    std::make_pair(31, 6),
    std::make_pair(31, 2),
    std::make_pair(30, 5),
    std::make_pair(31, 0),
    std::make_pair(30, 3),
    std::make_pair(31, 5)
  };

  for (int i = 0; i < 12; i++) {
    std::get<0>(days_in_month_map[i]) = std::get<0>(data[i]);
    std::get<2>(days_in_month_map[i]) = std::get<1>(data[i]);
  }
  year = 2017;
}

std::string Date_on_Deserted_Island::full_data(unsigned dayNum)
{
  const char *month = day_to_month(dayNum);
  unsigned offset;
  int i;

  for (i = 0; i < days_in_month_map.size() && dayNum > std::get<0>(days_in_month_map[i]) ; i++) {
    dayNum -= std::get<0>(days_in_month_map[i]);
  }
  offset = std::get<2>(days_in_month_map[i]);

  return weekdayName( offset + dayNum) \
  + " " + month + \
  + " " + std::to_string(dayNum) + \
  + " " + std::to_string(year); 
}

void Date_on_Deserted_Island::offset_calendar(unsigned val, std::tuple<unsigned, const char*, unsigned> &tuple)
{
  std::get<2>(tuple) = (std::get<2>(tuple) + val) % 7;
}

std::string Date_on_Deserted_Island::full_data2(unsigned dayNum)
{
  bool leaped = 0;
  std::string result{};

  while (dayNum > 365) {
    for (int i = 0; i < days_in_month_map.size(); i++) {
      if (leaped) {
        if (std::get<0>(days_in_month_map[i]) == 29)  /* remove shift 29th day from feburary */
          std::get<0>(days_in_month_map[i]) = 28;
        if (i <= 1)   /* shift jan-feb due to previous leap */
          offset_calendar(1, days_in_month_map[i]);
      }
      offset_calendar(1, days_in_month_map[i]);
    }

    dayNum -= leaped ? 366 : 365;
    if (leaped) {
      leaped = false;
    }

    if (leap_year(++year)) { /* leaped year */
      leaped = true;
      for (int i = 0; i < days_in_month_map.size(); i++) {
        if (i == 1) 
          std::get<0>(days_in_month_map[i]) = 29;
        if (i >= 2)   /* shift march-dec by one due to add leap year */
          offset_calendar(1, days_in_month_map[i]);
      }
    }
  }

  for (int i = 1; i <= 12; i++) {
    view_calendar_month(i);  /* print calendar year */
  }

  result = full_data(dayNum);
  reset_map();
  return result;
}

void Date_on_Deserted_Island::view_calendar_month(unsigned month)
{
  std::tuple<unsigned, const char*, unsigned> tuple;
  unsigned index = 0, count = 1, start_day = 0, end_day = 0;

  if (month < 1 || month > 12) {
    return;
  }

  fill_calendar(month);  // update matrix 
  tuple = days_in_month_map[month - 1]; // readin data for mapping calendar
  printf("\t%s\n", std::get<1>(tuple)); // print calendar month to view 

  for (int k = 1; k <= 7; k++) {
    printf("[%s]", days_of_week[k%7]);
  if (k == 7) 
    printf("\n");
  }

  start_day = std::get<2>(tuple);
  end_day = (std::get<0>(tuple) + std::get<2>(tuple));

  for (auto r = 0; r < 6; r++) {
    for (auto c = 0; c < 7; c++) {
      index = (r * 7) + c;
      if (index >= start_day && index < end_day) {
        (count < 10) ? printf("[**%d]", count) : printf("[*%d]", count);
        count++;
      } else {
        printf("[***]");
      }
    }
    printf("\n");
  }
}

void Date_on_Deserted_Island::fill_calendar(unsigned month)
{
  unsigned row = 0, col = 0;
  std::tuple<unsigned, const char*, unsigned> tuple = days_in_month_map[month - 1];

  clear_calendar();
  for (int i = std::get<2>(tuple); i < std::get<0>(tuple); i++) {
    row = std::floor(i / 7);
    col = (i % 7);
    curr_calendar[row][col] = days_of_week[col];
  }
}

void Date_on_Deserted_Island::clear_calendar()
{
  for (auto r = 0; r < 6; r++) {
    for (auto c = 0; c < 7; c++) {
      curr_calendar[r][c] = "*";
    }
  }
}

	
	
};
	
	
	
