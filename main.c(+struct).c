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