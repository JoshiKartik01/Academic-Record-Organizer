#include <stdio.h>
#include <stdlib.h>

struct student {
    int roll;
    char name[100];
    float marks;
};

void addRecord();
void displayRecords();
void searchRecord();
void modifyRecord();
void deleteRecord();

int main() {
    int choice;

    while (1) {
        printf("\n===== STUDENT RECORD SYSTEM =====\n");
        printf("1. Add Record\n");
        printf("2. Display Records\n");
        printf("3. Search Record\n");
        printf("4. Modify Record\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addRecord(); break;
            case 2: displayRecords(); break;
            case 3: searchRecord(); break;
            case 4: modifyRecord(); break;
            case 5: deleteRecord(); break;
            case 6: printf("Exiting...\n");
                    exit(0);
            default: printf("Invalid Choice!\n");
        }
    }

    return 0;
}

void addRecord() {
    FILE *fp;
    struct student s;

    fp = fopen("student.txt", "a");
    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d \"%s\" %.2f\n", s.roll, s.name, s.marks);
    fclose(fp);

    printf("Record Added Successfully!\n");
}

void displayRecords() {
    FILE *fp;
    struct student s;

    fp = fopen("student.txt", "r");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n%-8s %-25s %-8s\n", "Roll", "Name", "Marks");
    printf("------------------------------------------------\n");

    while (fscanf(fp, "%d \"%[^\"]\" %f",
                  &s.roll, s.name, &s.marks) == 3) {

        printf("%-8d %-25s %-8.2f\n",
               s.roll, s.name, s.marks);
    }

    fclose(fp);
}

void searchRecord() {
    FILE *fp;
    struct student s;
    int roll, found = 0;

    fp = fopen("student.txt", "r");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d \"%[^\"]\" %f",
                  &s.roll, s.name, &s.marks) == 3) {

        if (s.roll == roll) {
            printf("\nRecord Found:\n");
            printf("Roll: %d\nName: %s\nMarks: %.2f\n",
                   s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Record Not Found!\n");

    fclose(fp);
}

void modifyRecord() {
    FILE *fp, *temp;
    struct student s;
    int roll, found = 0;

    fp = fopen("student.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Roll Number to Modify: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d \"%[^\"]\" %f",
                  &s.roll, s.name, &s.marks) == 3) {

        if (s.roll == roll) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            found = 1;
        }

        fprintf(temp, "%d \"%s\" %.2f\n",
                s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found)
        printf("Record Modified Successfully!\n");
    else
        printf("Record Not Found!\n");
}

void deleteRecord() {
    FILE *fp, *temp;
    struct student s;
    int roll, found = 0;

    fp = fopen("student.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d \"%[^\"]\" %f",
                  &s.roll, s.name, &s.marks) == 3) {

        if (s.roll == roll) {
            found = 1;
            continue;
        }

        fprintf(temp, "%d \"%s\" %.2f\n",
                s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found)
        printf("Record Deleted Successfully!\n");
    else
        printf("Record Not Found!\n");
}