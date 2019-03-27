boolean [][] occupancy = new boolean [10][10];
boolean [][] shortestPath = new boolean [100][2];
int targetX = 425;
int targetY = 425;
int roverX = 75;
int roverY = 25;
float cWidth;
float cHeight;

void setup() {
  size(500, 500);
  occupancy[1][5] = true;
  cWidth = width/occupancy[0].length;
  cHeight = height/occupancy.length;
  shortestPath();
}

void draw() {
  for (int r = 0; r < occupancy.length; r ++) {
    for (int c = 0; c < occupancy[0].length; c++) {
      if (occupancy[r][c]) {    //Draw the obstacles
        fill(255, 0, 0);
        ellipse(c*(cWidth)+cWidth/2, r*(cHeight)+cHeight/2, cWidth, cHeight);
      }
      else{    //Draw the nodes
       fill(0, 255, 0);
        ellipse(c*(cWidth)+cWidth/2, r*(cHeight)+cHeight/2, (cWidth)/4, (cHeight)/4);
      }
    }
  }
  
  //Draw the target
  fill(255);
  ellipse(targetX, targetY, 25, 25);
  
  //Draw the rover
  fill(0, 0, 255);
  ellipse(roverX, roverY, 25, 25);
  
}


////Custom Functions////

void shortestPath(){  //Calculate the shortest path
  boolean done = false;
  int [] currentNode = new int [2];  //Store the current node
  int [] cameFrom = new int [2];  //Store the previous node
  int [][] que = new int [100][2];  //Matrix for the que
  int [][] donePile = new int [100][100];  //Matrix for the finished nodes
  
  currentNode[0] = int((roverX - cWidth/2)/cWidth);  //Set the initial node column
  currentNode[1] = int((roverY - cHeight/2)/cHeight); //Set the initial node row
  println(currentNode[0]);
  print(currentNode[1]);
  
  cameFrom = currentNode;  //Set the initial previous node to the current one
  
  while(done == false){
    
    int i = 0;
   // if();  //Find all neighbors and add to que
           
           //Sort the que
           
           //Add currentNode to donePile array, along with the value of cameFrom
           
           //Update camefrom to the value of currentNode
           
           //Change currentNode to the node on top of the que
           
          //If the item on top of the que is the target, then stop and reconstruct the path
          done = true;
  }
}

float cost(int c, int r){    //Calculate the cost of the given point
 return(sqrt((targetX-c*(cWidth)+cWidth/2)*(targetX-c*(cWidth)+cWidth/2) + (targetY-r*(cHeight)+cHeight/2)*(targetY-r*(cHeight)+cHeight/2))); 
}

void reconstructPath(){    //Reconstruct the path used to get to the target
  
}
