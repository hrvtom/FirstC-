//============================================================================
// Name        : cpp_first.cpp
// Author      : me
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <string.h> //Without this is OK but std::string used instead

using namespace std;

const int MAX = 3;

// print characters starting from provided index
void printString(char *c, int i) {
	std::cout << (c + i) << endl;
}

//print single character at provided index
void printCharacter(char* c, int i) {
	cout << *(c + i) << endl;
	cout << c[i] << endl; // a i ovo radi !!!!(zasto??)
}

class Temp {
private:
	string name;
	int value;

	// ovdje se zali da je copy constructor private
//	Temp(const Temp &other) {
//		cout << "Temp copy constructing: " << endl;
//	}

public:
	int value2;

	Temp() {
		cout << "Temp constructing:" << endl;
	}

	Temp(string name) {
		cout << "Temp constructing with name:" << endl;
		this->name = name;

	}

	Temp(string name, int value) :
			name(name), value(value) {
		cout << "Temp constructing with name and value:" << endl;
		// initialization of name and value is done before
		// constructor body is executed
		cout << "name in constructor: " << this->name << endl;
		cout << "value in constructor: " << this->value << endl;
		cout << "value2 in constructor: " << this->value2 << endl;
	}

	~Temp() {
		cout << "Temp destructing: " << this << endl;
	}

	void setName(string name) {
		this->name = name;
	}

	string getName() {
		return name;
	}

	int getValue() {
		return value;
	}

	Temp(const Temp &other) {
		cout << "Temp copy constructing: " << endl;
	}

	Temp& operator=(const Temp &other) {
		cout << "Temp = operator: " << endl;
		cout << "this: " << this << endl;
		cout << "other: " << &other << endl;
		this->name = other.name;
		return *this;
	}

	void operator()(const char* str) {
		cout << "Temp () operator: " << endl;
		cout << "New name is: " << str << endl;
//		str.copy(name,str.length());
		name = str; //kako kopirati string
//		strcpy(name.c_str(), str);
	}

	//overloading () operator
	void operator()(int num) {
		cout << "Overloading () operator" << endl;
	}
};

Temp createTemp() {
	Temp temp;
	temp.setName("localTemp");
	cout << "Local: Temp address " << &temp << endl;
	cout << "Local: Temp name " << temp.getName() << endl;
	//creates temp, but when sending result, copy constructor is invoked
	//and temp is transfered by value
	return temp;
	//If temp is returned as a pointer(*temp), the temp object will be destroyed at the
	//end of this method, and the caller will end up wit the poniter to object that
	//doesn't exist any more. this causes Segmentation fault.
	//solution is to create temp object with help of new Temp(), this object is stored in heap memory
	//and must be destroyed manually.
}

struct DemoStruct {
	int someInt;
	double someDouble;
	//struct Constructor, da i ovo postoji
	DemoStruct(int i = 0, double d = 0) :
			someInt(i), someDouble(d) { // ovo nisu constructori, ovo je function call operator (operator())
	}
};

class Box {
public:
	double length = 0.0;
	double breadth = 0.0;
	double height = 0.0;
	int index;
	static int count;

	double getVoume(void) {
		return length * breadth * height;
	}

	void printBox() {
		cout << "length:" << length << " breath:" << breadth << " height:"
				<< breadth << endl;
	}

	void setLength(double len);
	void setBreadth(double bre);
	void setHeight(double hei);

	Box() { //empty constructor
		count++;
		index = count;
		cout << "Box " << index << " is being created" << endl;
	}
	Box(double len, double bre, double hei);
	/*
	 Box(double len, double bre, double hei) {
	 length = len;
	 breadth		cout << ">>> Box" << count << " is being created <<<" << endl;
	 = bre;
	 height = hei;
	 cout << ">>> Box with parameters is being created <<<" << endl;
	 }
	 */
	Box(Box&);
	~Box(); // destructor, cannot take any parameters

};

int Box::count = 0;

void Box::setLength(double len) {
	cout << "Length" << endl;
	length = len;
}

void Box::setBreadth(double bre) {
	cout << "Breadth" << endl;
	breadth = bre;
}

void Box::setHeight(double hei) {
	cout << "Height" << endl;
	height = hei;
}

Box::Box(double len, double bre, double hei) :
		length(len), breadth(bre) {
	cout << "length:" << length << " breath:" << breadth << " height:"
			<< breadth << endl;
	count++;
	index = count;
	cout << "Box " << index << " is being created" << endl;
	length = len;
	breadth = bre;
	height = hei;
}

Box::Box(Box& box) {
	count++;
	index = count;
	cout << "Box copy constructor, Box " << index << " created" << endl;
}

Box::~Box() {
	cout << "Box " << index << " is being deleted, reference:" << this << endl;
}

Box functionBoxNoRef(Box box) {
	cout << "functionBoxNORef returning" << endl;
	return box;
}

Box* functionBoxRef(Box* pBox) {
	cout << "functionBoxNORef returning" << endl;
	return pBox;
}

class Line {
public:
	int getLengt(void);
	Line(int); //simple constructor
	Line(const Line &obj); //copy constructor
//	Line(Line const &obj); //this is OK too
	~Line(); //destructor

private:
	int *ptr;
};

Line::Line(int len) {
	cout << "Normal constructor allocating ptr" << endl;
	ptr = new int; //allocate memory for the pointer
	*ptr = len;
}

Line::Line(const Line &obj) {
	cout << "Line Copy constructor" << endl;
	ptr = new int; //alocate memory for the pointer
	*ptr = *obj.ptr; // make copy of the value
}

Line::~Line() {
	cout << "Line destructor, Free memory" << endl;
	delete ptr;
}

int Line::getLengt() {
	return *ptr;
}

void checkLine(Line line) { //transfer by value, this should use copy constructor
	cout << "Line reference " << &line << endl;
	cout << "Length of the line " << line.getLengt() << endl;

}
void checkLineRef(Line &line) { //transfer by reference, no copy constructor
	cout << "Line reference " << &line << endl;
	cout << "Length of the line " << line.getLengt() << endl;

}

void displayLine(Line &obj) { //this does not initiate copy constructor
	cout << "Address of Line obj " << &obj << endl;
	cout << "Length of the line " << obj.getLengt() << endl;
}
/*
 void display(Line obj) {  //This initiates copy constructor
 cout << "Length of the line" << obj.getLengt() << endl;
 }
 */

class Shape {
protected:
	int width;
	int height;
public:
	Shape() {
		cout << "Shape() consturctor" << endl;
		width = 10;
		height = 10;
	}
	Shape(int a, int b) {
		cout << "Shape(int,int) consturctor" << endl;
		width = a;
		height = b;
	}
	~Shape() {
		cout << "Shape() desturctor" << endl;
	}
	void setWidth(int w) {
		width = w;
	}
	void setHeight(int h) {
		height = h;
	}

	virtual int area() { // this is like abstract method
		cout << "Parent class area :" << endl;
		return 0;
	}
};

class PaintCost {
public:
	int getCost(int area) {
		return area * 70;
	}
};

//Multiple inheritance
class Rectangle: public Shape, public PaintCost {
public:
	Rectangle(int a = 0, int b = 0) :
			Shape(a, b) {
		cout << "Rectangle(int,int) consturctor" << endl;
	}
	~Rectangle() {
		cout << "Rectangle() desturctor" << endl;
	}
	int getArea() {
		return (width * height);
	}

	int area() {
		cout << "Rectangle class area :" << endl;
		return getArea();
	}
};

class Triangle: public Shape {
public:
	Triangle(int a, int b) :
			Shape(a, b) {
		cout << "Triangle(int,int) consturctor" << endl;
	}

	Triangle(int a) :
			Shape() {
		cout << "Triangle(int) consturctor" << endl;
		setWidth(a);
		setHeight(a);
	}
	~Triangle() {
		cout << "Triangle() desturctor" << endl;
	}
	int area() {
		cout << "Triangle class area :" << endl;
		return (width + height) / 2;
	}
};

