/*
 This program returns the rightmost set bit startubg count from right gradually towards left. 
*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;


int PosRightMostSetBit(int n) {
        int pos = 1;

        while(n) {
            if (n & 1) {
                return pos;
            }
            n = n >> 1;
            pos++;
        }
}

int main(){
    int n = 28;
    cout << n << " in binary is  " << bitset<8>(n) << endl;

    cout << "The position of right most set bit " << PosRightMostSetBit(n) << endl;
    return 0;
}
