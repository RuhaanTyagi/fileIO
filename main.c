//
//  main.c
//  recordMenu
//
//  Created by Ruhaan Dev Tyagi on 01/07/19.
//  Copyright © 2019 Ruhaan Dev Tyagi. All rights reserved.
//

#include <stdio.h>
#include <string.h>

struct employee
{
    int code;
    char nm[50];
    float sal;
};

int main(int argc, const char * argv[])
{
    //declaring variables
    int ch=0,c,f;
    int tbytes,nrec,rec,pos;
    struct employee e1;
    FILE *fb;
    FILE *fb1;
    
    //displaying menu
    while(ch!=10)
    {
        printf("\n1. Add record\n");
        printf("2. Display record\n");
        printf("3. Search by code through sequential access\n");
        printf("4. Number of records\n");
        printf("5. Search by code through Random access file\n");
        printf("6. Modify code through sequential access\n");
        printf("7. Modify code through Random access file\n");
        printf("8. Delete code through sequential access\n");
        printf("9. Delete code through Random access file\n");
        printf("10. Exit\n");
        printf("Enter you choice: \n");
        scanf("%d",&ch);
    
    
    
    //creating menu
    
    switch(ch)
    {
        case 1:
            
            fb=fopen("file3.txt","a");
            printf("Enter the code, name, and salary: \n");
            scanf("%d%s%f",&e1.code,e1.nm,&e1.sal);
            fwrite(&e1,sizeof(e1),1,fb);
            fclose(fb);
            break;
        
        case 2:
            
            fb=fopen("file3.txt","r");
            printf("\nCODE\tNAME\tSALARY");
            
            while(fread(&e1, sizeof(e1), 1, fb))
            {
                printf("\n%d\t%s\t%f",e1.code,e1.nm,e1.sal);
            }
            
            fclose(fb);
            break;
        
        case 3:
            fb=fopen("file3.txt","r");
            f=0;
            printf("Enter code of the record: \n");
            scanf("%d",&c);
            printf("\nCODE\tNAME\tSALARY");
            while(fread(&e1, sizeof(e1), 1, fb))
            {
                if(c == e1.code)
                {
                    printf("\n%d\t%s\t%f",e1.code,e1.nm,e1.sal);
                    f=1;
                    break;
                }
            }
            if(f==0)
            {
                printf("Record does not exist");
            }
            break;
        
        case 4:
            fb=fopen("file3.txt","r");
            fseek(fb,0,SEEK_END);
            tbytes = (int)ftell(fb);
            nrec = tbytes/sizeof(e1);
            printf("\nNumber of records is %d",nrec);
            break;
        
        case 5:
            fb=fopen("file3.txt","r");
            fseek(fb,0,SEEK_END);
            tbytes = (int)ftell(fb);
            nrec = tbytes/sizeof(e1);
            scanf("%d",&rec);
            
            if(rec>nrec)
            {
                printf("The record does not exist");
                
            }
            else
            {
                rewind(fb);
                pos=(rec-1)*sizeof(e1);
                fseek(fb,pos,SEEK_SET);
                fread(&e1,sizeof(e1),1,fb);
                printf("\n%d\t%s\t%f",e1.code,e1.nm,e1.sal);
            }
            fclose(fb);
            break;
            
        case 6:
            fb=fopen("file3.txt","r+");
            f=0;
            printf("Enter the code of the entry to be modified:\n");
            scanf("%d",&c);
            
            while(fread(&e1, sizeof(e1), 1, fb))
            {
                if(e1.code == c)
                {
                    printf("Enter new data in format\n");
                    printf("Enter code, name, and salary:\n");
                    scanf("%d%s%f",&e1.code,e1.nm,&e1.sal);
                    
                    pos = sizeof(e1);
                    fseek(fb, -pos, SEEK_CUR);
                    fwrite(&e1, sizeof(e1), 1, fb);
                    f=1;
                    break;
                }
            }
            if(f==0)
            {
                printf("The record does not exist.\n");
            }
            fclose(fb);
            break;
            
        case 7:
            fb=fopen("file3.txt","r+");
            fseek(fb,0, SEEK_END);
            tbytes = (int)ftell(fb);
            nrec = tbytes/sizeof(e1);
            
            printf("Enter the number of the record you want to modify:\n");
            scanf("%d",&rec);
            
            if(rec>nrec)
            {
                printf("Record does not exist.\n");
            }
            else
            {
                printf("Enter new information.\n Enter code, name, and salary:\n");
                scanf("%d%s%f",&e1.code,e1.nm,&e1.sal);
                pos = (rec-1)*sizeof(e1);
                fseek(fb,pos,SEEK_SET);
                fwrite(&e1,sizeof(e1),1,fb);
                printf("Record modified.\n");
            }
            fclose(fb);
            break;

        case 8:
            fb=fopen("file3.txt","r");
            f=0;
            fb1=fopen("temp.txt","w");
            
            printf("Enter the code of the entry to be removed:\n");
            scanf("%d",&c);
            
            while(fread(&e1, sizeof(e1), 1, fb))
            {
                if(e1.code != c)
                {
                    fwrite(&e1,sizeof(e1),1,fb1);
                }
                else
                {
                    f=1;
                }
            }
            if(f==0)
            {
                printf("The record does not exist.\n");
            
            }
            else{
                printf("Record has been deleted.\n");
                
            }
            
            fclose(fb);
            fclose(fb1);
            remove("file3.txt");
            rename("temp.txt","file3.txt");
            
            break;
            
        case 9:
            fb=fopen("file3.txt","r");
            fb1=fopen("temp.txt","w");
            fseek(fb,0,SEEK_END);
            tbytes = (int)ftell(fb);
            nrec = tbytes/sizeof(e1);
            printf("Enter the number of the record to be deleted");
            scanf("%d",&rec);
            
            if(rec>nrec)
            {
                printf("The record does not exist.\n");
                fclose(fb);
                fclose(fb1);
                break;
            }
            else{
                rewind(fb);
                for(int i=1;i<=nrec;i++)
                {
                    fread(&e1, sizeof(e1), 1, fb);
                    if(i != rec)
                    {
                        fwrite(&e1,sizeof(e1),1,fb1);
                        
                    }
                }
                fclose(fb);
                fclose(fb1);
                remove("file3.txt");
                rename("temp.txt","file3.txt");
            }
            break;
            
        case 10:
            exit(0);
    }
  }
  
    
    return 0;
}
