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
#include <fstream>

class Anagrams
{
public:
    typedef std::vector<std::string> StringVector;
    typedef std::unordered_map<int, StringVector> HashAnagram;

    Anagrams()
    {
        primeGenerator(prime_vct, 200);
    }
    virtual ~Anagrams()
    {
        
    }
    
    void ReadWords()
    {
        std::ifstream ifs("/usr/share/dict/words", std::ifstream::in);
        char word[256];
        
        while(ifs.getline(word,256))
        {
            hash[GetHashKey(word)].push_back(word);
        }
    }
    
    void PrintAnagrams()
    {
        for (HashAnagram::iterator itr = hash.begin(); itr != hash.end(); ++itr)
        {
            if(itr->second.size() <2)
                continue;
            
            std::cout<<"{";
            for (StringVector::iterator itr2 = itr->second.begin();
                 itr2 != itr->second.end(); ++itr2)
            {
                std::cout << itr2->c_str() << ", ";
            }
            std::cout <<"}"<< std::endl;
        }
    }
    
private:
    void primeGenerator(std::vector<int> &prime_vct, unsigned int maxPrime)
    {
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
            char c = word[i];
            
            if(c >= 'A' && c <= 'Z')
                c='a' + (c-'A');
            
            key *= prime_vct[c - 'a'];
            ++i;
        }
        
        return key;
    }

    std::vector<int> prime_vct;
    HashAnagram hash;
};

int main(int argc, char* argv[])
{
    Anagrams anagrams;
    
    anagrams.ReadWords();
    anagrams.PrintAnagrams();
    return 0;
}
