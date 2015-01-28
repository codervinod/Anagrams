//
//  main.cpp
//  Anagrams
//
//  Created by Vinod Gupta on 1/28/15.
//  Copyright (c) 2015 Vinod Gupta. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include <map>
#include <unordered_map>

std::vector<int> prime_vct;

//Copied form gist https://gist.github.com/vinodg/a9bf40195c7d3a211e0d
void primeGenerator(std::vector<int> &prime_vct, unsigned int maxPrime)
{
    prime_vct.push_back(1);
    prime_vct.push_back(2);
    
    for (unsigned int i = 3; i < maxPrime; i += 2)
    {
        int found = 1;
        double sqrt_i = sqrt(i);
        std::vector<int>::iterator itr = prime_vct.begin();
        while (itr != prime_vct.end())
        {
            if (*itr >= 3)
            {
                if (*itr> sqrt_i)
                    break;
                
                if (i%*itr == 0)
                {
                    found = 0;
                    break;
                }
            }
            ++itr;
        }
        if (found)
        {
            prime_vct.push_back(i);
            if (prime_vct.size() > maxPrime - 1)
                break;
        }
    }
    
}

int GetHashKey(const char* word)
{
    int i = 0;
    int key = 1;
    while (word[i] != '\0')
    {
        key *= prime_vct[word[i] - 'a'];
        ++i;
    }
    
    return key;
}

int main(int argc, char* argv[])
{
    typedef std::vector<std::string> StringVector;
    typedef std::unordered_map<int, StringVector> HashAnagram;
    HashAnagram hash;
    
    primeGenerator(prime_vct, 100);
    StringVector test_set;
    test_set.push_back("act");
    test_set.push_back("vinod");
    test_set.push_back("rat");
    test_set.push_back("atr");
    test_set.push_back("tar");
    test_set.push_back("cat");
    test_set.push_back("inodv");
    
    
    for (StringVector::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr)
    {
        hash[GetHashKey(itr->c_str())].push_back(*itr);
    }
    
    for (HashAnagram::iterator itr = hash.begin(); itr != hash.end(); ++itr)
    {
        for (StringVector::iterator itr2 = itr->second.begin();
             itr2 != itr->second.end(); ++itr2)
        {
            std::cout << itr2->c_str() << "\t";
        }
        std::cout << std::endl;
    }
    return 0;
}
