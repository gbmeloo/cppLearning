#include <iostream>

int main()
{
   std::cout << "Hello world!";
   int width { 5 };    // define variable width and initialize with initial value 5
   std::cout << width; // prints 5

   int a ( 10 );         // default-initialization (no initializer)

   // Traditional initialization forms:
   int b = 5;     // copy-initialization (initial value after equals sign)
   int c ( 6 );   // direct-initialization (initial value in parenthesis)

   // Modern initialization forms (preferred):
   int d { 7 };   // direct-list-initialization (initial value in braces)
   int e {};      // value-initialization (empty braces)


   std::cout << a;
   std::cout << b;
   std::cout << c;
   std::cout << d;
   std::cout << "Last variable declaration " << e << std::endl;

   // String declaration example
   std::string myString("This is my string");

   std::cout << myString << std::endl;
   std::cout << "The length of my string is: " << myString.length() << std::endl;
	
   // Demonstrating dynamic string resizing
   myString += " and it automatic resizes :)";
   std::cout << myString << std::endl;
   std::cout << "String length after resizing: " << myString.length() << std::endl;

   return 0;
}
