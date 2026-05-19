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