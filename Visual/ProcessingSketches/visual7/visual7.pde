
color c = color(240, 245, 230);
boolean trigger = false;
float noise = 0;

void setup() {
  
  size(500,500);
  
}

void draw() {
 
 background(0);
 

 for (int j = 0; j < height; j+=100) {
 
  noise -= .40;
   
   if(noise <= 0.0) {
   noise = 0.0;  
   }
   
   println(noise);
   
 if(trigger) {
  
   noise = random(0, 255);
   
 } 
 
 
 pushMatrix();
 scale(0.5, 0.5);
 translate(width * .5, height * .5);
 //stroke(c);
 noStroke();
 fill(c, noise);
 rect(0,j, width, 75);
 popMatrix();
   } 
 }

  



void keyPressed() {
  
  if(key == ' ') {
  trigger = true;
  }
}


void keyReleased() {
  
  if(key == ' ') {
  trigger = false;
  }
}



