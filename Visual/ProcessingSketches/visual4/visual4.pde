
boolean trigger = false;
color background = color(0);
color c = color(240, 245, 230);
float blend = 0;
float alpha = 0;

void setup() {
  size(500,500);
}

void draw() {
  
 background(background);
 
 blend += 5.0;
 if (blend >= height - 5) {
   blend = 0.0;
 }
 
 pushMatrix();
 noStroke();
 fill(0, 255, 250, 150); 
 scale(0.5, 0.5);
 translate(width * .5, height * .5);
 rect(0,blend, width, 5);
 popMatrix();
 
 
 
 for (int j = 0; j < height; j+=30) { 
 
 alpha -= 0.50;

 if( alpha <= 10.0) {
   
   alpha = 0;
 }

 println(alpha);
 
 if(trigger) {
   alpha = 255;
 }
 
 pushMatrix();
 noStroke();
 fill(c, alpha); 
 scale(0.5, 0.5);
 translate(width * .5, height * .5);
 rect(0,0, width, j);
 popMatrix();
 }
 
 for (int h = 0; h < height; h+=15) { 

 pushMatrix();
 scale(0.5, 0.5);
 translate(width * .5, height * .5);
 stroke(c);
 line(0, h, width, h);
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

