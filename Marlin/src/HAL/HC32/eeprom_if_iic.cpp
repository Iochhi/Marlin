/**
 * Marlin 3D Printer Firmware
<<<<<<<< HEAD:Marlin/src/HAL/NATIVE_SIM/pinsDebug.cpp
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
========
 * Copyright (c) 2023 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
>>>>>>>> bugfix-2.1.x:Marlin/src/HAL/HC32/eeprom_if_iic.cpp
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

<<<<<<<< HEAD:Marlin/src/HAL/NATIVE_SIM/pinsDebug.cpp
#ifdef __PLAT_NATIVE_SIM__
========
/**
 * Platform-independent Arduino functions for I2C EEPROM.
 * Enable USE_SHARED_EEPROM if not supplied by the framework.
 */
#ifdef ARDUINO_ARCH_HC32
>>>>>>>> bugfix-2.1.x:Marlin/src/HAL/HC32/eeprom_if_iic.cpp

#include "../../inc/MarlinConfig.h"
#include "pinsDebug.h"

<<<<<<<< HEAD:Marlin/src/HAL/NATIVE_SIM/pinsDebug.cpp
int8_t ADC_pin_mode(pin_t pin) { return -1; }

int8_t get_pin_mode(const pin_t pin) { return VALID_PIN(pin) ? 0 : -1; }

bool GET_PINMODE(const pin_t pin) {
  const int8_t pin_mode = get_pin_mode(pin);
  if (pin_mode == -1 || pin_mode == ADC_pin_mode(pin)) // Invalid pin or active analog pin
    return false;

  return (Gpio::getMode(pin) != 0); // Input/output state
}

bool GET_ARRAY_IS_DIGITAL(const pin_t pin) {
  return !IS_ANALOG(pin) || get_pin_mode(pin) != ADC_pin_mode(pin);
}

void print_port(const pin_t) {}
void pwm_details(const pin_t) {}
bool pwm_status(const pin_t) { return false; }

#endif
========
#if ENABLED(IIC_BL24CXX_EEPROM)

#include "../../libs/BL24CXX.h"
#include "../shared/eeprom_if.h"

void eeprom_init() {
  BL24CXX::init();
}

void eeprom_write_byte(uint8_t *pos, unsigned char value) {
  const unsigned eeprom_address = (unsigned)pos;
  return BL24CXX::writeOneByte(eeprom_address, value);
}

uint8_t eeprom_read_byte(uint8_t *pos) {
  const unsigned eeprom_address = (unsigned)pos;
  return BL24CXX::readOneByte(eeprom_address);
}

#endif // IIC_BL24CXX_EEPROM
#endif // ARDUINO_ARCH_HC32
>>>>>>>> bugfix-2.1.x:Marlin/src/HAL/HC32/eeprom_if_iic.cpp
