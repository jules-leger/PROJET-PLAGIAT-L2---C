#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct node {
    int data;
    struct node *next;
};

struct linked_list {
    struct node *head;
    struct node *tail;
};

void init(struct linked_list *list) {
    list->head = NULL;
    list->tail = NULL;
}

void insert_at_beginning(struct linked_list *list, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    if (list->tail == NULL) {
        list->tail = new_node;
    }
}

void insert_at_end(struct linked_list *list, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

void delete_at_beginning(struct linked_list *list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct node *temp = list->head;
    list->head = list->head->next;
    free(temp);
    if (list->head == NULL) {
        list->tail = NULL;
    }
}

void delete_at_end(struct linked_list *list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }
    if (list->head->next == NULL) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return;
    }
    struct node *temp = list->head;
    while (temp->next != list->tail) {
        temp = temp->next;
    }
    temp->next = NULL;
    free(list->tail);
    list->tail = temp;
}

void print_list(struct linked_list *list) {
    struct node *temp = list->head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int find_length(struct linked_list *list) {
    int length = 0;
    struct node *temp = list->head;
    while (temp != NULL) {
        temp = temp->next;
        length++;
    }
    return length;
}

void reverse_list(struct linked_list *list) {
    struct node *current = list->head;
    struct node *prev = NULL;
    struct node *next;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->tail = list->head;
    list->head = prev;
}

void sort_list(struct linked_list *list) {
    struct node *temp1 = list->head;
    struct node *temp2;
    int temp;
    while (temp1 != NULL) {
        temp2 = temp1->next;
        while (temp2 != NULL) {
            if (temp1->data > temp2->data) {
                temp = temp1->data;
                temp1->data = temp2->data;
                temp2->data = temp;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}

void insert_at_position(struct linked_list *list, int data, int position) {
    if (position < 0 || position > find_length(list)) {
        printf("Invalid position.\n");
        return;
    }
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    if (position == 0) {
        new_node->next = list->head;
        list->head = new_node;
        if (list->tail == NULL) {
            list->tail = new_node;
        }
        return;
    }
    struct node *temp = list->head;
    for (int i = 0; i < position - 1; i++) {
        temp = temp->next;
    }
    new_node->next = temp->next;
    temp->next = new_node;
}

int main() {
    struct linked_list list;
    init(&list);
    int choice, data;
    while (1) {
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Delete at beginning\n");
        printf("4. Delete at end\n");
        printf("5. Print list\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the data: ");
                scanf("%d", &data);
                insert_at_beginning(&list, data);
                break;
            case 2:
                printf("Enter the data: ");
                scanf("%d", &data);
                insert_at_end(&list, data);
                break;
            case 3:
                delete_at_beginning(&list);
                break;
            case 4:
                delete_at_end(&list);
                break;
            case 5:
                print_list(&list);
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    int n, data;
    printf("Enter the number of elements you want to add to the list: ");
    scanf("%d", &n);
    srand(time(0)); // initialisation de la fonction rand
    for (int i = 0; i < n; i++) {
        data = rand() % 100; // génère un nombre aléatoire entre 0 et 99
        insert_at_end(&list, data);
    }
    printf("Original list: ");
    print_list(&list);

    printf("\nReversed list: ");
    reverse_list(&list);
    print_list(&list);

    printf("\nSorted list: ");
    sort_list(&list);
    print_list(&list);

    printf("\nInserting element at position 3: ");
    insert_at_position(&list, 200, 3);
    print_list(&list);

    printf("\nDeleting first element: ");
    delete_at_beginning(&list);
    print_list(&list);

    printf("\nDeleting last element: ");
    delete_at_end(&list);
    print_list(&list);

    printf("\nThe length of the list is: %d\n", find_length(&list));

    return 0;
}
