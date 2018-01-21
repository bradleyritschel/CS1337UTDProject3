//
//  main.cpp
//  bsr160130_Project3
//
//  Created by Bradley Ritschel on 10/14/17.
//  Copyright © 2017 Bradley Ritschel. All rights reserved.
//
// program to generate odd-sized "magic squares"


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <tgmath.h>

using namespace std;

int GetNumberOfDigits (unsigned i) // get the number of digits in an element
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1; // take log base 10 of the argument and add 1
}

// A function to generate odd sized magic squares
void generateSquare(unsigned short n)
{
    int magicSquare[n][n]; // declare magic square 2 dimensional array
    
    // set all slots as 0
    memset(magicSquare, 0, sizeof(magicSquare));
    
    // Initialize position for 1
    int i = n/2;
    int j = n-1;
    
    // One by one put all values in magic square
    for (int num=1; num <= n*n; )
    {
        if (i==-1 && j==n) //3rd condition
        {
            j = n-2;
            i = 0;
        }
        else
        {
            //1st condition helper if next number
            // goes to out of square's right side
            if (j == n)
                j = 0;
            //1st condition helper if next number
            // is goes to out of square's upper side
            if (i < 0)
                i=n-1;
        }
        if (magicSquare[i][j]) //2nd condition
        {
            j -= 2;
            i++;
            continue;
        }
        else
            magicSquare[i][j] = num++; //set number
        
        j++; i--; //1st condition
    }
    
    // write magic square to file
    
    ofstream outputFile; //declare object
    outputFile.open("output.txt", ios::app); //open and associate file
    
    if (!outputFile) {
        cout << "Unable to create file";
        exit(1);   // call system to stop if file did not open
    }

    outputFile << "The Magic Sum: " << (n*(n*n+1)/2) << endl << "The Magic Square for n = " << n << endl;
    for(i=0; i<n; i++) // for each row
    {
        for(j=0; j<n; j++) { // for each column
            outputFile << magicSquare[i][j];
            for(int k = 0; k < 7 - GetNumberOfDigits(magicSquare[i][j]); k++) //evenly space elements
                outputFile << " ";
        }
        outputFile << endl;
    }
    cout << "File written successfully." << endl;
    outputFile << endl; // write blank line to start next contestant report
    outputFile.close();// close reportFile
}

int enterNumber(unsigned short &number, const int inclusiveMin, const int inclusiveMax) { //validation for user input
    //We are taking a string in for ease of use. Then, people can enter 10,000 with a comma instead of 10000
    cin >> number;
    
    while (cin.fail() || number < inclusiveMin || number > inclusiveMax) {
        cout << "You must enter a number between and including " << inclusiveMin << " and " << inclusiveMax << " " << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> number;
    }
    return number;
}

unsigned short getN() {
    unsigned short n;
    cout << "Please enter an odd number between and including 1 and 999. Or, enter 0 to exit." << endl;
    enterNumber(n, 0, 999);
    if (n == 0) { // if the user enters 0, return 0 to exit the program
        return 0;
    }
    else if (n % 2 == 0 || n > 999 || n < 0) { // if n is not odd, ask for a new n
        cout << "Error: Odd number was not entered, or number was not in interval [1,999]" << endl;
        return getN();
    }
    else { //  if n is valid, return n
        return n;
    }
}

void clearOutput() // clear outputFile
{
    ofstream outputFile; //declare object
    outputFile.open("output.txt", ios::out | ios::trunc); //open and associate file
    
    if (!outputFile) {
        cout << "Unable to create file";
        exit(1);   // call system to stop if file did not open
    }
    
    outputFile.close();// close reportFile
}

int main()
{
    clearOutput();
    
    unsigned short n = getN();
    while (n != 0) {
        generateSquare (n);
        n = getN();
    }
    return 0;
}
