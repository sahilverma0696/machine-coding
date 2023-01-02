/*
IDEA:
The idea is to have a hashmap of version to hashset containing all the supported binaries

explaination :
Part 1
We've certain binaries which are compatible together,
and We've transitive property in them 

so say we've examples as :
1<-2<-3  
4<-5<-6 

Now we've 1,2,3 compatible with each other
and 4,5,6 compatible with each other

but there two sets are non-overlapping 

So, we can take them as buckets
So, we've one bucket as 
x1 = { 1,2,3 }
x2 = { 4,5,6 }

So, we make buckets by using hashset, 
hashset x1, hashset x2 respectively 

Part 2
Now since we've the bucket

We need to perform the search
as in the API isCompatible we're provided with srcVer and tarVer

take example 
2,3 
So, we try to reach the bucket in which 2 resides and then check if 3 is also in the same bucket. 
And done.

So for this we create a hashmap 
which will look something like this 

Y=
{
    1 -> x1,
    2 -> x1,
    3 -> x1,

    4 -> x2,
    5 -> x2,
    6 -> x2,
}
So, we make a hashmap of hashmap<version,hashset<version>>

and perform the search 

example 

isCompatible(2,3)

take 2 -> Y(2)->find(3) 
    -> returns true since 2,3 points in the same bucket.

isCompatible(3,4)

take 3 -> Y(3)->find(4) 
    -> returns false since 3,4 does not points in the same bucket.


Time complexity 

addVersion()
    -> O(1), since only hash based operations are done, no iterative 

isCompatible 
    -> O(1), since only hash based searching is done.

*/

// #include<bits/stdc++h.>
#include<iostream>
#include<unordered_map>
#include<unordered_set>

using namespace std;

class CompatibilityChecker {
private:

    unordered_map<int,unordered_set<int> > records;

public:
    void    addVersion(int version, bool isCompatible)
    {
        unordered_set<int> x;
        x.insert(version);

        if(!isCompatible)
        {
            records[version] = x;
        }
        else 
        {
            if(records.find(version-1)!=records.end())
            {
                records[version-1].insert(version);
                records[version] = records[version-1];
            }
            else
            {
                records[version-1] = x;
                records[version]   = x;
            }
            
        }

    }

    bool    isCompatible(int srcVer, int tarVer)
    {
        return records[srcVer].count(tarVer)!=0 ? true:false;
    }

    void    makeCompatible(int srcVer, int tarVer)
    {
       
        auto new_bucket = &records[tarVer];
        auto src_bucket = records[srcVer];
        auto tar_bucket_copy = records[tarVer];

        // appending values in source bucket
        for(auto &x: src_bucket)
        {
            new_bucket->insert(x);
        }

        // making pointers right 
        for(auto &x: src_bucket)
        {
            records[x]= *new_bucket;
        }

        for(auto &x: tar_bucket_copy)
        {
            records[x]= *new_bucket;
        }
    }

    void    __print__()
    {
        for(auto x: records)
        {
            cout<<x.first<<"-> {\n";
            // TODO: need to print the address of hashset i.e., x.second, &x.second gives same address
            for(auto y : x.second)
            {
                cout<<"\t"<<y<<"\n";
            }
            cout<<"}\n";
        }
    }

};

int main()
{
    CompatibilityChecker c;
    c.addVersion(2,false);
    c.addVersion(3,true);
    c.addVersion(4,true);
    c.addVersion(5,false);
    c.addVersion(6,true);
    c.addVersion(7,false);
    c.addVersion(8,true);


    c.__print__();

    c.makeCompatible(6,8);

    cout<<"\n\n\n\n\n";

    c.__print__();

    return 0;
}