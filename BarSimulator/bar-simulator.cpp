#include "bar-simulator.h"

#include <string>
#include <cassert>

#include "Student.h"
#include "List.hpp"
#include "Group.h"
#include "Bar.h"

namespace BachelorStringConstants {
	const char* FRAUD = "Fraud";
	const char* INTERNATIONAL_SCHEMES = "InternationalSchemes";
	const char* CREATIVE_NIHILISM = "CreativeNihilism";
	const char* SUBJECTIVE_RESEARCHES = "SubjectiveResearches";
	const char* FILE_ANALIZIS = "FileAnalizis";
	const char* MICROMANAGEMENT = "Micromanagement";
	const char* APPLIED_MATERIALIZATION = "AppliedMaterialization";
	const char* SUBJESTIVISTICS = "Subjectivistics";
	const char* MAGNETISM_AND_CLEARING = "MagnetismAndClearing";
}

///
/// @brief Simulate the student bar problem
///
/// @param input
///   The stream, which contains the simulation commands
/// @param output
///   The stream, where the steps of simulation have to be printed.
///
void simulate_bar(std::istream& input, std::ostream& output) {
	int barCapacity, groupCapacity, studentsCount;
	input >> barCapacity >> groupCapacity >> studentsCount;
	input.ignore();

	if (studentsCount == 0) {
		return;
	}

	if (barCapacity == 0) {
		throw incorrect_simulation("bar capacity is 0");
	}

	assert(groupCapacity > 0);
	Group::MAX_SIZE = groupCapacity;

	List<Student> students;
	initStudents(input, students, studentsCount);

	List<Group> groups;

	Bar bar(barCapacity);
	for (List<Student>::iterator it = students.begin(); students.isValid(it); ++it) {
		Student& currStudent = *it;
		bar.setCurrentMinute(currStudent.getMinuteArrived());

		addStudentToGroup(currStudent, groups, barCapacity);

		bar.checkStudentsInBar(output, false);

		if (bar.getCurrentCapacity() > 0) {
			bar.addGroups(groups, output);
		}
	}

	while (!groups.empty()) {
		bar.checkStudentsInBar(output, true);

		if (bar.getCurrentCapacity() > 0) {
			bar.addGroups(groups, output);
		}
	}

	bar.empty(output);
}

void initStudents(std::istream& input, List<Student>& students, int studentsCount) {
	std::string buffer;
	for (int i = 0; i < studentsCount; i++) {
		getline(input, buffer);
		Student student(buffer);

		students.push_back(student);
	}
}

void addStudentToGroup(const Student& student, List<Group>& groups, int barCapacity) {
	const Group* group = nullptr;

	if (groups.empty()) {
		group = addStudentToNewGroup(student, groups);
	}
	else {
		group = addStudentToGroup(student, groups);
	}

	if (group->getSize() > barCapacity) {
		throw incorrect_simulation("group with more students than bar capacity");
	}
}

const Group* addStudentToNewGroup(const Student& student, List<Group>& groups) {
	Group group(student.getBachelor());
	groups.push_back(group);

	groups.back().add(student);

	return &groups.back();
}

const Group* addStudentToGroup(const Student& student, List<Group>& groups) {
	for (List<Group>::iterator it = groups.begin(); groups.isValid(it); ++it) {
		Group& currGroup = *it;

		if (student.getBachelor() == currGroup.getBachelor() && currGroup.getSize() < currGroup.MAX_SIZE) {
			currGroup.add(student);

			return &currGroup;
		}
	}

	return addStudentToNewGroup(student, groups);
}

const char* getBachelorString(Student::Bachelor bachelor) {
	switch (bachelor) {
	case Student::Bachelor::Fraud: return BachelorStringConstants::FRAUD;
	case Student::Bachelor::InternationalSchemes: return BachelorStringConstants::INTERNATIONAL_SCHEMES;
	case Student::Bachelor::CreativeNihilism: return BachelorStringConstants::CREATIVE_NIHILISM;
	case Student::Bachelor::SubjectiveResearches: return BachelorStringConstants::SUBJECTIVE_RESEARCHES;
	case Student::Bachelor::FileAnalizis: return BachelorStringConstants::FILE_ANALIZIS;
	case Student::Bachelor::Micromanagement: return BachelorStringConstants::MICROMANAGEMENT;
	case Student::Bachelor::AppliedMaterialization: return BachelorStringConstants::APPLIED_MATERIALIZATION;
	case Student::Bachelor::Subjectivistics: return BachelorStringConstants::SUBJESTIVISTICS;
	case Student::Bachelor::MagnetismAndClearing: return BachelorStringConstants::MAGNETISM_AND_CLEARING;
	default: throw incorrect_simulation("no such bachelor exists");
	}
}
