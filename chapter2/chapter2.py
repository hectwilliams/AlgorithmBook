import math
import random

def sigma (num):
  sum = 0
  for n in range(1, num + 1):
    sum += n
  return sum

def factorial (num):
  sum = 1
  for n in range(1, num + 1):
    sum *= n
  return sum

class StarArt():
  def __init__(self):
    self.length = 75
  def draw_left_stars(self, num):
    result = ''
    while self.length is not  0 and num > 0:
      num -= 1
      self.length -= 1;
      result += '*'
    self.length = 75
    return result
  def draw_right_stars(self, num):
    start_point = self.length - num
    counter = 0
    result = ''

    while start_point > 0  and  self.length is not 0:
      if counter >= start_point  :
        result += '*'
      else:
        result += ' '
      self.length -= 1
      counter += 1
    self.length = 75
    return result

  def draw_center_stars(self, num, character = '*'):
    result = ''
    counter = 1
    mid = 37
    length_from_mid =  int(math.floor(num * 0.5)) + ( 0 if num % 2 == 1 else - 1 )
    start = mid - length_from_mid
    end = start + num - 1

    if num <= 0:
      return result


    while self.length :
      if counter >= start and counter <= end:
        result += character
      else:
        result += ' '
      counter += 1
      self.length -= 1

    return result

def threes_and_fives(start = 100, end = 4000000):
  sum = 0
  for i in range(start, end + 1):
    if (not i % 3) ^ (not i % 5):
      sum += i
  return sum

def generate_coin_change (number):
  coins = []

  while number :

    if number >= 100:
      number -= 100
      coins.append('dollar')
    elif number >=50:
      number -=50
      coins.append('half-dollar')
    elif number >= 25:
      number -= 25
      coins.append('quarter')
    elif number >= 10:
      number -= 10
      coins.append('dime')
    elif number >= 5:
      number -= 5
      coins.append('nickel')
    elif number >=1:
      number -= 1
      coins.append('penny')
  return coins

def messyMath(num):
  sum = 0
  for i in range (0, num +1 ):
    if  not i % 3:
      pass
    elif not i % 7:
      sum += 2 * i
    elif num/3 is num:
      return -1
    else:
      sum += i
  return sum

def twelve_bar_blues():
  for i in range(0, 12):
    print(str(i) + 'chick' + 'boom' + 'chick')

def fibonacci(number):
  reg = [0, 1]
  result = 0

  if number < 0:
    return None

  if number < 2:
    return number

  for i in range(1, number + 1 ):
    result = reg[1]
    reg[0], reg[1] = reg[1], reg[0]
    reg [1] = reg[0] + reg[1]

  return result

def sum_to_one_digit(number):
  while number > 9:
    tmp = number
    number = 0
    while tmp >= 1:
      number += tmp % 10
      tmp = math.floor(tmp / 10)
  return number

def clock_hand_angles(seconds):
  s = seconds % 60
  m = (seconds / 60) % 60
  h = (seconds / 3600) % 12
  print(s, m, h)
  # 60 second == 6 degrees (i.e. minute hand)
  # 60 min  == 30 degree (i.e.  hour hand)

  extra_m_angle = (s / 60.0) * 6
  extra_h_angle =  (m / 60.0) * 30

  s_hand = ((s / 60.0) * 360.0)
  m_hand = ((m / 60.0) * 360.0) + extra_m_angle
  h_hand = ((h / 12.0) * 360.0) + extra_h_angle

  return {'second_hand': s_hand, 'minute_hand': m_hand, 'hour_hand': h_hand }

def is_prime (number):
  for i in range (2, int(math.sqrt(number + 1)) + 1):
    if not number % i:
      return False
  return True

def rockin_dojo_sweatshirt(num):
  amount = 20
  num  = num if num < 4 else 3

  if num < 0:
    return None

  return {
    0: amount,
    1: amount * 0.9,
    2: amount * 0.19,
    3: amount * 0.35,
  }[num]

def extract_o_matic (num, digitNum):
  for i in range(0, digitNum):
    num  /=  10
  return num % 10

def most_sig_digit(number):
  result = 0
  while number:
    result = number % 10
    number /= 10
  return result

class Gaming_Fundamentals():
  def __init__(self):
    pass
  def rollOne(self):
    return (math.floor(random.random() * 6)) + 1
  def playFives(self, number):
    for i in range(0, number):
      data = int(self.rollOne())
      print(data)
      if data is 5:
        print 'good luck!'
  def playStatistics(self):
    hi = None
    low = None

    for i in range(0, 8):
      data = self.rollOne()
      if hi is None or data > hi:
        hi = data
      if low is None or data < low:
        low = data
    return {'low': low, 'hi': hi}

  def playStatistics2(self):
    hi = None
    low = None
    acc = 0
    for i in range(0, 8):
      data = self.rollOne()
      if hi is None or data > hi:
        hi = data
      if low is None or data < low:
        low = data
      acc += data
    return {'low': low, 'hi': hi, 'acc': acc}

  def playStatistics3(self, number):
    hi = None
    low = None
    acc = 0
    for i in range(0, number):
      data = self.rollOne()
      if hi is None or data > hi:
        hi = data
      if low is None or data < low:
        low = data
      acc += data
    return {'low': low, 'hi': hi, 'acc': acc}

  def playStatistics4(self, number):
    hi = None
    low = None
    acc = 0
    avg = 0

    if number <= 0:
      return None

    for i in range(0, number):
      data = self.rollOne()
      if hi is None or data > hi:
        hi = data
      if low is None or data < low:
        low = data
      acc += data
    return {'low': low, 'hi': hi, 'acc': acc, 'avg': acc / number }

