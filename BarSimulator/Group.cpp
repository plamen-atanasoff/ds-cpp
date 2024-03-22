#include "Group.h"

#include <cassert>

#include "bar-simulator.h"

int Group::MAX_SIZE;

void Group::add(const Student& student) {
	students.push_back(student);
	size++;
}

void Group::printStudents(std::ostream& os) {
	if (students.empty()) {
		os << "Group is empty!\n";
	}
	else {
		for (List<Student>::iterator it = students.begin(); students.isValid(it); ++it) {
			os << *it << '\n';
		}
	}
}

std::ostream& operator<<(std::ostream& os, Group& group) {
	os << "size: " << group.getSize() << " bachelor: " << getBachelorString(group.getBachelor()) << '\n';
	group.printStudents(os);
	return os;
}
