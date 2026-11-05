#include <iostream>
#include "../include/rtxcvr/flow.h"


int main() {
    Tunnel::Flow<int> flow(0);
    bool added = true;

    flow.collect([&](const int value) {
        std::cout << "First callback: " << value << '\n';
        if (added) {
            flow.collect([](const int value) {
                std::cout << "New callback:  "<< value << '\n';
            });   
        }
        
    });
    

    
    flow.update([](const int  value) {
        return 10;
    });
    flow.update([](const int& value) {
        return 20;
    });

    flow.update([](const int& value) {
        return 30;
    });

}
