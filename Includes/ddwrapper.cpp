/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   *  DirectDraw Wrapper                                                             *
   *  version 1.0, August 6th, 2010                                                  *
   *                                                                                 *
   *  Copyright (C) 2010 Jari Komppa                                                 *
   *                                                                                 *
   *  This software is provided 'as-is', without any express or implied              *
   *  warranty.  In no event will the authors be held liable for any damages         *
   *  arising from the use of this software.                                         *
   *                                                                                 *
   *  Permission is granted to anyone to use this software for any purpose,          *
   *  including commercial applications, and to alter it and redistribute it         *
   *  freely, subject to the following restrictions:                                 *
   *                                                                                 *
   *  1. The origin of this software must not be misrepresented; you must not        *
   *     claim that you wrote the original software. If you use this software        *
   *     in a product, an acknowledgment in the product documentation would be       *
   *     appreciated but is not required.                                            *
   *  2. Altered source versions must be plainly marked as such, and must not be     *
   *     misrepresented as being the original software.                              *
   *  3. This notice may not be removed or altered from any source distribution.     *
   *                                                                                 *
   *  Jari Komppa; http://iki.fi/sol/                                                *
   *                                                                                 *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   *                                                                                 *
   *  Based on a zlib/libpng licensed source code found on the net,                  *
   *  http://www.mikoweb.eu/index.php?node=28                                        *
   *  re-worked so much that there's fairly little left of the original.             *
   *                                                                                 *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   *                                                                                 *
   *  Modified by Doix - not the original wrapper                                    *
   *  More modifications made by Someone else                                        *
   *                                                                                 *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   *                                                                                 *
   *  Some modifications made by zort; https://github.com/zort/lf2-ai-scriptengine   *
   *                                                                                 *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   *                                                                                 *
   *  Extra modifications and code rearrangement by Mesujin.                         *
   *                                                                                 *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Base Code
 //Includes
  #include "stdafx.h"
  #include "detours.h"

  #include "scriptmathcomplex.h"
  #include "scriptstdstring.h"
  #include "scriptbuilder.h"
  #include "scriptmath3d.h"
  #include "scriptarray.h"
  #include "scriptmath.h"
  #include "gamearrays.h"
  #include "gameenums.h"
  #include "bmp.h"

  #include <sys/stat.h>
  #include <windows.h>
  #include <varargs.h>
  #include <sstream>
  #include <fstream>
 //-//
 //Global Variables
  #pragma data_seg (".ddraw_shared")
   HINSTANCE gl_hOriginalDll;
   HINSTANCE gl_hThisInstance;
  #pragma data_seg ()
 //-//
 //Variables
  bool Multi_Stating;
  int Console_Style;
  int Console_Size;
  int mode;
  int difficulty;
  int elapsed_time;
  int background = -1;
  int bg_width;
  int bg_zwidth1;
  int bg_zwidth2;
  int stage_bound;
  int current_phase;
  int current_phase_count;
  int current_stage;
  char stage_clear;
  sGame *game = (sGame*)0x458b00;

  class Info
  {
   public:
    int x; int y; int z;
    Vector3 position; double x_real; double y_real; double z_real;
    char facing;
    char holding_up; char holding_down; char holding_left; char holding_right; char holding_a; char holding_j; char holding_d;
    char up; char down; char left; char right; char A; char J; char D;
    char DrA; char DlA; char DuA; char DdA; char DrJ; char DlJ; char DuJ; char DdJ; char DJA;
    int hp; int dark_hp; int max_hp; int mp;
    int frame;
    int bdefend;
    int fall;
    int team;
    int id;
    int blink;
    int state;
    int weapon_type; int weapon_held; int weapon_holder;
    int shake;
    int wait_counter;
    int num;
    int ctimer;
    int arest;
    char vrests[400];
    int vrest;
    Vector3 velocity; double x_velocity; double y_velocity; double z_velocity;
    int clone;
    int type;
    int reserve;
    sDataFile* data;
    Info(){num = -1; type = -1; RefCount = 1;}
    Info(int object_num){Info(); operator=(object_num);}
    Info(const Info& info){Info(); operator=(info.num);}
    void AddRef(){RefCount++;}
    void RelRef(){if(--RefCount == 0) delete this;}
    int operator=(int object_num)
    {
 	 if(object_num < 0 || !game->exists[object_num]) return -1; 
	 x = game->objects[object_num]->x;
	 y = game->objects[object_num]->y;
	 z = game->objects[object_num]->z;
	 x_real = game->objects[object_num]->x_real;
	 y_real = game->objects[object_num]->y_real;
	 z_real = game->objects[object_num]->z_real;
	 position = Vector3(x_real, y_real, z_real);
	 facing = game->objects[object_num]->facing;
	 holding_up = game->objects[object_num]->holding_up;
	 holding_down = game->objects[object_num]->holding_down;
	 holding_left = game->objects[object_num]->holding_left;
	 holding_right = game->objects[object_num]->holding_right;
	 holding_a = game->objects[object_num]->holding_a;
	 holding_j = game->objects[object_num]->holding_j;
	 holding_d = game->objects[object_num]->holding_d;
	 up = game->objects[object_num]->up;
	 down = game->objects[object_num]->down;
	 left = game->objects[object_num]->left;
	 right = game->objects[object_num]->right;
	 A = game->objects[object_num]->A;
	 J = game->objects[object_num]->J;
	 D = game->objects[object_num]->D;
	 DrA = game->objects[object_num]->DrA;
	 DlA = game->objects[object_num]->DlA;
	 DuA = game->objects[object_num]->DuA;
	 DdA = game->objects[object_num]->DdA;
	 DrJ = game->objects[object_num]->DrJ;
	 DlJ = game->objects[object_num]->DlJ;
	 DuJ = game->objects[object_num]->DuJ;
	 DdJ = game->objects[object_num]->DdJ;
	 DJA = game->objects[object_num]->DJA;
	 hp = game->objects[object_num]->hp;
	 dark_hp = game->objects[object_num]->dark_hp;
	 max_hp = game->objects[object_num]->max_hp;
	 mp = game->objects[object_num]->mp;
	 frame = game->objects[object_num]->frame1;
	 fall = game->objects[object_num]->fall;
	 bdefend = game->objects[object_num]->bdefend;
	 team = game->objects[object_num]->team;
	 id = game->objects[object_num]->data->id;
	 blink = game->objects[object_num]->blink;
	 state = game->objects[object_num]->data->frames[frame].state;
	 weapon_type = game->objects[object_num]->weapon_type;
	 if(weapon_type == 0){weapon_held = -1;} else {weapon_held = game->objects[object_num]->weapon_held;}
	 weapon_holder = game->objects[object_num]->weapon_holder;
	 shake = game->objects[object_num]->shake;
	 wait_counter = game->objects[object_num]->wait_counter;
	 num = object_num;
	 ctimer = game->objects[object_num]->ctimer;
	 arest = game->objects[object_num]->arest;
	 memcpy(vrests, game->objects[object_num]->vrests, 400);
	 vrest = (int)(*(char*)(*(int*)(0x458c94 + object_num * 4) + 0xF0));
	 if (vrest < (int)(*(char*)(*(int*)(0x458c94 + object_num * 4) + 0xF3))) vrest = (int)(*(char*)(*(int*)(0x458c94 + object_num * 4) + 0xF3));
	 x_velocity = game->objects[object_num]->x_velocity;
	 y_velocity = game->objects[object_num]->y_velocity;
	 z_velocity = game->objects[object_num]->z_velocity;
	 velocity = Vector3(x_velocity, y_velocity, z_velocity);
	 clone = game->objects[object_num]->clone;
	 type = game->objects[object_num]->data->type;
	 reserve = game->objects[object_num]->reserve;
	 data = game->objects[object_num]->data;
	 return type;
    }
    int operator=(const Info& info){return operator=(info.num);}
    int operator+=(int object_num){return operator=(num + object_num);}
    int operator+=(const Info& info){return operator=(num + info.num);}
    int operator-=(int object_num){return operator=(num - object_num);}
    int operator-=(const Info& info){return operator=(num - info.num);}
    int operator++(){return operator=(num + 1);}
    int operator--(){return operator=(num - 1);}
   private:
    unsigned int RefCount;
  };
 
  Info *Info_Factory(){return new Info();}
  Info *Info_Factory(int object_num){return new Info(object_num);}
  Info *Info_Factory(const Info &info){return new Info(info);}
  Info self;
  Info target;
  asIScriptModule *ScriptModule;
  asIScriptEngine *ScriptEngine;
  asIScriptContext *ScriptContext;

  #ifdef DEBUG_VERSION
   #include <map>
   std::map < int, FILETIME > ModuleTimes;
  #endif

  typedef enum {INVALID, VALID, MODULE} FileValidity;
 //-//
 //Declaration
  void startup();
  void cleanup();
  void Process(int);
  void Initialization();
  void Hiding();
  void Cleaning();
  void Encryption(unsigned char, std::string);
  int (__stdcall *AI_o )(int target_num, int object_num, int x, int y, int z, int a, int b);
  int (__stdcall *AIa_o)(int object_num, int unkwn1);
 //-//
 //Functions
  //Shared
   int random(int max) //random function that works with replays
   {
    int result;    // eax@2
    signed int v3; // eax@3
    DWORD &dword_450C34 = *((DWORD*)0x450C34);
    DWORD &dword_450BCC = *((DWORD*)0x450BCC);
    if(max > 0)
    {
     dword_450C34 = (dword_450C34 + 1) % 1234; 
	 v3 = dword_450C34 + (unsigned __int8)*(((BYTE*)0x44FF90) + (dword_450BCC + 1) % 3000);
	 dword_450BCC = (dword_450BCC + 1) % 3000;
	 result = v3 % max;
    } else {result = 0;}
    return result;
   }
   int loadTarget(int target_num)
   {
    return target = target_num;
   }
   int setEnemy(int object_num)
   {
    if(object_num < 0 || object_num >= 400 || !game->exists[object_num]) return -1;
    return game->objects[self.num]->enemy = object_num;
   }
   void up(char key, char holding)
   {
    game->objects[self.num]->up = key;
    game->objects[self.num]->holding_up = holding;
    self.up = key; self.holding_up = holding;
   }
   void down(char key, char holding)
   {
    game->objects[self.num]->down = key;
    game->objects[self.num]->holding_down = holding;
    self.down = key; self.holding_down = holding;
   }
   void left(char key, char holding)
   {
    game->objects[self.num]->left = key;
    game->objects[self.num]->holding_left = holding;
    self.left = key; self.holding_left = holding;
   }
   void right(char key, char holding)
   {
    game->objects[self.num]->right = key;
    game->objects[self.num]->holding_right = holding;
    self.right = key; self.holding_right = holding;
   }
   void A(char key,char holding)
   {
    game->objects[self.num]->A = key;
    game->objects[self.num]->holding_a = holding;
    self.A = key; self.holding_a = holding;
   }
   void J(char key,char holding)
   {
    game->objects[self.num]->J = key;
    game->objects[self.num]->holding_j = holding;
    self.J = key; self.holding_j = holding;
   }
   void D(char key,char holding)
   {
    game->objects[self.num]->D = key;
    game->objects[self.num]->holding_d = holding;
    self.D = key; self.holding_d = holding;
   }
   void DrA(){game->objects[self.num]->DrA = 3; self.DrA = 3;}
   void DlA(){game->objects[self.num]->DlA = 3; self.DlA = 3;}
   void DuA(){game->objects[self.num]->DuA = 3; self.DuA = 3;}
   void DdA(){game->objects[self.num]->DdA = 3; self.DdA = 3;}
   void DrJ(){game->objects[self.num]->DrJ = 3; self.DrJ = 3;}
   void DlJ(){game->objects[self.num]->DlJ = 3; self.DlJ = 3;}
   void DuJ(){game->objects[self.num]->DuJ = 3; self.DuJ = 3;}
   void DdJ(){game->objects[self.num]->DdJ = 3; self.DdJ = 3;}
   void DJA(){game->objects[self.num]->DJA = 3; self.DJA = 3;}
   void clr()
   {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(hConsole == INVALID_HANDLE_VALUE) return;
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    if(!GetConsoleScreenBufferInfo(hConsole, &csbi)){return;}
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    if(!FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten)){return;}
    if(!GetConsoleScreenBufferInfo(hConsole, &csbi)){return;}
    if(!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)){return;}
    SetConsoleCursorPosition(hConsole, coordScreen);
   }
   void printAddr(void *Addr){printf("%p", Addr);}
   void print(bool p){if(p){printf("true");} else {printf("false");}}
   void print(char p){printf("%i", p);}
   void print(short p){printf("%i", p);}
   void print(int p){printf("%i", p);}
   void print(long long p){printf("%lli", p);}
   void print(unsigned char p){printf("%u", p);}
   void print(unsigned short p){printf("%u", p);}
   void print(unsigned int p){printf("%u", p);}
   void print(unsigned long long p){printf("%llu", p);}
   void print(float p){printf("%f", p);}
   void print(double p){printf("%Lf", p);}
   void print(const std::string &p){printf("%s", p.c_str());}
  //-//
  //Private
   std::string getFileName(int);
   FileValidity isValidFileName(std::string);
   std::string getModuleName(const std::string&);
   
   #ifdef DEBUG_VERSION
	bool hasFileTimeChanged(const char *File,FILETIME *Time)
	{
	 HANDLE hFile;
     hFile = CreateFile(File, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
     FILETIME ftWrite;
     if(hFile == INVALID_HANDLE_VALUE){ftWrite.dwLowDateTime = 0; ftWrite.dwHighDateTime = 0;} else
	 {
	  if(!GetFileTime(hFile, NULL, NULL, &ftWrite)){CloseHandle(hFile); return false;}
	  CloseHandle(hFile);
	 }
     if(CompareFileTime(&ftWrite, Time) != 0){(*Time) = ftWrite; return true;}
     return false;
	}
	void rebuildIfUpdated(int id_int,const std::string &fileName)
	{
	 if(ModuleTimes.count(id_int))
	 {
	  if(hasFileTimeChanged(fileName.c_str(), &(ModuleTimes[id_int])))
	  {
	   CScriptBuilder Builder;
	   Builder.DefineWord("debug");
       if(fileName.at(0) == '_'){Builder.DefineWord("module");} else {Builder.DefineWord("character");}
	   ScriptEngine->WriteMessage(fileName.c_str(), 0, 0, asMSGTYPE_INFORMATION, "Rebuilding.");
	   Builder.StartNewModule(ScriptEngine,getModuleName(fileName).c_str());
       if(Builder.AddSectionFromFile(fileName.c_str()) < 0)
	   {
		ScriptEngine->WriteMessage(fileName.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to load file.");
		ScriptEngine->DiscardModule(getModuleName(fileName).c_str());
		return;
	   }
	   if(Builder.BuildModule() < 0)
	   {
		ScriptEngine->WriteMessage(fileName.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to build module.");
		ScriptEngine->DiscardModule(getModuleName(fileName).c_str());
		return;
	   }
	  }
	 } else
	 {
	  FILETIME Time = {0, 0};
	  if(hasFileTimeChanged(fileName.c_str(), &Time))
	  {
	   ModuleTimes.insert(std::pair < int, FILETIME > (id_int, Time));
	   CScriptBuilder Builder;
	   Builder.DefineWord("debug");
       ScriptEngine->WriteMessage(fileName.c_str(), 0, 0, asMSGTYPE_INFORMATION, "Building.");
       Builder.StartNewModule(ScriptEngine, getModuleName(fileName).c_str());
	   if(Builder.AddSectionFromFile(fileName.c_str()) < 0)
	   {
		ScriptEngine->WriteMessage(fileName.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to load file.");
		ScriptEngine->DiscardModule(getModuleName(fileName).c_str());
		return;
	   }
	   if(Builder.BuildModule() < 0)
	   {
		ScriptEngine->WriteMessage(fileName.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to build module.");
		ScriptEngine->DiscardModule(getModuleName(fileName).c_str());
	    return;
	   }
	  }
	 }
	}
    int getIdFromFileName(const std::string &file){int x; std::stringstream(getModuleName(file)) >> x; return x;}
   #endif

   int callEgo(int object_num, int target_num, asIScriptFunction *Function)
   {
	elapsed_time = *(int*)0x450b8c;
	difficulty = *(int*)0x450c30;
	mode = *(int*)0x451160;
	if(background != *(int*)0x44d024)
	{
	 background = *(int*)0x44d024;
	 bg_width = game->files->backgrounds[background].bg_width;
	 bg_zwidth1 = game->files->backgrounds[background].bg_zwidth1;
	 bg_zwidth2 = game->files->backgrounds[background].bg_zwidth2;
     stage_bound = bg_width;
	 stage_clear = false;
	}
	if(mode == 1)
	{
	 stage_bound = *(int*)0x450bb4;
	 stage_clear = stage_bound == 0;
	}
	current_phase = *(int*)0x44fb6c;
	current_phase_count = *(int*)0x44f880;
	current_stage = *(int*)0x450b94;
	if((self = object_num) == -1)
	{
	 #ifdef DEBUG_VERSION
	 #ifdef MULTI_STATE
      if(Multi_Stating)
      {
     #endif
	  ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare self.");
	 #endif
	 #ifdef MULTI_STATE
      }
     #endif
	}
	if((target = target_num) == -1)
	{
	 #ifdef DEBUG_VERSION
	 #ifdef MULTI_STATE
      if(Multi_Stating)
      {
     #endif
	  ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare target.");
	 #endif
	 #ifdef MULTI_STATE
      }
     #endif
	}
	if(ScriptContext->Prepare(Function) < 0)
	{
	 #ifdef DEBUG_VERSION
	 #ifdef MULTI_STATE
      if(Multi_Stating)
      {
     #endif
	  ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	 #endif
	 #ifdef MULTI_STATE
      }
     #endif
	 return 0;
	}
	if(ScriptContext->Execute() < 0)
	{
	 #ifdef DEBUG_VERSION
	 #ifdef MULTI_STATE
      if(Multi_Stating)
      {
     #endif
	  ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	 #endif
	 #ifdef MULTI_STATE
      }
     #endif
	 return 0;
	}
	Process(object_num);
	return ScriptContext->GetReturnDWord();
   }
   void callId(int object_num, asIScriptFunction *Function)
   {
	elapsed_time = *(int*)0x450b8c;
	difficulty = *(int*)0x450c30;
	mode = *(int*)0x451160;
	if(background != *(int*)0x44d024)
	{
	 background = *(int*)0x44d024;
	 bg_width = game->files->backgrounds[background].bg_width;
	 bg_zwidth1 = game->files->backgrounds[background].bg_zwidth1;
	 bg_zwidth2 = game->files->backgrounds[background].bg_zwidth2;
     stage_bound = bg_width;
	 stage_clear = false;
	}
	if(mode == 1)
	{
	 stage_bound = *(int*)0x450bb4;
	 stage_clear = stage_bound == 0;
	}
	current_phase = *(int*)0x44fb6c;
	current_phase_count = *(int*)0x44f880;
	current_stage = *(int*)0x450b94;
	if((self = object_num) == -1)
	{
	 #ifdef DEBUG_VERSION
	 #ifdef MULTI_STATE
      if(Multi_Stating)
      {
     #endif
	  ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare self.");
	 #endif
	 #ifdef MULTI_STATE
      }
     #endif
	}
    if(ScriptContext->Prepare(Function) < 0)
	{
	 #ifdef DEBUG_VERSION
	 #ifdef MULTI_STATE
      if(Multi_Stating)
      {
     #endif
	  ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	 #endif
	 #ifdef MULTI_STATE
      }
     #endif
	 return;
	}
	if(ScriptContext->Execute() < 0)
	{
	 #ifdef DEBUG_VERSION
	 #ifdef MULTI_STATE
      if(Multi_Stating)
      {
     #endif
	  ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	 #endif
	 #ifdef MULTI_STATE
      }
     #endif
	}
	Process(object_num);
   }
   int __stdcall AI(int target_num, int object_num, int unkwn1, int unkwn2, int unkwn3, int unkwn4, int unkwn5)
   {
	DWORD return_value;
	DWORD unkwn6;
	__asm
	{
	 mov dword ptr ds:[unkwn6], ecx;
	}
	int id_int = game->objects[object_num]->data->id;
    std::string fileName = getFileName(id_int);
	ScriptModule = ScriptEngine->GetModule(getModuleName(fileName).c_str());
	if(ScriptModule)
	{
	 asIScriptFunction *Function = ScriptModule->GetFunctionByDecl("int ego()");
     if(Function){return callEgo(object_num,target_num,Function);}
	}
	__asm
	{
	 mov ecx, dword ptr ds:[unkwn5];
	 push ecx;
	 mov ecx, dword ptr ds:[unkwn4];
	 push ecx;
	 mov ecx, dword ptr ds:[unkwn3];
	 push ecx;
	 mov ecx, dword ptr ds:[unkwn2];
	 push ecx;
	 mov ecx, dword ptr ds:[unkwn1];
	 push ecx;
	 mov ecx, dword ptr ds:[object_num];
	 push ecx;
	 mov ecx, dword ptr ds:[target_num];
	 push ecx;
	 mov ecx, dword ptr ds:[unkwn6];
	 call AI_o;
	 mov dword ptr ds:[return_value], eax;
	}
	return return_value;
   }
   void __stdcall AIa(int object_num, int unkwn1)
   {
	DWORD unkwn2;
	_asm
	{
	 mov dword ptr ds:[unkwn2], ecx;
	}
	int id_int = game->objects[object_num]->data->id;
	std::string fileName = getFileName(id_int);
	#ifdef DEBUG_VERSION
	#ifdef MULTI_STATE
     if(Multi_Stating)
     {
    #endif
	 rebuildIfUpdated(id_int,fileName);
	#endif
	#ifdef MULTI_STATE
     }
    #endif
	ScriptModule = ScriptEngine->GetModule(getModuleName(fileName).c_str());
	if(ScriptModule)
	{
	 asIScriptFunction *Function = ScriptModule->GetFunctionByDecl("void id()");
     if(Function){callId(object_num, Function); return;}
	 #ifdef DEBUG_VERSION
	  else
	  {
	   #ifdef MULTI_STATE
        if(Multi_Stating)
       #endif
	   if(!ScriptModule->GetFunctionByDecl("int ego()"))
	   {
		ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Neither 'void id()' nor 'int ego()' are defined.");
	   }
	  }
	 #endif
	}
	Process(object_num);
	_asm
	{
	 mov ecx, dword ptr ds:[unkwn1];
	 push ecx;
	 mov ecx, dword ptr ds:[object_num];
	 push ecx;
	 mov ecx, dword ptr ds:[unkwn2];
	 call AIa_o;
	}
   }
   
   #ifdef DEBUG_VERSION
	void MessageCallback(const asSMessageInfo *msg,void *)
	{
	 if(msg->section[0] == '\0')
	 {
	  printf("%s: %s\n", msg->type == asMSGTYPE_ERROR ? "ERROR" : msg->type == asMSGTYPE_WARNING ? "WARNING" : "INFORMATION", msg->message);
	 } else if(msg->row == 0 && msg->col == 0)
	 {
	  printf("%s: %s : %s\n", msg->section, msg->type == asMSGTYPE_ERROR ? "ERROR" : msg->type == asMSGTYPE_WARNING ? "WARNING" : "INFORMATION", msg->message);
	 } else
	 {
	  printf("%s(%d, %d): %s : %s\n", msg->section, msg->row, msg->col, msg->type == asMSGTYPE_ERROR ? "ERROR" : msg->type == asMSGTYPE_WARNING ? "WARNING" : "INFORMATION", msg->message);
	 }
	}
   #endif

   void RegisterScriptFunctions()
   {
    RegisterScriptMath(ScriptEngine);
	RegisterScriptMathComplex(ScriptEngine);
	RegisterScriptMath3D(ScriptEngine);
	RegisterStdString(ScriptEngine);
	RegisterScriptArray(ScriptEngine, true);
	RegisterStdStringUtils(ScriptEngine);
	RegisterGameEnums(ScriptEngine);
	RegisterGameArrays(ScriptEngine);

	ScriptEngine->RegisterGlobalFunction("void clr()", asFUNCTION(clr), asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void print(bool p)", asFUNCTIONPR(print, (bool p), void), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(int8 p)", asFUNCTIONPR(print, (char p), void), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(int16 p)", asFUNCTIONPR(print, (short p), void), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(int32 p)", asFUNCTIONPR(print, (int p), void), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(int64 p)", asFUNCTIONPR(print, (long long p), void), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(uint8 p)", asFUNCTIONPR(print, (unsigned char p), void), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(uint16 p)", asFUNCTIONPR(print, (unsigned short p), void), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(uint32 p)", asFUNCTIONPR(print, (unsigned int p), void), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(uint64 p)", asFUNCTIONPR(print, (unsigned long long p), void), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(float p)", asFUNCTIONPR(print, (float p), void), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(double p)", asFUNCTIONPR(print, (double p), void), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(const string &in p)", asFUNCTIONPR(print, (const std::string &p), void), asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("int loadTarget(int object_num)", asFUNCTION(loadTarget), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("int setEnemy(int object_num)", asFUNCTION(setEnemy), asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void up(int8 key = 1,int8 holding = 0)", asFUNCTION(up), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void up(bool key,int8 holding = 0)", asFUNCTION(up), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void up(int8 key,bool holding)", asFUNCTION(up), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void up(bool key,bool holding)", asFUNCTION(up), asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void down(int8 key = 1,int8 holding = 0)", asFUNCTION(down), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void down(bool key,int8 holding = 0)", asFUNCTION(down), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void down(int8 key,bool holding)", asFUNCTION(down), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void down(bool key,bool holding)", asFUNCTION(down), asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void left(int8 key = 1,int8 holding = 0)", asFUNCTION(left), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void left(bool key,int8 holding = 0)", asFUNCTION(left), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void left(int8 key,bool holding)", asFUNCTION(left), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void left(bool key,bool holding)", asFUNCTION(left), asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void right(int8 key = 1,int8 holding = 0)", asFUNCTION(right), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void right(bool key,int8 holding = 0)", asFUNCTION(right), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void right(int8 key,bool holding)", asFUNCTION(right), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void right(bool key,bool holding)", asFUNCTION(right), asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void A(int8 key = 1,int8 holding = 0)", asFUNCTION(A), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void A(bool key,int8 holding = 0)", asFUNCTION(A), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void A(int8 key,bool holding)", asFUNCTION(A), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void A(bool key,bool holding)", asFUNCTION(A), asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void J(int8 key = 1,int8 holding = 0)", asFUNCTION(J), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void J(bool key,int8 holding = 0)", asFUNCTION(J), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void J(int8 key,bool holding)", asFUNCTION(J), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void J(bool key,bool holding)", asFUNCTION(J), asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void D(int8 key = 1,int8 holding = 0)", asFUNCTION(D), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void D(bool key,int8 holding = 0)", asFUNCTION(D), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void D(int8 key,bool holding)", asFUNCTION(D), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void D(bool key,bool holding)", asFUNCTION(D), asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void DrA()", asFUNCTION(DrA), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DlA()", asFUNCTION(DlA), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DuA()", asFUNCTION(DuA), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DdA()", asFUNCTION(DdA), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DrJ()", asFUNCTION(DrJ), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DlJ()", asFUNCTION(DlJ), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DuJ()", asFUNCTION(DuJ), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DdJ()", asFUNCTION(DdJ), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DJA()", asFUNCTION(DJA), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("int rand(int n)", asFUNCTION(random), asCALL_CDECL);

	ScriptEngine->RegisterGlobalProperty("const int mode", &mode);
	ScriptEngine->RegisterGlobalProperty("const int difficulty", &difficulty);
	ScriptEngine->RegisterGlobalProperty("const int elapsed_time", &elapsed_time);
	ScriptEngine->RegisterGlobalProperty("const int background", &background);
	ScriptEngine->RegisterGlobalProperty("const int bg_width", &bg_width);
	ScriptEngine->RegisterGlobalProperty("const int bg_zwidth1", &bg_zwidth1);
	ScriptEngine->RegisterGlobalProperty("const int bg_zwidth2", &bg_zwidth2);
	ScriptEngine->RegisterGlobalProperty("const int stage_bound", &stage_bound);
	ScriptEngine->RegisterGlobalProperty("const bool stage_clear", &stage_clear);
	ScriptEngine->RegisterGlobalProperty("const int current_phase", &current_phase);
	ScriptEngine->RegisterGlobalProperty("const int current_phase_count", &current_phase_count);
	ScriptEngine->RegisterGlobalProperty("const int current_stage", &current_stage);

	ScriptEngine->RegisterObjectType("Info", 0, asOBJ_REF);
	ScriptEngine->RegisterObjectBehaviour("Info", asBEHAVE_ADDREF, "void f()", asMETHOD(Info, AddRef), asCALL_THISCALL);
	ScriptEngine->RegisterObjectBehaviour("Info", asBEHAVE_RELEASE, "void f()", asMETHOD(Info, RelRef), asCALL_THISCALL);
	ScriptEngine->RegisterObjectBehaviour("Info", asBEHAVE_FACTORY, "Info @f()", asFUNCTIONPR(Info_Factory, (), Info*), asCALL_CDECL);
	ScriptEngine->RegisterObjectBehaviour("Info", asBEHAVE_FACTORY, "Info @f(int)", asFUNCTIONPR(Info_Factory, (int object_num), Info*), asCALL_CDECL);
	ScriptEngine->RegisterObjectBehaviour("Info", asBEHAVE_FACTORY, "Info @f(const Info &in info)", asFUNCTIONPR(Info_Factory, (const Info &info), Info*), asCALL_CDECL);

	ScriptEngine->RegisterObjectMethod("Info", "int opAssign(int object_num)", asMETHODPR(Info, operator=, (int object_num), int), asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("Info", "int opAssign(const Info &in info)", asMETHODPR(Info, operator=, (const Info &info), int), asCALL_THISCALL);

	ScriptEngine->RegisterObjectMethod("Info", "int opAddAssign(int object_num)", asMETHODPR(Info, operator+=, (int object_num), int), asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("Info", "int opAddAssign(const Info &in info)", asMETHODPR(Info, operator+=,(const Info &info), int), asCALL_THISCALL);

	ScriptEngine->RegisterObjectMethod("Info", "int opSubAssign(int object_num)", asMETHODPR(Info, operator-=, (int object_num), int), asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("Info", "int opSubAssign(const Info &in info)", asMETHODPR(Info, operator-=, (const Info &info), int), asCALL_THISCALL);

	ScriptEngine->RegisterObjectMethod("Info", "int opPreInc()", asMETHODPR(Info, operator++, (), int), asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("Info", "int opPreSub()", asMETHODPR(Info, operator--, (), int), asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("Info", "int opPostInc()", asMETHODPR(Info, operator++, (), int), asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("Info", "int opPostSub()", asMETHODPR(Info, operator--, (), int), asCALL_THISCALL);

	ScriptEngine->RegisterObjectProperty("Info", "int x", asOFFSET(Info, x));
	ScriptEngine->RegisterObjectProperty("Info", "int y", asOFFSET(Info, y));
	ScriptEngine->RegisterObjectProperty("Info", "int z", asOFFSET(Info, z));
	ScriptEngine->RegisterObjectProperty("Info", "vector3 position", asOFFSET(Info, position));
	ScriptEngine->RegisterObjectProperty("Info", "double x_real", asOFFSET(Info, x_real));
	ScriptEngine->RegisterObjectProperty("Info", "double y_real", asOFFSET(Info, y_real));
	ScriptEngine->RegisterObjectProperty("Info", "double z_real", asOFFSET(Info, z_real));
	ScriptEngine->RegisterObjectProperty("Info", "bool facing", asOFFSET(Info, facing));
	ScriptEngine->RegisterObjectProperty("Info", "bool holding_up", asOFFSET(Info, holding_up));
	ScriptEngine->RegisterObjectProperty("Info", "bool holding_down", asOFFSET(Info, holding_down));
	ScriptEngine->RegisterObjectProperty("Info", "bool holding_left", asOFFSET(Info, holding_left));
	ScriptEngine->RegisterObjectProperty("Info", "bool holding_right", asOFFSET(Info, holding_right));
	ScriptEngine->RegisterObjectProperty("Info", "bool holding_a", asOFFSET(Info, holding_a));
	ScriptEngine->RegisterObjectProperty("Info", "bool holding_j", asOFFSET(Info, holding_j));
	ScriptEngine->RegisterObjectProperty("Info", "bool holding_d", asOFFSET(Info, holding_d));
	ScriptEngine->RegisterObjectProperty("Info", "bool up", asOFFSET(Info, up));
	ScriptEngine->RegisterObjectProperty("Info", "bool down", asOFFSET(Info, down));
	ScriptEngine->RegisterObjectProperty("Info", "bool left", asOFFSET(Info, left));
	ScriptEngine->RegisterObjectProperty("Info", "bool right", asOFFSET(Info, right));
	ScriptEngine->RegisterObjectProperty("Info", "bool A", asOFFSET(Info, A));
	ScriptEngine->RegisterObjectProperty("Info", "bool J", asOFFSET(Info, J));
	ScriptEngine->RegisterObjectProperty("Info", "bool D", asOFFSET(Info, D));
	ScriptEngine->RegisterObjectProperty("Info", "int8 DrA", asOFFSET(Info, DrA));
	ScriptEngine->RegisterObjectProperty("Info", "int8 DlA", asOFFSET(Info, DlA));
	ScriptEngine->RegisterObjectProperty("Info", "int8 DuA", asOFFSET(Info, DuA));
	ScriptEngine->RegisterObjectProperty("Info", "int8 DdA", asOFFSET(Info, DdA));
	ScriptEngine->RegisterObjectProperty("Info", "int8 DrJ", asOFFSET(Info, DrJ));
	ScriptEngine->RegisterObjectProperty("Info", "int8 DlJ", asOFFSET(Info, DlJ));
	ScriptEngine->RegisterObjectProperty("Info", "int8 DuJ", asOFFSET(Info, DuJ));
	ScriptEngine->RegisterObjectProperty("Info", "int8 DdJ", asOFFSET(Info, DdJ));
	ScriptEngine->RegisterObjectProperty("Info", "int8 DJA", asOFFSET(Info, DJA));
	ScriptEngine->RegisterObjectProperty("Info", "int hp", asOFFSET(Info, hp));
	ScriptEngine->RegisterObjectProperty("Info", "int dark_hp", asOFFSET(Info, dark_hp));
	ScriptEngine->RegisterObjectProperty("Info", "int max_hp", asOFFSET(Info, max_hp));
	ScriptEngine->RegisterObjectProperty("Info", "int mp", asOFFSET(Info, mp));
	ScriptEngine->RegisterObjectProperty("Info", "int frame", asOFFSET(Info, frame));
	ScriptEngine->RegisterObjectProperty("Info", "int bdefend", asOFFSET(Info, bdefend));
	ScriptEngine->RegisterObjectProperty("Info", "int fall", asOFFSET(Info, fall));
	ScriptEngine->RegisterObjectProperty("Info", "int team", asOFFSET(Info, team));
	ScriptEngine->RegisterObjectProperty("Info", "int id", asOFFSET(Info, id));
	ScriptEngine->RegisterObjectProperty("Info", "int blink", asOFFSET(Info, blink));
	ScriptEngine->RegisterObjectProperty("Info", "int state", asOFFSET(Info, state));
	ScriptEngine->RegisterObjectProperty("Info", "int weapon_type", asOFFSET(Info, weapon_type));
	ScriptEngine->RegisterObjectProperty("Info", "int weapon_held", asOFFSET(Info, weapon_held));
	ScriptEngine->RegisterObjectProperty("Info", "int weapon_holder", asOFFSET(Info, weapon_holder));
	ScriptEngine->RegisterObjectProperty("Info", "int shake", asOFFSET(Info, shake));
	ScriptEngine->RegisterObjectProperty("Info", "int wait_counter", asOFFSET(Info, wait_counter));
	ScriptEngine->RegisterObjectProperty("Info", "int num", asOFFSET(Info, num));
	ScriptEngine->RegisterObjectProperty("Info", "int ctimer", asOFFSET(Info, ctimer));
	ScriptEngine->RegisterObjectProperty("Info", "int arest", asOFFSET(Info, arest));
	ScriptEngine->RegisterObjectProperty("Info", "CharArray vrests", asOFFSET(Info, vrests));
	ScriptEngine->RegisterObjectProperty("Info", "int vrest", asOFFSET(Info, vrest));
	ScriptEngine->RegisterObjectProperty("Info", "vector3 velocity", asOFFSET(Info, velocity));
	ScriptEngine->RegisterObjectProperty("Info", "double x_velocity", asOFFSET(Info, x_velocity));
	ScriptEngine->RegisterObjectProperty("Info", "double y_velocity", asOFFSET(Info, y_velocity));
	ScriptEngine->RegisterObjectProperty("Info", "double z_velocity", asOFFSET(Info, z_velocity));
	ScriptEngine->RegisterObjectProperty("Info", "int clone", asOFFSET(Info, clone));
	ScriptEngine->RegisterObjectProperty("Info", "int type", asOFFSET(Info, type));
	ScriptEngine->RegisterObjectProperty("Info", "int reserve", asOFFSET(Info, reserve));
	ScriptEngine->RegisterObjectProperty("Info", "DataFile @data", asOFFSET(Info, data));

	ScriptEngine->RegisterGlobalFunction("void printAddr(const IntArray @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const BoolArray @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const CharArray @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const CharArrayArray30 @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const CharArrayArray40 @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const DataFileArray @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const ObjectArray @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const FrameArray @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const BackgroundArray @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const SpawnArray @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const PhaseArray @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const StageArray @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const ItrArray @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const BdyArray @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Game @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const FileManager @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Stage @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Phase @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Spawn @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Background @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Object @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const DataFile @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Frame @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Bdy @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Itr @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Wpoint @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Cpoint @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Bpoint @addr)", asFUNCTION(printAddr), asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Opoint @addr)", asFUNCTION(printAddr), asCALL_CDECL);

	ScriptEngine->RegisterGlobalProperty("const Info self", &self);
	ScriptEngine->RegisterGlobalProperty("Info target", &target);
	ScriptEngine->RegisterGlobalProperty("const Game game", game);
   }
   void cleanup(){if(ScriptContext) ScriptContext->Release(); if(ScriptEngine) ScriptEngine->Release();}
   BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
   {
    LPVOID lpDummy = lpReserved;
    lpDummy = NULL;
    switch(ul_reason_for_call)
    {
     case DLL_PROCESS_ATTACH: Initialization(); startup(); InitInstance(hModule); break;
     case DLL_PROCESS_DETACH: Hiding(); Cleaning(); cleanup(); ExitInstance(); break;
     case DLL_THREAD_ATTACH: break;
     case DLL_THREAD_DETACH: break;
    }
    return(true);
   }
   HRESULT WINAPI DirectDrawCreate(GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter)
   {
    if(!gl_hOriginalDll) LoadOriginalDll();
    typedef HRESULT (WINAPI* DirectDrawCreate_Type)(GUID FAR *, LPVOID *, IUnknown FAR *);
    DirectDrawCreate_Type DirectDrawCreate_fn = (DirectDrawCreate_Type)GetProcAddress(gl_hOriginalDll, _T("DirectDrawCreate"));
    if(!DirectDrawCreate_fn){::ExitProcess(0);}
    LPDIRECTDRAW7 FAR dummy;
    HRESULT h = DirectDrawCreate_fn(lpGUID, (LPVOID*) &dummy, pUnkOuter);
    *lplpDD = (LPDIRECTDRAW) new myIDDraw7(dummy);
    return (h);
   }
   void InitInstance(HANDLE hModule){gl_hOriginalDll = NULL; gl_hThisInstance = NULL; gl_hThisInstance = (HINSTANCE)hModule;}
   void LoadOriginalDll(void){char buffer[MAX_PATH]; ::GetSystemDirectory(buffer, MAX_PATH); strcat(buffer,"\\ddraw.dll"); if(!gl_hOriginalDll) gl_hOriginalDll = ::LoadLibrary(buffer); if(!gl_hOriginalDll){::ExitProcess(0);}}
   void ExitInstance(){if(gl_hOriginalDll){::FreeLibrary(gl_hOriginalDll); gl_hOriginalDll = NULL;}}
  //-//
 //-//
//-//


//External Code
 //Commands
  #include <filesystem>
  #include <thread>
  #include <chrono>
  #define INJECTION_VERSION "(v1.40.221019)"
  #define ENCODING_KEY "SiuHungIsAGoodBearBecauseHeIsVeryGood"
  #define TEMPORAL_FILE "data\\temporary.txt"

  using int0 = void;
  using int1 = bool;
  using int8 = char;
  using int16 = short;
  using int32 = int;
  using int64 = long long;
  using uint8 = unsigned char;
  using uint16 = unsigned short;
  using uint32 = unsigned int;
  using uint64 = unsigned long long;
  using xint32 = float;
  using xint64 = double;
  using string = std::string;
 //-//
 //Variables
  struct CONFIG {string Storing; string AI = "ai"; int1 Full_Injection = false; int1 Sleep_Mode = false; uint32 Not_Post = 0; int1 Model = false; int32 IDs[14]; uint32 LandingFrame = 219; int1 LoadDLL = false; string DDirectory = "dlls"; int1 Debug = false; int16 Style = 0; int16 Delay = 0; string Build; string Input; string Output; string Insight; string Outsight; int1 Overwrite = false; int1 Get_Mirrors = false; int1 Permanentness = false; int1 Build_Directory = false; int8 Key[95]; int8 TD_Mode = false; int32 TD_Post = 0; int1 Hold_Def = false; int32 Hold_Def_TU = 0; int32 Min_Bdef = 0; xint64 Bdef_E = 100; int1 Dis_DHP = false; int1 Dis_MP = false; int32 M_Amount = 0; int32 M_Speed = 0; int32 T_Amount = 0; int32 T_Speed = 0; int32 B_Reserve = 0; int32 S_Reserve = 0; int1 MP_Rest = false; int32 Imm_Time = 40; int1 HP_Regen = false; int1 MP_Regen = false; xint64 DTDHP_Conv = 0; xint64 DTHP_Conv = 0; xint64 DTMP_Conv = 0;
  int1 ReAdj_Basic = false;
  xint64 ReAdj_RecDMG = 0;
  xint64 ReAdj_MP_Cost = 0;
  int1 ReAdj_Held = false;
  int1 ReAdj_Catch = false;
  xint64 ReAdj_Pres = 0;
  int1 ReAdj_Speed = false;
  int8 ReAding_Spd = 0;
  xint64 ReAdj_Spd_Base = 100;
  xint64 ReAdj_Spd_Walk = 100;
  xint64 ReAdj_Spd_Run = 200;
  xint64 ReAdj_Spd_Jump = 150;
  xint64 ReAdj_Spd_JumpY = -0.1;
  xint64 ReAdj_Spd_JumpB = -16;
  xint64 ReAdj_Spd_Dash = 250;
  xint64 ReAdj_Spd_DashY = -0.1;
  xint64 ReAdj_Spd_DashB = -10;
  xint64 ReAdj_Spd_Heavy = 80;
  xint64 ReAdj_Spd_FlipX = 5;
  xint64 ReAdj_Spd_FlipY = -2;
  xint64 ReAdj_Spd_Ratio = 8;
  int1 ReAdj_bdy = false;
  int8 ReAding_bdy = 0;
  int1 ReAdj_itr = false;
  int1 Dis_Il_Input = true; int1 Clean_Val = false; int1 Overlaying = false; int1 Neg_Fall = false; int1 C_Shift = false; int1 C_Smoothness = true; xint64 C_Speed = 0; xint64 C_Effectiviness = 0; int32 C_Off = 0; int32 C_Sensitivity = 0; int32 C_Size = 0; int32 Damage_Limiter = 0;}; CONFIG Config;
  struct CONSOLE {string Log; int0 PrintSet(){Vrab08 = true; PrintOut(); Vrab08 = false;} int0 PrintOut(){if(!Config.Debug) return; if(!Varb07) Openning(); HANDLE Hand01 = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleCursorPosition(Hand01, {0, 0}); Ostr01.str(""); if(Vrab08){Ostr01 << "\n==== Building Log ===============================\n\n"; if(Vrab09){if(Log != "") Vect01[0] += Log + "\n=================================================\n\n==== Building Log ===============================\n\n"; Log.clear();} Vrab09 = false;} else {Ostr01 << "\n==== Installation Log ===========================\n\n"; if(!Vrab09){if(Log != "") Vect01[0] += Log + "\n=================================================\n\n==== Installation Log ===========================\n\n"; Log.clear();} Vrab09 = true;} Varb01 = 0; Varb02 = 0; Varb03 = (int32)Log.size(); Varb04 = 0; while(Varb01 < (uint32)Varb03){Varb04 += 1; if(Log[Varb01] == (int8)-125) Varb04 = 0; if(Log[Varb01] == '\n'){if(Varb04 == 1){Log[Varb01] = (int8)-125; Varb02 -= 1;} Varb04 = 0; Varb02 += 1;} if((uint32)Varb04 >= (uint32)(Varb06 - 0)){if(Log[Varb01 + 1] != '\n' && Log[Varb01 + 1] != (int8)-125){Varb04 = 0; while((Log[Varb01 + 1] != ' ' && Log[Varb01 + 1] >= 0) || Log[Varb01 + 2] != ' ' || Log[Varb01 + 3] != ' '){Log.insert(Varb01 + 1, " "); Varb04 -= 25;} if(Varb04 != 0) Log[Varb01 + 1] = (int8)Varb04;} Varb04 = 0; Varb02 += 1; Varb03 = (int32)Log.size();} Varb01 += 1;} while(Varb02 >= (uint16)((Varb06 / 2) - 4)){Varb01 = 0; Varb04 = 0; Varb03 = (int32)Log.size(); while(Varb01 < (uint32)Varb03){Varb04 += 1; if(Log[Varb01] == (int8)-125) Varb04 -= 1; if(Log[Varb01] == '\n') break; if((uint32)Varb04 >= (uint32)(Varb06 - 0)) break; Varb01 += 1;} Vect01[0].append(Log, 0, Varb01 + 1); if(Vect01[0].size() >= 30000){Vect01.push_back(Vect01[0]); Vect01[0] = "";} Log.erase(0, Varb01 + 1); Varb02 -= 1;} Strn01 = Log; Varb03 = (int32)Strn01.size(); for(Varb01 = 0; Varb01 < (uint32)Varb03; ++Varb01){if(Strn01[Varb01] == (int8)-125){Strn01.erase(Varb01, 1); Varb03 = (int32)Strn01.size();} if(Strn01[Varb01] < 0) Strn01[Varb01] = ' ';} Ostr01 << Strn01; Varb03 = 20; while(Varb03 > Varb02){Ostr01 << "\n"; Varb03 -= 1;} Ostr01 << "\n================================================="; Strn02 = ""; Strn01 = Ostr01.str().c_str(); Ostr01.str(""); Varb01 = Strn01.length(); Varb03 = 0; Varb04 = 0; Varb02 = 0; while((uint32)Varb03 != Varb01){if(Strn01[Varb03] == '\n'){Varb05 = (int32)Varb02; if(PrintSize.size() > (uint32)Varb04) while(Varb02 < PrintSize[Varb04]){Strn02 += " "; Varb02 += 1;} if(Varb02 < Varb06) Strn02 += "\n"; if(PrintSize.size() <= (uint32)Varb04){PrintSize.push_back((uint16)Varb05);} else {PrintSize[Varb04] = (uint16)Varb05;} Varb04 += 1; Varb02 = 65535;} else {Strn02 += Strn01[Varb03];} Varb02 += 1; if(Varb02 == Varb06){Varb02 = 0; if(PrintSize.size() <= (uint32)Varb04){PrintSize.push_back(Varb06);} else {PrintSize[Varb04] = Varb06;} Varb04 += 1;} Varb03 += 1;} Varb05 = (int32)Varb02; if(PrintSize.size() > (uint32)Varb04) while(Varb02 < PrintSize[Varb04]){Strn02 += " "; Varb02 += 1;} if(Varb02 < Varb06) Strn02 += "\n"; if(PrintSize.size() <= (uint32)Varb04){PrintSize.push_back((uint16)Varb05);} else {PrintSize[Varb04] = (uint16)Varb05;} Varb04 += 1; Varb05 = Varb04; while((uint32)Varb04 < PrintSize.size()){Varb02 = 0; while(Varb02 < PrintSize[Varb04]){Strn02 += " "; Varb02 += 1;} if(Varb02 < Varb06) if((uint32)Varb04 + 1 < PrintSize.size()) Strn02 += "\n"; Varb04 += 1;} std::cout << Strn02; Strn01 = ""; Strn02 = ""; PrintSize.resize(Varb05); std::this_thread::sleep_for(std::chrono::milliseconds(Config.Delay));} int0 Opening(){std::ifstream File01; File01.open(Config.Output + "\\status.edb"); if(File01.is_open()){File01.close(); std::terminate();} std::ofstream File02; File02.open(Config.Output + "\\status.edb"); File02 << "Do not erase this file!"; File02.close();} int0 Ending(){std::ifstream File02; File02.open(Config.Output + "\\status.edb"); if(File02.is_open()){File02.close(); std::remove((Config.Output + "\\status.edb").c_str());} if(!Config.Debug) return; if(Varb07){Vect01[0] += Log + "\n=================================================\n\n"; Log.clear(); for(Varb01 = Vect01.size() - 1; (int32)Varb01 >= 0; --Varb01) for(Varb03 = 0; (uint32)Varb03 < Vect01[Varb01].size(); ++Varb03){if(Vect01[Varb01][(uint32)Varb03] == (int8)-125) Vect01[Varb01][(uint32)Varb03] = '\n'; if(Vect01[Varb01][(uint32)Varb03] < 0) Vect01[Varb01].erase((uint32)Varb03, (uint32)-(Vect01[Varb01][(uint32)Varb03] / 25));} std::ofstream File01(Special_Execution(Config.Output + "\\log.log")); auto Vrab04 = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); File01 << std::ctime(&Vrab04) << "\n"; Varb03 = 1; while(Varb03 < (int32)Vect01.size()){File01 << Vect01[(uint32)Varb03]; Vect01[(uint32)Varb03].clear(); Varb03 += 1;} File01 << Vect01[0]; Vect01[0].clear(); Vect01.clear(); File01.close(); ShowWindow(GetConsoleWindow(), 0); FreeConsole(); Varb07 = false;}} private: std::vector < string > Vect01; std::vector < uint16 > PrintSize; std::ostringstream Ostr01; string Strn01; string Strn02; uint32 Varb01; uint16 Varb02; int32 Varb03; int32 Varb04; int32 Varb05; int16 Varb06 = 50; int1 Varb07 = false; int1 Vrab08 = false; int1 Vrab09 = false; string Special_Execution(string Vrab01){string Temp01 = Vrab01; uint32 Vrab02 = Temp01.size() - 1; while(Vrab02 != 0 && Temp01[Vrab02] != '\\') Vrab02 -= 1; if(Vrab02 > 0) Temp01.erase(Vrab02, Temp01.size() - Vrab02); std::filesystem::create_directories(Temp01); return Vrab01;} int0 Openning(){Vect01.clear(); if(Vrab08){Vect01.push_back("==== Building Log ===============================\n\n");} else {Vect01.push_back("==== Installation Log ===========================\n\n");} uint8 Vrab01 = (uint8)Config.Style; uint8 Vrab02; if(Vrab01 < 128){Vrab02 = 255;} else {Vrab02 = 0;} AllocConsole(); HANDLE Hand01 = GetStdHandle(STD_OUTPUT_HANDLE); freopen("CONIN$", "rb", stdin); freopen("CONOUT$", "wb", stdout); freopen("CONOUT$", "wb", stderr); SMALL_RECT Rect01 = {0, 0, Varb06, 28}; CONSOLE_SCREEN_BUFFER_INFOEX Info01; Info01.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX); SetConsoleScreenBufferSize(Hand01, {Varb06, 26}); GetConsoleScreenBufferInfoEx(Hand01, &Info01); Info01.wAttributes = true; Info01.srWindow = Rect01; Info01.ColorTable[0] = RGB((int32)Vrab01, (int32)Vrab01, (int32)Vrab01); Info01.ColorTable[1] = RGB((int32)Vrab02, (int32)Vrab02, (int32)Vrab02); Info01.ColorTable[7] = Info01.ColorTable[1]; SetConsoleScreenBufferInfoEx(Hand01, &Info01); SetConsoleScreenBufferSize(Hand01, {Varb06, 26}); SetConsoleTitleA("Injector's Console"); Varb07 = true;}}; CONSOLE Console;
  struct MODIFER {std::vector < int32 > BG_Cam[3]; std::vector < int32 > BG_Z1; std::vector < int32 > BG_Z2; std::vector < std::vector < int32 > > BG_Y; std::vector < std::vector < int32 > > BG_H;}; MODIFER Modifer;

  const uint32 MaximumObject = 400;
  const uint32 MaximumFrames = 400;
  const int32 MaximumMP = 500;

  int1 Database_First = true;
  int1 Database_FirstInGame = true;
  int32 Database_Exist[MaximumObject];
  int32 Database_ExistT0[MaximumObject];
  int32 Database_ExistT0COM[MaximumObject];
  uint32 NumberOfExist;
  uint32 NumberOfExistT0;
  uint32 NumberOfExistT0COM;
  
  int1 InGame = false;
  int32 TU = -1;
  int32 LastTU = 2147483647;
  int32 InjectorNUM = -1;
  int32 InjectorFRAME = -1;
  int32 Full_Injection_ID = -1;
  int32 Full_Injection_ID2 = -1;
  int32 Hold_Def_TU_Count[MaximumObject];
  int32 ReserveCount[MaximumObject];
  int32 Dis_DHP_HP_R[MaximumObject];
  int32 Convertion[MaximumObject];
  int8 LastInput[7][MaximumObject];
  int1 Overlay[100];
  int1 Debugging = true;
  int1 InjectionDone = false;
  
  std::vector < HINSTANCE > Hins0001;
  std::vector < int32 > Vect0001;
  std::vector < string > Strn0001;
  std::ifstream File0001;
  std::ofstream File0002;
  int32 Vrab0001;
  uint32 Vrab0002;
  uint32 Vrab0003;
  xint64 Vrab0004;
  string Temp0001;
  string Temp0002;
  string Temp0003;
 //-//
 //Modified Functions
  string getFileName(int32 Vrab01){return Config.AI + "\\" + std::to_string(Vrab01) + ".as";}
  FileValidity isValidFileName(string Vrab01)
  {
   if(Vrab01.size() < Config.AI.size() + 5) return INVALID;
   Vrab01.erase(0, Config.AI.size() + 1);
   if(Vrab01.at(0) == '_') return MODULE;
   if(Vrab01.at(0) == '0')
   {
    if(Vrab01.at(2) == 'A') Vrab01.at(2) += 32;
    if(Vrab01.at(3) == 'S') Vrab01.at(3) += 32;
    if(Vrab01 != "0.as") return INVALID;
   }
   while(Vrab01.at(0) != '.' && Vrab01.at(0) >= '0' && Vrab01.at(0) <= '9') Vrab01.erase(0, 1);
   if(Vrab01.at(0) != '.') return INVALID;
   if(Vrab01.at(1) == 'A') Vrab01.at(1) += 32;
   if(Vrab01.at(2) == 'S') Vrab01.at(2) += 32;
   if(Vrab01 != ".as") return INVALID;
   return VALID;
  }
  string getModuleName(const string &Vrab01){return Vrab01.substr(Config.AI.size() + 1);}
  int0 startup()
  {
   #ifdef DEBUG_VERSION
   #ifdef MULTI_STATE
    if(Multi_Stating)
    {
   #endif
    int32 Vrab01;
    if(Console_Style <= 127){Vrab01 = 255;} else {Vrab01 = 0;}
	AllocConsole();
    HANDLE Hand01 = GetStdHandle(STD_OUTPUT_HANDLE);
	freopen("CONIN$","rb",stdin);   // reopen stdin handle as console window input
	freopen("CONOUT$","wb",stdout); // reopen stout handle as console window output
	freopen("CONOUT$","wb",stderr); // reopen stderr handle as console window output
    SMALL_RECT Rect01 = {0, 0, (int16)Console_Size, (int16)(Console_Size / 2)};
    CONSOLE_SCREEN_BUFFER_INFOEX Info01; Info01.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    SetConsoleScreenBufferSize(Hand01, {(int16)Console_Size, (int16)((Console_Size / 2) - 2)});
    GetConsoleScreenBufferInfoEx(Hand01, &Info01);
    Info01.wAttributes = true; Info01.srWindow = Rect01;
    Info01.ColorTable[0] = RGB(Console_Style, Console_Style, Console_Style); 
    Info01.ColorTable[1] = RGB((int32)Vrab01, (int32)Vrab01, (int32)Vrab01); 
    Info01.ColorTable[7] = Info01.ColorTable[1]; 
    SetConsoleScreenBufferInfoEx(Hand01, &Info01); 
    SetConsoleScreenBufferSize(Hand01, {(int16)Console_Size, (int16)((Console_Size / 2) - 2)}); 
    SetConsoleTitleA("Injector's Console");
   #endif
   #ifdef MULTI_STATE
    }
   #endif
   ScriptModule = NULL;
   ScriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION); if(!ScriptEngine){::ExitProcess(0);}
   #ifdef DEBUG_VERSION
   #ifdef MULTI_STATE
    if(Multi_Stating)
    {
   #endif
	ScriptEngine->SetMessageCallback(asFUNCTION(MessageCallback), NULL, asCALL_CDECL);
   #endif
   #ifdef MULTI_STATE
    }
   #endif
   ScriptContext = ScriptEngine->CreateContext();
   RegisterScriptFunctions();
   AI_o = (int32 (__stdcall*)(int32, int32, int32, int32, int32, int32, int32))DetourFunction((PBYTE)0x00403a40, (PBYTE)AI);
   AIa_o = (int32 (__stdcall*)(int32, int32))DetourFunction((PBYTE)0x004094b0, (PBYTE)AIa);
   HANDLE hFind; WIN32_FIND_DATA FindFileData;
   int8 DirPath[MAX_PATH]; strcpy(DirPath, (Config.AI + "\\").c_str());
   int8 FileName[MAX_PATH]; strcpy(FileName, DirPath);
   strcat(DirPath, "*.as");
   hFind = FindFirstFile(DirPath, &FindFileData); if(hFind == INVALID_HANDLE_VALUE) return;
   strcpy(DirPath, FileName);
   do 
   {
    strcpy(FileName, DirPath);
    strcat(FileName, FindFileData.cFileName);
    if(!(FindFileData.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY))
    {
     FileValidity Validity = isValidFileName(FileName);
     if(Validity)
     {
      #ifdef DEBUG_VERSION
	  #ifdef MULTI_STATE
       if(Multi_Stating)
       {
      #endif
	   FILETIME Time;
	   hasFileTimeChanged(FileName, &Time);
	   ModuleTimes.insert(std::pair < int, FILETIME > (getIdFromFileName(FileName), Time));
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	  CScriptBuilder Builder;
	  #ifdef DEBUG_VERSION
	  #ifdef MULTI_STATE
       if(Multi_Stating)
       {
      #endif
	   Builder.DefineWord("debug");
	   ScriptEngine->WriteMessage(FileName, 0, 0, asMSGTYPE_INFORMATION, "Building.");
	  #ifdef MULTI_STATE
       }
      #endif
	  #else
	   Builder.DefineWord("release");
	  #endif
	  if(Validity == MODULE){Builder.DefineWord("module");} else {Builder.DefineWord("character");}
	  Builder.StartNewModule(ScriptEngine, getModuleName(FileName).c_str());
	  if(Builder.AddSectionFromFile(FileName) < 0)
	  {
       #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
       if(Multi_Stating)
       {
       #endif
        ScriptEngine->WriteMessage(FileName, 0, 0, asMSGTYPE_ERROR, "Unable to load file.");
       #endif
	   #ifdef MULTI_STATE
        }
       #endif
       ScriptEngine->DiscardModule(getModuleName(FileName).c_str());
       continue;
	  }
	  if(Builder.BuildModule() < 0)
	  {
       #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Multi_Stating)
        {
       #endif
        ScriptEngine->WriteMessage(FileName, 0, 0, asMSGTYPE_ERROR, "Unable to build module.");
       #endif
	   #ifdef MULTI_STATE
        }
       #endif
       ScriptEngine->DiscardModule(getModuleName(FileName).c_str());
       continue;
	  }
	 }
	}
   } while(FindNextFile(hFind, &FindFileData));
   FindClose(hFind);
  }
 //-//
 //Useful Functions
  int32 Rounding(xint64 Varb01){if(Varb01 > (double)(int)Varb01 + 0.5){return (int)Varb01 + 1;} else {return (int)Varb01;}}
  int32 Positive(int32 Vrab01){if(Vrab01 >= 0) return Vrab01; return -Vrab01;}
  int32 ToNum(string Vrab01){if(Vrab01[0] != '-' && (Vrab01[0] < '0' || Vrab01[0] > '9')) return 0; uint32 Vrab02 = 0; int64 Vrab03 = (int64)(int32)Vrab01.size(); if(Vrab03 > 18) Vrab03 = 18; int64 Vrab04 = 0; if(Vrab01[0] == '-') Vrab02 += 1; while(Vrab02 < (uint32)(int32)Vrab03 && Vrab01[Vrab02] >= '0' && Vrab01[Vrab02] <= '9') Vrab02 += 1; Vrab02 -= 1;Vrab03 = 1; while(Vrab02 > 0){switch(Vrab01[Vrab02]){case '1': Vrab04 += Vrab03; break; case '2': Vrab04 += Vrab03 * 2; break; case '3': Vrab04 += Vrab03 * 3; break; case '4': Vrab04 += Vrab03 * 4; break; case '5': Vrab04 += Vrab03 * 5; break; case '6': Vrab04 += Vrab03 * 6; break; case '7': Vrab04 += Vrab03 * 7; break; case '8': Vrab04 += Vrab03 * 8; break; case '9': Vrab04 += Vrab03 * 9; break; default: break;} Vrab03 *= 10; Vrab02 -= 1;} if(Vrab01[0] == '-'){Vrab04 = -Vrab04;} else {switch(Vrab01[0]){case '1': Vrab04 += Vrab03; break; case '2': Vrab04 += Vrab03 * 2; break; case '3': Vrab04 += Vrab03 * 3; break; case '4': Vrab04 += Vrab03 * 4; break; case '5': Vrab04 += Vrab03 * 5; break; case '6': Vrab04 += Vrab03 * 6; break; case '7': Vrab04 += Vrab03 * 7; break; case '8': Vrab04 += Vrab03 * 8; break; case '9': Vrab04 += Vrab03 * 9; break; default: break;}} return (int32)Vrab04;}
  string Execute(string Vrab01){string Temp01 = Vrab01; uint32 Vrab02 = Temp01.size() - 1; while(Vrab02 != 0 && Temp01[Vrab02] != '\\') Vrab02 -= 1; if(Vrab02 > 0) Temp01.erase(Vrab02, Temp01.size() - Vrab02); std::filesystem::create_directories(Temp01); return Vrab01;}
  int0 FrameCopy(uint32 Vrab01, uint32 Vrab02, uint32 Vrab03){game->files->datas[Vrab01]->frames[Vrab03].exists = true; game->files->datas[Vrab01]->frames[Vrab03].pic = game->files->datas[Vrab01]->frames[Vrab02].pic; game->files->datas[Vrab01]->frames[Vrab03].state = game->files->datas[Vrab01]->frames[Vrab02].state; game->files->datas[Vrab01]->frames[Vrab03].wait = game->files->datas[Vrab01]->frames[Vrab02].wait; game->files->datas[Vrab01]->frames[Vrab03].next = game->files->datas[Vrab01]->frames[Vrab02].next; game->files->datas[Vrab01]->frames[Vrab03].dvx = game->files->datas[Vrab01]->frames[Vrab02].dvx; game->files->datas[Vrab01]->frames[Vrab03].dvy = game->files->datas[Vrab01]->frames[Vrab02].dvy; game->files->datas[Vrab01]->frames[Vrab03].dvz = game->files->datas[Vrab01]->frames[Vrab02].dvz; game->files->datas[Vrab01]->frames[Vrab03].centerx = game->files->datas[Vrab01]->frames[Vrab02].centerx; game->files->datas[Vrab01]->frames[Vrab03].centery = game->files->datas[Vrab01]->frames[Vrab02].centery; game->files->datas[Vrab01]->frames[Vrab03].hit_a = game->files->datas[Vrab01]->frames[Vrab02].hit_a; game->files->datas[Vrab01]->frames[Vrab03].hit_d = game->files->datas[Vrab01]->frames[Vrab02].hit_d; game->files->datas[Vrab01]->frames[Vrab03].hit_j = game->files->datas[Vrab01]->frames[Vrab02].hit_j; game->files->datas[Vrab01]->frames[Vrab03].hit_Fa = game->files->datas[Vrab01]->frames[Vrab02].hit_Fa; game->files->datas[Vrab01]->frames[Vrab03].hit_Fj = game->files->datas[Vrab01]->frames[Vrab02].hit_Fj; game->files->datas[Vrab01]->frames[Vrab03].hit_Da = game->files->datas[Vrab01]->frames[Vrab02].hit_Da; game->files->datas[Vrab01]->frames[Vrab03].hit_Dj = game->files->datas[Vrab01]->frames[Vrab02].hit_Dj; game->files->datas[Vrab01]->frames[Vrab03].hit_Ua = game->files->datas[Vrab01]->frames[Vrab02].hit_Ua; game->files->datas[Vrab01]->frames[Vrab03].hit_Uj = game->files->datas[Vrab01]->frames[Vrab02].hit_Uj; game->files->datas[Vrab01]->frames[Vrab03].hit_ja = game->files->datas[Vrab01]->frames[Vrab02].hit_ja; game->files->datas[Vrab01]->frames[Vrab03].mp = game->files->datas[Vrab01]->frames[Vrab02].mp; game->files->datas[Vrab01]->frames[Vrab03].sound = game->files->datas[Vrab01]->frames[Vrab02].sound; game->files->datas[Vrab01]->frames[Vrab03].bpoint.x = game->files->datas[Vrab01]->frames[Vrab02].bpoint.x; game->files->datas[Vrab01]->frames[Vrab03].bpoint.y = game->files->datas[Vrab01]->frames[Vrab02].bpoint.y; game->files->datas[Vrab01]->frames[Vrab03].cpoint.kind = game->files->datas[Vrab01]->frames[Vrab02].cpoint.kind; game->files->datas[Vrab01]->frames[Vrab03].cpoint.x = game->files->datas[Vrab01]->frames[Vrab02].cpoint.x; game->files->datas[Vrab01]->frames[Vrab03].cpoint.y = game->files->datas[Vrab01]->frames[Vrab02].cpoint.y; game->files->datas[Vrab01]->frames[Vrab03].cpoint.vaction = game->files->datas[Vrab01]->frames[Vrab02].cpoint.vaction; game->files->datas[Vrab01]->frames[Vrab03].cpoint.aaction = game->files->datas[Vrab01]->frames[Vrab02].cpoint.aaction; game->files->datas[Vrab01]->frames[Vrab03].cpoint.daction = game->files->datas[Vrab01]->frames[Vrab02].cpoint.daction; game->files->datas[Vrab01]->frames[Vrab03].cpoint.jaction = game->files->datas[Vrab01]->frames[Vrab02].cpoint.jaction; game->files->datas[Vrab01]->frames[Vrab03].cpoint.taction = game->files->datas[Vrab01]->frames[Vrab02].cpoint.taction; game->files->datas[Vrab01]->frames[Vrab03].cpoint.dircontrol = game->files->datas[Vrab01]->frames[Vrab02].cpoint.dircontrol; game->files->datas[Vrab01]->frames[Vrab03].cpoint.decrease = game->files->datas[Vrab01]->frames[Vrab02].cpoint.decrease; game->files->datas[Vrab01]->frames[Vrab03].cpoint.throwvx = game->files->datas[Vrab01]->frames[Vrab02].cpoint.throwvx; game->files->datas[Vrab01]->frames[Vrab03].cpoint.throwvy = game->files->datas[Vrab01]->frames[Vrab02].cpoint.throwvy; game->files->datas[Vrab01]->frames[Vrab03].cpoint.throwvz = game->files->datas[Vrab01]->frames[Vrab02].cpoint.throwvz; game->files->datas[Vrab01]->frames[Vrab03].cpoint.throwinjury = game->files->datas[Vrab01]->frames[Vrab02].cpoint.throwinjury; game->files->datas[Vrab01]->frames[Vrab03].cpoint.cover = game->files->datas[Vrab01]->frames[Vrab02].cpoint.cover; game->files->datas[Vrab01]->frames[Vrab03].cpoint.hurtable = game->files->datas[Vrab01]->frames[Vrab02].cpoint.hurtable; game->files->datas[Vrab01]->frames[Vrab03].cpoint.injury = game->files->datas[Vrab01]->frames[Vrab02].cpoint.injury; game->files->datas[Vrab01]->frames[Vrab03].wpoint.kind = game->files->datas[Vrab01]->frames[Vrab02].wpoint.kind; game->files->datas[Vrab01]->frames[Vrab03].wpoint.x = game->files->datas[Vrab01]->frames[Vrab02].wpoint.x; game->files->datas[Vrab01]->frames[Vrab03].wpoint.y = game->files->datas[Vrab01]->frames[Vrab02].wpoint.y; game->files->datas[Vrab01]->frames[Vrab03].wpoint.dvx = game->files->datas[Vrab01]->frames[Vrab02].wpoint.dvx; game->files->datas[Vrab01]->frames[Vrab03].wpoint.dvy = game->files->datas[Vrab01]->frames[Vrab02].wpoint.dvy; game->files->datas[Vrab01]->frames[Vrab03].wpoint.dvz = game->files->datas[Vrab01]->frames[Vrab02].wpoint.dvz; game->files->datas[Vrab01]->frames[Vrab03].wpoint.weaponact = game->files->datas[Vrab01]->frames[Vrab02].wpoint.weaponact; game->files->datas[Vrab01]->frames[Vrab03].wpoint.attacking = game->files->datas[Vrab01]->frames[Vrab02].wpoint.attacking; game->files->datas[Vrab01]->frames[Vrab03].wpoint.cover = game->files->datas[Vrab01]->frames[Vrab02].wpoint.cover; game->files->datas[Vrab01]->frames[Vrab03].opoint.kind = game->files->datas[Vrab01]->frames[Vrab02].opoint.kind; game->files->datas[Vrab01]->frames[Vrab03].opoint.x = game->files->datas[Vrab01]->frames[Vrab02].opoint.x; game->files->datas[Vrab01]->frames[Vrab03].opoint.y = game->files->datas[Vrab01]->frames[Vrab02].opoint.y; game->files->datas[Vrab01]->frames[Vrab03].opoint.dvx = game->files->datas[Vrab01]->frames[Vrab02].opoint.dvx; game->files->datas[Vrab01]->frames[Vrab03].opoint.dvy = game->files->datas[Vrab01]->frames[Vrab02].opoint.dvy; game->files->datas[Vrab01]->frames[Vrab03].opoint.oid = game->files->datas[Vrab01]->frames[Vrab02].opoint.oid; game->files->datas[Vrab01]->frames[Vrab03].opoint.action = game->files->datas[Vrab01]->frames[Vrab02].opoint.action; game->files->datas[Vrab01]->frames[Vrab03].opoint.facing = game->files->datas[Vrab01]->frames[Vrab02].opoint.facing; game->files->datas[Vrab01]->frames[Vrab03].itr_count = game->files->datas[Vrab01]->frames[Vrab02].itr_count; game->files->datas[Vrab01]->frames[Vrab03].itrs = game->files->datas[Vrab01]->frames[Vrab02].itrs; game->files->datas[Vrab01]->frames[Vrab03].itr_x = game->files->datas[Vrab01]->frames[Vrab02].itr_x; game->files->datas[Vrab01]->frames[Vrab03].itr_y = game->files->datas[Vrab01]->frames[Vrab02].itr_y; game->files->datas[Vrab01]->frames[Vrab03].itr_w = game->files->datas[Vrab01]->frames[Vrab02].itr_w; game->files->datas[Vrab01]->frames[Vrab03].itr_h = game->files->datas[Vrab01]->frames[Vrab02].itr_h; game->files->datas[Vrab01]->frames[Vrab03].bdy_count = game->files->datas[Vrab01]->frames[Vrab02].bdy_count; game->files->datas[Vrab01]->frames[Vrab03].bdys = game->files->datas[Vrab01]->frames[Vrab02].bdys; game->files->datas[Vrab01]->frames[Vrab03].bdy_x = game->files->datas[Vrab01]->frames[Vrab02].bdy_x; game->files->datas[Vrab01]->frames[Vrab03].bdy_y = game->files->datas[Vrab01]->frames[Vrab02].bdy_y; game->files->datas[Vrab01]->frames[Vrab03].bdy_w = game->files->datas[Vrab01]->frames[Vrab02].bdy_w; game->files->datas[Vrab01]->frames[Vrab03].bdy_h = game->files->datas[Vrab01]->frames[Vrab02].bdy_h;}
  int0 Rename(string &Vrab01){uint32 Vrab02 = Vrab01.size() - 1; while((int32)Vrab02 >= 0 && Vrab01[Vrab02] != '-') Vrab02 -= 1; if(Vrab01[Vrab02 + 1] >= '0' && Vrab01[Vrab02 + 1] <= '9'){string Temp01 = ""; uint32 Vrab03 = Vrab02; Temp01 += Vrab01[Vrab03 + 1]; while(Vrab01[Vrab03 + 2] >= '0' && Vrab01[Vrab03 + 2] <= '9'){Temp01 += Vrab01[Vrab03 + 2]; Vrab03 += 1;} Temp01 = std::to_string((uint32)ToNum(Temp01) + 1); Vrab01.erase(Vrab02 + 1, (Vrab03 + 2) - (Vrab02 + 1)); Vrab01.insert(Vrab02 + 1, Temp01);} else {Vrab02 = Vrab01.size() - 1; while((int32)Vrab02 >= 0 && Vrab01[Vrab02] != '.') Vrab02 -= 1; if(Vrab02 > 7) if(string(Vrab01, Vrab02 - 8, 7) == "_mirror") Vrab02 -= 8; if(Vrab02 > 0){Vrab01.insert(Vrab02, "-2");} else {Vrab01.insert(Vrab01.size() - 1, "-2");}}}
  int0 Manage(string &Vrab01){if(Vrab01 == "_"){Vrab01 = std::filesystem::current_path().string(); return;} uint32 Vrab02 = Vrab01.size() - 1; while((int32)Vrab02 >= 0){if(Vrab01[Vrab02] == '_') Vrab01[Vrab02] = ' '; Vrab02 -= 1;}}
  int1 Exist(const string &Vrab01){struct stat Vrab02; return (stat(Vrab01.c_str(), &Vrab02) == 0);}
  int0 LoadOtherDll(){Hins0001.clear(); if(Exist(Config.DDirectory)) for(auto const &Vrab01 : std::filesystem::recursive_directory_iterator(Config.DDirectory)){Temp0001 = Vrab01.path().string(); if(string(Temp0001, Temp0001.size() - 4, 4) == ".dll") Hins0001.push_back(LoadLibraryA(Vrab01.path().string().c_str()));}}
  int0 UnloadOtherDll(){Vrab0002 = Hins0001.size(); Vrab0003 = 0; while(Vrab0003 < Vrab0002){FreeLibrary(Hins0001[Vrab0003]); Vrab0003 += 1;}}
  xint64 Decryption94(int8 Vrab01){if(Vrab01 == Config.Key[0]) return 0; if(Vrab01 == Config.Key[1]) return 1; if(Vrab01 == Config.Key[2]) return 2; if(Vrab01 == Config.Key[3]) return 3; if(Vrab01 == Config.Key[4]) return 4; if(Vrab01 == Config.Key[5]) return 5; if(Vrab01 == Config.Key[6]) return 6; if(Vrab01 == Config.Key[7]) return 7; if(Vrab01 == Config.Key[8]) return 8; if(Vrab01 == Config.Key[9]) return 9; if(Vrab01 == Config.Key[10]) return 10; if(Vrab01 == Config.Key[11]) return 11; if(Vrab01 == Config.Key[12]) return 12; if(Vrab01 == Config.Key[13]) return 13; if(Vrab01 == Config.Key[14]) return 14; if(Vrab01 == Config.Key[15]) return 15; if(Vrab01 == Config.Key[16]) return 16; if(Vrab01 == Config.Key[17]) return 17; if(Vrab01 == Config.Key[18]) return 18; if(Vrab01 == Config.Key[19]) return 19; if(Vrab01 == Config.Key[20]) return 20; if(Vrab01 == Config.Key[21]) return 21; if(Vrab01 == Config.Key[22]) return 22; if(Vrab01 == Config.Key[23]) return 23; if(Vrab01 == Config.Key[24]) return 24; if(Vrab01 == Config.Key[25]) return 25; if(Vrab01 == Config.Key[26]) return 26; if(Vrab01 == Config.Key[27]) return 27; if(Vrab01 == Config.Key[28]) return 28; if(Vrab01 == Config.Key[29]) return 29; if(Vrab01 == Config.Key[30]) return 30; if(Vrab01 == Config.Key[31]) return 31; if(Vrab01 == Config.Key[32]) return 32; if(Vrab01 == Config.Key[33]) return 33; if(Vrab01 == Config.Key[34]) return 34; if(Vrab01 == Config.Key[35]) return 35; if(Vrab01 == Config.Key[36]) return 36; if(Vrab01 == Config.Key[37]) return 37; if(Vrab01 == Config.Key[38]) return 38; if(Vrab01 == Config.Key[39]) return 39; if(Vrab01 == Config.Key[40]) return 40; if(Vrab01 == Config.Key[41]) return 41; if(Vrab01 == Config.Key[42]) return 42; if(Vrab01 == Config.Key[43]) return 43; if(Vrab01 == Config.Key[44]) return 44; if(Vrab01 == Config.Key[45]) return 45; if(Vrab01 == Config.Key[46]) return 46; if(Vrab01 == Config.Key[47]) return 47; if(Vrab01 == Config.Key[48]) return 48; if(Vrab01 == Config.Key[49]) return 49; if(Vrab01 == Config.Key[50]) return 50; if(Vrab01 == Config.Key[51]) return 51; if(Vrab01 == Config.Key[52]) return 52; if(Vrab01 == Config.Key[53]) return 53; if(Vrab01 == Config.Key[54]) return 54; if(Vrab01 == Config.Key[55]) return 55; if(Vrab01 == Config.Key[56]) return 56; if(Vrab01 == Config.Key[57]) return 57; if(Vrab01 == Config.Key[58]) return 58; if(Vrab01 == Config.Key[59]) return 59; if(Vrab01 == Config.Key[60]) return 60; if(Vrab01 == Config.Key[61]) return 61; if(Vrab01 == Config.Key[62]) return 62; if(Vrab01 == Config.Key[63]) return 63; if(Vrab01 == Config.Key[64]) return 64; if(Vrab01 == Config.Key[65]) return 65; if(Vrab01 == Config.Key[66]) return 66; if(Vrab01 == Config.Key[67]) return 67; if(Vrab01 == Config.Key[68]) return 68; if(Vrab01 == Config.Key[69]) return 69; if(Vrab01 == Config.Key[70]) return 70; if(Vrab01 == Config.Key[71]) return 71; if(Vrab01 == Config.Key[72]) return 72; if(Vrab01 == Config.Key[73]) return 73; if(Vrab01 == Config.Key[74]) return 74; if(Vrab01 == Config.Key[75]) return 75; if(Vrab01 == Config.Key[76]) return 76; if(Vrab01 == Config.Key[77]) return 77; if(Vrab01 == Config.Key[78]) return 78; if(Vrab01 == Config.Key[79]) return 79; if(Vrab01 == Config.Key[80]) return 80; if(Vrab01 == Config.Key[81]) return 81; if(Vrab01 == Config.Key[82]) return 82; if(Vrab01 == Config.Key[83]) return 83; if(Vrab01 == Config.Key[84]) return 84; if(Vrab01 == Config.Key[85]) return 85; if(Vrab01 == Config.Key[86]) return 86; if(Vrab01 == Config.Key[87]) return 87; if(Vrab01 == Config.Key[88]) return 88; if(Vrab01 == Config.Key[89]) return 89; if(Vrab01 == Config.Key[90]) return 90; if(Vrab01 == Config.Key[91]) return 91; if(Vrab01 == Config.Key[92]) return 92; if(Vrab01 == Config.Key[93]) return 93; return 0;}
  string DecryptionSTRING(string Vrab01){int8 Vrab02; uint32 Vrab03 = (uint32)Vrab01.size(); uint32 Vrab04 = 0; while(Vrab04 != Vrab03){Vrab02 = Vrab01[Vrab04]; if(Vrab02 >= '!' && Vrab02 <= '~') Vrab01[Vrab04] = (((uint32)(int32)Decryption94(Vrab02) - (Vrab04 % 94) + 94) % 94) + 33; Vrab04 += 1;} return Vrab01;}
  xint64 DecryptionDOUBLE(const int8 Vrab01[11]){return Decryption94(Vrab01[0]) * 8836 + Decryption94(Vrab01[1]) * 94 + Decryption94(Vrab01[2]) - 400000 + Decryption94(Vrab01[3]) * 0.064847759419264 + Decryption94(Vrab01[4]) * 0.000689869781056 + Decryption94(Vrab01[5]) * 0.000007339040224 + Decryption94(Vrab01[6]) * 0.000000078074896 +  Decryption94(Vrab01[7]) * 0.000000000830584 + Decryption94(Vrab01[8]) * 0.000000000008836 + Decryption94(Vrab01[9]) * 0.000000000000094 + Decryption94(Vrab01[10]) * 0.000000000000001;}
  uint64 DecryptionUINT64(const int8 Vrab01[10]){return (uint64)Decryption94(Vrab01[9]) + (uint64)Decryption94(Vrab01[8]) * 94 + (uint64)Decryption94(Vrab01[7]) * 8836 + (uint64)Decryption94(Vrab01[6]) * 830584 + (uint64)Decryption94(Vrab01[5]) * 78074896 + (uint64)Decryption94(Vrab01[4]) * 7339040224 + (uint64)Decryption94(Vrab01[3]) * 689869781056 + (uint64)Decryption94(Vrab01[2]) * 64847759419264 + (uint64)Decryption94(Vrab01[1]) * 6095689385410816 + (uint64)Decryption94(Vrab01[0]) * 572994802228616704;}
  uint32 DecryptionUINT32(const int8 Vrab01[5]){return (uint32)Decryption94(Vrab01[4]) + (uint32)Decryption94(Vrab01[3]) * 94 + (uint32)Decryption94(Vrab01[2]) * 8836 + (uint32)Decryption94(Vrab01[1]) * 830584 + (uint32)Decryption94(Vrab01[0]) * 78074896;}
  uint16 DecryptionUINT16(const int8 Vrab01[3]){return (uint16)Decryption94(Vrab01[2]) + (uint16)Decryption94(Vrab01[1]) * 94 + (uint16)Decryption94(Vrab01[0]) * 8836;}
  uint8 DecryptionUINT8(const int8 Vrab01[2]){return (uint8)Decryption94(Vrab01[1]) + (uint8)Decryption94(Vrab01[0]) * 94;}
  int64 DecryptionINT64(const int8 Vrab01[10]){return (int64)Decryption94(Vrab01[9]) + (int64)Decryption94(Vrab01[8]) * 94 + (int64)Decryption94(Vrab01[7]) * 8836 + (int64)Decryption94(Vrab01[6]) * 830584 + (int64)Decryption94(Vrab01[5]) * 78074896 + (int64)Decryption94(Vrab01[4]) * 7339040224 + (int64)Decryption94(Vrab01[3]) * 689869781056 + (int64)Decryption94(Vrab01[2]) * 64847759419264 + (int64)Decryption94(Vrab01[1]) * 6095689385410816 + (int64)Decryption94(Vrab01[0]) * 572994802228616704;}
  int32 DecryptionINT32(const int8 Vrab01[5]){return (int32)Decryption94(Vrab01[4]) + (int32)Decryption94(Vrab01[3]) * 94 + (int32)Decryption94(Vrab01[2]) * 8836 + (int32)Decryption94(Vrab01[1]) * 830584 + (int32)Decryption94(Vrab01[0]) * 78074896;}
  int16 DecryptionINT16(const int8 Vrab01[3]){return (int16)Decryption94(Vrab01[2]) + (int16)Decryption94(Vrab01[1]) * 94 + (int16)Decryption94(Vrab01[0]) * 8836;}
  int8 DecryptionINT8(const int8 Vrab01[2]){return (int8)Decryption94(Vrab01[1]) + (int8)Decryption94(Vrab01[0]) * 94;}
  uint32 DecryptionBMP(const int8 Vrab01[4]){return (uint32)Decryption94(Vrab01[3]) + (uint32)Decryption94(Vrab01[2]) * 94 + (uint32)Decryption94(Vrab01[1]) * 8836 + (uint32)Decryption94(Vrab01[0]) * 830584;}
  string Encryption94(const uint8 Vrab01){return {Config.Key[Vrab01 % 94]};}
  string EncryptionSTRING(string Vrab01){int8 Vrab02; uint32 Vrab03 = (uint32)Vrab01.size(); uint32 Vrab04 = 0; while(Vrab04 != Vrab03){Vrab02 = Vrab01[Vrab04]; if(Vrab02 >= '!' && Vrab02 <= '~') Vrab01[Vrab04] = Encryption94(((uint32)Vrab02 - 33 + Vrab04) % 94)[0]; Vrab04 += 1;} return Vrab01;}
  string EncryptionDOUBLE(xint64 Vrab01){Vrab01 += 400000; if(Vrab01 < 0){Vrab01 = 0;} else {if(Vrab01 > 800000) Vrab01 = 800000;} uint64 Vrab02 = (uint64)Vrab01; uint64 Vrab03 = Vrab02 / 94; xint64 Vrab11 = (Vrab01 - (xint64)(uint64)Vrab01) * 100000; xint64 Vrab12 = (Vrab11 - (xint64)(uint64)Vrab11) * 100000; xint64 Vrab13 = (Vrab12 - (xint64)(uint64)Vrab12) * 100000; uint64 Vrab04 = (uint64)Vrab11 * 10000000000 + (uint64)Vrab12 * 100000 + (uint64)Vrab13; uint64 Vrab05 = Vrab04 / 94; uint64 Vrab06 = Vrab05 / 94; uint64 Vrab07 = Vrab06 / 94; uint64 Vrab08 = Vrab07 / 94; uint64 Vrab09 = Vrab08 / 94; uint64 Vrab10 = Vrab09 / 94; return Encryption94((Vrab03 / 94) % 94) + Encryption94(Vrab03 % 94) + Encryption94(Vrab02 % 94) + Encryption94((Vrab10 / 94) % 94) + Encryption94(Vrab10 % 94) + Encryption94(Vrab09 % 94) + Encryption94(Vrab08 % 94) + Encryption94(Vrab07 % 94) + Encryption94(Vrab06 % 94) + Encryption94(Vrab05 % 94) + Encryption94(Vrab04 % 94);}
  string EncryptionUINT64(uint64 Vrab01){uint64 Vrab02 = Vrab01 / 94; uint64 Vrab03 = Vrab02 / 94; uint64 Vrab04 = Vrab03 / 94; uint64 Vrab05 = Vrab04 / 94; uint64 Vrab06 = Vrab05 / 94; uint64 Vrab07 = Vrab06 / 94; uint64 Vrab08 = Vrab07 / 94; uint64 Vrab09 = Vrab08 / 94; return Encryption94((Vrab09 / 94) % 94) + Encryption94(Vrab09 % 94) + Encryption94(Vrab08 % 94) + Encryption94(Vrab07 % 94) + Encryption94(Vrab06 % 94) + Encryption94(Vrab05 % 94) + Encryption94(Vrab04 % 94) + Encryption94(Vrab03 % 94) + Encryption94(Vrab02 % 94) + Encryption94(Vrab01 % 94);}
  string EncryptionUINT32(uint32 Vrab01){uint32 Vrab02 = Vrab01 / 94; uint32 Vrab03 = Vrab02 / 94; uint32 Vrab04 = Vrab03 / 94; return Encryption94((Vrab04 / 94) % 94) + Encryption94(Vrab04 % 94) + Encryption94(Vrab03 % 94) + Encryption94(Vrab02 % 94) + Encryption94(Vrab01 % 94);}
  string EncryptionUINT16(uint16 Vrab01){uint16 Vrab02 = Vrab01 / 94; return Encryption94((Vrab02 / 94) % 94) + Encryption94(Vrab02 % 94) + Encryption94(Vrab01 % 94);}
  string EncryptionUINT8(uint8 Vrab01){return Encryption94((Vrab01 / 94) % 94) + Encryption94(Vrab01 % 94);}
  string EncryptionINT64(int64 Vrab01){return EncryptionUINT64((uint64)Vrab01);}
  string EncryptionINT32(int32 Vrab01){return EncryptionUINT32((uint32)Vrab01);}
  string EncryptionINT8(int8 Vrab01){return EncryptionUINT8((uint8)Vrab01);}
  string EncryptionBMP(uint32 Vrab01){uint32 Vrab02 = Vrab01 / 94; uint32 Vrab03 = Vrab02 / 94; return Encryption94((Vrab03 / 94) % 94) + Encryption94(Vrab03 % 94) + Encryption94(Vrab02 % 94) + Encryption94(Vrab01 % 94);}
  string EncryptionECD(string Vrab01){std::streampos Post01; uint32 Vrab02; switch(Vrab0002){case 0: if(Vrab01 == "<bmp_begin>"){Vrab0002 = 1; return {Config.Key[0]};} if(Vrab01 == "<weapon_strength_list>"){Vrab0002 = 2; return {Config.Key[1]};} if(Vrab01 == "<frame>"){Vrab0002 = 11; Vect0001[Vect0001.size() - 1] = 0; return {Config.Key[2]};} return ""; case 1: if(Vrab01 == "<bmp_end>"){Vrab0002 = 0; return {Config.Key[0]};} if(Vrab01 == "name:"){Vrab0002 = 4; return {Config.Key[1]};} if(Vrab01 == "head:"){Vrab0002 = 5; Vrab0004 = 23; return {Config.Key[2]};} if(Vrab01 == "small:"){Vrab0002 = 5; Vrab0004 = 23; return {Config.Key[3]};} if(Vrab01[0] == 'f' && Vrab01[1] == 'i' && Vrab01[2] == 'l' && Vrab01[3] == 'e' && Vrab01[4] == '('){Vrab0002 = 5; Vrab0004 = 0; return {Config.Key[4]};} if(Vrab01 == "w:"){Vrab0002 = 7; return {Config.Key[5]};} if(Vrab01 == "h:"){Vrab0002 = 7; return {Config.Key[6]};} if(Vrab01 == "row:"){Vrab0002 = 7; return {Config.Key[7]};} if(Vrab01 == "col:"){Vrab0002 = 7; return {Config.Key[8]};} if(Vrab01 == "walking_frame_rate"){Vrab0002 = 7; return {Config.Key[9]};} if(Vrab01 == "running_frame_rate"){Vrab0002 = 7; return {Config.Key[10]};} if(Vrab01 == "walking_speed"){Vrab0002 = 8; return {Config.Key[11]};} if(Vrab01 == "walking_speedz"){Vrab0002 = 8; return {Config.Key[12]};} if(Vrab01 == "running_speed"){Vrab0002 = 8; return {Config.Key[13]};} if(Vrab01 == "running_speedz"){Vrab0002 = 8; return {Config.Key[14]};} if(Vrab01 == "heavy_walking_speed"){Vrab0002 = 8; return {Config.Key[15]};} if(Vrab01 == "heavy_walking_speedz"){Vrab0002 = 8; return {Config.Key[16]};} if(Vrab01 == "heavy_running_speed"){Vrab0002 = 8; return {Config.Key[17]};} if(Vrab01 == "heavy_running_speedz"){Vrab0002 = 8; return {Config.Key[18]};} if(Vrab01 == "jump_height"){Vrab0002 = 8; return {Config.Key[19]};} if(Vrab01 == "jump_distance"){Vrab0002 = 8; return {Config.Key[20]};} if(Vrab01 == "jump_distancez"){Vrab0002 = 8; return {Config.Key[21]};} if(Vrab01 == "dash_height"){Vrab0002 = 8; return {Config.Key[22]};} if(Vrab01 == "dash_distance"){Vrab0002 = 8; return {Config.Key[23]};} if(Vrab01 == "dash_distancez"){Vrab0002 = 8; return {Config.Key[24]};} if(Vrab01 == "rowing_height"){Vrab0002 = 8; return {Config.Key[25]};} if(Vrab01 == "rowing_distance"){Vrab0002 = 8; return {Config.Key[26]};} if(Vrab01 == "weapon_hp:"){Vrab0002 = 7; return {Config.Key[27]};} if(Vrab01 == "weapon_drop_hurt:"){Vrab0002 = 7; return {Config.Key[28]};} if(Vrab01 == "weapon_hit_sound:"){Vrab0002 = 6; return {Config.Key[29]};} if(Vrab01 == "weapon_drop_sound:"){Vrab0002 = 6; return {Config.Key[30]};} if(Vrab01 == "weapon_broken_sound:"){Vrab0002 = 6; return {Config.Key[31]};} return ""; case 4: Vrab0002 = 1; return EncryptionUINT32(Vrab01.size()) + EncryptionSTRING(Vrab01); case 5: Post01 = File0001.tellg(); Vrab0002 = 0; Vrab0003 = Strn0001.size(); while(Vrab0002 < Vrab0003){if(Vrab01 == Strn0001[Vrab0002]){Vrab0003 = Vrab0002; goto Labl0014;} Vrab0002 += 1;} Strn0001.push_back(Temp0003); File0001.close(); File0001.open(Vrab01, std::ios::in | std::ios::binary); if(!File0001.is_open()){File0001.open(Strn0001[Strn0001.size() - 1]); File0001.seekg(Post01); Strn0001.pop_back(); goto Labl0014;} Temp0003 = Vrab01; Encryption(3, EncryptionUINT32(Vrab0002)); if(File0001.is_open()) File0001.close(); File0001.open(Strn0001[Strn0001.size() - 1], std::ios::in | std::ios::binary); File0001.seekg(Post01); Temp0003 = Strn0001[Strn0001.size() - 1]; Strn0001.pop_back(); Strn0001.push_back(Vrab01); Vrab0003 = Strn0001.size() - 1; Labl0014: Vrab0002 = 1; return EncryptionUINT32(Vrab0003); case 6: Post01 = File0001.tellg(); Vrab0002 = 0; Vrab0003 = Strn0001.size(); while(Vrab0002 < Vrab0003){if(Vrab01 == Strn0001[Vrab0002]){Vrab0003 = Vrab0002; goto Labl0015;} Vrab0002 += 1;} Strn0001.push_back(Temp0003); File0001.close(); File0001.open(Vrab01, std::ios::in | std::ios::binary); if(!File0001.is_open()){File0001.open(Strn0001[Strn0001.size() - 1]); File0001.seekg(Post01); Strn0001.pop_back(); goto Labl0015;} Temp0003 = Vrab01; Encryption(1, EncryptionUINT32(Vrab0002)); if(File0001.is_open()) File0001.close(); File0001.open(Strn0001[Strn0001.size() - 1], std::ios::in | std::ios::binary); File0001.seekg(Post01); Temp0003 = Strn0001[Strn0001.size() - 1]; Strn0001.pop_back(); Strn0001.push_back(Vrab01); Vrab0003 = Strn0001.size() - 1; Labl0015: Vrab0002 = 1; return EncryptionUINT32(Vrab0003); case 7: Vrab0002 = 1; return EncryptionINT32(ToNum(Vrab01)); case 8: if((Vrab01[0] < '0' || Vrab01[0] > '9') && Vrab01[0] != '-') Vrab01.insert(0, "0"); Vrab0002 = 0; if(Vrab01[0] == '-') Vrab0002 += 1; Vrab0003 = 0; while(Vrab0002 + Vrab0003 < Vrab01.size() && Vrab01[Vrab0002 + Vrab0003] >= '0' && Vrab01[Vrab0002 + Vrab0003] <= '9') Vrab0003 += 1; if(Vrab0003 > 9) Vrab01.erase(Vrab0002, Vrab0003 - 9); Vrab02 = (uint32)ToNum(Vrab01); while(Vrab01[0] != '.' && 0 < Vrab01.size()) Vrab01.erase(0, 1); if(Vrab01.size() > 1){if(Vrab01[0] == '.' && Vrab01[1] >= '0' && Vrab01[1] <= '9'){Vrab01.erase(0, 1); Vrab0002 = 0; while(Vrab0002 < Vrab01.size() && Vrab01[Vrab0002] >= '0' && Vrab01[Vrab0002] <= '9') Vrab0002 += 1; if(Vrab0002 > 9) Vrab01.erase(10, Vrab0003 - 9); Vrab0003 = (uint32)ToNum(Vrab01);} else {Vrab0003 = 0;}} else {Vrab0003 = 0;} Vrab0002 = 1; return EncryptionUINT32(Vrab02) + EncryptionUINT32(Vrab0003); case 2: if(Vrab01 == "<weapon_strength_list_end>"){Vrab0002 = 0; return {Config.Key[0]};} if(Vrab01 == "entry:"){Vrab0002 = 9; return {Config.Key[1]};} if(Vrab01 == "dvx:"){Vrab0002 = 9; return {Config.Key[2]};} if(Vrab01 == "dvy:"){Vrab0002 = 9; return {Config.Key[3]};} if(Vrab01 == "fall:"){Vrab0002 = 9; return {Config.Key[4]};} if(Vrab01 == "arest:"){Vrab0002 = 9; return {Config.Key[5]};} if(Vrab01 == "vrest:"){Vrab0002 = 9; return {Config.Key[6]};} if(Vrab01 == "respond:"){Vrab0002 = 9; return {Config.Key[7]};} if(Vrab01 == "effect:"){Vrab0002 = 9; return {Config.Key[8]};} if(Vrab01 == "bdefend:"){Vrab0002 = 9; return {Config.Key[9]};} if(Vrab01 == "injury:"){Vrab0002 = 9; return {Config.Key[10]};} if(Vrab01 == "zwidth:"){Vrab0002 = 9; return {Config.Key[11]};} return ""; case 9: Vrab0002 = 2; return EncryptionINT32(ToNum(Vrab01)); case 3: if(Vrab01 == "<frame_end>"){Vrab0002 = 0; return {Config.Key[0]};} if(Vrab01 == "pic:"){Vrab0002 = 11; return {Config.Key[1]};} if(Vrab01 == "state:"){Vrab0002 = 32; return {Config.Key[2]};} if(Vrab01 == "wait:"){Vrab0002 = 11; return {Config.Key[3]};} if(Vrab01 == "next:"){Vrab0002 = 11; return {Config.Key[4]};} if(Vrab01 == "dvx:"){Vrab0002 = 11; return {Config.Key[5]};} if(Vrab01 == "dvy:"){Vrab0002 = 11; return {Config.Key[6]};} if(Vrab01 == "dvz:"){Vrab0002 = 11; return {Config.Key[7]};} if(Vrab01 == "centerx:"){Vrab0002 = 11; return {Config.Key[8]};} if(Vrab01 == "centery:"){Vrab0002 = 25; return {Config.Key[9]};} if(Vrab01 == "hit_a:"){Vrab0002 = 11; return {Config.Key[10]};} if(Vrab01 == "hit_d:"){Vrab0002 = 11; return {Config.Key[11]};} if(Vrab01 == "hit_j:"){Vrab0002 = 11; return {Config.Key[12]};} if(Vrab01 == "hit_Fa:"){Vrab0002 = 11; return {Config.Key[13]};} if(Vrab01 == "hit_Fj:"){Vrab0002 = 11; return {Config.Key[14]};} if(Vrab01 == "hit_Da:"){Vrab0002 = 11; return {Config.Key[15]};} if(Vrab01 == "hit_Dj:"){Vrab0002 = 11; return {Config.Key[16]};} if(Vrab01 == "hit_Ua:"){Vrab0002 = 11; return {Config.Key[17]};} if(Vrab01 == "hit_Uj:"){Vrab0002 = 11; return {Config.Key[18]};} if(Vrab01 == "hit_ja:"){Vrab0002 = 11; return {Config.Key[19]};} if(Vrab01 == "mp:"){Vrab0002 = 11; return {Config.Key[20]};} if(Vrab01 == "sound:"){Vrab0002 = 10; return {Config.Key[21]};} if(Vrab01 == "bpoint:"){Vrab0002 = 12; return {Config.Key[22]};} if(Vrab01 == "cpoint:"){Vrab0002 = 14; return {Config.Key[23]};} if(Vrab01 == "wpoint:"){Vrab0002 = 16; return {Config.Key[24]};} if(Vrab01 == "opoint:"){Vrab0002 = 18; return {Config.Key[25]};} if(Vrab01 == "itr:"){Vrab0002 = 20; return {Config.Key[26]};} if(Vrab01 == "bdy:"){Vrab0002 = 23; return {Config.Key[27]};} return ""; case 10: Post01 = File0001.tellg(); Vrab0002 = 0; Vrab0003 = Strn0001.size(); while(Vrab0002 < Vrab0003){if(Vrab01 == Strn0001[Vrab0002]){Vrab0003 = Vrab0002; goto Labl0016;} Vrab0002 += 1;} Strn0001.push_back(Temp0003); File0001.close(); File0001.open(Vrab01, std::ios::in | std::ios::binary); if(!File0001.is_open()){File0001.open(Strn0001[Strn0001.size() - 1]); File0001.seekg(Post01); Strn0001.pop_back(); goto Labl0016;} Temp0003 = Vrab01; Encryption(1, EncryptionUINT32(Vrab0002)); if(File0001.is_open()) File0001.close(); File0001.open(Strn0001[Strn0001.size() - 1], std::ios::in | std::ios::binary); File0001.seekg(Post01); Temp0003 = Strn0001[Strn0001.size() - 1]; Strn0001.pop_back(); Strn0001.push_back(Vrab01); Vrab0003 = Strn0001.size() - 1; Labl0016: Vrab0002 = 3; return EncryptionUINT32(Vrab0003); case 32: Vrab0003 = (uint32)ToNum(Vrab01); if((int32)Vrab0003 / 1000 == 8){Vrab0003 = Vrab0003 % 1000; Vrab0002 = 0; while(Vrab0002 < Vect0001.size() - 1){if(Vect0001[Vrab0002] == (int32)Vrab0003){Vrab0003 = Vrab0002; Vrab0002 = 3; return std::string(1, Config.Key[93]) + EncryptionUINT32(Vrab0003);} Vrab0002 += 1;}} Vrab0002 = 3; return EncryptionUINT32(Vrab0003); case 25: Vrab0003 = (uint32)Positive(ToNum(Vrab01) / 1000000); if(Vrab0003 == 0){Vrab0002 = 3; return EncryptionINT32(ToNum(Vrab01));} Vrab0002 = 0; while(Vrab0002 < Vect0001.size() - 1){if(Vect0001[Vrab0002] == (int32)Vrab0003){Vrab0003 = Vrab0002; Vrab0002 = 3; return std::string(1, Config.Key[93]) + EncryptionUINT32(Vrab0003) + EncryptionINT32(ToNum(Vrab01) % 1000000);} Vrab0002 += 1;} case 11: Vrab0002 = 3; return EncryptionINT32(ToNum(Vrab01)); case 12: if(Vrab01 == "bpoint_end:"){Vrab0002 = 3; return {Config.Key[0]};} if(Vrab01 == "x:"){Vrab0002 = 13; return {Config.Key[1]};} if(Vrab01 == "y:"){Vrab0002 = 13; return {Config.Key[2]};} return ""; case 13: Vrab0002 = 12; return EncryptionINT32(ToNum(Vrab01)); case 14: if(Vrab01 == "cpoint_end:"){Vrab0002 = 3; return {Config.Key[0]};} if(Vrab01 == "kind:"){Vrab0002 = 15; return {Config.Key[1]};} if(Vrab01 == "x:"){Vrab0002 = 15; return {Config.Key[2]};} if(Vrab01 == "y:"){Vrab0002 = 26; return {Config.Key[3]};} if(Vrab01 == "vaction:"){Vrab0002 = 15; return {Config.Key[4]};} if(Vrab01 == "aaction:"){Vrab0002 = 15; return {Config.Key[5]};} if(Vrab01 == "jaction:"){Vrab0002 = 15; return {Config.Key[7]};} if(Vrab01 == "taction:"){Vrab0002 = 15; return {Config.Key[8]};} if(Vrab01 == "throwvx:"){Vrab0002 = 15; return {Config.Key[9]};} if(Vrab01 == "throwvy:"){Vrab0002 = 15; return {Config.Key[10]};} if(Vrab01 == "throwvz:"){Vrab0002 = 15; return {Config.Key[11]};} if(Vrab01 == "throwinjury:"){Vrab0002 = 15; return {Config.Key[12]};} if(Vrab01 == "dircontrol:"){Vrab0002 = 15; return {Config.Key[13]};} if(Vrab01 == "decrease:"){Vrab0002 = 15; return {Config.Key[14]};} if(Vrab01 == "hurtable:"){Vrab0002 = 15; return {Config.Key[15]};} if(Vrab01 == "cover:"){Vrab0002 = 15; return {Config.Key[16]};} if(Vrab01 == "injury:"){Vrab0002 = 15; return {Config.Key[17]};} return ""; case 26: Vrab0003 = (uint32)Positive(ToNum(Vrab01) / 1000000); if(Vrab0003 == 0){Vrab0002 = 14; return EncryptionINT32(ToNum(Vrab01));} Vrab0002 = 0; while(Vrab0002 < Vect0001.size() - 1){if(Vect0001[Vrab0002] == (int32)Vrab0003){Vrab0003 = Vrab0002; Vrab0002 = 14; return std::string(1, Config.Key[93]) + EncryptionUINT32(Vrab0003) + EncryptionINT32(ToNum(Vrab01) % 1000000);} Vrab0002 += 1;} case 15: Vrab0002 = 14; return EncryptionINT32(ToNum(Vrab01)); case 16: if(Vrab01 == "wpoint_end:"){Vrab0002 = 3; return {Config.Key[0]};} if(Vrab01 == "kind:"){Vrab0002 = 17; return {Config.Key[1]};} if(Vrab01 == "x:"){Vrab0002 = 17; return {Config.Key[2]};} if(Vrab01 == "y:"){Vrab0002 = 27; return {Config.Key[3]};} if(Vrab01 == "weaponact:"){Vrab0002 = 17; return {Config.Key[4]};} if(Vrab01 == "attacking:"){Vrab0002 = 17; return {Config.Key[5]};} if(Vrab01 == "cover:"){Vrab0002 = 17; return {Config.Key[6]};} if(Vrab01 == "dvx:"){Vrab0002 = 17; return {Config.Key[7]};} if(Vrab01 == "dvy:"){Vrab0002 = 17; return {Config.Key[8]};} if(Vrab01 == "dvz:"){Vrab0002 = 17; return {Config.Key[9]};} return ""; case 27: Vrab0003 = (uint32)Positive(ToNum(Vrab01) / 1000000); if(Vrab0003 == 0){Vrab0002 = 16; return EncryptionINT32(ToNum(Vrab01));} Vrab0002 = 0; while(Vrab0002 < Vect0001.size() - 1){if(Vect0001[Vrab0002] == (int32)Vrab0003){Vrab0003 = Vrab0002; Vrab0002 = 16; return std::string(1, Config.Key[93]) + EncryptionUINT32(Vrab0003) + EncryptionINT32(ToNum(Vrab01) % 1000000);} Vrab0002 += 1;} case 17: Vrab0002 = 16; return EncryptionINT32(ToNum(Vrab01)); case 18: if(Vrab01 == "opoint_end:"){Vrab0002 = 3; return {Config.Key[0]};} if(Vrab01 == "kind:"){Vrab0002 = 19; return {Config.Key[1]};} if(Vrab01 == "x:"){Vrab0002 = 19; return {Config.Key[2]};} if(Vrab01 == "y:"){Vrab0002 = 28; return {Config.Key[3]};} if(Vrab01 == "oid:"){Vrab0002 = 31; return {Config.Key[4]};} if(Vrab01 == "action:"){Vrab0002 = 19; return {Config.Key[5]};} if(Vrab01 == "facing:"){Vrab0002 = 19; return {Config.Key[6]};} if(Vrab01 == "dvx:"){Vrab0002 = 19; return {Config.Key[7]};} if(Vrab01 == "dvy:"){Vrab0002 = 19; return {Config.Key[8]};} return ""; case 31: Vrab0003 = (uint32)ToNum(Vrab01); Vrab0002 = 0; while(Vrab0002 < Vect0001.size() - 1){if(Vect0001[Vrab0002] == (int32)Vrab0003){Vrab0003 = Vrab0002; Vrab0002 = 18; return std::string(1, Config.Key[93]) + EncryptionUINT32(Vrab0003);} Vrab0002 += 1;} Vrab0002 = 18; return EncryptionINT32(ToNum(Vrab01)); case 28: Vrab0003 = (uint32)Positive(ToNum(Vrab01) / 1000000); if(Vrab0003 == 0){Vrab0002 = 18; return EncryptionINT32(ToNum(Vrab01));} Vrab0002 = 0; while(Vrab0002 < Vect0001.size() - 1){if(Vect0001[Vrab0002] == (int32)Vrab0003){Vrab0003 = Vrab0002; Vrab0002 = 18; return std::string(1, Config.Key[93]) + EncryptionUINT32(Vrab0003) + EncryptionINT32(ToNum(Vrab01) % 1000000);} Vrab0002 += 1;} case 19: Vrab0002 = 18; return EncryptionINT32(ToNum(Vrab01)); case 20: if(Vrab01 == "itr_end:"){Vrab0002 = 3; return {Config.Key[0]};} if(Vrab01 == "kind:"){Vrab0002 = 21; return {Config.Key[1]};} if(Vrab01 == "x:"){Vrab0002 = 21; return {Config.Key[2]};} if(Vrab01 == "y:"){Vrab0002 = 29; return {Config.Key[3]};} if(Vrab01 == "w:"){Vrab0002 = 21; return {Config.Key[4]};} if(Vrab01 == "h:"){Vrab0002 = 21; return {Config.Key[5]};} if(Vrab01 == "zwidth:"){Vrab0002 = 21; return {Config.Key[6]};} if(Vrab01 == "dvx:"){Vrab0002 = 21; return {Config.Key[7]};} if(Vrab01 == "dvy:"){Vrab0002 = 21; return {Config.Key[8]};} if(Vrab01 == "arest:"){Vrab0002 = 21; return {Config.Key[9]};} if(Vrab01 == "vrest:"){Vrab0002 = 21; return {Config.Key[10]};} if(Vrab01 == "bdefend:"){Vrab0002 = 21; return {Config.Key[11]};} if(Vrab01 == "fall:"){Vrab0002 = 21; return {Config.Key[12]};} if(Vrab01 == "injury:"){Vrab0002 = 21; return {Config.Key[13]};} if(Vrab01 == "effect:"){Vrab0002 = 21; return {Config.Key[14]};} if(Vrab01 == "respond:"){Vrab0002 = 21; return {Config.Key[15]};} if(Vrab01 == "catchingact:"){Vrab0002 = 22; return {Config.Key[16]};} if(Vrab01 == "caughtact:"){Vrab0002 = 22; return {Config.Key[17]};} return ""; case 29: Vrab0003 = (uint32)Positive(ToNum(Vrab01) / 1000000); if(Vrab0003 == 0){if(Vrab0002 == 22){Vrab0002 = 21;} else {Vrab0002 = 20;} return EncryptionINT32(ToNum(Vrab01));} Vrab0002 = 0; while(Vrab0002 < Vect0001.size() - 1){if(Vect0001[Vrab0002] == (int32)Vrab0003){Vrab0003 = Vrab0002; Vrab0002 = 20; return std::string(1, Config.Key[93]) + EncryptionUINT32(Vrab0003) + EncryptionINT32(ToNum(Vrab01) % 1000000);} Vrab0002 += 1;} case 22: Full_Injection_ID2 = ToNum(Vrab01); Full_Injection_ID = 0; case 21: if(Full_Injection_ID == 0 && Vrab01[0] != '-' && (Vrab01[0] < '0' || Vrab01[0] > '9')){Temp0001 += EncryptionINT32(Full_Injection_ID2); Vrab0002 = 20; return EncryptionECD(Vrab01);} if(Vrab0002 == 22){Vrab0002 = 21;} else {Full_Injection_ID = -1; Vrab0002 = 20;} return EncryptionINT32(ToNum(Vrab01)); case 23: if(Vrab01 == "bdy_end:"){Vrab0002 = 3; return {Config.Key[0]};} if(Vrab01 == "kind:"){Vrab0002 = 24; return {Config.Key[1]};} if(Vrab01 == "x:"){Vrab0002 = 24; return {Config.Key[2]};} if(Vrab01 == "y:"){Vrab0002 = 30; return {Config.Key[3]};} if(Vrab01 == "w:"){Vrab0002 = 24; return {Config.Key[4]};} if(Vrab01 == "h:"){Vrab0002 = 24; return {Config.Key[5]};} return ""; case 30: Vrab0003 = (uint32)Positive(ToNum(Vrab01) / 1000000); if(Vrab0003 == 0){Vrab0002 = 23; return EncryptionINT32(ToNum(Vrab01));} Vrab0002 = 0; while(Vrab0002 < Vect0001.size() - 1){if(Vect0001[Vrab0002] == (int32)Vrab0003){Vrab0003 = Vrab0002; Vrab0002 = 23; return std::string(1, Config.Key[93]) + EncryptionUINT32(Vrab0003) + EncryptionINT32(ToNum(Vrab01) % 1000000);} Vrab0002 += 1;} case 24: Vrab0002 = 23; return EncryptionINT32(ToNum(Vrab01)); default: return "";}}
  int0 Encryption(uint8 Vrab01, string Vrab02){if(!File0001.is_open()) return; if(!File0002.is_open()) return; std::stringstream Strn01; switch(Vrab01){case 0: Vrab0003 = 0; while(Temp0001.size() > 0 && (Temp0001[Vrab0003] < '0' || Temp0001[Vrab0003] > '9')) Temp0001.erase(0, 1); if(Temp0001.size() == 0) return; Vrab0003 = (uint32)ToNum(string(Temp0001, 0, Temp0001.size() - 3)); Vrab0002 = 0; while(Vrab0002 < Vect0001.size()){if(Vect0001[Vrab0002] == (int32)Vrab0003){Strn01 << File0001.rdbuf(); Temp0003 = Strn01.str(); File0002 << Config.Key[0] << EncryptionINT32(Vrab0002) << EncryptionUINT32(Temp0003.size()) << EncryptionSTRING(Temp0003); File0001.close(); return;} Vrab0002 += 1;} File0001.close(); break; case 1: Console.Log += "[] Packing \"" + Temp0003 + "\".\n"; Console.PrintSet(); Strn01 << File0001.rdbuf(); Temp0003 = Strn01.str(); File0002 << Config.Key[1] << Vrab02 << EncryptionUINT32(Temp0003.size()) << EncryptionSTRING(Temp0003); File0001.close(); break; case 2: Vect0001.push_back(0); Temp0001 = ""; Vrab0002 = 0; while(File0001){File0001 >> Temp0002; if(Temp0002[0] == '#'){std::getline(File0001, Temp0002); continue;} Temp0001 += EncryptionECD(Temp0002);} File0002 << Vrab02 << EncryptionUINT32(Temp0001.size()) << EncryptionSTRING(Temp0001); Vect0001.pop_back(); File0001.close(); break; case 3: goto Labl0019; default: File0001.close(); break;} return; Labl0019: Vect0001.push_back(0); BMP Bitm01(Temp0003.c_str()); if(Bitm01.bmp_info_header.compression != 3 && Bitm01.bmp_info_header.bit_count != 3 && Bitm01.bmp_info_header.size_image != 0 && Bitm01.data.size() != (uint32)(Bitm01.bmp_info_header.width * Bitm01.bmp_info_header.height * 3)){File0001.close(); if(InjectionDone){Temp0003.erase(Temp0003.size() - 4, Temp0003.size() - 1); Temp0002 = Strn0001[Strn0001.size() - 1]; Strn0001.pop_back(); Vrab0002 = 0; Vrab0003 = Strn0001.size(); while(Vrab0002 < Vrab0003){if(Temp0003 + "_mirror.bmp" == Strn0001[Vrab0002]){Strn0001.push_back(Temp0002); Vect0001.pop_back(); if(File0001.is_open()) File0001.close(); Temp0003 += ".bmp"; File0001.open(Temp0003, std::ios::in | std::ios::binary); Encryption(1, Vrab02); return;} Vrab0002 += 1;} if(!Exist(Temp0003 + "_mirror.bmp")){Strn0001.push_back(Temp0002); Vect0001.pop_back(); if(File0001.is_open()) File0001.close(); Temp0003 += ".bmp"; File0001.open(Temp0003, std::ios::in | std::ios::binary); Encryption(1, Vrab02); return;} if(File0001.is_open()) File0001.close(); File0001.open(Temp0003 + ".bmp", std::ios::in | std::ios::binary); Strn0001.push_back(Temp0003 + "_mirror.bmp"); Temp0003 += ".bmp"; Encryption(1, EncryptionUINT32(DecryptionUINT32(Vrab02.c_str()) + 1)); File0001.close(); Temp0003 = Strn0001[Strn0001.size() - 1]; Strn0001.pop_back(); File0001.open(Temp0003, std::ios::in | std::ios::binary); if(File0001.is_open()){Strn0001.push_back(Temp0003); Strn0001.push_back(Temp0002); File0002 << Config.Key[4]; Encryption(1, EncryptionUINT32(Strn0001.size() - 2));} else {Strn0001.push_back(Temp0002); Vect0001.pop_back(); return;}} else {File0001.open(Temp0003, std::ios::in | std::ios::binary); Temp0002 = Temp0003; Encryption(1, Vrab02);}} else {Console.Log += "[] Including \"" + Temp0003 + "\".\n"; Console.PrintSet(); Vrab0002 = (uint32)Bitm01.data.size(); if(Vrab0004 == 23){File0002 << Config.Key[5];} else {File0002 << Config.Key[3];} File0002 << Vrab02 << EncryptionUINT32((uint32)Bitm01.bmp_info_header.width) << EncryptionUINT32((uint32)Bitm01.bmp_info_header.height) << EncryptionUINT32(Vrab0002 / 3); Vrab0004 = 0; for(Vrab0003 = 0; Vrab0003 < Vrab0002; Vrab0003 += 3){Vect0001[Vect0001.size() - 1] = (int32)((uint32)Bitm01.data[Vrab0003] + ((uint32)Bitm01.data[Vrab0003 + 1] * 256) + ((uint32)Bitm01.data[Vrab0003 + 2] * 65536)); if((uint32)Vect0001[Vect0001.size() - 1] == (uint32)(int32)Vrab0004){File0002 << Config.Key[93];} else {File0002 << EncryptionBMP((uint32)Vect0001[Vect0001.size() - 1]); Vrab0004 = (xint64)Vect0001[Vect0001.size() - 1];}}} Vect0001.pop_back(); File0001.close();}
 //-//
 //Functions
  int0 I_Configuring()
  {
   Temp0002 = "true"; Temp0003 = "false"; Vrab0003 = 0; std::stringstream Temp01; if(File0001.is_open()) File0001.close(); File0001.open(TEMPORAL_FILE, std::ios::in | std::ios::binary); File0001.seekg(0, File0001.end); if((uint32)File0001.tellg() > (uint32)295){File0001.seekg(File0001.tellg() - (std::streampos)94); Temp0001.resize(94); File0001.read(&Temp0001[0], 94); if(Temp0001 == "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"){Vrab0003 = 1; File0001.seekg(0, File0001.beg); Temp01; Temp01.str(""); Temp01 << File0001.rdbuf(); Temp0001 = Temp01.str(); Temp0001.erase(0, 200); Temp0001.erase(Temp0001.size() - 94, 94); strcpy(Config.Key, "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"); if(File0002.is_open()) File0002.close(); File0002.open(TEMPORAL_FILE, std::ios::out | std::ios::binary); File0002 << EncryptionSTRING(Temp0001); File0001.close(); File0002.close();}}
   Labl0001: Multi_Stating = false; strcpy(Config.Key, "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"); if(File0001.is_open()) File0001.close(); if(Vrab0003 == 1){File0001.open(TEMPORAL_FILE, std::ios::in | std::ios::binary);} else {File0001.open("configuration.txt", std::ios::in | std::ios::binary);}
   if(File0001.is_open())
   {
    while(File0001){File0001 >> Temp0001; if(Temp0001.compare(INJECTION_VERSION) == 0) goto Labl0003;} goto Labl0002; Labl0003: File0001.seekg(0, File0001.beg); while(File0001){File0001 >> Temp0001; if(Temp0001.compare("Mesujin.") == 0) goto Labl0004;} goto Labl0002; Labl0004: File0001.seekg(0, File0001.beg); while(File0001){File0001 >> Temp0001; if(Temp0001.compare("Doix,") == 0) goto Labl0005;} goto Labl0002; Labl0005: File0001.seekg(0, File0001.beg); while(File0001){File0001 >> Temp0001; if(Temp0001.compare("Som1Lse,") == 0) goto Labl0006;} goto Labl0002; Labl0006: File0001.seekg(0, File0001.beg); while(File0001){File0001 >> Temp0001; if(Temp0001.compare("zort,") == 0) goto Labl0007;} goto Labl0002; Labl0007: File0001.seekg(0, File0001.beg); while(File0001){File0001 >> Temp0001; if(Temp0001.compare("Determination,") == 0){File0001 >> Temp0002 >> Temp0001 >> Temp0003; break;}} File0001.seekg(0, File0001.beg);
    while(File0001)
	{
	 File0001 >> Temp0001;
	 if(Temp0001[0] == '/') if(Temp0001[1] == '/'){getline(File0001, Temp0001); continue;}
     if(Temp0001.compare("Determination,") == 0){File0001 >> Temp0001 >> Temp0001 >> Temp0001; continue;}
     if(Temp0001.compare("Key") == 0){File0001 >> Temp0001 >> Temp0001; continue;}

	 if(Temp0001.compare("Load_Other_DLL") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.LoadDLL = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.LoadDLL = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("DLL_Directory") == 0){File0001 >> Temp0001 >> Config.DDirectory; Manage(Config.DDirectory); continue;}
     if(Temp0001.compare("AI_Directory") == 0){File0001 >> Temp0001 >> Config.AI; Manage(Config.AI); continue;}
     if(Temp0001.compare("AI_Debug_Console") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Multi_Stating = true;} else {if(Temp0001.compare(Temp0003) == 0){Multi_Stating = false;} else {goto Labl0002;}} continue;}
     if(Temp0001.compare("AI_Debug_Console_Size") == 0){File0001 >> Temp0001 >> Console_Size; if(Console_Size < 0) goto Labl0002; continue;}
     if(Temp0001.compare("AI_Debug_Console_Style") == 0){File0001 >> Temp0001 >> Console_Style; if(Console_Style < 0 || Console_Style > 255) goto Labl0002; continue;}
     if(Temp0001.compare("Sleep_Mode") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Sleep_Mode = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Sleep_Mode = false;} else {goto Labl0002;}} continue;}
     if(Temp0001.compare("Hidden_Mode") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){if(Vrab0003 == 1){Vrab0003 = 1;} else {Vrab0003 = 2;}} else {if(Temp0001.compare(Temp0003) == 0){Vrab0003 = 0;} else {goto Labl0002;}} continue;}
     if(Temp0001.compare("Full_Injection") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Full_Injection = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Full_Injection = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Notification_Post") == 0){File0001 >> Temp0001 >> Config.Not_Post; if(Config.Not_Post < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("Notification_Model") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Model = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Model = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Landing_Frame") == 0){File0001 >> Temp0001 >> Config.LandingFrame; if(Config.LandingFrame < 0) goto Labl0002; continue;}
    
     if(Temp0001.compare("Hidden_IDs") == 0){File0001 >> Temp0001 >> Config.IDs[0] >> Temp0001 >> Config.IDs[1]; if(Config.IDs[0] < 0 || Config.IDs[1] < 0) goto Labl0002; continue;}
     if(Temp0001.compare("Weapon_IDs") == 0){File0001 >> Temp0001 >> Config.IDs[12] >> Temp0001 >> Config.IDs[13]; if(Config.IDs[12] < 0 || Config.IDs[13] < 0) goto Labl0002; continue;}
     if(Temp0001.compare("Minion_IDs") == 0){File0001 >> Temp0001 >> Config.IDs[2] >> Temp0001 >> Config.IDs[3]; if(Config.IDs[2] < 0 || Config.IDs[3] < 0) goto Labl0002; continue;}
     if(Temp0001.compare("Minion_IDs_2") == 0){File0001 >> Temp0001 >> Config.IDs[4] >> Temp0001 >> Config.IDs[5]; if(Config.IDs[4] < 0 || Config.IDs[5] < 0) goto Labl0002; continue;}
     if(Temp0001.compare("Available_IDs") == 0){File0001 >> Temp0001 >> Config.IDs[6] >> Temp0001 >> Config.IDs[7]; if(Config.IDs[6] < 0 || Config.IDs[7] < 0) goto Labl0002; continue;}
     if(Temp0001.compare("Available_IDs_2") == 0){File0001 >> Temp0001 >> Config.IDs[8] >> Temp0001 >> Config.IDs[9]; if(Config.IDs[8] < 0 || Config.IDs[9] < 0) goto Labl0002; continue;}
     if(Temp0001.compare("Available_IDs_3") == 0){File0001 >> Temp0001 >> Config.IDs[10] >> Temp0001 >> Config.IDs[11]; if(Config.IDs[10] < 0 || Config.IDs[11] < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("Debug") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Debug = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Debug = false;} else {goto Labl0002;}} continue;}
     if(Temp0001.compare("Style") == 0){File0001 >> Temp0001 >> Config.Style; if(Config.Style < 0) goto Labl0002; continue;}
     if(Temp0001.compare("Delay") == 0){File0001 >> Temp0001 >> Config.Delay; if(Config.Delay < 0) goto Labl0002; continue;}
     if(Temp0001.compare("Build") == 0){File0001 >> Temp0001 >> Config.Build; Manage(Config.Build); continue;}
	 if(Temp0001.compare("Input") == 0){File0001 >> Temp0001 >> Config.Input; Manage(Config.Input); continue;}
	 if(Temp0001.compare("Output") == 0){File0001 >> Temp0001 >> Config.Output; continue;}
	 if(Temp0001.compare("Insight") == 0){File0001 >> Temp0001 >> Config.Insight; Manage(Config.Insight); continue;}
	 if(Temp0001.compare("Outsight") == 0){File0001 >> Temp0001 >> Config.Outsight; Manage(Config.Outsight); continue;}
	 if(Temp0001.compare("Overwrite") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Overwrite = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Overwrite = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Get_Mirrors") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Get_Mirrors = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Get_Mirrors = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Permanentness") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Permanentness = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Permanentness = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Separated_Files") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Build_Directory = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Build_Directory = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Key") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.length() != 94) goto Labl0002; strcpy(Config.Key, Temp0001.c_str());}

     if(Temp0001.compare("2D_Mode") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.TD_Mode = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.TD_Mode = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Position") == 0){File0001 >> Temp0001 >> Config.TD_Post; if(Config.TD_Post < 0 || Config.TD_Post > 2) goto Labl0002; continue;}
	 if(Temp0001.compare("Holdable_Defend") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Hold_Def = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Hold_Def = false;} else {goto Labl0002;}} continue;}
     if(Temp0001.compare("Holdable_Defend_TU") == 0){File0001 >> Temp0001 >> Config.Hold_Def_TU; if(Config.Hold_Def_TU < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("Minimum_'bdefend:'") == 0){File0001 >> Temp0001 >> Config.Min_Bdef; if(Config.Min_Bdef < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("'bdefend:'_Effectivity") == 0){File0001 >> Temp0001 >> Config.Bdef_E; if(Config.Bdef_E < 0) goto Labl0002; continue;}
     
	 if(Temp0001.compare("Disable_DHP") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Dis_DHP = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Dis_DHP = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Disable_MP") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Dis_MP = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Dis_MP = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Milk_Amount") == 0){File0001 >> Temp0001 >> Config.M_Amount; if(Config.M_Amount < 0) goto Labl0002; continue;}
     if(Temp0001.compare("Milk_Speed") == 0){File0001 >> Temp0001 >> Config.M_Speed; if(Config.M_Speed < 0) goto Labl0002; continue;}
     if(Temp0001.compare("Tea_Amount") == 0){File0001 >> Temp0001 >> Config.T_Amount; if(Config.T_Amount < 0) goto Labl0002; continue;}
     if(Temp0001.compare("Tea_Speed") == 0){File0001 >> Temp0001 >> Config.T_Speed; if(Config.T_Speed < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("Base_Reserve") == 0){File0001 >> Temp0001 >> Config.B_Reserve; Config.B_Reserve += 1; if(Config.B_Reserve < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("Stage_Reserve") == 0){File0001 >> Temp0001 >> Config.S_Reserve; if(Config.S_Reserve < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("MP_Rest") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.MP_Rest = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.MP_Rest = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Immune_Time") == 0){File0001 >> Temp0001 >> Config.Imm_Time; if(Config.Imm_Time < 0) goto Labl0002; continue;}

     if(Temp0001.compare("Disable_HP_Regen") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.HP_Regen = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.HP_Regen = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Disable_MP_Regen") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.MP_Regen = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.MP_Regen = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("DMG_To_DHP_Convertion") == 0){File0001 >> Temp0001 >> Config.DTDHP_Conv; if(Config.DTDHP_Conv < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("DMG_To_HP_Convertion") == 0){File0001 >> Temp0001 >> Config.DTHP_Conv; if(Config.DTHP_Conv < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("DMG_To_MP_Convertion") == 0){File0001 >> Temp0001 >> Config.DTMP_Conv; if(Config.DTMP_Conv < 0) goto Labl0002; continue;}
     
	 if(Temp0001.compare("Re-adjusted_Basic") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.ReAdj_Basic = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.ReAdj_Basic = false;} else {goto Labl0002;}} continue;}
     if(Temp0001.compare("Re-adjusted_Recieved_DMG") == 0){File0001 >> Temp0001 >> Config.ReAdj_RecDMG; continue;}
     if(Temp0001.compare("Re-adjusted_MP_Cost") == 0){File0001 >> Temp0001 >> Config.ReAdj_MP_Cost; continue;}
	 if(Temp0001.compare("Re-adjusted_Held") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.ReAdj_Held = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.ReAdj_Held = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Re-adjusted_Catch") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.ReAdj_Catch = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.ReAdj_Catch = false;} else {goto Labl0002;}} continue;}
     if(Temp0001.compare("Re-adjusted_Z-Prespective") == 0){File0001 >> Temp0001 >> Config.ReAdj_Pres; continue;}
	 if(Temp0001.compare("Re-adjusted_Speed") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.ReAdj_Speed = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.ReAdj_Speed = false;} else {goto Labl0002;}} continue;}
     if(Temp0001.compare("Re-adjusting_Speed_Method") == 0){File0001 >> Temp0001 >> Config.ReAding_Spd; if(Config.ReAding_Spd < 0) goto Labl0002; continue;}
     if(Temp0001.compare("Re-adjusted_Speed_Base") == 0){File0001 >> Temp0001 >> Config.ReAdj_Spd_Base; continue;}
     if(Temp0001.compare("Re-adjusted_Speed_Walk") == 0){File0001 >> Temp0001 >> Config.ReAdj_Spd_Walk; continue;}
     if(Temp0001.compare("Re-adjusted_Speed_Run") == 0){File0001 >> Temp0001 >> Config.ReAdj_Spd_Run; continue;}
     if(Temp0001.compare("Re-adjusted_Speed_Jump") == 0){File0001 >> Temp0001 >> Config.ReAdj_Spd_Jump; continue;}
     if(Temp0001.compare("Re-adjusted_Speed_JumpY") == 0){File0001 >> Temp0001 >> Config.ReAdj_Spd_JumpY; continue;}
     if(Temp0001.compare("Re-adjusted_Speed_JumpB") == 0){File0001 >> Temp0001 >> Config.ReAdj_Spd_JumpB; continue;}
     if(Temp0001.compare("Re-adjusted_Speed_Dash") == 0){File0001 >> Temp0001 >> Config.ReAdj_Spd_Dash; continue;}
     if(Temp0001.compare("Re-adjusted_Speed_DashY") == 0){File0001 >> Temp0001 >> Config.ReAdj_Spd_DashY; continue;}
     if(Temp0001.compare("Re-adjusted_Speed_DashB") == 0){File0001 >> Temp0001 >> Config.ReAdj_Spd_DashB; continue;}
     if(Temp0001.compare("Re-adjusted_Speed_Heavy") == 0){File0001 >> Temp0001 >> Config.ReAdj_Spd_Heavy; continue;}
     if(Temp0001.compare("Re-adjusted_Speed_FlipX") == 0){File0001 >> Temp0001 >> Config.ReAdj_Spd_FlipX; continue;}
     if(Temp0001.compare("Re-adjusted_Speed_FlipY") == 0){File0001 >> Temp0001 >> Config.ReAdj_Spd_FlipY; continue;}
     if(Temp0001.compare("Re-adjusted_Speed_Ratio") == 0){File0001 >> Temp0001 >> Config.ReAdj_Spd_Ratio; continue;}
	 if(Temp0001.compare("Re-adjusted_'bdy:'") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.ReAdj_bdy = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.ReAdj_bdy = false;} else {goto Labl0002;}} continue;}
     if(Temp0001.compare("Re-adjusting_'bdy:'_Method") == 0){File0001 >> Temp0001 >> Config.ReAding_bdy; if(Config.ReAding_bdy < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("Re-adjusted_'itr:'") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.ReAdj_itr = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.ReAdj_itr = false;} else {goto Labl0002;}} continue;}

     if(Temp0001.compare("Disable_Illegal_Input") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Dis_Il_Input = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Dis_Il_Input = false;} else {goto Labl0002;}} continue;}
     if(Temp0001.compare("Clean_Values") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Clean_Val = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Clean_Val = false;} else {goto Labl0002;}} continue;} 
     if(Temp0001.compare("Overlaying") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Overlaying = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Overlaying = false;} else {goto Labl0002;}} continue;}
     if(Temp0001.compare("Fix_Negative_Fall") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.Neg_Fall = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.Neg_Fall = false;} else {goto Labl0002;}} continue;}

     if(Temp0001.compare("Camera_Shift") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.C_Shift = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.C_Shift = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Camera_Smoothness") == 0){File0001 >> Temp0001 >> Temp0001; if(Temp0001.compare(Temp0002) == 0){Config.C_Smoothness = true;} else {if(Temp0001.compare(Temp0003) == 0){Config.C_Smoothness = false;} else {goto Labl0002;}} continue;}
	 if(Temp0001.compare("Camera_Effectiviness") == 0){File0001 >> Temp0001 >> Config.C_Effectiviness; if(Config.C_Effectiviness < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("Camera_Speed") == 0){File0001 >> Temp0001 >> Config.C_Speed; if(Config.C_Speed < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("Camera_Off") == 0){File0001 >> Temp0001 >> Config.C_Off; if(Config.C_Off < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("Camera_Sensitivity") == 0){File0001 >> Temp0001 >> Config.C_Sensitivity; if(Config.C_Sensitivity < 0) goto Labl0002; continue;}
	 if(Temp0001.compare("Camera_Size") == 0){File0001 >> Temp0001 >> Config.C_Size; if(Config.C_Size < 0) goto Labl0002; continue;}
	 
	 if(Temp0001.compare("Beta_Damage_Limiter") == 0){File0001 >> Temp0001 >> Config.Damage_Limiter; if(Config.Damage_Limiter < 0) goto Labl0002; continue;}

     if(Temp0001 != "" && Temp0001 != "\n" && (int32)Temp0001[0] != 13) goto Labl0002;
	}
    File0001.close();
    if(File0001.is_open()) File0001.close(); if(File0002.is_open()) File0002.close();
   } else {Labl0002: Vrab0003 = 0; File0002.open("configuration.txt"); File0002 << "//////////////////////////////////////////////////////////////////////////////////////////////////////\n//                                    Configuration of ddraw.dll                                    //\n//                                          " INJECTION_VERSION "                                          //\n//                                                                                                  //\n//                                       Modified by Mesujin.                                       //\n//                                  \"I may to modify this, right?\"                                  //\n//                                                                                                  //\n// Credits : Doix, Som1Lse, zort, and everyone else who have an effort in it.                       //\n// *If you modify the credit, the file will be overwritten :P.                                      //\n//////////////////////////////////////////////////////////////////////////////////////////////////////\n\n////\n// Notes;\n// - if the ddraw.dll fail to read the Value, this file will be overwritten without any warning.\n// - For the integer Values, it must be positive.\n// - \"//\" <-- this thing is used to give a comment, basically the same as \"#\" in LF2's Data.\n////\n\n// Main\n Determination, Active | Inactive // Determining the 'true' and 'false' in this file.\n Load_Other_DLL : Active          // Load other DLL(s)?\n DLL_Directory : add-on\\Libraries // 'Load_Other_DLL''s directory.\n AI_Directory : add-on\\AI         //\n AI_Debug_Console : Inactive      // A.k.a. Debug Version.\n AI_Debug_Console_Size : 80       //\n AI_Debug_Console_Style : 0       //\n Sleep_Mode : Inactive            // Disabling almost all feature of this DDraw except DLL Loader,\n                                  // 'Hidden_Mode', AI, Builder, and Installer.\n Hidden_Mode : Inactive           // IMPORTANT! Once this config active, this configuration will hide\n                                  // in \"" TEMPORAL_FILE "\". To stop the configuration from hiding,\n                                  // you'll need to delete it.\n Full_Injection : Active          // Modify all characters' in-game data to make the injection works\n                                  // finely. One empty frame is required in all type0 character.\n Notification_Post : 130          //\n Notification_Model : Inactive    // Dunno why i made this...\n Landing_Frame : 219              // Landing frame for 'Full_Injection'. In rare cases, you might need\n                                  // to change this into 0 (or starting frame) instead. (For example,\n                                  // Armored Julio, who won't goto frame219 at the beginning of game.)\n\n // Installation\n  Hidden_IDs : 50 - 59\n  Weapon_IDs : 100 - 199\n  Minion_IDs : 30 - 37\n  Minion_IDs_2 : 39 - 39\n  Available_IDs : 8 - 29\n  Available_IDs_2 : 60 - 99\n  Available_IDs_3 : 230 - 998\n  Debug : Active\n  Style : 255\n  Delay : 0\n  Build : add-on\\Build\n  Input : add-on\n  Output : add-on\\Out\n  Insight : data\\data.txt\n  Outsight : data\\data.temp\n  Overwrite : Inactive\n  Get_Mirrors : Inactive\n  Permanentness : Inactive\n  Separated_Files : Inactive\n  Key : !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\n\n  // Please do not questioning about these things, find what are these things used for, by yourself,\n  // if you wish to know.\n  // As for 'Permanentness', you might want change it into 'Active', bcs it'll make the ddraw.dll to\n  // not clean the installation once you close LF2.\n\n//-//\n\n// \"LF2 : TD\"\n 2D_Mode : Inactive               //\n Position : 0                     // 0 = Bottom; 1 = Top; 2 = Middle;\n Holdable_Defend : Inactive       //\n Holdable_Defend_TU : 4           // Base TU of 'Holdable_Defend', normally, it's 12.\n Minimum_'bdefend:' : 0           //\n 'bdefend:'_Effectivity : 100.00  // Calculated after 'Minimum_'bdefend:''.\n\n// \"LF2 : Skill-Out\"\n Disable_DHP : Inactive           // Enchanted \"drink\" included.\n Disable_MP : Inactive            //\n Milk_Amount : 3                  // Only effective when 'Disable_DHP' is 'Active'.\n Milk_Speed : 6                   // Only effective when 'Disable_DHP' is 'Active'.\n Tea_Amount : 3                   // Only effective when 'Disable_DHP' is 'Active'.\n Tea_Speed : 3                    // Only effective when 'Disable_DHP' is 'Active'.\n Base_Reserve : 0                 //\n Stage_Reserve : 0                // Additional reserve for Stage Mode.\n MP_Rest : Inactive               // Reset MP on resurrect?\n Immune_Time : 40                 // Immune time after resurrect.\n\n// \"LF2 : Vampirism\"\n Disable_HP_Regen : Inactive      //\n Disable_MP_Regen : Inactive      //\n DMG_To_DHP_Convertion : 0.00     // Percentage.\n DMG_To_HP_Convertion : 0.00      // Percentage.\n DMG_To_MP_Convertion : 0.00      // Percentage.\n\n// \"LF2 : Enhanced\"\n Re-adjusted_Basic : Inactive     // (Alot of things will be affected by this configuration.)\n Re-adjusted_Recieved_DMG : 50.00 // Percentage.\n Re-adjusted_MP_Cost : 200.00     // Percentage.\n Re-adjusted_Held : Inactive      // Reformat the way of helding weapon, and weapons' itself.\n Re-adjusted_Catch : Inactive     // In rare case, this configuration might not effective.\n Re-adjusted_Z-Prespective : 0.40 //\n Re-adjusted_Speed : Inactive     //\n Re-adjusting_Speed_Method : 0    // 0 = Based on total speed; 1 = Based on walking speed; 2 = Based\n                                  // on walking and running speed;\n Re-adjusted_Speed_Base : 100.00  // Percentage. \n Re-adjusted_Speed_Walk : 100.00  // Percentage. \n Re-adjusted_Speed_Run : 200.00   // Percentage. \n Re-adjusted_Speed_Jump : 150.00  // Percentage. \n Re-adjusted_Speed_JumpY : -0.10  // Percentage. \n Re-adjusted_Speed_JumpB : -16.00 // Base value of 'Re-adjusted_Speed_JumpY'.\n Re-adjusted_Speed_Dash : 250.00  // Percentage. \n Re-adjusted_Speed_DashY : -0.10  // Percentage. \n Re-adjusted_Speed_DashB : -10.00 // Base value of 'Re-adjusted_Speed_DashY'.\n Re-adjusted_Speed_Heavy : 80.00  // Percentage. Speed ratio when in heavy state.\n Re-adjusted_Speed_FlipX : 5.00   //\n Re-adjusted_Speed_FlipY : -2.00  //\n Re-adjusted_Speed_Ratio : 8.00   // 'frame_rate''s value's determining scale.\n Re-adjusted_'bdy:' : Inactive    // Reformat 'bdy:'(s)'s size determining according to LF2ET's DC-ing\n                                  // format.\n Re-adjusting_'bdy:'_Method : 0   // 0 = All 'bdy:'s; 1 = Injured frames only; 2 = Almost all 'bdy:'s\n                                  // except 'bdy:'(s) in \"fighting\" frames.\n Re-adjusted_'itr:' : Inactive    // Reformat 'itr:'(s) according to LF2ET's DC-ing format.\n\n// Etc\n // Et Cetera\n  Disable_Illegal_Input : Active  // Prevent COM from casting illegal input. KEEP THIS ONE 'Active'! :<\n  Clean_Values : Inactive         // Prevent HP, DHP, MP, etc in becoming negative.\n  Fix_Negative_Fall : Active      //\n\n // Z Camera Shift\n  Camera_Shift : Inactive         //\n  Camera_Smoothness : Active      // 'Active' = 'double'; 'Inactive' = 'int';\n  Camera_Effectiviness : 80.00    // The effectiviness of Y-Axis to the camera.\n  Camera_Speed : 100.00           // Percentage of the speed.\n  Camera_Sensitivity : 0          // Reaction time. I don't think this is useful at all.\n  Camera_Off : 385                // Position's off of the camera.\n  Camera_Size : 550               // The Y-Axis size of the camera.\n\n//-//\n \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; File0002.close(); goto Labl0001;}
   
   if(Vrab0003 != 0){if(Vrab0003 == 1){File0001.open(TEMPORAL_FILE, std::ios::in | std::ios::binary);} else {File0001.open("configuration.txt", std::ios::in | std::ios::binary);} Temp01.str(""); Temp01 << File0001.rdbuf(); Temp0001 = Temp01.str(); Config.Storing = Temp0001; if(File0001.is_open()) File0001.close(); if(File0002.is_open()) File0002.close(); std::remove(string("configuration.txt").c_str());} else {Config.Storing = "";} File0002.open(TEMPORAL_FILE, std::ios::out | std::ios::binary); File0002 << "Do not erase this file."; File0002.close();
   if(Exist(Config.Output + "\\summary.edb") || Exist(Config.Outsight)){if(Config.Permanentness){Config.Permanentness = false; Cleaning(); Config.Permanentness = true;} else {Cleaning();}}
  }
  int0 I_Building()
  {
   //////////////////////////
   if(Exist(Config.Build)) for(auto const &Vrab01 : std::filesystem::recursive_directory_iterator(Config.Build)){Temp0001 = Vrab01.path().string(); if(Temp0001[Config.Build.size()] == '#') continue; Vrab0002 = Temp0001.size(); if(Vrab0002 < 9) continue; Temp0001.erase(0, Vrab0002 - 9); if(Temp0001.compare("build.txt") == 0){Console.Log += ">< \"" + Vrab01.path().string() + "\" found.\n"; Console.PrintSet(); if(File0001.is_open()) File0001.close(); File0001.open(Vrab01.path(), std::ios::in | std::ios::binary); if(!File0001.is_open()) continue; InjectionDone = true; int8 Vrab04[95]; strcpy(Vrab04, Config.Key); strcpy(Config.Key, "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"); while(File0001){File0001 >> Temp0001; if(Temp0001.compare("<config>") == 0){while(File0001){File0001 >> Temp0001; if(Temp0001[0] == '#'){std::getline(File0001, Temp0001); continue;} if(Temp0001.compare("exclude_mirror:") == 0){File0001 >> Temp0001; if(Temp0001 == "true") InjectionDone = false; continue;} if(Temp0001.compare("out:") == 0){File0001 >> Temp0001; Vrab0003 = Temp0001.size() - 1; while(Temp0001[Vrab0003] != '\\' && (int32)Vrab0003 >= 0){Vrab0003 -= 1;} Temp0002 = Temp0001; if((int32)Vrab0003 >= 0) Temp0002.erase(0, Vrab0003); Vrab0003 = Temp0002.size() - 1; while(Temp0002[Vrab0003] != '.' && (int32)Vrab0003 >= 0){Vrab0003 -= 1;} if((int32)Vrab0003 >= 0) Temp0002.erase(Vrab0003, Temp0002.size() - 1); Vrab0003 = Temp0002.size(); while(Vrab0003 > 0){Vrab0003 -= 1; if(Temp0002[Vrab0003] == '_') Temp0002[Vrab0003] = ' ';} if(File0002.is_open()) File0002.close(); Console.Log += "[] Building \"" + Config.Output + "\\" + Temp0002 + ".ecd\".\n"; Console.PrintSet(); File0002.open(Execute(Config.Output + "\\" + Temp0002 + ".ecd"), std::ios::binary); File0002 << "# ======= Encrypted Character Data | By Mesujin ======= #\n"; continue;} if(Temp0001.compare("key:") == 0){File0001 >> Temp0001; if(Temp0001.length() != 94) continue; strcpy(Config.Key, Temp0001.c_str()); continue;} if(Temp0001.compare("<config_end>") == 0) goto Labl0017;} continue;}} continue; Labl0017: File0001.seekg(0, File0001.beg); std::vector < int32 > Vrab02; std::vector < uint32 > Vrab03; Vect0001.resize(0); while(File0001){File0001 >> Temp0001;if(Temp0001.compare("<data>") == 0){while(File0001){File0001 >> Temp0001; if(Temp0001[0] == '#'){std::getline(File0001, Temp0001); continue;} if(Temp0001.compare("id:") == 0){File0001 >> Vrab0002; Vect0001.push_back(Vrab0002); Vrab02.push_back(0); Vrab03.push_back(0); continue;} if(Temp0001.compare("type:") == 0){File0001 >> Vrab0002; Vrab02[Vect0001.size() - 1] = Vrab0002; continue;} if(Temp0001.compare("<data_end>") == 0) goto Labl0011;} continue;}} continue; Labl0011: File0001.close(); std::ifstream File01(Vrab01.path()); while(File01){File01 >> Temp0001; if(Temp0001.compare("<config>") == 0){while(File01){File01 >> Temp0001; if(Temp0001[0] == '#'){std::getline(File0001, Temp0001); continue;} if(Temp0001.compare("ai:") == 0){File01 >> Temp0001; if(string(Temp0001, Temp0001.size() - 3, 3) != ".as") continue; File0001.open(Temp0001, std::ios::in | std::ios::binary); Encryption(0, ""); continue;} if(Temp0001.compare("set:") == 0){Vrab0002 = Vrab03.size(); for(Vrab0003 = 0; Vrab0003 < Vrab0002; ++Vrab0003){File01 >> Vrab0001; Vrab03[Vrab0003] = (uint32)Vrab0001;} continue;} if(Temp0001.compare("<config_end>") == 0) goto Labl0012;} strcpy(Config.Key, Vrab04); continue;}} strcpy(Config.Key, Vrab04); continue; Labl0012: File01.seekg(0, File01.beg); Strn0001.resize(0); while(File01){File01 >> Temp0001; if(Temp0001.compare("<data>") == 0){Labl0013: while(File01){File01 >> Temp0001; if(Temp0001[0] == '#'){std::getline(File0001, Temp0001); continue;} if(Temp0001.compare("data:") == 0){File01 >> Temp0003; Vrab0002 = 0; Vrab0003 = Strn0001.size(); while(Vrab0002 < Vrab0003){if(Temp0003 == Strn0001[Vrab0002]) goto Labl0013; Vrab0002 += 1;} File0001.open(Temp0003); if(!File0001.is_open()) continue; Strn0001.push_back(Temp0003); Encryption(1, EncryptionUINT32(Strn0001.size() - 1)); continue;} if(Temp0001.compare("file:") == 0){File01 >> Temp0003; Vrab0002 = 0; Vrab0003 = Strn0001.size(); while(Vrab0002 < Vrab0003){if(Temp0003 == Strn0001[Vrab0002]) goto Labl0013; Vrab0002 += 1;} File0001.open(Temp0003, std::ios::in | std::ios::binary); if(!File0001.is_open()) continue; Strn0001.push_back(Temp0003); Vrab0002 = Temp0003.size() - 1; if(Temp0003[Vrab0002 - 3] == '.') if(Temp0003[Vrab0002 - 2] == 'd' || Temp0003[Vrab0002 - 2] == 'D') if(Temp0003[Vrab0002 - 1] == 'a' || Temp0003[Vrab0002 - 1] == 'A') if(Temp0003[Vrab0002] == 't' || Temp0003[Vrab0002] == 'T'){std::stringstream Ostr01; Ostr01 << File0001.rdbuf(); File0001.close(); Temp0001 = Ostr01.str(); Vrab0003 = 12; Vrab0004 = (xint64)(int32)Temp0001.size(); for(Vrab0002 = 123; Vrab0002 < (uint32)(int32)Vrab0004; ++Vrab0002){Temp0001[Vrab0002] -= string(ENCODING_KEY)[Vrab0003]; Vrab0003 += 1; if(Vrab0003 == string(ENCODING_KEY).size()) Vrab0003 = 0;} std::ofstream File02(Execute(TEMPORAL_FILE), std::ios::out | std::ios::binary); Console.Log += "[] Decrypting and encrypting \"" + Temp0003 + "\".\n"; Console.PrintSet(); Temp0001.erase(0, 123); File02 << Temp0001; File02.close(); Temp0003 = TEMPORAL_FILE; File0001.open(TEMPORAL_FILE, std::ios::in | std::ios::binary); Encryption(2, std::string(1, Config.Key[2]) + EncryptionUINT32(Strn0001.size() - 1)); continue;} if(Temp0003[Vrab0002 - 3] == '.') if(Temp0003[Vrab0002 - 2] == 't' || Temp0003[Vrab0002 - 2] == 'T') if(Temp0003[Vrab0002 - 1] == 'x' || Temp0003[Vrab0002 - 1] == 'X') if(Temp0003[Vrab0002] == 't' || Temp0003[Vrab0002] == 'T'){Console.Log += "[] Encrypting \"" + Temp0003 + "\".\n"; Console.PrintSet(); Encryption(2, std::string(1, Config.Key[2]) + EncryptionUINT32(Strn0001.size() - 1)); continue;} if(Temp0003[Vrab0002 - 3] == '.') if(Temp0003[Vrab0002 - 2] == 'b' || Temp0003[Vrab0002 - 2] == 'B') if(Temp0003[Vrab0002 - 1] == 'm' || Temp0003[Vrab0002 - 1] == 'M') if(Temp0003[Vrab0002] == 'p' || Temp0003[Vrab0002] == 'P'){Encryption(3, EncryptionUINT32(Strn0001.size() - 1)); continue;} Encryption(1, EncryptionUINT32(Strn0001.size() - 1)); continue;} if(Temp0001.compare("<data_end>") == 0) goto Labl0018;} strcpy(Config.Key, Vrab04); continue;}} strcpy(Config.Key, Vrab04); continue; Labl0018: strcpy(Config.Key, Vrab04); Vrab0001 = 0; Vrab0002 = 0; while((uint32)Vrab0001 < Vect0001.size()){File0002 << EncryptionUINT32((uint32)Vect0001[(uint32)Vrab0001]) << EncryptionUINT32((uint32)Vrab02[(uint32)Vrab0001]) << EncryptionUINT32(Vrab03[(uint32)Vrab0001]); Vrab0002 += 15; Vrab0001 += 1;} File0002 << EncryptionUINT32(Vrab0002); Vrab0001 = 0; Vrab0002 = 0; while((uint32)Vrab0001 < Strn0001.size()){File0002 << EncryptionUINT32((uint32)(Strn0001[(uint32)Vrab0001].size() - 1)) << EncryptionSTRING(Strn0001[(uint32)Vrab0001]); Vrab0002 += 5 + (uint32)(Strn0001[(uint32)Vrab0001].size()); Vrab0001 += 1;} File0002 << EncryptionUINT32(Vrab0002) << "\n# ===================================================== #"; File0002.close();}}
   //////////////////////////

   InjectionDone = false; Full_Injection_ID = -1; Full_Injection_ID2 = -1; Temp0001 = ""; Temp0002 = ""; Temp0003 = ""; if(File0001.is_open()) File0001.close(); if(File0002.is_open()) File0002.close();
  }
  int0 I_Installation()
  {
   std::vector < int1 > Vrab01; std::vector < int32 > Vrab02; std::vector < int32 > Vrab03; std::vector < string > Vrab04; Vrab01.resize(Config.IDs[9]);
   
   Labl0008:
   if(File0001.is_open()) File0001.close();
   File0001.open(Config.Insight);
   if(File0001.is_open())
   {
    while(File0001)
    {
     File0001 >> Temp0001;
     if(Temp0001.compare("<object>") == 0)
     {
      while(File0001)
      {
       File0001 >> Temp0001; if(Temp0001[0] == '#'){std::getline(File0001, Temp0001); continue;}
       if(Temp0001.compare("id:") == 0)
       {
        File0001 >> Vrab0001;
        if((uint32)Vrab0001 + 1 > Vrab01.size()) Vrab01.resize((uint32)Vrab0001 + 1);
        Vrab01[(uint32)Vrab0001] = true;
        continue;
       }
       if(Temp0001.compare("<object_end>") == 0) goto Labl0010;
      } goto Labl0009;
     }
    } goto Labl0009; Labl0010:
    File0001.close();
   } else {Labl0009: if(File0002.is_open()) File0002.close(); File0002.open(Execute(Config.Insight)); File0002 << "<object>\nid:  0  type: 0  file: data\\template.dat\nid:  52  type: 0  file: data\\julian.dat\nid:  51  type: 0  file: data\\firzen.dat\nid:  50  type: 0  file: data\\louisEX.dat\nid:  38  type: 0  file: data\\bat.dat\nid:  39  type: 0  file: data\\justin.dat\nid:  37  type: 0  file: data\\knight.dat\nid:  36  type: 0  file: data\\jan.dat\nid:  35  type: 0  file: data\\monk.dat\nid:  34  type: 0  file: data\\sorcerer.dat\nid:  33  type: 0  file: data\\jack.dat\nid:  32  type: 0  file: data\\mark.dat\nid:  31  type: 0  file: data\\hunter.dat\nid:  30  type: 0  file: data\\bandit.dat\nid:  1  type: 0  file: data\\deep.dat\nid:  2  type: 0  file: data\\john.dat\nid:  4  type: 0  file: data\\henry.dat\nid:  5  type: 0  file: data\\rudolf.dat\nid:  6  type: 0  file: data\\louis.dat\nid:  7  type: 0  file: data\\firen.dat\nid:  8  type: 0  file: data\\freeze.dat\nid:  9  type: 0  file: data\\dennis.dat\nid: 10  type: 0  file: data\\woody.dat\nid: 11  type: 0  file: data\\davis.dat\n\nid: 100  type: 1  file: data\\weapon0.dat   #stick\nid: 101  type: 1  file: data\\weapon2.dat   #hoe\nid: 120  type: 1  file: data\\weapon4.dat   #knife\nid: 121  type: 4  file: data\\weapon5.dat   #baseball\nid: 122  type: 6  file: data\\weapon6.dat   #milk\nid: 150  type: 2  file: data\\weapon1.dat   #stone\nid: 151  type: 2  file: data\\weapon3.dat   #wooden_box\nid: 123  type: 6  file: data\\weapon8.dat   #beer\nid: 124  type: 1  file: data\\weapon9.dat   #<\nid: 217  type: 2  file: data\\weapon10.dat  #louis_armour\nid: 218  type: 2  file: data\\weapon11.dat  #louis_armour\nid: 300  type: 5  file: data\\criminal.dat  #criminal\n\nid: 200  type: 3  file: data\\john_ball.dat\nid: 201  type: 1  file: data\\henry_arrow1.dat\nid: 202  type: 1  file: data\\rudolf_weapon.dat\nid: 203  type: 3  file: data\\deep_ball.dat\nid: 204  type: 3  file: data\\henry_wind.dat\nid: 205  type: 3  file: data\\dennis_ball.dat\nid: 206  type: 3  file: data\\woody_ball.dat\nid: 207  type: 3  file: data\\davis_ball.dat\nid: 208  type: 3  file: data\\henry_arrow2.dat\nid: 209  type: 3  file: data\\freeze_ball.dat\nid: 210  type: 3  file: data\\firen_ball.dat\nid: 211  type: 3  file: data\\firen_flame.dat\nid: 212  type: 3  file: data\\freeze_column.dat\nid: 213  type: 1  file: data\\weapon7.dat   #ice_sword\nid: 214  type: 3  file: data\\john_biscuit.dat\nid: 215  type: 3  file: data\\dennis_chase.dat\nid: 216  type: 3  file: data\\jack_ball.dat\nid: 219  type: 3  file: data\\jan_chaseh.dat\nid: 220  type: 3  file: data\\jan_chase.dat\nid: 221  type: 3  file: data\\firzen_chasef.dat\nid: 222  type: 3  file: data\\firzen_chasei.dat\nid: 223  type: 3  file: data\\firzen_ball.dat\nid: 224  type: 3  file: data\\bat_ball.dat\nid: 225  type: 3  file: data\\bat_chase.dat\nid: 226  type: 3  file: data\\justin_ball.dat\nid: 228  type: 3  file: data\\julian_ball.dat\nid: 229  type: 3  file: data\\julian_ball2.dat\n\nid: 998  type: 5  file: data\\etc.dat\nid: 999  type: 5  file: data\\broken_weapon.dat\n<object_end>\n\n<file_editing>\ndata\\nothing.txt\n<file_editing_end>\n\n<background>\nid: 4    file: bg\\sys\\hkc\\bg.dat\nid: 2    file: bg\\sys\\lf\\bg.dat\nid: 3    file: bg\\sys\\sp\\bg.dat\nid: 5    file: bg\\sys\\gw\\bg.dat\nid: 6    file: bg\\sys\\qi\\bg.dat\nid: 7    file: bg\\sys\\ft\\bg.dat\nid: 8    file: bg\\sys\\bc\\bg.dat\nid: 1    file: bg\\sys\\cuhk\\bg.dat\nid: 0    file: bg\\sys\\thv\\bg.dat\nid: 10    file: bg\\template\\1\\bg.dat\nid: 11    file: bg\\template\\2\\bg.dat\nid: 12    file: bg\\template\\3\\bg.dat\n<background_end>"; File0002.close(); goto Labl0008;}
  
   if(!Config.Sleep_Mode && Config.Full_Injection)
   {
    Vrab0001 = 0;
    for(Vrab0002 = (uint32)Config.IDs[0]; Vrab0002 <= (uint32)Config.IDs[1]; ++Vrab0002)
    {
     if(Vrab01.size() < Vrab0002 + 1) Vrab01.resize(Vrab0002 + 1);
     if(!Vrab01[Vrab0002]){Vrab01[Vrab0002] = true; Vrab0001 += 1; goto Labl0028;}
    }
    for(Vrab0002 = (uint32)Config.IDs[6]; Vrab0002 <= (uint32)Config.IDs[7]; ++Vrab0002)
    {
     if(Vrab01.size() < Vrab0002 + 1) Vrab01.resize(Vrab0002 + 1);
     if(!Vrab01[Vrab0002]){Vrab01[Vrab0002] = true; Vrab0001 += 1; goto Labl0028;}
    }
    for(Vrab0002 = (uint32)Config.IDs[8]; Vrab0002 <= (uint32)Config.IDs[9]; ++Vrab0002)
    {
     if(Vrab01.size() < Vrab0002 + 1) Vrab01.resize(Vrab0002 + 1);
     if(!Vrab01[Vrab0002]){Vrab01[Vrab0002] = true; Vrab0001 += 1; goto Labl0028;}
    }
    Labl0028: if(Vrab0001 >= 2) goto Labl0029;
    for(Vrab0002 = (uint32)Config.IDs[10]; Vrab0002 <= (uint32)Config.IDs[11]; ++Vrab0002)
    {
     if(Vrab01.size() < Vrab0002 + 1) Vrab01.resize(Vrab0002 + 1);
     if(!Vrab01[Vrab0002]){Vrab01[Vrab0002] = true; Vrab0001 += 1; goto Labl0028;}
    }
    for(Vrab0002 = 0; Vrab0002 <= 4294967295; ++Vrab0002)
    {
     if(Vrab01.size() < Vrab0002 + 1) Vrab01.resize(Vrab0002 + 1);
     if(!Vrab01[Vrab0002]){Vrab01[Vrab0002] = true; Vrab0001 += 1; goto Labl0028;}
    }
   }
   Labl0029:
   Temp0003 = ""; std::vector < uint32 > Vrab11;

   //////////////////////////
   std::filesystem::create_directories(Config.Output); if(Exist(Config.Input)) for(auto const &Vrab05 : std::filesystem::directory_iterator(Config.Input)){Vrab0001 = (int32)Vrab02.size(); Temp0001 = Vrab05.path().string(); Vrab0002 = Temp0001.size(); if(Temp0001[Vrab0002 - 4] == '.') if(Temp0001[Vrab0002 - 3] == 'e') if(Temp0001[Vrab0002 - 2] == 'c') if(Temp0001[Vrab0002 - 1] == 'd'){if(File0001.is_open()) File0001.close(); File0001.open(Temp0001, std::ios::in | std::ios::binary); if(!File0001.is_open()) continue; Console.PrintOut(); Console.Log += ">< \"" + Temp0001 + "\" found.\n"; Console.PrintOut(); File0001.seekg(0, File0001.end); File0001.seekg(File0001.tellg() - (std::streampos)58); Temp0002.resize(58); File0001.read(&Temp0002[0], 58); if(Temp0002 != "\n# ===================================================== #"){Console.Log += "[] ERROR : Unexpected end of \"" + Temp0001 + "\".\n"; Console.PrintOut(); continue;} File0001.seekg(File0001.tellg() - (std::streampos)63); std::streampos Post01 = File0001.tellg(); File0001 >> Temp0002; File0001.seekg(File0001.tellg() - (std::streampos)(DecryptionUINT32(Temp0002.c_str()) + 5)); Strn0001.resize(0); Console.Log += "[] Seeking file(s) inside \"" + Temp0001 + "\".\n"; Console.PrintOut(); while(File0001.tellg() < Post01){Temp0002.resize(5); File0001.read(&Temp0002[0], 5); Temp0002.resize(DecryptionUINT32(Temp0002.c_str()) + 1); File0001.read(&Temp0002[0], Temp0002.size()); Strn0001.push_back(DecryptionSTRING(Temp0002));} Console.Log += "[] " + std::to_string(Strn0001.size()) + " file(s) found.\n"; Console.PrintOut(); for(Vrab0002 = 0; Vrab0002 < Strn0001.size(); ++Vrab0002){Console.Log += "[] \"" + Strn0001[Vrab0002] + "\" located within.\n"; Console.PrintOut();} File0001 >> Temp0002; File0001.seekg(File0001.tellg() - (std::streampos)(DecryptionUINT32(Temp0002.c_str()) + 10)); Post01 = File0001.tellg(); Temp0002.resize(5); File0001.read(&Temp0002[0], 5); File0001.seekg(File0001.tellg() - (std::streampos)(DecryptionUINT32(Temp0002.c_str()) + 5)); Vect0001.resize(1); Vect0001[0] = 0; Console.Log += "[] Seeking object(s) inside \"" + Temp0001 + "\".\n"; Console.PrintOut(); while(File0001.tellg() < Post01){File0001.read(&Temp0002[0], 5); Vrab02.push_back(DecryptionINT32(Temp0002.c_str())); File0001.read(&Temp0002[0], 5); Vrab03.push_back(DecryptionINT32(Temp0002.c_str())); File0001.read(&Temp0002[0], 5); Vect0001.push_back(DecryptionINT32(Temp0002.c_str()));} Console.Log += "[] " + std::to_string(Vrab02.size() - (uint32)Vrab0001) + " object(s) found.\n"; Console.PrintOut(); for(Vrab0002 = (uint32)Vrab0001; Vrab0002 < Vrab02.size(); ++Vrab0002){Console.Log += "[] An object with (id: " + std::to_string(Vrab02[Vrab0002]) + " type: " + std::to_string(Vrab03[Vrab0002]) + " set: " + std::to_string(Vect0001[Vrab0002 - Vrab0001 + 1]) + "), located within.\n"; Console.PrintOut(); if(Vrab02[Vrab0002] > 999){Console.Log += "[] WARNING - Original Little Fighter 2 doesn't support ID which is higher than 999. (state: 8xxx as the example.)\n"; Console.PrintOut();} if((uint32)Vrab02[Vrab0002] + 1 > Vrab01.size()) Vrab01.resize((uint32)Vrab02[Vrab0002] + 1); if(Vrab01[(uint32)Vrab02[Vrab0002]]){Console.Log += "[] INFO - The ID of this object already exist or used"; if(Vect0001[Vrab0002 - Vrab0001 + 1] == 1){Console.Log += ", but exception is used for this object, this object won't be installed into the game.\n"; Console.PrintOut(); continue;} if(Vect0001[Vrab0002 - Vrab0001 + 1] == 2){Console.Log += ", but exception is used for this object, the objects before this object will be replaced with this object.\n"; if((uint32)Vrab02[Vrab0002] + 1 > Vrab11.size()) Vrab11.resize((uint32)Vrab02[Vrab0002] + 1); Vrab11[(uint32)Vrab02[Vrab0002]] += 1; Console.PrintOut(); continue;} Console.Log += ".\n"; Console.PrintOut(); if(Vrab02[Vrab0002] >= Config.IDs[12] && Vrab02[Vrab0002] <= Config.IDs[13]){Vrab0003 = 6;} else {if(Vrab02[Vrab0002] >= Config.IDs[0] && Vrab02[Vrab0002] <= Config.IDs[1]){Vrab0003 = 0;} else {if(Vrab02[Vrab0002] >= Config.IDs[2] && Vrab02[Vrab0002] <= Config.IDs[3]){Vrab0003 = 1;} else {if(Vrab02[Vrab0002] >= Config.IDs[4] && Vrab02[Vrab0002] <= Config.IDs[5]){Vrab0003 = 2;} else {if(Vrab02[Vrab0002] >= Config.IDs[6] && Vrab02[Vrab0002] <= Config.IDs[7]){Vrab0003 = 3;} else {if(Vrab02[Vrab0002] >= Config.IDs[8] && Vrab02[Vrab0002] <= Config.IDs[9]){Vrab0003 = 4;} else {if(Vrab02[Vrab0002] >= Config.IDs[10] && Vrab02[Vrab0002] <= Config.IDs[11]){Vrab0003 = 5;} else {Vrab0003 = 7;}}}}}}} Vrab02.push_back(Vrab02[Vrab0002]); switch(Vrab0003){case 1: Vrab0003 = (uint32)Config.IDs[2]; while(Vrab0003 <= (uint32)Config.IDs[3]){if(!Vrab01[Vrab0003]){Vrab02[Vrab0002] = Vrab0003; Vrab01[Vrab0003] = true; goto Labl0021;} Vrab0003 += 1;} case 2: Vrab0003 = (uint32)Config.IDs[4]; while(Vrab0003 <= (uint32)Config.IDs[5]){if(!Vrab01[Vrab0003]){Vrab02[Vrab0002] = Vrab0003; Vrab01[Vrab0003] = true; goto Labl0021;} Vrab0003 += 1;} case 0: Vrab0003 = (uint32)Config.IDs[0]; while(Vrab0003 <= (uint32)Config.IDs[1]){if(!Vrab01[Vrab0003]){Vrab02[Vrab0002] = Vrab0003; Vrab01[Vrab0003] = true; goto Labl0021;} Vrab0003 += 1;} case 3: Vrab0003 = (uint32)Config.IDs[6]; while(Vrab0003 <= (uint32)Config.IDs[7]){if(!Vrab01[Vrab0003]){Vrab02[Vrab0002] = Vrab0003; Vrab01[Vrab0003] = true; goto Labl0021;} Vrab0003 += 1;} case 4: Vrab0003 = (uint32)Config.IDs[8]; while(Vrab0003 <= (uint32)Config.IDs[9]){if(!Vrab01[Vrab0003]){Vrab02[Vrab0002] = Vrab0003; Vrab01[Vrab0003] = true; goto Labl0021;} Vrab0003 += 1;} case 5: Vrab0003 = (uint32)Config.IDs[10]; while(Vrab0003 <= (uint32)Config.IDs[11]){if(!Vrab01[Vrab0003]){Vrab02[Vrab0002] = Vrab0003; Vrab01[Vrab0003] = true; goto Labl0021;} Vrab0003 += 1;} case 6: Vrab0003 = (uint32)Config.IDs[12]; while(Vrab0003 <= (uint32)Config.IDs[13]){if(!Vrab01[Vrab0003]){Vrab02[Vrab0002] = Vrab0003; Vrab01[Vrab0003] = true; goto Labl0021;} Vrab0003 += 1;} default: Console.Log += "[] WARNING - The ID of this object is out of scope, please check your Configuration, or contact the builder of this Encrypted File.\n[] INFO - Forcing an ID for this object, a bug might occur in the game.\n"; Console.PrintOut(); Vrab0003 = 0; while(Vrab0003 < 4294967295){if(Vrab0003 > Vrab01.size() - 1) Vrab01.resize(Vrab0003 + 1); if(!Vrab01[Vrab0003]){Vrab02[Vrab0002] = (int32)Vrab0003; Vrab01[Vrab0003] = true; goto Labl0021;} Vrab0003 += 1;} break;} Labl0021: Vrab0003 = (uint32)Vrab02[Vrab02.size() - 1]; Vrab02.pop_back(); if(Vrab0003 != (uint32)Vrab02[Vrab0002]){Console.Log += "[] INFO - This object will be installed as ID " + std::to_string(Vrab02[Vrab0002]) + " instead.\n"; Console.PrintOut();} else {Console.Log += "[] ERROR - There are no more available IDs that can be used for this object. This object won't exist in the game.\n"; Console.PrintOut();}} else {Vrab01[Vrab02[Vrab0002]] = true;}} File0001.read(&Temp0002[0], 5); Post01 = File0001.tellg() - (std::streampos)(DecryptionUINT32(Temp0002.c_str()) + 5); File0001.seekg((std::streampos)58); while(File0001 && File0001.tellg() != Post01){Temp0002.resize(5); File0001.read(&Temp0002[0], 1); if(Temp0002[0] == Config.Key[0]){File0001.read(&Temp0002[0], 5); Vrab0002 = DecryptionUINT32(Temp0002.c_str()); File0001.read(&Temp0002[0], 5); Console.Log += "[] Extracting \"" + Config.AI + "\\" + std::to_string(Vrab02[(uint32)Vrab0001 + Vrab0002]) + ".as\""; if(!Config.Overwrite) if(Exist(Config.AI + "\\" + std::to_string(Vrab02[(uint32)Vrab0001 + Vrab0002]) + ".as")){Console.Log += "...\n[] INFO - \"" + Config.AI + "\\" + std::to_string(Vrab02[(uint32)Vrab0001 + Vrab0002]) + ".as\" not being parsed due to a file with same name already exist.\n"; Console.PrintOut(); File0001.seekg(File0001.tellg() + (std::streampos)DecryptionUINT32(Temp0002.c_str())); continue;} Console.Log += ".\n"; Console.PrintOut(); if(File0002.is_open()) File0002.close(); File0002.open(Execute(Config.AI + "\\" + std::to_string(Vrab02[(uint32)Vrab0001 + Vrab0002]) + ".as")); Temp0003 += Config.AI + "\\" + std::to_string(Vrab02[(uint32)Vrab0001 + Vrab0002]) + ".as\n"; Vrab0002 = DecryptionUINT32(Temp0002.c_str()); Temp0002.resize(Vrab0002); File0001.read(&Temp0002[0], Vrab0002); File0002 << DecryptionSTRING(Temp0002); File0002.close(); continue;} if(Temp0002[0] == Config.Key[1]){Labl0020: Temp0002.resize(5); File0001.read(&Temp0002[0], 5); Vrab0002 = DecryptionUINT32(Temp0002.c_str()); File0001.read(&Temp0002[0], 5); Console.Log += "[] Parsing \"" + Strn0001[Vrab0002] + "\""; if(!Config.Overwrite) if(Exist(Strn0001[Vrab0002])){Console.Log += "...\n[] INFO - \"" + Strn0001[Vrab0002] + "\" not being parsed due to a file with same name already exist.\n"; Console.PrintOut(); File0001.seekg(File0001.tellg() + (std::streampos)DecryptionUINT32(Temp0002.c_str())); continue;} if(Config.Build_Directory){Vrab0003 = Strn0001[Vrab0002].size() - 1; while(Strn0001[Vrab0002][Vrab0003] != '\\' && (int32)Vrab0003 >= 0) Vrab0003 -= 1; Strn0001[Vrab0002].erase(0, (int32)Vrab0003 + 1); Strn0001[Vrab0002].insert(0, Config.Output + "\\"); if(!Config.Overwrite) while(Exist(Strn0001[Vrab0002])) Rename(Strn0001[Vrab0002]); Console.Log += " as \"" + Strn0001[Vrab0002] + "\"";} Console.Log += ".\n"; Console.PrintOut(); if(File0002.is_open()) File0002.close(); File0002.open(Execute(Strn0001[Vrab0002]), std::ios::out | std::ios::binary); Temp0003 += Strn0001[Vrab0002] + "\n"; Vrab0002 = DecryptionUINT32(Temp0002.c_str()); Temp0002.resize(Vrab0002); File0001.read(&Temp0002[0], Vrab0002); File0002 << DecryptionSTRING(Temp0002); File0002.close(); continue;} if(Temp0002[0] == Config.Key[2]){Temp0002.resize(5); File0001.read(&Temp0002[0], 5); Vrab0002 = DecryptionUINT32(Temp0002.c_str()); File0001.read(&Temp0002[0], 5); Console.Log += "[] Decrypting \"" + Strn0001[Vrab0002] + "\""; if(!Config.Overwrite) if(Exist(Strn0001[Vrab0002])){Console.Log += "...\n[] INFO - \"" + Strn0001[Vrab0002] + "\" not being parsed due to a file with same name already exist.\n"; Console.PrintOut(); File0001.seekg(File0001.tellg() + (std::streampos)DecryptionUINT32(Temp0002.c_str())); continue;} if(Config.Build_Directory){Vrab0003 = Strn0001[Vrab0002].size() - 1; while(Strn0001[Vrab0002][Vrab0003] != '\\' && (int32)Vrab0003 >= 0) Vrab0003 -= 1; Strn0001[Vrab0002].erase(0, (int32)Vrab0003 + 1); Strn0001[Vrab0002].insert(0, Config.Output + "\\"); if(string(Strn0001[Vrab0002], Strn0001[Vrab0002].size() - 3, 3) == "dat"){Strn0001[Vrab0002].erase(Strn0001[Vrab0002].size() - 3, 3); Strn0001[Vrab0002] += "txt";} if(!Config.Overwrite) while(Exist(Strn0001[Vrab0002])) Rename(Strn0001[Vrab0002]); Console.Log += " as \"" + Strn0001[Vrab0002] + "\"";} else {if(string(Strn0001[Vrab0002], Strn0001[Vrab0002].size() - 3, 3) == "dat"){Strn0001[Vrab0002].erase(Strn0001[Vrab0002].size() - 3, 3); Strn0001[Vrab0002] += "txt"; Console.Log += " as \"" + Strn0001[Vrab0002] + "\"";}} Vrab04.push_back(Strn0001[Vrab0002]); Console.Log += ".\n"; Console.PrintOut(); if(File0002.is_open()) File0002.close(); File0002.open(Execute(Strn0001[Vrab0002]), std::ios::out | std::ios::binary); Temp0003 += Strn0001[Vrab0002] + "\n"; Vrab0002 = 0; Vrab0003 = DecryptionUINT32(Temp0002.c_str()); Temp0002.resize(Vrab0003); File0001.read(&Temp0002[0], Vrab0003); Temp0002 = DecryptionSTRING(Temp0002); Vrab0003 = 0; Vrab0004 = 0; while(Vrab0003 < Temp0002.size()){switch(Vrab0002){case 0: if(Temp0002[Vrab0003] == Config.Key[0]){Vrab0003 += 1; File0002 << "<bmp_begin> "; Vrab0002 = 1; continue;} if(Temp0002[Vrab0003] == Config.Key[1]){Vrab0003 += 1; File0002 << "<weapon_strength_list> "; Vrab0002 = 4; continue;} if(Temp0002[Vrab0003] == Config.Key[2]){Vrab0003 += 1; if(Vrab0004 == 0){File0002 << "<weapon_strength_list> entry: 1 G respond: " << Vect0001[Vect0001[0] + 1] << " <weapon_strength_list_end> "; Vrab0004 = 2;} File0002 << "<frame> "; Strn0001.push_back(string(Temp0002, Vrab0003, 5)); Vrab0003 += 5; File0002 << DecryptionUINT32(Strn0001[Strn0001.size() - 1].c_str()) << " G "; Strn0001.pop_back(); Vrab0002 = 7; continue;} break; case 1: if(Temp0002[Vrab0003] == Config.Key[0]){Vrab0003 += 1; File0002 << "<bmp_end> "; Vrab0002 = 0; continue;} if(Temp0002[Vrab0003] == Config.Key[1]){Vrab0003 += 1; File0002 << "name: "; Vrab0002 = DecryptionUINT32(string(Temp0002, Vrab0003, 5).c_str()); Vrab0003 += 5; File0002 << DecryptionSTRING(string(Temp0002, Vrab0003, Vrab0002).c_str()) + " "; Vrab0003 += Vrab0002; Vrab0002 = 1; continue;} if(Temp0002[Vrab0003] == Config.Key[2]){Vrab0003 += 1; File0002 << "head: " + Strn0001[DecryptionUINT32(string(Temp0002, Vrab0003, 5).c_str())] + " "; Vrab0003 += 5; continue;} if(Temp0002[Vrab0003] == Config.Key[3]){Vrab0003 += 1; File0002 << "small: " + Strn0001[DecryptionUINT32(string(Temp0002, Vrab0003, 5).c_str())] + " "; Vrab0003 += 5; continue;} if(Temp0002[Vrab0003] == Config.Key[4]){Vrab0003 += 1; File0002 << "file(0-0): " + Strn0001[DecryptionUINT32(string(Temp0002, Vrab0003, 5).c_str())] + " "; Vrab0003 += 5; continue;} if(Temp0002[Vrab0003] == Config.Key[5]){Vrab0003 += 1; File0002 << "w: "; Vrab0002 = 2; continue;} if(Temp0002[Vrab0003] == Config.Key[6]){Vrab0003 += 1; File0002 << "h: "; Vrab0002 = 2; continue;} if(Temp0002[Vrab0003] == Config.Key[7]){Vrab0003 += 1; File0002 << "row: "; Vrab0002 = 2; continue;} if(Temp0002[Vrab0003] == Config.Key[8]){Vrab0003 += 1; File0002 << "col: "; Vrab0002 = 2; continue;} if(Temp0002[Vrab0003] == Config.Key[9]){Vrab0003 += 1; File0002 << "walking_frame_rate "; Vrab0002 = 2; continue;} if(Temp0002[Vrab0003] == Config.Key[10]){Vrab0003 += 1; File0002 << "running_frame_rate "; Vrab0002 = 2; continue;} if(Temp0002[Vrab0003] == Config.Key[11]){Vrab0003 += 1; File0002 << "walking_speed "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[12]){Vrab0003 += 1; File0002 << "walking_speedz "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[13]){Vrab0003 += 1; File0002 << "running_speed "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[14]){Vrab0003 += 1; File0002 << "running_speedz "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[15]){Vrab0003 += 1; File0002 << "heavy_walking_speed "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[16]){Vrab0003 += 1; File0002 << "heavy_walking_speedz "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[17]){Vrab0003 += 1; File0002 << "heavy_running_speed "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[18]){Vrab0003 += 1; File0002 << "heavy_running_speedz "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[19]){Vrab0003 += 1; File0002 << "jump_height "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[20]){Vrab0003 += 1; File0002 << "jump_distance "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[21]){Vrab0003 += 1; File0002 << "jump_distancez "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[22]){Vrab0003 += 1; File0002 << "dash_height "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[23]){Vrab0003 += 1; File0002 << "dash_distance "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[24]){Vrab0003 += 1; File0002 << "dash_distancez "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[25]){Vrab0003 += 1; File0002 << "rowing_height "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[26]){Vrab0003 += 1; File0002 << "rowing_distance "; Vrab0002 = 3; continue;} if(Temp0002[Vrab0003] == Config.Key[27]){Vrab0003 += 1; File0002 << "weapon_hp: "; Vrab0002 = 2; continue;} if(Temp0002[Vrab0003] == Config.Key[28]){Vrab0003 += 1; File0002 << "weapon_drop_hurt: "; Vrab0002 = 2; continue;} if(Temp0002[Vrab0003] == Config.Key[29]){Vrab0003 += 1; File0002 << "weapon_hit_sound: " + Strn0001[DecryptionUINT32(string(Temp0002, Vrab0003, 5).c_str())] + " "; Vrab0003 += 5; continue;} if(Temp0002[Vrab0003] == Config.Key[30]){Vrab0003 += 1; File0002 << "weapon_drop_sound: " + Strn0001[DecryptionUINT32(string(Temp0002, Vrab0003, 5).c_str())] + " "; Vrab0003 += 5; continue;} if(Temp0002[Vrab0003] == Config.Key[31]){Vrab0003 += 1; File0002 << "weapon_broken_sound:" + Strn0001[DecryptionUINT32(string(Temp0002, Vrab0003, 5).c_str())] + " "; Vrab0003 += 5; continue;} break; case 2: File0002 << DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str()) << " "; Vrab0003 += 5; Vrab0002 = 1; continue; case 3: File0002 << DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str()) << "." << DecryptionUINT32(string(Temp0002, Vrab0003 + 5, 5).c_str()) << " "; Vrab0003 += 10; Vrab0002 = 1; continue; case 4: if(Temp0002[Vrab0003] == Config.Key[0]){Vrab0003 += 1; if(Vrab0004 == 0){File0002 << "entry: 1 G respond: " << Vect0001[Vect0001[0] + 1] << " "; Vrab0004 = 2;} File0002 << "<weapon_strength_list_end> "; Vrab0002 = 0; continue;} if(Temp0002[Vrab0003] == Config.Key[1]){Vrab0003 += 1; if(Vrab0004 == 1){File0002 << "respond: " << Vect0001[Vect0001[0] + 1] << " "; Vrab0004 = 2;} File0002 << "entry: "; Vrab0002 = 6; if(Vrab0004 == 0) Vrab0004 = 1; continue;} if(Temp0002[Vrab0003] == Config.Key[2]){Vrab0003 += 1; File0002 << "dvx: "; Vrab0002 = 5; continue;} if(Temp0002[Vrab0003] == Config.Key[3]){Vrab0003 += 1; File0002 << "dvy: "; Vrab0002 = 5; continue;} if(Temp0002[Vrab0003] == Config.Key[4]){Vrab0003 += 1; File0002 << "fall: "; Vrab0002 = 5; continue;} if(Temp0002[Vrab0003] == Config.Key[5]){Vrab0003 += 1; File0002 << "arest: "; Vrab0002 = 5; continue;} if(Temp0002[Vrab0003] == Config.Key[6]){Vrab0003 += 1; File0002 << "vrest: "; Vrab0002 = 5; continue;} if(Temp0002[Vrab0003] == Config.Key[7]){Vrab0003 += 1; File0002 << "respond: "; Vrab0002 = 5; continue;} if(Temp0002[Vrab0003] == Config.Key[8]){Vrab0003 += 1; File0002 << "effect: "; Vrab0002 = 5; continue;} if(Temp0002[Vrab0003] == Config.Key[9]){Vrab0003 += 1; File0002 << "bdefend: "; Vrab0002 = 5; continue;} if(Temp0002[Vrab0003] == Config.Key[10]){Vrab0003 += 1; File0002 << "injury: "; Vrab0002 = 5; continue;} if(Temp0002[Vrab0003] == Config.Key[11]){Vrab0003 += 1; File0002 << "zwidth: "; Vrab0002 = 5; continue;} break; case 5: File0002 << DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str()) << " "; Vrab0003 += 5; Vrab0002 = 4; continue; case 6: File0002 << DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str()) << " G "; Vrab0003 += 5; Vrab0002 = 4; continue; case 7: if(Temp0002[Vrab0003] == Config.Key[0]){Vrab0003 += 1; File0002 << "<frame_end> "; Vrab0002 = 0; continue;} if(Temp0002[Vrab0003] == Config.Key[1]){Vrab0003 += 1; File0002 << "pic: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[2]){Vrab0003 += 1; File0002 << "state: "; if(Temp0002[Vrab0003] == Config.Key[93]){Vrab0003 += 1; File0002 << std::to_string(Vrab02[Vrab0001 + DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str())] + 8000) + " "; Vrab0003 += 5;} else {Vrab0002 = 8;} continue;} if(Temp0002[Vrab0003] == Config.Key[3]){Vrab0003 += 1; File0002 << "wait: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[4]){Vrab0003 += 1; File0002 << "next: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[5]){Vrab0003 += 1; File0002 << "dvx: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[6]){Vrab0003 += 1; File0002 << "dvy: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[7]){Vrab0003 += 1; File0002 << "dvz: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[8]){Vrab0003 += 1; File0002 << "centerx: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[9]){Vrab0003 += 1; File0002 << "centery: "; if(Temp0002[Vrab0003] == Config.Key[93]){Vrab0003 += 1; Vrab0002 = DecryptionUINT32(string(Temp0002, Vrab0003 + 5, 5).c_str()); if((int32)Vrab0002 < 0){File0002 << "-"; Vrab0002 = (uint32)-(int32)Vrab0002;} File0002 << std::to_string((Vrab02[Vrab0001 + DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str())] * 1000000) + Vrab0002) + " "; Vrab0003 += 10; Vrab0002 = 7;} else {Vrab0002 = 8;} continue;} if(Temp0002[Vrab0003] == Config.Key[10]){Vrab0003 += 1; File0002 << "hit_a: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[11]){Vrab0003 += 1; File0002 << "hit_d: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[12]){Vrab0003 += 1; File0002 << "hit_j: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[13]){Vrab0003 += 1; File0002 << "hit_Fa: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[14]){Vrab0003 += 1; File0002 << "hit_Fj: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[15]){Vrab0003 += 1; File0002 << "hit_Da: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[16]){Vrab0003 += 1; File0002 << "hit_Dj: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[17]){Vrab0003 += 1; File0002 << "hit_Ua: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[18]){Vrab0003 += 1; File0002 << "hit_Uj: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[19]){Vrab0003 += 1; File0002 << "hit_ja: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[20]){Vrab0003 += 1; File0002 << "mp: "; Vrab0002 = 8; continue;} if(Temp0002[Vrab0003] == Config.Key[21]){Vrab0003 += 1; File0002 << "sound: " + Strn0001[DecryptionUINT32(string(Temp0002, Vrab0003, 5).c_str())] + " "; Vrab0003 += 5; continue;} if(Temp0002[Vrab0003] == Config.Key[22]){Vrab0003 += 1; File0002 << "bpoint: "; Vrab0002 = 9; continue;} if(Temp0002[Vrab0003] == Config.Key[23]){Vrab0003 += 1; File0002 << "cpoint: "; Vrab0002 = 11; continue;} if(Temp0002[Vrab0003] == Config.Key[24]){Vrab0003 += 1; File0002 << "wpoint: "; Vrab0002 = 13; continue;} if(Temp0002[Vrab0003] == Config.Key[25]){Vrab0003 += 1; File0002 << "opoint: "; Vrab0002 = 15; continue;} if(Temp0002[Vrab0003] == Config.Key[26]){Vrab0003 += 1; File0002 << "itr: "; Vrab0002 = 17; continue;} if(Temp0002[Vrab0003] == Config.Key[27]){Vrab0003 += 1; File0002 << "bdy: "; Vrab0002 = 19; continue;} break; case 8: File0002 << DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str()) << " "; Vrab0003 += 5; Vrab0002 = 7; continue; case 9: if(Temp0002[Vrab0003] == Config.Key[0]){Vrab0003 += 1; File0002 << "bpoint_end: "; Vrab0002 = 7; continue;} if(Temp0002[Vrab0003] == Config.Key[1]){Vrab0003 += 1; File0002 << "x: "; Vrab0002 = 10; continue;} if(Temp0002[Vrab0003] == Config.Key[2]){Vrab0003 += 1; File0002 << "y: "; Vrab0002 = 10; continue;} break; case 10: File0002 << DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str()) << " "; Vrab0003 += 5; Vrab0002 = 9; continue; case 11: if(Temp0002[Vrab0003] == Config.Key[0]){Vrab0003 += 1; File0002 << "cpoint_end: "; Vrab0002 = 7; continue;} if(Temp0002[Vrab0003] == Config.Key[1]){Vrab0003 += 1; File0002 << "kind: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[2]){Vrab0003 += 1; File0002 << "x: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[3]){Vrab0003 += 1; File0002 << "y: "; if(Temp0002[Vrab0003] == Config.Key[93]){Vrab0003 += 1; Vrab0002 = DecryptionUINT32(string(Temp0002, Vrab0003 + 5, 5).c_str()); if((int32)Vrab0002 < 0){File0002 << "-"; Vrab0002 = (uint32)-(int32)Vrab0002;} File0002 << std::to_string((Vrab02[Vrab0001 + DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str())] * 1000000) + Vrab0002) + " "; Vrab0003 += 10; Vrab0002 = 11;} else {Vrab0002 = 12;} continue;} if(Temp0002[Vrab0003] == Config.Key[4]){Vrab0003 += 1; File0002 << "vaction: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[5]){Vrab0003 += 1; File0002 << "aaction: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[6]){Vrab0003 += 6; continue;} if(Temp0002[Vrab0003] == Config.Key[7]){Vrab0003 += 1; File0002 << "jaction: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[8]){Vrab0003 += 1; File0002 << "taction: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[9]){Vrab0003 += 1; File0002 << "throwvx: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[10]){Vrab0003 += 1; File0002 << "throwvy: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[11]){Vrab0003 += 1; File0002 << "throwvz: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[12]){Vrab0003 += 1; File0002 << "throwinjury: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[13]){Vrab0003 += 1; File0002 << "dircontrol: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[14]){Vrab0003 += 1; File0002 << "decrease: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[15]){Vrab0003 += 1; File0002 << "hurtable: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[16]){Vrab0003 += 1; File0002 << "cover: "; Vrab0002 = 12; continue;} if(Temp0002[Vrab0003] == Config.Key[17]){Vrab0003 += 1; File0002 << "injury: "; Vrab0002 = 12; continue;} break; case 12: File0002 << DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str()) << " "; Vrab0003 += 5; Vrab0002 = 11; continue; case 13: if(Temp0002[Vrab0003] == Config.Key[0]){Vrab0003 += 1; File0002 << "wpoint_end: "; Vrab0002 = 7; continue;} if(Temp0002[Vrab0003] == Config.Key[1]){Vrab0003 += 1; File0002 << "kind: "; Vrab0002 = 14; continue;} if(Temp0002[Vrab0003] == Config.Key[2]){Vrab0003 += 1; File0002 << "x: "; Vrab0002 = 14; continue;} if(Temp0002[Vrab0003] == Config.Key[3]){Vrab0003 += 1; File0002 << "y: "; if(Temp0002[Vrab0003] == Config.Key[93]){Vrab0003 += 1; Vrab0002 = DecryptionUINT32(string(Temp0002, Vrab0003 + 5, 5).c_str()); if((int32)Vrab0002 < 0){File0002 << "-"; Vrab0002 = (uint32)-(int32)Vrab0002;} File0002 << std::to_string((Vrab02[Vrab0001 + DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str())] * 1000000) + Vrab0002) + " "; Vrab0003 += 10; Vrab0002 = 13;} else {Vrab0002 = 14;} continue;} if(Temp0002[Vrab0003] == Config.Key[4]){Vrab0003 += 1; File0002 << "weaponact: "; Vrab0002 = 14; continue;} if(Temp0002[Vrab0003] == Config.Key[5]){Vrab0003 += 1; File0002 << "attacking: "; Vrab0002 = 14; continue;} if(Temp0002[Vrab0003] == Config.Key[6]){Vrab0003 += 1; File0002 << "cover: "; Vrab0002 = 14; continue;} if(Temp0002[Vrab0003] == Config.Key[7]){Vrab0003 += 1; File0002 << "dvx: "; Vrab0002 = 14; continue;} if(Temp0002[Vrab0003] == Config.Key[8]){Vrab0003 += 1; File0002 << "dvy: "; Vrab0002 = 14; continue;} if(Temp0002[Vrab0003] == Config.Key[9]){Vrab0003 += 1; File0002 << "dvz: "; Vrab0002 = 14; continue;} break; case 14: File0002 << DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str()) << " "; Vrab0003 += 5; Vrab0002 = 13; continue; case 15: if(Temp0002[Vrab0003] == Config.Key[0]){Vrab0003 += 1; File0002 << "opoint_end: "; Vrab0002 = 7; continue;} if(Temp0002[Vrab0003] == Config.Key[1]){Vrab0003 += 1; File0002 << "kind: "; Vrab0002 = 16; continue;} if(Temp0002[Vrab0003] == Config.Key[2]){Vrab0003 += 1; File0002 << "x: "; Vrab0002 = 16; continue;} if(Temp0002[Vrab0003] == Config.Key[3]){Vrab0003 += 1; File0002 << "y: "; if(Temp0002[Vrab0003] == Config.Key[93]){Vrab0003 += 1; Vrab0002 = DecryptionUINT32(string(Temp0002, Vrab0003 + 5, 5).c_str()); if((int32)Vrab0002 < 0){File0002 << "-"; Vrab0002 = (uint32)-(int32)Vrab0002;} File0002 << std::to_string((Vrab02[Vrab0001 + DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str())] * 1000000) + Vrab0002) + " "; Vrab0003 += 10; Vrab0002 = 15;} else {Vrab0002 = 16;} continue;} if(Temp0002[Vrab0003] == Config.Key[4]){Vrab0003 += 1; File0002 << "oid: "; if(Temp0002[Vrab0003] == Config.Key[93]){Vrab0003 += 1; File0002 << std::to_string(Vrab02[Vrab0001 + DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str())]) + " "; Vrab0003 += 5;} else {Vrab0002 = 16;} continue;} if(Temp0002[Vrab0003] == Config.Key[5]){Vrab0003 += 1; File0002 << "action: "; Vrab0002 = 16; continue;} if(Temp0002[Vrab0003] == Config.Key[6]){Vrab0003 += 1; File0002 << "facing: "; Vrab0002 = 16; continue;} if(Temp0002[Vrab0003] == Config.Key[7]){Vrab0003 += 1; File0002 << "dvx: "; Vrab0002 = 16; continue;} if(Temp0002[Vrab0003] == Config.Key[8]){Vrab0003 += 1; File0002 << "dvy: "; Vrab0002 = 16; continue;} break; case 16: File0002 << DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str()) << " "; Vrab0003 += 5; Vrab0002 = 15; continue; case 17: if(Temp0002[Vrab0003] == Config.Key[0]){Vrab0003 += 1; File0002 << "itr_end: "; Vrab0002 = 7; continue;} if(Temp0002[Vrab0003] == Config.Key[1]){Vrab0003 += 1; File0002 << "kind: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[2]){Vrab0003 += 1; File0002 << "x: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[3]){Vrab0003 += 1; File0002 << "y: "; if(Temp0002[Vrab0003] == Config.Key[93]){Vrab0003 += 1; Vrab0002 = DecryptionUINT32(string(Temp0002, Vrab0003 + 5, 5).c_str()); if((int32)Vrab0002 < 0){File0002 << "-"; Vrab0002 = (uint32)-(int32)Vrab0002;} File0002 << std::to_string((Vrab02[Vrab0001 + DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str())] * 1000000) + Vrab0002) + " "; Vrab0003 += 10; Vrab0002 = 17;} else {Vrab0002 = 18;} continue;} if(Temp0002[Vrab0003] == Config.Key[4]){Vrab0003 += 1; File0002 << "w: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[5]){Vrab0003 += 1; File0002 << "h: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[6]){Vrab0003 += 1; File0002 << "zwidth: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[7]){Vrab0003 += 1; File0002 << "dvx: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[8]){Vrab0003 += 1; File0002 << "dvy: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[9]){Vrab0003 += 1; File0002 << "arest: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[10]){Vrab0003 += 1; File0002 << "vrest: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[11]){Vrab0003 += 1; File0002 << "bdefend: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[12]){Vrab0003 += 1; File0002 << "fall: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[13]){Vrab0003 += 1; File0002 << "injury: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[14]){Vrab0003 += 1; File0002 << "effect: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[15]){Vrab0003 += 1; File0002 << "respond: "; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[16]){Vrab0003 += 1; File0002 << "catchingact: "; File0002 << DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str()) << " "; Vrab0003 += 5; Vrab0002 = 18; continue;} if(Temp0002[Vrab0003] == Config.Key[17]){Vrab0003 += 1; File0002 << "caughtact: "; File0002 << DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str()) << " "; Vrab0003 += 5; Vrab0002 = 18; continue;} break; case 18: File0002 << DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str()) << " "; Vrab0003 += 5; Vrab0002 = 17; continue; case 19: if(Temp0002[Vrab0003] == Config.Key[0]){Vrab0003 += 1; File0002 << "bdy_end: "; Vrab0002 = 7; continue;} if(Temp0002[Vrab0003] == Config.Key[1]){Vrab0003 += 1; File0002 << "kind: "; Vrab0002 = 20; continue;} if(Temp0002[Vrab0003] == Config.Key[2]){Vrab0003 += 1; File0002 << "x: "; Vrab0002 = 20; continue;} if(Temp0002[Vrab0003] == Config.Key[3]){Vrab0003 += 1; File0002 << "y: "; if(Temp0002[Vrab0003] == Config.Key[93]){Vrab0003 += 1; Vrab0002 = DecryptionUINT32(string(Temp0002, Vrab0003 + 5, 5).c_str()); if((int32)Vrab0002 < 0){File0002 << "-"; Vrab0002 = (uint32)-(int32)Vrab0002;} File0002 << std::to_string((Vrab02[Vrab0001 + DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str())] * 1000000) + Vrab0002) + " "; Vrab0003 += 10; Vrab0002 = 19;} else {Vrab0002 = 20;} continue;} if(Temp0002[Vrab0003] == Config.Key[4]){Vrab0003 += 1; File0002 << "w: "; Vrab0002 = 20; continue;} if(Temp0002[Vrab0003] == Config.Key[5]){Vrab0003 += 1; File0002 << "h: "; Vrab0002 = 20; continue;} break; case 20: File0002 << DecryptionINT32(string(Temp0002, Vrab0003, 5).c_str()) << " "; Vrab0003 += 5; Vrab0002 = 19; continue; default: break;} break;} if(Vrab0004 == 0) File0002 << "<weapon_strength_list> entry: 1 G respond: " << Vect0001[Vect0001[0] + 1] << " <weapon_strength_list_end> "; Vect0001[0] += 1; File0001.seekg(File0001.tellg() + (std::streampos)(Temp0002.size() - Vrab0003)); Temp0002.resize(5); continue;} if(Temp0002[0] == Config.Key[3] || Temp0002[0] == Config.Key[5]){if(Temp0002[0] == Config.Key[3]){Vrab0004 = -1;} else {Vrab0004 = 0;} Temp0002.resize(5); File0001.read(&Temp0002[0], 5); Vrab0002 = DecryptionUINT32(Temp0002.c_str()); File0001.read(&Temp0002[0], 5); Console.Log += "[] Generating \"" + Strn0001[Vrab0002] + "\""; if(!Config.Overwrite) if(Exist(Strn0001[Vrab0002])){Console.Log += "...\n[] INFO - \"" + Strn0001[Vrab0002] + "\" not being generated due to a file with same name already exist.\n"; Console.PrintOut(); File0001.seekg(File0001.tellg() + (std::streampos)5); File0001.read(&Temp0002[0], 5); Vrab0002 = DecryptionUINT32(Temp0002.c_str()); while(Vrab0002 != 0){File0001.read(&Temp0002[0], 1); Vrab0002 -= 1; if(Temp0002[0] != Config.Key[93]) File0001.read(&Temp0002[1], 3);} continue;} if(Config.Build_Directory){Vrab0003 = Strn0001[Vrab0002].size() - 1; while(Strn0001[Vrab0002][Vrab0003] != '\\' && (int32)Vrab0003 >= 0) Vrab0003 -= 1; Strn0001[Vrab0002].erase(0, (int32)Vrab0003 + 1); Strn0001[Vrab0002].insert(0, Config.Output + "\\"); if(!Config.Overwrite) while(Exist(Strn0001[Vrab0002])) Rename(Strn0001[Vrab0002]); Console.Log += " as \"" + Strn0001[Vrab0002] + "\"";} int1 Vrab10 = Vrab0004 == -1 && Config.Get_Mirrors; if(Vrab10){Console.Log += ", and it's mirror";} Console.Log += ".\n"; Console.PrintOut(); Vrab0003 = DecryptionUINT32(Temp0002.c_str()); File0001.read(&Temp0002[0], 5); BMP Bitm01(Vrab0003, DecryptionUINT32(Temp0002.c_str()), false); Temp0003 += Strn0001[Vrab0002] + "\n"; BMP Bitm02(Vrab0003, Bitm01.bmp_info_header.height, false); uint32 Vrab06 = Vrab0003 * 3; uint32 Vrab07 = 0; uint32 Vrab08 = 0; uint32 Vrab09 = 0; if(Vrab10) if(Exist(string(Strn0001[Vrab0002], 0, Strn0001[Vrab0002].size() - 4) + "_mirror.bmp")){Vrab10 = false; Console.Log += "[] INFO - \"" + string(Strn0001[Vrab0002], 0, Strn0001[Vrab0002].size() - 4) + "_mirror.bmp\" not being generated due to a file with same name already exist.\n"; Console.PrintOut();} else {Temp0003 += string(Strn0001[Vrab0002], 0, Strn0001[Vrab0002].size() - 4) + "_mirror.bmp\n";} File0001.read(&Temp0002[0], 5); Vrab0003 = DecryptionUINT32(Temp0002.c_str()) * 3; Temp0002.resize(4); while(Vrab07 < Vrab0003){File0001.read(&Temp0002[0], 1); if(Temp0002[0] == Config.Key[93]){if(Vrab07 == 0){Bitm01.data[Vrab07] = 0; Bitm01.data[Vrab07 + 1] = 0; Bitm01.data[Vrab07 + 2] = 0; if(Vrab10){Vrab09 = Vrab06 - 3; Bitm02.data[Vrab09] = 0; Bitm02.data[Vrab09 + 1] = 0; Bitm02.data[Vrab09 + 2] = 0;}} else {Vrab08 = Vrab07 - 1; Vrab09 = Vrab08 - 1; Bitm01.data[Vrab07] = Bitm01.data[Vrab09 - 1]; Bitm01.data[Vrab07 + 1] = Bitm01.data[Vrab09]; Bitm01.data[Vrab07 + 2] = Bitm01.data[Vrab08]; if(Vrab10){Vrab09 = Vrab07 % Vrab06; Vrab09 = Vrab07 - Vrab09 + (Vrab06 - Vrab09) - 3; Bitm02.data[Vrab09] = Bitm01.data[Vrab07]; Bitm02.data[Vrab09 + 1] = Bitm01.data[Vrab07 + 1]; Bitm02.data[Vrab09 + 2] = Bitm01.data[Vrab07 + 2];}}} else {File0001.read(&Temp0002[1], 3); Vrab08 = DecryptionBMP(Temp0002.c_str()); Vrab09 = Vrab08 / 256; Bitm01.data[Vrab07] = (uint8)(Vrab08 % 256); Bitm01.data[Vrab07 + 1] = (uint8)(Vrab09 % 256); Bitm01.data[Vrab07 + 2] = (uint8)((Vrab09 / 256) % 256); if(Vrab10){Vrab09 = Vrab07 % Vrab06; Vrab09 = Vrab07 - Vrab09 + (Vrab06 - Vrab09) - 3; Bitm02.data[Vrab09] = Bitm01.data[Vrab07]; Bitm02.data[Vrab09 + 1] = Bitm01.data[Vrab07 + 1]; Bitm02.data[Vrab09 + 2] = Bitm01.data[Vrab07 + 2];}} Vrab07 += 3;} Temp0001.resize(5); Bitm01.write(Execute(Strn0001[Vrab0002]).c_str()); if(Vrab10) Bitm02.write(Execute(string(Strn0001[Vrab0002], 0, Strn0001[Vrab0002].size() - 4) + "_mirror.bmp").c_str()); continue;} if(Temp0002[0] == Config.Key[4]){File0001.seekg(File0001.tellg() + (std::streampos)1); if(Config.Get_Mirrors) goto Labl0020; Temp0002.resize(5); File0001.read(&Temp0002[0], 5); Console.Log += "[] INFO - \"" + Strn0001[DecryptionUINT32(Temp0002.c_str())] + "\" skipped, unsolicited.\n"; Console.PrintOut(); File0001.read(&Temp0002[0], 5); File0001.seekg(File0001.tellg() + (std::streampos)DecryptionUINT32(Temp0002.c_str())); continue;} break;}}}
   //////////////////////////
   
   if(File0001.is_open()) File0001.close();
   if(File0002.is_open()) File0002.close();

   File0001.open(Config.Insight, std::ios::in | std::ios::binary); if(!File0001.is_open())
   {
    Labl0022:
    File0002.open(Execute(Config.Insight), std::ios::out | std::ios::binary); File0002 << "<object>\n id: 0   type: 0 file: data\\template.dat\n id: 52  type: 0 file: data\\julian.dat\n id: 51  type: 0 file: data\\firzen.dat\n id: 50  type: 0 file: data\\louisEX.dat\n id: 38  type: 0 file: data\\bat.dat\n id: 39  type: 0 file: data\\justin.dat\n id: 37  type: 0 file: data\\knight.dat\n id: 36  type: 0 file: data\\jan.dat\n id: 35  type: 0 file: data\\monk.dat\n id: 34  type: 0 file: data\\sorcerer.dat\n id: 33  type: 0 file: data\\jack.dat\n id: 32  type: 0 file: data\\mark.dat\n id: 31  type: 0 file: data\\hunter.dat\n id: 30  type: 0 file: data\\bandit.dat\n id: 1   type: 0 file: data\\deep.dat\n id: 2   type: 0 file: data\\john.dat\n id: 4   type: 0 file: data\\henry.dat\n id: 5   type: 0 file: data\\rudolf.dat\n id: 6   type: 0 file: data\\louis.dat\n id: 7   type: 0 file: data\\firen.dat\n id: 8   type: 0 file: data\\freeze.dat\n id: 9   type: 0 file: data\\dennis.dat\n id: 10  type: 0 file: data\\woody.dat\n id: 11  type: 0 file: data\\davis.dat\n\n id: 100 type: 1 file: data\\weapon0.dat  #stick\n id: 101 type: 1 file: data\\weapon2.dat  #hoe\n id: 120 type: 1 file: data\\weapon4.dat  #knife\n id: 121 type: 4 file: data\\weapon5.dat  #baseball\n id: 122 type: 6 file: data\\weapon6.dat  #milk\n id: 150 type: 2 file: data\\weapon1.dat  #stone\n id: 151 type: 2 file: data\\weapon3.dat  #wooden_box\n id: 123 type: 6 file: data\\weapon8.dat  #beer\n id: 124 type: 1 file: data\\weapon9.dat  #<\n id: 217 type: 2 file: data\\weapon10.dat #louis_armour\n id: 218 type: 2 file: data\\weapon11.dat #louis_armour\n id: 300 type: 5 file: data\\criminal.dat #criminal\n\n id: 200 type: 3 file: data\\john_ball.dat\n id: 201 type: 1 file: data\\henry_arrow1.dat\n id: 202 type: 1 file: data\\rudolf_weapon.dat\n id: 203 type: 3 file: data\\deep_ball.dat\n id: 204 type: 3 file: data\\henry_wind.dat\n id: 205 type: 3 file: data\\dennis_ball.dat\n id: 206 type: 3 file: data\\woody_ball.dat\n id: 207 type: 3 file: data\\davis_ball.dat\n id: 208 type: 3 file: data\\henry_arrow2.dat\n id: 209 type: 3 file: data\\freeze_ball.dat\n id: 210 type: 3 file: data\\firen_ball.dat\n id: 211 type: 3 file: data\\firen_flame.dat\n id: 212 type: 3 file: data\\freeze_column.dat\n id: 213 type: 1 file: data\\weapon7.dat  #ice_sword\n id: 214 type: 3 file: data\\john_biscuit.dat\n id: 215 type: 3 file: data\\dennis_chase.dat\n id: 216 type: 3 file: data\\jack_ball.dat\n id: 219 type: 3 file: data\\jan_chaseh.dat\n id: 220 type: 3 file: data\\jan_chase.dat\n id: 221 type: 3 file: data\\firzen_chasef.dat\n id: 222 type: 3 file: data\\firzen_chasei.dat\n id: 223 type: 3 file: data\\firzen_ball.dat\n id: 224 type: 3 file: data\\bat_ball.dat\n id: 225 type: 3 file: data\\bat_chase.dat\n id: 226 type: 3 file: data\\justin_ball.dat\n id: 228 type: 3 file: data\\julian_ball.dat\n id: 229 type: 3 file: data\\julian_ball2.dat\n\n id: 998 type: 5 file: data\\etc.dat\n id: 999 type: 5 file: data\\broken_weapon.dat\n<object_end>\n\n<file_editing>\n data\\nothing.txt\n<file_editing_end>\n\n<background>\n id: 4  file: bg\\sys\\hkc\\bg.dat\n id: 2  file: bg\\sys\\lf\\bg.dat\n id: 3  file: bg\\sys\\sp\\bg.dat\n id: 5  file: bg\\sys\\gw\\bg.dat\n id: 6  file: bg\\sys\\qi\\bg.dat\n id: 7  file: bg\\sys\\ft\\bg.dat\n id: 8  file: bg\\sys\\bc\\bg.dat\n id: 1  file: bg\\sys\\cuhk\\bg.dat\n id: 0  file: bg\\sys\\thv\\bg.dat\n id: 10 file: bg\\template\\1\\bg.dat\n id: 11 file: bg\\template\\2\\bg.dat\n id: 12 file: bg\\template\\3\\bg.dat\n<background_end>";
    File0002.close(); if(File0001.is_open()) File0001.close(); File0001.open(Config.Insight, std::ios::in | std::ios::binary);
   }
   File0002.open(Execute(Config.Outsight), std::ios::out | std::ios::binary); File0002 << File0001.rdbuf(); File0002.close(); File0001.close();
   File0001.open(Config.Outsight, std::ios::in | std::ios::binary); File0002.open(Execute(Config.Insight), std::ios::out | std::ios::binary);

   Vrab01.clear();

   while(File0001)
   {
    File0001 >> Temp0001;
    if(Temp0001 == "<object>")
    {
     File0002 << Temp0001 + " ";
     while(File0001)
     {
      File0001 >> Temp0001; if(Temp0001[0] == '#'){std::getline(File0001, Temp0001); continue;}
      if(Temp0001 == "id:"){File0002 << Temp0001 + " "; File0001 >> Vrab0002; if(Vrab0002 + 1 > Vrab11.size()) Vrab11.resize(Vrab0002 + 1); if(Vrab11[Vrab0002] > 0){Vrab11[Vrab0002] -= 1; while(File0001){File0001 >> Temp0001; if(Temp0001[0] == '#'){std::getline(File0001, Temp0001); continue;} if(Temp0001 == "id:") goto Labl0027;} goto Labl0022; Labl0027: File0001 >> Vrab0002;} if(Vrab01.size() < Vrab0002 + 1) Vrab01.resize(Vrab0002 + 1); Vrab01[Vrab0002] = true; File0002 << Vrab0002 << " "; continue;}
      if(Temp0001 == "type:"){File0002 << Temp0001 + " "; File0001 >> Temp0001; File0002 << Temp0001 + " "; continue;}
      if(Temp0001 == "file:"){File0002 << Temp0001 + " "; File0001 >> Temp0001; File0002 << Temp0001 + " "; continue;}
      if(Temp0001 == "<object_end>") goto Labl0023;
     } goto Labl0022;
    }
   } goto Labl0022;
   Labl0023:

   Vect0001.clear(); Strn0001.clear(); if(!Config.Sleep_Mode && Config.Full_Injection)
   {
    Vect0001.resize(2); Vrab0001 = 0;
    for(Vrab0002 = (uint32)Config.IDs[0]; Vrab0002 <= (uint32)Config.IDs[1]; ++Vrab0002)
    {
     if(Vrab01.size() < Vrab0002 + 1) Vrab01.resize(Vrab0002 + 1);
     if(!Vrab01[Vrab0002]){Vrab01[Vrab0002] = true; Vect0001[(uint32)Vrab0001] = (int32)Vrab0002; Vrab0001 += 1; goto Labl0026;}
    }
    for(Vrab0002 = (uint32)Config.IDs[6]; Vrab0002 <= (uint32)Config.IDs[7]; ++Vrab0002)
    {
     if(Vrab01.size() < Vrab0002 + 1) Vrab01.resize(Vrab0002 + 1);
     if(!Vrab01[Vrab0002]){Vrab01[Vrab0002] = true; Vect0001[(uint32)Vrab0001] = (int32)Vrab0002; Vrab0001 += 1; goto Labl0026;}
    }
    for(Vrab0002 = (uint32)Config.IDs[8]; Vrab0002 <= (uint32)Config.IDs[9]; ++Vrab0002)
    {
     if(Vrab01.size() < Vrab0002 + 1) Vrab01.resize(Vrab0002 + 1);
     if(!Vrab01[Vrab0002]){Vrab01[Vrab0002] = true; Vect0001[(uint32)Vrab0001] = (int32)Vrab0002; Vrab0001 += 1; goto Labl0026;}
    }
    Labl0026: if(Vrab0001 >= 2) goto Labl0025;
    for(Vrab0002 = (uint32)Config.IDs[10]; Vrab0002 <= (uint32)Config.IDs[11]; ++Vrab0002)
    {
     if(Vrab01.size() < Vrab0002 + 1) Vrab01.resize(Vrab0002 + 1);
     if(!Vrab01[Vrab0002]){Vrab01[Vrab0002] = true; Vect0001[(uint32)Vrab0001] = (int32)Vrab0002; Vrab0001 += 1; goto Labl0026;}
    }
    for(Vrab0002 = 0; Vrab0002 <= 4294967295; ++Vrab0002)
    {
     if(Vrab01.size() < Vrab0002 + 1) Vrab01.resize(Vrab0002 + 1);
     if(!Vrab01[Vrab0002]){Vrab01[Vrab0002] = true; Vect0001[(uint32)Vrab0001] = (int32)Vrab0002; Vrab0001 += 1; goto Labl0026;}
    }
    Labl0025:
    Strn0001.push_back(Config.Output + "\\" + "injector.txt"); Strn0001.push_back(Config.Output + "\\" + "injector_disp.txt");
    while(Exist(Strn0001[0])) Rename(Strn0001[0]); while(Exist(Strn0001[1])) Rename(Strn0001[1]);
   }
   Vrab0003 = Vrab04.size();
   for(Vrab0002 = 0; Vrab0002 < Vrab0003; ++Vrab0002)
   {
    if(Vrab11[Vrab02[Vrab0002]] > 0){Vrab11[Vrab02[Vrab0002]] -= 1; continue;}
    if(!Vrab01[Vrab02[Vrab0002]]){File0002 << "id: " << Vrab02[Vrab0002] << " type: " << Vrab03[Vrab0002] << " file: " << Vrab04[Vrab0002] << " "; Vrab01[Vrab02[Vrab0002]] = true;}
   }
   if(!Config.Sleep_Mode && Config.Full_Injection){File0002 << "id: " << Vect0001[0] << " type: 0 file: " + Strn0001[0] + " id: " << Vect0001[1] << " type: 3 file: " + Strn0001[1] + " <object_end> ";} else
   {File0002 << "<object_end> ";}

   File0001.seekg(0, File0001.beg);
   while(File0001)
   {
    File0001 >> Temp0001;
    if(Temp0001 == "<background>")
    {
     File0002 << Temp0001 + " ";
     while(File0001)
     {
      File0001 >> Temp0001; if(Temp0001[0] == '#'){std::getline(File0001, Temp0001); continue;}
      if(Temp0001 == "id:"){File0002 << Temp0001 + " "; File0001 >> Temp0001; File0002 << Temp0001 + " "; continue;}
      if(Temp0001 == "file:"){File0002 << Temp0001 + " "; File0001 >> Temp0001; File0002 << Temp0001 + " "; continue;}
      if(Temp0001 == "<background_end>") goto Labl0024;
     } goto Labl0022;
    }
   } goto Labl0022;
   Labl0024:
   File0002 << Temp0001 + " ";

   if(Vect0001.size() == 2)
   {
    Strn0001.push_back(Config.Output + "\\" + "notification.bmp"); while(Exist(Strn0001[2])) Rename(Strn0001[2]); Strn0001.push_back(Config.Output + "\\" + "none.bmp"); while(Exist(Strn0001[3])) Rename(Strn0001[3]);
    BMP Bitm02(208, 70, false); uint8 Temp01[] = "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\377\377\377\376\377\377\377\377\377\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\377\377\377\376\377\377\377\377\377\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377" "\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377" "\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000";
    Bitm02.data.insert(Bitm02.data.begin(), &Temp01[0], &Temp01[43680]); Bitm02.data.resize(43680);
    if(Config.Model){for(Vrab0001 = 0; Vrab0001 < 208 * 70 * 3; Vrab0001 += 3) if(Bitm02.data[Vrab0001] == 254) if(Bitm02.data[Vrab0001 + 1] == 255) if(Bitm02.data[Vrab0001 + 2] == 255){Bitm02.data[Vrab0001] = 108; Bitm02.data[Vrab0001 + 1] = 32; Bitm02.data[Vrab0001 + 2] = 16;}} else
    {for(Vrab0001 = 0; Vrab0001 < 208 * 70 * 3; Vrab0001 += 3) if(Bitm02.data[Vrab0001] == 254) if(Bitm02.data[Vrab0001 + 1] == 255) if(Bitm02.data[Vrab0001 + 2] == 255){Bitm02.data[Vrab0001] = 0; Bitm02.data[Vrab0001 + 1] = 0; Bitm02.data[Vrab0001 + 2] = 0;}}
    Bitm02.write(Execute(Strn0001[2]).c_str()); Temp0003 += Strn0001[2] + "\n";
	Bitm02.bmp_info_header.width = 1; Bitm02.bmp_info_header.height = 1; Bitm02.data = {0, 0};
    Bitm02.write(Execute(Strn0001[3]).c_str()); Temp0003 += Strn0001[3] + "\n";

    if(File0002.is_open()) File0002.close(); File0002.open(Execute(Strn0001[0]), std::ios::out | std::ios::binary); Full_Injection_ID = Vect0001[0]; Full_Injection_ID2 = Vect0001[1];
    File0002 << "<bmp_begin>\nname: Injector\nhead: " + Strn0001[3] + "\nsmall: " + Strn0001[3] + "\nfile(0-0): " + Strn0001[3] + " w: 1 h: 1 row: 1 col: 1\n<bmp_end>\n\n<frame> 180 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 9999999\n<frame_end>\n<frame> 182 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 186 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 188 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 219 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 212 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 0 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 1 Injection\n pic: -1 wait: 1 state: 3005 next: 2 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 2 Injection\n pic: -1 state: 9998 next: 1000 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n\n<frame> 235 Injection\n pic: -1 state: 3005 next: 236 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 236 Injection\n pic: -1 state: 3005 next: 235 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 237 Injection\n pic: -1 state: 3005 wait: 2 next: 238 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 238 Injection\n pic: -1 state: 3005 next: 239 dvx: -2147483648 dvy: 550 dvz: 99999999\n opoint: kind: 1 x: 100 y: 0 action: 0 oid: " << Full_Injection_ID2 << " facing: 10 opoint_end:\n<frame_end>\n<frame> 239 Injection\n pic: -1 state: 3005 next: 235 dvx: -2147483648 dvy: 550 dvz: 99999999\n opoint: kind: 1 x: 100 y: 0 action: 1 oid: " << Full_Injection_ID2 << " facing: 10 opoint_end:\n<frame_end>";
    File0002.close(); Temp0003 += Strn0001[0] + "\n"; File0002.open(Execute(Strn0001[1]), std::ios::out | std::ios::binary);
    File0002 << "<bmp_begin>\nfile(0-1): " + Strn0001[2] + " w: 207 h: 34 row: 1 col: 2\n<bmp_end>\n\n<frame> 0 Injection\n pic: 0 state: 3005 wait: 121 next: 2 dvx: 550 dvy: 550 dvz: 99999999 centerx: 1000 centery: -1000\n<frame_end>\n<frame> 1 Injection\n pic: 1 state: 3005 wait: 140 next: 2 dvx: 550 dvy: 550 dvz: 9999999 centerx: 1000 centery: -1000\n<frame_end>\n\n<frame> 2 Injection\n pic: -1 state: 9998 next: 0 dvx: 550 dvy: 550 dvz: 9999999\n<frame_end>";
    File0002.close(); Temp0003 += Strn0001[1] + "\n"; File0002.open(Execute(Config.AI + "\\" + std::to_string(Full_Injection_ID) + ".as"), std::ios::out | std::ios::binary);
    File0002 << "void id(){return;}";
    File0002.close(); Temp0003 += Config.AI + "\\" + std::to_string(Full_Injection_ID) + ".as\n";
   }

   if(File0001.is_open()) File0001.close();
   if(File0002.is_open()) File0002.close();
   File0002.open(Execute(Config.Output + "\\summary.edb")); File0002 << Temp0003; File0002.close();
   Temp0001.clear(); Temp0002.clear(); Temp0003.clear(); Vect0001.clear(); Strn0001.clear();
   Vrab0001 = 0; Vrab0002 = 0; Vrab0003 = 0; Vrab0004 = 0;
  }
 //-//
 //Modifer Functions
  //Pragma Once
   int0 Once_FullInjection()
   {
    if(!Config.Full_Injection) return;
	int1 Vrab01 = false; Vrab0002 = 0;
    while(game->files->datas[Vrab0002] != 0)
    {
     if(game->files->datas[Vrab0002]->id == Full_Injection_ID) goto Labl0012;
     if(game->files->datas[Vrab0002]->type == 0)
     {
      Vrab0003 = 0;
      while(game->files->datas[Vrab0002]->frames[Vrab0003].exists){Vrab0003 += 1; if(Vrab0003 == MaximumFrames){Vrab01 = true; goto Labl0012;}}
      if(game->files->datas[Vrab0002]->frames[Config.LandingFrame].exists)
      {
       if(game->files->datas[Vrab0002]->frames[Config.LandingFrame].wait <= 0){Vrab01 = true; goto Labl0012;}
       game->files->datas[Vrab0002]->frames[Vrab0003].exists = true;
       game->files->datas[Vrab0002]->frames[Vrab0003].wait = game->files->datas[Vrab0002]->frames[Config.LandingFrame].wait - 1;
       game->files->datas[Vrab0002]->frames[Config.LandingFrame].wait = 0;
       game->files->datas[Vrab0002]->frames[Vrab0003].next = game->files->datas[Vrab0002]->frames[Config.LandingFrame].next;
       game->files->datas[Vrab0002]->frames[Config.LandingFrame].next = Vrab0003;
       game->files->datas[Vrab0002]->frames[Vrab0003].centerx = game->files->datas[Vrab0002]->frames[Config.LandingFrame].centerx;
       game->files->datas[Vrab0002]->frames[Vrab0003].centery = game->files->datas[Vrab0002]->frames[Config.LandingFrame].centery;
       game->files->datas[Vrab0002]->frames[Vrab0003].opoint.kind = 1;
       game->files->datas[Vrab0002]->frames[Vrab0003].opoint.x = game->files->datas[Vrab0002]->frames[Vrab0003].centerx;
       game->files->datas[Vrab0002]->frames[Vrab0003].opoint.y = game->files->datas[Vrab0002]->frames[Vrab0003].centery;
       game->files->datas[Vrab0002]->frames[Vrab0003].opoint.oid = Full_Injection_ID;
       game->files->datas[Vrab0002]->frames[Vrab0003].opoint.action = 0;
       game->files->datas[Vrab0002]->frames[Vrab0003].opoint.facing = 10;
       game->files->datas[Vrab0002]->frames[Vrab0003].pic = game->files->datas[Vrab0002]->frames[Config.LandingFrame].pic;
       game->files->datas[Vrab0002]->frames[Vrab0003].state = game->files->datas[Vrab0002]->frames[Config.LandingFrame].state;
       game->files->datas[Vrab0002]->frames[Vrab0003].mp = game->files->datas[Vrab0002]->frames[Config.LandingFrame].mp;
       game->files->datas[Vrab0002]->frames[Vrab0003].hit_a = game->files->datas[Vrab0002]->frames[Config.LandingFrame].hit_a;
       game->files->datas[Vrab0002]->frames[Vrab0003].hit_d = game->files->datas[Vrab0002]->frames[Config.LandingFrame].hit_d;
       game->files->datas[Vrab0002]->frames[Vrab0003].hit_j = game->files->datas[Vrab0002]->frames[Config.LandingFrame].hit_j;
       game->files->datas[Vrab0002]->frames[Vrab0003].hit_Fa = game->files->datas[Vrab0002]->frames[Config.LandingFrame].hit_Fa;
       game->files->datas[Vrab0002]->frames[Vrab0003].hit_Fj = game->files->datas[Vrab0002]->frames[Config.LandingFrame].hit_Fj;
       game->files->datas[Vrab0002]->frames[Vrab0003].hit_Da = game->files->datas[Vrab0002]->frames[Config.LandingFrame].hit_Da;
       game->files->datas[Vrab0002]->frames[Vrab0003].hit_Dj = game->files->datas[Vrab0002]->frames[Config.LandingFrame].hit_Dj;
       game->files->datas[Vrab0002]->frames[Vrab0003].hit_Ua = game->files->datas[Vrab0002]->frames[Config.LandingFrame].hit_Ua;
       game->files->datas[Vrab0002]->frames[Vrab0003].hit_Uj = game->files->datas[Vrab0002]->frames[Config.LandingFrame].hit_Uj;
       game->files->datas[Vrab0002]->frames[Vrab0003].hit_ja = game->files->datas[Vrab0002]->frames[Config.LandingFrame].hit_ja;
       game->files->datas[Vrab0002]->frames[Vrab0003].bdy_count = game->files->datas[Vrab0002]->frames[Config.LandingFrame].bdy_count;
       game->files->datas[Vrab0002]->frames[Vrab0003].bdys = game->files->datas[Vrab0002]->frames[Config.LandingFrame].bdys;
       game->files->datas[Vrab0002]->frames[Vrab0003].bdy_x = game->files->datas[Vrab0002]->frames[Config.LandingFrame].bdy_x;
       game->files->datas[Vrab0002]->frames[Vrab0003].bdy_y = game->files->datas[Vrab0002]->frames[Config.LandingFrame].bdy_y;
       game->files->datas[Vrab0002]->frames[Vrab0003].bdy_w = game->files->datas[Vrab0002]->frames[Config.LandingFrame].bdy_w;
       game->files->datas[Vrab0002]->frames[Vrab0003].bdy_h = game->files->datas[Vrab0002]->frames[Config.LandingFrame].bdy_h;
       game->files->datas[Vrab0002]->frames[Vrab0003].itr_count = game->files->datas[Vrab0002]->frames[Config.LandingFrame].itr_count;
       game->files->datas[Vrab0002]->frames[Vrab0003].itrs = game->files->datas[Vrab0002]->frames[Config.LandingFrame].itrs;
       game->files->datas[Vrab0002]->frames[Vrab0003].itr_x = game->files->datas[Vrab0002]->frames[Config.LandingFrame].itr_x;
       game->files->datas[Vrab0002]->frames[Vrab0003].itr_y = game->files->datas[Vrab0002]->frames[Config.LandingFrame].itr_y;
       game->files->datas[Vrab0002]->frames[Vrab0003].itr_w = game->files->datas[Vrab0002]->frames[Config.LandingFrame].itr_w;
       game->files->datas[Vrab0002]->frames[Vrab0003].itr_h = game->files->datas[Vrab0002]->frames[Config.LandingFrame].itr_h;
       game->files->datas[Vrab0002]->frames[Vrab0003].wpoint.kind = game->files->datas[Vrab0002]->frames[Config.LandingFrame].wpoint.kind;
       game->files->datas[Vrab0002]->frames[Vrab0003].wpoint.x = game->files->datas[Vrab0002]->frames[Config.LandingFrame].wpoint.x;
       game->files->datas[Vrab0002]->frames[Vrab0003].wpoint.y = game->files->datas[Vrab0002]->frames[Config.LandingFrame].wpoint.y;
       game->files->datas[Vrab0002]->frames[Vrab0003].wpoint.dvx = game->files->datas[Vrab0002]->frames[Config.LandingFrame].wpoint.dvx;
       game->files->datas[Vrab0002]->frames[Vrab0003].wpoint.dvy = game->files->datas[Vrab0002]->frames[Config.LandingFrame].wpoint.dvy;
       game->files->datas[Vrab0002]->frames[Vrab0003].wpoint.dvz = game->files->datas[Vrab0002]->frames[Config.LandingFrame].wpoint.dvz;
       game->files->datas[Vrab0002]->frames[Vrab0003].wpoint.weaponact = game->files->datas[Vrab0002]->frames[Config.LandingFrame].wpoint.weaponact;
       game->files->datas[Vrab0002]->frames[Vrab0003].wpoint.attacking = game->files->datas[Vrab0002]->frames[Config.LandingFrame].wpoint.attacking;
       game->files->datas[Vrab0002]->frames[Vrab0003].wpoint.cover = game->files->datas[Vrab0002]->frames[Config.LandingFrame].wpoint.cover;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.kind = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.kind;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.x = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.x;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.y = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.y;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.vaction = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.vaction;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.aaction = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.aaction;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.daction = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.daction;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.jaction = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.jaction;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.taction = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.taction;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.dircontrol = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.dircontrol;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.decrease = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.decrease;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.throwvx = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.throwvx;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.throwvy = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.throwvy;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.throwvz = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.throwvz;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.throwinjury = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.throwinjury;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.cover = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.cover;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.hurtable = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.hurtable;
       game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.injury = game->files->datas[Vrab0002]->frames[Config.LandingFrame].cpoint.injury;
       game->files->datas[Vrab0002]->frames[Vrab0003].bpoint.x = game->files->datas[Vrab0002]->frames[Config.LandingFrame].bpoint.x;
       game->files->datas[Vrab0002]->frames[Vrab0003].bpoint.y = game->files->datas[Vrab0002]->frames[Config.LandingFrame].bpoint.y;
      } else {Vrab01 = true;}
     }
     Labl0012:
	 Vrab0002 += 1;
    }
    if(Vrab01)
	{
	  
	}
   }
   int0 Once_EtCetera()
   {
    if(Config.Neg_Fall)
    {
     Vrab0002 = 0; while(game->files->datas[Vrab0002] != 0)
     {
      Vrab0003 = 0; while(Vrab0003 < MaximumFrames)
      {Vrab0001 = game->files->datas[Vrab0002]->frames[Vrab0003].itr_count - 1; while(Vrab0001 >= 0){switch(game->files->datas[Vrab0002]->frames[Vrab0003].itrs[Vrab0001].effect){case 2: case 20: case 21: case 22: game->files->datas[Vrab0002]->frames[Vrab0003].itrs[Vrab0001].fall = 999999999; break; default: break;} Vrab0001 -= 1;} Vrab0003 += 1;}
      Vrab0002 += 1;
     }
    }
   }
   int0 Once_CodedSpeciality()
   {
    std::vector < int1 > Vrab01; Vrab01.resize(1); Vrab0002 = 0; while(game->files->datas[Vrab0002] != 0)
    {
     switch((int32)(uint8)game->files->datas[Vrab0002]->unkwn2[144] + (int32)(uint8)game->files->datas[Vrab0002]->unkwn2[145] * 256 + (int32)(uint8)game->files->datas[Vrab0002]->unkwn2[146] * 65536  + (int32)(uint8)game->files->datas[Vrab0002]->unkwn2[147] * 16777216)
     {
      case -3: /*/ 2022 - Grandmaster v1.17.221004 /*/ if(Vrab01[0]) break; Vrab01[0] = true;
       Vrab0003 = 0; while(game->files->datas[Vrab0003] != 0)
       {
        switch(game->files->datas[Vrab0003]->id)
        {
         case 209:
          Vrab0001 = 0; while(game->files->datas[Vrab0003]->frames[Vrab0001].exists || Vrab0001 % 10 == 0 || Vrab0001 == 202 || Vrab0001 == 212) Vrab0001 += 1;
          Vrab0004 = 0; while((uint32)(int32)Vrab0004 < MaximumFrames)
          {
           if(game->files->datas[Vrab0003]->frames[(int32)Vrab0004].exists)
           if(Positive(game->files->datas[Vrab0003]->frames[(int32)Vrab0004].next) == 31)
           if(game->files->datas[Vrab0003]->frames[(int32)Vrab0004].next > 0){game->files->datas[Vrab0003]->frames[(int32)Vrab0004].next = Vrab0001;} else {game->files->datas[Vrab0003]->frames[(int32)Vrab0004].next = -Vrab0001;}
           Vrab0004 += 1;
          }
          FrameCopy(Vrab0003, 31, (uint32)Vrab0001);
          FrameCopy(Vrab0003, 30, 31);
         break; default: break;
        }
        Vrab0003 += 1;
       }
       Vrab0003 = 0; while(game->files->datas[Vrab0003] != 0)
       {
        switch(game->files->datas[Vrab0003]->id)
        {
         case 200: case 203: case 205: case 206: case 207: case 215: case 216:
          Vrab0001 = 0; while(game->files->datas[Vrab0003]->frames[Vrab0001].exists || Vrab0001 % 10 == 0 || Vrab0001 == 202 || Vrab0001 == 212) Vrab0001 += 1;
          if(Vrab0001 >= MaximumFrames){ break;}
          FrameCopy(Vrab0003, 30, (uint32)Vrab0001);
          game->files->datas[Vrab0003]->frames[(uint32)Vrab0001].dvx = 550;
          game->files->datas[Vrab0003]->frames[(uint32)Vrab0001].dvy = 550;
          game->files->datas[Vrab0003]->frames[(uint32)Vrab0001].dvz = 550;
          game->files->datas[Vrab0003]->frames[(uint32)Vrab0001].state = 8209;
          game->files->datas[Vrab0003]->unkwn2[224] = (int8)(Vrab0001 % 256);
          game->files->datas[Vrab0003]->unkwn2[225] = (int8)((Vrab0001 / 256) % 256);
         break; default: break;
        }
        Vrab0003 += 1;
       }
      break;
      default: break;
     }
     Vrab0002 += 1;
    }
   }
   int0 Once_PackSkillOut()
   {
    if(!Config.Dis_DHP) return;
    Vrab0002 = 0;
	while(game->files->datas[Vrab0002] != 0)
    {
     if(game->files->datas[Vrab0002]->type == 0)
     {
      for(Vrab0003 = 0; Vrab0003 < MaximumFrames; ++Vrab0003) if(game->files->datas[Vrab0002]->frames[Vrab0003].exists) if(game->files->datas[Vrab0002]->frames[Vrab0003].state == 17) game->files->datas[Vrab0002]->frames[Vrab0003].state = 69696969;
     }
     Vrab0002 += 1;
    }
   }
   int0 Once_PackTDMode()
   {
    if(Config.TD_Mode)
    {
     Vrab0002 = 0;
     while(game->files->datas[Vrab0002] != 0)
     {
      if(game->files->datas[Vrab0002]->id != Full_Injection_ID && game->files->datas[Vrab0002]->id != Full_Injection_ID2) switch(game->files->datas[Vrab0002]->type)
      {
       case 0: case 5:
        game->files->datas[Vrab0002]->walking_speedz = 0;
        game->files->datas[Vrab0002]->running_speedz = 0;
        game->files->datas[Vrab0002]->heavy_walking_speedz = 0;
        game->files->datas[Vrab0002]->heavy_running_speedz = 0;
        game->files->datas[Vrab0002]->jump_distancez = 0;
        game->files->datas[Vrab0002]->dash_distancez = 0;
        Vrab0003 = 0;
        while(Vrab0003 < MaximumFrames)
        {
         if(game->files->datas[Vrab0002]->frames[Vrab0003].exists)
         {
          game->files->datas[Vrab0002]->frames[Vrab0003].dvz = 550;
          game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.throwvz = 0;
          game->files->datas[Vrab0002]->frames[Vrab0003].wpoint.dvz = 0;
         }
         Vrab0003 += 1;
        }
       break;
       default:
        Vrab0003 = 0;
        while(Vrab0003 < MaximumFrames)
        {
         if(game->files->datas[Vrab0002]->frames[Vrab0003].exists)
         {
          game->files->datas[Vrab0002]->frames[Vrab0003].dvz = 550;
          if(game->files->datas[Vrab0002]->frames[Vrab0003].hit_j != 50) game->files->datas[Vrab0002]->frames[Vrab0003].hit_j = 0;
          game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.throwvz = 0;
          game->files->datas[Vrab0002]->frames[Vrab0003].wpoint.dvz = 0;
         }
         Vrab0003 += 1;
        }
       break;
      }
      Vrab0002 += 1;
     }
    }
    //Min_Bdef & Bdef_E
     if(Config.Min_Bdef > 0 || Config.Bdef_E != 100)
     {
      Vrab0002 = 0;
	  while(game->files->datas[Vrab0002] != 0)
      {
       for(Vrab0003 = 0; Vrab0003 < MaximumFrames; ++Vrab0003)
       {
        if(game->files->datas[Vrab0002]->frames[Vrab0003].exists) for(Vrab0001 = 0; Vrab0001 < game->files->datas[Vrab0002]->frames[Vrab0003].itr_count; ++Vrab0001)
        {
         if(game->files->datas[Vrab0002]->frames[Vrab0003].itrs[Vrab0001].bdefend < Config.Min_Bdef) game->files->datas[Vrab0002]->frames[Vrab0003].itrs[Vrab0001].bdefend = 0;
         game->files->datas[Vrab0002]->frames[Vrab0003].itrs[Vrab0001].bdefend = Rounding((xint64)game->files->datas[Vrab0002]->frames[Vrab0003].itrs[Vrab0001].bdefend * Config.Bdef_E * 0.01);
        }
       }
       Vrab0002 += 1;
      }
     }
    //-//
    //Hold_B_Def
     if(Config.Hold_Def)
     {
      Vrab0002 = 0;
	  while(game->files->datas[Vrab0002] != 0)
      {
       for(Vrab0003 = 0; Vrab0003 < MaximumFrames; ++Vrab0003) if(game->files->datas[Vrab0002]->frames[Vrab0003].exists) game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.daction = 0;
       Vrab0003 = 110;
       while(Vrab0003 != 999)
       {
        if(game->files->datas[Vrab0002]->frames[Vrab0003].state == 0 || game->files->datas[Vrab0002]->frames[Vrab0003].state == 1) break;
        if(!game->files->datas[Vrab0002]->frames[Vrab0003].exists) break;
        if(game->files->datas[Vrab0002]->frames[Vrab0003].state == 7){game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.daction = 1;} else {game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.daction = 2;}
        if(game->files->datas[Vrab0002]->frames[Vrab0003].cpoint.daction != 0) break;
        if(game->files->datas[Vrab0002]->frames[Vrab0003].next == 0) break;
        Vrab0003 = game->files->datas[Vrab0002]->frames[Vrab0003].next;
       }
       Vrab0002 += 1;
      }
     }
    //-//
   }
  //-//
  //Pragma Peat
   int0 Peat_FullInjection()
   {
    if(Config.Full_Injection)
    {
     for(Vrab0002 = 0; Vrab0002 < MaximumObject; ++Vrab0002) if(game->objects[Vrab0002]->data->id == Full_Injection_ID2)
     {
      switch(game->objects[Vrab0002]->frame1)
      {
       case 0:
        Vrab0001 = 20;
        if(game->objects[Vrab0002]->wait_counter > 1)
        if(game->objects[Vrab0002]->wait_counter < 22)
        {
         Vrab0001 = 20 - (game->objects[Vrab0002]->wait_counter - 2);
        } else 
        {
         Vrab0001 = 0;
         if(game->objects[Vrab0002]->wait_counter > 97) Vrab0001 = game->objects[Vrab0002]->wait_counter - 97;
        }
        Vrab0003 = 20;
        if(game->objects[Vrab0002]->wait_counter > 13) Vrab0003 = 20 - (game->objects[Vrab0002]->wait_counter - 13);
        if(game->objects[Vrab0002]->wait_counter > 33) Vrab0003 = 0;
        game->objects[Vrab0002]->data->frames[0].centerx = (Vrab0001 * (Vrab0001 + ((Vrab0001 - 1) / -2))) - *(int*)0x450bc4;
        game->objects[Vrab0002]->data->frames[0].centery = game->files->backgrounds[*(int*)0x44d024].bg_zwidth2 - Config.Not_Post - (210 - ((int32)Vrab0003 * ((int32)Vrab0003 + (((int32)Vrab0003 - 1) / -2)))) / 5;
       break;
       case 1:
        if(game->objects[Vrab0002]->data->frames[0].pic == -1)
        {
         Vrab0001 = 20;
         if(game->objects[Vrab0002]->wait_counter > 0)
         if(game->objects[Vrab0002]->wait_counter < 21)
         {
          Vrab0001 = 20 - (game->objects[Vrab0002]->wait_counter - 1);
         } else 
         {
          Vrab0001 = 0;
          if(game->objects[Vrab0002]->wait_counter > 96) Vrab0001 = game->objects[Vrab0002]->wait_counter - 96;
         }
         game->objects[Vrab0002]->data->frames[1].centerx = (Vrab0001 * (Vrab0001 + ((Vrab0001 - 1) / -2))) - *(int*)0x450bc4;
         game->objects[Vrab0002]->data->frames[1].centery = game->files->backgrounds[*(int*)0x44d024].bg_zwidth2 - Config.Not_Post;
        } else
        {
         Vrab0001 = 20;
         if(game->objects[Vrab0002]->wait_counter > 20)
         if(game->objects[Vrab0002]->wait_counter < 41)
         {
          Vrab0001 = 20 - (game->objects[Vrab0002]->wait_counter - 21);
         } else 
         {
          Vrab0001 = 0;
          if(game->objects[Vrab0002]->wait_counter > 116) Vrab0001 = game->objects[Vrab0002]->wait_counter - 116;
         }
         game->objects[Vrab0002]->data->frames[1].centerx = (Vrab0001 * (Vrab0001 + ((Vrab0001 - 1) / -2))) - *(int*)0x450bc4;
         game->objects[Vrab0002]->data->frames[1].centery = game->files->backgrounds[*(int*)0x44d024].bg_zwidth2 - Config.Not_Post;
        }
       break;
       default: break;
      }
     }
    }
   }
   int0 Peat_CodedSpeciality()
   {
    for(Vrab0002 = 0; Vrab0002 < NumberOfExist; ++Vrab0002) switch((int32)(uint8)game->objects[Database_Exist[Vrab0002]]->data->unkwn2[144] + (int32)(uint8)game->objects[Database_Exist[Vrab0002]]->data->unkwn2[145] * 256 + (int32)(uint8)game->objects[Database_Exist[Vrab0002]]->data->unkwn2[146] * 65536 + (int32)(uint8)game->objects[Database_Exist[Vrab0002]]->data->unkwn2[147] * 16777216)
    {
     case -1: /*/ 2022 - Grandmaster v1.00.220930 /*/ if(game->objects[Database_Exist[Vrab0002]]->frame1 == 255 || game->objects[Database_Exist[Vrab0002]]->frame1 == 256) if(game->objects[Database_Exist[Vrab0002]]->mp > 5){game->objects[Database_Exist[Vrab0002]]->mp -= 5;} else {game->objects[Database_Exist[Vrab0002]]->frame1 += 2;} if((game->objects[Database_Exist[Vrab0002]]->frame1 >= 252 && game->objects[Database_Exist[Vrab0002]]->frame1 <= 258) || (game->objects[Database_Exist[Vrab0002]]->frame1 >= 269 && game->objects[Database_Exist[Vrab0002]]->frame1 <= 278)){game->objects[Database_Exist[Vrab0002]]->fall = -99999999; game->objects[Database_Exist[Vrab0002]]->shake = 0; if(game->objects[Database_Exist[Vrab0002]]->x_velocity != 0) game->objects[Database_Exist[Vrab0002]]->x_velocity /= 2; if(game->objects[Database_Exist[Vrab0002]]->z_velocity != 0) game->objects[Database_Exist[Vrab0002]]->z_velocity /= 2;} else {if(game->objects[Database_Exist[Vrab0002]]->frame1 >= 288 && game->objects[Database_Exist[Vrab0002]]->frame1 <= 301){game->objects[Database_Exist[Vrab0002]]->fall = -99999999; game->objects[Database_Exist[Vrab0002]]->shake = 0; if(game->objects[Database_Exist[Vrab0002]]->frame1 >= 290 && game->objects[Database_Exist[Vrab0002]]->frame1 <= 292) if(game->objects[Database_Exist[Vrab0002]]->mp <= 5){game->objects[Database_Exist[Vrab0002]]->frame1 = 300; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0; game->objects[Database_Exist[Vrab0002]]->mp = 1;}} else {if(game->objects[Database_Exist[Vrab0002]]->fall <= -9999999) game->objects[Database_Exist[Vrab0002]]->fall = 0;}} if(game->objects[Database_Exist[Vrab0002]]->frame1 >= 290 && game->objects[Database_Exist[Vrab0002]]->frame1 <= 292){if((game->objects[Database_Exist[Vrab0002]]->right != 0 || game->objects[Database_Exist[Vrab0002]]->holding_right != 0) && game->objects[Database_Exist[Vrab0002]]->left == 0 && game->objects[Database_Exist[Vrab0002]]->holding_left == 0){if(game->objects[Database_Exist[Vrab0002]]->facing == 1){game->objects[Database_Exist[Vrab0002]]->facing = 0; game->objects[Database_Exist[Vrab0002]]->frame1 = 299; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0;} else {game->objects[Database_Exist[Vrab0002]]->frame1 = 293; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0;}} if((game->objects[Database_Exist[Vrab0002]]->left != 0 || game->objects[Database_Exist[Vrab0002]]->holding_left != 0) && game->objects[Database_Exist[Vrab0002]]->right == 0 && game->objects[Database_Exist[Vrab0002]]->holding_right == 0){if(game->objects[Database_Exist[Vrab0002]]->facing == 0){game->objects[Database_Exist[Vrab0002]]->facing = 1; game->objects[Database_Exist[Vrab0002]]->frame1 = 299; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0;} else {game->objects[Database_Exist[Vrab0002]]->frame1 = 293; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0;}}} if(game->objects[Database_Exist[Vrab0002]]->frame1 >= 293 && game->objects[Database_Exist[Vrab0002]]->frame1 <= 298){if((game->objects[Database_Exist[Vrab0002]]->right != 0 || game->objects[Database_Exist[Vrab0002]]->holding_right != 0) && game->objects[Database_Exist[Vrab0002]]->left == 0 && game->objects[Database_Exist[Vrab0002]]->holding_left == 0) if(game->objects[Database_Exist[Vrab0002]]->facing == 1){game->objects[Database_Exist[Vrab0002]]->frame1 = 299; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0;} if((game->objects[Database_Exist[Vrab0002]]->left != 0 || game->objects[Database_Exist[Vrab0002]]->holding_left != 0) && game->objects[Database_Exist[Vrab0002]]->right == 0 && game->objects[Database_Exist[Vrab0002]]->holding_right == 0) if(game->objects[Database_Exist[Vrab0002]]->facing == 0){game->objects[Database_Exist[Vrab0002]]->frame1 = 299; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0;}} break;
     case -2: /*/ 2022 - Grandmaster v1.00.220930 /*/ if(game->objects[Database_Exist[Vrab0002]]->max_hp > 10) game->objects[Database_Exist[Vrab0002]]->max_hp = 10; if(game->objects[Database_Exist[Vrab0002]]->dark_hp > 10) game->objects[Database_Exist[Vrab0002]]->dark_hp = 10; if(game->objects[Database_Exist[Vrab0002]]->hp > 10) game->objects[Database_Exist[Vrab0002]]->hp = 10; break;
     case -3: /*/ 2022 - Grandmaster v1.17.221004 /*/
      if(game->objects[Database_Exist[Vrab0002]]->bdefend == 0) game->objects[Database_Exist[Vrab0002]]->fall = -99999999;
      if(game->objects[Database_Exist[Vrab0002]]->bdefend > 0 && game->objects[Database_Exist[Vrab0002]]->fall <= -9999999) game->objects[Database_Exist[Vrab0002]]->fall = 0;

      if(game->objects[Database_Exist[Vrab0002]]->frame1 == 255 || game->objects[Database_Exist[Vrab0002]]->frame1 == 256) if(game->objects[Database_Exist[Vrab0002]]->mp > 5)
      {game->objects[Database_Exist[Vrab0002]]->mp -= 5;} else {game->objects[Database_Exist[Vrab0002]]->frame1 += 2;}
      if((game->objects[Database_Exist[Vrab0002]]->frame1 >= 252 && game->objects[Database_Exist[Vrab0002]]->frame1 <= 258) || (game->objects[Database_Exist[Vrab0002]]->frame1 >= 269 && game->objects[Database_Exist[Vrab0002]]->frame1 <= 278))
      {game->objects[Database_Exist[Vrab0002]]->fall = -99999999; game->objects[Database_Exist[Vrab0002]]->shake = 0; if(game->objects[Database_Exist[Vrab0002]]->x_velocity != 0) game->objects[Database_Exist[Vrab0002]]->x_velocity /= 2; if(game->objects[Database_Exist[Vrab0002]]->z_velocity != 0) game->objects[Database_Exist[Vrab0002]]->z_velocity /= 2;} else
      {
       if(game->objects[Database_Exist[Vrab0002]]->frame1 >= 288 && game->objects[Database_Exist[Vrab0002]]->frame1 <= 301)
       {game->objects[Database_Exist[Vrab0002]]->fall = -99999999; game->objects[Database_Exist[Vrab0002]]->shake = 0; if(game->objects[Database_Exist[Vrab0002]]->frame1 >= 290 && game->objects[Database_Exist[Vrab0002]]->frame1 <= 292) if(game->objects[Database_Exist[Vrab0002]]->mp <= 5){game->objects[Database_Exist[Vrab0002]]->frame1 = 300; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0; game->objects[Database_Exist[Vrab0002]]->mp = 1;}} else
       {if(game->objects[Database_Exist[Vrab0002]]->fall <= -9999999 && game->objects[Database_Exist[Vrab0002]]->bdefend > 0) game->objects[Database_Exist[Vrab0002]]->fall = 0;}
      }
      if(game->objects[Database_Exist[Vrab0002]]->frame1 >= 290 && game->objects[Database_Exist[Vrab0002]]->frame1 <= 292)
      {
       if((game->objects[Database_Exist[Vrab0002]]->right != 0 || game->objects[Database_Exist[Vrab0002]]->holding_right != 0) && game->objects[Database_Exist[Vrab0002]]->left == 0 && game->objects[Database_Exist[Vrab0002]]->holding_left == 0)
       {
        if(game->objects[Database_Exist[Vrab0002]]->facing == 1){game->objects[Database_Exist[Vrab0002]]->facing = 0; game->objects[Database_Exist[Vrab0002]]->frame1 = 299; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0;} else {game->objects[Database_Exist[Vrab0002]]->frame1 = 293; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0;}
       }
       if((game->objects[Database_Exist[Vrab0002]]->left != 0 || game->objects[Database_Exist[Vrab0002]]->holding_left != 0) && game->objects[Database_Exist[Vrab0002]]->right == 0 && game->objects[Database_Exist[Vrab0002]]->holding_right == 0)
       {
        if(game->objects[Database_Exist[Vrab0002]]->facing == 0){game->objects[Database_Exist[Vrab0002]]->facing = 1; game->objects[Database_Exist[Vrab0002]]->frame1 = 299; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0;} else {game->objects[Database_Exist[Vrab0002]]->frame1 = 293; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0;}
       }
      }
      if(game->objects[Database_Exist[Vrab0002]]->frame1 >= 293 && game->objects[Database_Exist[Vrab0002]]->frame1 <= 298)
      {
       if((game->objects[Database_Exist[Vrab0002]]->right != 0 || game->objects[Database_Exist[Vrab0002]]->holding_right != 0) && game->objects[Database_Exist[Vrab0002]]->left == 0 && game->objects[Database_Exist[Vrab0002]]->holding_left == 0) if(game->objects[Database_Exist[Vrab0002]]->facing == 1){game->objects[Database_Exist[Vrab0002]]->frame1 = 299; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0;}
       if((game->objects[Database_Exist[Vrab0002]]->left != 0 || game->objects[Database_Exist[Vrab0002]]->holding_left != 0) && game->objects[Database_Exist[Vrab0002]]->right == 0 && game->objects[Database_Exist[Vrab0002]]->holding_right == 0) if(game->objects[Database_Exist[Vrab0002]]->facing == 0){game->objects[Database_Exist[Vrab0002]]->frame1 = 299; game->objects[Database_Exist[Vrab0002]]->wait_counter = 0;}
      }

      if(game->objects[Database_Exist[Vrab0002]]->data->frames[game->objects[Database_Exist[Vrab0002]]->frame1].itr_count != 0)
      {
       int32 Vrab06[2] = {game->objects[Database_Exist[Vrab0002]]->frame1, 0};
       int32 Vrab01 = game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].itr_count; int32 Vrab02; int32 Vrab03; int32 Vrab04[6]; int32 Vrab05[5]; int32 Vrab07[4];
       Vrab0001 = 0; while(Vrab0001 < Vrab01)
       {
        if(game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].itrs[Vrab0001].kind != 0){Vrab0001 += 1; continue;}
        Vrab04[0] = game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].itrs[Vrab0001].x - game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].centerx;
        Vrab04[1] = game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].itrs[Vrab0001].y - game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].centery;
        Vrab04[2] = game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].itrs[Vrab0001].w;
        Vrab04[3] = game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].itrs[Vrab0001].h;
        Vrab04[4] = game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].itrs[Vrab0001].zwidth;
        if(game->objects[Database_Exist[Vrab0002]]->facing)
        {Vrab04[0] = -Vrab04[0]; Vrab04[2] = -Vrab04[2];}
        if(game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].dvz >= 501)
        {Vrab04[5] = Rounding(game->objects[Database_Exist[Vrab0002]]->z_real) + game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].dvz - 550;} else
        {Vrab04[5] = Rounding(game->objects[Database_Exist[Vrab0002]]->z_real + game->objects[Database_Exist[Vrab0002]]->z_velocity) + game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].dvz;}
        if(game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].dvx >= 501)
        {Vrab04[0] += Rounding(game->objects[Database_Exist[Vrab0002]]->x_real) + game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].dvx - 550;} else
        {
         if(game->objects[Database_Exist[Vrab0002]]->facing)
         {Vrab04[0] += Rounding(game->objects[Database_Exist[Vrab0002]]->x_real + game->objects[Database_Exist[Vrab0002]]->x_velocity) - game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].dvx;} else
         {Vrab04[0] += Rounding(game->objects[Database_Exist[Vrab0002]]->x_real + game->objects[Database_Exist[Vrab0002]]->x_velocity) + game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].dvx;}
        }
        if(game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].dvy >= 501)
        {Vrab04[1] += Rounding(game->objects[Database_Exist[Vrab0002]]->y_real) + game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].dvy - 550;} else
        {Vrab04[1] += Rounding(game->objects[Database_Exist[Vrab0002]]->y_real + game->objects[Database_Exist[Vrab0002]]->y_velocity) + game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].dvy;}
        if(Vrab04[4] == 0) Vrab04[4] = 15;
        if(game->objects[Database_Exist[Vrab0002]]->facing)
        {Vrab07[1] = Vrab04[0]; Vrab07[0] = Vrab04[0] + Vrab04[2];} else
        {Vrab07[0] = Vrab04[0]; Vrab07[1] = Vrab04[0] + Vrab04[2];}
        
          //std::cout << "\n============\n: " << Database_Exist[Vrab0002] << " : " << Vrab04[0] << ", " << Vrab04[1] << ", " << Vrab04[2] << ", " << Vrab04[3] << ", " << Vrab04[4] << "\n";

        for(Vrab0003 = 0; Vrab0003 < NumberOfExist; ++Vrab0003) if(game->objects[Database_Exist[Vrab0003]]->data->frames[game->objects[Database_Exist[Vrab0003]]->frame1].state == 3000) if(game->objects[Database_Exist[Vrab0003]]->data->frames[game->objects[Database_Exist[Vrab0003]]->frame1].bdy_count != 0) switch(game->objects[Database_Exist[Vrab0003]]->data->id)
        {
         case 200: case 203: case 205: case 206: case 207: case 215: case 216:
          if(game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].itrs[Vrab0001].effect != 23 && game->objects[Database_Exist[Vrab0002]]->facing == game->objects[Database_Exist[Vrab0003]]->facing) continue;
          Vrab06[1] = game->objects[Database_Exist[Vrab0003]]->frame1;
          Vrab02 = game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].bdy_count;
          Vrab03 = 0; if(Vrab04[2] != 0 && Vrab04[3] != 0) while(Vrab03 < Vrab02)
          {
           Vrab05[0] = game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].bdys[Vrab03].x - game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].centerx;
           Vrab05[1] = game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].bdys[Vrab03].y - game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].centery;
           Vrab05[2] = game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].bdys[Vrab03].w;
           Vrab05[3] = game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].bdys[Vrab03].h;
           Vrab05[4] = 0;
           if(game->objects[Database_Exist[Vrab0003]]->facing)
           {Vrab05[0] = -Vrab05[0]; Vrab05[2] = -Vrab05[2];}
           if(game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].dvz >= 501)
           {Vrab05[4] = Rounding(game->objects[Database_Exist[Vrab0003]]->z_real) + game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].dvz - 550;} else
           {Vrab05[4] = Rounding(game->objects[Database_Exist[Vrab0003]]->z_real + game->objects[Database_Exist[Vrab0003]]->z_velocity) + game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].dvz;}
           if(game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].dvx >= 501)
           {Vrab05[0] += Rounding(game->objects[Database_Exist[Vrab0003]]->x_real) + game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].dvx - 550;} else
           {
            if(game->objects[Database_Exist[Vrab0003]]->facing)
            {Vrab05[0] += Rounding(game->objects[Database_Exist[Vrab0003]]->x_real + game->objects[Database_Exist[Vrab0003]]->x_velocity) - game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].dvx;} else
            {Vrab05[0] += Rounding(game->objects[Database_Exist[Vrab0003]]->x_real + game->objects[Database_Exist[Vrab0003]]->x_velocity) + game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].dvx;}
           }
           if(game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].dvy >= 501)
           {Vrab05[1] += Rounding(game->objects[Database_Exist[Vrab0003]]->y_real) + game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].dvy - 550;} else
           {Vrab05[1] += Rounding(game->objects[Database_Exist[Vrab0003]]->y_real + game->objects[Database_Exist[Vrab0003]]->y_velocity) + game->objects[Database_Exist[Vrab0003]]->data->frames[Vrab06[1]].dvy;}
           if(game->objects[Database_Exist[Vrab0003]]->facing)
           {Vrab07[3] = Vrab05[0]; Vrab07[2] = Vrab05[0] + Vrab05[2];} else
           {Vrab07[2] = Vrab05[0]; Vrab07[3] = Vrab05[0] + Vrab05[2];}

           // std::cout << "| " << Database_Exist[Vrab0003] << " : " << Vrab05[0] << ", " << Vrab05[1] << ", " << Vrab05[2] << ", " << Vrab05[3] << "\n";

           if(Vrab05[2] != 0 && Vrab05[3] != 0)
           if((Vrab07[0] >= Vrab07[2] && Vrab07[0] <= Vrab07[3]) || (Vrab07[1] >= Vrab07[2] && Vrab07[1] <= Vrab07[3]) || (Vrab07[2] >= Vrab07[0] && Vrab07[3] <= Vrab07[1]))
           if((Vrab04[1] >= Vrab05[1] && Vrab04[1] <= Vrab05[1] + Vrab05[3]) || (Vrab04[1] + Vrab04[3] >= Vrab05[1] && Vrab04[1] + Vrab04[3] <= Vrab05[1] + Vrab05[3]) || (Vrab05[1] >= Vrab04[1] && Vrab05[1] + Vrab05[3] <= Vrab04[1] + Vrab04[3]))
           if(Vrab04[5] - Vrab04[4] <= Vrab05[4] && Vrab04[5] + Vrab04[4] >= Vrab05[4])
           if((game->objects[Database_Exist[Vrab0003]]->vrests[Database_Exist[Vrab0002]] == 0 && game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].itrs[Vrab0001].vrest != 0) || game->objects[Database_Exist[Vrab0002]]->arest == 0)
           {
            game->objects[Database_Exist[Vrab0003]]->frame1 = (int32)(uint8)game->objects[Database_Exist[Vrab0003]]->data->unkwn2[224] + (int32)(uint8)game->objects[Database_Exist[Vrab0003]]->data->unkwn2[225] * 256;
            game->objects[Database_Exist[Vrab0003]]->team = game->objects[Database_Exist[Vrab0002]]->team;
            game->objects[Database_Exist[Vrab0003]]->shake = -3;
            game->objects[Database_Exist[Vrab0003]]->x_velocity = 0;
            game->objects[Database_Exist[Vrab0003]]->y_velocity = 0;
            game->objects[Database_Exist[Vrab0003]]->z_velocity = 0;
            game->objects[Database_Exist[Vrab0003]]->x_acceleration = 0;
            game->objects[Database_Exist[Vrab0003]]->y_acceleration = 0;
            game->objects[Database_Exist[Vrab0003]]->z_acceleration = 0;
            game->objects[Database_Exist[Vrab0003]]->wait_counter = 0;
            game->objects[Database_Exist[Vrab0003]]->vrests[Database_Exist[Vrab0002]] = (int8)game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].itrs[Vrab0001].vrest;
            game->objects[Database_Exist[Vrab0002]]->arest = game->objects[Database_Exist[Vrab0002]]->data->frames[Vrab06[0]].itrs[Vrab0001].arest;
            game->objects[Database_Exist[Vrab0002]]->shake = -3;
           }
           Vrab03 += 1;
          }
         break; default: break;
        }
        Vrab0001 += 1;
       }
      }
      for(Vrab0003 = 0; Vrab0003 < NumberOfExist; ++Vrab0003) if(game->objects[Database_Exist[Vrab0003]]->data->id == 209) if(game->objects[Database_Exist[Vrab0003]]->frame1 == 31) game->objects[Database_Exist[Vrab0003]]->pic_gain = 0;
     break;
     default: break;
    }
   }
   int0 Peat_EtCetera()
   {
    if(Config.Dis_Il_Input) for(Vrab0002 = 0; Vrab0002 < NumberOfExistT0COM; ++Vrab0002)
    {
     if(LastInput[0][Database_ExistT0COM[Vrab0002]] == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->A == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->holding_a == 0){game->objects[Database_ExistT0COM[Vrab0002]]->holding_a = 0; game->objects[Database_ExistT0COM[Vrab0002]]->A = 0;}
     if(LastInput[1][Database_ExistT0COM[Vrab0002]] == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->D == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->holding_d == 0){game->objects[Database_ExistT0COM[Vrab0002]]->holding_d = 0; game->objects[Database_ExistT0COM[Vrab0002]]->D = 0;}
     if(LastInput[2][Database_ExistT0COM[Vrab0002]] == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->J == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->holding_j == 0){game->objects[Database_ExistT0COM[Vrab0002]]->holding_j = 0; game->objects[Database_ExistT0COM[Vrab0002]]->J = 0;}
     if(LastInput[3][Database_ExistT0COM[Vrab0002]] == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->up == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->holding_up == 0){game->objects[Database_ExistT0COM[Vrab0002]]->holding_up = 0; game->objects[Database_ExistT0COM[Vrab0002]]->up = 0;}
     if(LastInput[4][Database_ExistT0COM[Vrab0002]] == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->left == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->holding_left == 0){game->objects[Database_ExistT0COM[Vrab0002]]->holding_left = 0; game->objects[Database_ExistT0COM[Vrab0002]]->left = 0;}
     if(LastInput[5][Database_ExistT0COM[Vrab0002]] == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->down == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->holding_down == 0){game->objects[Database_ExistT0COM[Vrab0002]]->holding_down = 0; game->objects[Database_ExistT0COM[Vrab0002]]->down = 0;}
     if(LastInput[6][Database_ExistT0COM[Vrab0002]] == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->right == 1 && game->objects[Database_ExistT0COM[Vrab0002]]->holding_right == 0){game->objects[Database_ExistT0COM[Vrab0002]]->holding_right = 0; game->objects[Database_ExistT0COM[Vrab0002]]->right = 0;}
     LastInput[0][Database_ExistT0COM[Vrab0002]] = game->objects[Database_ExistT0COM[Vrab0002]]->A;
     LastInput[1][Database_ExistT0COM[Vrab0002]] = game->objects[Database_ExistT0COM[Vrab0002]]->D;
     LastInput[2][Database_ExistT0COM[Vrab0002]] = game->objects[Database_ExistT0COM[Vrab0002]]->J;
     LastInput[3][Database_ExistT0COM[Vrab0002]] = game->objects[Database_ExistT0COM[Vrab0002]]->up;
     LastInput[4][Database_ExistT0COM[Vrab0002]] = game->objects[Database_ExistT0COM[Vrab0002]]->left;
     LastInput[5][Database_ExistT0COM[Vrab0002]] = game->objects[Database_ExistT0COM[Vrab0002]]->down;
     LastInput[6][Database_ExistT0COM[Vrab0002]] = game->objects[Database_ExistT0COM[Vrab0002]]->right;
    }
   }
   int0 Peat_PackVampirism()
   {
    int32 Vrab01;
    if(Config.HP_Regen) if((*(int*)0x450b8c + 1) % 12 == 0) for(Vrab0002 = 0; Vrab0002 < NumberOfExistT0; ++Vrab0002) if(game->objects[Database_ExistT0[Vrab0002]]->hp > 1) if(game->objects[Database_ExistT0[Vrab0002]]->hp < game->objects[Database_ExistT0[Vrab0002]]->dark_hp) game->objects[Database_ExistT0[Vrab0002]]->hp -= 1;
    if(Config.MP_Regen) if((*(int*)0x450b8c + 1) % 3 == 0) for(Vrab0002 = 0; Vrab0002 < NumberOfExistT0; ++Vrab0002) if(game->objects[Database_ExistT0[Vrab0002]]->mp > 1) if(game->objects[Database_ExistT0[Vrab0002]]->mp < MaximumMP) game->objects[Database_ExistT0[Vrab0002]]->mp -= 5 - ((game->objects[Database_ExistT0[Vrab0002]]->hp - 1) / 100);
    for(Vrab0002 = 0; Vrab0002 < NumberOfExistT0; ++Vrab0002)
    {
     if(Convertion[Database_ExistT0[Vrab0002]] < game->objects[Database_ExistT0[Vrab0002]]->total_attack) if(game->objects[Database_ExistT0[Vrab0002]]->hp > 0)
     {
      Vrab0001 = game->objects[Database_ExistT0[Vrab0002]]->total_attack - Convertion[Database_ExistT0[Vrab0002]];
      if(Config.DTDHP_Conv != 0) if(game->objects[Database_ExistT0[Vrab0002]]->dark_hp < game->objects[Database_ExistT0[Vrab0002]]->max_hp) if(!Config.Dis_DHP)
      {
       Vrab01 = Rounding((xint64)Vrab0001 * Config.DTDHP_Conv * 0.01);
       if(game->objects[Database_ExistT0[Vrab0002]]->dark_hp + Vrab01 > game->objects[Database_ExistT0[Vrab0002]]->max_hp){game->objects[Database_ExistT0[Vrab0002]]->dark_hp = game->objects[Database_ExistT0[Vrab0002]]->max_hp;} else {game->objects[Database_ExistT0[Vrab0002]]->dark_hp += Vrab01;}
      }
      if(Config.DTHP_Conv != 0)
      {
       Vrab01 = Rounding((xint64)Vrab0001 * Config.DTHP_Conv * 0.01);
       if(game->objects[Database_ExistT0[Vrab0002]]->hp < game->objects[Database_ExistT0[Vrab0002]]->dark_hp)
       {
        if(game->objects[Database_ExistT0[Vrab0002]]->hp + Vrab01 > game->objects[Database_ExistT0[Vrab0002]]->dark_hp){game->objects[Database_ExistT0[Vrab0002]]->hp = game->objects[Database_ExistT0[Vrab0002]]->dark_hp;} else {game->objects[Database_ExistT0[Vrab0002]]->hp += Vrab01;}
       } else
       {
        if(Config.Dis_DHP)
        if(game->objects[Database_ExistT0[Vrab0002]]->hp + Vrab01 > game->objects[Database_ExistT0[Vrab0002]]->max_hp){game->objects[Database_ExistT0[Vrab0002]]->hp = game->objects[Database_ExistT0[Vrab0002]]->max_hp;} else {game->objects[Database_ExistT0[Vrab0002]]->hp += Vrab01;}
       }
      }
      if(Config.DTMP_Conv != 0) if(game->objects[Database_ExistT0[Vrab0002]]->mp < MaximumMP)
      {
       Vrab01 = Rounding((xint64)Vrab0001 * Config.DTMP_Conv * 0.01);
       if(game->objects[Database_ExistT0[Vrab0002]]->mp + Vrab01 > MaximumMP){game->objects[Database_ExistT0[Vrab0002]]->mp = MaximumMP;} else {game->objects[Database_ExistT0[Vrab0002]]->mp += Vrab01;}
      }
     }
     Convertion[Database_ExistT0[Vrab0002]] = game->objects[Database_ExistT0[Vrab0002]]->total_attack;
    }
   }
   int0 Peat_PackSkillOut()
   {
    if(Config.B_Reserve > 1 || (Config.S_Reserve > 1 && *(int*)0x451160 == 1)) for(Vrab0002 = 0; Vrab0002 < NumberOfExistT0; ++Vrab0002)
    if(Database_ExistT0[Vrab0002] >= 20){break;} else
    {
     if(*(int*)0x450b8c > 1) if(ReserveCount[Database_ExistT0[Vrab0002]] > 99){game->objects[Database_ExistT0[Vrab0002]]->reserve = 100;} else {game->objects[Database_ExistT0[Vrab0002]]->reserve = ReserveCount[Database_ExistT0[Vrab0002]];}
     if(game->objects[Database_ExistT0[Vrab0002]]->blink < -25) game->objects[Database_ExistT0[Vrab0002]]->reserve = 0;
     if(ReserveCount[Database_ExistT0[Vrab0002]] > 1)
     if(game->objects[Database_ExistT0[Vrab0002]]->hp <= 0 || game->objects[Database_ExistT0[Vrab0002]]->hp >= 50000000)
     {
      if(game->objects[Database_ExistT0[Vrab0002]]->frame1 < 203 && game->objects[Database_ExistT0[Vrab0002]]->frame1 > 206 && game->objects[Database_ExistT0[Vrab0002]]->data->frames[game->objects[Database_ExistT0[Vrab0002]]->frame1].state != 13 && game->objects[Database_ExistT0[Vrab0002]]->data->frames[game->objects[Database_ExistT0[Vrab0002]]->frame1].state != 14 && game->objects[Database_ExistT0[Vrab0002]]->data->frames[game->objects[Database_ExistT0[Vrab0002]]->frame1].state != 12 && game->objects[Database_ExistT0[Vrab0002]]->data->frames[game->objects[Database_ExistT0[Vrab0002]]->frame1].state != 10)
      {if(game->objects[Database_ExistT0[Vrab0002]]->hp == 0){game->objects[Database_ExistT0[Vrab0002]]->hp = 100000000;} else {game->objects[Database_ExistT0[Vrab0002]]->hp = 0;}} else {game->objects[Database_ExistT0[Vrab0002]]->hp = 100000000;}
      game->objects[Database_ExistT0[Vrab0002]]->dark_hp = 0;
      if(game->objects[Database_ExistT0[Vrab0002]]->mp <= MaximumMP * 2) game->objects[Database_ExistT0[Vrab0002]]->mp = game->objects[Database_ExistT0[Vrab0002]]->mp * MaximumMP * 2;
      game->objects[Database_ExistT0[Vrab0002]]->A = 0;
      game->objects[Database_ExistT0[Vrab0002]]->D = 0;
      game->objects[Database_ExistT0[Vrab0002]]->J = 0;
      game->objects[Database_ExistT0[Vrab0002]]->up = 0;
      game->objects[Database_ExistT0[Vrab0002]]->left = 0;
      game->objects[Database_ExistT0[Vrab0002]]->down = 0;
      game->objects[Database_ExistT0[Vrab0002]]->right = 0;
      game->objects[Database_ExistT0[Vrab0002]]->holding_a = 0;
      game->objects[Database_ExistT0[Vrab0002]]->holding_d = 0;
      game->objects[Database_ExistT0[Vrab0002]]->holding_j = 0;
      game->objects[Database_ExistT0[Vrab0002]]->holding_up = 0;
      game->objects[Database_ExistT0[Vrab0002]]->holding_left = 0;
      game->objects[Database_ExistT0[Vrab0002]]->holding_down = 0;
      game->objects[Database_ExistT0[Vrab0002]]->holding_right = 0;
      game->objects[Database_ExistT0[Vrab0002]]->DrA = 0;
      game->objects[Database_ExistT0[Vrab0002]]->DrJ = 0;
      game->objects[Database_ExistT0[Vrab0002]]->DlA = 0;
      game->objects[Database_ExistT0[Vrab0002]]->DlJ = 0;
      game->objects[Database_ExistT0[Vrab0002]]->DdA = 0;
      game->objects[Database_ExistT0[Vrab0002]]->DdJ = 0;
      game->objects[Database_ExistT0[Vrab0002]]->DuA = 0;
      game->objects[Database_ExistT0[Vrab0002]]->DuJ = 0;
      game->objects[Database_ExistT0[Vrab0002]]->DJA = 0;
      if(game->objects[Database_ExistT0[Vrab0002]]->data->frames[game->objects[Database_ExistT0[Vrab0002]]->frame1].state == 14)
      {
       if(game->objects[Database_ExistT0[Vrab0002]]->wait_counter <= 1)
	   {
	    game->objects[Database_ExistT0[Vrab0002]]->blink = 30;
	    game->objects[Database_ExistT0[Vrab0002]]->wait_counter = 2;
	   }
       if(game->objects[Database_ExistT0[Vrab0002]]->wait_counter > 2)
	   game->objects[Database_ExistT0[Vrab0002]]->wait_counter = 2;
       if(game->objects[Database_ExistT0[Vrab0002]]->blink == 0)
	   {
	    game->objects[Database_ExistT0[Vrab0002]]->hp = game->objects[Database_ExistT0[Vrab0002]]->max_hp;
	    game->objects[Database_ExistT0[Vrab0002]]->dark_hp = game->objects[Database_ExistT0[Vrab0002]]->max_hp;
        if(game->objects[Database_ExistT0[Vrab0002]]->mp > MaximumMP) game->objects[Database_ExistT0[Vrab0002]]->mp = game->objects[Database_ExistT0[Vrab0002]]->mp / (MaximumMP * 2);
        if(game->objects[Database_ExistT0[Vrab0002]]->mp > MaximumMP) game->objects[Database_ExistT0[Vrab0002]]->mp = MaximumMP;
	    if(Config.MP_Rest) game->objects[Database_ExistT0[Vrab0002]]->mp = MaximumMP;
	    game->objects[Database_ExistT0[Vrab0002]]->blink = Config.Imm_Time;
	    game->objects[Database_ExistT0[Vrab0002]]->y_real = -400;
	    ReserveCount[Database_ExistT0[Vrab0002]] -= 1;
	    game->objects[Database_ExistT0[Vrab0002]]->frame1 = 212; 
	   }
      }
     }
    }
    if(Config.Dis_DHP) 
    {
     for(Vrab0002 = 0; Vrab0002 < MaximumObject; ++Vrab0002) if(!game->exists[Vrab0002]) Dis_DHP_HP_R[Vrab0002] = 0;
     for(Vrab0002 = 0; Vrab0002 < NumberOfExistT0; ++Vrab0002)
     {
      if(Dis_DHP_HP_R[Database_ExistT0[Vrab0002]] < 0) Dis_DHP_HP_R[Database_ExistT0[Vrab0002]] = 0;
      if(game->objects[Database_ExistT0[Vrab0002]]->dark_hp > 0 && Dis_DHP_HP_R[Database_ExistT0[Vrab0002]] > 0)
      {
       game->objects[Database_ExistT0[Vrab0002]]->hp = Dis_DHP_HP_R[Database_ExistT0[Vrab0002]] + game->objects[Database_ExistT0[Vrab0002]]->dark_hp;
       if(game->objects[Database_ExistT0[Vrab0002]]->hp > game->objects[Database_ExistT0[Vrab0002]]->max_hp) game->objects[Database_ExistT0[Vrab0002]]->hp = game->objects[Database_ExistT0[Vrab0002]]->max_hp;
      }
      Dis_DHP_HP_R[Database_ExistT0[Vrab0002]] = game->objects[Database_ExistT0[Vrab0002]]->hp;
      game->objects[Database_ExistT0[Vrab0002]]->dark_hp = 0;
      if(game->objects[Database_ExistT0[Vrab0002]]->data->frames[game->objects[Database_ExistT0[Vrab0002]]->frame1].state == 69696969)
      {
       if(!game->exists[game->objects[Database_ExistT0[Vrab0002]]->weapon_held])
       {
        if(game->objects[Database_ExistT0[Vrab0002]]->data->frames[game->objects[Database_ExistT0[Vrab0002]]->frame1].hit_d >= MaximumFrames)
        {game->objects[Database_ExistT0[Vrab0002]]->frame1 = 0;} else
        {game->objects[Database_ExistT0[Vrab0002]]->frame1 = game->objects[Database_ExistT0[Vrab0002]]->data->frames[game->objects[Database_ExistT0[Vrab0002]]->frame1].hit_d;}
        continue;
       }
       if(game->objects[game->objects[Database_ExistT0[Vrab0002]]->weapon_held]->data->type == 6) switch(game->objects[game->objects[Database_ExistT0[Vrab0002]]->weapon_held]->data->id)
       {
        case 122:
         if(game->objects[game->objects[Database_ExistT0[Vrab0002]]->weapon_held]->bottle_hp > 0)
         {
          game->objects[Database_ExistT0[Vrab0002]]->hp += Config.M_Amount;
          if(game->objects[Database_ExistT0[Vrab0002]]->hp > game->objects[Database_ExistT0[Vrab0002]]->max_hp) game->objects[Database_ExistT0[Vrab0002]]->hp = game->objects[Database_ExistT0[Vrab0002]]->max_hp;
          game->objects[game->objects[Database_ExistT0[Vrab0002]]->weapon_held]->bottle_hp -= Config.M_Speed;
         } else
         {
          game->objects[game->objects[Database_ExistT0[Vrab0002]]->weapon_held]->bottle_hp = -1;
          game->objects[game->objects[Database_ExistT0[Vrab0002]]->weapon_held]->hp = 0;
         }
        break;
        case 123:
         if(game->objects[game->objects[Database_ExistT0[Vrab0002]]->weapon_held]->bottle_hp > 0)
         {
          game->objects[Database_ExistT0[Vrab0002]]->mp += Config.T_Amount;
          if(game->objects[Database_ExistT0[Vrab0002]]->mp > MaximumMP) game->objects[Database_ExistT0[Vrab0002]]->mp = MaximumMP;
          game->objects[game->objects[Database_ExistT0[Vrab0002]]->weapon_held]->bottle_hp -= Config.T_Speed;
         } else
         {
          game->objects[game->objects[Database_ExistT0[Vrab0002]]->weapon_held]->bottle_hp = -1;
          game->objects[game->objects[Database_ExistT0[Vrab0002]]->weapon_held]->hp = 0;
         }
        break;
        default: break;
       }
      }
     }
    }
    if(Config.Dis_MP) for(Vrab0002 = 0; Vrab0002 < NumberOfExistT0; ++Vrab0002) game->objects[Database_ExistT0[Vrab0002]]->mp = 0;
   }
   int0 Peat_PackTDMode()
   {
    if(Config.Hold_Def)
    {
     for(Vrab0002 = 0; Vrab0002 < NumberOfExistT0; ++Vrab0002)
     {
      if(game->objects[Database_ExistT0[Vrab0002]]->data->frames[game->objects[Database_ExistT0[Vrab0002]]->frame1].cpoint.daction == 1)
      {
       Hold_Def_TU_Count[Database_ExistT0[Vrab0002]] += 1; if(Hold_Def_TU_Count[Database_ExistT0[Vrab0002]] > 999999999) Hold_Def_TU_Count[Database_ExistT0[Vrab0002]] = 999999999;
       if(game->objects[Database_ExistT0[Vrab0002]]->D == 0 && game->objects[Database_ExistT0[Vrab0002]]->holding_d == 0){if(game->objects[Database_ExistT0[Vrab0002]]->shake != 0) continue; if(Hold_Def_TU_Count[Database_ExistT0[Vrab0002]] < Config.Hold_Def_TU) continue; game->objects[Database_ExistT0[Vrab0002]]->wait_counter = 0; if(game->objects[Database_ExistT0[Vrab0002]]->data->frames[game->objects[Database_ExistT0[Vrab0002]]->frame1].next >= MaximumFrames){game->objects[Database_ExistT0[Vrab0002]]->frame1 = 0;} else {game->objects[Database_ExistT0[Vrab0002]]->frame1 = game->objects[Database_ExistT0[Vrab0002]]->data->frames[game->objects[Database_ExistT0[Vrab0002]]->frame1].next;}} else
       {game->objects[Database_ExistT0[Vrab0002]]->wait_counter -= 1;}
      } else {Hold_Def_TU_Count[Database_ExistT0[Vrab0002]] = 0;}
     }
    }
   }
   int0 Peat_EtCetera2()
   {
    //Clean Value
     if(Config.Clean_Val) for(Vrab0002 = 0; Vrab0002 < NumberOfExist; ++Vrab0002)
     {
      if(game->objects[Database_Exist[Vrab0002]]->hp < 0) game->objects[Database_Exist[Vrab0002]]->hp = 0;
      if(game->objects[Database_Exist[Vrab0002]]->dark_hp < 0) game->objects[Database_Exist[Vrab0002]]->dark_hp = 0;
      if(game->objects[Database_Exist[Vrab0002]]->mp < 0) game->objects[Database_Exist[Vrab0002]]->mp = 0;
      if(game->objects[Database_Exist[Vrab0002]]->kills < 0) game->objects[Database_Exist[Vrab0002]]->kills = 0;
      if(game->objects[Database_Exist[Vrab0002]]->total_attack < 0) game->objects[Database_Exist[Vrab0002]]->total_attack = 0;
      if(game->objects[Database_Exist[Vrab0002]]->hp_lost < 0) game->objects[Database_Exist[Vrab0002]]->hp_lost = 0;
      if(game->objects[Database_Exist[Vrab0002]]->mp_usage < 0) game->objects[Database_Exist[Vrab0002]]->mp_usage = 0;
      if(game->objects[Database_Exist[Vrab0002]]->weapon_picks < 0) game->objects[Database_Exist[Vrab0002]]->weapon_picks = 0;
     }
    //-//
    //Overlaying
     
    //-//
    //Camera Shift
     if(Config.C_Shift)
     {
      if(Modifer.BG_Cam[0].size() < (uint32)*(int*)0x44d024 + 1)
      {
       Vrab0001 = *(int*)0x44d024 + 1;
       Modifer.BG_Cam[0].resize(Vrab0001);
       Modifer.BG_Cam[1].resize(Vrab0001);
       Modifer.BG_Cam[2].resize(Vrab0001);
       Modifer.BG_Z1.resize(Vrab0001);
       Modifer.BG_Z2.resize(Vrab0001);
       Modifer.BG_Y.resize(Vrab0001);
       Modifer.BG_H.resize(Vrab0001);
       for(Vrab0002 = 0; Vrab0002 < (uint32)Vrab0001; ++Vrab0002) Modifer.BG_Y[Vrab0002].resize(40);
       for(Vrab0002 = 0; Vrab0002 < (uint32)Vrab0001; ++Vrab0002) Modifer.BG_H[Vrab0002].resize(40);
      }
      if(Modifer.BG_Cam[0][*(int*)0x44d024] == 0)
      {
       Vrab0001 = *(int*)0x44d024;
       Modifer.BG_Z1[Vrab0001] = game->files->backgrounds[Vrab0001].bg_zwidth1;
       Modifer.BG_Z2[Vrab0001] = game->files->backgrounds[Vrab0001].bg_zwidth2;
       for(Vrab0002 = 0; Vrab0002 < (uint32)game->files->backgrounds[Vrab0001].layer_count + 5; ++Vrab0002)
       {
        Modifer.BG_Y[Vrab0001][Vrab0002] = game->files->backgrounds[Vrab0001].layer_y[Vrab0002];
        Modifer.BG_H[Vrab0001][Vrab0002] = game->files->backgrounds[Vrab0001].layer_height[Vrab0002];
       } 
      }

      Vrab0001 = 0; Vrab0003 = 0; Vrab0004 = 0; for(Vrab0002 = 0; Vrab0002 < 10; ++Vrab0002)
      {
       if(!game->exists[Vrab0002]) continue;
       if(Config.C_Smoothness)
       {
        if(game->objects[Vrab0002]->data->frames[game->objects[Vrab0002]->frame1].dvy <= 500)
        {
         if(game->objects[Vrab0002]->data->frames[game->objects[Vrab0002]->frame1].dvz <= 500)
         {
          Vrab0004 += ((game->objects[Vrab0002]->y_real + game->objects[Vrab0002]->y_velocity) * Config.C_Effectiviness * 0.01) + game->objects[Vrab0002]->z_real + game->objects[Vrab0002]->z_velocity + (xint64)Modifer.BG_Cam[0][*(int*)0x44d024];
         } else
         {
          Vrab0004 += ((game->objects[Vrab0002]->y_real + game->objects[Vrab0002]->y_velocity) * Config.C_Effectiviness * 0.01) + game->objects[Vrab0002]->z_real + (game->objects[Vrab0002]->data->frames[game->objects[Vrab0002]->frame1].dvz - 550) + (xint64)Modifer.BG_Cam[0][*(int*)0x44d024];
         }
        } else
        {
         if(game->objects[Vrab0002]->data->frames[game->objects[Vrab0002]->frame1].dvz <= 500)
         {
          Vrab0004 += ((game->objects[Vrab0002]->y_real + (game->objects[Vrab0002]->data->frames[game->objects[Vrab0002]->frame1].dvy - 550)) * Config.C_Effectiviness * 0.01) + game->objects[Vrab0002]->z_real + game->objects[Vrab0002]->z_velocity + (xint64)Modifer.BG_Cam[0][*(int*)0x44d024];
         } else
         {
          Vrab0004 += ((game->objects[Vrab0002]->y_real + (game->objects[Vrab0002]->data->frames[game->objects[Vrab0002]->frame1].dvy - 550)) * Config.C_Effectiviness * 0.01) + game->objects[Vrab0002]->z_real + (game->objects[Vrab0002]->data->frames[game->objects[Vrab0002]->frame1].dvz - 550) + (xint64)Modifer.BG_Cam[0][*(int*)0x44d024];
         }
        }
       } else
       {Vrab0001 += Rounding(((game->objects[Vrab0002]->y_real + game->objects[Vrab0002]->y_velocity) * Config.C_Effectiviness * 0.01) + game->objects[Vrab0002]->z_real + game->objects[Vrab0002]->z_velocity) + Modifer.BG_Cam[0][*(int*)0x44d024];}
       Vrab0003 += 1;
      }
      if(Vrab0003 != 0) if(Config.C_Smoothness)
      {Vrab0004 = (Vrab0004 / (xint64)(int32)Vrab0003) - (xint64)Config.C_Off;} else
      {Modifer.BG_Cam[2][*(int*)0x44d024] = Rounding((xint64)Vrab0001 / (xint64)(int32)Vrab0003) - Config.C_Off;}
      Vrab0001 = *(int*)0x44d024;

      ///
      if(Config.C_Smoothness)
      {
       Modifer.BG_Cam[1][Vrab0001] = Rounding(Vrab0004 - (xint64)Modifer.BG_Cam[0][Vrab0001]);
      } else
      {
       Vrab0003 = (uint32)(Modifer.BG_Cam[2][Vrab0001] - Modifer.BG_Cam[0][Vrab0001]);
       if((int32)Vrab0003 > 0)
       {
        if((Modifer.BG_Cam[1][Vrab0001] * 500) / (int32)Config.C_Speed < (int32)Vrab0003) if(Modifer.BG_Cam[1][Vrab0001] + (((int32)Vrab0003 * (int32)Config.C_Speed) / 20) > ((int32)Vrab0003 * (int32)Config.C_Speed) / 5){Modifer.BG_Cam[1][Vrab0001] = ((int32)Vrab0003 * (int32)Config.C_Speed) / 5;} else {Modifer.BG_Cam[1][Vrab0001] += ((int32)Vrab0003 * (int32)Config.C_Speed) / 20;}
        if((Modifer.BG_Cam[1][Vrab0001] * 500) / (int32)Config.C_Speed > (int32)Vrab0003) if(Modifer.BG_Cam[1][Vrab0001] - (((int32)Vrab0003 * (int32)Config.C_Speed) / 10) < ((int32)Vrab0003 * (int32)Config.C_Speed) / 5){Modifer.BG_Cam[1][Vrab0001] = ((int32)Vrab0003 * (int32)Config.C_Speed) / 5;} else {Modifer.BG_Cam[1][Vrab0001] -= ((int32)Vrab0003 * (int32)Config.C_Speed) / 10;}
       } else
       {
        if((int32)Vrab0003 < 0)
        {
         if((Modifer.BG_Cam[1][Vrab0001] * 500) / (int32)Config.C_Speed > (int32)Vrab0003) if(Modifer.BG_Cam[1][Vrab0001] - (((int32)Vrab0003 * (int32)Config.C_Speed) / 20) < ((int32)Vrab0003 * (int32)Config.C_Speed) / 5){Modifer.BG_Cam[1][Vrab0001] = ((int32)Vrab0003 * (int32)Config.C_Speed) / 5;} else {Modifer.BG_Cam[1][Vrab0001] -= ((int32)Vrab0003 * (int32)Config.C_Speed) / 20;}
         if((Modifer.BG_Cam[1][Vrab0001] * 500) / (int32)Config.C_Speed < (int32)Vrab0003) if(Modifer.BG_Cam[1][Vrab0001] + (((int32)Vrab0003 * (int32)Config.C_Speed) / 10) > ((int32)Vrab0003 * (int32)Config.C_Speed) / 5){Modifer.BG_Cam[1][Vrab0001] = ((int32)Vrab0003 * (int32)Config.C_Speed) / 5;} else {Modifer.BG_Cam[1][Vrab0001] += ((int32)Vrab0003 * (int32)Config.C_Speed) / 10;}
        }
       }
      }

      Vrab0003 = (uint32)Modifer.BG_Cam[1][Vrab0001];
      Modifer.BG_Cam[0][Vrab0001] += (int32)Vrab0003;
      ///

      game->files->backgrounds[Vrab0001].bg_zwidth1 = Modifer.BG_Z1[Vrab0001] - Modifer.BG_Cam[0][Vrab0001];
      game->files->backgrounds[Vrab0001].bg_zwidth2 = Modifer.BG_Z2[Vrab0001] - Modifer.BG_Cam[0][Vrab0001];
      for(Vrab0002 = 0; Vrab0002 < (uint32)game->files->backgrounds[Vrab0001].layer_count + 5; ++Vrab0002)
      {
       game->files->backgrounds[Vrab0001].layer_y[Vrab0002] = Modifer.BG_Y[Vrab0001][Vrab0002] - Modifer.BG_Cam[0][Vrab0001];
       if(Modifer.BG_H[Vrab0001][Vrab0002] + game->files->backgrounds[Vrab0001].layer_y[Vrab0002] > Config.C_Size){game->files->backgrounds[Vrab0001].layer_height[Vrab0002] = Config.C_Size - game->files->backgrounds[Vrab0001].layer_y[Vrab0002];} else {game->files->backgrounds[Vrab0001].layer_height[Vrab0002] = Modifer.BG_H[Vrab0001][Vrab0002];}
      }
      for(Vrab0002 = 0; Vrab0002 < NumberOfExist; ++Vrab0002) game->objects[Database_Exist[Vrab0002]]->z_real -= (xint64)(int32)Vrab0003;

      /*clr();
      std::cout << "\n\n============\n[" << Vrab0001 << "] : " << Modifer.BG_Cam[0][Vrab0001] << ", " << Modifer.BG_Cam[1][Vrab0001] << ", " << Modifer.BG_Cam[2][Vrab0001] << " {" << Modifer.BG_Z1[Vrab0001] << ", " << Modifer.BG_Z2[Vrab0001] << "}\n";
      for(Vrab0002 = 0; Vrab0002 < NumberOfExist; ++Vrab0002)
      {
       std::cout << "\n[" << Database_Exist[Vrab0002] << "] = " << game->objects[Database_Exist[Vrab0002]]->z_real << " : " << Rounding(((game->objects[Database_Exist[Vrab0002]]->y_real + game->objects[Database_Exist[Vrab0002]]->y_velocity) * Config.C_Effectiviness * 0.01) + game->objects[Database_Exist[Vrab0002]]->z_real + game->objects[Database_Exist[Vrab0002]]->z_velocity) - Modifer.BG_Cam[0][*(int*)0x44d024] - Config.C_Off;
      }/*/
     }
    //-//
   }
  //-//
  int0 Base_Process()
  {
   if(Database_FirstInGame)
   {
	Database_FirstInGame = false;
    Once_FullInjection();
    Once_EtCetera();
    Once_CodedSpeciality();
    Once_PackSkillOut();
    Once_PackTDMode();
   }

   Peat_CodedSpeciality();
   Peat_EtCetera();
   Peat_PackVampirism();
   Peat_PackSkillOut();
   Peat_PackTDMode();
   Peat_EtCetera2();
   Peat_FullInjection();
  }
  int0 Base_Reset()
  {
   //Data Reset
   // int1 Vrab01 = false; if(*(int*)0x450b8c < LastTU) Vrab01 = true; LastTU = *(int*)0x450b8c - 1;
   // if(Vrab01)
   // {
     //Full_Injection
      if(Config.Full_Injection){while(game->files->datas[Vrab0002] != 0){if(game->files->datas[Vrab0002]->id == Full_Injection_ID2){game->files->datas[Vrab0002]->frames[0].centerx = 1000; game->files->datas[Vrab0002]->frames[1].centerx = 1000; game->files->datas[Vrab0002]->frames[0].centery = -1000; game->files->datas[Vrab0002]->frames[1].centery = -1000; break;} Vrab0002 += 1;}}
     //-//
     //Characters' Hardcoded Speciality
    
     //-//
     //LF2: TD Mode
      if(Config.TD_Mode){Vrab0001 = 0; if(game->files->backgrounds[*(int*)0x44d024].bg_zwidth2 != game->files->backgrounds[*(int*)0x44d024].bg_zwidth1){switch(Config.TD_Post){case 0: Vrab0001 = game->files->backgrounds[*(int*)0x44d024].bg_zwidth2; break; case 1: Vrab0001 = game->files->backgrounds[*(int*)0x44d024].bg_zwidth1; break; case 2: Vrab0001 = (game->files->backgrounds[*(int*)0x44d024].bg_zwidth2 + game->files->backgrounds[*(int*)0x44d024].bg_zwidth1) / 2; break; default: break;} game->files->backgrounds[*(int*)0x44d024].bg_zwidth1 = Vrab0001; game->files->backgrounds[*(int*)0x44d024].bg_zwidth2 = Vrab0001;}}
      if(Config.Hold_Def) for(Vrab0002 = 0; Vrab0002 < MaximumObject; ++Vrab0002) Hold_Def_TU_Count[Vrab0002] = 0;
     //-//
     //LF2: Vampirism
      for(Vrab0002 = 0; Vrab0002 < MaximumObject; ++Vrab0002) Convertion[Vrab0002] = 0;
     //-//
     //LF2: Skill-Out
      for(Vrab0002 = 0; Vrab0002 < MaximumObject; ++Vrab0002) ReserveCount[Vrab0002] = 0; if(Config.B_Reserve > 1) for(Vrab0002 = 0; Vrab0002 < 20; ++Vrab0002){if(game->exists[Vrab0002]){ReserveCount[Vrab0002] = Config.B_Reserve;} else {ReserveCount[Vrab0002] = 0;}} if(Config.S_Reserve > 1 && *(int*)0x451160 == 1) for(Vrab0002 = 0; Vrab0002 < 20; ++Vrab0002){if(game->exists[Vrab0002]){ReserveCount[Vrab0002] += Config.S_Reserve;} else {ReserveCount[Vrab0002] = 0;}} if(Config.Dis_DHP) for(Vrab0002 = 0; Vrab0002 < MaximumObject; ++Vrab0002) Dis_DHP_HP_R[Vrab0002] = 0;
     //-//
     //Et Cetera
      //Input Fix
       if(Config.Dis_Il_Input) for(Vrab0002 = 0; Vrab0002 < 7; ++Vrab0002) for(Vrab0003 = 0; Vrab0003 < MaximumObject; ++Vrab0003) LastInput[Vrab0002][Vrab0003] = 0;
      //-//
      //Overlaying
       if(Config.Overlaying) if(!Overlay[*(int*)0x44d024]){Overlay[*(int*)0x44d024] = true; game->files->backgrounds[*(int*)0x44d024].bg_zwidth1 -= 50; game->files->backgrounds[*(int*)0x44d024].bg_zwidth2 += 50;}
      //-//
     //-//
   // }
   //-//
  }
  int0 Base_Redeclaration()
  {
   NumberOfExist = 0; NumberOfExistT0 = 0; NumberOfExistT0COM = 0;
   for(Vrab0002 = 0; Vrab0002 < MaximumObject; ++Vrab0002) if(game->exists[Vrab0002]) if(game->objects[Vrab0002]->frame1 != 9998 && game->objects[Vrab0002]->data->frames[game->objects[Vrab0002]->frame1].state != 9998)
   switch(game->objects[Vrab0002]->data->type)
   {
    case 0:
     if(Config.Full_Injection)
     {
      if(game->objects[Vrab0002]->data->id != Full_Injection_ID)
      {
       Database_Exist[NumberOfExist] = Vrab0002; NumberOfExist += 1;
       Database_ExistT0[NumberOfExistT0] = Vrab0002; NumberOfExistT0 += 1;
       if(Vrab0002 >= 10){Database_ExistT0COM[NumberOfExistT0COM] = Vrab0002; NumberOfExistT0COM += 1;}
      } else
      {
       game->objects[Vrab0002]->hp = 0; game->objects[Vrab0002]->mp = 0; game->objects[Vrab0002]->max_hp = 0; game->objects[Vrab0002]->team = (int32)MaximumObject - 1; game->objects[Vrab0002]->blink = -199;
       if(Vrab0002 >= 10)
       if(!InGame && game->objects[Vrab0002]->frame1 == 1)
       {
        InjectorNUM = Vrab0002; game->objects[Vrab0002]->frame1 = 237; InjectorFRAME = 237; InGame = true; Base_Reset(); if(InjectionDone){Vrab0003 = 0; while(game->files->datas[Vrab0003] != 0){if(game->files->datas[Vrab0003]->id == Full_Injection_ID2){game->files->datas[Vrab0003]->frames[0].pic = -1; break;} Vrab0003 += 1;}} else {InjectionDone = true;}
       } else
       {
        if((int32)Vrab0002 == InjectorNUM){if(InjectorFRAME == game->objects[Vrab0002]->frame1){InGame = false;} else {InGame = true;} if(InjectorFRAME == 237) InGame = true; InjectorFRAME = game->objects[Vrab0002]->frame1;}
       }
       Database_ExistT0COM[NumberOfExistT0COM] = Vrab0002; NumberOfExistT0COM += 1;
      }
     } else
     {
      Database_Exist[NumberOfExist] = Vrab0002; NumberOfExist += 1;
      Database_ExistT0[NumberOfExistT0] = Vrab0002; NumberOfExistT0 += 1;
      if(Vrab0002 >= 10){Database_ExistT0COM[NumberOfExistT0COM] = Vrab0002; NumberOfExistT0COM += 1;}
     }
    break;
    default:
     if(Config.Full_Injection){if(game->objects[Vrab0002]->data->id != Full_Injection_ID2){Database_Exist[NumberOfExist] = Vrab0002; NumberOfExist += 1;}} else
     {Database_Exist[NumberOfExist] = Vrab0002; NumberOfExist += 1;}
    break;
   }
  }
 //-//
 //Main Functions
  int0 Process(int32 Vrab01)
  {
   if(Config.Sleep_Mode) return;
   if(Database_First){Base_Redeclaration(); if(!Config.Full_Injection) Base_Reset(); Database_First = false;}
   if(Vrab01 == Database_ExistT0COM[NumberOfExistT0COM - 1]){if(InGame || (!InjectionDone && !InGame)) Base_Process(); Database_First = true;}
  }
  int0 Initialization()
  {
   I_Configuring();
   Console.Opening();
   I_Building();
   I_Installation();
   Console.Ending();
   if(Config.LoadDLL) LoadOtherDll();
  }
  int0 Hiding(){if(Config.LoadDLL) UnloadOtherDll(); if(Config.Storing.size() < 50) return; if(File0002.is_open()) File0002.close(); strcpy(Config.Key, "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"); File0002.open(Execute(TEMPORAL_FILE), std::ios::out | std::ios::binary); File0002 << "Do not erase this file.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" + DecryptionSTRING(Config.Storing) + "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"; File0002.close();}
  int0 Cleaning(){Console.Ending(); if(!Config.Permanentness){File0001.open(Config.Outsight); if(File0001.is_open()){File0001.close(); File0001.open(Config.Insight); if(File0001.is_open()){File0001.close(); std::remove(Config.Insight.c_str());} std::filesystem::copy_file(Config.Outsight, Config.Insight); std::remove(Config.Outsight.c_str());} File0001.open(Config.Output + "\\summary.edb"); if(File0001.is_open()){while(File0001){File0001 >> Temp0001; std::remove(Temp0001.c_str()); while(Temp0001 != ""){Vrab0002 = Temp0001.size() - 1; while(Temp0001[Vrab0002] != '\\' && Temp0001 != ""){Temp0001.pop_back(); Vrab0002 -= 1;} if(Temp0001 != ""){if(Temp0001[Vrab0002] == '\\') Temp0001.pop_back();} else {break;} if(Exist(Temp0001)){if((std::size_t)std::distance(std::filesystem::directory_iterator{Temp0001}, std::filesystem::directory_iterator{}) == 0){std::filesystem::remove_all(Temp0001.c_str());} else {break;}} else {break;}}} File0001.close(); std::remove((Config.Output + "\\summary.edb").c_str());}}}
 //-//
//-//