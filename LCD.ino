// displays a simple splash screen on start up
void LCD_init(LiquidCrystal &lcd)
{
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    delay(500);
    lcd.clear();
}

// prints the gait name and current angular speed
void LCD_gait(LiquidCrystal &lcd, const Gait &g)
{
    lcd.clear();
    char line[17];
    lcd.setCursor(0, 0);
    snprintf(line, 16, "GAIT:  %s", g.name);
    lcd.print(line);
}
