abstract class shape {
  abstract double getArea();
}

class circle extends shape {
  double radius;

  circle(double r) {
    this.radius = r;
  }

  double getArea() {
    return 3.14 * radius * radius;
  }
}

class triangle extends shape {
  double base, height;

  triangle(double b, double h) {
    this.base = b;
    this.height = h;
  }

  double getArea() {
    return 0.5 * base * height;
  }
}

class rectangle extends shape {
  double length, breadth;

  rectangle(double l, double b) {
    this.length = l;
    this.breadth = b;
  }

  double getArea() {
    return length * breadth;
  }
}

class square extends rectangle {
  square(double s) {
    super(s, s);
  }
}

public class AbstractClass {
  public static void main(String[] args) {
    circle c = new circle(5);
    triangle t = new triangle(10, 20);
    rectangle r = new rectangle(10, 20);
    square s = new square(10);
    System.out.println("Area of circle is " + c.getArea());
    System.out.println("Area of triangle is " + t.getArea());
    System.out.println("Area of rectangle is " + r.getArea());
    System.out.println("Area of square is " + s.getArea());
  }
}
