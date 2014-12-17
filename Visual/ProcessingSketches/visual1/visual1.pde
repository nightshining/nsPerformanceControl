
boolean trigger = false;
float alpha = 0;

void setup() {
 
 size(500,500);

  
  
}

void draw() {
  background(0);

  for (int i = 0; i < 3; i++) { 
 
 if(trigger) {
  alpha = map(sin(i + millis() * .005) * 255, -255, 255, 0, 255);
 } 
 
 
 rectMode(CENTER);
 pushMatrix();
 translate(width * .35, height * .5);
 noStroke();
 fill(240, 240, 230, alpha);
 rect(i * 59, 0, 50, 100);
 popMatrix();
 
 println("alpha " + i + ": " + alpha);
 } 
 
    alpha -= 5; 

 
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

