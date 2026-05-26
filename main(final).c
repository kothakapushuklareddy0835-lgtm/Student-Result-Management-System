#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STUDENTS 100
#define SUBJECT_COUNT 5
#define TOTAL_CREDITS 15

// Subject credits array
const int subjectCredits[SUBJECT_COUNT] = {4, 3, 3, 3, 2};

// Subject names
const char* subjectNames[SUBJECT_COUNT] = {
    "Matrices and Calculus",
    "Engineering Chemistry",
    "Programming for Problem Solving",
    "Digital Electronics",
    "English"
};

// Structure to store grade information for a subject
typedef struct {
    int marks;
    char grade[3];
    int gradePoints;
    char result[10];
} SubjectResult;

// Student structure
typedef struct {
    char rollNo[20];
    char name[50];
    int marks[SUBJECT_COUNT];
    SubjectResult subjectResults[SUBJECT_COUNT];
    float percentage;
    float sgpa;
    char overallGrade[3];
    char overallResult[10];
} Student;

// Global variables
Student students[MAX_STUDENTS];
int studentCount = 0;

// Function declarations
void displayMenu();
void addStudent();
void editStudent();
void deleteStudent();
void searchStudent();
void displayAllStudents();
void displayRanking();
void displaySubjectAverages();
void checkAtRiskStudents();
void saveToFile();
void loadFromFile();
void calculateSubjectGrade(SubjectResult *result, int marks);
void calculateStudentResults(Student *student);
float calculateSGPA(Student *student);
void displayGradeCard(Student student);

// Main function
int main() {
    loadFromFile();
    
    printf("\n========================================\n");
    printf("  STUDENT RESULT MANAGEMENT SYSTEM\n");
    printf("  JNTUH AFFILIATED COLLEGE\n");
    printf("  CREDIT BASED GRADING SYSTEM\n");
    printf("========================================\n");
    
    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                editStudent();
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                displayAllStudents();
                break;
            case 6:
                displayRanking();
                break;
            case 7:
                displaySubjectAverages();
                break;
            case 8:
                checkAtRiskStudents();
                break;
            case 9:
                printf("\nSaving data and exiting...\n");
                saveToFile();
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please enter 1-9.\n");
        }
    } while(choice != 9);
    
    return 0;
}

void displayMenu() {
    printf("\n========== MAIN MENU ==========\n");
    printf("1. Add New Student\n");
    printf("2. Edit Student Details\n");
    printf("3. Delete Student\n");
    printf("4. Search Student\n");
    printf("5. View All Students\n");
    printf("6. View Rank List (SGPA based)\n");
    printf("7. Subject-wise Class Average\n");
    printf("8. Check At-Risk Students (AI)\n");
    printf("9. Exit\n");
    printf("================================\n");
}

// Calculate grade for a subject based on JNTUH rules
void calculateSubjectGrade(SubjectResult *result, int marks) {
    result->marks = marks;
    
    if(marks >= 90 && marks <= 100) {
        strcpy(result->grade, "O");
        result->gradePoints = 10;
        strcpy(result->result, "Pass");
    }
    else if(marks >= 80 && marks <= 89) {
        strcpy(result->grade, "A+");
        result->gradePoints = 9;
        strcpy(result->result, "Pass");
    }
    else if(marks >= 70 && marks <= 79) {
        strcpy(result->grade, "A");
        result->gradePoints = 8;
        strcpy(result->result, "Pass");
    }
    else if(marks >= 60 && marks <= 69) {
        strcpy(result->grade, "B+");
        result->gradePoints = 7;
        strcpy(result->result, "Pass");
    }
    else if(marks >= 50 && marks <= 59) {
        strcpy(result->grade, "B");
        result->gradePoints = 6;
        strcpy(result->result, "Pass");
    }
    else if(marks >= 40 && marks <= 49) {
        strcpy(result->grade, "C");
        result->gradePoints = 5;
        strcpy(result->result, "Pass");
    }
    else {
        strcpy(result->grade, "F");
        result->gradePoints = 0;
        strcpy(result->result, "Fail");
    }
}

// Calculate SGPA using JNTUH formula
float calculateSGPA(Student *student) {
    int totalGradePoints = 0;
    int totalCreditsEarned = 0;
    
    for(int i = 0; i < SUBJECT_COUNT; i++) {
        totalGradePoints += student->subjectResults[i].gradePoints * subjectCredits[i];
        if(student->subjectResults[i].gradePoints > 0) {
            totalCreditsEarned += subjectCredits[i];
        }
    }
    
    if(totalCreditsEarned == 0) return 0.0;
    return (float)totalGradePoints / totalCreditsEarned;
}

