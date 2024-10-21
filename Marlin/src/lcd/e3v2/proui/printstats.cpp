/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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
 * Print Stats page for PRO UI
<<<<<<< HEAD
 * Author: Miguel A. Risco-Castillo (MRISCOC)
 * Version: 1.4.2
=======
 * Based on the original work of: Miguel Risco-Castillo (MRISCOC)
 * https://github.com/mriscoc/Ender3V2S1
 * Version: 1.4.0
>>>>>>> bugfix-2.1.x
 * Date: 2022/12/03
 */

#include "../../../inc/MarlinConfigPre.h"

#if ALL(DWIN_LCD_PROUI, PRINTCOUNTER)

#include "printstats.h"

#include "../../../core/types.h"
#include "../../../MarlinCore.h"
#include "../../marlinui.h"
#include "../../../module/printcounter.h"
<<<<<<< HEAD
#include "dwin_lcd.h"
#include "dwinui.h"
#include "dwin_popup.h"
#include "dwin.h"

PrintStatsClass PrintStats;

void PrintStatsClass::Draw() {
  char buf[50] = "";
  char str[30] = "";
  constexpr int8_t MRG = 30;

  Title.ShowCaption(GET_TEXT_F(MSG_INFO_STATS_MENU));
  DWINUI::ClearMainArea();
  Draw_Popup_Bkgd();
  DWINUI::Draw_Button(BTN_Continue, 86, 250);
  printStatistics ps = print_job_timer.getStats();

  sprintf_P(buf, PSTR(S_FMT ": %i"), GET_TEXT(MSG_INFO_PRINT_COUNT), ps.totalPrints);
  DWINUI::Draw_String(MRG, 80, buf);
  sprintf_P(buf, PSTR(S_FMT ": %i"), GET_TEXT(MSG_INFO_COMPLETED_PRINTS), ps.finishedPrints);
  DWINUI::Draw_String(MRG, 100, buf);
  duration_t(print_job_timer.getStats().printTime).toDigital(str, true);
  sprintf_P(buf, PSTR(S_FMT ": %s"), GET_TEXT(MSG_INFO_PRINT_TIME), str);
  DWINUI::Draw_String(MRG, 120, buf);
  duration_t(print_job_timer.getStats().longestPrint).toDigital(str, true);
  sprintf_P(buf, PSTR(S_FMT ": %s"), GET_TEXT(MSG_INFO_PRINT_LONGEST), str);
  DWINUI::Draw_String(MRG, 140, buf);
  sprintf_P(buf, PSTR(S_FMT ": %s m"), GET_TEXT(MSG_INFO_PRINT_FILAMENT), dtostrf(ps.filamentUsed / 1000, 1, 2, str));
  DWINUI::Draw_String(MRG, 160, buf);
}

void PrintStatsClass::Reset() {
=======
#include "dwin.h"
#include "dwin_popup.h"

PrintStats printStats;

void PrintStats::draw() {
  char str[30] = "";
  constexpr int8_t MRG = 30;

  title.showCaption(GET_TEXT_F(MSG_INFO_STATS_MENU));
  DWINUI::clearMainArea();
  drawPopupBkgd();
  DWINUI::drawButton(BTN_Continue, 86, 250);
  printStatistics ps = print_job_timer.getStats();

  DWINUI::drawString(MRG,  80, TS(GET_TEXT_F(MSG_INFO_PRINT_COUNT), F(": "), ps.totalPrints));
  DWINUI::drawString(MRG, 100, TS(GET_TEXT_F(MSG_INFO_COMPLETED_PRINTS), F(": "), ps.finishedPrints));
  duration_t(print_job_timer.getStats().printTime).toDigital(str, true);
  DWINUI::drawString(MRG, 120, TS(GET_TEXT_F(MSG_INFO_PRINT_TIME), F(": "), str));
  duration_t(print_job_timer.getStats().longestPrint).toDigital(str, true);
  DWINUI::drawString(MRG, 140, TS(GET_TEXT_F(MSG_INFO_PRINT_LONGEST), F(": "), str));
  DWINUI::drawString(MRG, 160, TS(GET_TEXT_F(MSG_INFO_PRINT_FILAMENT), F(": "), p_float_t(ps.filamentUsed / 1000, 2), F(" m")));
}

void PrintStats::reset() {
>>>>>>> bugfix-2.1.x
  print_job_timer.initStats();
  DONE_BUZZ(true);
}

<<<<<<< HEAD
void Goto_PrintStats() {
  PrintStats.Draw();
  HMI_SaveProcessID(WaitResponse);
}

// Print Stats Reset popup
void Popup_ResetStats() { DWIN_Popup_ConfirmCancel(ICON_Info_0, GET_TEXT_F(MSG_RESET_STATS)); }
void OnClick_ResetStats() {
  if (HMI_flag.select_flag) PrintStatsClass::Reset();
  HMI_ReturnScreen();
}
void PrintStatsReset() { Goto_Popup(Popup_ResetStats, OnClick_ResetStats); }
=======
void gotoPrintStats() {
  printStats.draw();
  hmiSaveProcessID(ID_WaitResponse);
}

// Print Stats Reset popup
void popupResetStats() { dwinPopupConfirmCancel(ICON_Info_0, GET_TEXT_F(MSG_RESET_STATS)); }
void onClickResetStats() {
  if (hmiFlag.select_flag) printStats.reset();
  hmiReturnScreen();
}
void printStatsReset() { gotoPopup(popupResetStats, onClickResetStats); }
>>>>>>> bugfix-2.1.x

#endif // DWIN_LCD_PROUI && PRINTCOUNTER
