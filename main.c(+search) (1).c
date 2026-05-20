void searchStudent() {
    char rollNo[20];
    printf("\n--- Search Student ---\n");
    printf("Enter Roll Number: ");
    scanf("%s", rollNo);
    
    for(int i = 0; i < studentCount; i++) {
        if(strcmp(students[i].rollNo, rollNo) == 0) {
            printf("\nRoll No: %s\n", students[i].rollNo);
            printf("Name: %s\n", students[i].name);
            for(int j = 0; j < SUBJECT_COUNT; j++) {
                printf("%s: %d\n", subjectNames[j], students[i].marks[j]);
            }
            return;
        }
    }
    printf("Student not found!\n");
}