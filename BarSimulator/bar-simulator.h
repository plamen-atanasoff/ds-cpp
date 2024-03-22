#pragma once

#include <exception>
#include <iostream>
#include <string>

#include "Student.h"
#include "Group.h"
#include "List.hpp"

// An exception that is thrown by simulate_bar when it detects an invalid state or data
class incorrect_simulation : public std::runtime_error {
public:
    incorrect_simulation(const std::string& what_arg)
        : runtime_error(what_arg)
    {
        // Nothing to do here        
    }
};

void simulate_bar(std::istream& input, std::ostream& output);

void initStudents(std::istream& input, List<Student>& students, int studentsCount);

void addStudentToGroup(const Student& student, List<Group>& groups, int barCapacity);
const Group* addStudentToNewGroup(const Student& student, List<Group>& groups);
const Group* addStudentToGroup(const Student& student, List<Group>& groups);

const char* getBachelorString(Student::Bachelor bachelor);
