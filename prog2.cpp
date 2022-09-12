#include <iostream>
#include <limits.h>
#include <algorithm> 
using namespace std;

void findPaths(long* res, long* weights, int h, int n){ //Finds the lowest weight walk of length h between all nodes in a graph O(n^3log(h))
    
    long *old = (long int*)malloc(sizeof(long)*n*n);
    long *cur = (long int*)malloc(sizeof(long)*n*n);
    for(int i = 0; i< n; i++){               //Sets up an array storing the weights of a path of length 1 between each node
        for(int k = 0; k< n; k++){
            if(i == k) old[i*n+k] = LONG_MAX; 
            else old[i*n+k] = weights[i*n+k]; 
        }
    }
    int len;
    for(len = 2; len < h+1; len*=2){ //If there is a path from node a to b, and a path from node b to c, and the sum of those paths is less than the current path from a to c, use that
        for(int i = 0; i<n; i++){    // path between a and c. Do this for all nodes a,b, and c. Repeat for all power of 2 path lengths between 2 and h.
            for(int k = 0; k<n; k++){
                cur[i*n+k] = LONG_MAX;
                for(int m = 0; m<n; m++){
                    if(old[i*n+m] != LONG_MAX && LONG_MAX != old[m*n+k]) cur[i*n+k] = min(cur[i*n+k], old[i*n+m]+old[m*n+k]);
                } 
            }
        }
        long *tmp = old;
        old = cur;
        cur = tmp;
    }
    long *resNew = (long int*)malloc(sizeof(long)*n*n);
    if(h-(len/2) == 0){          //If h was a power of 2, the previous loops found the answer, therefore copy the result into the res array and return
        for(int i = 0; i<n; i++){
            for(int k = 0; k<n; k++){
                res[i*n+k] = old[i*n+k];
            }
        }
        free(resNew);
        free(old);
        free(cur);
        return;
    }
    findPaths(resNew, weights, h-(len/2), n); //If h was not a power of 2, this alg needs to be done again on the distance between the highest power of 2 less than h and h.
    for(int i = 0; i<n; i++){     //If any shorter paths are found by this recursion, use them instead
        for(int k = 0; k<n; k++){
            res[i*n+k] = LONG_MAX;
            for(int m = 0; m<n; m++){
                if(old[i*n+m] != LONG_MAX && LONG_MAX != resNew[m*n+k]) res[i*n+k] = min(res[i*n+k], old[i*n+m]+resNew[m*n+k]);
            } 
        }
    }
    free(resNew);
    free(old);
    free(cur);
}

int main(){
    int numNodes;
    int numPaths;
    int lenOfWalk;
    cin >> numNodes;
    cin >> numPaths;
    cin >> lenOfWalk;
    long weights[numNodes][numNodes];
    int from;
    int to;
    long weight;
    for(int i = 0; i< numNodes; i++){     //set up adjacency array
        for(int k = 0; k< numNodes; k++){
            weights[i][k] = LONG_MAX;
        }
    }
    for(int i = 0; i< numPaths; i++){ //populate adjacency array
        cin >> from;
        cin >> to;
        cin >> weight;
        weights[from-1][to-1] = weight;
    }
    if(lenOfWalk == 0){ // deal with trivial case of a 0 lenth walk
        for(int i = 0; i<numNodes; i++){
            for(int k = 0; k<numNodes-1; k++){
                if(i==k) cout << "0 ";
                else cout <<  "x ";
            }
            if(i==numNodes-1) cout << "0 " << endl;
            else cout <<  "x" << endl;
        }
        return 0;
    }
    long* res = (long int*)malloc(sizeof(long)*numNodes*numNodes); 
    findPaths(res, (long*)(&weights),lenOfWalk, numNodes); //Generate answers
    for(int i = 0; i<numNodes; i++){ //display answers
        for(int k = 0; k<numNodes-1; k++){
            if(res[i*numNodes+k] == LONG_MAX) cout << "x ";
            else cout << res[i*numNodes+k]<< " ";
        }
        if(res[i*numNodes+numNodes-1]== LONG_MAX) cout << "x " << endl;
        else cout << res[i*numNodes+numNodes-1]<< endl;
    }
    free(res);
}