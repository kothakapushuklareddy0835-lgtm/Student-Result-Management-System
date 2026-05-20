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
    for(int i = 0; i < SUBJECT_COUNT; i++) {
        printf("%s [Credits: %d]: ", subjectNames[i], subjectCredits[i]);
        scanf("%d", &newStudent.marks[i]);
        
        if(newStudent.marks[i] < 0 || newStudent.marks[i] > 100) {
            printf("Error: Marks must be between 0 and 100!\n");
            return;
        }
    }
    
    students[studentCount] = newStudent;
    studentCount++;
    
    printf("\n[SUCCESS] Student added successfully!\n");
}