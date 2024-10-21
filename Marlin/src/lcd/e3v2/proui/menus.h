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
<<<<<<< HEAD
=======
#pragma once
>>>>>>> bugfix-2.1.x

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
 */
#pragma once
=======
 * Version: 1.10.1
 * Date: 2022/05/01
 */
>>>>>>> bugfix-2.1.x

#include "dwinui.h"

#define MENU_CHAR_LIMIT  24
<<<<<<< HEAD
#define MENU_MAX_ITEMS   TERN(SDSORT_LIMIT, SDSORT_LIMIT, 64)

typedef struct {
  int32_t MaxValue     = 0;        // Auxiliar max integer/scaled float value
  int32_t MinValue     = 0;        // Auxiliar min integer/scaled float value
  int8_t dp            = 0;        // Auxiliar decimal places
  int32_t Value        = 0;        // Auxiliar integer / scaled float value
  int16_t *P_Int       = nullptr;  // Auxiliar pointer to 16 bit integer variable
  float *P_Float       = nullptr;  // Auxiliar pointer to float variable
  void (*Apply)()      = nullptr;  // Auxiliar apply function
  void (*LiveUpdate)() = nullptr;  // Auxiliar live update function
} MenuData_t;

extern MenuData_t MenuData;
=======

#ifndef MENU_MAX_ITEMS
  #define MENU_MAX_ITEMS 100
#endif

typedef struct {
  int32_t maxValue     = 0;        // Auxiliar max integer/scaled float value
  int32_t minValue     = 0;        // Auxiliar min integer/scaled float value
  int8_t dp            = 0;        // Auxiliar decimal places
  int32_t value        = 0;        // Auxiliar integer / scaled float value
  int16_t *intPtr      = nullptr;  // Auxiliar pointer to 16 bit integer variable
  float *floatPtr      = nullptr;  // Auxiliar pointer to float variable
  void (*apply)()      = nullptr;  // Auxiliar apply function
  void (*liveUpdate)() = nullptr;  // Auxiliar live update function
} MenuData_t;

extern MenuData_t menuData;
>>>>>>> bugfix-2.1.x

// Auxiliary Macros ===========================================================

// Create and add a MenuItem object to the menu array
<<<<<<< HEAD
#define SET_MENU(I,L,V) SetMenu(I, GET_TEXT_F(L), V)
#define SET_MENU_F(I,L,V) SetMenu(I, F(L), V)
#define SET_MENU_R(I,R,L,V) SetMenu(I, R, GET_TEXT_F(L), V)

#define BACK_ITEM(H) MenuItemAdd(ICON_Back, GET_TEXT_F(MSG_BUTTON_BACK), onDrawMenuItem, H)
#define MENU_ITEM(I,L,V...) MenuItemAdd(I, GET_TEXT_F(L), V)
#define EDIT_ITEM(I,L,V...) EditItemAdd(I, GET_TEXT_F(L), V)
#define MENU_ITEM_F(I,L,V...) MenuItemAdd(I, F(L), V)
#define EDIT_ITEM_F(I,L,V...) EditItemAdd(I, F(L), V)

// Menu Classes ===============================================================

class CustomMenuItemClass;
class MenuItemClass;

typedef void (*OnDrawCustomItem)(CustomMenuItemClass*  menuitem, int8_t line);
typedef void (*OnDrawItem)(MenuItemClass*  menuitem, int8_t line);
typedef void (*OnClickItem)();

