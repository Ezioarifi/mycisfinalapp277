// ProjectOfOPP2.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
//#include <conio.h>
#include <string>
#include <iomanip>


using namespace std;

//*****************		PUBLIC VARIABLES		*****************//

string output = "----------------------------------------------"
				"---------------------------------------------\n"
				"\n\t\t\t\t\tResults\n"
				"\n---------------------------------------------"
				"----------------------------------------------\n\n";
float sum = 0;
float passedStudents = 0;
float failedStudents = 0;
float maxVal = 0; // For Determing the max grade
float minVal = 1000; // For Determing the min Grade
string bestStudent;
string worstStudent;

//*****************		CLASSES		*****************//

class Student {
protected:
	string m_name;
	static int m_matricNo;
	static int i; // Count Students in an Array

public:
	static int countStudents();
	virtual void Display(int index);
};

int Student::m_matricNo = 16000;
int Student::i = 0;
int counter = Student::countStudents(); // To Return The Count Of The Students In Array

class Grade {
protected:
	float m_midTermExam, m_finalExam, total;
	string m_status;

public:
	virtual void Display(int index);
};

class Result : public Student, Grade {
public:
	Result() {}

	Result(string name, float midTermExam, float finalExam);

	~Result() {}

	string getName();

	string getStatus();

	friend void maxGrade(Result s);
	friend void minGrade(Result s);
	friend void sumOfResults(Result s);
	static void bestAndWorst();
	static void passedAndFailed();
	static void avg();
	void Display(int index);

};





//*****************		FUNCTIONS		*****************//

// Student Class Functions

int Student::countStudents() { return i; }

void Student::Display(int index) {
	cout << setw(8) << m_matricNo + (index + 1)
		<< setw(18) << m_name;

	cout << "\n" << endl;
}

// Grade Class Functions

void Grade::Display(int index) {

	cout << setw(12) << m_midTermExam
		<< setw(18) << m_finalExam
		<< setw(15) << total
		<< setw(15) << m_status;

	cout << "\n" << endl;
}


// Result Class Functions

Result::Result(string name, float midTermExam, float finalExam) {
	m_name = name;
	m_midTermExam = midTermExam;
	m_finalExam = finalExam;
	total = m_midTermExam + m_finalExam;
	getStatus();
	i++; // increament student by 1 in every instantiaion
}

string Result::getName() { return m_name; }

string Result::getStatus() {
	if (total > 50) {
		m_status = "Pass";
		passedStudents++;
	}
	else {
		m_status = "Fail";
		failedStudents++;
	}

	return m_status;
}


void  maxGrade(Result s) {
	if (s.total > maxVal) {
		maxVal = s.total;
		bestStudent = s.getName();
	}
}

void  minGrade(Result s) {
	if (s.total < minVal) {
		minVal = s.total;
		worstStudent = s.getName();
	}
}

void sumOfResults(Result s) {
	sum += s.total;
}

void Result::bestAndWorst() {
	cout << "------------------------------------------------------------------\n"
		<< "\n\tBest Result For:\t\t" << bestStudent << "\t" << maxVal
		<< "\n\tWorst Result For:\t\t" << worstStudent << "\t" << minVal
		<< "\n\n------------------------------------------------------------------\n\n";
}

void Result::passedAndFailed() {
	cout << "------------------------------------------------------------------\n"
		<< "\nNumber of Students Who Already Passed is:\t" << passedStudents
		<< "\t%" << ((passedStudents / countStudents()) * 100)

		<< "\nNumber of Students Who Already Failed is:\t" << failedStudents
		<< "\t%" << ((failedStudents / countStudents()) * 100)
		<< "\n\n------------------------------------------------------------------\n\n";
}

void Result::avg() {
	cout << "----------------------------------------------------------\n"
		<< "\n\tThe Average Result is: \t\t" << sum / countStudents()
		<< "\n\n----------------------------------------------------------\n\n";
}

