#ifndef ACCOUNT_H
#define ACCOUNT_H

#define UUID_STR_LEN 37
#define HASH_SIZE 100

typedef struct Account {
    char account_number[UUID_STR_LEN];
    double balance;
    struct Account* next; // Pointer to the next account in the list
} Account;

Account* account_create();
void account_deposit(Account* account, double amount);
void account_withdraw(Account* account, double amount);
double account_get_balance(const Account* account);
void account_destroy(Account* account);
void add_account(Account* account);
Account* find_account(const char* account_number);
void remove_account(const char* account_number);
void save_accounts(const char* filename);
void load_accounts(const char* filename);
void free_all_accounts();

#endif
