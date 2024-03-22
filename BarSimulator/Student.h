#pragma once

#include <string>
#include <ostream>

class Student {
public:
	enum class Bachelor {
		Fraud,
		InternationalSchemes,
		CreativeNihilism,
		SubjectiveResearches,
		FileAnalizis,
		Micromanagement,
		AppliedMaterialization,
		Subjectivistics,
		MagnetismAndClearing
	};
private:
	static int LAST_MINUTE_ARRIVED;

	int fn; // non-negative integer with up to 9 digits
	int minuteArrived; // non-negative integer
	Bachelor bachelor;
	int minutesStaying; // positive integer

	int minuteEntered = -1;

	Bachelor getBachelorEnum(const std::string& str) const;
	void verifyData(int fn, int minuteArrived, int minutesStaying) const;
public:
	Student() = default;
	Student(const std::string& line);

	int getFN() const { return fn; }
	int getMinuteArrived() const { return minuteArrived; }
	Bachelor getBachelor() const { return bachelor; }
	int getMinutesStaying() const { return minutesStaying; }
	int getMinuteEntered() const { return minuteEntered; }

	void setMinuteEntered(int minEntered);
};

std::ostream& operator<<(std::ostream& os, const Student& student);
