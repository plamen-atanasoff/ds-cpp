#include "Bar.h"

void Bar::removeStudents(std::ostream& output) {
	List<Student>::iterator it = students.begin();
	int minLeavingFirstStudent = (*it).getMinuteEntered() + (*it).getMinutesStaying();

	while (students.isValid(it)) {
		Student& currStudent = *it;
		int minLeaving = currStudent.getMinuteEntered() + currStudent.getMinutesStaying();

		if (minLeaving == minLeavingFirstStudent) {
			output << minLeavingFirstStudent << ' ' << currStudent.getFN() << " exit\n";

			it = students.pop_front();
			currCapacity++;
		}
		else {
			break;
		}
	}

	currMinute = minLeavingFirstStudent;
}

void Bar::checkStudentsEnthusiasm(std::ostream& output) {
	for (List<Student>::iterator it = students.begin(); students.isValid(it); ++it) {
		Student& currStudent = *it;
		int minLeaving = currStudent.getMinuteEntered() + currStudent.getMinutesStaying();

		if (currMinute >= minLeaving) {
			output << minLeaving << ' ' << currStudent.getFN() << " exit\n";

			it = students.pop_front();
			currCapacity++;

			currMinute = minLeaving;
		}
	}
}

void Bar::addStudentsFromGroup(Group& group, std::ostream& output) {
	List<Student>& students = group.getStudents();
	for (List<Student>::iterator it = students.begin(); students.isValid(it); ++it) {
		Student& currStudent = *it;

		currStudent.setMinuteEntered(currMinute);

		addStudent(currStudent);
		currCapacity--;

		output << currMinute << ' ' << currStudent.getFN() << " enter\n";
	}
}

void Bar::addStudent(Student& student) {
	int minLeaving = student.getMinuteEntered() + student.getMinutesStaying();

	List<Student>::iterator prev = students.begin();
	for (List<Student>::iterator it = students.begin(); students.isValid(it); ++it) {
		int currMinLeaving = (*it).getMinuteEntered() + (*it).getMinutesStaying();

		if (minLeaving < currMinLeaving) {
			if (it == students.begin()) {
				students.push_front(student);
				return;
			}
			else {
				students.insert(prev, student);
				return;
			}
		}

		prev = it;
	}

	students.push_back(student);
}

void Bar::checkStudentsInBar(std::ostream& output, bool noMoreStudentsComing) {
	if (students.empty()) {
		return;
	}

	if (noMoreStudentsComing) {
		removeStudents(output);
	}
	else {
		checkStudentsEnthusiasm(output);
	}
}

void Bar::addGroups(List<Group>& groups, std::ostream& output) {
	List<Group>::iterator prev = groups.begin();
	for (List<Group>::iterator it = groups.begin(); groups.isValid(it);) {
		Group& currGroup = *it;

		if (currGroup.getSize() <= currCapacity) {
			addStudentsFromGroup(currGroup, output);

			if (it == groups.begin()) {
				it = groups.pop_front();
			}
			else {
				it = groups.eraseNext(prev);
			}
		}
		else {
			prev = it;
			++it;
		}
	}
}

void Bar::empty(std::ostream& output) {
	for (List<Student>::iterator it = students.begin(); students.isValid(it); ++it) {
		Student& currStudent = *it;
		int minLeaving = currMinute + currStudent.getMinutesStaying();

		output << minLeaving << ' ' << currStudent.getFN() << " exit\n";
	}
}

void Bar::setCurrentMinute(int currMin) {
	currMinute = currMin;
}
