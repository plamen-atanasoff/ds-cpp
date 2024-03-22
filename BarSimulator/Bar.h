#pragma once

#include <iostream>

#include "List.hpp"
#include "Student.h"
#include "Group.h"

class Bar {
private:
	List<Student> students;
	const int maxCapacity;
	int currCapacity;
	int currMinute;

	void removeStudents(std::ostream& output);
	void checkStudentsEnthusiasm(std::ostream& output);

	void addStudentsFromGroup(Group& group, std::ostream& output);
	void addStudent(Student& student);
public:
	Bar(int maxCapacity) : maxCapacity(maxCapacity), currCapacity(maxCapacity), currMinute() {}

	void checkStudentsInBar(std::ostream& output, bool noMoreStudentsComing);
	void addGroups(List<Group>& groups, std::ostream& output);
	void empty(std::ostream& output);

	void setCurrentMinute(int currMin);

	int getCurrentCapacity() const { return currCapacity; }
};
