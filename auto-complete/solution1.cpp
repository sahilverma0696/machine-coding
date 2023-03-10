/*
HashMap based solution
input
vector<string> values = 
    {"The mysterious diary records the voice",
     "Yeah I think it's a good environment for learning English",
     "Abstraction is often one floor above you",
     "It was getting dark, and we weren’t there yet",
     "He was willing to find the depths of the rabbit hole in order to be with her"
    }


IDEA:
-> convert the strings to tokens
-> use a hashmap<string,hashmap<string,int>> which stores the frequency a word has come after a certain word
-> in result map, set a word to a next word with highest frequency
-> and just return the value from hashmap


important concept 
1. since it is provided that write just happens one a day, write can be made slow, since its 
a less asked query 
2. but reads is very much so make reads fast 

so design the ds according to that.

NOTE: this solution is case specific, meaning "The" is different from "the"
*/


#include<unordered_map>
#include<vector>
#include<iostream>
#include<string>
#include<sstream>


using namespace std;


class WordRecommender
{
private:

unordered_map< string,unordered_map<string,int> >   freqTable;
unordered_map<string,string>                        values;
vector< vector<string> >                            tokenList;
string                                              empty;
bool                                                caseSensitive; 

void    __stringToToken__(vector<string>& inputStrings)
{
    tokenList.clear();
        for(string s:inputStrings)
        {
            vector<string> tokens;
            stringstream stream(s);

            string intermediate;
            while(stream >> intermediate)
            {
                tokens.push_back(intermediate);
            }
                tokenList.push_back(tokens);
        }
}



void    __toLowerCase__()
{
    for(auto &vec:tokenList)
    {
        for(string &s:vec)
        {
            transform(s.begin(), s.end(), s.begin(), ::tolower);
        }
    }
}
void    __makeFreqTable__()
{
    freqTable.clear();
    for(vector<string> &vec:tokenList)
    {
        for(int i =0;i<vec.size();i++)
        {
            if(i==vec.size()-1)
                continue;
            freqTable[vec[i]][vec[i+1]]++;
        }
    }
}

void    __updateValues__()
{
    for(auto &umap: freqTable)
    {
        int counter  =0;
        string value;
        for(auto &obj:umap.second)
        {
            if(obj.second>counter)
            {
                counter = obj.second;
                value = obj.first;
            }
        }
        values[umap.first] = value;
    }
}


void    __printFreqTable__()
{
    for(auto &x: freqTable)
    {
        cout<<x.first<<"\n\t{";
        for(auto &y: x.second)
        {
            cout<<"\n\t"<<y.first<<"\t->\t"<<y.second<<"\n";
        }
        cout<<"\n\n\n";
    }

    
}
public:

        WordRecommender(bool isCaseSensitive = false)
        {
            caseSensitive = isCaseSensitive;
            empty = "";
        }

void    insert(vector<string> rawData)
{
    __stringToToken__(rawData);

    if(!caseSensitive)
        __toLowerCase__();

    __makeFreqTable__();

    __updateValues__();
}

string  suggest(string word)
{
    if(values.find(word)!=values.end())
    {
        return values[word];
    }
    else
        return empty;
}

void    printFreqTable()
{
    __printFreqTable__();
}

};

int main()
{
    vector<string> values = {
    "The mysterious diary records the voice",
     "Yeah I think it's a good environment for learning English",
     "Abstraction is often one floor above you",
     "It was getting dark, and we weren’t there yet",
     "the way the way the way the way",
     "He was willing to find the depths of the rabbit hole in order to be with her"
                            };

    WordRecommender Recommender;
    Recommender.insert(values);
    
    //Recommender.printFreqTable();

    string result = Recommender.suggest("the");
    cout<<result;

    return 0;
}
