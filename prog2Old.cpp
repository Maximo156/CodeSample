
#include <iostream>
#include <limits.h>
#include <algorithm> 

using namespace std;
int main(){
    int n;
    int m;
    int h;

    cin >> n;
    cin >> m;
    cin >> h;

    long weights[n][n];
    int from;
    int to;
    long weight;

    for(int i = 0; i< n; i++){
        for(int k = 0; k< n; k++){
            weights[i][k] = LONG_MAX;
        }
    }

    for(int i = 0; i< m; i++){
        cin >> from;
        cin >> to;
        cin >> weight;
        weights[from-1][to-1] = weight;
    }

    if(h == 0){
        for(int i = 0; i<n; i++){
            for(int k = 0; k<n-1; k++){
                if(i==k)
                    cout << "0 ";
                else
                    cout <<  "x ";
            }
            if(i==n-1)
                cout << "0 " << endl;
            else
                cout <<  "x" << endl;
        }
        return 0;
    }

    long *old = (long int*)malloc(sizeof(long)*n*n);
    long *cur = (long int*)malloc(sizeof(long)*n*n);
    for(int i = 0; i< n; i++){
        for(int k = 0; k< n; k++){
            if(i == k){
                old[i*n+k] = LONG_MAX; 
            }
            else{
                old[i*n+k] = weights[i][k];
            }
        }
    }
    int len;
    for(len = 2; len < h+1; len*=2){
        for(int i = 0; i<n; i++){
            for(int k = 0; k<n; k++){
                cur[i*n+k] = LONG_MAX;
                for(int m = 0; m<n; m++){
                    if(old[i*n+m] != LONG_MAX && LONG_MAX != old[m*n+k])
                        cur[i*n+k] = min(cur[i*n+k], old[i*n+m]+old[m*n+k]);
                } 
            }
        }
        long *tmp = old;
        old = cur;
        cur = tmp;
    }

    for(len=len/2+1 ; len < h+1; len++){
        for(int i = 0; i<n; i++){
            for(int k = 0; k<n; k++){
                cur[i*n+k] = LONG_MAX;
                for(int m = 0; m<n; m++){
                    if(old[i*n+m] != LONG_MAX && LONG_MAX != weights[m][k])
                        cur[i*n+k] = min(cur[i*n+k], old[i*n+m]+weights[m][k]);
                } 
            }
        }
        long *tmp = old;
        old = cur;
        cur = tmp;
    }

    int index = h;
    for(int i = 0; i<n; i++){
        for(int k = 0; k<n-1; k++){
            if(old[i*n+k] == LONG_MAX)
                cout << "x ";
            else
                cout << old[i*n+k]<< " ";
        }
        if(old[i*n+n-1]== LONG_MAX)
                cout << "x " << endl;
        else
            cout << old[i*n+n-1]<< endl;
    }
    free(cur);
    free(old);
}