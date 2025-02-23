#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char* name;
    char* action;
    int shares;
} Transaction;

void printTransactions(double m, int k, int d, char* name[], int owned[], double prices[][5]) {
    Transaction* transactions = malloc(2 * k * sizeof(Transaction));
    int count = 0;

    // Process SELL transactions
    for (int i = 0; i < k; ++i) {
        double current = prices[i][4];
        double max_p = current;
        for (int j = 0; j < 5; ++j) {
            if (prices[i][j] > max_p) {
                max_p = prices[i][j];
            }
        }
        if (current == max_p && owned[i] > 0) {
            transactions[count].name = name[i];
            transactions[count].action = "SELL";
            transactions[count].shares = owned[i];
            ++count;
        }
    }

    // Process BUY transactions
    double available = m;
    for (int i = 0; i < k; ++i) {
        double current = prices[i][4];
        double min_p = current;
        for (int j = 0; j < 5; ++j) {
            if (prices[i][j] < min_p) {
                min_p = prices[i][j];
            }
        }
        if (current == min_p) {
            if (current <= available + 1e-9) { // Handle floating point precision
                int shares = (int)(available / current);
                if (shares > 0) {
                    transactions[count].name = name[i];
                    transactions[count].action = "BUY";
                    transactions[count].shares = shares;
                    available -= shares * current;
                    ++count;
                }
            }
        }
    }

    // Output the transactions
    printf("%d\n", count);
    for (int i = 0; i < count; ++i) {
        printf("%s %s %d\n", transactions[i].name, transactions[i].action, transactions[i].shares);
    }

    free(transactions);
}

int main(void) {
    double _m;
    scanf("%lf", &_m);
    
    int _k;
    scanf("%d", &_k);
    
    int _d;
    scanf("%d", &_d);
    
    char* _name[_k];
    int _owned[_k];
    double _prices[_k][5];
    
    for(int _i = 0; _i < _k; _i++) { 
        _name[_i] = (char *)malloc(10240 * sizeof(char));
        scanf("%s", _name[_i]);
        scanf("%d", &_owned[_i]);
        for(int _j = 0; _j<5; _j++) {
            scanf("%lf", &_prices[_i][_j]);
        }        
    }

    printTransactions(_m, _k, _d, _name, _owned, _prices);
    
    return 0;
}
