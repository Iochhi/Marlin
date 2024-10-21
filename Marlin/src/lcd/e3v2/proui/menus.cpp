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
 * Menu functions for ProUI
 * Author: Miguel A. Risco-Castillo
<<<<<<< HEAD
 * Version: 1.9.1
 * Date: 2022/12/02
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
=======
 * Version: 1.10.1
 * Date: 2022/05/01
>>>>>>> bugfix-2.1.x
 */

#include "../../../inc/MarlinConfigPre.h"

#if ENABLED(DWIN_LCD_PROUI)

#include "../common/encoder.h"
<<<<<<< HEAD
#include "dwin_lcd.h"
#include "dwinui.h"
=======
>>>>>>> bugfix-2.1.x
#include "dwin.h"
#include "menus.h"

int8_t MenuItemTotal = 0;
int8_t MenuItemCount = 0;
<<<<<<< HEAD
CustomMenuItemClass** MenuItems = nullptr;
MenuClass *CurrentMenu = nullptr;
MenuClass *PreviousMenu = nullptr;
MenuData_t MenuData;

// Menuitem Drawing functions =================================================

void Draw_Title(TitleClass* title) {
  DWIN_Draw_Rectangle(1, HMI_data.TitleBg_Color, 0, 0, DWIN_WIDTH - 1, TITLE_HEIGHT - 1);
  if (title->frameid)
    DWIN_Frame_AreaCopy(title->frameid, title->frame.left, title->frame.top, title->frame.right, title->frame.bottom, 14, (TITLE_HEIGHT - (title->frame.bottom - title->frame.top)) / 2 - 1);
  else
    #if ENABLED(TITLE_CENTERED)
      DWINUI::Draw_CenteredString(false, DWIN_FONT_HEAD, HMI_data.TitleTxt_Color, HMI_data.TitleBg_Color, (TITLE_HEIGHT - DWINUI::fontHeight(DWIN_FONT_HEAD)) / 2 - 1, title->caption);
    #else
      DWIN_Draw_String(false, DWIN_FONT_HEAD, HMI_data.TitleTxt_Color, HMI_data.TitleBg_Color, 14, (TITLE_HEIGHT - DWINUI::fontHeight(DWIN_FONT_HEAD)) / 2 - 1, title->caption);
    #endif
}

void Draw_Menu(MenuClass* menu) {
  DWINUI::SetColors(HMI_data.Text_Color, HMI_data.Background_Color, HMI_data.StatusBg_Color);
  DWIN_Draw_Rectangle(1, DWINUI::backcolor, 0, TITLE_HEIGHT, DWIN_WIDTH - 1, STATUS_Y - 1);
}

void Draw_Menu_Cursor(const int8_t line) {
  const uint16_t ypos = MYPOS(line);
  DWINUI::Draw_Box(1, HMI_data.Cursor_Color, {0, ypos, 15, MLINE - 1});
}

void Erase_Menu_Cursor(const int8_t line) {
  const uint16_t ypos = MYPOS(line);
  DWINUI::Draw_Box(1, HMI_data.Background_Color, {0, ypos, 15, MLINE - 1});
}

void Erase_Menu_Text(const int8_t line) {
  if (line < 0 || line >= TROWS) return;
  const uint16_t ypos = MYPOS(line) + 1;
  DWINUI::Draw_Box(1, HMI_data.Background_Color, {LBLX, ypos, DWIN_WIDTH - LBLX, MLINE - 2});
}

void Draw_Menu_Line(const uint8_t line, const uint8_t icon /*=0*/, const char * const label /*=nullptr*/, bool more /*=false*/, bool selected /*=false*/) {
  if (icon)  DWINUI::Draw_Icon(icon, ICOX, MBASE(line) - 3);
  if (label) DWINUI::Draw_String(LBLX, MBASE(line) - 1, (char*)label);
  if (more)  DWINUI::Draw_Icon(ICON_More, VALX + 16, MBASE(line) - 3);
  if (selected) Draw_Menu_Cursor(line);
  DWIN_Draw_HLine(HMI_data.SplitLine_Color, 16, MYPOS(line + 1), 240);
}

void Draw_Menu_Line(const uint8_t line, const uint8_t icon /*=0*/, FSTR_P label /*=nullptr*/, bool more /*=false*/, bool selected /*=false*/) {
  Draw_Menu_Line(line, icon, FTOP(label), more, selected);
}

void Draw_Chkb_Line(const uint8_t line, const bool checked) {
  DWINUI::Draw_Checkbox(HMI_data.Text_Color, HMI_data.Background_Color, VALX + 3 * DWINUI::fontWidth(), MBASE(line) - 1, checked);
}

void Show_Chkb_Line(const bool checked) {
  const uint8_t line = CurrentMenu->line();
  DWINUI::Draw_Checkbox(HMI_data.Text_Color, HMI_data.Background_Color, VALX + 3 * DWINUI::fontWidth(), MBASE(line) - 1, checked);
  DWIN_UpdateLCD();
}

void Toggle_Chkb_Line(bool &checked) {
  checked = !checked;
  Show_Chkb_Line(checked);
}

void Draw_Menu_IntValue(uint16_t bcolor, const uint8_t line, uint8_t iNum, const int32_t value /*=0*/) {
  DWINUI::Draw_Signed_Int(HMI_data.Text_Color, bcolor, iNum , VALX, MBASE(line) - 1, value);
}

void onDrawMenuItem(MenuItemClass* menuitem, int8_t line) {
  if (menuitem->icon) DWINUI::Draw_Icon(menuitem->icon, ICOX, MBASE(line) - 3);
  if (menuitem->frameid)
    DWIN_Frame_AreaCopy(menuitem->frameid, menuitem->frame.left, menuitem->frame.top, menuitem->frame.right, menuitem->frame.bottom, LBLX, MBASE(line));
  else if (menuitem->caption)
    DWINUI::Draw_String(LBLX, MBASE(line) - 1, menuitem->caption);
  DWIN_Draw_HLine(HMI_data.SplitLine_Color, 16, MYPOS(line + 1), 240);
}

