void  ControlAtas() {
  if (ph_value[0] < 6) { /* -- PH 1 -- */
    PompaAtasUp_On();
    PompaAtasDown_Off();
  } else if (ph_value[0] > 9) {
    PompaAtasDown_On();
    PompaAtasUp_Off();
  } else {
    PompaAtasUp_Off();
    PompaAtasDown_Off();
  }
  if (suhu_value[0] < 28) { /* -- SUHU 1 -- */
    LampuAtas_On();
    KipasAtas_Off();
  } else if (suhu_value[0] > 35) {
    KipasAtas_On();
    LampuAtas_Off();
  } else {
    LampuAtas_Off();
    KipasAtas_Off();
  }
  if (moisture_value[0] < 60) {/* -- KELEMBABAN 1 -- */
    PompaAtas_On();
  } else {
    PompaAtas_Off();
  }
}
void ControlTengah() {
  if (ph_value[1] < 6) { /* -- PH 2 -- */
    PompaTengahUp_On();
    PompaTengahDown_Off();
  } else if (ph_value[1] > 9) {
    PompaTengahDown_On();
    PompaTengahUp_Off();
  } else {
    PompaTengahUp_Off();
    PompaTengahDown_Off();
  }
  if (suhu_value[1] < 28) { /* -- SUHU 2 -- */
    LampuTengah_On();
    KipasTengah_Off();
  } else if (suhu_value[1] > 35) {
    KipasTengah_On();
    LampuTengah_Off();
  } else {
    LampuTengah_Off();
    KipasTengah_Off();
  }
  if (moisture_value[1] < 60) { /* -- KELEMBABAN 2 -- */
    PompaTengah_On();
  } else {
    PompaTengah_Off();
  }
}
void ControlBawah() {
  if (ph_value[2] < 6) { /* -- PH 3 -- */
    PompaBawahUp_On();
    PompaAtasDown_Off();
  } else if (ph_value[2] > 9) {
    PompaBawahDown_On();
    PompaBawahUp_Off();
  } else {
    PompaBawahUp_Off();
    PompaAtasDown_Off();
  }

  if (suhu_value[2] < 28) { /* -- SUHU 3 -- */
    LampuBawah_On();
    KipasBawah_Off();
  } else if (suhu_value[2] > 35) {
    KipasBawah_On();
    LampuBawah_Off();
  } else {
    LampuBawah_Off();
    KipasBawah_Off();
  }
  if (moisture_value[2] < 60) { /* -- KELEMBABAN 3 -- */
    PompaBawah_On();
  } else {
    PompaBawah_Off();
  }
}
void LCD_Control() {
  if (millis() - u_time[0] >= 4000) {
    u_time[0] = millis();

    if (flag_lcd == 0) {
      lcd.setCursor(3, 0);
      lcd.print("MEDIA 1          ");
      lcd.setCursor(3, 1);
      lcd.print("Suhu = " + String(suhu_value[0]) + " *C   ");
      lcd.setCursor(3, 2);
      lcd.print("Kelembapan = " + String(moisture_value[0]) + " %  ");
      lcd.setCursor(3, 3);
      lcd.print("Ph = " + String(ph_value[0]));
      flag_lcd += 1;
    }
    else if (flag_lcd == 1) {
      lcd.setCursor(3, 0);
      lcd.print("MEDIA 2         ");
      lcd.setCursor(3, 1);
      lcd.print("Suhu = " + String(suhu_value[1]) + " *C   ");
      lcd.setCursor(3, 2);
      lcd.print("Kelembapan = " + String(moisture_value[1]) + " %  ");
      lcd.setCursor(3, 3);
      lcd.print("Ph = " + String(ph_value[1]));

      flag_lcd += 1;
    }

    else if (flag_lcd == 2) {
      lcd.setCursor(3, 0);
      lcd.print("MEDIA 3      ");
      lcd.setCursor(3, 1);
      lcd.print("Suhu = " + String(suhu_value[2]) + " *C  ");
      lcd.setCursor(3, 2);
      lcd.print("Kelembapan = " + String(moisture_value[2]) + " %  ");
      lcd.setCursor(3, 3);
      lcd.print("Ph = " + String(ph_value[2]));

      flag_lcd = 0;
    }

  }
}
