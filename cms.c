#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void addContact();
void listAllContact();
void searchContact();
void editContact();
void deleteContact();

struct contact {
  long ph;
  char name[20], add[20], email[30];
}list;

char query[20], name[20];
FILE * fp, * ft;
int i, n, ch, l, found;

int main() {
  main:
    system("clear");
    /* ************Main menu ***********************  */
    printf("\n\t **** Welcome to Contact Management System ****");
    printf("\n\n\n\t\tMAIN MENU\n\t*===============================*");
    printf("\n\t| %30s", "[1] Add a new Contact \t|");
    printf("\n\t| %30s", "[2] List all Contacts \t|");
    printf("\n\t| %30s", "[3] Search for contact\t|");
    printf("\n\t| %30s", "[4] Edit a Contact    \t|");
    printf("\n\t| %30s", "[5] Delete a Contact  \t|");
    printf("\n\t| %20s","[0] Exit   \t\t|");
    printf("\n\t*===============================*\n");
    printf("Enter the choice:");
    scanf("%d", & ch);
    switch (ch){
      case 0:
          printf("\n\n\t\tAre you sure you want to exit?");
      break;
      case 1:
        /* *********************Add new contacts************  */
        addContact();
      break;
      case 2:
          /* *********************list of contacts*************************  */
        listAllContact();
      break;
      /* *******************search contacts**********************  */
      case 3:
        searchContact();
      break;
      case 4:
      /* *********************edit contacts*********************** */
        editContact();
      break;
      case 5:
    /* ********************delete contacts********************* */
        deleteContact();
      break;
      default:
        printf("Invalid choice");
      break;
    }
    printf("\n\n\n..::Enter the Choice:\n\n\t[1] Main Menu\t\t[0] Exit\n");
    scanf("%d", & ch);
    switch(ch){
      case 1:
        goto main;
      case 0:
      break;
      default:
        printf("Invalid choice");
      break;
    }
  return 0;
}

void addContact(){
    system("clear");
    fp = fopen("contact.dll", "a");
    for (;;){
        fflush(stdin);
        printf("To exit enter blank space in the name input\nName (Use identical):");
        scanf("%[^\n]", list.name);
        if (strncmp(list.name, "",2) == 0 || strncmp(list.name, " ",2) == 0){
            break;
        }
        fflush(stdin);
        printf("Phone:");
        scanf("%ld", & list.ph);
        fflush(stdin);
        printf("Address:");
        scanf("%[^\n]", & list.add);
        fflush(stdin);
        printf("Email address:");
        scanf("%[^\n]", & list.email);
        fflush(stdin);
        fgets(list.email, sizeof(list), fp);
        printf("\n");
        fwrite( & list, sizeof(list), 1, fp);
    }
    fclose(fp);
}

void listAllContact(){
  system("clear");
  printf("\n|------------------------\t LIST OF CONTACTS \t------------------------|\n");
  printf("|%79s|\n", "");
  for (i = 97; i <= 122; i = i + 1){
      fp = fopen("contact.dll", "r");
      fflush(stdin);
      found = 0;
      while (fread( & list, sizeof(list), 1, fp) == 1){
          if (list.name[0] == i || list.name[0] == i - 32){
             if(found-1 == 0){
                printf("|.............................................................                  |\n");

              }
              printf("|\t\tName\t: %30s \t\t\t|\n|\t\tPhone\t: %30d \t\t\t|\n|\t\tAddress\t: %30s \t\t\t|\n|\t\tEmail\t: %30s \t\t\t|\n", list.name, list.ph, list.add, list.email);
              found++;
          }
      }
      if (found != 0){
          printf("|_____________________________________________________________ [%c]-(%d) _________|\n", i - 32, found);
          getc(fp);
      }
      fclose(fp);
  }
}

void searchContact(){
   system("clear");
    do{
      found = 0;
      printf("\n\n\t..::CONTACT SEARCH\n\t===========================\n\t..::Name of contact to search: ");
      fflush(stdin);
      scanf("%[^\n]", & query);
      l = strlen(query);
      fp = fopen("contact.dll", "r");
      system("clear");
      printf("\n\n..::Search result for '%s' \n===================================================\n", query);
      while (fread( & list, sizeof(list), 1, fp) == 1){
        for (i = 0; i <= l; i++){
            name[i] = list.name[i];
        }
        name[l] = '\0';
        if (strcmp(name, query) == 0){
          printf("\n..::Name\t: %s\n..::Phone\t: %ld\n..::Address\t: %s\n..::Email\t: %s\n", list.name, list.ph, list.add, list.email);
          found++;
          if (found % 4 == 0){
            printf("..::Press any key to continue...");
            getc(fp);
          }
        }
      }
      if (found == 0){
          printf("\n..::No match found!");
      }else{
        printf("\n..::%d match(s) found!", found);
      }
      fclose(fp);
      printf("\n ..::Try again?\n\n\t[1] Yes\t\t[0] No\n\t");
      scanf("%d", & ch);
    }while (ch == 1);
}

void editContact(){
    system("clear");
    fp = fopen("contact.dll", "r");
    ft = fopen("temp.dat", "w");
    fflush(stdin);
    printf("..::Edit contact\n===============================\n\n\t..::Enter the name of contact to edit:");
    scanf("%[^\n]", name);
    while (fread( & list, sizeof(list), 1, fp) == 1){
      if (strcmp(name, list.name) != 0){
        fwrite( & list, sizeof(list), 1, ft);
      }
    }
    fflush(stdin);
    printf("\n\n..::Editing '%s'\n\n", name);
    printf("..::Name(Use identical):");
    scanf("%[^\n]", & list.name);
    fflush(stdin);
    printf("..::Phone:");
    scanf("%ld", & list.ph);
    fflush(stdin);
    printf("..::address:");
    scanf("%[^\n]", & list.add);
    fflush(stdin);
    printf("..::email address:");
    scanf("%[^\n]", & list.email);
    fgets(list.email, sizeof(list), fp);
    printf("\n");
    fwrite( & list, sizeof(list), 1, ft);
    fclose(fp);
    fclose(ft);
    remove("contact.dll");
    rename("temp.dat", "contact.dll");
}

void deleteContact(){
    system("clear");
    fflush(stdin);
    printf("\n\n\t..::DELETE A CONTACT\n\t==========================\n\t..::Enter the name of contact to delete:");
    scanf("%[^\n]", & name);
    fp = fopen("contact.dll", "r");
    ft = fopen("temp.dat", "w");
    while (fread( & list, sizeof(list), 1, fp) != 0){
      if (strcmp(name, list.name) != 0){
        fwrite( & list, sizeof(list), 1, ft);
      }
    }
    fclose(fp);
    fclose(ft);
    remove("contact.dll");
    rename("temp.dat", "contact.dll");
}
