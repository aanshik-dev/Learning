class Rectange:
  def __init__(self, length, breadth):
    self.length = length
    self.breadth = breadth

  def area(self):
    return self.length * self.breadth
  
  def ifSquare(self):
    return self.length == self.breadth
  
class BankAccount:
  def __init__(self, accountNumber, balance):
    self.accountNumber = accountNumber
    self.balance = balance

  def deposit(self, amount):
    self.balance += amount

  def withdraw(self, amount):
    self.balance -= amount

class Vector2d:
  def __init__(self, x, y):
    self.x = x
    self.y = y

  def __add__(self, other):
    return Vector2d(self.x + other.x, self.y + other.y)

  def __sub__(self, other):
    return Vector2d(self.x - other.x, self.y - other.y)
  
def squared(list):
  return [x*x for x in list]

ls = [1,3,5,2,6]
cube = list(map(lambda x: x*x*x, ls))
print(cube)

divby3 = list(filter(lambda x: x%3 == 0, ls))
print(divby3)

def square(x):
  return x*x
def parent(fun, ls):
  return list(map(fun, ls))

print(parent(square, ls))