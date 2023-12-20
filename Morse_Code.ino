#define  SIZE 26
const int b_led = 4;
const int g_led = 5;
const int y_led = 6;
const int r_led = 7; 
const int dotButton   = 11;
const int dashButton  = 10;
const int spaceButton = 9;
const int enterButton = 8;

String  morseCode="";
String  text="";
int     characterAscii=0;
int     startPos=0, endPos=0;
int     startPos1=0, endPos1=0;
String  characterCode="";
int     dashButtonState=0;
int     dotButtonState=0;


//Array of MorseCode for  letters of English Language A to Z
String letters[SIZE]={

// A to I
".-",  "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
// J  to R 
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",  ".-.",
// S to Z
"...", "-", "..-", "...-", ".--", "-..-", "-.--",  "--.." ,
//1 to 9
".----","..---","...--","....-",".....","-....","--...","--...","---..","----.","-----",
};

        
void setup() {

pinMode(b_led, OUTPUT);
pinMode(g_led, OUTPUT);
pinMode(y_led, OUTPUT);
pinMode(r_led, OUTPUT);
pinMode(dotButton,   INPUT);
pinMode(dashButton,  INPUT);
pinMode(spaceButton, INPUT);
pinMode(enterButton, INPUT);
Serial.begin(9600);

Serial.println("*************************************************************");
Serial.println("                    Demonstration of Morse Code              ");
Serial.println("*************************************************************  ");
Serial.println("\n Enter Your  Morse Code Here  ");

}


void loop() {

//while(Serial.available() > 0 ) {
//      int  ascii=Serial.read();
//      switch(ascii)
//      {
//        case 49: // 49 is Ascii value of 1
//        morseCode.concat("@");
//        Serial.print("@");
//        delay(200);
//        break;
//      }
//  }
  if(digitalRead(spaceButton)==1){
        morseCode.concat("@");
        Serial.print("@");
        delay(200);
  }
  if(digitalRead(enterButton)==1){
      morseCode.concat("#");
      Serial.print("#");
      delay(200);
        endPos1=morseCode.indexOf('#');

        while(endPos1 < morseCode.length() )
        {
            extractLetters(morseCode.substring(startPos1,  endPos1)); 
           startPos1=endPos1+1;
           if(startPos1  == morseCode.length() )
           {
              break; 
           }
           endPos1= morseCode.indexOf('#', startPos1);
        }
        startPos1=0;
        endPos1=0;

        text=""; //  For New Translation   
        morseCode="";
        Serial.println("\n Enter Your Morse Code Here ");
  }

process();

}

void  code_led()
{
  digitalWrite(b_led, HIGH);
}

void process()
{
  
  dotButtonState   = digitalRead(dotButton);
  dashButtonState  = digitalRead(dashButton);

  if(dashButtonState == HIGH)
  {
    code_led();
    morseCode.concat("-");  // Storing code in variable morseCode with the help of concatenation function
    Serial.print("-");//Prints User entered Code
    delay(200);
  }
  else if(dotButtonState == HIGH)
  {
   code_led();
   morseCode.concat(".");
   Serial.print(".");
   delay(200);
  }
  else
  {
    digitalWrite(b_led, LOW);  
  }
}

char convertIntoText(String  characterCode)
{
  characterAscii=65;
  
  for(int index=0; index<SIZE;  index++)
  {
    if(characterCode == letters[index])
    {
      return  characterAscii;   
    }
    characterAscii++;  
  }

}

void  extractLetters(String words)
{
        words.concat('@'); // Placeing @ at  the end of word to simplify further processing
        endPos=words.indexOf('@');
        //Loop to extracting single character morse Code from string  of word        
        while( endPos<words.length() )
       {
         characterCode=words.substring(startPos,  endPos);
         //Now CharacterCode will now convert in text
         text.concat(convertIntoText(characterCode));
         startPos=endPos+1;
         characterCode="";
          // if condition is just to  terminate loop when our extracting single character code is complete thats all
         if(startPos == words.length() )
         {
           break;
         }
         endPos=words.indexOf('@', startPos);   
       }

        Serial.print(" ");
        Serial.println(text);
        int len = text.length();
        for(int i = 0; i<=len; i++){
          digitalWrite(g_led,HIGH);
          delay(300);
          digitalWrite(y_led,HIGH);
          delay(300);
          digitalWrite(y_led,LOW);
          digitalWrite(g_led,LOW);
          digitalWrite(r_led,HIGH);
          delay(300);
          digitalWrite(r_led,LOW);
        }
        Serial.print(" ");
        startPos=0;
        endPos=0;
        text="";    
  
}


