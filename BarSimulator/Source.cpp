#include <iostream>
#include <sstream>

#include "bar-simulator.h"

int main()
{
    // example
    //std::stringstream empty{
    //"3 2 10\n"
    //"220 0 Fraud 10\n"
    //"221 1 Fraud 9\n"
    //"222 2 Fraud 8\n"
    //"320 2 Subjectivistics 10\n"
    //"410 2 Micromanagement 10\n"
    //"321 3 Subjectivistics 5\n"
    //"411 3 Micromanagement 10\n"
    //"322 4 Subjectivistics 10\n"
    //"323 4 Subjectivistics 10\n"
    //"510 5 International Schemes 3\n" };
    //const std::string expected =
    //    "0 220 enter\n"
    //    "1 221 enter\n"
    //    "2 222 enter\n"
    //    "10 220 exit\n"
    //    "10 221 exit\n"
    //    "10 222 exit\n"
    //    "10 320 enter\n"
    //    "10 321 enter\n"
    //    "10 510 enter\n"
    //    "13 510 exit\n"
    //    "15 321 exit\n"
    //    "15 410 enter\n"
    //    "15 411 enter\n"
    //    "20 320 exit\n"
    //    "25 410 exit\n"
    //    "25 411 exit\n"
    //    "25 322 enter\n"
    //    "25 323 enter\n"
    //    "35 322 exit\n"
    //    "35 323 exit\n";

    //std::stringstream output;

	// Try to simulate the student bar system
	try {
		simulate_bar(std::cin, std::cout);
	}
	catch (const incorrect_simulation& e) {
		std::cout << "Some of the simulation states are wrong or invalid: " << e.what() << "\n";
		return 1;
	}
	catch (const std::exception& e) {
		std::cout << "Failed to simulate the student bad: " << e.what() << "\n";
		return 2;
	}

    //std::cout << output.str();
}