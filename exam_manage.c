#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int student_id;
    char name[50];
    char subject[50];
    struct Student* next;
};

struct StudentList {
    struct Student* head;
};

struct ExamSystem {
    struct StudentList* student_list;
    struct Student* queue[100]; // Queue for exam seat allocation
    int front, rear;
};

// Create a new student
struct Student* create_student(int student_id, char* name, char* subject) {
    struct Student* new_student = (struct Student*)malloc(sizeof(struct Student));
    new_student->student_id = student_id;
    strcpy(new_student->name, name);
    strcpy(new_student->subject, subject);
    new_student->next = NULL;
    return new_student;
}

// Add a student to the linked list
void add_student_to_list(struct StudentList* list, struct Student* student) {
    if (list->head == NULL) {
        list->head = student;
    } else {
        struct Student* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = student;
    }
}

// Display registered students
void display_students(struct StudentList* list) {
    if (list->head == NULL) {
        printf("No students registered.\n");
        return;
    }
    struct Student* current = list->head;
    printf("\nRegistered Students:\n");
    while (current != NULL) {
        printf("ID: %d, Name: %s, Subject: %s\n", current->student_id, current->name, current->subject);
        current = current->next;
    }
}

// Register a student
void register_student(struct ExamSystem* system, int student_id, char* name, char* subject) {
    struct Student* new_student = create_student(student_id, name, subject);
    add_student_to_list(system->student_list, new_student);
    system->queue[system->rear++] = new_student; // Add to the queue
    printf("Student %s registered successfully!\n", name);
}

// Allocate exam seats
void allocate_exam_seats(struct ExamSystem* system) {
    if (system->front == system->rear) {
        printf("No students to allocate exam seats.\n");
        return;
    }

    printf("\nAllocating Exam Seats:\n");
    int seat_number = 1;
    while (system->front < system->rear) {
        struct Student* student = system->queue[system->front++];
        printf("Allocating seat %d to %s (ID: %d) for %s\n", seat_number, student->name, student->student_id, student->subject);
        seat_number++;
    }
}

// Display allocated seats
void display_seat_allocation(struct ExamSystem* system) {
    if (system->front == 0 && system->rear == 0) {
        printf("No exam seats allocated yet.\n");
        return;
    }

    printf("\nAllocated Exam Seats:\n");
    for (int i = 0; i < system->front; i++) {
        printf("Seat %d: %s (ID: %d) for %s\n", i + 1, system->queue[i]->name, system->queue[i]->student_id, system->queue[i]->subject);
    }
}

// Cancel seat
void cancel_exam_seat(struct ExamSystem* system, int student_id) {
    int found = 0;
    for (int i = 0; i < system->rear; i++) {
        if (system->queue[i]->student_id == student_id) {
            printf("Exam seat for student ID: %d canceled.\n", student_id);
            free(system->queue[i]);

            // Shift 
            for (int j = i; j < system->rear - 1; j++) {
                system->queue[j] = system->queue[j + 1];
            }
            system->rear--;
            if (i < system->front) {
                system->front--;
            }
            
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No exam seat found for student ID: %d\n", student_id);
    }
}


int main() {
    struct ExamSystem system;
    system.student_list = (struct StudentList*)malloc(sizeof(struct StudentList));
    system.student_list->head = NULL;
    system.front = 0;
    system.rear = 0;

    char* subjects[] = {"Data Structures", "DSTL", "UHV", "COA", "Python"};
    int subject_count = 5;

    while (1) {
        int choice, student_id, subject_choice;
        char name[50], subject[50];

        printf("\nOnline Exam System Menu:\n");
        printf("1. Register Student\n");
        printf("2. Display Registered Students\n");
        printf("3. Allocate Exam Seats\n");
        printf("4. Cancel Exam Seat\n");
        printf("5. Display Allocated Seats\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Register a new student
                printf("Enter Student ID: ");
                scanf("%d", &student_id);
                getchar(); // Consume newline character
                printf("Enter Student Name: ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character
                printf("Select Subject:\n");
                for (int i = 0; i < subject_count; i++) {
                    printf("%d. %s\n", i + 1, subjects[i]);
                }
                printf("Enter your choice: ");
                scanf("%d", &subject_choice);

                if (subject_choice < 1 || subject_choice > subject_count) {
                    printf("Invalid subject choice.\n");
                    break;
                }

                strcpy(subject, subjects[subject_choice - 1]);
                register_student(&system, student_id, name, subject);
                break;
            case 2:
                display_students(system.student_list);
                break;
            case 3:
                allocate_exam_seats(&system);
                break;
            case 4:
                printf("Enter Student ID to cancel exam seat: ");
                scanf("%d", &student_id);
                cancel_exam_seat(&system, student_id);
                break;
            case 5:
                display_seat_allocation(&system);
                break;
            case 6:
                printf("Exiting the system.\n");
                free(system.student_list);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
