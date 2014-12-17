
color c = color(240, 245, 230);
float alpha = 255;
float size = 0.0;
boolean trigger = false;

void setup() {
  size(500, 500);
  smooth(8);
}



void draw() {
  background(0);

  if (trigger) {
        alpha = random(0,255);
      } 
        alpha-= 5.0;
       
       if(alpha <= 0.0) {
        alpha = 0.0;
       } 
      
  for (int i = 0; i < width; i+=50) {
    for (int j = 0; j < height; j+=50) {

    

      pushMatrix();
      noStroke();
      fill(c, alpha);

      if (i == 250 && j == 200) {
        fill(200, 0, 50);
         size = map(sin(millis() * 0.001) * 35, -35, 35, 30, 35);

      } else {
       
       size = 35; 
      }
      scale(.5, .5);
      translate(width * .5, height * .5);
      ellipse(i, j, size, size);
      popMatrix();
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

