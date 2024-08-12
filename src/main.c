#include <stdio.h>
#include <stdlib.h>
#include "account.h"

void print_menu() {
    printf("\n");
    printf("********************************\n");
    printf("* Welcome to the Bank System!   *\n");
    printf("********************************\n");
    printf("* 1. Create Account              *\n");
    printf("* 2. Deposit                     *\n");
    printf("* 3. Withdraw                    *\n");
    printf("* 4. Check Balance               *\n");
    printf("* 5. Save Accounts               *\n");
    printf("* 6. Load Accounts               *\n");
    printf("* 7. Exit                        *\n");
    printf("********************************\n");
    printf("Please select an option: ");
}

void handle_create_account() {
    Account* account = account_create();
    if (account != NULL) {
        add_account(account);
        printf("Account created successfully!\n");
        printf("Account Number: %s\n", account->account_number);
    }
}

void handle_deposit(Account* account) {
    double amount;
    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);
    if (amount <= 0) {
        printf("Invalid amount. Deposit failed.\n");
        return;
    }
    account_deposit(account, amount);
    printf("Deposit successful. New balance: %.2f\n", account_get_balance(account));
}

void handle_withdraw(Account* account) {
    double amount;
    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);
    if (amount <= 0) {
        printf("Invalid amount. Withdrawal failed.\n");
        return;
    }
    if (amount > account_get_balance(account)) {
        printf("Insufficient funds!\n");
    } else {
        account_withdraw(account, amount);
        printf("Withdrawal successful. New balance: %.2f\n", account_get_balance(account));
    }
}

void handle_check_balance(const Account* account) {
    printf("Current balance: %.2f\n", account_get_balance(account));
}

int main() {
    int option;
    load_accounts("accounts.txt");

    while (1) {
        char account_number[UUID_STR_LEN];
        print_menu();
        scanf("%d", &option);

        Account* account = NULL;

        switch (option) {
        case 1:
            handle_create_account();
            break;
        case 2:
            printf("Enter account number: ");
            scanf("%s", account_number);
            account = find_account(account_number);
            if (account == NULL) {
                printf("No account found with that number. Please create an account first.\n");
                break;
            }
            handle_deposit(account);
            break;
        case 3:
            printf("Enter account number: ");
            scanf("%s", account_number);
            account = find_account(account_number);
            if (account == NULL) {
                printf("No account found with that number. Please create an account first.\n");
                break;
            }
            handle_withdraw(account);
            break;
        case 4:
            printf("Enter account number: ");
            scanf("%s", account_number);
            account = find_account(account_number);
            if (account == NULL) {
                printf("No account found with that number. Please create an account first.\n");
                break;
            }
            handle_check_balance(account);
            break;
        case 5:
            save_accounts("accounts.txt");
            printf("Accounts saved successfully.\n");
            break;
        case 6:
            load_accounts("accounts.txt");
            printf("Accounts loaded successfully.\n");
            break;
        case 7:
            free_all_accounts(); // Free all memory before exiting
            printf("Exiting. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid option. Please try again.\n");
        }
    }
}
