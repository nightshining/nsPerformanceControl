
float alphas[];
color c = color(240, 245, 230);
boolean trigger = false;

void setup() {
  
  size(500,500);
  
  
  alphas = new float [width * height];
  
  for (int i = 0; i < width * height; i++) {
   
    alphas[i] = 0.0;
  }
  
}

void draw() {
 
 background(0);
 
 for(int i = 0; i < width; i+=50) {
   for (int j = 0; j < height; j+=25) {
 
 float size = cos(i  + millis() * 0.001) * 25;
 float yPos = height * .5 + sin(j  + millis() * 0.005 ) * 150;
 
 alphas[i] -= noise(i) + 0.20;
 
 if(alphas[i] <= 1.0) {
 
   alphas[i] = 0.0;
 }
 
 if(trigger) {
  
  alphas[i] = 255.0; 
   
 }
 
 pushMatrix();
 scale(0.5, 0.5);
 translate(width * .5, height * .5);
 //stroke(c);
 noStroke();
 fill(c, alphas[i]);
 ellipse(i, yPos, size, size);
 popMatrix();
   } 
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