def stat_until_double():
  min = None
  max = None
  prev = 0
  sum = 0
  count = 0
  current_role = 0

  while 1:

    current_role = int ((random.random() * 20) + 1 )

    if current_role is prev:
      break

    prev = current_role

    if min is None or current_role < min:
      min = current_role
    if max is None or current_role > max:
      max =  current_role

  sum += current_role
  count += 1
  return {'max': max, 'min': min, 'avg': sum/ count, 'count': count }

class Claire_Is_Where():
  def __init__(self):
    self.x = 0
    self.y = 0

  @property
  def reset(self):
    self.x = 0
    self.y = 0
    return self

  def moveBy(self, x_offset, y_offset):
    self.x += x_offset
    self.y += y_offset
    return self
  def xLocation(self):
    return self.x

  def yLocation(self):
    return self.y

  def current_location(self):
    return {'x': self.x, 'y': self.y}

  def distFromHome(self):
    x_offset = 0
    y_offset = 0
    x = 0
    y = 0
    steps = 0

    if self.x > 0 and self.y > 0:
      x_offset = 1
      y_offset = 1

    if self.x < 0 and self.y > 0:
      x_offset = -1
      y_offset = 1

    if self.x < 0 and self.y < 0:
      x_offset = -1
      y_pffset = -1

    if self.x > 0 and self.y < 0:
      x_offset = 1
      y_offset = -1

    while x is not self.x or   y is not self.y:
      if x is self.x or y is self.y:
        if x is not self.x:
          steps+= abs(x - self.x)
        if y is not self.y:
          steps+= abs(y- self.y)
        break
      else:
        x += x_offset
        y += y_offset
        steps += 1
    return str(steps) + ' units'

class Date_On_Deserted_Island():

  def __init__(self):
    self.year = 2016
    self.months = { 1: 31, 2: 29, 3: 31, 4: 30, 5: 31, 6: 30, 7: 31,8: 31, 9: 30, 10: 31,  11: 30, 12: 31 }
    self.month_code =  ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'June', 'July', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec']
    self.days = ['Monday', 'Tuesday', 'Wednesday', 'Thurday', 'Friday', 'Saturday', 'Sunday']
    self.day_index = 5
    self.month_index = 12
    self.day = 31

  def weekday_name(self, number):
    if number < 0 or number > 7:
      return None
    index = (self.day_index + 1) % 7
    return self.days[index]

  def weekday_name2(self, number):

    day = self.day
    day_sel = self.day_index
    month = self.month_index
    year = self.year

    if number < 0 or number > 365:
      return None

    while number :

      # ending leap year || end of year

      if month is 12 and day is 31:
        if year == 2016:
          self.months[2] = 28
        year += 1
        month = 1
        day = 0

      # last day of month

      elif day is self.months[month]:
        month += 1
        day = 0

      day += 1
      day_sel = (day_sel + 1) % 7
      number -= 1

    return  {'month': month, 'days_name': self.days[day_sel], 'day': day, 'year':  year}

  def some_days(self):
    for i in range(0, 17):
      data = self.weekday_name2(int(random.random()*365 + 1 ))
      print(data)
      if data['days_name'] in ['Saturday', 'Sunday']:
        print('Enjoy your days off')

  def month_name(self, num):
    return self.month_code[num - 1]

  def month_to_days(self, num):
    return self.months[num - 1]

  def full_data(self, num):
    data = self.weekday_name2(num);
    if data:
      i = data['month']
      print( data['days_name'] + ' ' +  self.month_name(i)  + ' ' + str(data['day']) + ' ' + str (data['year']) )
    return None

  def full_data_2 (self, number, cb = None ):

    day = self.day
    day_sel = self.day_index
    month = self.month_index
    year = self.year

    if number < 0 :
      return None

    while number :
      if month is 12 and day is 31:
        if cb((year + 1)) if cb else (year + 1) % 4 == 0:
          self.months[2] = 29
        if cb(year) if cb else not year % 4 :
          self.months[2] = 28
        year += 1
        month = 1
        day = 0
      elif day is self.months[month]:
        month += 1
        day = 0
      day += 1
      day_sel = (day_sel + 1) % 7
      number -= 1

    return  {'month': month, 'days_name': self.days[day_sel], 'day': day, 'year':  year}


  def full_data_3 (self, number):
    data =  self.full_data_2(number, is_leap_year)
    if data:
      i = data['month']
      return   '' +  data['days_name'] + ' ' +  self.month_name(i)  + ' ' + str(data['day']) + ' ' + str (data['year'])
    return None

def is_leap_year (year):
  if not year % 400:
    return True
  if not year % 100:
    return False
  if not year % 4:
    return True
  return False

#Test function/method
island = Date_On_Deserted_Island()
print(island.full_data_3( 139947))
