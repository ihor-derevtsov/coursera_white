#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct Specialization {
	explicit Specialization(string new_value) {
		data = new_value;
	} 
	string data;
};

struct Course {
	explicit Course(string new_value) {
		data = new_value;
	} 
	string data;
};

struct Week {
	explicit Week(string new_value) {
		data = new_value;
	} 
	string data;
};

struct LectureTitle {
	LectureTitle(Specialization new_specialization, Course new_course, Week new_week) {
		specialization = new_specialization.data;
		course = new_course.data;
		week = new_week.data;
	}
	string specialization;
	string course;
	string week;
};

