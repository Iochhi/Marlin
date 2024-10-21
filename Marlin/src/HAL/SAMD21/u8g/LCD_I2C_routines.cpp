/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2022 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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

/**
<<<<<<<< HEAD:Marlin/src/HAL/SAMD21/u8g/LCD_I2C_routines.cpp
 * SAMD21 HAL developed by Bart Meijer (brupje)
 * Based on SAMD51 HAL by Giuliano Zaro (AKA GMagician)
 */
// adapted from  I2C/master/master.c example
//   https://www-users.cs.york.ac.uk/~pcc/MCP/HAPR-Course-web/CMSIS/examples/html/master_8c_source.html

#ifdef __SAMD21__

#endif // __SAMD21__
========
 * DWIN G-code thumbnail preview
 * Author: Miguel A. Risco-Castillo
 * version: 3.1.2
 * Date: 2022/09/03
 */

class Preview {
public:
  static void drawFromSD();
  static void invalidate();
  static bool valid();
  static void show();
private:
  static bool hasPreview();
};

extern Preview preview;
>>>>>>>> bugfix-2.1.x:Marlin/src/lcd/e3v2/proui/gcode_preview.h
