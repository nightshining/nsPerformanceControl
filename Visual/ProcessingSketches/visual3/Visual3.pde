
boolean trigger = false;
color background = color(0);
color circles = color(240, 245, 230);
float fade = random(50, 255);

void setup() {
  size(500,500);
}

void draw() {
  
  background(background);

  for (int i = 0; i < width; i+=20) { 
     for (int j = 0; j < height; j+=20) { 
  
 float alpha = map(noise(i * j + millis() * .005) * 255, -255, 255, 0, 255);

 float radius = 15;
 
 if(trigger) {
   fade -= 0.05;
   if(fade <= 0.0) {
     fade = 0.0;
   }
 } else { 
 }
 
 pushMatrix();
 rectMode(CENTER);
 scale(0.5, 0.5);
 translate(width * .5, height * .5);
 noStroke();
 fill(circles, alpha + fade);
 rect(i, j, radius, radius);
 popMatrix();
 
 println("fade: " + fade);
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

