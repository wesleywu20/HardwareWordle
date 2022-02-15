int numGuesses = 0;
String guess;
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  generateClock(A0, "00000", "00000");
  generateClock(A1, "00000", "00000");
  generateClock(A2, "00000", "00000");
  generateClock(A3, "00000", "00000");
  generateClock(A4, "00000", "00000");
  generateClock(A5, "00000", "00000");
}

void loop() {
  // check if data is available
    // read the incoming string:
    generateClock(A5, "00000", "00000");
    while (!Serial.available()){}
    guess = Serial.readStringUntil('\n');

    // prints the received data
    while (guess.length() != 5) {
      Serial.println("Invalid guess! Please enter a guess of length 5!");
      while (!Serial.available()){}
      guess = Serial.readStringUntil('\n');
    }
    if (guess.length() == 5) {
      numGuesses++; 
    }
    outputClock();
    if (comparison("spear", guess) == "GGGGG") {
      Serial.println("Game won!");
      exit(0);
    }
    if (numGuesses == 6) {
      Serial.println("Game over!");
      exit(0);
    }
//    lightLEDs(guess);
//    delay(2000);
//    clearLEDs();
}

void clearLEDs() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
//  digitalWrite(10, LOW);
//  digitalWrite(9, LOW);
}
void generateClock(int pinNum, String gBitStream, String yBitStream) {
  String gTemp = gBitStream;
  String yTemp = yBitStream;
  for (int i = 0; i < 8; i++) {
    digitalWrite(pinNum, HIGH);
    if (gTemp[0] == '1') {
      digitalWrite(12, HIGH);
    }
    else {
      digitalWrite(12, LOW);
    }
    if (yTemp[0] == '1') {
      digitalWrite(11, HIGH);
    }
    else {
      digitalWrite(11, LOW);
    }
    
    gTemp = gTemp.substring(1,5) + '0' ;
    yTemp = yTemp.substring(1,5) + '0' ;
    delay(250);
    digitalWrite(pinNum, LOW);
    delay(250);
  }
}
void outputClock() {
  String comp = comparison("spear", guess); 
  String gBits = generateG(comp);
  String yBits = generateY(comp);
  if (numGuesses == 1) {
    generateClock(A0, gBits, yBits);
  }
  else if (numGuesses == 2) {
    generateClock(A1, gBits, yBits);
  }
  else if (numGuesses == 3) {
    generateClock(A2, gBits, yBits);
  }
  else if (numGuesses == 4) {
    generateClock(A3, gBits, yBits);
  }
  else if (numGuesses == 5) {
    generateClock(A4, gBits, yBits);
  }
  else if (numGuesses == 6) {
    generateClock(A5, gBits, yBits);
  }
  else {}
}

String generateG(String comp) {
  String gBitStream = "00000";
  for (int i = 0; i < comp.length(); i++) {
    if (comp[i] == 'G') {
      gBitStream[i] = '1';
    }
  }
  return gBitStream;
}

String generateY(String comp) {
  String yBitStream = "00000";
  for (int i = 0; i < comp.length(); i++) {
    if (comp[i] == 'Y') {
      yBitStream[i] = '1';
    }
  }
  return yBitStream;
}

void lightLEDs(String guess_word) {
  String comp = comparison("spear", guess_word);
  if (comp[0] == 'G') {
    digitalWrite(A0, HIGH);
  }
  else if (comp[0] == 'Y') {
    digitalWrite(A1, HIGH);
  }
  else {
    
  }
  if (comp[1] == 'G') {
    digitalWrite(A2, HIGH);
  }
  else if (comp[1] == 'Y') {
    digitalWrite(A3, HIGH);
  }
  else {
    
  }
  if (comp[2] == 'G') {
    digitalWrite(A4, HIGH);
  }
  else if (comp[2] == 'Y') {
    digitalWrite(A5, HIGH);
  }
  else {
    
  }
  if (comp[3] == 'G') {
    digitalWrite(12, HIGH);
  }
  else if (comp[3] == 'Y') {
    digitalWrite(11, HIGH);
  }
  else {
    
  }
  if (comp[4] == 'G') {
    digitalWrite(10, HIGH);
  }
  else if (comp[4] == 'Y') {
    digitalWrite(9, HIGH);
  }
  else {
    
  }
}

String comparison(String Answer, String guess){
  //starts as all grey
  String comp = "XXXXX";
  String temp = "XXXXX";
  Answer.toUpperCase();
  guess.toUpperCase();
  //green loop
  for( int x = 0; x < Answer.length(); x++){
    if (Answer[x] == guess[x]){
      comp[x] =  'G';
      temp[x] =  'G';
    }
  }
  
  //yellow loop
  for( int i = 0; i < guess.length(); i++){
    if(comp[i] == 'G'){continue;}
    if(comp[i] == 'Y'){continue;}
    
    for ( int j = 0; j < Answer.length(); j++){
      if(temp[j] == 'G'){continue;}
      if(temp[j] == 'Y'){continue;}
      
      if(guess[i] == Answer[j]){
        comp[i] = 'Y';
        temp[j] = 'Y';
      }
    }
  }
  return comp;
}
