void LCD_mainMenu() {
  if      (customKey == 'A') {
    _mode = MonitoringMode;
    _PZEMMode = PZEMMenu;
  }
  else if (customKey == 'B') {
    _mode = TempMode;
  }
  else if (customKey == 'C') {
    _mode = MainControl;
    _ctrlMode = CtrlMenuCondition;
  }
  else if (customKey == 'D') {
    _mode = ExtrasMode;
  }
  else if (customKey == 'E') _mode = MenuMode;
  else if (customKey == 'F') _mode = ResetMode;
  switch (_mode) {
    case MenuMode:
      lcd.setCursor(0, 0);
      lcd.print(String(HHMMMSS[0]) + " ");
      lcd.setCursor(2, 0);
      lcd.print(":");
      lcd.setCursor(3, 0);
      lcd.print(String(HHMMMSS[1]) + "   ");
      lcd.setCursor(8, 0);
      lcd.print(String(YYMMDD[0]) + "/");
      lcd.setCursor(13, 0);
      lcd.print(String(YYMMDD[1]) + " ");
      lcd.setCursor(15, 0);
      lcd.print("/");
      lcd.setCursor(16, 0);
      lcd.print(String(YYMMDD[2]) + " ");
      lcd.setCursor(0, 1);
      lcd.print("A.PZEM Condition    ");
      lcd.setCursor(0, 2);
      lcd.print("B.Humidity Condition");
      lcd.setCursor(0, 3);
      lcd.print("C.Actuator Condition");
      break;
    case MonitoringMode:
      switch (_PZEMMode) {
        case PZEMMenu:
          lcd.setCursor(0, 0);
          lcd.print("   PZEM MONITORING  ");
          lcd.setCursor(0, 1);
          lcd.print("1.PZEM A Condition  ");
          lcd.setCursor(0, 2);
          lcd.print("2.PZEM B Condition  ");
          lcd.setCursor(0, 3);
          lcd.print("3.PZEM C Condition  ");
          if ((_mode == MonitoringMode) and (customKey == '1')) _PZEMMode = PZEMA;
          else if ((_mode == MonitoringMode) and (customKey == '2')) _PZEMMode = PZEMB;
          else if ((_mode == MonitoringMode) and (customKey == '3')) _PZEMMode = PZEMC;
          break;
        case PZEMA:
          lcd.setCursor(0, 0);
          lcd.print("Voltage A = " + String(voltage[0]) + "   ");
          lcd.setCursor(0, 1);
          lcd.print("Current A = " + String(current[0]) + "   ");
          lcd.setCursor(0, 2);
          lcd.print("Power A = " + String(power[0]) + "      ");
          lcd.setCursor(0, 3);
          lcd.print("Energy A = " + String(energy[0]) + "     ");
          break;
        case PZEMB:
          lcd.setCursor(0, 0);
          lcd.print("Voltage B = " + String(voltage[1]) + "   ");
          lcd.setCursor(0, 1);
          lcd.print("Current B = " + String(current[1]) + "   ");
          lcd.setCursor(0, 2);
          lcd.print("Power B = " + String(power[1]) + "      ");
          lcd.setCursor(0, 3);
          lcd.print("Energy B = " + String(energy[1]) + "     ");
          break;
        case PZEMC:
          lcd.setCursor(0, 0);
          lcd.print("Voltage C = " + String(voltage[2]) + "   ");
          lcd.setCursor(0, 1);
          lcd.print("Current C = " + String(current[2]) + "   ");
          lcd.setCursor(0, 2);
          lcd.print("Power C = " + String(power[2]) + "      ");
          lcd.setCursor(0, 3);
          lcd.print("Energy C = " + String(energy[2]) + "     ");
          break;
      }
      break;
    case TempMode:
      lcd.setCursor(0, 0);
      lcd.print(" SUHU & KELEMBAPAN");
      lcd.setCursor(0, 1);
      lcd.print("Suhu = " + String(bme_val[0]) + "  *C    ");
      lcd.setCursor(0, 2);
      lcd.print("Kelembaban = " + String(bme_val[1]) + " %");
      lcd.setCursor(0, 3);
      lcd.print("                    ");
      break;
    case MainControl:
      switch (_ctrlMode) {
        case CtrlMenuCondition:
          lcd.setCursor(0, 0);
          lcd.print("   CONTROL MENU     ");
          lcd.setCursor(0, 1);
          lcd.print("1. RELAY Condition  ");
          lcd.setCursor(0, 2);
          lcd.print("2. LAMP Condition   ");
          lcd.setCursor(0, 3);
          lcd.print("3. MOTOR Condition  ");
          if ((_mode == MainControl) and (customKey == '1')) _ctrlMode = RelayCondition;
          else if ((_mode == MainControl) and (customKey == '2')) _ctrlMode = LampCondition;
          else if ((_mode == MainControl) and (customKey == '3')) _ctrlMode = MotorCondition;
          break;
        case RelayCondition:
          if ((!stateRelay[2]) and (customKey == '1')) stateRelay[2] = 1;
          else if ((stateRelay[2]) and (customKey == '1')) stateRelay[2] = 0;
          if ((!stateRelay[1]) and (customKey == '2')) stateRelay[1] = 1;
          else if ((stateRelay[1]) and (customKey == '2')) stateRelay[1] = 0;
          if ((!stateRelay[0]) and (customKey == '3')) stateRelay[0] = 1;
          else if ((stateRelay[0]) and (customKey == '3')) stateRelay[0] = 0;

          lcd.setCursor(0, 0);
          lcd.print("   RELAY CONTROL    ");
          lcd.setCursor(0, 1);
          if (stateRelay[2] == 1) lcd.print("1. Relay Satu= ON.  ");
          else lcd.print("1. Relay Satu= OFF. ");
          lcd.setCursor(0, 2);
          if (stateRelay[1]) lcd.print("2. Relay Dua= ON.   ");
          else lcd.print("2. Relay Dua= OFF.  ");
          lcd.setCursor(0, 3);
          if (stateRelay[0]) lcd.print("3. Relay Tiga= ON.  ");
          else lcd.print("3. Relay Tiga= OFF. ");
          break;
        case LampCondition:
          lcd.setCursor(0, 0);
          lcd.print("     RBD DImmer     ");
          lcd.setCursor(0, 1);
          lcd.print("             <Up>   ");
          lcd.setCursor(0, 2);
          lcd.print("Value =      " + String(outVal) + "   ");
          lcd.setCursor(0, 3);
          lcd.print("            <Down>  ");
          if (customKey == '2') outVal += 20;
          else if (customKey == '8') outVal -= 20;

          if (outVal < 0) outVal = 0;
          else if (outVal > 100) outVal = 100;

          break;
        case MotorCondition:
          lcd.setCursor(0, 0);
          lcd.print("   MOTOR CONTROL    ");
          lcd.setCursor(0, 1);
          if (motorState[0]) lcd.print("1. CW         <ON> " + String(t_second_forward));
          else lcd.print("1. CW         <OFF> ");
          lcd.setCursor(0, 2);
          if (motorState[1]) lcd.print("2. CCW        <ON> " + String(t_second_backward));
          else lcd.print("2. CCW        <OFF> ");
          lcd.setCursor(0, 3);
          lcd.print("                    ");
          if (customKey == '1') motorState[0] = 1;
          else if (customKey == '2') motorState[1] = 1;
          break;
      }
      break;
    case ResetMode:
      ESP.restart();
      break;
  };
}
