
boolean trigger = false;
color background = color(240, 245, 230);
color c = color(0);
float blend = 0;
float alpha = 0;
float fade = 255;

void setup() {
  size(500,500);
}

void draw() {
  
 background(0);
 
 fade -= 5.0;
 
 if(fade <= 20.0) {
  fade = 20.0; 
 }
 
 if(trigger) {
   fade = 255;
 } 

pushMatrix();
scale(0.5, 0.5);
translate(width * .5, height * .5);
noStroke();
fill(background);
rect(0,0,width,height);
popMatrix();

for(int w = 0; w < width; w+=5){
  
 float sine = sin(w + millis() * 0.003) * fade;
 alpha = cos(w) * 255;
 float size = map( sin(w + millis() * 0.005), -1.0, 1.0, 10, 20);
 
 pushMatrix();
 scale(0.5, 0.5);
 translate(width * .5, height);
 noStroke();
 fill(c, alpha);
 ellipse(w, sine, size, size);
 popMatrix();
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