// Calculate all results for a student
void calculateStudentResults(Student *student) {
    int totalMarks = 0;
    int passedSubjects = 0;
    int failedSubjects = 0;
    
    for(int i = 0; i < SUBJECT_COUNT; i++) {
        calculateSubjectGrade(&student->subjectResults[i], student->marks[i]);
        totalMarks += student->marks[i];
        
        if(student->subjectResults[i].gradePoints > 0) {
            passedSubjects++;
        } else {
            failedSubjects++;
        }
    }
    
    student->percentage = (float)totalMarks / SUBJECT_COUNT;
    student->sgpa = calculateSGPA(student);
    
    if(failedSubjects == 0) {
        strcpy(student->overallResult, "PASS");
        
        if(student->sgpa >= 9.0) strcpy(student->overallGrade, "O");
        else if(student->sgpa >= 8.0) strcpy(student->overallGrade, "A+");
        else if(student->sgpa >= 7.0) strcpy(student->overallGrade, "A");
        else if(student->sgpa >= 6.0) strcpy(student->overallGrade, "B+");
        else if(student->sgpa >= 5.0) strcpy(student->overallGrade, "B");
        else if(student->sgpa >= 4.0) strcpy(student->overallGrade, "C");
        else strcpy(student->overallGrade, "F");
    } else {
        strcpy(student->overallResult, "FAIL");
        strcpy(student->overallGrade, "F");
    }
}

// Display grade card for a student (CLEAN VERSION - no special characters)
void displayGradeCard(Student student) {
    printf("\n");
    printf("+============================================================+\n");
    printf("|                 GRADE CARD - JNTUH STYLE                   |\n");
    printf("+============================================================+\n");
    printf("| Roll Number: %-43s |\n", student.rollNo);
    printf("| Student Name: %-42s |\n", student.name);
    printf("+------------------------------------------------------------+\n");
    printf("| SUBJECT                          | CREDITS | MARKS | GRADE |\n");
    printf("+------------------------------------------------------------+\n");
    
    for(int i = 0; i < SUBJECT_COUNT; i++) {
        printf("| %-32s | %5d | %5d | %-5s |\n", 
               subjectNames[i], 
               subjectCredits[i],
               student.marks[i], 
               student.subjectResults[i].grade);
    }
    
    printf("+------------------------------------------------------------+\n");
    printf("| TOTAL CREDITS                                 |         15 |\n");
    printf("| SGPA (Semester Grade Point Average)           | %10.2f |\n", student.sgpa);
    printf("| OVERALL GRADE                                 | %10s |\n", student.overallGrade);
    printf("| RESULT                                        | %10s |\n", student.overallResult);
    printf("+============================================================+\n");
}

void addStudent() {
    if(studentCount >= MAX_STUDENTS) {
        printf("Database full! Cannot add more students.\n");
        return;
    }
    
    Student newStudent;
    
    printf("\n--- Add New Student ---\n");
    printf("Enter Roll Number : ");
    scanf("%s", newStudent.rollNo);
    
    // Check for duplicate roll number
    for(int i = 0; i < studentCount; i++) {
        if(strcmp(students[i].rollNo, newStudent.rollNo) == 0) {
            printf("Error: Roll number %s already exists!\n", newStudent.rollNo);
            return;
        }
    }
    
    printf("Enter Name: ");
    scanf(" %[^\n]", newStudent.name);
    
    printf("\n--- Enter Marks (Out of 100) ---\n");
    printf("Subject 1 (Matrices and Calculus) [Credits: 4]: ");
    scanf("%d", &newStudent.marks[0]);
    printf("Subject 2 (Engineering Chemistry) [Credits: 3]: ");
    scanf("%d", &newStudent.marks[1]);
    printf("Subject 3 (Programming for Problem Solving) [Credits: 3]: ");
    scanf("%d", &newStudent.marks[2]);
    printf("Subject 4 (Digital Electronics) [Credits: 3]: ");
    scanf("%d", &newStudent.marks[3]);
    printf("Subject 5 (English) [Credits: 2]: ");
    scanf("%d", &newStudent.marks[4]);
    
    // Validate marks (0-100)
    for(int i = 0; i < SUBJECT_COUNT; i++) {
        if(newStudent.marks[i] < 0 || newStudent.marks[i] > 100) {
            printf("Error: Marks must be between 0 and 100!\n");
            return;
        }
    }
    
    calculateStudentResults(&newStudent);
    
    students[studentCount] = newStudent;
    studentCount++;
    
    printf("\n[SUCCESS] Student added successfully!\n");
    displayGradeCard(newStudent);
}

