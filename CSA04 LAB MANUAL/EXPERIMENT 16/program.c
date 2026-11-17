#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Random access file: each employee record sits at a fixed offset,
   so any record can be read/updated directly using fseek(). */
struct Employee { int empId; char empName[50]; float empSalary; };

#define FILENAME "employee.dat"

void add_record(FILE *fp) {
    struct Employee e;
    printf("ID: "); scanf("%d", &e.empId);
    printf("Name: "); scanf("%49s", e.empName);
    printf("Salary: "); scanf("%f", &e.empSalary);
    fseek(fp, (e.empId - 1) * sizeof(e), SEEK_SET);
    fwrite(&e, sizeof(e), 1, fp);
    fflush(fp);
    printf("Record %d added.\n", e.empId);
}

void read_record(FILE *fp) {
    struct Employee e;
    int id;
    printf("ID to read: "); scanf("%d", &id);
    fseek(fp, (id - 1) * sizeof(e), SEEK_SET);
    if (fread(&e, sizeof(e), 1, fp) != 1 || e.empId != id) { printf("Record %d not found.\n", id); return; }
    printf("ID: %d  Name: %s  Salary: %.2f\n", e.empId, e.empName, e.empSalary);
}

void update_record(FILE *fp) {
    struct Employee e;
    int id;
    printf("ID to update: "); scanf("%d", &id);
    fseek(fp, (id - 1) * sizeof(e), SEEK_SET);
    if (fread(&e, sizeof(e), 1, fp) != 1 || e.empId != id) { printf("Record %d not found.\n", id); return; }
    printf("New name: "); scanf("%49s", e.empName);
    printf("New salary: "); scanf("%f", &e.empSalary);
    fseek(fp, (id - 1) * sizeof(e), SEEK_SET);
    fwrite(&e, sizeof(e), 1, fp);
    fflush(fp);
    printf("Record %d updated.\n", id);
}

int main() {
    FILE *fp = fopen(FILENAME, "rb+");
    if (fp == NULL) {                           /* create if missing */
        fp = fopen(FILENAME, "wb+");
        if (fp == NULL) { printf("Error creating file.\n"); return 1; }
    }
    int choice;
    do {
        printf("\n1. Add  2. Display  3. Update  4. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1: add_record(fp); break;
            case 2: read_record(fp); break;
            case 3: update_record(fp); break;
            case 4: printf("Exiting.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
    fclose(fp);
    return 0;
}
