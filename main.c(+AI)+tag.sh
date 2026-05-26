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