void editStudent() {
    char rollNo[20];
    int found = -1;
    
    printf("\n--- Edit Student ---\n");
    printf("Enter Roll Number to edit: ");
    scanf("%s", rollNo);
    
    for(int i = 0; i < studentCount; i++) {
        if(strcmp(students[i].rollNo, rollNo) == 0) {
            found = i;
            break;
        }
    }
    
    if(found == -1) {
        printf("Student with roll number %s not found!\n", rollNo);
        return;
    }
    
    printf("\nCurrent Details:\n");
    displayGradeCard(students[found]);
    
    printf("\nEnter new details:\n");
    printf("Enter Name: ");
    scanf(" %[^\n]", students[found].name);
    
    printf("\n--- Enter New Marks (Out of 100) ---\n");
    printf("Subject 1 (Matrices and Calculus) [Credits: 4]: ");
    scanf("%d", &students[found].marks[0]);
    printf("Subject 2 (Engineering Chemistry) [Credits: 3]: ");
    scanf("%d", &students[found].marks[1]);
    printf("Subject 3 (Programming for Problem Solving) [Credits: 3]: ");
    scanf("%d", &students[found].marks[2]);
    printf("Subject 4 (Digital Electronics) [Credits: 3]: ");
    scanf("%d", &students[found].marks[3]);
    printf("Subject 5 (English) [Credits: 2]: ");
    scanf("%d", &students[found].marks[4]);
    
    calculateStudentResults(&students[found]);
    
    printf("\n[SUCCESS] Student details updated successfully!\n");
    displayGradeCard(students[found]);
}

