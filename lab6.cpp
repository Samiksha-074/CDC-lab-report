#include <iostream>
#include <cstring>
using namespace std;
const int MAX_PRODUCTIONS = 20;
const int MAX_SYMBOLS = 100;
char terminals[MAX_SYMBOLS] = {};
int no_t;
char non_terminals[MAX_SYMBOLS] = {};
int no_nt;
char goto_table[MAX_PRODUCTIONS][MAX_SYMBOLS];
char follow[MAX_PRODUCTIONS][MAX_SYMBOLS];
char first[MAX_PRODUCTIONS][MAX_SYMBOLS];
struct State {
    int prod_count;
    char prod[MAX_PRODUCTIONS][MAX_SYMBOLS];
};
void add_dots(State *I) {
    for (int i = 0; i < I->prod_count; i++) {
        for (int j = MAX_SYMBOLS - 1; j > 3; j--)
            I->prod[i][j] = I->prod[i][j - 1];
        I->prod[i][3] = '.';
    }
}
void augument(State *S, State *I) {
    if (I->prod[0][0] == 'S')
        strcpy(S->prod[0], "Z->.S");
    else
        sprintf(S->prod[0], "S->.%c", I->prod[0][0]);
    S->prod_count++;
}
void get_prods(State *I) {
    cout << "Enter the number of productions:\n";
    cin >> I->prod_count;
    cout << "Enter the number of non terminals:" << endl;
    cin >> no_nt;
    cout << "Enter the non terminals one by one:" << endl;
    for (int i = 0; i < no_nt; i++)
        cin >> non_terminals[i];
    cout << "Enter the number of terminals:" << endl;
    cin >> no_t;
    cout << "Enter the terminals (single lettered) one by one:" << endl;
    for (int i = 0; i < no_t; i++)
        cin >> terminals[i];
    cout << "Enter the productions one by one in form (S->ABc):\n";
    for (int i = 0; i < I->prod_count; i++)
        cin >> I->prod[i];
}

bool is_non_terminal(char a) {
    return (a >= 'A' && a <= 'Z');
}

bool in_state(State *I, char *a) {
    for (int i = 0; i < I->prod_count; i++) {
        if (!strcmp(I->prod[i], a))
            return true;
    }
    return false;
}
char char_after_dot(char a[MAX_SYMBOLS]) {
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] == '.')
            return a[i + 1];
    }
    return '\0';
}

char* move_dot(char b[MAX_SYMBOLS]) {
    static char a[MAX_SYMBOLS];
    strcpy(a, b);
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] == '.') {
            swap(a[i], a[i + 1]);
            break;
        }
    }
    return a;
}

bool same_state(State *I0, State *I) {
    if (I0->prod_count != I->prod_count)
        return false;
    for (int i = 0; i < I0->prod_count; i++) {
        bool found = false;
        for (int j = 0; j < I->prod_count; j++) {
            if (strcmp(I0->prod[i], I->prod[j]) == 0) {
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}

void closure(State *I, State *I0) {
    for (int i = 0; i < I0->prod_count; i++) {
        char a = char_after_dot(I0->prod[i]);
        if (is_non_terminal(a)) {
            for (int j = 0; j < I->prod_count; j++) {
                if (I->prod[j][0] == a && !in_state(I0, I->prod[j])) {
                    strcpy(I0->prod[I0->prod_count], I->prod[j]);
                    I0->prod_count++;
                }
            }
        }
    }
}

void goto_state(State *I, State *S, char a) {
    int time = 1;
    for (int i = 0; i < I->prod_count; i++) {
        if (char_after_dot(I->prod[i]) == a) {
            if (time == 1)
                time++;
            strcpy(S->prod[S->prod_count], move_dot(I->prod[i]));
            S->prod_count++;
        }
    }
}

void print_prods(State *I) {
    for (int i = 0; i < I->prod_count; i++)
        cout << I->prod[i] << endl;
    cout << endl;
}

bool in_array(char a[MAX_SYMBOLS], char b) {
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] == b)
            return true;
    }
    return false;
}

char* chars_after_dots(State *I) {
    static char a[MAX_SYMBOLS] = {};
    for (int i = 0; i < I->prod_count; i++) {
        if (!in_array(a, char_after_dot(I->prod[i])) && char_after_dot(I->prod[i]) != '\0') {
            a[strlen(a)] = char_after_dot(I->prod[i]);
        }
    }
    return a;
}

void cleanup_prods(State *I) {
    for (int i = 0; i < I->prod_count; i++)
        strcpy(I->prod[i], "");
    I->prod_count = 0;
}

int return_index(char a) {
    for (int i = 0; i < no_t; i++) {
        if (terminals[i] == a)
            return i;
    }
    for (int i = 0; i < no_nt; i++) {
        if (non_terminals[i] == a)
            return no_t + i;
    }
    return -1;
}

void print_shift_table(int state_count) {
    cout << "********Shift Actions*********" << endl << endl;
    cout << "\t";
    for (int i = 0; i < no_t; i++)
        cout << terminals[i] << "\t";
    cout << endl;
    for (int i = 0; i < state_count; i++) {
        int arr[MAX_SYMBOLS] = {-1};
        for (int j = 0; j < state_count; j++) {
            if (goto_table[i][j] != '~') {
                arr[return_index(goto_table[i][j])] = j;
            }
        }
        cout << "I" << i << "\t";
        for (int j = 0; j < no_t + no_nt; j++) {
            if (arr[j] == -1)
                cout << "\t";
            else
                cout << "S" << arr[j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    State init, temp, temp1;
    int state_count = 1;
    get_prods(&init);
    temp = init;
    temp1 = temp;
    add_dots(&init);
    for (int i = 0; i < MAX_PRODUCTIONS; i++)
        for (int j = 0; j < MAX_SYMBOLS; j++)
            goto_table[i][j] = '~';
    State I[50];
    augument(&I[0], &init);
    closure(&init, &I[0]);
    cout << "\nI0:\n";
    print_prods(&I[0]);
    char characters[MAX_SYMBOLS] = {};
    for (int i = 0; i < state_count; i++) {
        char characters[MAX_SYMBOLS] = {};
        for (int z = 0; z < I[i].prod_count; z++)
            if (!in_array(characters, char_after_dot(I[i].prod[z])))
                characters[strlen(characters)] = char_after_dot(I[i].prod[z]);

        for (int j = 0; j < strlen(characters); j++) {
            goto_state(&I[i], &I[state_count], characters[j]);
            closure(&init, &I[state_count]);
            int flag = 0;
            for (int k = 0; k < state_count - 1; k++) {
                if (same_state(&I[k], &I[state_count])) {
                    cleanup_prods(&I[state_count]);
                    flag = 1;
                    goto_table[i][k] = characters[j];
                    break;
                }
            }
            if (flag == 0) {
                state_count++;
                goto_table[i][state_count - 1] = characters[j];
            }
        }
    }
    print_shift_table(state_count);
    return 0;
}