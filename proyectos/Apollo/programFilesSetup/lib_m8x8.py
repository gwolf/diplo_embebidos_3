#!/usr/bin/env python
# -*- coding: utf-8 -*-

from constantes import constants

class device(object):

    NUM_DIGITS = 8
    
    def __init__(self, spi_bus = 0, spi_device = 0):

        import spidev

        self._buffer = [0] * self.NUM_DIGITS # 8(por pantalla) * [1,,2,,3...] pantallas conectadas
        self._spi = spidev.SpiDev() # Crea un objeto spi
        self._spi.open(spi_bus, spi_device) #Abre spi_bus(puerto), dispositivo (CS) 
        
        self.command(constants.MAX7219_REG_SCANLIMIT, 7)    # setea los registro para multiplexear los 8 digitos
        self.command(constants.MAX7219_REG_DECODEMODE, 0)   # no decodifica usamos matriz (no display de digitos)
        self.command(constants.MAX7219_REG_DISPLAYTEST, 0)  # no display test
        self.command(constants.MAX7219_REG_SHUTDOWN, 1)     # no utilizamos shutdown mode
        self.brightness(7)                                  # intensity: range: 0..15
        self.clear()


    def command(self, register, data):

        assert constants.MAX7219_REG_DECODEMODE <= register <= constants.MAX7219_REG_DISPLAYTEST
        self._write([register, data])


    def _write(self, data):

        self._spi.xfer2(list(data)) #transfiere un dato, list retorna una lista


    def pixel(self, x, y, value, redraw=True): 

        assert 0 <= x < len(self._buffer)   # manejo de error: valor de  0<x<8 
        assert 0 <= y < self.NUM_DIGITS     # 

        if value:
            self._buffer[x] |=  (1 << y)   #coloca el pixel en las coordenadas (x, y)
        else:
            self._buffer[x] &= ~(1 << y) #no coloca nada, apaga todos los leds
        if redraw:
            self.flush()

            
    def _preprocess_buffer(self, buf):

        return buf    

    def _values(self, position, buf):

        yield position + constants.MAX7219_REG_DIGIT0
        yield buf[(0 * self.NUM_DIGITS) + position]


    def flush(self):

        buf = self._preprocess_buffer(list(self._buffer))
        assert len(buf) == len(self._buffer), "Preprocessed buffer is wrong size"
        
        for posn in range(self.NUM_DIGITS):
            self._write(self._values(posn, buf))
    
    
    def brightness(self, intensity):

        assert 0 <= intensity < 16, "Invalid brightness: {0}".format(intensity)
        self.command(constants.MAX7219_REG_INTENSITY, intensity)


    def set_byte(self, position, value, redraw=True):

        assert constants.MAX7219_REG_DIGIT0 <= position <= constants.MAX7219_REG_DIGIT7, "Invalid digit/column: {0}".format(position)
        assert 0 <= value < 256, 'Value {0} outside range 0..255'.format(value)

        offset = (0 * self.NUM_DIGITS) + position - constants.MAX7219_REG_DIGIT0
        self._buffer[offset] = value

        if redraw:
            self.flush()

    def clear(self, deviceId=None):

          for position in range(self.NUM_DIGITS):
              self.set_byte(position + constants.MAX7219_REG_DIGIT0, 0, redraw=False)

          self.flush()


            

