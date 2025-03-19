#include <cstdio>
enum Node { RED, BLACK};
struct Color {
	enum ColorEnum { RED, GREEN, DEFAULT };
	static void setColor(ColorEnum color){		
		static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
		std::puts(pallete[color]);
	}
};



template <class T>
double drawBig(T& shape){
	double a0 = shape.area();
	shape.scale(2);
	double a1 = shape.area();
	return a1 - a0;
}

class Scaleable {
public:
	virtual ~Scaleable() { }	
	virtual void scale(double f = 2.0) = 0;
};

class Shape : public Scaleable {
public:
	Shape() : m_id(++NumOfShapes) {
		std::printf("Shape::CTOR - %d\n", m_id); 
	}	

	~Shape() {
		draw();
		std::printf("Shape::DTOR - %d\n", m_id);
		--NumOfShapes; 
	}

	Shape(const Shape& other) : m_id(++NumOfShapes) {
		std::printf("Shape::CCTOR %d from - %d\n", m_id, other.m_id);
	}

	virtual void draw() const {
		std::printf("Shape::draw() - %d\n", m_id);		
	}
	
	virtual void draw(Color::ColorEnum c) const {
		Color::setColor(c);
		std::printf("Shape::draw(%d)\n", m_id);
		draw();
		Color::setColor(Color::DEFAULT);
	}
	
	virtual void scale(double) { }
	virtual double area() { return -1; }
	static void printInventory() {
		std::printf("Shape::printInventory - %d\n", NumOfShapes);
	}

private:
	Shape& operator=(const Shape &); // disabled, no implementation provided

protected:
	 int m_id;
};

void test(Scaleable& s) {
	s.scale(2.4);,
}
int Shape::NumOfShapes = 0;


class Circle : public Shape {	
public:
	Circle() : m_radius(1) { 
		std::printf("Circle::CTOR() - %d, r:%f\n", m_id, m_radius); 
	}

	Circle(double r) : m_radius(r) { 
		std::printf("Circle::CTOR(double) - %d, r:%f\n", m_id, m_radius); 
	}

	Circle(const Circle& other)
	: Shape(other), m_radius(other.m_radius) { 
		std::printf("Circle::CCTOR - %d, r:%f\n", m_id, m_radius);
	}

	~Circle() { 
		std::printf("Circle::DTOR - %d, r:%f\n", m_id, m_radius); 
	}

	void draw() const { 
		std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
	}

	void scale(double f){
		m_radius *= f;
	}
    
	double area()  {
		return m_radius * m_radius * 3.1415;	
	}

	double radius() const { 
		std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
		return m_radius;
	}

private:
	double m_radius;
};

void f(int x= 3, int y = 5);

f();
f(9);
f(1, 2);

class Rectangle: public Shape {
public:
	Rectangle() : m_a(1), m_b(1) { 
		std::printf("Rectangle::CTOR - %d, a:%d/%d\n", m_id, m_a, m_b);
	}

	Rectangle(int a) : m_a(a), m_b(a) { 
		std::printf("Rectangle::CTOR - %d, a:%d/%d\n", m_id, m_a, m_b);
	}

	Rectangle(int a, int b) : m_a(a), m_b(b) { 
		std::printf("Rectangle::CTOR - %d, a:%d/%d\n", m_id, m_a, m_b);
	}
	
	Rectangle(const Rectangle &other ) : Shape(other),m_a(other.m_a), m_b(other.m_b) { 
		std::printf("Rectangle::CCTOR - %d, a:%d/%d\n", m_id, m_a, m_b);
	}
	
	~Rectangle() { 
		std::printf("Rectangle::DTOR - %d, a:%d/%d\n", m_id, m_a, m_b);
	}

	void draw() const { 
		std::printf("Rectangle::draw()  - %d, a:%d/%d\n", m_id, m_a, m_b);
	}

    void draw(Color::ColorEnum c) const {
		std::printf("Rectangle::draw(%d)  - %d, a:%d/%d\n", c, m_id, m_a, m_b);
	}

	void scale(double f){
		m_a *= f;
		m_b *= f;
	}

	double area(){
		return m_a * m_b;
	}

private:
	int m_a, m_b;
};

void report(const Shape& s) {
	std::puts("-----------");
	s.draw(); 
	Shape::printInventory();
}


inline void draw(Shape& obj) { 
	obj.scale(2);
	obj.draw();	
}


void draw(Circle c) { 
	static Circle unit(1);
	
	unit.draw();
	unit.scale(3);
	c.draw(); 
}

void doPointerArray(){
	Shape *array[] =  {
	    new Circle(),
	    new Rectangle(3),
	    new Circle(4)
	};

    for(int i = 0; i < 3; ++i) 
		array[i]->draw();

	std::printf("area: %f\n", drawBig(*array[2]));

    for(int i = 0; i < 3; ++i) { 
		delete array[i]; 
		array[i] = 0; 
	}
}

void doObjArray(){
	Shape objects[] = {
	    Circle(),
	    Rectangle(4),
	    Circle(9)
	};

    for(int i = 0; i < 3; ++i) 
		objects[i].draw();
}




int main(int argc, char **argv, char **envp)
{	
    Circle c;
	Rectangle s(4);
	
	draw(c);
	draw(c);

    draw(s);

	report(c);
	printf("*********\n");
	
	
    doPointerArray();
	printf("*********\n");

    doObjArray();
	printf("*********\n");


    Shape::printInventory();

    Circle c2(17);
    c2.printInventory();
    
    Circle olympics[5];
	drawBig(olympics[1]);

    Rectangle *fourRectangles = new Rectangle[4];
	drawBig(*fourRectangles);
    delete[] fourRectangles;

    return 0;
}

