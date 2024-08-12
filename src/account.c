#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "account.h"
#include "uuid4.h"

static Account* hash_table[HASH_SIZE] = {NULL};

unsigned int hash(const char* account_number) {
    unsigned long int hash = 5381;
    int c;

    while ((c = *account_number++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % HASH_SIZE;
}

Account* account_create() {
    Account* new_account = malloc(sizeof(Account));
    if (new_account == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    UUID4_STATE_T state;
    UUID4_T uuid;

    uuid4_seed(&state);
    uuid4_gen(&state, &uuid);

    char buffer[UUID4_STR_BUFFER_SIZE];
    if (!uuid4_to_s(uuid, buffer, sizeof(buffer))) {
        perror("The UUID could not be converted to a string");
        exit(EXIT_FAILURE);
    }

    snprintf(new_account->account_number, sizeof(new_account->account_number), "%s", buffer);
    new_account->balance = 0.0;
    new_account->next = NULL;

    return new_account;
}

void account_deposit(Account* account, double amount) {
    if (account == NULL || amount <= 0) {
        printf("Invalid account or deposit amount.\n");
        return;
    }
    account->balance += amount;
}

void account_withdraw(Account* account, double amount) {
    if (account == NULL || amount <= 0) {
        printf("Invalid account or withdrawal amount.\n");
        return;
    }
    if (amount > account->balance) {
        printf("Insufficient funds\n");
        return;
    }
    account->balance -= amount;
}

double account_get_balance(const Account* account) {
    if (account == NULL) {
        printf("Account is NULL\n");
        return 0.0;
    }
    return account->balance;
}

void account_destroy(Account* account) {
    if (account != NULL) {
        free(account);
    }
}

void add_account(Account* account) {
    if (account == NULL) return;

    unsigned int index = hash(account->account_number);
    account->next = hash_table[index];
    hash_table[index] = account;
}

Account* find_account(const char* account_number) {
    unsigned int index = hash(account_number);
    Account* current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->account_number, account_number) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void remove_account(const char* account_number) {
    unsigned int index = hash(account_number);
    Account* current = hash_table[index];
    Account* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->account_number, account_number) == 0) {
            if (prev == NULL) {
                hash_table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void save_accounts(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        Account* current = hash_table[i];
        while (current != NULL) {
            fprintf(file, "%s %f\n", current->account_number, current->balance);
            current = current->next;
        }
    }

    fclose(file);
}


void load_accounts(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        if (errno != ENOENT) {
            perror("Failed to open file for reading");
        }
        return;
    }

    char account_number[UUID_STR_LEN];
    double balance;
    while (fscanf(file, "%s %lf", account_number, &balance) != EOF) {
        Account* existing_account = find_account(account_number);
        if (existing_account != NULL) {
            existing_account->balance = balance;
        } else {
            Account* new_account = malloc(sizeof(Account));
            if (new_account == NULL) {
                perror("Memory allocation failed");
                fclose(file);
                exit(EXIT_FAILURE);
            }

            strncpy(new_account->account_number, account_number, UUID_STR_LEN);
            new_account->balance = balance;
            new_account->next = hash_table[hash(account_number)];
            hash_table[hash(account_number)] = new_account;
        }
    }

    fclose(file);
}


void free_all_accounts() {
    for (int i = 0; i < HASH_SIZE; i++) {
        Account* current = hash_table[i];
        while (current != NULL) {
            Account* to_free = current;
            current = current->next;
            free(to_free);
        }
        hash_table[i] = NULL;
    }
}
