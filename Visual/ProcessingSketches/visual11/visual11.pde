

float counter = 0.0;
float alpha = 0.0;
boolean trigger = false;

void setup() {
 size(500,500, P3D); 
 smooth(8);
background(0);

}

void draw() {


if(key == ' ') {
 trigger = true;
} else {
 trigger = false;
}

if(trigger) {
  clear();
  alpha = 0.0;
} 

if(!trigger) {
  redraw();
  alpha = random(0, 100);

}


println("Alpha: " + alpha);

translate(0,0,-200);
noFill();
stroke(255, alpha);

beginShape();
curveVertex(0, height * .5); //start
curveVertex(0, height * .5); //second important same as first


for(int i = 0; i < width; i+=125) {
  
curveVertex(100 + i - 100, noise(i + millis() * 0.001) * height - 50);
}

curveVertex(width, height * .5); //second to last important same as first
curveVertex(width, height * .5); //last

endShape();
  
}
