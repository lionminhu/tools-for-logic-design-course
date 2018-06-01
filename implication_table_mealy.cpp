// First line of input is
// (n := initial number of states) (in := number of inputs)
// Next `n` inputs have `in` next state values from 0th input value to (n-1)th input value
// Next `n` inputs have `in` output values from 0th input value to (n-1)th input value
//
// Output shows the results of state reduction

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 100;
const int MAX_IN = 10;

typedef struct state{
    int out[MAX_IN];
    int next[MAX_IN];
}state;

state S[MAX_N + 1];
int n, in;
bool T[MAX_N][MAX_N];
int C[MAX_N];

void initTable(){
    for(int col = 0; col <= n - 1; col++)
        for(int row = col; row <= n - 1; row++)
            T[row][col] = true;

    for(int col = 0; col <= n - 2; col++)
        for(int row = col + 1; row <= n - 1; row++)
            for(int i = 0; i < in; i++)
                if(S[col].out[i] != S[row].out[i]){
                    T[row][col] = false;
                    break;
                }
}

bool pass(){
    bool changed = false;
    for(int col = 0; col <= n - 2; col++)
        for(int row = col + 1; row <= n - 1; row++)
            if(T[row][col])
                for(int i = 0; i < in; i++){
                    int nextRow = max(S[row].next[i], S[col].next[i]);
                    int nextCol = min(S[row].next[i], S[col].next[i]);
                    if(!T[nextRow][nextCol]){
                        changed = true;
                        T[row][col] = false;
                        break;
                    }
                }
    return changed;
}

void printCombined(){
    for(int i = 0; i < n; i++)
        C[i] = i;
    for(int col = 0; col <= n - 2; col++)
        for(int row = col + 1; row <= n - 1; row++)
            if(T[row][col]){
                C[row] = C[col] = min(C[row], C[col]);
                printf("%d combined with %d into %d'\n", row, col, C[row]);
            }
    int cnt = 0;
    for(int i = 0; i < n; i++)
        if(C[i] == i)
            cnt++;
    printf("Total number of states after reduction: %d\n", cnt);
}

int main(){
    scanf("%d %d", &n, &in);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < in; j++)
            scanf("%d", &S[i].next[j]);
        for(int j = 0; j < in; j++)
            scanf("%d", &S[i].out[j]);
    }
    initTable();
    while(pass());
    printCombined();
    return 0;
}
