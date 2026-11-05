
#include <iostream>
#include <list>
#include "../include/rtxcvr/flow.h"
#include <functional>
using namespace std;


namespace{
    string n= "\n";
    string t= "\t";
    
}
int main(){ 

   Tunnel::Flow<list<int>> flow({});
   

    function<void(list<int>)> live=[](list<int> y){
        cout<<t<<"3-🔵Activetl Data: "<<y.front()<<n;
    };
    void(*live1)(list<int>) = [](list<int> y){
        cout<<t<<"2-🟢Activetl Data: "<<y.front()<<n;

     };
    
    function<void(list<int>)> mod = [&flow](list<int> y){
        function<list<int>(list<int>)> mody=[y](list<int> x){ 
       
            return y;   
        };     
        flow.update(mody);
    };          
    
      
    flow.collect(
    [](list<int> xj){
        cout<<t<<"1-🔴Activetl Data: "<<xj.front()<<n;

    }, 2, 5);
    
    flow.collect(live);
    flow.collect(live1,0, 50);
    
   
     
     
     
    
    for(int i = 1; i<=100;i++){ 
        mod({i});
    }
    
  
    return 0;
}