class CustomMenuItemClass {
=======
#define SET_MENU(I,L,V) setMenu(I, GET_TEXT_F(L), V)
#define SET_MENU_F(I,L,V) setMenu(I, F(L), V)
#define SET_MENU_R(I,R,L,V) setMenu(I, R, GET_TEXT_F(L), V)

#define BACK_ITEM(H) menuItemAdd(ICON_Back, GET_TEXT_F(MSG_BUTTON_BACK), onDrawMenuItem, H)
#define MENU_ITEM(I,L,V...) menuItemAdd(I, GET_TEXT_F(L), V)
#define EDIT_ITEM(I,L,V...) editItemAdd(I, GET_TEXT_F(L), V)
#define MENU_ITEM_F(I,L,V...) menuItemAdd(I, F(L), V)
#define EDIT_ITEM_F(I,L,V...) editItemAdd(I, F(L), V)

// Menu Classes ===============================================================

class CustomMenuItem;
class MenuItem;

typedef void (*OnDrawCustomItem)(CustomMenuItem* menuitem, int8_t line);
typedef void (*OnDrawItem)(MenuItem* menuitem, int8_t line);
typedef void (*OnClickItem)();

class CustomMenuItem {
>>>>>>> bugfix-2.1.x
public:
  int8_t pos = 0;
  OnDrawItem onDraw = nullptr;
  void (*onClick)() = nullptr;
<<<<<<< HEAD
  CustomMenuItemClass() {};
  CustomMenuItemClass(OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
  virtual ~CustomMenuItemClass(){};
=======
  CustomMenuItem() {};
  CustomMenuItem(OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
  virtual ~CustomMenuItem(){};
>>>>>>> bugfix-2.1.x
  virtual void draw(int8_t line);
  void redraw(bool erase=false);
};

<<<<<<< HEAD
class MenuItemClass: public CustomMenuItemClass {
=======
class MenuItem: public CustomMenuItem {
>>>>>>> bugfix-2.1.x
public:
  uint8_t icon = 0;
  char caption[MENU_CHAR_LIMIT] = "";
  uint8_t frameid = 0;
  rect_t frame = {0};
<<<<<<< HEAD
  using CustomMenuItemClass::CustomMenuItemClass;
  MenuItemClass(uint8_t cicon, const char * const text=nullptr, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
  MenuItemClass(uint8_t cicon, uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
  void SetFrame(uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
  void SetCaption(const char * const text = nullptr);
};

class MenuItemPtrClass: public MenuItemClass {
public:
  void *value = nullptr;
  using MenuItemClass::MenuItemClass;
  MenuItemPtrClass(uint8_t cicon, const char * const text, OnDrawItem ondraw, OnClickItem onclick, void* val);
  MenuItemPtrClass(uint8_t cicon, FSTR_P text, OnDrawItem ondraw, OnClickItem onclick, void* val) : MenuItemPtrClass(cicon, FTOP(text), ondraw, onclick, val){}
};

class MenuClass {
public:
  int8_t topline = 0;
  int8_t selected = 0;
  TitleClass MenuTitle;
  MenuClass();
  virtual ~MenuClass(){};
=======
  using CustomMenuItem::CustomMenuItem;
  MenuItem(uint8_t cicon, const char * const text=nullptr, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
  MenuItem(uint8_t cicon, uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
  void setFrame(uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
  void setCaption(const char * const text=nullptr);
};

class MenuItemPtr: public MenuItem {
public:
  void *value = nullptr;
  using MenuItem::MenuItem;
  MenuItemPtr(uint8_t cicon, const char * const text, OnDrawItem ondraw, OnClickItem onclick, void* val);
  MenuItemPtr(uint8_t cicon, FSTR_P text, OnDrawItem ondraw, OnClickItem onclick, void* val) : MenuItemPtr(cicon, FTOP(text), ondraw, onclick, val){}
};

class Menu {
public:
  int8_t topline = 0;
  int8_t selected = 0;
  Title menuTitle;
  Menu();
  virtual ~Menu(){};
>>>>>>> bugfix-2.1.x
  inline int8_t line() { return selected - topline; };
  inline int8_t line(uint8_t pos) {return pos - topline; };
  int8_t count();
  virtual void draw();
  virtual void onScroll(bool dir);
  void onClick();
<<<<<<< HEAD
  CustomMenuItemClass* SelectedItem();
  static CustomMenuItemClass** Items();
};
extern MenuClass *CurrentMenu;
extern MenuClass *PreviousMenu;

// Menuitem Drawing functions =================================================

void Draw_Title(TitleClass* title);
void Draw_Menu(MenuClass* menu);
void Draw_Menu_Cursor(const int8_t line);
void Erase_Menu_Cursor(const int8_t line);
void Erase_Menu_Text(const int8_t line);
void Draw_Menu_Line(const uint8_t line, const uint8_t icon=0, const char * const label=nullptr, bool more=false, bool selected=false);
void Draw_Menu_Line(const uint8_t line, const uint8_t icon=0, FSTR_P label=nullptr, bool more=false, bool selected=false);
void Draw_Chkb_Line(const uint8_t line, const bool checked);
void Show_Chkb_Line(const bool checked);
void Toggle_Chkb_Line(bool &checked);
void Draw_Menu_IntValue(uint16_t bcolor, const uint8_t line, uint8_t iNum, const int32_t value=0);
void onDrawMenuItem(MenuItemClass* menuitem, int8_t line);
void onDrawSubMenu(MenuItemClass* menuitem, int8_t line);
void onDrawIntMenu(MenuItemClass* menuitem, int8_t line, int32_t value);
void onDrawPIntMenu(MenuItemClass* menuitem, int8_t line);
void onDrawPInt8Menu(MenuItemClass* menuitem, int8_t line);
void onDrawPInt32Menu(MenuItemClass* menuitem, int8_t line);
void onDrawFloatMenu(MenuItemClass* menuitem, int8_t line, uint8_t dp, const float value);
void onDrawPFloatMenu(MenuItemClass* menuitem, int8_t line, uint8_t dp);
inline void onDrawPFloatMenu(MenuItemClass* menuitem, int8_t line) { onDrawPFloatMenu(menuitem, line, UNITFDIGITS); };
inline void onDrawPFloat2Menu(MenuItemClass* menuitem, int8_t line) { onDrawPFloatMenu(menuitem, line, 2); };
inline void onDrawPFloat3Menu(MenuItemClass* menuitem, int8_t line) { onDrawPFloatMenu(menuitem, line, 3); };
inline void onDrawPFloat4Menu(MenuItemClass* menuitem, int8_t line) { onDrawPFloatMenu(menuitem, line, 4); };
void onDrawChkbMenu(MenuItemClass* menuitem, int8_t line, bool checked);
void onDrawChkbMenu(MenuItemClass* menuitem, int8_t line);

// On click functions =========================================================

void SetOnClick(uint8_t process, const int32_t lo, const int32_t hi, uint8_t dp, const int32_t val, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);
void SetValueOnClick(uint8_t process, const int32_t lo, const int32_t hi, const int32_t val, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);
void SetValueOnClick(uint8_t process, const float lo, const float hi, uint8_t dp, const float val, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);
void SetIntOnClick(const int32_t lo, const int32_t hi, const int32_t val, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);
void SetPIntOnClick(const int32_t lo, const int32_t hi, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);
void SetFloatOnClick(const float lo, const float hi, uint8_t dp, const float val, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);
void SetPFloatOnClick(const float lo, const float hi, uint8_t dp, void (*Apply)() = nullptr, void (*LiveUpdate)() = nullptr);

// HMI user control functions =================================================

void HMI_Menu();
void HMI_SetDraw();
void HMI_SetNoDraw();
void HMI_SetPInt();
void HMI_SetPFloat();
=======
  CustomMenuItem* selectedItem();
  static CustomMenuItem** items();
};
extern Menu *currentMenu;
extern Menu *previousMenu;

// Menuitem Drawing functions =================================================

void drawTitle(Title* aTitle);
void drawMenuCursor(const int8_t line);
void eraseMenuCursor(const int8_t line);
void eraseMenuText(const int8_t line);
void drawMenuLine(const uint8_t line, const uint8_t icon=0, const char * const label=nullptr, bool more=false, bool selected=false);
void drawMenuLine(const uint8_t line, const uint8_t icon=0, FSTR_P label=nullptr, bool more=false, bool selected=false);
void drawCheckboxLine(const uint8_t line, const bool checked);
void showCheckboxLine(const bool checked);
void toggleCheckboxLine(bool &checked);
void drawMenuIntValue(uint16_t bcolor, const uint8_t line, uint8_t iNum, const int32_t value=0);
void onDrawMenuItem(MenuItem* menuitem, int8_t line);
void onDrawSubMenu(MenuItem* menuitem, int8_t line);
void onDrawIntMenu(MenuItem* menuitem, int8_t line, int32_t value);
void onDrawPIntMenu(MenuItem* menuitem, int8_t line);
void onDrawPInt8Menu(MenuItem* menuitem, int8_t line);
void onDrawPInt32Menu(MenuItem* menuitem, int8_t line);
void onDrawFloatMenu(MenuItem* menuitem, int8_t line, uint8_t dp, const float value);
void onDrawPFloatMenu(MenuItem* menuitem, int8_t line, uint8_t dp);
inline void onDrawPFloatMenu(MenuItem* menuitem, int8_t line) { onDrawPFloatMenu(menuitem, line, UNITFDIGITS); };
inline void onDrawPFloat2Menu(MenuItem* menuitem, int8_t line) { onDrawPFloatMenu(menuitem, line, 2); };
inline void onDrawPFloat3Menu(MenuItem* menuitem, int8_t line) { onDrawPFloatMenu(menuitem, line, 3); };
inline void onDrawPFloat4Menu(MenuItem* menuitem, int8_t line) { onDrawPFloatMenu(menuitem, line, 4); };
void onDrawChkbMenu(MenuItem* menuitem, int8_t line, bool checked);
void onDrawChkbMenu(MenuItem* menuitem, int8_t line);

// On click functions =========================================================

void setOnClick(uint8_t process, const int32_t lo, const int32_t hi, uint8_t dp, const int32_t val, void (*apply)()=nullptr, void (*liveUpdate)()=nullptr);
void setValueOnClick(uint8_t process, const int32_t lo, const int32_t hi, const int32_t val, void (*apply)()=nullptr, void (*liveUpdate)()=nullptr);
void setValueOnClick(uint8_t process, const float lo, const float hi, uint8_t dp, const float val, void (*apply)()=nullptr, void (*liveUpdate)()=nullptr);
void setIntOnClick(const int32_t lo, const int32_t hi, const int32_t val, void (*apply)()=nullptr, void (*liveUpdate)()=nullptr);
void setPIntOnClick(const int32_t lo, const int32_t hi, void (*apply)()=nullptr, void (*liveUpdate)()=nullptr);
void setFloatOnClick(const float lo, const float hi, uint8_t dp, const float val, void (*apply)()=nullptr, void (*liveUpdate)()=nullptr);
void setPFloatOnClick(const float lo, const float hi, uint8_t dp, void (*apply)()=nullptr, void (*liveUpdate)()=nullptr);

// HMI user control functions =================================================

void hmiMenu();
void hmiSetDraw();
void hmiSetNoDraw();
void hmiSetPInt();
void hmiSetPFloat();
>>>>>>> bugfix-2.1.x

// Menu auxiliary functions ===================================================

// Initialize menu
<<<<<<< HEAD
void InitMenu();

// Create a new menu
bool SetMenu(MenuClass* &menu, FSTR_P title, int8_t totalitems);
bool SetMenu(MenuClass* &menu, frame_rect_t cn, FSTR_P title, int8_t totalitems);

// Invalidate CurrentMenu to prepare for full menu drawing
void InvalidateMenu();

//Update the Menu and Draw if it is valid
void UpdateMenu(MenuClass* &menu);

//Redraw the current Menu if it is valid
void ReDrawMenu(bool force = false);

// Clear MenuItems array and free MenuItems elements
void MenuItemsClear();

// Prepare MenuItems array
void MenuItemsPrepare(int8_t totalitems);

// Is the current menu = menu?
bool IsMenu(MenuClass* menu);

// Add elements to the MenuItems array
CustomMenuItemClass* MenuItemAdd(OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
MenuItemClass* MenuItemAdd(uint8_t cicon, const char * const text=nullptr, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
inline MenuItemClass* MenuItemAdd(uint8_t cicon, FSTR_P text = nullptr, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr) {
  return MenuItemAdd(cicon, FTOP(text), ondraw, onclick);
}
MenuItemClass* MenuItemAdd(uint8_t cicon, uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
MenuItemClass* EditItemAdd(uint8_t cicon, const char * const text, OnDrawItem ondraw, OnClickItem onclick, void* val);
inline MenuItemClass* EditItemAdd(uint8_t cicon, FSTR_P text, OnDrawItem ondraw, OnClickItem onclick, void* val) {
  return EditItemAdd(cicon, FTOP(text), ondraw, onclick, val);
=======
void initMenu();

// Create a new menu
bool setMenu(Menu* &menu, FSTR_P fTitle, int8_t totalitems);
bool setMenu(Menu* &menu, frame_rect_t cn, FSTR_P fTitle, int8_t totalitems);

// Reset top line and selected item
void resetMenu(Menu* &menu);

// Invalidate currentMenu to prepare for full menu drawing
void invalidateMenu();

// Update the Menu and Draw if it is valid
void updateMenu(Menu* &menu);

// Redraw the current Menu if it is valid
void ReDrawMenu(bool force=false);

// Redraw selected menu item
void ReDrawItem();

// Clear menuItems array and free menuItems elements
void menuItemsClear();

// Prepare menuItems array
void menuItemsPrepare(int8_t totalitems);

// Is the current menu = menu?
bool isMenu(Menu* menu);

// Add elements to the menuItems array
CustomMenuItem* menuItemAdd(OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
MenuItem* menuItemAdd(uint8_t cicon, const char * const text=nullptr, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
inline MenuItem* menuItemAdd(uint8_t cicon, FSTR_P text=nullptr, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr) {
  return menuItemAdd(cicon, FTOP(text), ondraw, onclick);
}
MenuItem* menuItemAdd(uint8_t cicon, uint8_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, OnDrawItem ondraw=nullptr, OnClickItem onclick=nullptr);
MenuItem* editItemAdd(uint8_t cicon, const char * const text, OnDrawItem ondraw, OnClickItem onclick, void* val);
inline MenuItem* editItemAdd(uint8_t cicon, FSTR_P text, OnDrawItem ondraw, OnClickItem onclick, void* val) {
  return editItemAdd(cicon, FTOP(text), ondraw, onclick, val);
>>>>>>> bugfix-2.1.x
}
