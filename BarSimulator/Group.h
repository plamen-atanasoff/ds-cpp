#pragma once

#include "Student.h"
#include "List.hpp"

class Group {
public:
	static int MAX_SIZE;
private:
	List<Student> students;
	Student::Bachelor bachelor;
	int size;
public:
	Group(Student::Bachelor bachelor) : students(), bachelor(bachelor), size() {}

	void add(const Student& student);

	Student::Bachelor getBachelor() const { return bachelor; }
	int getSize() const { return size; }
	List<Student>& getStudents() { return students; }

	void printStudents(std::ostream& os);
};

std::ostream& operator<<(std::ostream& os, Group& group);
