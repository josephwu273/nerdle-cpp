#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;

vector<string> prod(string s, int n){
    vector<string> v;
    if(n==1){
        for(char c : s){
            string y(1,c);// = (string) c;
            v.emplace_back(y);
        }
        
    }
    else{
        vector<string> vv = prod(s,n-1);
        for(char c : s){
            //cout << c << '\n';
            for(string s: vv){
                v.emplace_back(s+c);
                //cout<< s+c << "\n";
            }
        }
    }
    return v;
}


int main()
{
    vector<string> x = prod("1234567890+-/*",6);
    cout << x.size();
    return 0;
}
