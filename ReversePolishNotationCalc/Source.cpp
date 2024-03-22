#include <iostream>
#include <fstream>
#include <sstream>

#include "expression.h"

int main()
{
	// example
	std::stringstream ops(
		"a * 23 R\n"
		"b /  5 R\n"
		"c * 26 R\n"
		"d - 36 L\n"
		"e / 27 R\n"
		"f + 40 R\n"
		"g - 27 R\n"
		"h /  4 R\n"
		"i + 27 R\n"
		"j / 21 R\n"
		"k - 30 L\n"
		"l /  7 R\n"
		"m / 14 L\n"
		"n *  5 R\n"
		"o -  1 L\n"
		"p *  6 R\n"
		"q * 23 L\n"
		"r * 21 L\n"
		"s + 27 L\n"
		"t * 35 R\n"
		"u *  2 R\n"
		"v * 33 L\n"
		"w - 13 R\n"
		"x * 26 L\n"
		"y / 40 R\n"
		"z + 10 L"
	);
	const char* expression = "-3599 e ( -4453 u 4245 k 1308 d ( -3023 l -4060 ) j -792 i ( 2059 g ( 3075 b 4170 u ( 236 v 1381 z -353 o 4961 j ( 166 h ( -4394 ) x ( 1306 c ( -1952 v -746 z 2735 n ( 644 ) m ( -3965 i ( -231 s -3861 x ( -1424 a -3623 k 765 a ( 589 z ( -1575 f ( -4292 g 2176 h ( -2333 e -4596 ) l 4061 ) d ( -972 r ( -4484 p 3774 a 4052 c -3722 u 1241 j ( -2279 p ( 394 h 4245 u 1603 ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) )";
	double res = -65.6993606761429;

	// Try to evaluate the expression
	try {
		double result = evaluate(expression, ops);
		std::cout << "Calculated value is " << result << "\n";
	}
	catch (incorrect_expression& e) {
		std::cout << "The provided expression is incorrect: " << e.what() << "\n";
		return 3;
	}
	catch (std::exception& e) {
		std::cout << "Cannot evaluate expression: " << e.what() << "\n";
		return 4;
	}
}