void deleteStudent() {
    char rollNo[20];
    int found = -1;
    
    printf("\n--- Delete Student ---\n");
    printf("Enter Roll Number to delete: ");
    scanf("%s", rollNo);
    
    for(int i = 0; i < studentCount; i++) {
        if(strcmp(students[i].rollNo, rollNo) == 0) {
            found = i;
            break;
        }
    }
    
    if(found == -1) {
        printf("Student with roll number %s not found!\n", rollNo);
        return;
    }
    
    printf("\nDeleting student: %s (%s)\n", students[found].name, students[found].rollNo);
    printf("Are you sure? (Y/N): ");
    char confirm;
    scanf(" %s", &confirm);
    
    if(confirm == 'y' || confirm == 'Y') {
        for(int i = found; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        printf("[SUCCESS] Student deleted successfully!\n");
    } else {
        printf("Deletion cancelled.\n");
    }
}

void searchStudent() {
    char rollNo[20];
    printf("\n--- Search Student ---\n");
    printf("Enter Roll Number: ");
    scanf("%s", rollNo);
    
    for(int i = 0; i < studentCount; i++) {
        if(strcmp(students[i].rollNo, rollNo) == 0) {
            displayGradeCard(students[i]);
            return;
        }
    }
    printf("Student with roll number %s not found!\n", rollNo);
}

void displayAllStudents() {
    if(studentCount == 0) {
        printf("\nNo students in database!\n");
        return;
    }
    
    printf("\n");
    printf("+====================+========================+==========+==========+==========+\n");
    printf("| ROLL NUMBER        | NAME                   | PERCENT  | SGPA     | GRADE    |\n");
    printf("+====================+========================+==========+==========+==========+\n");
    
    for(int i = 0; i < studentCount; i++) {
        printf("| %-18s | %-22s | %8.2f | %8.2f | %-8s |\n", 
               students[i].rollNo, 
               students[i].name, 
               students[i].percentage, 
               students[i].sgpa,
               students[i].overallGrade);
    }
    printf("+====================+========================+==========+==========+==========+\n");
}

void displayRanking() {
    if(studentCount == 0) {
        printf("\nNo students to rank!\n");
        return;
    }
    
    Student sorted[MAX_STUDENTS];
    for(int i = 0; i < studentCount; i++) {
        sorted[i] = students[i];
    }
    
    for(int i = 0; i < studentCount - 1; i++) {
        for(int j = 0; j < studentCount - i - 1; j++) {
            if(sorted[j].sgpa < sorted[j + 1].sgpa) {
                Student temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    
    printf("\n");
    printf("+======+====================+========================+==========+==========+\n");
    printf("| RANK | ROLL NUMBER        | NAME                   | SGPA     | GRADE    |\n");
    printf("+======+====================+========================+==========+==========+\n");
    
    for(int i = 0; i < studentCount; i++) {
        printf("| %4d | %-18s | %-22s | %8.2f | %-8s |\n", 
               i + 1,
               sorted[i].rollNo, 
               sorted[i].name, 
               sorted[i].sgpa,
               sorted[i].overallGrade);
    }
    printf("+======+====================+========================+==========+==========+\n");
}

void displaySubjectAverages() {
    if(studentCount == 0) {
        printf("\nNo students to calculate averages!\n");
        return;
    }
    
    float subjectAvg[SUBJECT_COUNT] = {0};
    int passCount[SUBJECT_COUNT] = {0};
    
    for(int i = 0; i < studentCount; i++) {
        for(int j = 0; j < SUBJECT_COUNT; j++) {
            subjectAvg[j] += students[i].marks[j];
            if(students[i].marks[j] >= 40) {
                passCount[j]++;
            }
        }
    }
    
    for(int j = 0; j < SUBJECT_COUNT; j++) {
        subjectAvg[j] /= studentCount;
    }
    
    printf("\n");
    printf("+================================================+==============+============+\n");
    printf("| SUBJECT                                        | CLASS AVG    | PASS %%     |\n");
    printf("+================================================+==============+============+\n");
    
    for(int j = 0; j < SUBJECT_COUNT; j++) {
        float passPercent = (float)passCount[j] / studentCount * 100;
        printf("| %-44s | %12.2f | %10.1f%% |\n", 
               subjectNames[j], subjectAvg[j], passPercent);
    }
    printf("+================================================+==============+============+\n");
}

void checkAtRiskStudents() {
    if(studentCount == 0) {
        printf("\nNo students to analyze!\n");
        return;
    }
    
    float classAvg[SUBJECT_COUNT] = {0};
    
    for(int i = 0; i < studentCount; i++) {
        for(int j = 0; j < SUBJECT_COUNT; j++) {
            classAvg[j] += students[i].marks[j];
        }
    }
    
    for(int j = 0; j < SUBJECT_COUNT; j++) {
        classAvg[j] /= studentCount;
    }
    
    printf("\n");
    printf("+============================================================================+\n");
    printf("|                 AT-RISK STUDENT DETECTOR (RULE-BASED AI)                  |\n");
    printf("+============================================================================+\n");
    printf("| Students scoring >15%% below class average in any subject:                  |\n");
    printf("+============================================================================+\n");
    
    int atRiskFound = 0;
    
    for(int i = 0; i < studentCount; i++) {
        int hasRisk = 0;
        int riskySubject = -1;
        float lowestMark = 101;
        
        for(int j = 0; j < SUBJECT_COUNT; j++) {
            float threshold = classAvg[j] * 0.85;
            
            if(students[i].marks[j] < threshold) {
                hasRisk = 1;
                if(students[i].marks[j] < lowestMark) {
                    lowestMark = students[i].marks[j];
                    riskySubject = j;
                }
            }
        }
        
        if(hasRisk) {
            atRiskFound = 1;
            printf("\n[!] %s (Roll: %s)\n", students[i].name, students[i].rollNo);
            printf("    -> Needs improvement in: %s\n", subjectNames[riskySubject]);
            printf("    -> Current Score: %d/100\n", students[i].marks[riskySubject]);
            printf("    -> Class Average in this subject: %.2f\n", classAvg[riskySubject]);
            printf("    -> Required to pass: At least 40 marks\n");
            printf("    -> Personalised note: Focus on %s concepts.\n\n", subjectNames[riskySubject]);
        }
    }
    
    if(!atRiskFound) {
        printf("\n[OK] No at-risk students found! All students performing well.\n");
    }
    
    printf("\n+============================================================================+\n");
    printf("| AI RULE SUMMARY:                                                           |\n");
    printf("| - Threshold: 15%% below class average                                      |\n");
    printf("| - Purpose: Identify students needing academic support                      |\n");
    printf("| - Action: Personalized improvement suggestions generated                   |\n");
    printf("+============================================================================+\n");
}

void saveToFile() {
    FILE *fp = fopen("students.dat", "wb");
    if(fp == NULL) {
        printf("Error: Cannot create save file!\n");
        return;
    }
    
    fwrite(&studentCount, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), studentCount, fp);
    
    fclose(fp);
    printf("[SUCCESS] Saved %d students to file.\n", studentCount);
}

void loadFromFile() {
    FILE *fp = fopen("students.dat", "rb");
    if(fp == NULL) {
        printf("No existing data file found. Starting fresh.\n");
        return;
    }
    
    fread(&studentCount, sizeof(int), 1, fp);
    fread(students, sizeof(Student), studentCount, fp);
    
    fclose(fp);
    printf("[SUCCESS] Loaded %d students from file.\n", studentCount);
}