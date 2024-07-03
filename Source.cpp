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
#include <algorithm>
#include <limits>//for sorting
#include <fstream>
#include <set>

using namespace std;


//to store major variables 
struct Course {
	string name;
	string semester;
	int credits = 0;// 1-4
	int year = 0;
	double grades = 0.0; //4.0 etc
};
// 
class courseManagement {
public:
	double calculateGpa(const string& semester, int year);
	double calculateCgpa()const;
	void displayCourseGrade()const;
	void userInput();
	void displayGpaBySemesterAndYear();//chat gpt function
	void storeFileData(const double& cgpa);

	//retrieves private class memebers could also just be put into public
	const vector<Course>& getAllCourses() const { return allCourses; }

	// used to access private member
private:
	vector<Course> allCourses;
	//not needed just use allcourses




};
// function declaration

// calculates gpa for 1 class & used for reference not to make copy
// use {} in place of () for initializing values
//create error handling for user input
void courseManagement::userInput() {
	string choice = "yes";
	while (choice == "yes") {
		//creates object newCourse
		Course newCourse;

		cout << "Enter Semester:" << endl;
		cin >> newCourse.semester;

		cout << "Enter Year:" << endl;
		while (!(cin >> newCourse.year) || newCourse.year < 1900 || newCourse.year > 2100) {
			cout << " invalid year 1900-2100 only " << endl;
			cin.clear();//clears error
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		cout << "Enter course Name:" << endl;
		cin.ignore();
		getline(cin, newCourse.name);//grabs the entire line of code incase of space

		cout << "Enter the # of Credits:" << endl;
		while (!(cin >> newCourse.credits) || newCourse.credits <= 0 || newCourse.credits > 10) {
			cout << "Invalid number of credits. Please enter a valid number of credits (1-10):" << endl;
			cin.clear(); // Clear error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
		}
		//

		cout << "Enter grade(0.0-4.0):" << endl;
		while (!(cin >> newCourse.grades) || newCourse.grades < 0.0 || newCourse.grades > 4.0) {
			cout << "Invalid grade. Please enter a valid grade (0.0-4.0):" << endl;
			cin.clear(); // Clear error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
		}


		//add to the vector
		allCourses.push_back(newCourse);


		cout << "do you want to enter more courses? (yes/no)" << endl;
		while (!(cin >> choice) || choice != "yes" && choice != "no") {
			cout << "invalid option choose yes or no " << endl;
			cin.clear();
			cin.ignore(); (numeric_limits<streamsize>::max(), '\n');
		}
		

	}


}


double courseManagement::calculateGpa(const string& semester, int year) {
	
	int totalCredit = { 0 };
	double totalGrade = { 0.0 };

	for (const auto& course : allCourses) {
		if (course.semester==semester && course.year == year){
			//multiply points(0-4) by credits(1-5) and add up then divide by total credits 
			totalGrade += course.grades * course.credits;
			totalCredit += course.credits; 
		}
	}//used to find gpa 

	if (totalCredit == 0) {
		return 0.0;// to avoid math error
	}
	
	double gpa = totalGrade / totalCredit;

	return gpa;
}

//calculates gpa for all classes  cgpa needs to calculate for all semesters as well
double courseManagement::calculateCgpa()const {
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
	cout << "CGPA: " << fixed << setprecision(2) << cgpa << endl;
	
	return cgpa;

}
//store and show grade
void courseManagement::displayCourseGrade()const {
	
	for (const auto& course : allCourses)
	{

			cout << "*************************************************************************" << endl;
			cout << left << setw(12) << " Semester:" << course.semester << endl;
			cout << left << setw(12) << " Year:" << course.year << endl;
			cout << left << setw(12) << " Course:" << course.name << endl;
			cout << left << setw(12) << " Credits:" << course.credits << endl;
			cout << left << setw(12) << " Grade:" << fixed << setprecision(2) << course.grades << endl;
			cout << "*************************************************************************" << endl;
	}
}
//label parameters as const since they are not being changed 
void courseManagement::storeFileData(const double& cgpa ) {
	
	ofstream outFile;
	outFile.open("course_Data.txt");

	if (!outFile) {
		cout << "file could not open" << endl;
			return ;
	}

	for (const auto& course : allCourses)
	{

		outFile << "*************************************************************************" << endl;
		outFile << left << setw(12) << " Semester:" << course.semester << endl;
		outFile << left << setw(12) << " Year:" << course.year << endl;
		outFile << left << setw(12) << " Course:" << course.name << endl;
		outFile << left << setw(12) << " Credits:" << course.credits << endl;
		outFile << left << setw(12) << " Grade:" << fixed << setprecision(2) << course.grades << endl;
		outFile << "*************************************************************************" << endl;
		
		
		
	}
	// Collect unique semester-year combinations
	set<pair<string, int>> semesterYearCombinations;
	for (const auto& course : allCourses) {
		semesterYearCombinations.insert(make_pair(course.semester, course.year));
	}

	// Iterate over unique combinations and calculate/display GPA
	for (const auto& semYear : semesterYearCombinations) {
		double gpa = calculateGpa(semYear.first, semYear.second);
		outFile << "GPA for: " << semYear.first << "(" << semYear.second << "): "
			<< fixed << setprecision(2) << left << setw(6) << gpa << endl;
	}
	
	/*
	//fix the one below still get repeat code during output of file
	for (const auto& course : allCourses) {
		
		double gpa = calculateGpa(course.semester, course.year);//calls calculategpa function
		//output code
		outFile << "Gpa for: " << course.semester << "(" << course.year << "): "
			<< fixed << setprecision(2) << left << setw(6) << gpa << endl;

	}
	*/
	outFile << "CGPA: " << fixed << setprecision(2) << cgpa << endl;

	outFile.close();
}
void courseManagement::displayGpaBySemesterAndYear() {//cgpt function
	const vector<Course>& courses = getAllCourses();

	// Collect unique semester-year combinations
	set<pair<string, int>> semesterYearCombinations;
	for (const auto& course : courses) {
		semesterYearCombinations.insert(make_pair(course.semester, course.year));
	}

	// Iterate over unique combinations and calculate/display GPA
	for (const auto& semYear : semesterYearCombinations) {
		double gpa = calculateGpa(semYear.first, semYear.second);
		cout << "GPA for: " << semYear.first << "(" << semYear.second << "): "
			<< fixed << setprecision(2) << left << setw(6) << gpa << endl;
	}
}


int main() {


	courseManagement cm;

	cm.userInput();
	
	cm.displayCourseGrade();

	cm.displayGpaBySemesterAndYear();

	//getter method
	const vector<Course>& courses = cm.getAllCourses();
	//const vector<string>& semesters = cm.getSemesters();

	
		for (const auto& course : cm.getAllCourses()) {
		
				cm.calculateGpa(course.semester, course.year);
				break;//stops from repeating gpa for semesters
			}

		
	
	//double gpa = cm.calculateGpa(courses);
	double cgpa = cm.calculateCgpa();

	cm.storeFileData(cgpa);//chat gpt used to call storefile data 
	}