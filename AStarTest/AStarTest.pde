boolean [][] occupancy = new boolean [10][10]; //<>//
int [][] shortestPath = new int [100][2];
int targetX = 325;
int targetY = 325;
int roverX = 75;
int roverY = 25;
float cWidth;
float cHeight;

void setup() {
  size(500, 500);
//  occupancy[1][5] = true;
//  occupancy[1][6] = true;
//  occupancy[4][3] = true;
//  occupancy[4][5] = true;
//  occupancy[5][5] = true;
//  occupancy[6][5] = true;
  cWidth = width/occupancy[0].length;
  cHeight = height/occupancy.length;
 
}

void draw() {
  background(255); //clear the previous frame
  
   shortestPath(); //Calculate the shortest path
   
   
  for (int r = 0; r < occupancy.length; r ++) {
    for (int c = 0; c < occupancy[0].length; c++) {
      if (occupancy[r][c]) {    //Draw the obstacles
        fill(255, 0, 0);
        ellipse(r*(cHeight)+cHeight/2, c*(cWidth)+cWidth/2, cWidth, cHeight);
      } else {    //Draw the nodes
        fill(0, 255, 0);
        ellipse(r*(cHeight)+cHeight/2, c*(cWidth)+cWidth/2, (cWidth)/4, (cHeight)/4);
      }
    }
  }

  //Draw the target
  fill(255);
  ellipse(targetX, targetY, 25, 25);

  //Draw the rover
  fill(0, 0, 255);
  ellipse(roverX, roverY, 25, 25);
  
  //Draw the path
  for(int i = 0; i < (shortestPath.length - 1); i++){
    if(shortestPath[i + 1][0] == -1){
     break; 
    }
    else{
      strokeWeight(5);
      line(shortestPath[i][0] *(cWidth) + cWidth/2, shortestPath[i][1] *(cHeight) + cHeight/2, shortestPath[i+1][0] *(cWidth) + cWidth/2, shortestPath[i+1][1] *(cHeight) + cHeight/2); //<>//
      strokeWeight(1);
    }  
}
  
}

void mousePressed(){
 occupancy[int((mouseX - cWidth/2)/cWidth)][int((mouseY - cHeight/2)/cHeight)] = true; 
}

////Custom Functions////

