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
        printf("Student not found!\n");
        return;
    }
    
    printf("Enter New Name: ");
    scanf(" %[^\n]", students[found].name);
    
    for(int i = 0; i < SUBJECT_COUNT; i++) {
        printf("%s [Credits: %d]: ", subjectNames[i], subjectCredits[i]);
        scanf("%d", &students[found].marks[i]);
    }
    
    printf("\n[SUCCESS] Student updated!\n");
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
        printf("Student not found!\n");
        return;
    }
    
    printf("Delete %s? (Y/N): ", students[found].name);
    char confirm;
    scanf(" %c", &confirm);
    
    if(confirm == 'Y' || confirm == 'y') {
        for(int i = found; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        printf("[SUCCESS] Student deleted!\n");
    }
}