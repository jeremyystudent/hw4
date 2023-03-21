#ifndef RECCHECK
#include <utility>
#include <algorithm>
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


std::pair<int,bool> pathCounter(Node * root);


bool equalPaths(Node * root)
{
    return pathCounter(root).second;
}

std::pair<int,bool> pathCounter(Node * root){
    if(root == nullptr){return std::pair<int,bool>(-1,true);}
    if(root->left == nullptr && root->right == nullptr){
        return std::pair<int,bool>(0,true);
    }
    std::pair<int,bool> left = pathCounter(root->left);  
    std::pair<int,bool> right = pathCounter(root->right);    
    if(!left.second  || !right.second){
        return std::pair<int,bool>(std::max(left.first,right.first)+1,false);
    }
    if(left.first != -1 && right.first != -1){
        if(left.first != right.first){
            return std::pair<int,bool>(std::max(left.first,right.first)+1,false);
        }
    }
    return std::pair<int,bool>(std::max(left.first,right.first)+1,true);
}