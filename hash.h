#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        int n = k.size(); 
        int lastInd = 4; 
        std::vector<HASH_INDEX_T>parts(5,0);  //set all to 0
      
        /*
        //turn index of parts to 0
        for (int i = 0; i < 5; i++){
            parts[i] = 0; 
        }
        */

        int pos = n; 
        while(pos > 0 && lastInd >= 0){
            HASH_INDEX_T val = 0;
            HASH_INDEX_T base = 1; 

            //go through next 6 letters
            for (int i = 0; i < 6 && pos > 0; i++){
                pos--;

                //get number and turn to a letter
                HASH_INDEX_T number = letterDigitToNumber(k[pos]);
                
                val += (number * base);
                base *= 36; 
            }
            //set it
            parts[lastInd] = val; 
            lastInd--; 
        }

        //multiply each part by r and add
        HASH_INDEX_T finalHash = 0; 
        for (int i =0; i < 5; i++){
            finalHash += (parts[i] * rValues[i]);
        }
        return finalHash; 
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        //first turn to lowercase (in ascii, its +32)
        if (letter >= 'A' && letter <= 'Z'){
            letter += 32; 
        }

        //0 = a - a, 1 = b - 1, etc
        if (letter >= 'a' && letter <= 'z'){
            return letter - 'a'; 
        }
        //else its 0-9 (26,27,28, etc)
        else{
            return (letter - '0') + 26; 
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif