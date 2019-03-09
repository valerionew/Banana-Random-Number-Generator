

import processing.serial.*;

Serial bananaPort;  // Create object from Serial class

int x,y; // coordinates
float scalefactor;
String[] Serialports = Serial.list();
long inside, outside, total;

void setup() {
  
  if(Serialports.length > 0) // chech if there is at least one serial port
    bananaPort = new Serial(this, Serialports[0] , 9600); // choose the serial port of intrest, e.g. Serialports[1]
  printArray(Serial.list()); //print all serials, verify which number corresponds to yours
  
  // choose whatever resolution fits your screen.
  // it should be approximately 2x1 to display the interface correctly
  size(1500,750); 
  
  // scaling the 0-255 value from the serial into the appropriate format for the screen in use
  scalefactor = (height*0.7)/255;
 
   
  background(255); // white background
  colorMode(RGB,255); // RGB color mode
   
  // apply the transformation matrix for the point plot. 
  // remember that this function pushes a matrix, you have to pop it
  plotTransformation(); 
  
  strokeWeight(0.002); // set weak stroke weight
  ellipseMode(CENTER); // use center mode for the arcs
  fill(color(221, 254, 255)); // fill the shape with the right shade of blue
  arc(0,0,height*1.4,height*1.4,0,HALF_PI); // draw the circle quadrant
  
  noFill(); 
  strokeWeight(1); // heavier stroke
  rectMode(CORNER);
  rect(0,0,height*0.7,height*0.7); // draw the square
    
  noStroke(); // disable the stroke

  popMatrix(); // popping the plotTransformation() matrix
  
  
      fill(0); // black fill for the text
      textSize(width*0.05);
      text("Punti:", width*0.5, height*0.2); // total points label
      text("Interni:", width*0.5, height*0.35); // inside points label
      text("Esterni:", width*0.5, height*0.5); // outside points label
      textSize(width*0.075); // bigger text
      text("Pi:", width*0.5, height*0.8); // pi result label

  
}

void draw(){
  if (Serialports.length > 0){ // if there's at least one serial (not checking if it's assigned and initialized correctly, could be improved)
    
    if ( bananaPort.available() > 1) {  // if there's more than 1 byte available (we need two for each execution)
      x = bananaPort.read(); // first byte goes here
      y = bananaPort.read(); // second byte goes here
      total++; // increase total number
      plotTransformation(); // push transformation matrix for the plot
      if( x*x + y*y <= 255*255){ // if (x,y) belongs to a circle with raduis 255 the dot is inside
        fill(color(255,0,0));   // red dot
        inside++; // increase inside number
      }
      else{ // the point is outside the circle
        fill(color(0,0,255)); // blue dot
        outside++; // increase outside number
      }
      ellipse(x*scalefactor,y*scalefactor,5,5); // draw the dot, 5 pixel in size (not scalable, could be improved)
      popMatrix(); // pop the plot matrix
      
      println( x, y,inside,outside,total,(4.0*inside)/total); // DEBUG purpose only
      
      // blank the precedent values area
      fill(255); 
      rect(width*0.7,0,width*0.3,height);
      rect(width*0.6,height*0.65,width*0.4,height*0.35);
      
      // write the results since now
      fill(0);
      textSize(width*0.05);    
      text(int(total), width*0.7, height*0.2);
      text(int(inside), width*0.7, height*0.35);
      text(int(outside), width*0.7, height*0.5);
      textSize(width*0.075);
      text((4.0*inside)/total, width*0.6, height*0.8);
      
    }
  }
    
    
}

void plotTransformation(){
  pushMatrix(); // push a new matrix
  scale(1,-1); // invert Y axis
  translate(0,-height); // translate everything downwards
  translate(height*0.1,height*0.1); // give the plot a bit of margin
  // now point 0,0 is the origin of the plot
}
