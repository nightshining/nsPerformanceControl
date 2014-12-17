
boolean trigger = false;
color background = color(0);
color circles = color(240, 240, 230);

void setup() {
  size(500,500);
}

void draw() {
  
  background(background);

  for (int i = 0; i < width; i+=50) { 
     for (int j = 0; j < height; j+=50) { 
  
 float alpha = 0;
 float radius = 0;
 if(trigger) {
  alpha = map(sin(i + millis() * .005) * 255, -255, 255, 0, 255);
  radius = map(sin(i + millis() * .005) * 25, -25, 25, 0, 25);
 } else { 
  alpha = 0; 
 }
 
 pushMatrix();
 scale(0.5, 0.5);
 translate(width * .5, height * .5);
 noStroke();
 fill(circles, alpha);
 ellipse(i, j, radius, radius);
 popMatrix();
 
 println("alpha " + i + ": " + alpha);
     } 
  }
 
}

void keyPressed() {

  if (key == ' ') {
  trigger = true;
  }
  

  
  
  
}

void keyReleased() {

  if (key == ' ') {
  trigger = false;
  }
  
}