void shortestPath() {  //Calculate the shortest path
  boolean done = false;
  int [] currentNode = new int [2];  //Store the current node
  int [] cameFrom = new int [2];  //Store the previous node
  float [][] que = new float [100][3];  //Matrix for the que
  int [][] donePile = new int [100][4];  //Matrix for the finished nodes
  int donePileCount = 0;

  currentNode[0] = int((roverX - cWidth/2)/cWidth);  //Set the initial node column
  currentNode[1] = int((roverY - cHeight/2)/cHeight); //Set the initial node row
  println(currentNode[0]);
  println(currentNode[1]);

  cameFrom[0] = currentNode[0];  //Set the initial previous node to the current one
  cameFrom[1] = currentNode[1];

  while (done == false) {

    int i = 0;
    //Find all neighbors and add to que
    if (currentNode[0] > 0) {  //Add the node to the left;
      if (occupancy[currentNode[0] - 1][currentNode[1]] == false) {  //Check if the node is open
        if(inDonePile(currentNode[0] - 1, currentNode[1], donePile, donePileCount) == false){  //Check if the node was already traveled to
        que[i][0] = currentNode[0] - 1;
        que[i][1] = currentNode[1];
        i++;
        }
      }
    }
    if (currentNode[0] < occupancy.length - 1) {  //Add the node to the right //<>//
      if (occupancy[currentNode[0] + 1][currentNode[1]] == false) {  //Check if the node is open //<>//
       if(inDonePile(currentNode[0] + 1, currentNode[1], donePile, donePileCount) == false){  //Check if the node was already traveled to
        que[i][0] = currentNode[0] + 1;
        que[i][1] = currentNode[1];
        i++;
       }
      }
    }
    if (currentNode[1] > 0) {  //Add the node above
      if (occupancy[currentNode[0]][currentNode[1] - 1] == false) {  //Check if the node is open
       if(inDonePile(currentNode[0], currentNode[1] - 1, donePile, donePileCount) == false){  //Check if the node was already traveled to
        que[i][0] = currentNode[0];
        que[i][1] = currentNode[1] - 1;
        i++;
       }
      }
    }
    if (currentNode[1] < occupancy[0].length - 1) { //Add the node below
      if (occupancy[currentNode[0]][currentNode[1] + 1] == false) {  //Check if the node is open
       if(inDonePile(currentNode[0], currentNode[1] + 1, donePile, donePileCount) == false){  //Check if the node was already traveled to
        que[i][0] = currentNode[0];  
        que[i][1] = currentNode[1] + 1;
        i++;
       }
      }
    }
    if (currentNode[0] > 0 && currentNode[1] > 0) {  //Add the node at the top left corner
      if (occupancy[currentNode[0] - 1][currentNode[1] - 1] == false) {  //Check if the node is open
        if(inDonePile(currentNode[0] - 1, currentNode[1] - 1, donePile, donePileCount) == false){  //Check if the node was already traveled to
        que[i][0] = currentNode[0] - 1;
        que[i][1] = currentNode[1] - 1;
        i++;
        }
      }
    }
    if (currentNode[0] < occupancy.length - 1 && currentNode[1] > 0) {  //Add the node at the top right corner
      if (occupancy[currentNode[0] + 1][currentNode[1] - 1] == false) {  //Check if the node is open
       if(inDonePile(currentNode[0] + 1, currentNode[1] - 1, donePile, donePileCount) == false){  //Check if the node was already traveled to
        que[i][0] = currentNode[0] + 1;
        que[i][1] = currentNode[1] - 1;
        i++;
       }
      }
    }
    if (currentNode[0] < occupancy.length - 1 && currentNode[1] < occupancy[0].length - 1) {  //Add the node at the bottom right corner
      if (occupancy[currentNode[0] + 1][currentNode[1] + 1] == false) {  //Check if the node is open
       if(inDonePile(currentNode[0] + 1, currentNode[1] + 1, donePile, donePileCount) == false){  //Check if the node was already traveled to
        que[i][0] = currentNode[0] + 1;
        que[i][1] = currentNode[1] + 1;
        i++;
       }
      }
    }
    if (currentNode[0] > 0 && currentNode[1] < occupancy[0].length - 1) {  //Add the node at the bottom left corner
      if (occupancy[currentNode[0] - 1][currentNode[1] + 1] == false) {  //Check if the node is open
       if(inDonePile(currentNode[0] - 1, currentNode[1] + 1, donePile, donePileCount) == false){  //Check if the node was already traveled to
        que[i][0] = currentNode[0] - 1;
        que[i][1] = currentNode[1] + 1;
        i++;
       }
      }
    }

    for (int g = 0; g < que.length; g++) {  //calculate the cost (distance) values
      que[g][2] = cost(que[g][0], que[g][1]);
    }

    //Sort the que
    boolean doneSorting = false;
    float temp1 = 100;
    float temp2 = 100;
    float temp3 = 100;
    while (doneSorting == false) {
      for (int s = 0; s < que.length - 1; s++) {  //Bubble sort
        if (que[s+1][2] < que[s][2]) {
          temp1 = que[s][0];
          temp2 = que[s][1];
          temp3 = que[s][2];
          que[s][0] = que[s+1][0];
          que[s][1] = que[s+1][1];
          que[s][2] = que[s+1][2];
          que[s+1][0] = temp1;
          que[s+1][1] = temp2;
          que[s+1][2] = temp3;
        }
      }

      boolean notDone = false;
      for (int d = 0; d < que.length - 1; d++) {  //Check if sorting is done
        if (que[d + 1][2] < que[d][2]) {
          notDone = true;
        }
      }
      if (notDone == false) {
        doneSorting = true;
      }
    }

    for (int g = 0; g < donePile.length; g++) {  //Print the que for debug
      println(donePile[g]);
    }
    
    //Add currentNode to donePile array, along with the value of cameFrom
    donePile[donePileCount][0] = currentNode[0];
    donePile[donePileCount][1] = currentNode[1];
    donePile[donePileCount][2] = cameFrom[0];
    donePile[donePileCount][3] = cameFrom[1];
    donePileCount++;  //Incrament the counter
    //Update camefrom to the value of currentNode
    cameFrom[0] = currentNode[0];
    cameFrom[1] = currentNode[1];
    
    //Change currentNode to the node on top of the que
    if(donePileCount >= 100){  //If the done pile reaches this point, it is likely because a solution was not found
     println("Failed to find solution");
     noLoop();  //Stop looping
     break;
    }
    if(int(que[0][0]) == donePile[donePileCount][2] && que[0][1] == donePile[donePileCount][3]){  //Make sure the node on the top of the que was not the previous node 
       currentNode[0] = int(que[1][0]);
      currentNode[1] = int(que[1][1]);
    }
    else{
      currentNode[0] = int(que[0][0]);
      currentNode[1] = int(que[0][1]);
    }
    
    //If the item on top of the que is the target, then stop and reconstruct the path
    if(cost(currentNode[0],currentNode[1]) <= cWidth){
      donePile[donePileCount][0] = -1;  //This is a marker so the reconstructPath function knows where the pile ends
      done = true;
      reconstructPath(donePile);
    }
  }
}

float cost(float c, float r) {    //Calculate the cost of the given point

  return(sqrt((targetX-c*(cWidth)+cWidth/2)*(targetX-c*(cWidth)+cWidth/2) + (targetY-r*(cHeight)+cHeight/2)*(targetY-r*(cHeight)+cHeight/2)));
}

void reconstructPath(int [][] donePile) {    //Reconstruct the path used to get to the target
  int lastElementPos = -1;
  println("Path reconstructing...");
  for(int i = 0; i < donePile.length; i++){  //Find where the last element is in the donePile
    if(donePile[i][0] == -1){
      lastElementPos = i - 1;
      break;
    }
  }
  
  int possitiveInc = 0;
  for(int n = lastElementPos; n >= 0; n = n - 1){
    shortestPath[n][0] = donePile[n][0];
    shortestPath[n][1] = donePile[n][1];
  }
  
  shortestPath[lastElementPos + 1][0] = int((targetX - cWidth/2)/cWidth);
  shortestPath[lastElementPos + 1][1] = int((targetY - cHeight/2)/cHeight);
  shortestPath[lastElementPos + 2][0] = -1;  //Marker to indicate the end of the path for the drawing function
  
  
  //Print the shortest path
  for(int i = 0; i < shortestPath.length; i++){
    println(shortestPath[i]);
  }
}

boolean inDonePile(int x, int y, int [][] donePile, int donePileCount){
  boolean inPile = false;
  for(int i = 0; i < donePile.length; i++){
   if(x == donePile[i][0] && y == donePile[i][1]){
     inPile = true;
   }
  }
 
 //if(x == donePile[donePileCount][0] && y == donePile[donePileCount][1]){
 // inPile = true; 
 //}
   if(inPile){
    println("Duplicate node"); 
   }
   return inPile;
}
