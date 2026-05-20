void displayAllStudents() {
    if(studentCount == 0) {
        printf("\nNo students in database!\n");
        return;
    }
    
    printf("\n%-20s %-30s %10s\n", "ROLL NUMBER", "NAME", "PERCENTAGE");
    printf("------------------------------------------------------------\n");
    
    for(int i = 0; i < studentCount; i++) {
        printf("%-20s %-30s %10.2f\n", 
               students[i].rollNo, students[i].name, students[i].percentage);
    }
}

void displayRanking() {
    if(studentCount == 0) {
        printf("\nNo students to rank!\n");
        return;
    }
    
    // Simple bubble sort by SGPA
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
    
    printf("\n%-6s %-20s %-30s %8s\n", "RANK", "ROLL NUMBER", "NAME", "SGPA");
    printf("------------------------------------------------------------\n");
    
    for(int i = 0; i < studentCount; i++) {
        printf("%-6d %-20s %-30s %8.2f\n", 
               i + 1, sorted[i].rollNo, sorted[i].name, sorted[i].sgpa);
    }
}