#!/usr/bin/python
#import
import time
import Adafruit_CharLCD as LCD

# Definiendo los pines que serán utilizados por el LCD

lcd_rs = 'P8_8'
lcd_en = 'P8_10'
lcd_d4 = 'P8_18'
lcd_d5 = 'P8_16'
lcd_d6 = 'P8_14'
lcd_d7 = 'P8_12'
lcd_backLight = 'P8_7'

#Se utilizan 2 columnas LCD
lcd_columns = 16
lcd_rows = 2

#Inicializando el display LCD
lcd = LCD.Adafruit_CharLCD(lcd_rs,lcd_en,lcd_d4,lcd_d5,lcd_d6,lcd_d7,lcd_columns,lcd_rows,lcd_backLight)

#test de Prueba
lcd.message('Hello\nStation X!')
time.sleep(5.0)

# Secuencias de prueba
lcd.clear()
lcd.show_cursor(True)
lcd.message('Parpadeando')

time.sleep(5.0)
lcd.show_cursor(False)
lcd.blink(False)


lcd.clear()
message = 'scroll'

lcd.message(message)

for i in range(lcd_columns-len(message)):
    time.sleep(0.5)
    lcd.move_right()
    
for i in range(lcd_columns-len(message)):
    rime.sleep(0.5)
    lcd.move_left()


lcd.clear()
lcd.message('Flash Backlight \nin 5 seconds')
time.sleep(5.0)

lcd.set_backlight(0)
time.sleep(2.0)

lcd.clear()
lcd.message('Adieu')
lcd.set(1)
lcd.blink(False)

