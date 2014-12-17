

color c = color(240, 245, 230);
boolean trigger = false;
float noise = 0;
float alpha = 255;

void setup() {
  size(500, 500, P3D);
  smooth(8);
}

void draw() {
  background(0);
  for(int i = 0; i < width; i+=50){
  for(int j = 0; j < height; j+=50) {
  for(int radius = 0; radius < 5; radius++) {
  pushMatrix();
  noFill();
  
  if (trigger) {
   alpha = 255;
  }
  stroke(c, alpha);
  if (i == 250 && j == 250) {
  stroke(255, 0, 150, alpha - 100); 
  }
  scale(.5,.5);
  translate(width * .5, height * .5);
  float size = radius * 10;
  ellipse(i + cos(i + millis() * .005) * 5, j + sin(j + millis() * .005) * 5, size, size);
  popMatrix();
  }
    }
  }
  
  alpha -= 5.0;
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


