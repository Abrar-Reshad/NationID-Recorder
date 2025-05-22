#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int main();
struct information_ppl
{
    char name[50],age[20],nid[300];
    int gender_select;

}info;
int add_data_to_file()
{
    FILE *file;
    file=fopen("information.txt","r");
    char check_nid[100],check_nid_2[100]="NID: ";//check nid 2 is the input

    printf("\nenter the NID number\ninput: ");
    gets(info.nid);

    strcat(check_nid_2,info.nid);
    check_nid_2[strlen(check_nid_2)]='\n';
    check_nid_2[strlen(check_nid_2)+1]='\0';
    fflush(stdin);
    while(!feof(file))
    {
        fgets(check_nid,90,file);  //check_nid is from file
        if(strcmp(check_nid,check_nid_2)==0)
        {
            printf("the NID is already registered,\n\nPress any key to return to main the main menu");
            getchar();
            fclose(file);
            main();
        }
    }
    file=fopen("information.txt","a");


    fputs("NID: ",file);
    fputs(info.nid,file);
    fputc('\n',file);

    printf("\nenter the name of the person\n");
    gets(info.name);

    fputs("NAME: ",file);
    fputs(info.name,file);
    fputs("\n",file);

    printf("\nenter the age of the person\n");
    gets(info.age);
    fflush(stdin);
    fputs("age: ",file);
    fputs(info.age,file);
    label:
    printf("\nselect gender\nenter\n1 for MALE\n2 for FEMALE\n");
    scanf("%i",&info.gender_select);
    fflush(stdin);

    if(info.gender_select==1)
    {
        fputs("\ngender: male\n",file);
    }
    else if(info.gender_select==2)
    {
        fputs("\ngender: female\n",file);
    }
    else
    {
        printf("invalid input for gender. please try again\n");
        goto label;
    }


    fputs("\n\n\n",file);
    system("cls");
    fclose(file);
    printf("Information entered successfully.\n\nwould you like to make another entry?\n");
    printf("\nenter\n1 for YES\n2 for NO\n\n");
    int yes_no;
    scanf("%i",&yes_no);
    fflush(stdin);
    if(yes_no==1)
    {
        system("cls");
        add_data_to_file();
    }
    else if(yes_no==2)
    {
        system("cls");
        main();
    }
    return 0;
}
void view_all_records()
{
    FILE *file;
    file=fopen("information.txt","r");

    char ch;
    while(!feof(file))
    {

        ch= fgetc(file);
        printf("%c",ch);
    }
    fclose(file);
    main();
}
void view_specific_record()
{

    FILE *file;
    file=fopen("information.txt","r");
    char ch[20],string[100],line[100],new_string[100]="NID: ";
    int i,length,mark=0,yes_no;

    printf("enter the NID no. of the person\n");
    gets(string);
    strcat(new_string,string);
    printf("\n");
    length=strlen(new_string);
    new_string[length]='\n';
    new_string[length+1]='\0';
    while(!feof(file))
    {
        fgets(ch,100,file);  //ch is the one from file

        if(strcmp(ch,new_string)==0)
        {
            printf("\nDETAILS\n\n");
            printf("%s\n",new_string);
            mark++;
            for(i=0;i<3;i++)
            {
                fgets(line,100,file);
                puts(line);
            }
        }
    }
    if(mark==0)
    {
        printf("\nid not found in the records\n");
    }

    fclose(file);

    printf("\nENTER\n1 to return to main menu\n2 to search again\n3 to add a new entry\n");
    scanf("%i",&yes_no);
    fflush(stdin);
    if(yes_no==1)
    {
        system("cls");
        main();
    }
    else if(yes_no==2)
    {
        system("cls");
        view_specific_record();
    }
    else if(yes_no==3)
    {
        system("cls");
        add_data_to_file();
    }
    else
    {
        system("cls");
        printf("invalid input.please try again\n");

    }

}
void file_destruction()
{
    printf("re you sure you want to delete all records?\n\nOnce deleted,the records can not be retrieved\n");
    int yes_no;
    label:
    printf("\nenter\n1 for YES\n2 for NO\n\n");
    scanf("%i",&yes_no);

    fflush(stdin);
    if(yes_no==1)
    {
        system("cls");

    }
    else if(yes_no==2)
    {
        system("cls");

        main();
    }
    else
    {
        printf("invalid input. please try again\n");
        goto label;
    }
    FILE *file;
    file= fopen("information.txt","w+");
    fclose(file);
    printf("records deleted successfully.\nenter any key to return to the main menu.\n");
    getchar();
    system("cls");
    main();
}
void specific_record_deletion()
{
    FILE *file;
    char string[100],line_read[100],add_string[100]="NID: ";
    int length,mark=0;
    file=fopen("information.txt","r+");
    if(file==NULL)
    {
        printf("file wasnt opened successfully. returned to main menu");
        main();
    }
    else
    {
        printf("enter nid of the person\n");
       gets(string);
        strcat(add_string,string);
        length=strlen(add_string);
        add_string[length]='\n';
        add_string[length+1]='\0';

        while(!feof(file))
        {
            fgets(line_read,100,file);
            if(strcmp(line_read,add_string)==0)
            {
                fseek(file,(-1*strlen(line_read))-1,SEEK_CUR);          //searches for the nid and if found, moves the pointer to the star ofthe line
                mark++;
                break;
            }
        }
        int count=0;
        char ch;
       if(mark!=0)  //only executes if the nid was found
       {
            while(count<4)
            {

                 ch=fgetc(file);
                 if(ch=='\n')
                 {
                     count++;
                     continue;
                 }
                 else
                 {
                     fseek(file,1,SEEK_CUR);
                     fputc(' ',file);
                     fflush(stdin);
                 }
            }
       }
    }
    fclose(file);
    main();
}
int main()
{
    FILE *file;
    file=fopen("information.txt","r");
    if(file==NULL)
    {
        file=fopen("information.txt","w");  //this makes sure there is a file present every time the program is started
        fclose(file);
    }
    else
    {
        fclose(file);
    }

    printf("MAIN MENU\n\nENTER\n");
    printf("1 to add data\n");//main menu
    printf("2 to view all records\n");
    printf("3 to search for specific record\n");     //navigates the user to different functions
    printf("4 to exit program\n");
    printf("5 to for file destruction\n");
    printf("6 to for specific record deletion\n");
    int num;
    scanf("%i",&num);
    fflush(stdin);
    if(num==1)
    {
        system("cls");
        add_data_to_file();
    }
    else if(num==4)
    {
        system("cls");
        return 0;
    }
    else if(num==2)
    {
        system("cls");
        view_all_records();                  //directing user to their desired funtion
    }
    else if(num==3)
    {
        system("cls");
        view_specific_record();
    }
    else if(num==5)
    {
        system("cls");
        file_destruction();
    }
    else if(num==6)
    {
        system("cls");
        specific_record_deletion();
    }
}

