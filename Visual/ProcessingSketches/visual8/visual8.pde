
float alpha, freq, max;
boolean trigger = false;

void setup() {
  size(500,500, P3D);
  smooth(8);
  alpha = 0.0;
  freq = 0.0;
  max = 100;
}

void draw() {
   
  background(0);
  max-=10;
  if(max <= 0) {
    max = 0;
  }
  
  for (int j = 0; j < 50; j++){
  
  freq = sin(millis() * 0.003) * max - sin(millis() * 0.002) * 20;

  if(trigger == true) {
    max = 255;
  } 
  
  pushMatrix();
  alpha = noise(j) * 200;
  translate(0, -j);
  beginShape();
  curveVertex(0, height * .5);
  curveVertex(0, height * .5);
  noFill();
  stroke(255, alpha);
  if(j == 4) {
  stroke(255, 0, 100, 200); 
  }
  
  for(int i = 0; i < 50; i++) {
  curveVertex(width * .1 + i * 7, width * .5 + noise(i + millis() * 0.0005) * cos(millis() * .005) * freq);
  }
  curveVertex(width, height * .5);
  curveVertex(width, height * .5);
  endShape();
  popMatrix();  
  }
  
  

}

void keyPressed() {
  
  if(key == ' ') {
   trigger = true; 
  } 
}

void keyReleased() {
  
  if(key == ' '){
  trigger = false;
  }
}

