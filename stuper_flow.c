#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 50
#define SUBJECTS 4

typedef struct Student {
    int roll;
    char name[NAME_SIZE];
    float marks[SUBJECTS]; // [0]=Math, [1]=Science, [2]=English, [3]=Computer
    float total;
    char grade;
    struct Student *next;
} Student;

Student *head = NULL;

// Function to calculate grade
char calcGrade(float avg) {
    if (avg >= 90) return 'A';
    else if (avg >= 80) return 'B';
    else if (avg >= 70) return 'C';
    else if (avg >= 60) return 'D';
    else return 'F';
}

// Function to compute total and grade
void computeTotal(Student *s) {
    s->total = 0;
    for (int i = 0; i < SUBJECTS; i++)
        s->total += s->marks[i];
    float avg = s->total / SUBJECTS;
    s->grade = calcGrade(avg);
}

// Function to add a new student
void addStudent() {
    Student *s = (Student *)malloc(sizeof(Student));
    if (s == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("\nEnter Roll No: ");
    scanf("%d", &s->roll);
    getchar(); // consume newline

    printf("Enter Name: ");
    fgets(s->name, NAME_SIZE, stdin);
    s->name[strcspn(s->name, "\n")] = '\0';

    char *subjects[] = {"Math", "Science", "English", "Computer"};
    for (int i = 0; i < SUBJECTS; i++) {
        printf("Enter %s Marks: ", subjects[i]);
        scanf("%f", &s->marks[i]);
    }

    computeTotal(s);
    s->next = NULL;

    if (head == NULL)
        head = s;
    else {
        Student *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = s;
    }

    printf("\n✅ Student Added Successfully!\n");
}

// Display all students
void displayStudents() {
    if (head == NULL) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n%-6s %-15s %-8s %-8s %-8s %-10s %-8s %-6s\n",
           "Roll", "Name", "Math", "Science", "English", "Computer", "Total", "Grade");
    printf("-----------------------------------------------------------------------\n");

    Student *temp = head;
    while (temp != NULL) {
        printf("%-6d %-15s %-8.2f %-8.2f %-8.2f %-10.2f %-8.2f %-6c\n",
               temp->roll, temp->name,
               temp->marks[0], temp->marks[1], temp->marks[2], temp->marks[3],
               temp->total, temp->grade);
        temp = temp->next;
    }
}

// Show subject-wise toppers and overall topper
void showToppers() {
    if (head == NULL) {
        printf("\nNo student records.\n");
        return;
    }

    Student *topperSub[SUBJECTS] = {NULL};
    float maxMarks[SUBJECTS] = {-1, -1, -1, -1};
    Student *overallTop = head;
    char *subjects[] = {"Math", "Science", "English", "Computer"};

    for (Student *temp = head; temp != NULL; temp = temp->next) {
        for (int i = 0; i < SUBJECTS; i++) {
            if (temp->marks[i] > maxMarks[i]) {
                maxMarks[i] = temp->marks[i];
                topperSub[i] = temp;
            }
        }
        if (temp->total > overallTop->total)
            overallTop = temp;
    }

    printf("\n===== Subject-wise Toppers =====\n");
    for (int i = 0; i < SUBJECTS; i++) {
        printf("%-10s : %-15s (%.2f)\n", subjects[i], topperSub[i]->name, maxMarks[i]);
    }

    printf("\n===== Overall Topper =====\n");
    printf("Name: %-15s | Roll: %d | Total: %.2f | Grade: %c\n",
           overallTop->name, overallTop->roll, overallTop->total, overallTop->grade);
}

// Search student by roll
void searchStudent() {
    int roll;
    printf("\nEnter Roll No to Search: ");
    scanf("%d", &roll);

    Student *temp = head;
    while (temp != NULL) {
        if (temp->roll == roll) {
            printf("\nStudent Found:\n");
            printf("Roll: %d\nName: %s\nMath: %.2f\nScience: %.2f\nEnglish: %.2f\nComputer: %.2f\nTotal: %.2f\nGrade: %c\n",
                   temp->roll, temp->name,
                   temp->marks[0], temp->marks[1], temp->marks[2], temp->marks[3],
                   temp->total, temp->grade);
            return;
        }
        temp = temp->next;
    }
    printf("❌ Student not found.\n");
}

// Update marks
void updateStudent() {
    int roll;
    printf("\nEnter Roll No to Update: ");
    scanf("%d", &roll);

    Student *temp = head;
    while (temp != NULL) {
        if (temp->roll == roll) {
            char *subjects[] = {"Math", "Science", "English", "Computer"};
            for (int i = 0; i < SUBJECTS; i++) {
                printf("Enter new %s Marks (current %.2f): ", subjects[i], temp->marks[i]);
                scanf("%f", &temp->marks[i]);
            }
            computeTotal(temp);
            printf("✅ Updated Successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("❌ Student not found.\n");
}

// Delete student by roll
void deleteStudent() {
    int roll;
    printf("\nEnter Roll No to Delete: ");
    scanf("%d", &roll);

    Student *temp = head, *prev = NULL;
    while (temp != NULL) {
        if (temp->roll == roll) {
            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;
            free(temp);
            printf("✅ Student Deleted Successfully!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("❌ Student not found.\n");
}

// Free all memory
void freeAll() {
    Student *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int choice;
    do {
        printf("\n========= Student Grade Management =========\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Show Subject-wise & Overall Toppers\n");
        printf("4. Search Student\n");
        printf("5. Update Student Marks\n");
        printf("6. Delete Student\n");
        printf("7. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: showToppers(); break;
            case 4: searchStudent(); break;
            case 5: updateStudent(); break;
            case 6: deleteStudent(); break;
            case 7:
                printf("\nExiting... Thank you!\n");
                freeAll();
                break;
            default:
                printf("Invalid Option! Try Again.\n");
        }
    } while (choice != 7);

    return 0;
}