void Result::Display(int index) {
	cout << setw(8) << m_matricNo + (index + 1)
		<< setw(18) << m_name
		<< setw(12) << m_midTermExam
		<< setw(18) << m_finalExam
		<< setw(15) << total
		<< setw(15) << m_status;

	cout << "\n" << endl;
}


//*****************		MAIN METHOD		*****************//

int main()
{
	Result *students[100];

	cout << "----------------------------------------------\n"
		<< "\n\t\t\tWELCOME TO MY OOP PROJECT\n\n"
		"----------------------------------------------\n\n";
	char choice; // For determining if the user inputs a letter or a digit

	do {

		cout << "\n\nPress the Number To Select Your Choice:\n\n"
			<< "[1] Adding New Student Info and His Grades\n"
			<< "[2] Printing Course's Result\n"
			<< "[3] Display Max and Min Grades\n"
			<< "[4] Number Of Passed & Failed Students Find Percentage\n"
			<< "[5] General Average of Results\n"
			<< "[6] Finish\n\n"
			<< "  >> ";

		cin >> choice;

		while (isalpha(choice))
		{
			cout << "Error, You must enter a digit.\n  >> ";
			cin >> choice;
		}


		switch (choice) {
		case '1': {
			//char b;
			string name = "";
			float midTermExam = 0, finalExam = 0;

			cout << "\nStudent (" << ( counter + 1 ) << ")\n\n";

			// input the Student's data
			cout << "\tFirstName (Press Y if you need to return):\t";
			cin >> name;

			if (name.length() == 1 && ( name[0] == 'y' || name[0] == 'Y') )
			{
				break;
			}

			do {

				cout << "\tMidTerm Exam Grade ( From 40 ):\t\t";
				cin >> midTermExam;

			} while (midTermExam < 0 || midTermExam > 40);

			do {

				cout << "\tFinal Exam Grade ( From 60 ):\t\t";
				cin >> finalExam;


			} while (finalExam < 0 || finalExam > 60);

			students[counter] = new Result(name, midTermExam, finalExam);

			sumOfResults(*students[counter]);  // This Line Makes a Destructor Call
			maxGrade(*students[counter]);	  //  This Line Makes a Destructor Call
			minGrade(*students[counter]);    //   This Line Makes a Destructor Call

			counter++;
			cout << "\n\n----------------------------------------------------------\n\n";

		}break;

		case '2': {
			if (counter == 0)
			{
				cout << "\n\nYou didn't add any student to display the results\n\n";
			}
			else
			{

				cout << output;
				cout << setw(10) << "MatricNo"
					<< setw(15) << "Name"
					<< setw(15) << "Grade1"
					<< setw(20) << "Grade2"
					<< setw(13) << "Total"
					<< setw(13) << "Status";

				cout << '\n' << endl;

				for (int i = 0; i < counter; i++) {
					students[i]->Display(i);
				}

				cout << "----------------------------------------------"
				"---------------------------------------------\n"
				"\n\tTotal Number of Students\t(" << counter << ")\n"
				"\n---------------------------------------------"
				"----------------------------------------------\n\n";
			}
		}break;

		case '3': {
			if (counter == 0)
			{
				cout << "\n\nYou didn't add any student to display Max & Min Grades\n\n";
			}
			else if (counter == 1)
			{
				cout << "\n\nComparison can't be made, There's only one student";
			}
			else
			{
				Result::bestAndWorst();
			}
		}break;

		case '4': {

			if (counter == 0)
			{
				cout << "\n\nYou didn't add any student to display The Percentage of Passed & Failed Students\n\n";
			}

			else
			{
				Result::passedAndFailed();
			}

		}break;

		case '5': {
			if (counter == 0)
			{
				cout << "\n\nYou didn't add any student to display Max & Min Grades\n\n";
			}
			else
			{
				Result::avg();
			}

		}break;

		case '6': break;
		default: cout << "\n\nError, You have to choose the option you need from the list below\n\n";

		}
	} while (choice !=  '6');



	cout << "Created By: Motaz Alarefi";
	if (counter != 0)
	{
		delete *students;
	}
	//getch();
	return 0;
}


