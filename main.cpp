#include <iostream>
#include <stdio.h>
#include <malloc.h>

using namespace std;

enum Direction {UP=0,DOWN=1,LEFT=2,RIGHT=3};
struct Cup
{
  int level;         // level of the current cup;
  Direction dir;    // direction of the current cup.
  Cup* cup_list;    // stores the cups in the next level; 
  Direction* dir_list; //stores the connection direction between cups in the next level;
  
  Cup(int level,Direction dir,bool next_level){
    this->level=level;
    this->dir=dir;
    
//     if(cup_list!=NULL)
//       free(cup_list);
//     if(dir_list!=NULL)
//       free(dir_list);
      
    this->cup_list=NULL;
    this->dir_list=NULL;
    
    if(next_level){
      //allocating memory for the next levels cups.
      this->cup_list=(Cup*)malloc(4*sizeof(Cup));
      this->dir_list=(Direction*)malloc(3*sizeof(Direction));
      
//       for(int i=0;i<4;i++)
//         cup_list[i].level=-1;
      
      
      
      
    }
   
  }
  
  void display()
  {
    Cup* current;
    if(this->cup_list!=NULL)
    {
      current=this->cup_list;
      for(int i=0;i<4;i++)
      {
        cout<<"level:"<<current[i].level<<" direction:"<<current[i].dir<<endl;
      }
      this->cup_list[0].display();
      this->cup_list[1].display();
      this->cup_list[2].display();
      this->cup_list[3].display();
      
    }
    
    
  }
  
  
};



void generate_hilbert_curve(int level,Cup& hcurve,Direction dir,int current_level)
{
  bool state=true;
  if(level==1 || current_level==level)
  {
    state=false;
    hcurve=Cup(level,dir,state);
    return;
  }
  

  
  if(current_level<level)
  {
    state=true;
    
    if(current_level==1)
      hcurve=Cup(current_level,dir,state);
    
    switch(hcurve.dir)
    {
      case UP:           hcurve.cup_list[0]=Cup(current_level+1,LEFT,state);
                         hcurve.dir_list[0]=DOWN;
                         hcurve.cup_list[1]=Cup(current_level+1,UP,state);
                         hcurve.dir_list[1]=RIGHT;
                         hcurve.cup_list[2]=Cup(current_level+1,UP,state);
                         hcurve.dir_list[2]=UP;
                         hcurve.cup_list[3]=Cup(current_level+1,RIGHT,state);
                         
                         generate_hilbert_curve(level,hcurve.cup_list[0],LEFT,current_level+1);
                         generate_hilbert_curve(level,hcurve.cup_list[1],UP,current_level+1);
                         generate_hilbert_curve(level,hcurve.cup_list[2],UP,current_level+1);
                         generate_hilbert_curve(level,hcurve.cup_list[3],RIGHT,current_level+1);
                         
                         break;
      case DOWN:
                         hcurve.cup_list[0]=Cup(current_level+1,LEFT,state);
                         hcurve.dir_list[0]=UP;
                         hcurve.cup_list[1]=Cup(current_level+1,DOWN,state);
                         hcurve.dir_list[1]=RIGHT;
                         hcurve.cup_list[2]=Cup(current_level+1,DOWN,state);
                         hcurve.dir_list[2]=DOWN;
                         hcurve.cup_list[3]=Cup(current_level+1,RIGHT,state);
                         
                         generate_hilbert_curve(level,hcurve.cup_list[0],LEFT,current_level+1);
                         generate_hilbert_curve(level,hcurve.cup_list[1],DOWN,current_level+1);
                         generate_hilbert_curve(level,hcurve.cup_list[2],DOWN,current_level+1);
                         generate_hilbert_curve(level,hcurve.cup_list[3],RIGHT,current_level+1);
                         
                         break;
      case LEFT:
                         hcurve.cup_list[0]=Cup(current_level+1,UP,state);
                         hcurve.dir_list[0]=RIGHT;
                         hcurve.cup_list[1]=Cup(current_level+1,LEFT,state);
                         hcurve.dir_list[1]=DOWN;
                         hcurve.cup_list[2]=Cup(current_level+1,LEFT,state);
                         hcurve.dir_list[2]=LEFT;
                         hcurve.cup_list[3]=Cup(current_level+1,DOWN,state);
                         
                         generate_hilbert_curve(level,hcurve.cup_list[0],UP,current_level+1);
                         generate_hilbert_curve(level,hcurve.cup_list[1],LEFT,current_level+1);
                         generate_hilbert_curve(level,hcurve.cup_list[2],LEFT,current_level+1);
                         generate_hilbert_curve(level,hcurve.cup_list[3],DOWN,current_level+1);
                         
                         break;
      case RIGHT:
                         hcurve.cup_list[0]=Cup(current_level+1,DOWN,state);
                         hcurve.dir_list[0]=LEFT;
                         hcurve.cup_list[1]=Cup(current_level+1,RIGHT,state);
                         hcurve.dir_list[1]=UP;
                         hcurve.cup_list[2]=Cup(current_level+1,RIGHT,state);
                         hcurve.dir_list[2]=RIGHT;
                         hcurve.cup_list[3]=Cup(current_level+1,UP,state);
                         
                         generate_hilbert_curve(level,hcurve.cup_list[0],DOWN,current_level+1);
                         generate_hilbert_curve(level,hcurve.cup_list[1],RIGHT,current_level+1);
                         generate_hilbert_curve(level,hcurve.cup_list[2],RIGHT,current_level+1);
                         generate_hilbert_curve(level,hcurve.cup_list[3],UP,current_level+1);
                         
                         break;
                         
       default:          cout<<"Hilbert Curve Generation Error"<<endl;
                         break;
     
      
    }
    
  }
  
    
  
}


int main(int argc, char **argv) {
    
    Cup root(1,UP,false);
    generate_hilbert_curve(5,root,UP,1);
    
    root.display();
    
    
    return 0;
}
