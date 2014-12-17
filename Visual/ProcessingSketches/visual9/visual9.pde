
float alpha = 0.0;
float counter = 0.003;

void setup() {
  size(500, 500, P3D);
  smooth(8);
}

void draw() {

  background(0);

  for (int i = 0; i < 50; i++) {
    pushMatrix();
    translate(width * .5, height * .5);
    float move = counter * i + 20;
    stroke(255, move);
    if(i == 25) {
     stroke(0,200,200,80); 
     rotateX(millis() * 0.001);
    }
    noFill();
    rotateX(move);
    rotateY(move);
    ellipse(0, 0, 200, 200);
    popMatrix();
  }


  pushMatrix();
  fill(255, alpha);
  noStroke();
  scale(.5, .5);
  translate(width * .5, height * .5);
  rect(0, 0, width, height);
  popMatrix();

  alpha -= 3.0;
}

void keyPressed() {
  alpha = random(50, 255); 
  counter = noise(millis()) * 0.10;
}

