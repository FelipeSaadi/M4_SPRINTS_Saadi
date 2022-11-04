int LED1 = 1;
int LED2 = 2;
int LED3 = 3;
int LED4 = 11;

int BUZZER = 7;
int LDR = 18;

int buttonSave = 9;
int buttonSaveState = 0;
int buttonPlay = 45;
int buttonPlayState = 0;

int binary[4] = {0, 0, 0, 0};
int saved[100] = {};
int count = 0;

int NOTE_F1 = 44;
int NOTE_C3 = 131;
int NOTE_B4 = 494;
int NOTE_CS6 = 1109;

// Código de conversão - não utilzado por não fazer sentido
// a conversão para binário descrita no enunciado
// int values[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// void converter(int value) {
//   int rest = value;
//   int count = 0;

//   while (value > 0) {
//     rest = value % 2;
//     value = value / 2;
//     values[count] = rest;
//     count++;
//   }

//   int binary [count] = {};
//   for (int i = 0; i < count; count--) {
//     binary[i] = values[count-1];
//     Serial.print(binary[i]);
//   }
// }

void convert(int value) {
  if (value <= 3) {
    binary[0] = 0;
    binary[1] = 0;
    binary[2] = 0;
    binary[3] = 1;
  }

  else if (value > 3 && value <= 6) {
    binary[0] = 0;
    binary[1] = 0;
    binary[2] = 1;
    binary[3] = 0;
  }

  else if ( value > 6 && value <= 9) {
    binary[0] = 0;
    binary[1] = 1;
    binary[2] = 0;
    binary[3] = 0;
  }

  else {
    binary[0] = 1;
    binary[1] = 0;
    binary[2] = 0;
    binary[3] = 0;
  }
}

void save() {
  if (count < 100) {
    for (int i = 0; i < 4; i++) {
      saved[count] = binary[i];
      count++;
    }
  }
  else {
    Serial.print("Já foram salvos mais de 100 valores. ");
    Serial.println("Para adicionar novos valores, limpe os dados salvos.");
  }
}

void play() {

  for (int i = 0; i < count; i += 4) {
    if (saved[i] == 1) {
      tone(BUZZER, NOTE_F1, 300);
      digitalWrite(LED1, HIGH);
    }
    else if (saved[i + 1] == 1) {
      tone(BUZZER, NOTE_C3, 300);
      digitalWrite(LED2, HIGH);
    }
    else if (saved[i + 2] == 1) {
      tone(BUZZER, NOTE_B4, 300);
      digitalWrite(LED3, HIGH);
    }
    else {
      tone(BUZZER, NOTE_CS6, 300);
      digitalWrite(LED4, HIGH);
    }
    delay(300);
    noTone(BUZZER);

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    delay(1000);
  }
}

void clear() {
  for (int i = 0; i < count; i++) {
    saved[i] = 0;
  }
  count = 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LDR, OUTPUT);
  pinMode(buttonSave, INPUT_PULLUP);
  pinMode(buttonPlay, INPUT_PULLUP);
}

void loop() {
  int analogValue = analogRead(LDR);

  Serial.println(analogValue);

  if (digitalRead(buttonSave) == LOW) {
    convert(analogValue);
    save();

    if (binary[0] == 1) {
      tone(BUZZER, NOTE_F1, 300);
      digitalWrite(LED1, HIGH);
    }
    else if (binary[1] == 1) {
      tone(BUZZER, NOTE_C3, 300);
      digitalWrite(LED2, HIGH);
    }
    else if (binary[2] == 1) {
      tone(BUZZER, NOTE_B4, 300);
      digitalWrite(LED3, HIGH);
    }
    else {
      tone(BUZZER, NOTE_CS6, 300);
      digitalWrite(LED4, HIGH);
    }
    delay(300);
    noTone(BUZZER);

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    delay(1000);
  }

  if (digitalRead(buttonPlay) == LOW) {
    play();
    clear();
  }
}
