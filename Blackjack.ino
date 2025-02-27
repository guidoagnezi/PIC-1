#include <LiquidCrystal_I2C.h>
#include <Servo.h>


LiquidCrystal_I2C lcd_1(0x27, 16, 2);

byte coracao[8] = { B00000, B00100, B01110, B11111, B11111, B00100, B01110, B00000 };
byte ouro[8] = { B00000, B01010, B11111, B11111, B11111, B01110, B00100, B00000 };
byte espada[8] = { B00000, B00100, B01110, B11111, B11111, B01110, B00100, B00000 };
byte paus[8] = { B00000, B01110, B01110, B11111, B11111, B00100, B01110, B00000 };

byte cartas[40] = { 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10 };

volatile byte estado = 1;  // 1 = tela de titulo; 2 = jogo; 3 = fim
volatile byte modo = 0;    // 0 = PvE; 1 = PvP
volatile byte vez = 0;

volatile byte mao1 = 0;
volatile byte mao2 = 0;

int cartasMao1[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int naipesMao1[9] = { 5, 5, 5, 5, 5, 5, 5, 5, 0 };
int cartasMao2[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int naipesMao2[9] = { 5, 5, 5, 5, 5, 5, 5, 5, 0 };
int index1 = 0;
int index2 = 0;

volatile bool c1 = false;
volatile bool c2 = false;
volatile bool tavaOff = false;
volatile byte cE = 0;

volatile byte agiu = 0;

Servo meuServo;
int pos = 0;

Servo medidor;
int med = 0;

const int botaoMao = 8;

void comando1() {
  Serial.print("1\n");
  c1 = true;
}

void comando2() {
  Serial.print("2\n");
  c2 = true;
}

byte mostrarCarta(byte mao, byte vez) {
  c1 = false;
  c2 = false;
  bool as = false;
  lcd_1.clear();
  int carta = cartas[random(0, 40)];
  byte naipe = random(0, 4);

  if (vez == 0) {
    cartasMao1[index1] = carta;
    naipesMao1[index1] = naipe;

    index1 = index1 + 1;
  }
  if (vez == 1) {
    cartasMao2[index2] = carta;
    naipesMao2[index2] = naipe;

    index2 = index2 + 1;
  }

  if (carta != 1) {
    mao = mao + carta;
  }

  lcd_1.print("P");
  if (modo == 0 && vez == 1) {
    lcd_1.print("C");
  } else {
    lcd_1.print(vez + 1);
  }

  if (carta == 1) {  // #######################
    lcd_1.print(" comprou um ");
    lcd_1.write(byte(naipe));
    lcd_1.print("A");
    lcd_1.setCursor(0, 1);
    lcd_1.print("1 ou 11? Mao: ");
    lcd_1.print(mao);
    if (modo == 0 && vez == 1) {
      delay(2500);
      byte rand = random(0, 2);
      if (mao + 1 == 21) {
        mao = mao + 1;
        as = true;
      } else if (mao + 11 == 21) {
        mao = mao + 11;
        as = false;
      }

      else if (rand == 0 && mao + 1 < 21) {
        mao = mao + 1;
        as = true;
      } else if (rand == 1 && mao + 11 < 21) {
        mao = mao + 11;
        as = false;
      } else {
        mao = mao + 1;
        as = true;
      }
    } else {
      while (1) {
        if (c1 == true) {
          mao = mao + 1;
          c1 = false;
          c2 = false;
          as = true;
          break;
        }
        if (c2 == true) {
          mao = mao + 11;
          c1 = false;
          c2 = false;
          as = false;
          break;
        }
      }
    }
    lcd_1.clear();
    lcd_1.print("P");
    if (modo == 0 && vez == 1) {
      lcd_1.print("C");
    } else {
      lcd_1.print(vez + 1);
    }
    lcd_1.print(" Escolheu ");
    if (as) {
      lcd_1.print(1);
    } else {
      lcd_1.print(11);
    }
    lcd_1.setCursor(0, 1);
    lcd_1.print(" Sua mao: ");
    lcd_1.print(mao);
  }  // ########################
  
  

  else {
    lcd_1.print(" voce comprou: ");
    lcd_1.setCursor(0, 1);
    lcd_1.write(byte(naipe));
    if (carta != 10) {
      lcd_1.print(carta);
    } else {
      lcd_1.print("K");
    }
    lcd_1.print(" Sua mao: ");
    lcd_1.print(mao);
  }
  if (modo == 0 && vez != 1) {
    medir(mao);
  }
  if (modo == 1) {
    medir(mao);
  }
  Serial.println(mao);
  delay(2500);

  return mao;
}

void imprimeCartas1() {
  if (digitalRead(botaoMao) == LOW) {
    int k = 0;
    for (k = 0; k < 8; k++) {
      int carta = cartasMao1[k];
      Serial.print(k);
      Serial.print("\nNaipe ");
      Serial.print(naipesMao1[k]);
      Serial.print("\nCartas ");
      Serial.print(carta);
      Serial.print("\n");

      if (naipesMao1[k] <= 3) {
        lcd_1.write(byte(naipesMao1[k]));
      }
      if (carta != 0) {
        if (carta != 1 && carta != 10) {
          lcd_1.print(carta);
        } else if (carta == 1) {
          lcd_1.print("A");
        } else if (carta == 10) {
          lcd_1.print("K");
        }
      }
    }
  }
  else {
    lcd_1.setCursor(0, 1);
    lcd_1.print("                ");
    lcd_1.setCursor(0, 1);
    lcd_1.print(index1);
    lcd_1.print(" Cartas");
  }
}

void imprimeCartas2() {
  if (digitalRead(botaoMao) == LOW) {
    int k = 0;
    for (k = 0; k < 8; k++) {
      int carta = cartasMao2[k];
      Serial.print(k);
      Serial.print("\nNaipe ");
      Serial.print(naipesMao2[k]);
      Serial.print("\nCartas ");
      Serial.print(cartasMao2[k]);
      Serial.print("\n");

      if (naipesMao2[k] <= 3) {
        lcd_1.write(byte(naipesMao2[k]));
      }
      if (carta != 0) {
        if (carta != 1 && carta != 10) {
          lcd_1.print(carta);
        } else if (carta == 1) {
          lcd_1.print("A");
        } else if (carta == 10) {
          lcd_1.print("K");
        }
      }
    }
  }
  else {
    lcd_1.setCursor(0, 1);
    lcd_1.print("                ");
    lcd_1.setCursor(0, 1);
    lcd_1.print(index2);
    lcd_1.print(" Cartas");
  }
}

void passou(byte vez) {

  lcd_1.clear();
  lcd_1.print("P");
  if (modo == 1 || (modo == 0 && vez == 0)) {
    lcd_1.print(vez + 1);
  } else if (modo == 0 && vez != 0) {
    lcd_1.print("C");
  }
  lcd_1.print(" passou a vez!");
  delay(2500);
}

void fim() {
  medidor.write(45);
  lcd_1.clear();
  lcd_1.print("Fim! ");
  if (mao1 == 21 || mao2 > 21) {
    lcd_1.print("P1 ");
  }
  if (mao1 > 21 || mao2 == 21) {
    if (modo == 1) {
      lcd_1.print("P2 ");
    } else {
      lcd_1.print("PC ");
    }
  }
  if (mao1 == 21 || mao2 == 21) {
    lcd_1.print("fez 21!");
  } else {
    lcd_1.print("ganhou!");
  }
  lcd_1.setCursor(0, 1);
  lcd_1.print("P1 - ");
  lcd_1.print(mao1);
  if (modo == 1) {
    lcd_1.print(", P2 - ");
  } else {
    lcd_1.print(", PC - ");
  }
  lcd_1.print(mao2);
}

void girar() {

  /*int i = 0;
    while(i <= 6){
      meuServo.write(30);
      delay(600);
      meuServo.write(100);
      delay(600);
      i++;
    }
    meuServo.write(0);
    */
  int i = 0;
  for (i = 0; i < 8; i++){
  medidor.write(45);
  meuServo.write(0);
  delay(800);
  meuServo.write(180);
  delay(800);
  Serial.print("Rodou 1");
  }
}

void medir(byte mao) {

    med = 45;
    if (mao >= 11 && mao < 21) {
      med = 45 + ((mao - 11) * 9);
    }
    if (mao >= 21) {
      med = 135;
    }

    medidor.write(med);
  
}

void ligarDica1(byte mao){

  if (digitalRead(botaoMao) == HIGH && tavaOff == false) {
          tavaOff = true;
    if (medidor.read() != 45){
          medidor.write(45);
    	  Serial.print("\nDESLIGOU DICA\n");
    }
    lcd_1.setCursor(0, 1);
    lcd_1.print("                ");
    lcd_1.setCursor(0, 1);
    lcd_1.print(index1);
    lcd_1.print(" Cartas");
          
        }
        if (tavaOff == true && digitalRead(botaoMao) == LOW){
          medir(mao);
          lcd_1.setCursor(0, 1);
          lcd_1.print("                ");
          lcd_1.setCursor(0, 1);
          imprimeCartas1();
          tavaOff = false;
        }
}

void ligarDica2(byte mao){

  if (digitalRead(botaoMao) == HIGH && tavaOff == false) {
          tavaOff = true;
    if (medidor.read() != 45){
          medidor.write(45);
    	  Serial.print("\nDESLIGOU DICA\n");
    }
    lcd_1.setCursor(0, 1);
    lcd_1.print("                ");
    lcd_1.setCursor(0, 1);
    lcd_1.print(index2);
    lcd_1.print(" Cartas");
          
          
        }
        if (tavaOff == true && digitalRead(botaoMao) == LOW){
          medir(mao);
          lcd_1.setCursor(0, 1);
          lcd_1.print("                ");
    	  lcd_1.setCursor(0, 1);
          imprimeCartas2();
          Serial.print("LIGOU DICA");
          tavaOff = false;
        }
}

void setup() {
  lcd_1.init();
  lcd_1.backlight();
  lcd_1.createChar(0, coracao);
  lcd_1.createChar(1, ouro);
  lcd_1.createChar(2, espada);
  lcd_1.createChar(3, paus);
  pinMode(botaoMao, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  attachInterrupt(0, comando1, RISING);
  pinMode(3, OUTPUT);
  attachInterrupt(1, comando2, RISING);
  randomSeed(analogRead(0));
  digitalWrite(13, HIGH);
  meuServo.attach(10);  // Associa o servo motor ao pino digital 6 do Arduino
  medidor.attach(9);
  medidor.write(45);
  meuServo.write(92);
  Serial.print(cartasMao1[8]);

  // Print a message to the LCD.
  lcd_1.setCursor(0, 0);
  lcd_1.print(" Blackjack - 21");
  lcd_1.setCursor(1, 1);

  byte i = 0;
  while (i < 3) {
    lcd_1.write(byte(0));
    lcd_1.write(byte(1));
    lcd_1.write(byte(2));
    lcd_1.write(byte(3));
    lcd_1.print(" ");
    i = i + 1;
  }
}

void loop() {
  // tela de titulo
  if (estado == 1) {
    if (c1 == true) {
      modo = 0;
      estado = 2;
      c1 = false;
      lcd_1.clear();
      lcd_1.print("Vez do P1 - Mao:");
      vez = 0;
      lcd_1.setCursor(0, 1);
      imprimeCartas1();
    }
    if (c2 == true) {
      modo = 1;
      estado = 2;
      c2 = false;
      lcd_1.clear();
      lcd_1.print("Vez do P1 - Mao:");
      vez = 0;
      lcd_1.setCursor(0, 1);
      imprimeCartas1();
    }
  }

  // jogo
  if (estado == 2) {

    if (modo == 0) {  // PvE
      if (vez == 0 && estado != 3) {

        ligarDica1(mao1);

        if (c1 == true) {
          mao1 = mostrarCarta(mao1, vez);
          agiu = 1;
          c1 = false;
        }
        if (c2 == true) {
          passou(vez);
          agiu = 1;
          c2 = false;
        }
        if (agiu == 1) {
          if (mao1 > 21) {
            estado = 3;
          }
          if (mao1 == 21) {
            estado = 3;
          }
          vez = 1;
        }
        c1 = false;
        c2 = false;
      }

      if (vez == 1 && estado != 3) {
        agiu = 0;
        lcd_1.clear();
        lcd_1.print("Vez do PC - Mao:");
        lcd_1.setCursor(0, 1);
        imprimeCartas2();
        delay(2500);
        cE = random(8);
        if (mao2 <= 10) {
          mao2 = mostrarCarta(mao2, vez);
        }

        else if (mao2 > 10 && mao2 <= 15) {

          if (cE <= 5 || mao1 > mao2) {
            mao2 = mostrarCarta(mao2, vez);
          } else {
            passou(vez);
          }
        } else if (mao2 > 15 && mao2 <= 20) {

          if (cE <= 1 || mao1 > mao2) {
            mao2 = mostrarCarta(mao2, vez);
          } else {
            passou(vez);
          }
        }
        c1 = false;
        c2 = false;
        if (mao2 > 21) {
          estado = 3;
        }
        if (mao2 == 21) {
          estado = 3;
        }
        lcd_1.clear();
        if (estado != 3) {
          lcd_1.print("Vez do P1 - Mao:");
          lcd_1.setCursor(0, 1);
          imprimeCartas1();
        }
        medir(mao1);
        vez = 0;
        c1 = false;
        c2 = false;
      }
    }

    if (modo == 1) {
      if (vez == 0 && estado != 3) {

        ligarDica1(mao1);

        if (c1 == true) {
          mao1 = mostrarCarta(mao1, vez);
          agiu = 1;
          c1 = false;
        }
        if (c2 == true) {
          passou(vez);
          agiu = 1;
          c2 = false;
        }
        if (agiu == 1) {
          if (mao1 > 21) {
            estado = 3;
          }
          if (mao1 == 21) {
            estado = 3;
          }
          vez = 1;
          lcd_1.clear();
          if (estado != 3) {
            lcd_1.print("Vez do P2 - Mao:");
            lcd_1.setCursor(0, 1);
            imprimeCartas2();
          }
          medir(mao2);
        }
      }

      if (vez == 1 && estado != 3) {

        ligarDica2(mao2);
        agiu = 0;
        if (c1 == true) {
          mao2 = mostrarCarta(mao2, vez);
          agiu = 1;
          c1 = false;
        }
        if (c2 == true) {
          passou(vez);
          agiu = 1;
          c2 = false;
        }
        if (agiu == 1) {
          if (mao2 > 21) {
            estado = 3;
          }
          if (mao2 == 21) {
            estado = 3;
          }
          lcd_1.clear();
          if (estado != 3) {
            lcd_1.print("Vez do P1 - Mao:");
            lcd_1.setCursor(0, 1);
            imprimeCartas1();
          }
          medir(mao1);
          vez = 0;
          agiu = 0;
          c1 = false;
          c2 = false;
        }
      }
    }
  }

  if (estado == 3) {
    fim();
    mao1 = 0;
    mao2 = 0;
    vez = 0;
    for (int i = 0; i <= 8; i++) {

      cartasMao1[i] = 0;
      naipesMao1[i] = 5;
      cartasMao2[i] = 0;
      naipesMao2[i] = 5;
    }
    index1 = 0;
    index2 = 0;
    delay(1500);
    girar();

    c1 = false;
    c2 = false;
    lcd_1.clear();
    lcd_1.print(" Blackjack - 21");
    lcd_1.setCursor(1, 1);

    byte i = 0;
    while (i < 3) {
      lcd_1.write(byte(0));
      lcd_1.write(byte(1));
      lcd_1.write(byte(2));
      lcd_1.write(byte(3));
      lcd_1.print(" ");
      i = i + 1;
    }
    estado = 1;
  }
}