class Exam1 {
public:
	void funct1() {
		cout
				<< "This function is possible to execute on non-constant objects only"
				<< endl;
	}

	void funct2() const {
		cout
				<< "This function is possible to execute on constant objects only\n this method is executed on const object"
				<< endl;
	}

	void funct2() {
		cout
				<< "This is possible too, same function with and without 'const' keyword\n this method is executed on non-const object"
				<< endl;
	}

};

void message()           // Global function ::message()
{
	std::cout << "Within Global function ::message()\n";
}

namespace A {
using namespace std;
// Names of std are visible here
void message()       // Function A::message()
{
	cout << "Within function A::message()\n";
}
}

namespace B {
using std::cout;
// Declaring cout of std.
void message(void);   // Function B::message()
}
void B::message(void)    // Defining B::message()
		{
	cout << "Within function B::message()\n";
}

bool inputFromCommandLine(string& name, long& number) {
	cout << "INput client data!" << endl << "Name: ";
	if (!getline(cin, name))
		return false;
	cout << "Number: ";
	if (!(cin >> number))
		return false;
	return true;
}
int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	bool execute = false;
	bool hello = execute;
	bool pointersVsArrays = execute;
	bool stringHandling = execute;
	bool structConstructor = execute;
	bool constructor = execute;
	bool referencesAndPointers = execute;
	bool classesAndObjects = execute;
	bool objectsCopyConstructor = execute;
	bool objectsConstructionDestructing = true;
	bool operatorOverloading = execute;
	bool initializationLists = execute;
	bool inheritance = execute;
	bool polymorphism = true;
	bool constClassesconstPointersAndMemberFunctions = execute;
	bool transferByValueByReference = execute;
	bool namespaces = execute;
	bool commandLineInput = execute;

	stringstream version;
	version << "Version string " << __VERSION__;
	cout << version.str() << endl;

	if (hello) {
		cout << endl << ">>> Console input test <<<" << endl;
		cout << "Enter your name: " << flush;
		string input;
		cin >> input;
		cout << " Hello " << input << endl;
	}

	if (pointersVsArrays) {
		cout << endl << ">>> Pointers vs Arrays <<<" << endl;
		int var[MAX] = { 10, 100, 200 };
		int *ptrArray;

		ptrArray = var;
		for (int i = 0; i < MAX; i++) {
			cout << "Address of var[" << i << "] " << ptrArray << endl;

			// This is possible too (when not in function or??)
			// A pointer that points to the beginning of an array can access that array
			// by using either pointer arithmetic or array-style indexing.
			cout << "Value of var[" << i << "] " << ptrArray[i] << endl;
			/*
			 cout << "Value of var[" << i << "] " << *ptrArray << endl;
			 ptrArray++;
			 */
		}

		ptrArray = &var[MAX - 1];
		int i = MAX - 1;
		while (ptrArray >= var) {
			cout << "Address of var[" << i << "] " << ptrArray << endl;
			cout << "Value of var[" << i << "] " << *ptrArray << endl;
			ptrArray--;
			i--;
		}

		for (int i = 0; i < MAX; i++) {
			cout << "Value of var[" << i << "] " << *(var + i) << endl;
			//this is not possible, var is a constant that points
			//to the beginning of an array and can not be used as l-value
			//var++;

		}
	}

	if (stringHandling) {
		cout << endl << "!!!String Handling!!!" << endl;
		char c[] = "Some stupid string";
		int num[] = { 1, 2, 3, 5, 7 };

		cout << c << endl;
		cout << (c + 5) << endl;
		cout << (c + 12) << endl;

		printString(c, 0);
		printString(c, 5);
		printString(c, 12);

		printCharacter(c, 0);
		printCharacter(c, 5);
		printCharacter(c, 13);

		cout << num << endl;
		cout << *num << endl;
		cout << *(num + 1) << endl;
	}

	if (structConstructor) {
		cout << endl << "!!!Struct Constructor!!!" << endl;
		struct DemoStruct demoStruct1;
		struct DemoStruct demoStruct2(11, 12.3);
		struct DemoStruct demoStruct3(13.4); // firt argument is still integer
		cout << "DemoStruct1 int: " << demoStruct1.someInt << endl;
		cout << "DemoStruct1 double: " << demoStruct1.someDouble << endl;
		cout << "DemoStruct2 int: " << demoStruct2.someInt << endl;
		cout << "DemoStruct2 double: " << demoStruct2.someDouble << endl;
		cout << "DemoStruct3 int: " << demoStruct3.someInt << endl;
		cout << "DemoStruct3 double: " << demoStruct3.someDouble << endl;
	}

	if (referencesAndPointers) {
		cout << endl << ">>> References and pointers<<<" << endl;
		//You cannot have NULL reference
		//Once a reference is initialized to an object, it cannot be changed to refer
		//to another object. Pointers can be pointed to another object at any time.
		//A reference must be initialized when it is created. Pointers can be
		//initialized at any time
		int a;
		double b;
		int& ra = a;
		double& rb = b;
		int *pa;

		a = 5;
		cout << "Value a " << a << endl;
		cout << "Value  ra " << ra << endl;
		cout << "Pointer pa " << *pa << endl;
		pa = &a;
		cout << "Pointer pa " << *pa << endl;

		cout << "Address a " << &a << endl;
		cout << "Address ra " << &ra << endl;
		cout << "Address pa " << &pa << endl;
		cout << "Value pa " << pa << endl;

		ra = 11;
		cout << "Value a " << a << endl;
		cout << "Reference  ra " << ra << endl;
		cout << "Pointer pa " << *pa << endl;

		b = 11.7;
		cout << "Value b " << b << endl;
		cout << "Reference  rb " << rb << endl;
	}

	if (classesAndObjects) {
		cout << endl << ">>> Classes & Objects <<<" << endl;
		Box box1;
		Box box2;
		Box box3(10.0, 11.0, 9.0);
		double volume = 0.0;

		box1.setLength(6.0);
		box1.setBreadth(7.0);
		box1.setHeight(5.0);

		box2.setLength(12.0);
		box2.setBreadth(13.0);
		box2.setHeight(10.0);

		cout << "Volume of Box1 is " << box1.getVoume() << endl;
		cout << "Volume of Box2 is " << box2.getVoume() << endl;
		cout << "Volume of Box3 is " << box3.getVoume() << endl;
	}

	if (objectsCopyConstructor) {
		cout << endl << ">>> Classes & Objects - Copy constructor <<<" << endl;
		Line line1(10);
		Line line2 = line1;	//this also calls copy constructor

		displayLine(line1);
		displayLine(line2);
	}

	if (objectsConstructionDestructing) {
		cout << endl << "!!!Class constructing/destructing!!!" << endl;
		cout << ">> new Temp" << endl;
		//ovdje se u "istom" trenutku temp i deklarira i incijalizira,
		//na djelu je optimizacija i nema niti copy construktora niti = operatora
		Temp temp = createTemp();
		temp.setName("mainTemp");
		cout << ">> main temp address " << &temp << endl;
		cout << ">> main temp name " << temp.getName() << endl;
		cout << ">> function createTemp()" << endl;
		// u ovom slucaju aktivira se = operator
		// a ne transfer by value iz createTemp()
		temp = createTemp();
		cout << ">> Created Temp name " << temp.getName() << endl;
		cout << ">> Created Temp address " << &temp << endl;
//		temp = new Temp(); // temp bi trebao biti pointer Temp*
//		cout << ">> New Temp name " << temp.getName() << endl;
//		cout << ">> New Temp address " << &temp << endl;

		Rectangle rec(20, 18);
		Triangle tri(14);
		rec.area(); //this is virtual function
		tri.area(); //this is virtual function
	}

	if (operatorOverloading) {
		cout << endl << "!!!Operator overloading!!!" << endl;
		cout << ">> create new Temp" << endl;
		//ovdje se u "istom" trenutku temp i deklarira i incijalizira,
		//na djelu je optimizacija i nema niti copy construktora niti = operatora
		Temp temp = createTemp();
		//ovdje je na djelu  string konstruktor a ne () operator
		Temp temp2("temp's dva ime");
		temp.setName("mainTemp");
		cout << ">> main: temp address " << &temp << endl;
		cout << ">> main: temp name " << temp.getName() << endl;
		cout << ">> function createTemp()" << endl;
		// u ovom slucaju aktivira se = operator
		temp = createTemp();
		cout << ">> main: temp address " << &temp << endl;
		cout << ">> main: temp name " << temp.getName() << endl;
		// u ovom slucaju aktivira se () iliti functional operator
		temp("novo ime");
		cout << ">> main: temp address " << &temp << endl;
		cout << ">> main: temp name " << temp.getName() << endl;
		cout << ">> main: temp2 address " << &temp2 << endl;
		cout << ">> main: temp2 name " << temp2.getName() << endl;
		// overloadani () operator
		temp(32);

	}

	if (initializationLists) {
		cout << endl << "!!!Using intialization lists to initialize fields!!!"
				<< endl;
		cout << ">> create new Temp with initialization list" << endl;
		Temp temp("ime", 21);
		cout << ">> temp.name after construction " << temp.getName() << endl;
		cout << ">> temp.value after construction " << temp.getValue() << endl;
	}

	if (inheritance) {
		cout << endl << ">>> Inheritance - Multiple inheritance <<<" << endl;
		Rectangle rect;
		Rectangle *ptrRec = &rect;
		Rectangle &rect1 = *ptrRec;
		rect.setWidth(5);
		rect.setHeight(7);

		int area = rect.getArea();

		cout << "Total area: " << rect.getArea() << endl;
		cout << "Total paint cost: " << rect.getCost(area) << endl;
	}

	if (polymorphism) {
		cout << endl << ">>> Polymorphism <<<" << endl;
		Shape *shape;
		Rectangle rectangle(10, 7);
		Triangle triangle(10, 5);

		shape = &rectangle;
		shape->area(); //this is virtual method

		shape = &triangle;
		shape->area(); //this is virtual method

		rectangle.area();
	}

	if (constClassesconstPointersAndMemberFunctions) {
		cout << endl
				<< ">>> Const classes , pointers to const classes and member functions <<<"
				<< endl;

		Exam1 nonConstClass;
		const Exam1 constClass;

		nonConstClass.funct1();
		nonConstClass.funct2();
		//constClass.funct1();//it is not possible to execute non-const method on const object
		constClass.funct2();
	}

	if (transferByValueByReference) {
		cout << endl << ">>> Transfer by value and transfer by reference <<<"
				<< endl;
		Line line3(11);
		Line line4(12);
		cout << "display line with reference ....." << endl;
		displayLine(line3);
		cout << "display line with reference ....." << endl;
		displayLine(line4);
		cout << "check line without reference ...." << endl;
		checkLine(line3);
		cout << "check line with reference ...." << endl;
		checkLineRef(line3);
		cout << " end of function ...." << endl;

		cout << endl << "Making a Box" << endl;
		Box box;
		cout << " Calling functionBoxNoRef ...." << endl;
		functionBoxNoRef(box);
		cout << " Calling functionBoxRef ...." << endl;
		functionBoxRef(&box);
		cout << ">>> End of transfer by Reference <<<" << endl;
	}

	if (constructor) {
		cout << endl << ">>> Constructor: initial values <<<" << endl;
		Box box(3.0, 4.0, 8.0);
		box.printBox();
	}

	if (namespaces) {
		cout << endl << ">>> Namespaces:  <<<" << endl;
		using B::message;
		// Function name without braces!
		A::message();
		message();           // ::message() is hidden because
							 // of the using-declaration.
		::message();         // Global function

	}

	if (commandLineInput) {
		cout << endl << ">>> Input form command line:  <<<" << endl;
		string name;
		long number;
		if (inputFromCommandLine(name, number)) {
			cout << "Name is: " << name << endl;
			cout << "Number is: " << number << endl;
		} else {
			cout << "Some input was wrong";
		}

	}

	cout << endl << "exiting main" << endl;
	return 0;

}
