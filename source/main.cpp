#include <iostream>
#include "Graph.hpp"
using namespace std;

int main(){

     Graph grp;
     string filename;
     getline(cin, filename);

     grp.fromPajek(filename);

     grp.printMap();


     return 0;

}