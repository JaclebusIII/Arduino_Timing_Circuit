#define camera1 8
#define camera2 7
#define camera3 5
#define camera4 6

// this is the "meta counter"
signed int state = 0;

//interrupt frequency (Hz) = (Arduino clock speed 16,000,000Hz) / (prescaler * (compare match register + 1))
// this is the compare match register for the 1.115ms clock rate 
unsigned int ocr = 18; //18 for 1.115s or 17 for 1.088s

// this is how many of those ^^^ ticks it takes to get to 1/24 (.04s)
const int numstates = 35; //35 for .04025

ISR(TIMER1_COMPA_vect)
{ 
  switch (state) {
    case 0:
      //signal camera1
      //Serial.print("Camera1");
      //Serial.print("   ");  
      
      digitalWrite(camera1, HIGH);
      break;
    case 1:
      //signal camera2
      //Serial.print("Camera2");
      //Serial.print("   ");
      
      digitalWrite(camera2, HIGH);
      digitalWrite(camera1, LOW);
      break;
    case 2:
      //signal camera3
      //Serial.print("Camera3");
      //Serial.print("   ");
      
      digitalWrite(camera3, HIGH);
      digitalWrite(camera2, LOW);
      break;
    case 3:
      //signal camera4
      //Serial.print("Camera4");
      //Serial.print("   ");

      digitalWrite(camera4, HIGH);
      digitalWrite(camera3, LOW);
      break;
    case 4:
      // turn off the last camera 
      digitalWrite(camera4, LOW);
      break;
    case numstates:
      //reset state
      //Serial.print("resetting");
      state = -1;
    default:
      break;
  }
  //Serial.print(state);
  
  state ++;
}
void setup()
{
  //Serial.begin(9600); // for printing 
  
  // init pins values
  pinMode(camera1, OUTPUT);
  digitalWrite(camera1, LOW);
  pinMode(camera2, OUTPUT);
  digitalWrite(camera2, LOW);
  pinMode(camera3, OUTPUT);
  digitalWrite(camera3, LOW);
  pinMode(camera4, OUTPUT);
  digitalWrite(camera4, LOW);
  
  cli();
  //init counters to 0
  TCCR1A = 0;
  TCCR1B = 0; 
  // set this register to how high to count
  OCR1A = ocr;
  TCCR1B = (1<<WGM12);
  // this will set the prescale to 1024
  TCCR1B |= (1 << CS12) | (1 << CS10); 
  TIMSK1 = (1<<OCIE1A); 
  sei(); 
   }
  
void loop()
{

}
