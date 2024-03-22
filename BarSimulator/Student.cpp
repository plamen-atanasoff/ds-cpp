#include "Student.h"

#include <sstream>

#include "bar-simulator.h"

int Student::LAST_MINUTE_ARRIVED = 0;

Student::Bachelor Student::getBachelorEnum(const std::string& str) const
{
	if (str == "Fraud") {
		return Student::Bachelor::Fraud;
	}
	else if (str == "International Schemes") {
		return Student::Bachelor::InternationalSchemes;
	}
	else if (str == "Creative Nihilism") {
		return Student::Bachelor::CreativeNihilism;

	}
	else if (str == "Subjective Researches") {
		return Student::Bachelor::SubjectiveResearches;

	}
	else if (str == "File Analizis") {
		return Student::Bachelor::FileAnalizis;

	}
	else if (str == "Micromanagement") {
		return Student::Bachelor::Micromanagement;

	}
	else if (str == "Applied Materialization") {
		return Student::Bachelor::AppliedMaterialization;

	}
	else if (str == "Subjectivistics") {
		return Student::Bachelor::Subjectivistics;

	}
	else if (str == "Magnetism and Clearing") {
		return Student::Bachelor::MagnetismAndClearing;

	}
	else {
		throw  incorrect_simulation("incorrect bachelor");
	}
}

void Student::verifyData(int fn, int minuteArrived, int minutesStaying) const {
	if (fn < 0 || fn > 999'999'999) {
		throw incorrect_simulation("fn is incorrect");
	}

	if (minuteArrived < 0 || minuteArrived < LAST_MINUTE_ARRIVED) {
		throw incorrect_simulation("minuteArrived is incorrect");
	}

	if (minutesStaying < 0) {
		throw incorrect_simulation("minutesStaying is incorrect");
	}
}

Student::Student(const std::string& line)
{
	std::istringstream iss(line);
	int firstInt, secondInt, lastInt;
	std::string text;

	iss >> firstInt;
	iss >> secondInt;
	iss >> text;
	while (!(iss >> lastInt)) {
		iss.clear();
		std::string temp;
		iss >> temp;
		text += " " + temp;
	}

	verifyData(firstInt, secondInt, lastInt);

	fn = firstInt;
	minuteArrived = secondInt;
	bachelor = getBachelorEnum(text);
	minutesStaying = lastInt;

	LAST_MINUTE_ARRIVED = minuteArrived;
}

void Student::setMinuteEntered(int minEntered) {
	minuteEntered = minEntered;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
	os << "fn: " << student.getFN() << " minArr: " << student.getMinuteArrived()
		<< " bach : " << getBachelorString(student.getBachelor()) << " minSt: " << student.getMinutesStaying();
	return os;
}
