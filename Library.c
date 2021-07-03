#include <stdio.h>
#include <stdlib.h>
#include <conio.h> //for clearing the screen
#include <stdbool.h> //for boolean declaration.
#include <string.h> //for strcmp function

int index;

struct database{
    char name[100];
    int id;
    int quantity;
    bool deleted;
} data[100] , sorted_data[100];

void load_data();
void menu();
void take_input();
void insert_book();
void delete_book();
bool search_via_ID(int , int);
void swap_data(int , int);
void sort_data();
void search_via_Name();
void display_lexo();
void display_time();
void save();
void endd();

FILE* fptr;

bool firstTime;
bool exit_from_program;

int main(){
    /*
        input as follows:
        id
        name
        quantity
        ended by # mark
    */

    load_data();
    firstTime = true;

    while(1){
        menu();
        take_input();
        system("cls");
        endd();
        if(exit_from_program)
            break;
    }
    save();
}

void endd(){
    char last[65];
    printf("Do you Need anything else Yes/No ?\n");
    scanf("%s" , last);
    if(last[0] == 'N' || last[0] == 'n')
        exit_from_program = true;
}

load_data(){
    fptr = fopen("database.txt" , "r");
    puts("Loading Data...");
    while(!feof(fptr)){
        struct database temp;
        fscanf(fptr , "%d " , &temp.id);
        int jdx = 0;
        while(1){
            char cur = fgetc(fptr);
            if(cur == '\n')
                break;
            temp.name[jdx++] = cur;
        }
        temp.name[jdx] = '\0';
        fscanf(fptr , "%d" , &temp.quantity);
        temp.deleted = false;
        data[index] = temp;
        sorted_data[index] = temp;
        index++;
    }
    fclose(fptr);
    system("cls");
}

menu(){
    if(firstTime){
        puts("Welcome To Our Library..\n");
        puts("Library Menu :");
        firstTime = false;
    }
    puts("1 - Insert a book.");
    puts("2 - Delete a book via ID.");
    puts("3 - Search via ID.");
    puts("4 - Search via Name.");
    puts("5 - Display Library. (Lexicographically)");
    puts("6 - Display Library. (In Order of Input..)");
    puts("\nPlease choose the operation number and press enter..");
}

take_input(){
    int operation;
    scanf("%d" , &operation);
    if(operation == 1){
        insert_book();
    } else if(operation == 2){
        delete_book();
    } else if(operation == 3){
        system("cls");
        printf("What's your book ID ..\n");
        int id;
        scanf("%d" , &id);
        bool ret = search_via_ID(0 , id);
        if(!ret){
            puts("Not Found!");
            system("PAUSE");
        }
    } else if(operation == 4){
        system("cls");
        puts("Please Enter The Book Name..");
        struct database temp;
        scanf(" %[^\n]" , temp.name);
        sort_data();
        search_via_Name(&temp.name[0] , strlen(temp.name));
    } else if(operation == 5){
        sort_data();
        display_lexo();
    } else if(operation == 6){
        display_time();
    } else if(operation == 7) {
        exit_from_program = true;
        return;
    } else {
        puts("Please Enter One of the Above Operations!");
        return;
    }
}

insert_book(){
    system("cls");
    struct database temp;
    printf("ID :\n");
    scanf("%d" , &temp.id);
    fflush(stdin);
    printf("Book Name :\n");
    int jdx = 0;
    gets(temp.name);
    printf("Quantity :\n");
    scanf("%d" , &temp.quantity);
    puts("Your book saved in our library!");
    temp.deleted = false;
    data[index] = sorted_data[index] = temp;
    index++;
    save();
    system("PAUSE");
    system("cls");
}

delete_book(){
    system("cls");
    int id;
    printf("What's your book ID : ");
    scanf("%d" , &id);
    bool ret = false;
    for(int i = 0; i < index; i++){
        if(data[i].id == id){
            ret = true;
            data[i].deleted = true;
            break;
        }
    }
    for(int i = 0; i < index; i++){
        if(sorted_data[i].id == id){
            sorted_data[i].deleted = true;
            break;
        }
    }
    if(ret){
        puts("Your Book's been deleted..");
    } else {
        puts("Already Deleted!");
    }
    save();
    system("PAUSE");
}

bool search_via_ID(int idx , int id){
    if(idx == index)
        return false;
    if(data[idx].id == id && !data[idx].deleted){
        printf("Book Name : %s\n" , data[idx].name);
        printf("ID : %d , Quantity : %d\n" , data[idx].id , data[idx].quantity);
        system("PAUSE");
        return true;
    }
    return search_via_ID(idx + 1 , id);
}

swap(int id1 , int id2){
    struct database temp = sorted_data[id1];
    sorted_data[id1] = sorted_data[id2];
    sorted_data[id2] = temp;
}

sort_data(){
    for(int i = index; i > 0; i--){
        for(int j = 0; j < i-1; j++){
            if(strcmp(sorted_data[j].name , sorted_data[j+1].name) > 0){
                //J is bigger
                swap(j , j + 1);
            }
        }
    }
}

display_lexo(){
    system("cls");
    puts("Your Library (Lexo)..\n");
    for(int i = 0; i < index; i++){
        if(sorted_data[i].deleted)
            continue;
        printf("Book Name : %s\n" , sorted_data[i].name);
        printf("ID : %d , Quantity : %d\n" , sorted_data[i].id , sorted_data[i].quantity);
        puts("");
    }
    system("PAUSE");
}

search_via_Name(char *name , int n){
    system("cls");
    int l = 0 , r = index - 1 , ans = -1;
    while(l < r){
        int mid = (l + r + 1) / 2;
        if(strcmp(name , sorted_data[mid].name) >= 0){
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    if(!sorted_data[l].deleted && strcmp(sorted_data[l].name , name) == 0 ){
        printf("Book Name : %s\n" , sorted_data[l].name);
        printf("ID : %d , Quantity : %d\n" , sorted_data[l].id , sorted_data[l].quantity);
        puts("");
        system("PAUSE");
        return;
    }
    puts("Not Found!");
    system("PAUSE");
}

display_time(){
    system("cls");
    puts("Your Library (Time)..\n");
    for(int i = 0; i < index; i++){
        if(data[i].deleted)
            continue;
        printf("Book Name : %s\n" , data[i].name);
        printf("ID : %d , Quantity : %d\n" , data[i].id , data[i].quantity);
        puts("");
    }
    system("PAUSE");
}

save(){
    fptr = fopen("database.txt" , "w");
    bool did = 0;
    for(int i = 0; i < index; i++){
        if(data[i].deleted)
            continue;
        if(did)
            fprintf(fptr , "\n");
        did = true;
        fprintf(fptr , "%d\n%s\n%d" , data[i].id , data[i].name , data[i].quantity);
    }
    fclose(fptr);
}

