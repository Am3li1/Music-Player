#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char song[100];
    struct Node* next;
};

int itemCount = 0;
struct Node* top = NULL;

void push(char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newNode->song, data);
    newNode->next = top;
    top = newNode;
}

void tofile(char a[]) {
    FILE* f1 = fopen("playlist.txt", "a");
    if (f1 == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f1, "%s\n", a);
    fclose(f1);
}

void add_node(struct Node** start) {
    itemCount += 1;
    char a[100];

    if (*start == NULL) {
        // The list is empty, create the first node
        *start = (struct Node*)malloc(sizeof(struct Node));
        if (*start == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        struct Node* first = *start;
        first->next = NULL;

        printf("Enter Song name: ");
        scanf("%s", a);
        strcpy(first->song, a);
        tofile(a);
        printf("Song added: %s\n", a);
    } else {
        while ((*start)->next != NULL) {
            start = &((*start)->next);
        }

        *start = (struct Node*)malloc(sizeof(struct Node));
        if (*start == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        struct Node* last = *start;
        last->next = NULL;

        printf("Enter Song name: ");
        scanf("%s", a);
        strcpy(last->song, a);
        tofile(a);
        printf("Song added: %s\n", a);
    }
}


void delete_song(struct Node** start) {
    char a[100];
    printf("Enter the song name to delete: ");
    scanf("%s", a);
    struct Node* current = *start;
    struct Node* previous = NULL;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->song, a) == 0) {
            if (previous == NULL) {
                *start = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            itemCount -= 1;
            found = 1;
            printf("Song '%s' has been deleted.\n", a);
            break;
        }
        previous = current;
        current = current->next;
    }

    if (!found) {
        printf("Song '%s' not found.\n", a);
    }
}

void del_node(struct Node** start) {
    if (*start == NULL) {
        printf("Playlist is empty. Nothing to delete.\n");
        return;
    }
    struct Node* current = *start;
    struct Node* previous = NULL;

    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        free(current);
        *start = NULL;
    } else {
        previous->next = NULL;
        free(current);
    }

    itemCount -= 1;
    printf("Deleted\n");
}

void printlist(struct Node* start) {
    if (start == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    printf("Playlist Name:\n");
    while (start != NULL) {
        printf("%s\n", start->song);
        start = start->next;
    }
}

void count_nodes(struct Node* start) {
    printf("Total songs: %d\n", itemCount);
}

void search1(struct Node* start) {
    char song[100];
    printf("Enter song to be searched: ");
    scanf("%s", song);
    int flag = 0;
    while (start != NULL) {
        if (strcmp(start->song, song) == 0) {
            printf("Song Found\n");
            flag++;
            break;
        } else {
            start = start->next;
        }
    }
    if (flag == 0) {
        printf("Song Not found\n");
    }
}

void play(struct Node* start) {
    char song[100];
    printlist(start);
    printf("Choose a song you wish to play: ");
    scanf("%s", song);
    int flag = 0;
    while (start != NULL) {
        if (strcmp(start->song, song) == 0) {
            printf("Now Playing... %s\n", song);
            flag++;
            push(song);
            break;
        } else {
            start = start->next;
        }
    }
    if (flag == 0) {
        printf("Song Not found\n");
    }
}

void recent() {
    if (top == NULL) {
        printf("No recently played tracks.\n");
        return;
    }
    printf("Recently played tracks:\n");
    struct Node* top1 = top;
    while (top1 != NULL) {
        printf("%s\n", top1->song);
        top1 = top1->next;
    }
}

void topelement() {
    if (top == NULL) {
        printf("No last played tracks.\n");
        return;
    }
    printf("Last Played Song: %s\n", top->song);
}

int main() {
    int choice;
    struct Node* start = NULL;
    struct Node* hold = NULL;
    start = (struct Node*)malloc(sizeof(struct Node));
    printf("\t\t\t*WELCOME*\n");
    printf("**Please use '_' for space.\n");
    printf("\nEnter your playlist name: ");
    scanf("%s", start->song);
    start->next = NULL;
    hold = start;

    do {
        printf("\n1. Add New Song\n2. Delete Song\n3. Display Entered Playlist\n4. Total Songs\n5. Search Song\n6. Play Song\n7. Recently Played List\n8. Last Played\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_node(&start);
                break;
            case 2:
                delete_song(&start);
                break;
            case 3:
                printlist(start);
                break;
            case 4:
                count_nodes(start);
                break;
            case 5:
                search1(start);
                break;
            case 6:
                play(start);
                break;
            case 7:
                recent();
                break;
            case 8:
                topelement();
                break;
            case 9:
                printf("Thank you for using the program!\n");
                exit(0);
        }
    } while (choice != 9);

    while (start != NULL) {
        struct Node* temp = start;
        start = start->next;
        free(temp);
    }

    return 0;
}
