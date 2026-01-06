class Student:
  def __init__(self, name, roll):
    self.name = name
    self.roll = roll

  def display(self):
    print(self.name, self.roll)

s1 = Student("Aanshik", 37)
s1.display()

class Counter:
  def __init__(self):
    self.count = 0
  def increment(self):
    self.count += 1


class Vector2D:
  def __init__(self , x, y):
    self.x = x
    self.y = y
  def __add__(self , other):
    return Vector2D(self.x + other.x, self.y + other.y)
v1 = Vector2D(1, 2)
v2 = Vector2D(3, 4)
v3 = v1 + v2
print(v3.x, v3.y)

class Engine:
    def start(self):
        print("Engine started")

class Car: 
  def __init__(self):
    self.engine = Engine()

  def start(self):
    self.engine.start()

car = Car()
car.start()

def square(x):
  return x * x
f = square
print(f(5))

add = lambda a , b : a+b
print(add(5,6))

numbers = [1, 2, 3, 4, 5]
squares = list(map(lambda x: x * x, numbers))
evens = list(filter(lambda x: x % 2 == 0, numbers))
print(squares)
print(evens)

squares = [x*x for x in range(5)]
evens = [x for x in range(5) if x % 2 == 0]
print(squares)
print(evens)