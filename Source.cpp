/*
A student’s cumulative grade point average (CGPA) can be determined using the C++ program CGPA Calculator.
The user’s input is used to compute the CGPA, which includes information like the number of courses taken and the grades earned in each one.
The program also shows each student’s overall course grade. CGPA Calculator calculates a student’s Cumulative Grade Point Average (CGPA) from the given exam results
. The program can show the individual grades of each course, calculate total credits and total grade points achieved, determine the GPA for the semester,
and based on all the data, it can generate and present the CGPA of the student.

Technologies Required: C++ programming language, Data Structures, Basic Searching & Sorting algorithms,
Basic Arithmetic Operations and formulas, and File Handling ( I/O Streams ).
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;


//to store major variables 
struct course {
	string name;
	string semester;
	int credits = (0);// 1-4
	int year = (0);
	double grades = (0); //4.0 etc
};
// 
class courseManagement {
public:
	double calculateGpa(const vector<course>& courses);
	double calculateCgpa(const vector<course>& allCourses);
	void courseGrade()const;
	void userInput();
	const vector<course>& getAllCourses() const { return allCourses; }// used to access private member
private:
	vector<course> allCourses;
	vector<string> semesters;//stores semesters
	vector<double> semesterGpa;//stores gpa for each ^^
};
// function declaration

// calculates gpa for 1 class & used for reference not to make copy
// use {} in place of () for initializing values
double courseManagement::calculateGpa(const vector<course>& courses) {
	
	int totalCredit = { 0 };
	double totalGrade = { 0.0 };

	for (const auto& course : courses) {
		//multiply points(0-4) by credits(1-5) and add up then divide by total credits 
		totalGrade += course.grades * course.credits;
		totalCredit += course.credits;
	}//used to find gpa 

	if (totalCredit == 0) {
		return 0.0;// to avoid math error
	}
	
	double gpa = totalGrade / totalCredit;
	semesterGpa.push_back(gpa);
	//will display gpa as ex:3.42
	cout << "Gpa: " << fixed << setprecision(2) << gpa << endl;

	return gpa;
}
//store and shoe grade
void courseManagement::courseGrade()const {
	
	for (const auto& course : allCourses)
	{

			cout << "*************************************************************************" << endl;
			cout << " semester:" << course.semester << endl;
			cout << " year:" << course.year << endl; 
			cout << " course:" << course.name << endl;
			cout << " credits:" << course.credits << endl;
			cout << " Grade:" << fixed << setprecision(2) << course.grades << endl;
			cout << "*************************************************************************" << endl;
	}
}
//calculates gpa for all classes  cgpa needs to calculate for all semesters as well
double courseManagement::calculateCgpa(const vector<course>& allCourses) {
	int totalCredits = { 0 };
	double totalGradePoints = { 0.0 };
	for (const auto& course : allCourses) {
				totalGradePoints += course.grades * course.credits;
		totalCredits += course.credits;
	}

	if (totalCredits == 0) {
		return 0.0; 
	}
	double cgpa = totalGradePoints / totalCredits;
	cout << "CGPA: " << fixed << setprecision(2)
		<< cgpa << endl;
	return cgpa;
	
}
void courseManagement::userInput() {
	string choice = "yes";
	while (choice == "yes") {
		//creates object newCourse
		course newCourse;

		cout << "Enter Semester:" << endl;
		cin >> newCourse.semester;

		cout << "Enter Year:" << endl;
		cin >> newCourse.year;

		cout << "Enter course Name:" << endl;
		cin.ignore();
		getline(cin, newCourse.name);

		cout << "Enter the # of Credits:" << endl;
		cin >> newCourse.credits;
		//

	for (const auto& semester : semesters) {
		// Find the first course in this semester to determine the year
		for (const auto& course : courses) {
			if (course.semester == semester) {
				calculateGpa(semester, course.year);
				break;  // Stop after calculating GPA for this semester-year pair
			}
		}
	}
}
		
		cin >> newCourse.grades;

		//add to the vector
		allCourses.push_back(newCourse);
	
		cout << "do you want to enter more courses? (yes/no)" << endl;
			cin >> choice;
			cin.ignore();

	}

	
}
int main() {
	//vector<course> courses; //= {
		//{"Math", 5, 0},
		//{"Science", 4, 3.5},
		//{"History", 2, 3.7}
	//};
	courseManagement cm;
	cm.userInput();
	cm.courseGrade();
	//getter method
	const vector<course>& courses = cm.getAllCourses();

	for (const auto& course : courses) {
		cm.calculateGpa({ course });
	}
	//double gpa = cm.calculateGpa(courses);
	double cgpa = cm.calculateCgpa(courses);
	
	return 0;
}