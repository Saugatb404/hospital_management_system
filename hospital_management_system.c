#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

FILE *fp;

typedef struct patient{
    int id;
    char pname[20];
    int age;
    char gender[10] ,address[50] , symptomes[255] , checkby_doctor[20];
    char date[10];
    
    }patient;

    typedef struct doctor{
        int docid;
        char dname[20];
        char docaddress[50] ,specialized[50];
        char date[10];

    }doc;


    void admit_patient(){
        

        patient p;
        time_t t;// time_t is a datatype in <time.h> 
        struct tm *time_info;
        char buffer[20];
        time(&t);// store time in the variable
        time_info = localtime(&t);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info); // localtime():Converts the time to the local time zone. converts the time in human readable formate
        //strftime: . converts the time in human readable formate
        
        strcpy(p.date, buffer);


        fp = fopen("patient.txt", "ab");

        printf("Enter Patient id: ");
        scanf("%d", &p.id);
    
        printf("\nEnter Patient name: \t");
        fflush(stdin);     
        gets(p.pname);

        printf("\nEnter Patient gender: \t");
        fflush(stdin);
        gets(p.gender);

        
    
        printf("\nEnter Patient Address:\t ");
        fflush(stdin);
        gets(p.address);
    
        printf("\nEnter Patient symptomes: \t");
        fflush(stdin);
        gets(p.symptomes);

        printf("\nEnter Patient checkup doctor: \t");
        fflush(stdin);
        gets(p.checkby_doctor);
    
        fwrite(&p, sizeof(p), 1, fp);
        fclose(fp);
        printf("\nPatient Added Successfully");



    }


    void discharge_patient() {
        patient p;
        int id, f = 0;
        system("cls");
        printf("<== Discharge Patient ==>\n\n");
        printf("Enter Patient id to discharge: ");
        scanf("%d", &id);
    
        FILE *fp, *ft;  // Declare file pointers locally
    
        fp = fopen("patient.txt", "rb");
    
        ft = fopen("temp.txt", "wb");
    
        while (fread(&p, sizeof(p), 1, fp) == 1) {
            if (id == p.id) {
                f = 1;  // Found the patient, but don't write it to new file
            } else {
                fwrite(&p, sizeof(p), 1, ft);
            }
        }
    
        fclose(fp);
        fclose(ft);
    
        if (f == 1) {
            remove("patient.txt");
            rename("temp.txt", "patient.txt");
            printf("\n\nPatient Discharged Successfully.\n");
        } else {
            printf("\n\nRecord Not Found!\n");
            remove("temp.txt");  // Cleanup temp file
        }
    }
    
    


int main(){

    int choice;
     // infinite loop in while(true) ; the loop can be countered by switch statement
     while(1){  
        system("cls");
        printf("\t\t\t\t<-------Hospital Management system------->\n\n");
        printf("\t1. Admit Patient\n");
        printf("\t2. Discharge Patient\n");
        printf("\t3. Patient List\n");
        printf("\t4. Available Doctor\n");
        printf("\t5. Add Doctor\n");
        printf("\t6. Appointment\n");
        printf("\t0. Exit\n");
        printf("\n------------------------------------------------------");
        printf("\nEnter your choice :\t");
        scanf("%d",&choice);
        while (getchar() != '\n');  // Clear input buffer


        switch (choice) {
            case 1:
                admit_patient();
                break;
            case 2:
                discharge_patient();
                break;
            case 3:
                patient_list();
                break;
            case 4:
                available_doctor();
                break;
            case 5:
                add_doctor();
                break;
            case 6:
            	appointment();
            	break;
            case 0:
                printf("Exiting program...\n");
                exit(0); 
            default:
                printf("Invalid choice! Try again.\n");
        }
        printf("\n\n\t\t Press any key to continue---");
        getchar();
     }





    return 0;
}