void onDrawSubMenu(MenuItemClass* menuitem, int8_t line) {
  onDrawMenuItem(menuitem, line);
  DWINUI::Draw_Icon(ICON_More, VALX + 16, MBASE(line) - 3);
}

void onDrawIntMenu(MenuItemClass* menuitem, int8_t line, int32_t value) {
  onDrawMenuItem(menuitem, line);
  Draw_Menu_IntValue(HMI_data.Background_Color, line, 4, value);
}

void onDrawPIntMenu(MenuItemClass* menuitem, int8_t line) {
  const int16_t value = *(int16_t*)static_cast<MenuItemPtrClass*>(menuitem)->value;
  onDrawIntMenu(menuitem, line, value);
}

void onDrawPInt8Menu(MenuItemClass* menuitem, int8_t line) {
  const uint8_t value = *(uint8_t*)static_cast<MenuItemPtrClass*>(menuitem)->value;
  onDrawIntMenu(menuitem, line, value);
}

void onDrawPInt32Menu(MenuItemClass* menuitem, int8_t line) {
  const uint32_t value = *(uint32_t*)static_cast<MenuItemPtrClass*>(menuitem)->value;
  onDrawIntMenu(menuitem, line, value);
}

void onDrawFloatMenu(MenuItemClass* menuitem, int8_t line, uint8_t dp, const float value) {
  onDrawMenuItem(menuitem, line);
  DWINUI::Draw_Signed_Float(HMI_data.Text_Color, HMI_data.Background_Color, 3, dp, VALX - dp * DWINUI::fontWidth(DWIN_FONT_MENU), MBASE(line), value);
}

void onDrawPFloatMenu(MenuItemClass* menuitem, int8_t line, uint8_t dp) {
  const float value = *(float*)static_cast<MenuItemPtrClass*>(menuitem)->value;
  onDrawFloatMenu(menuitem, line, dp, value);
}

void onDrawChkbMenu(MenuItemClass* menuitem, int8_t line, bool checked) {
  onDrawMenuItem(menuitem, line);
  Draw_Chkb_Line(line, checked);
}

