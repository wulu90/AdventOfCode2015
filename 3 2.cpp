#include <iostream>
#include <set>

using namespace std;

void part1(){
  set<pair<int,int>> coords;
  pair<int,int> curr{0,0};
  coords.insert(curr);
  char c;
  while(cin>>c){
    auto [i,j]=curr;
    if(c=='^'){
      curr=make_pair(i-1,j);
    }else if(c=='>'){
      curr=make_pair(i,j+1);
    }else if(c=='v'){
      curr=make_pair(i+1,j);
    }else{
      curr=make_pair(i,j-1);
    }
    
    coords.insert(curr);
  }
  cout<<coords.size()<<endl;
}
void part2(){
  set<pair<int,int>> coords,coords_robot;
  pair<int,int> curr_o{0,0};
  pair<int,int> curr_r{0,0};
  
  coords.insert(curr_o);
  coords_robot.insert(curr_r);
  bool isrobot=false;
  char c;
  while(cin>>c){
    auto curr=isrobot?curr_r:curr_o;
    auto [i,j]=curr;
    
    if(c=='^'){
      curr=make_pair(i-1,j);
    }else if(c=='>'){
      curr=make_pair(i,j+1);
    }else if(c=='v'){
      curr=make_pair(i+1,j);
    }else{
      curr=make_pair(i,j-1);
    }
    
    if(isrobot){
      curr_r=curr;
      coords_robot.insert(curr);
    }else{
      curr_o=curr;
      coords.insert(curr);     
    }
    isrobot=!isrobot;
  }
  set<pair<int,int>> res;
  for(auto& co:coords){
    res.insert(co);
  }
  for(auto& co:coords_robot){
    res.insert(co);
  }
 
    cout<<res.size()<<endl;
}
int main(){
  part2();
  return 0;
}