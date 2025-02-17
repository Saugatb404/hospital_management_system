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


void available_doctor() {
    doc d;
    FILE *fp;

    fp = fopen("doctor.txt", "rb"); 

    char checkdate[10];
    printf("Enter the date to check for doctor availability: ");
    scanf("%s", checkdate);

    int davailable=0; 


    while (fread(&d, sizeof(d), 1, fp) == 1) {
        if (strcmp(d.date, checkdate) == 0) {
            
            printf("Doctor %s is available on this date with specialization in %s.\n", d.dname, d.specialized);
            davailable = 1;
        }
    }

    
    if (davailable == 0) {
        printf("No doctor is available for the date %s.\n", checkdate);
    }

    fclose(fp); 
}

void patient_list()
{
        struct patient s;
        FILE *fp;
        fp=fopen("patient.txt","rb");
        while(fread(&s,sizeof(s),1,fp)==1)
        {
            printf("ID: %d\n", s.id);
            printf("Name: %s\n", s.pname);
            printf("Age: %d\n", s.age);
            printf("Gender: %s\n", s.gender);
            printf("Address: %s\n", s.address);
            printf("Symptoms: %s\n", s.symptomes);
            printf("Checked by: %s\n", s.checkby_doctor);
            printf("Date: %d/%d/%d\n", s.date[0], s.date[1], s.date[2]);
            printf("\n");
        }
        fclose(fp);
}

void appointment()
{   
    int i=0;
    int dokid;
    struct doctor s[100];
    printf("doctor is only available for 3 hours in this hospital 9:00-10:00, 10:00-11:00, 11:00-12:00\n");
    printf("enter the doctor id:");
    scanf("%d",&dokid);
    FILE *fp;
    fp=fopen("doctor.txt","rb+");
    while(fread(&s,sizeof(s),1,fp)==1)
    {   i++;
        if(s->docid==dokid)
        {
            int choice;
            printf("Doctor Name:%s\n",s->dname);
            printf("Doctor Address:%s\n",s->docaddress);
            printf("Doctor Specialized:%s\n",s->specialized);
            printf("Doctor Date:%d/%d/%d\n",s->date[0],s->date[1],s->date[2]);
            printf("enter the timinings you want to book the appointment:");
            printf("1. 9:00-10:00\n");
            printf("2. 10:00-11:00\n");
            printf("3. 11:00-12:00\n");
            scanf("%d",&choice);
            if (choice < 1 || choice > 3) {
                printf("Invalid choice!\n");
                fclose(fp);
            }
            if(choice==1)
            {
                if(s->date[0]==0)
                {
                    s->date[0]=1;
                    printf("Appointment booked successfully\n");
                }
                else
                {
                    printf("Appointment already booked\n");
                }
            }
            if(choice==2)
            {
                if(s->date[1]==0)
                {
                    s->date[1]=1;
                    printf("Appointment booked successfully\n");
                }
                else
                {
                    printf("Appointment already booked\n");
                }
            }
            if(choice==3)
            {
                if(s->date[2]==0)
                {
                    s->date[2]=1;
                    printf("Appointment booked successfully\n");
                }
                else
                {
                    printf("Appointment already booked\n");
                }
            }
            fseek(fp,(i-1)*sizeof(s),SEEK_SET);
            fwrite(&s,sizeof(s),1,fp);
            fclose(fp);
            break;


        }
        else
        {
            printf("Doctor not found\n");
        }
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