void onDrawChkbMenu(MenuItemClass* menuitem, int8_t line) {
  const bool val = *(bool*)static_cast<MenuItemPtrClass*>(menuitem)->value;
=======
CustomMenuItem** menuItems = nullptr;
Menu *currentMenu = nullptr;
Menu *previousMenu = nullptr;
MenuData_t menuData;

// Menuitem Drawing functions =================================================

void drawTitle(Title* aTitle) {
  dwinDrawRectangle(1, hmiData.colorTitleBg, 0, 0, DWIN_WIDTH - 1, TITLE_HEIGHT - 1);
  if (aTitle->frameid)
    dwinFrameAreaCopy(aTitle->frameid, aTitle->frame.left, aTitle->frame.top, aTitle->frame.right, aTitle->frame.bottom, 14, (TITLE_HEIGHT - (aTitle->frame.bottom - aTitle->frame.top)) / 2 - 1);
  else
    #if ENABLED(TITLE_CENTERED)
      DWINUI::drawCenteredString(false, DWIN_FONT_HEAD, hmiData.colorTitleTxt, hmiData.colorTitleBg, (TITLE_HEIGHT - DWINUI::fontHeight(DWIN_FONT_HEAD)) / 2 - 1, aTitle->caption);
    #else
      dwinDrawString(false, DWIN_FONT_HEAD, hmiData.colorTitleTxt, hmiData.colorTitleBg, 14, (TITLE_HEIGHT - DWINUI::fontHeight(DWIN_FONT_HEAD)) / 2 - 1, aTitle->caption);
    #endif
}

void drawMenuCursor(const int8_t line) {
  const uint16_t ypos = MYPOS(line);
  DWINUI::drawBox(1, hmiData.colorCursor, {0, ypos, 15, MLINE - 1});
}

void eraseMenuCursor(const int8_t line) {
  const uint16_t ypos = MYPOS(line);
  DWINUI::drawBox(1, hmiData.colorBackground, {0, ypos, 15, MLINE - 1});
}

void eraseMenuText(const int8_t line) {
  if (line < 0 || line >= TROWS) return;
  const uint16_t ypos = MYPOS(line) + 1;
  DWINUI::drawBox(1, hmiData.colorBackground, {LBLX, ypos, DWIN_WIDTH - LBLX, MLINE - 2});
}

void drawMenuLine(const uint8_t line, const uint8_t icon/*=0*/, const char * const label/*=nullptr*/, bool more/*=false*/, bool selected/*=false*/) {
  if (icon)  DWINUI::drawIcon(icon, ICOX, MBASE(line) - 3);
  if (label) DWINUI::drawString(LBLX, MBASE(line) - 1, (char*)label);
  if (more)  DWINUI::drawIcon(ICON_More, VALX + 16, MBASE(line) - 3);
  if (selected) drawMenuCursor(line);
  dwinDrawHLine(hmiData.colorSplitLine, 16, MYPOS(line + 1), 240);
}

void drawMenuLine(const uint8_t line, const uint8_t icon/*=0*/, FSTR_P label/*=nullptr*/, bool more/*=false*/, bool selected/*=false*/) {
  drawMenuLine(line, icon, FTOP(label), more, selected);
}

void drawCheckboxLine(const uint8_t line, const bool checked) {
  DWINUI::drawCheckbox(hmiData.colorText, hmiData.colorBackground, VALX + 3 * DWINUI::fontWidth(), MBASE(line) - 1, checked);
}

void showCheckboxLine(const bool checked) {
  const uint8_t line = currentMenu->line();
  DWINUI::drawCheckbox(hmiData.colorText, hmiData.colorBackground, VALX + 3 * DWINUI::fontWidth(), MBASE(line) - 1, checked);
  dwinUpdateLCD();
}

void toggleCheckboxLine(bool &checked) {
  checked = !checked;
  showCheckboxLine(checked);
}

void drawMenuIntValue(uint16_t bcolor, const uint8_t line, uint8_t iNum, const int32_t value/*=0*/) {
  DWINUI::drawSignedInt(hmiData.colorText, bcolor, iNum , VALX, MBASE(line) - 1, value);
}

void onDrawMenuItem(MenuItem* menuitem, int8_t line) {
  if (menuitem->icon) DWINUI::drawIcon(menuitem->icon, ICOX, MBASE(line) - 3);
  if (menuitem->frameid)
    dwinFrameAreaCopy(menuitem->frameid, menuitem->frame.left, menuitem->frame.top, menuitem->frame.right, menuitem->frame.bottom, LBLX, MBASE(line));
  else
    DWINUI::drawString(LBLX, MBASE(line) - 1, menuitem->caption);
  dwinDrawHLine(hmiData.colorSplitLine, 16, MYPOS(line + 1), 240);
}

void onDrawSubMenu(MenuItem* menuitem, int8_t line) {
  onDrawMenuItem(menuitem, line);
  DWINUI::drawIcon(ICON_More, VALX + 16, MBASE(line) - 3);
}

void onDrawIntMenu(MenuItem* menuitem, int8_t line, int32_t value) {
  onDrawMenuItem(menuitem, line);
  drawMenuIntValue(hmiData.colorBackground, line, 4, value);
}

void onDrawPIntMenu(MenuItem* menuitem, int8_t line) {
  const int16_t value = *(int16_t*)static_cast<MenuItemPtr*>(menuitem)->value;
  onDrawIntMenu(menuitem, line, value);
}

void onDrawPInt8Menu(MenuItem* menuitem, int8_t line) {
  const uint8_t value = *(uint8_t*)static_cast<MenuItemPtr*>(menuitem)->value;
  onDrawIntMenu(menuitem, line, value);
}

void onDrawPInt32Menu(MenuItem* menuitem, int8_t line) {
  const uint32_t value = *(uint32_t*)static_cast<MenuItemPtr*>(menuitem)->value;
  onDrawIntMenu(menuitem, line, value);
}

void onDrawFloatMenu(MenuItem* menuitem, int8_t line, uint8_t dp, const float value) {
  onDrawMenuItem(menuitem, line);
  DWINUI::drawSignedFloat(hmiData.colorText, hmiData.colorBackground, 3, dp, VALX - dp * DWINUI::fontWidth(DWIN_FONT_MENU), MBASE(line), value);
}

void onDrawPFloatMenu(MenuItem* menuitem, int8_t line, uint8_t dp) {
  const float value = *(float*)static_cast<MenuItemPtr*>(menuitem)->value;
  onDrawFloatMenu(menuitem, line, dp, value);
}

void onDrawChkbMenu(MenuItem* menuitem, int8_t line, bool checked) {
  onDrawMenuItem(menuitem, line);
  drawCheckboxLine(line, checked);
}

void onDrawChkbMenu(MenuItem* menuitem, int8_t line) {
  const bool val = *(bool*)static_cast<MenuItemPtr*>(menuitem)->value;
>>>>>>> bugfix-2.1.x
  onDrawChkbMenu(menuitem, line, val);
}

void DrawItemEdit(const bool selected) {
<<<<<<< HEAD
  const uint16_t bcolor = selected ? HMI_data.Selected_Color : HMI_data.Background_Color;
  const uint8_t iNum = 4 - ((MenuData.dp > 0) ? (MenuData.dp - 1) : 0);
  switch (checkkey) {
    case SetIntNoDraw:  if (MenuData.LiveUpdate) MenuData.LiveUpdate(); break;
    case SetInt:
    case SetPInt:       DWINUI::Draw_Signed_Int(HMI_data.Text_Color, bcolor, iNum , VALX, MBASE(CurrentMenu->line()) - 1, MenuData.Value); break;
    case SetFloat:
    case SetPFloat:     DWINUI::Draw_Signed_Float(HMI_data.Text_Color, bcolor, iNum, MenuData.dp, VALX - 2 * DWINUI::fontWidth(), MBASE(CurrentMenu->line()), MenuData.Value / POW(10, MenuData.dp)); break;
=======
  const uint16_t bcolor = selected ? hmiData.colorSelected : hmiData.colorBackground;
  const uint8_t iNum = 4 - ((menuData.dp > 0) ? (menuData.dp - 1) : 0);
  switch (checkkey) {
    case ID_SetIntNoDraw: if (menuData.liveUpdate) menuData.liveUpdate(); break;
    case ID_SetInt:
    case ID_SetPInt:    DWINUI::drawSignedInt(hmiData.colorText, bcolor, iNum , VALX, MBASE(currentMenu->line()) - 1, menuData.value); break;
    case ID_SetFloat:
    case ID_SetPFloat:  DWINUI::drawSignedFloat(hmiData.colorText, bcolor, iNum, menuData.dp, VALX - 2 * DWINUI::fontWidth(), MBASE(currentMenu->line()), menuData.value / POW(10, menuData.dp)); break;
>>>>>>> bugfix-2.1.x
    default: break;
  }
}

//-----------------------------------------------------------------------------
// On click functions
//-----------------------------------------------------------------------------

// Generic onclick event without draw
//  process: process id HMI destiny
//  lo: low limit
//  hi: high limit
//  dp: decimal places, 0 for integers
//  val: value / scaled value
<<<<<<< HEAD
//  LiveUpdate: live update function when the encoder changes
//  Apply: update function when the encoder is pressed
void SetOnClick(uint8_t process, const int32_t lo, const int32_t hi, uint8_t dp, const int32_t val, void (*Apply)() /*= nullptr*/, void (*LiveUpdate)() /*= nullptr*/) {
  checkkey = process;
  MenuData.MinValue = lo;
  MenuData.MaxValue = hi;
  MenuData.dp = dp;
  MenuData.Apply = Apply;
  MenuData.LiveUpdate = LiveUpdate;
  MenuData.Value = constrain(val, lo, hi);
  EncoderRate.enabled = true;
=======
//  liveUpdate: live update function when the encoder changes
//  apply: update function when the encoder is pressed
void setOnClick(uint8_t process, const int32_t lo, const int32_t hi, uint8_t dp, const int32_t val, void (*apply)()/*=nullptr*/, void (*liveUpdate)()/*=nullptr*/) {
  checkkey = process;
  menuData.minValue = lo;
  menuData.maxValue = hi;
  menuData.dp = dp;
  menuData.apply = apply;
  menuData.liveUpdate = liveUpdate;
  menuData.value = constrain(val, lo, hi);
  encoderRate.enabled = true;
>>>>>>> bugfix-2.1.x
}

// Generic onclick event for integer values
//  process: process id HMI destiny
//  lo: scaled low limit
//  hi: scaled high limit
//  val: value
<<<<<<< HEAD
//  LiveUpdate: live update function when the encoder changes
//  Apply: update function when the encoder is pressed
void SetValueOnClick(uint8_t process, const int32_t lo, const int32_t hi, const int32_t val, void (*Apply)() /*= nullptr*/, void (*LiveUpdate)() /*= nullptr*/) {
  SetOnClick(process, lo, hi, 0, val, Apply, LiveUpdate);
=======
//  liveUpdate: live update function when the encoder changes
//  apply: update function when the encoder is pressed
void setValueOnClick(uint8_t process, const int32_t lo, const int32_t hi, const int32_t val, void (*apply)()/*=nullptr*/, void (*liveUpdate)()/*=nullptr*/) {
  setOnClick(process, lo, hi, 0, val, apply, liveUpdate);
>>>>>>> bugfix-2.1.x
  DrawItemEdit(true);
}

// Generic onclick event for float values
//  process: process id HMI destiny
//  lo: scaled low limit
//  hi: scaled high limit
//  val: value
<<<<<<< HEAD
//  LiveUpdate: live update function when the encoder changes
//  Apply: update function when the encoder is pressed
void SetValueOnClick(uint8_t process, const float lo, const float hi, uint8_t dp, const float val, void (*Apply)() /*= nullptr*/, void (*LiveUpdate)() /*= nullptr*/) {
  const int32_t value =  round(val * POW(10, dp));
  SetOnClick(process, lo * POW(10, dp), hi * POW(10, dp), dp, value, Apply, LiveUpdate);
=======
//  liveUpdate: live update function when the encoder changes
//  apply: update function when the encoder is pressed
void setValueOnClick(uint8_t process, const float lo, const float hi, uint8_t dp, const float val, void (*apply)()/*=nullptr*/, void (*liveUpdate)()/*=nullptr*/) {
  const int32_t value =  round(val * POW(10, dp));
  setOnClick(process, lo * POW(10, dp), hi * POW(10, dp), dp, value, apply, liveUpdate);
>>>>>>> bugfix-2.1.x
  DrawItemEdit(true);
}

// Generic onclick event for integer values
//  lo: scaled low limit
//  hi: scaled high limit
//  val: value
<<<<<<< HEAD
//  LiveUpdate: live update function when the encoder changes
//  Apply: update function when the encoder is pressed
void SetIntOnClick(const int32_t lo, const int32_t hi, const int32_t val, void (*Apply)() /*= nullptr*/, void (*LiveUpdate)() /*= nullptr*/) {
  SetValueOnClick(SetInt, lo, hi, val, Apply, LiveUpdate);
=======
//  liveUpdate: live update function when the encoder changes
//  apply: update function when the encoder is pressed
void setIntOnClick(const int32_t lo, const int32_t hi, const int32_t val, void (*apply)()/*=nullptr*/, void (*liveUpdate)()/*=nullptr*/) {
  setValueOnClick(ID_SetInt, lo, hi, val, apply, liveUpdate);
>>>>>>> bugfix-2.1.x
}

// Generic onclick event for set pointer to 16 bit uinteger values
//  lo: low limit
//  hi: high limit
<<<<<<< HEAD
//  LiveUpdate: live update function when the encoder changes
//  Apply: update function when the encoder is pressed
void SetPIntOnClick(const int32_t lo, const int32_t hi, void (*Apply)() /*= nullptr*/, void (*LiveUpdate)() /*= nullptr*/) {
  MenuData.P_Int = (int16_t*)static_cast<MenuItemPtrClass*>(CurrentMenu->SelectedItem())->value;
  const int32_t value = *MenuData.P_Int;
  SetValueOnClick(SetPInt, lo, hi, value, Apply, LiveUpdate);
=======
//  liveUpdate: live update function when the encoder changes
//  apply: update function when the encoder is pressed
void setPIntOnClick(const int32_t lo, const int32_t hi, void (*apply)()/*=nullptr*/, void (*liveUpdate)()/*=nullptr*/) {
  menuData.intPtr = (int16_t*)static_cast<MenuItemPtr*>(currentMenu->selectedItem())->value;
  const int32_t value = *menuData.intPtr;
  setValueOnClick(ID_SetPInt, lo, hi, value, apply, liveUpdate);
>>>>>>> bugfix-2.1.x
}

// Generic onclick event for float values
//  process: process id HMI destiny
//  lo: low limit
//  hi: high limit
//  dp: decimal places
//  val: value
<<<<<<< HEAD
void SetFloatOnClick(const float lo, const float hi, uint8_t dp, const float val, void (*Apply)() /*= nullptr*/, void (*LiveUpdate)() /*= nullptr*/) {
  SetValueOnClick(SetFloat, lo, hi, dp, val, Apply, LiveUpdate);
=======
void setFloatOnClick(const float lo, const float hi, uint8_t dp, const float val, void (*apply)()/*=nullptr*/, void (*liveUpdate)()/*=nullptr*/) {
  setValueOnClick(ID_SetFloat, lo, hi, dp, val, apply, liveUpdate);
>>>>>>> bugfix-2.1.x
}

// Generic onclick event for set pointer to float values
//  lo: low limit
//  hi: high limit
<<<<<<< HEAD
//  LiveUpdate: live update function when the encoder changes
//  Apply: update function when the encoder is pressed
void SetPFloatOnClick(const float lo, const float hi, uint8_t dp, void (*Apply)() /*= nullptr*/, void (*LiveUpdate)() /*= nullptr*/) {
  MenuData.P_Float = (float*)static_cast<MenuItemPtrClass*>(CurrentMenu->SelectedItem())->value;
  SetValueOnClick(SetPFloat, lo, hi, dp, *MenuData.P_Float, Apply, LiveUpdate);
=======
//  liveUpdate: live update function when the encoder changes
//  apply: update function when the encoder is pressed
void setPFloatOnClick(const float lo, const float hi, uint8_t dp, void (*apply)()/*=nullptr*/, void (*liveUpdate)()/*=nullptr*/) {
  menuData.floatPtr = (float*)static_cast<MenuItemPtr*>(currentMenu->selectedItem())->value;
  setValueOnClick(ID_SetPFloat, lo, hi, dp, *menuData.floatPtr, apply, liveUpdate);
>>>>>>> bugfix-2.1.x
}

// HMI Control functions ======================================================

// Generic menu control using the encoder
<<<<<<< HEAD
void HMI_Menu() {
  EncoderState encoder_diffState = get_encoder_state();
  if (CurrentMenu) {
    if (encoder_diffState == ENCODER_DIFF_NO) return;
    if (encoder_diffState == ENCODER_DIFF_ENTER)
      CurrentMenu->onClick();
    else
      CurrentMenu->onScroll(encoder_diffState == ENCODER_DIFF_CW);
=======
void hmiMenu() {
  const EncoderState encoder_diffState = get_encoder_state();
  if (currentMenu) {
    if (encoder_diffState == ENCODER_DIFF_NO) return;
    if (encoder_diffState == ENCODER_DIFF_ENTER)
      currentMenu->onClick();
    else
      currentMenu->onScroll(encoder_diffState == ENCODER_DIFF_CW);
>>>>>>> bugfix-2.1.x
  }
}

// Get a value using the encoder
// draw : draw the value
// Return value:
//  0 : no change
//  1 : live change
//  2 : apply change
<<<<<<< HEAD
int8_t HMI_Get(bool draw) {
  const int32_t lo = MenuData.MinValue;
  const int32_t hi = MenuData.MaxValue;
  const int32_t cval = MenuData.Value;
  EncoderState encoder_diffState = get_encoder_state();
  if (encoder_diffState != ENCODER_DIFF_NO) {
    if (Apply_Encoder(encoder_diffState, MenuData.Value)) {
      EncoderRate.enabled = false;
      if (draw) DrawItemEdit(false);
      checkkey = Menu;
      return 2;
    }
    LIMIT(MenuData.Value, lo, hi);
  }
  const bool change = cval != MenuData.Value;
=======
int8_t hmiGet(bool draw) {
  const int32_t lo = menuData.minValue, hi = menuData.maxValue, cval = menuData.value;
  const EncoderState encoder_diffState = TERN(SMOOTH_ENCODER_MENUITEMS, get_encoder_state(), encoderReceiveAnalyze());
  if (encoder_diffState != ENCODER_DIFF_NO) {
    if (applyEncoder(encoder_diffState, menuData.value)) {
      encoderRate.enabled = false;
      if (draw) DrawItemEdit(false);
      checkkey = ID_Menu;
      return 2;
    }
    LIMIT(menuData.value, lo, hi);
  }
  const bool change = cval != menuData.value;
>>>>>>> bugfix-2.1.x
  if (change) DrawItemEdit(true);
  return int8_t(change);
}

// Set and draw a value using the encoder
<<<<<<< HEAD
void HMI_SetDraw() {
  int8_t val = HMI_Get(true);
  switch (val) {
    case 0: return;
    case 1: if (MenuData.LiveUpdate) MenuData.LiveUpdate(); break;
    case 2: if (MenuData.Apply) MenuData.Apply(); break;
=======
void hmiSetDraw() {
  const int8_t val = hmiGet(true);
  switch (val) {
    case 0: return;
    case 1: if (menuData.liveUpdate) menuData.liveUpdate(); break;
    case 2: if (menuData.apply) menuData.apply(); break;
>>>>>>> bugfix-2.1.x
  }
}

// Set an value without drawing
<<<<<<< HEAD
void HMI_SetNoDraw() {
  int8_t val = HMI_Get(false);
  switch (val) {
    case 0: return;
    case 1: if (MenuData.LiveUpdate) MenuData.LiveUpdate(); break;
    case 2: if (MenuData.Apply) MenuData.Apply(); break;
=======
void hmiSetNoDraw() {
  const int8_t val = hmiGet(false);
  switch (val) {
    case 0: return;
    case 1: if (menuData.liveUpdate) menuData.liveUpdate(); break;
    case 2: if (menuData.apply) menuData.apply(); break;
>>>>>>> bugfix-2.1.x
  }
}

// Set an integer pointer variable using the encoder
<<<<<<< HEAD
void HMI_SetPInt() {
  int8_t val = HMI_Get(true);
  switch (val) {
    case 0: return;
    case 1: if (MenuData.LiveUpdate) MenuData.LiveUpdate(); break;
    case 2: *MenuData.P_Int = MenuData.Value; if (MenuData.Apply) MenuData.Apply(); break;
=======
void hmiSetPInt() {
  const int8_t val = hmiGet(true);
  switch (val) {
    case 0: return;
    case 1: if (menuData.liveUpdate) menuData.liveUpdate(); break;
    case 2: *menuData.intPtr = menuData.value; if (menuData.apply) menuData.apply(); break;
>>>>>>> bugfix-2.1.x
  }
}

// Set a scaled float pointer variable using the encoder
<<<<<<< HEAD
void HMI_SetPFloat() {
  const int8_t val = HMI_Get(true);
  switch (val) {
    case 0: return;
    case 1: if (MenuData.LiveUpdate) MenuData.LiveUpdate(); break;
    case 2: *MenuData.P_Float = MenuData.Value / POW(10, MenuData.dp); if (MenuData.Apply) MenuData.Apply(); break;
=======
void hmiSetPFloat() {
  const int8_t val = hmiGet(true);
  switch (val) {
    case 0: return;
    case 1: if (menuData.liveUpdate) menuData.liveUpdate(); break;
    case 2: *menuData.floatPtr = menuData.value / POW(10, menuData.dp); if (menuData.apply) menuData.apply(); break;
>>>>>>> bugfix-2.1.x
  }
}

// Menu Class ===============================================================

<<<<<<< HEAD
MenuClass::MenuClass() {
=======
Menu::Menu() {
>>>>>>> bugfix-2.1.x
  selected = 0;
  topline = 0;
}

<<<<<<< HEAD
void MenuClass::draw() {
  MenuTitle.draw();
  Draw_Menu(this);
  for (int8_t i = 0; i < MenuItemCount; i++)
    MenuItems[i]->draw(i - topline);
  Draw_Menu_Cursor(line());
  DWIN_UpdateLCD();
}

void MenuClass::onScroll(bool dir) {
=======
void Menu::draw() {
  menuTitle.draw();
  DWINUI::setColors(hmiData.colorText, hmiData.colorBackground, hmiData.colorStatusBg);
  dwinDrawRectangle(1, DWINUI::backColor, 0, TITLE_HEIGHT, DWIN_WIDTH - 1, STATUS_Y - 1);
  for (int8_t i = 0; i < MenuItemCount; i++)
    menuItems[i]->draw(i - topline);
  drawMenuCursor(line());
  dwinUpdateLCD();
}

void Menu::onScroll(bool dir) {
>>>>>>> bugfix-2.1.x
  int8_t sel = selected;
  if (dir) sel++; else sel--;
  LIMIT(sel, 0, MenuItemCount - 1);
  if (sel != selected) {
<<<<<<< HEAD
    Erase_Menu_Cursor(line());
    DWIN_UpdateLCD();
    if ((sel - topline) == TROWS) {
      DWIN_Frame_AreaMove(1, DWIN_SCROLL_UP, MLINE, DWINUI::backcolor, 0, TITLE_HEIGHT + 1, DWIN_WIDTH, STATUS_Y - 1);
      topline++;
      MenuItems[sel]->draw(TROWS - 1);
    }
    if ((sel < topline)) {
      DWIN_Frame_AreaMove(1, DWIN_SCROLL_DOWN, MLINE, DWINUI::backcolor, 0, TITLE_HEIGHT + 1, DWIN_WIDTH, STATUS_Y - 1);
      topline--;
      MenuItems[sel]->draw(0);
    }
    selected = sel;
    Draw_Menu_Cursor(line());
    DWIN_UpdateLCD();
  }
}

void MenuClass::onClick() {
  if (MenuItems[selected]->onClick != nullptr) (*MenuItems[selected]->onClick)();
}

CustomMenuItemClass *MenuClass::SelectedItem() {
  return MenuItems[selected];
}

CustomMenuItemClass** MenuClass::Items() {
  return MenuItems;
}

int8_t MenuClass::count() {
  return MenuItemCount;
};

/* MenuItem Class ===========================================================*/

void CustomMenuItemClass::draw(int8_t line) {
  if (line < 0 || line >= TROWS) return;
  if (onDraw != nullptr) (*onDraw)(static_cast<MenuItemClass*>(this), line);
};

void CustomMenuItemClass::redraw(bool erase /*=false*/) {
  const int8_t line = CurrentMenu->line(this->pos);
  if (erase) Erase_Menu_Text(line);
  draw(line);
}

CustomMenuItemClass::CustomMenuItemClass(OnDrawItem ondraw, OnClickItem onclick) {
=======
    eraseMenuCursor(line());
    dwinUpdateLCD();
    if ((sel - topline) == TROWS) {
      dwinFrameAreaMove(1, DWIN_SCROLL_UP, MLINE, DWINUI::backColor, 0, TITLE_HEIGHT + 1, DWIN_WIDTH, STATUS_Y - 1);
      topline++;
      menuItems[sel]->draw(TROWS - 1);
    }
    if ((sel < topline)) {
      dwinFrameAreaMove(1, DWIN_SCROLL_DOWN, MLINE, DWINUI::backColor, 0, TITLE_HEIGHT + 1, DWIN_WIDTH, STATUS_Y - 1);
      topline--;
      menuItems[sel]->draw(0);
    }
    selected = sel;
    drawMenuCursor(line());
    dwinUpdateLCD();
  }
}

void Menu::onClick() {
  if (menuItems[selected]->onClick != nullptr) (*menuItems[selected]->onClick)();
}

CustomMenuItem *Menu::selectedItem() {
  return menuItems[selected];
}

CustomMenuItem** Menu::items() {
  return menuItems;
}

int8_t Menu::count() {
  return MenuItemCount;
}

/* MenuItem Class ===========================================================*/

void CustomMenuItem::draw(int8_t line) {
  if (line < 0 || line >= TROWS) return;
  if (onDraw != nullptr) (*onDraw)(static_cast<MenuItem*>(this), line);
}

void CustomMenuItem::redraw(bool erase/*=false*/) {
  const int8_t line = currentMenu->line(this->pos);
  if (erase) eraseMenuText(line);
  draw(line);
}

CustomMenuItem::CustomMenuItem(OnDrawItem ondraw, OnClickItem onclick) {
>>>>>>> bugfix-2.1.x
  onClick = onclick;
  onDraw =  ondraw;
}

<<<<<<< HEAD
MenuItemClass::MenuItemClass(uint8_t cicon, const char * const text, OnDrawItem ondraw, OnClickItem onclick) : CustomMenuItemClass(ondraw, onclick) {
  icon = cicon;
  SetCaption(text);
}

MenuItemClass::MenuItemClass(uint8_t cicon, uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, OnDrawItem ondraw, OnClickItem onclick) : CustomMenuItemClass(ondraw, onclick) {
=======
MenuItem::MenuItem(uint8_t cicon, const char * const text, OnDrawItem ondraw, OnClickItem onclick) : CustomMenuItem(ondraw, onclick) {
  icon = cicon;
  setCaption(text);
}

MenuItem::MenuItem(uint8_t cicon, uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, OnDrawItem ondraw, OnClickItem onclick) : CustomMenuItem(ondraw, onclick) {
>>>>>>> bugfix-2.1.x
  icon = cicon;
  caption[0] = '\0';
  frameid = id;
  frame = { x1, y1, x2, y2 };
}

<<<<<<< HEAD
void MenuItemClass::SetCaption(const char * const text) {
=======
void MenuItem::setCaption(const char * const text) {
>>>>>>> bugfix-2.1.x
  const uint8_t len = _MIN(sizeof(caption) - 1, strlen(text));
  memcpy(&caption[0], text, len);
  caption[len] = '\0';
}

<<<<<<< HEAD
void MenuItemClass::SetFrame(uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
=======
void MenuItem::setFrame(uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
>>>>>>> bugfix-2.1.x
  caption[0] = '\0';
  frameid = id;
  frame = { x1, y1, x2, y2 };
}

<<<<<<< HEAD
MenuItemPtrClass::MenuItemPtrClass(uint8_t cicon, const char * const text, OnDrawItem ondraw, OnClickItem onclick, void* val) : MenuItemClass(cicon, text, ondraw, onclick) {
  value = val;
};

// Menu auxiliary functions ===================================================

void MenuItemsClear() {
  if (MenuItems == nullptr) return;
  for (int8_t i = 0; i < MenuItemCount; i++) delete MenuItems[i];
  delete[] MenuItems;
  MenuItems = nullptr;
=======
MenuItemPtr::MenuItemPtr(uint8_t cicon, const char * const text, OnDrawItem ondraw, OnClickItem onclick, void* val) : MenuItem(cicon, text, ondraw, onclick) {
  value = val;
}

// Menu auxiliary functions ===================================================

void menuItemsClear() {
  if (menuItems == nullptr) return;
  for (int8_t i = 0; i < MenuItemCount; i++) delete menuItems[i];
  delete[] menuItems;
  menuItems = nullptr;
>>>>>>> bugfix-2.1.x
  MenuItemCount = 0;
  MenuItemTotal = 0;
}

<<<<<<< HEAD
void MenuItemsPrepare(int8_t totalitems) {
  MenuItemsClear();
  MenuItemTotal = _MIN(totalitems, MENU_MAX_ITEMS);
  MenuItems = new CustomMenuItemClass*[totalitems];
}

bool IsMenu(MenuClass* _menu) {
  return ((checkkey == Menu) && !!CurrentMenu && (CurrentMenu == _menu));
}

template<typename T>
T* MenuItemAdd(T* menuitem) {
  MenuItems[MenuItemCount] = menuitem;
=======
void menuItemsPrepare(int8_t totalitems) {
  menuItemsClear();
  MenuItemTotal = _MIN(totalitems, MENU_MAX_ITEMS);
  menuItems = new CustomMenuItem*[totalitems];
}

bool isMenu(Menu* _menu) {
  return ((checkkey == ID_Menu) && !!currentMenu && (currentMenu == _menu));
}

template<typename T>
T* menuItemAdd(T* menuitem) {
  menuItems[MenuItemCount] = menuitem;
>>>>>>> bugfix-2.1.x
  menuitem->pos = MenuItemCount++;
  return menuitem;
}

<<<<<<< HEAD
CustomMenuItemClass* MenuItemAdd(OnDrawItem ondraw/*=nullptr*/, OnClickItem onclick/*=nullptr*/) {
  if (MenuItemCount < MenuItemTotal) {
    CustomMenuItemClass* menuitem = new CustomMenuItemClass(ondraw, onclick);
    return MenuItemAdd(menuitem);
=======
CustomMenuItem* menuItemAdd(OnDrawItem ondraw/*=nullptr*/, OnClickItem onclick/*=nullptr*/) {
  if (MenuItemCount < MenuItemTotal) {
    CustomMenuItem* menuitem = new CustomMenuItem(ondraw, onclick);
    return menuItemAdd(menuitem);
>>>>>>> bugfix-2.1.x
  }
  else return nullptr;
}

<<<<<<< HEAD
MenuItemClass* MenuItemAdd(uint8_t cicon, const char * const text/*=nullptr*/, OnDrawItem ondraw/*=nullptr*/, OnClickItem onclick/*=nullptr*/) {
  if (MenuItemCount < MenuItemTotal) {
    MenuItemClass* menuitem = new MenuItemClass(cicon, text, ondraw, onclick);
    return MenuItemAdd(menuitem);
=======
MenuItem* menuItemAdd(uint8_t cicon, const char * const text/*=nullptr*/, OnDrawItem ondraw/*=nullptr*/, OnClickItem onclick/*=nullptr*/) {
  if (MenuItemCount < MenuItemTotal) {
    MenuItem* menuitem = new MenuItem(cicon, text, ondraw, onclick);
    return menuItemAdd(menuitem);
>>>>>>> bugfix-2.1.x
  }
  else return nullptr;
}

<<<<<<< HEAD
MenuItemClass* MenuItemAdd(uint8_t cicon, uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, OnDrawItem ondraw/*=nullptr*/, OnClickItem onclick/*=nullptr*/) {
  if (MenuItemCount < MenuItemTotal) {
    MenuItemClass* menuitem = new MenuItemClass(cicon, id, x1, y1, x2, y2, ondraw, onclick);
    return MenuItemAdd(menuitem);
=======
MenuItem* menuItemAdd(uint8_t cicon, uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, OnDrawItem ondraw/*=nullptr*/, OnClickItem onclick/*=nullptr*/) {
  if (MenuItemCount < MenuItemTotal) {
    MenuItem* menuitem = new MenuItem(cicon, id, x1, y1, x2, y2, ondraw, onclick);
    return menuItemAdd(menuitem);
>>>>>>> bugfix-2.1.x
  }
  else return nullptr;
}

<<<<<<< HEAD
MenuItemClass* EditItemAdd(uint8_t cicon, const char * const text, OnDrawItem ondraw, OnClickItem onclick, void* val) {
  if (MenuItemCount < MenuItemTotal) {
    MenuItemClass* menuitem = new MenuItemPtrClass(cicon, text, ondraw, onclick, val);
    return MenuItemAdd(menuitem);
=======
MenuItem* editItemAdd(uint8_t cicon, const char * const text, OnDrawItem ondraw, OnClickItem onclick, void* val) {
  if (MenuItemCount < MenuItemTotal) {
    MenuItem* menuitem = new MenuItemPtr(cicon, text, ondraw, onclick, val);
    return menuItemAdd(menuitem);
>>>>>>> bugfix-2.1.x
  }
  else return nullptr;
}

<<<<<<< HEAD
void InitMenu() {
  PreviousMenu = nullptr;
  InvalidateMenu();
}

bool SetMenu(MenuClass* &menu, FSTR_P title, int8_t totalitems) {
  if (!menu) menu = new MenuClass();
  const bool NotCurrent = (CurrentMenu != menu);
  if (NotCurrent) {
    menu->MenuTitle.SetCaption(title);
    MenuItemsPrepare(totalitems);
  }
  return NotCurrent;
}

bool SetMenu(MenuClass* &menu, frame_rect_t cn, FSTR_P title, int8_t totalitems) {
  if (!menu) menu = new MenuClass();
  const bool NotCurrent = (CurrentMenu != menu);
  if (NotCurrent) {
    if (cn.w != 0)
      menu->MenuTitle.SetFrame(cn.x, cn.y, cn.w, cn.h);
    else
      menu->MenuTitle.SetCaption(title);
    MenuItemsPrepare(totalitems);
  }
  return NotCurrent;
}

void InvalidateMenu() {
  if (CurrentMenu) {
    CurrentMenu->topline = 0;
    CurrentMenu->selected = 0;
    CurrentMenu = nullptr;
  }
}

void UpdateMenu(MenuClass* &menu) {
  if (!menu) return;
  if (CurrentMenu != menu) {
    PreviousMenu = CurrentMenu;
    CurrentMenu = menu;
=======
void initMenu() {
  currentMenu = nullptr;
  previousMenu = nullptr;
}

bool setMenu(Menu* &menu, FSTR_P fTitle, int8_t totalitems) {
  if (!menu) menu = new Menu();
  const bool notCurrent = (currentMenu != menu);
  if (notCurrent) {
    menu->menuTitle.setCaption(fTitle);
    menuItemsPrepare(totalitems);
  }
  return notCurrent;
}

bool setMenu(Menu* &menu, frame_rect_t cn, FSTR_P fTitle, int8_t totalitems) {
  if (!menu) menu = new Menu();
  const bool notCurrent = (currentMenu != menu);
  if (notCurrent) {
    if (cn.w != 0)
      menu->menuTitle.setFrame(cn.x, cn.y, cn.w, cn.h);
    else
      menu->menuTitle.setCaption(fTitle);
    menuItemsPrepare(totalitems);
  }
  return notCurrent;
}

void resetMenu(Menu* &menu) {
  if (menu) {
    menu->topline = 0;
    menu->selected = 0;
  }
}

void invalidateMenu() {
  resetMenu(currentMenu);
  currentMenu = nullptr;
}

void updateMenu(Menu* &menu) {
  if (!menu) return;
  if (currentMenu != menu) {
    previousMenu = currentMenu;
    currentMenu = menu;
>>>>>>> bugfix-2.1.x
  }
  menu->draw();
}

<<<<<<< HEAD
void ReDrawMenu(bool force /*= false*/) {
  if (CurrentMenu && (force || checkkey==Menu)) CurrentMenu->draw();
  if (force) DrawItemEdit(true);
}

=======
void ReDrawMenu(bool force/*=false*/) {
  if (currentMenu && (force || checkkey == ID_Menu)) currentMenu->draw();
  if (force) DrawItemEdit(true);
}

void ReDrawItem() {
  static_cast<MenuItem*>(currentMenu->selectedItem())->redraw(false);
}

>>>>>>> bugfix-2.1.x
#endif // DWIN_LCD_PROUI
