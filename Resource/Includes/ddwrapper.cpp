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

// Code
 // Commands
  #pragma warning (disable : 26438)
  #pragma warning (disable : 26446)
  #pragma warning (disable : 26482)

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

  #include <filesystem>
  #include <fstream>
  #include <sstream>
  #include <thread>
  #include <chrono>

  #define INJECTOR_VERSION "(v2.00.230101)"
  #define ENCODING_KEY "SiuHungIsAGoodBearBecauseHeIsVeryGood"
  #define TEMPORAL_FILE "data\\temporary.txt"
  #define CONFIGURATION "configuration.ini"
  #define BASE_ENCRYPTION "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
  #define SUPPORTED_ECD_VERSION "(v2.00.230101)"

  #define rint0 static_cast < void >
  #define rint1 static_cast < bool >
  #define rint8 static_cast < char >
  #define rint16 static_cast < short >
  #define rint32 static_cast < int >
  #define rint64 static_cast < long long >
  #define ruint8 static_cast < unsigned char >
  #define ruint16 static_cast < unsigned short >
  #define ruint32 static_cast < unsigned int >
  #define ruint64 static_cast < unsigned long long >
  #define rxint32 static_cast < float >
  #define rxint64 static_cast < xint64 >
  #define fastened noexcept

  using int0 = void;
  using int1 = bool;
  using int8 = char;
  using int16 = short;
  using int32 = int;
  using int64 = long long;
  using sint8 = signed char;
  using sint16 = signed short;
  using sint32 = signed int;
  using sint64 = signed long long;
  using uint8 = unsigned char;
  using uint16 = unsigned short;
  using uint32 = unsigned int;
  using uint64 = unsigned long long;
  using xint32 = float;
  using xint64 = double;
  using string = std::string;
  
  #pragma data_seg (".ddraw_shared")
   HINSTANCE Hins0002;
   HINSTANCE Hins0003;
  #pragma data_seg ()
  #ifdef DEBUG_VERSION
   #include <map>
   std::map < int32, FILETIME > Moti0001;
   std::map < int32, FILETIME > Moti0002;
  #endif
  #ifdef MULTI_STATE
   #define CONFIG_TEXT "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//                                  Configuration of Modified DDraw(ddraw.dll)                                  //\n//                                                " INJECTOR_VERSION "                                                //\n//                                                                                                              //\n//                                             Modified by Mesujin.                                             //\n//                                        \"I may to modify this, right?\"                                        //\n//                                                                                                              //\n// Credits (Original DDraw) : Doix, Som1Lse, zort, and everyone else who have an effort in it.                  //\n// *If you modify the credit, this file will be rewritten :P.                                                   //\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n////\n// Notes;\n// - For the Integer Values, it must be positive.\n// - \"//\" <-- this thing is used to give a comment in this file, basically the same as \"#\" in LF2's Data.\n// - If the Modified DDraw can't read the Value, this file will be rewritten without any warning. This file will\n//   also get rewritten when you switch to different version of Modified DDraw.\n// - If error occured during Modified DDraw load stuff, and then you can't run the LF2, remove \"status.edb\" file\n//   in output directory, but before removing it out, i would be happy if you would report me the \"log.log\" file.\n////\n\n// Main\n Determination, Active | Inactive    // Determining the \"true\" and \"false\" Value in this file.\n AI           : Active               //\n DLL          : Active               //\n ECD          : Active               // Both 'ECD' and 'MOD' is required for PCD (Packed Character Data) to work.\n MOD          : Active               // Both 'ECD' and 'MOD' is required for PCD (Packed Character Data) to work.\n Hidden_Mode  : Inactive             // IMPORTANT! Once this config is \"Active\", this configuration file will hide\n                                     //  in \"" TEMPORAL_FILE "\". To stop this configuration from hiding, you'll\n                                     //  need to delete that file.\n//-//\n\n// AI Injection\n AI_Console       : Inactive         //\n AI_ConsoleSize   : 60               //\n AI_ConsoleStyle  : 0                //\n AI_ConsoleScroll : Active           //\n AI_Directory     : add-on\\Script    //\n AI_OldDirectory  : ai               //\n//-//\n\n// DLL(s) Loader\n DLL_Directory   : add-on\\Library    //\n DLL_Progressive : Active            // In most cases, this one has no matter at all.\n//-//\n\n// ECD Usage\n ECD_Console         : Active        //\n ECD_ConsoleStyle    : 255           //\n ECD_ConsoleDelay    : 0             //\n ECD_ResultDirectory : add-on\\Output //\n\n // Construction\n  Directory : add-on\\Build           //\n //-//\n // Installation\n  Inputs          : add-on           //\n  Insight         : data\\data.txt    //\n  Outsight        : data\\data.temp   //\n  Overwrite       : Inactive         //\n  NoMirroring     : Inactive         //\n  Permanentness   : Inactive         //\n  DefaultLocation : Inactive         //\n  HiddenIDs       : 53  ~ 59         // ID range.\n  WeaponIDs       : 100 ~ 199        // ID range.\n  MinionIDs       : 30  ~ 37         // ID range.\n  MinionIDs2      : 39  ~ 39         // ID range.\n  AvailableIDs    : 9   ~ 29         // ID range.\n  AvailableIDs2   : 60  ~ 99         // ID range.\n  AvailableIDs3   : 230 ~ 998        // ID range.\n\n  CodeFormat      : 0                // 0 ~ 3; 0 = Single Lined; 1 = Casual; 2 = Mesujin's; 3 = STM93's;\n  Key             : " BASE_ENCRYPTION "\n //-//\n//-//\n\n// MOD Moduling\n MOD_Level         : 2               // 0 ~ 2;\n                                     //   0 = Only working when there's a COM;\n                                     //   1 = Need COM for once;\n                                     //   2 = Always working by creating clones of the datas at the earlier, this\n                                     //       process will take a while. (if you activate \"AI_Console\", you'll see\n                                     //       it's process, it'll also detect a syntax errors in your characters);\n MOD_StartingFrame : 219             // In a rare cases, you might need to change this into \"0\" instead.\n\n MOD_Info          : Active          // The pop-up notification on the corner.\n MOD_InfoTrans     : Active          //\n MOD_InfoPosition  : 130             //\n\n // Level 2 Moduling Result\n  ResultFormat    : 0                // 0 ~ 1; 0 = Single Lined; 1 = Mesujin's;\n  ResultFraming   : Inactive         // Rearrange the frame order based on their frame number.\n  ResultExtension : db               // This can't be \"dat\".\n  ResultDirectory : object           //\n //-//\n//-//\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
  #else
   #ifdef DEBUG_VERSION
    #define CONFIG_TEXT "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//                                  Configuration of Modified DDraw(ddraw.dll)                                  //\n//                                                " INJECTOR_VERSION "                                                //\n//                                                                                                              //\n//                                             Modified by Mesujin.                                             //\n//                                        \"I may to modify this, right?\"                                        //\n//                                                                                                              //\n// Credits (Original DDraw) : Doix, Som1Lse, zort, and everyone else who have an effort in it.                  //\n// *If you modify the credit, this file will be rewritten :P.                                                   //\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n////\n// Notes;\n// - For the Integer Values, it must be positive.\n// - \"//\" <-- this thing is used to give a comment in this file, basically the same as \"#\" in LF2's Data.\n// - If the Modified DDraw can't read the Value, this file will be rewritten without any warning. This file will\n//   also get rewritten when you switch to different version of Modified DDraw.\n// - If error occured during Modified DDraw load stuff, and then you can't run the LF2, remove \"status.edb\" file\n//   in output directory, but before removing it out, i would be happy if you would report me the \"log.log\" file.\n////\n\n// Main\n Determination, Active | Inactive    // Determining the \"true\" and \"false\" Value in this file.\n AI           : Active               //\n DLL          : Active               //\n ECD          : Active               // Both 'ECD' and 'MOD' is required for PCD (Packed Character Data) to work.\n MOD          : Active               // Both 'ECD' and 'MOD' is required for PCD (Packed Character Data) to work.\n Hidden_Mode  : Inactive             // IMPORTANT! Once this config is \"Active\", this configuration file will hide\n                                     //  in \"" TEMPORAL_FILE "\". To stop this configuration from hiding, you'll\n                                     //  need to delete that file.\n//-//\n\n// AI Injection\n AI_ConsoleSize   : 60               //\n AI_ConsoleStyle  : 0                //\n AI_ConsoleScroll : Active           //\n AI_Directory     : add-on\\Script    //\n AI_OldDirectory  : ai               //\n//-//\n\n// DLL(s) Loader\n DLL_Directory   : add-on\\Library    //\n DLL_Progressive : Active            // In most cases, this one has no matter at all.\n//-//\n\n// ECD Usage\n ECD_Console         : Active        //\n ECD_ConsoleStyle    : 255           //\n ECD_ConsoleDelay    : 0             //\n ECD_ResultDirectory : add-on\\Output //\n\n // Construction\n  Directory : add-on\\Build           //\n //-//\n // Installation\n  Inputs          : add-on           //\n  Insight         : data\\data.txt    //\n  Outsight        : data\\data.temp   //\n  Overwrite       : Inactive         //\n  NoMirroring     : Inactive         //\n  Permanentness   : Inactive         //\n  DefaultLocation : Inactive         //\n  HiddenIDs       : 53  ~ 59         // ID range.\n  WeaponIDs       : 100 ~ 199        // ID range.\n  MinionIDs       : 30  ~ 37         // ID range.\n  MinionIDs2      : 39  ~ 39         // ID range.\n  AvailableIDs    : 9   ~ 29         // ID range.\n  AvailableIDs2   : 60  ~ 99         // ID range.\n  AvailableIDs3   : 230 ~ 998        // ID range.\n\n  CodeFormat      : 0                // 0 ~ 3; 0 = Single Lined; 1 = Casual; 2 = Mesujin's; 3 = STM93's;\n  Key             : " BASE_ENCRYPTION "\n //-//\n//-//\n\n// MOD Moduling\n MOD_Level         : 2               // 0 ~ 2;\n                                     //   0 = Only working when there's a COM;\n                                     //   1 = Need COM for once;\n                                     //   2 = Always working by creating clones of the datas at the earlier, this\n                                     //       process will take a while. (if you activate \"AI_Console\", you'll see\n                                     //       it's process, it'll also detect a syntax errors in your characters);\n MOD_StartingFrame : 219             // In a rare cases, you might need to change this into \"0\" instead.\n\n MOD_Info          : Active          // The pop-up notification on the corner.\n MOD_InfoTrans     : Active          //\n MOD_InfoPosition  : 130             //\n\n // Level 2 Moduling Result\n  ResultFormat    : 0                // 0 ~ 1; 0 = Single Lined; 1 = Mesujin's;\n  ResultFraming   : Inactive         // Rearrange the frame order based on their frame number.\n  ResultExtension : db               // This can't be \"dat\".\n  ResultDirectory : object           //\n //-//\n//-//\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
   #else
    #define CONFIG_TEXT "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//                                  Configuration of Modified DDraw(ddraw.dll)                                  //\n//                                                " INJECTOR_VERSION "                                                //\n//                                                                                                              //\n//                                             Modified by Mesujin.                                             //\n//                                        \"I may to modify this, right?\"                                        //\n//                                                                                                              //\n// Credits (Original DDraw) : Doix, Som1Lse, zort, and everyone else who have an effort in it.                  //\n// *If you modify the credit, this file will be rewritten :P.                                                   //\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n////\n// Notes;\n// - For the Integer Values, it must be positive.\n// - \"//\" <-- this thing is used to give a comment in this file, basically the same as \"#\" in LF2's Data.\n// - If the Modified DDraw can't read the Value, this file will be rewritten without any warning. This file will\n//   also get rewritten when you switch to different version of Modified DDraw.\n// - If error occured during Modified DDraw load stuff, and then you can't run the LF2, remove \"status.edb\" file\n//   in output directory, but before removing it out, i would be happy if you would report me the \"log.log\" file.\n////\n\n// Main\n Determination, Active | Inactive    // Determining the \"true\" and \"false\" Value in this file.\n AI           : Active               //\n DLL          : Active               //\n ECD          : Active               // Both 'ECD' and 'MOD' is required for PCD (Packed Character Data) to work.\n MOD          : Active               // Both 'ECD' and 'MOD' is required for PCD (Packed Character Data) to work.\n Hidden_Mode  : Inactive             // IMPORTANT! Once this config is \"Active\", this configuration file will hide\n                                     //  in \"" TEMPORAL_FILE "\". To stop this configuration from hiding, you'll\n                                     //  need to delete that file.\n//-//\n\n// AI Injection\n AI_Directory    : add-on\\Script     //\n AI_OldDirectory : ai                //\n//-//\n\n// DLL(s) Loader\n DLL_Directory   : add-on\\Library    //\n DLL_Progressive : Active            // In most cases, this one has no matter at all.\n//-//\n\n// ECD Usage\n ECD_Console         : Active        //\n ECD_ConsoleStyle    : 255           //\n ECD_ConsoleDelay    : 0             //\n ECD_ResultDirectory : add-on\\Output //\n\n // Construction\n  Directory : add-on\\Build           //\n //-//\n // Installation\n  Inputs          : add-on           //\n  Insight         : data\\data.txt    //\n  Outsight        : data\\data.temp   //\n  Overwrite       : Inactive         //\n  NoMirroring     : Inactive         //\n  Permanentness   : Inactive         //\n  DefaultLocation : Inactive         //\n  HiddenIDs       : 53  ~ 59         // ID range.\n  WeaponIDs       : 100 ~ 199        // ID range.\n  MinionIDs       : 30  ~ 37         // ID range.\n  MinionIDs2      : 39  ~ 39         // ID range.\n  AvailableIDs    : 9   ~ 29         // ID range.\n  AvailableIDs2   : 60  ~ 99         // ID range.\n  AvailableIDs3   : 230 ~ 998        // ID range.\n\n  CodeFormat      : 0                // 0 ~ 3; 0 = Single Lined; 1 = Casual; 2 = Mesujin's; 3 = STM93's;\n  Key             : " BASE_ENCRYPTION "\n //-//\n//-//\n\n// MOD Moduling\n MOD_Level         : 2               // 0 ~ 2;\n                                     //   0 = Only working when there's a COM;\n                                     //   1 = Need COM for once;\n                                     //   2 = Always working by creating clones of the datas at the earlier, this\n                                     //       process will take a while. (if you activate \"AI_Console\", you'll see\n                                     //       it's process, it'll also detect a syntax errors in your characters);\n MOD_StartingFrame : 219             // In a rare cases, you might need to change this into \"0\" instead.\n\n MOD_Info          : Active          // The pop-up notification on the corner.\n MOD_InfoTrans     : Active          //\n MOD_InfoPosition  : 130             //\n\n // Level 2 Moduling Result\n  ResultFormat    : 0                // 0 ~ 1; 0 = Single Lined; 1 = Mesujin's;\n  ResultFraming   : Inactive         // Rearrange the frame order based on their frame number.\n  ResultExtension : db               // This can't be \"dat\".\n  ResultDirectory : object           //\n //-//\n//-//\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
   #endif
  #endif
 //-//
 // Temporals
  int32 Vrab0001;
  int32 Vrab0002;
  int32 Vrab0003;
  std::ifstream File0001;
  std::ofstream File0002;
  std::vector < int32 > Vect0001;
  std::vector < string > Strn0001;
  std::vector < HINSTANCE > Hins0001;
 //-//
 // Declaration
  int1   M_EncryptionFile(const uint8, string);

  int1   L_Rebuilding(int32, const string&);
  int32  L_Numbering(string) fastened;
  int32  L_Rounding(xint64) fastened;
  uint32 L_Address(int32) fastened;
  string L_Lowercase(string) fastened;
  string L_Execute(const string);
  string L_Moduling(const string&);

  int0   G_Starting();
  int0   G_Cleaning();
  int0   G_Process(int32) fastened;
  int0   G_Initialization();
  int0   G_Hiding();
  int0   G_Cleaning();
  int0   G_Encryption(uint8, std::string);
  int32  (__stdcall *AI_o)(int32, int32, int32, int32, int32, int32, int32);
  int32  (__stdcall *AIa_o)(int32, int32);
 //-//
 // Structures
  struct MD_CONFIG 
  {
   int1   MAIN_AI = true;
   int1   MAIN_DLL = true;
   int1   MAIN_ECD = true;
   int1   MAIN_MOD = true;
   int1   MAIN_HiddenMode = false;

   int1   AI_Console = true;
   int1   AI_ConsoleScroll = true;
   int8   AI_ConsoleStyle = 0;
   int16  AI_ConsoleSize = 80;
   string AI_Directory;
   string AI_OldDirectory = "ai";

   int1   DLL_Progressive = true;
   string DLL_Directory;

   int1   ECD_Console = true;
   int16  ECD_ConsoleStyle = 0;
   int16  ECD_ConsoleDelay = 0;

   int8   ECD_ResultCodeFormat = 0;
   int8   ECD_ResultEncryption[95]{};
   string ECD_ResultDirectory;

   string ECD_BuildDirectory;

   int1   ECD_InstallOverwrite = false;
   int1   ECD_InstallNoMirrors = false;
   int1   ECD_InstallSeparated = false;
   int1   ECD_InstallPermanent = false;
   int32  ECD_InstallDataIDs[14]{};
   string ECD_InstallDirectory;
   string ECD_InstallDataDirectory;
   string ECD_InstallODataDirectory;

   int8   MOD_ModulingLevel = 2;
   int32  MOD_ModulingLevelStartingFrame = 219;
   
   int1   MOD_ModulingInfo = true;
   int1   MOD_ModulingInfoTrans = true;
   int32  MOD_ModulingInfoPostition = 130;

   int1   MOD_ResultFraming = false;
   int32  MOD_ResultFormat = 0;
   string MOD_ResultExtension = ".db";
   string MOD_ResultDirectory = "object";
  }; MD_CONFIG Config;
  struct MD_CONSOLE
  {
   int0 PrintWrite(const string Temp01){if(!Config.MAIN_ECD && !Config.ECD_Console) return; Temp001 += Temp01; std::ofstream File01(Execute(Config.ECD_ResultDirectory + "\\log.log"), std::ios::binary | std::ios::app); File01 << Temp01; File01.close();}
   int0 PrintSet(){Vrab002 = true; PrintOut(); Vrab002 = false;}
   int0 PrintOut()
   {
    if(!Config.MAIN_ECD) return;
    if(!Config.ECD_Console) return; if(!Vrab001) Opening(); 
   
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    std::ostringstream Ostr01;
    if(Vrab002)
    {
     Ostr01 << "\n==== Building Log ===============================\n\n"; if(Vrab003){if(Temp001 != "") Strn001[0] += Temp001 + "\n=================================================\n\n==== Building Log ===============================\n\n"; Temp001.clear(); Vrab003 = false; return;} Vrab003 = false;
    } else 
    {
     Ostr01 << "\n==== Installation Log ===========================\n\n"; if(!Vrab003){if(Temp001 != "") Strn001[0] += Temp001 + "\n=================================================\n\n==== Installation Log ===========================\n\n"; Temp001.clear(); Vrab003 = true; return;} Vrab003 = true;
    }

    string Strn01; string Strn02;
    uint32 Varb01 = 0; uint16 Varb02 = 0; int32 Varb03 = (int32)Temp001.size(); int32 Varb04 = 0; int32 Varb05 = 0; while(Varb01 < (uint32)Varb03){Varb04 += 1; if(Temp001[Varb01] == (int8)-125) Varb04 = 0; if(Temp001[Varb01] == '\n'){if(Varb04 == 1){Temp001[Varb01] = (int8)-125; Varb02 -= 1;} Varb04 = 0; Varb02 += 1;} if((uint32)Varb04 >= (uint32)(Vrab004 - 0)){if(Temp001[Varb01 + 1] != '\n' && Temp001[Varb01 + 1] != (int8)-125){Varb04 = 0; while((Temp001[Varb01 + 1] != ' ' && Temp001[Varb01 + 1] >= 0) || Temp001[Varb01 + 2] != ' ' || Temp001[Varb01 + 3] != ' '){Temp001.insert(Varb01 + 1, " "); Varb04 -= 25;} if(Varb04 != 0) Temp001[Varb01 + 1] = (int8)Varb04;} Varb04 = 0; Varb02 += 1; Varb03 = (int32)Temp001.size();} Varb01 += 1;} while(Varb02 >= (uint16)((Vrab004 / 2) - 4)){Varb01 = 0; Varb04 = 0; Varb03 = (int32)Temp001.size(); while(Varb01 < (uint32)Varb03){Varb04 += 1; if(Temp001[Varb01] == (int8)-125) Varb04 -= 1; if(Temp001[Varb01] == '\n') break; if((uint32)Varb04 >= (uint32)(Vrab004 - 0)) break; Varb01 += 1;} Strn001[0].append(Temp001, 0, Varb01 + 1); if(Strn001[0].size() >= 30000){Strn001.push_back(Strn001[0]); Strn001[0] = "";} Temp001.erase(0, Varb01 + 1); Varb02 -= 1;} Strn01 = Temp001; Varb03 = (int32)Strn01.size(); for(Varb01 = 0; Varb01 < (uint32)Varb03; ++Varb01){if(Strn01[Varb01] == (int8)-125){Strn01.erase(Varb01, 1); Varb03 = (int32)Strn01.size();} if(Strn01[Varb01] < 0) Strn01[Varb01] = ' ';} Ostr01 << Strn01; Varb03 = 20; while(Varb03 > Varb02){Ostr01 << "\n"; Varb03 -= 1;} Ostr01 << "\n================================================="; Strn02 = ""; Strn01 = Ostr01.str().c_str(); Ostr01.str(""); Varb01 = Strn01.length(); Varb03 = 0; Varb04 = 0; Varb02 = 0; while((uint32)Varb03 != Varb01){if(Strn01[Varb03] == '\n'){Varb05 = (int32)Varb02; if(Vect001.size() > (uint32)Varb04) while(Varb02 < Vect001[Varb04]){Strn02 += " "; Varb02 += 1;} if(Varb02 < Vrab004) Strn02 += "\n"; if(Vect001.size() <= (uint32)Varb04){Vect001.push_back((uint16)Varb05);} else {Vect001[Varb04] = (uint16)Varb05;} Varb04 += 1; Varb02 = 65535;} else {Strn02 += Strn01[Varb03];} Varb02 += 1; if(Varb02 == Vrab004){Varb02 = 0; if(Vect001.size() <= (uint32)Varb04){Vect001.push_back(Vrab004);} else {Vect001[Varb04] = Vrab004;} Varb04 += 1;} Varb03 += 1;} Varb05 = (int32)Varb02; if(Vect001.size() > (uint32)Varb04) while(Varb02 < Vect001[Varb04]){Strn02 += " "; Varb02 += 1;} if(Varb02 < Vrab004) Strn02 += "\n"; if(Vect001.size() <= (uint32)Varb04){Vect001.push_back((uint16)Varb05);} else {Vect001[Varb04] = (uint16)Varb05;} Varb04 += 1; Varb05 = Varb04; while((uint32)Varb04 < Vect001.size()){Varb02 = 0; while(Varb02 < Vect001[Varb04]){Strn02 += " "; Varb02 += 1;} if(Varb02 < Vrab004) if((uint32)Varb04 + 1 < Vect001.size()) Strn02 += "\n"; Varb04 += 1;} std::cout << Strn02; Strn01 = ""; Strn02 = ""; Vect001.resize(Varb05);

    std::this_thread::sleep_for(std::chrono::milliseconds(Config.ECD_ConsoleDelay));
   }
  
   int0 Starting(){std::ifstream File01(Config.ECD_ResultDirectory + "\\status.edb"); if(File01.is_open()){File01.close(); std::terminate();} std::ofstream File02(Execute(Config.ECD_ResultDirectory + "\\status.edb"), std::ios::binary | std::ios::out); File02 << "Do not erase this file."; File02.close(); File02.open(Execute(Config.ECD_ResultDirectory + "\\log.log"), std::ios::binary | std::ios::out); File02 << "Critical error occured in the system, please report this file to the developer of Modified DDraw, Mesujin.\n\n\n"; File02.close();}
   int0 Ending()
   {
    std::ifstream File01(Config.ECD_ResultDirectory + "\\status.edb"); if(File01.is_open()){File01.close(); std::remove((Config.ECD_ResultDirectory + "\\status.edb").c_str());}
    
    if(!Config.ECD_Console) return; if(Vrab001)
    {
     Strn001[0] += Temp001 + "\n=================================================\n\n"; Temp001.clear(); uint32 Vrab02 = 0;
     for(uint32 Vrab01 = Strn001.size() - 1; Vrab01 != -1; --Vrab01) 
     while(Vrab02 < Strn001[Vrab01].size())
     {
      if(Strn001[Vrab01].at(Vrab02) == -125) Strn001[Vrab01].at(Vrab02) = '\n'; 
      if(Strn001[Vrab01].at(Vrab02) < 0) Strn001[Vrab01].erase(Vrab02, -(Strn001[Vrab01].at(Vrab02) / 25));
      Vrab02 += 1;
     }
     std::ofstream File02(Execute(Config.ECD_ResultDirectory + "\\log.log"), std::ios::binary | std::ios::out);
     const auto Vrab03 = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); File02 << std::ctime(&Vrab03) << "\n";
     Vrab02 = 1; while(Vrab02 < Strn001.size()){File02 << Strn001[Vrab02]; Strn001[Vrab02].clear(); Vrab02 += 1;}
     File02 << Strn001[0]; Strn001[0].clear(); Strn001.clear(); File01.close(); 
     ShowWindow(GetConsoleWindow(), 0); FreeConsole(); Vrab001 = false;
    }
   }
   private:
    int1 Vrab001 = false;
    int1 Vrab002 = false;
    int1 Vrab003 = false;
    int16 Vrab004 = 50;
    string Temp001;
    std::vector < uint16 > Vect001;
    std::vector < string > Strn001;
    
    int0 Opening(){Strn001.clear(); if(Vrab002){Strn001.push_back("==== Building Log ===============================\n\n");} else {Strn001.push_back("==== Installation Log ===========================\n\n");} const uint8 Vrab01 = Config.ECD_ConsoleStyle & 0xFF; uint8 Vrab02 = 0; if(Vrab01 < 128){Vrab02 = 255;} else {Vrab02 = 0;} AllocConsole(); HANDLE Hand01 = GetStdHandle(STD_OUTPUT_HANDLE); freopen("CONIN$", "rb", stdin); freopen("CONOUT$", "wb", stdout); freopen("CONOUT$", "wb", stderr); SMALL_RECT Rect01 = {0, 0, Vrab004, 28}; CONSOLE_SCREEN_BUFFER_INFOEX Info01; Info01.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX); SetConsoleScreenBufferSize(Hand01, {Vrab004, 26}); GetConsoleScreenBufferInfoEx(Hand01, &Info01); Info01.wAttributes = true; Info01.srWindow = Rect01; Info01.ColorTable[0] = RGB((int32)Vrab01, (int32)Vrab01, (int32)Vrab01); Info01.ColorTable[1] = RGB((int32)Vrab02, (int32)Vrab02, (int32)Vrab02); Info01.ColorTable[7] = Info01.ColorTable[1]; SetConsoleScreenBufferInfoEx(Hand01, &Info01); SetConsoleScreenBufferSize(Hand01, {Vrab004, 26}); SetConsoleTitleA("ECD's Console"); Vrab001 = true;}
    string Execute(string Temp01){string Temp02 = Temp01; uint32 Vrab01 = Temp02.size() - 1; while(Vrab01 != 0 && Temp02.at(Vrab01) != '\\') Vrab01 -= 1; if(Vrab01 > 0) Temp02.erase(Vrab01, Temp02.size() - Vrab01); std::filesystem::create_directories(Temp02); return Temp01; }
  }; MD_CONSOLE Console;
  struct MD_CONTROLS 
  {

  }; MD_CONTROLS Control;
  struct MD_DATABASES {string Config; int1 InGame = false; int1 OutGame = true; int1 Reset = false; int1 First = true; int1 Done = false; int1 Init = true; int32 InjectorDATA = 0; int32 InjectorNUM = -1; int32 InjectorFRAME = 99999; int32 InjectorID = -1; int32 InjectorID2 = -1; uint32 Exist[MaximumObject]{}; uint32 ExistT0[MaximumObject]{}; uint32 ExistT0COM[MaximumObject]{}; uint32 NumberOfExist = 0; uint32 NumberOfExistT0 = 0; uint32 NumberOfExistT0COM = 0;}; MD_DATABASES Database;
  struct MD_AIDATABASES
  {
   uint32 MaximumFrame = MaximumFrames;
   uint32 MaximumObj = MaximumObject;
   int32  MaximumMP = MaximumManaPoint;

   int32  ModuleID = 0;
   MD_GAME *Game = (MD_GAME*)0x458b00; //0x44d024;

   #ifdef _MD_OLD_SCRIPT
    uint32 ElapsedTime = 0;
    int32  Mode = 0;
    int32  Difficulty = 0;
    int32  BackgroundID = -1;
    int32  Background_width = 0;
    int32  Background_zwidth1 = 0;
    int32  Background_zwidth2 = 0;
    int32  Stage = 0;
    int1   Stage_clear = 0;
    int32  Stage_bound = 0;
    int32  Phase = 0;
    int32  Phase_Count = 0;
    int32  User = -1;
    sGame *game = (sGame*)0x458b00;
   #endif

   asIScriptModule  *Modu0001 = NULL;
   asIScriptEngine  *Engi0001 = NULL;
   asIScriptEngine  *Engi0002 = NULL;
   asIScriptContext *Cont0001 = NULL;
   asIScriptContext *Cont0002 = NULL;
  
   int1   L_Copy(uint32 Vrab01, uint32 Vrab02, uint32 Vrab03) fastened {if(Game->Database->Data[Vrab01] == 0) return false; if(Vrab02 >= MaximumFrames || Vrab02 < 0 || Vrab03 >= MaximumFrames || Vrab03 < 0) return false; Game->Database->Data[Vrab01]->Frame[Vrab03] = Game->Database->Data[Vrab01]->Frame[Vrab02]; return true;}
   int1   L_Copys(uint32 Vrab01, uint32 Vrab02, uint32 Vrab03, uint32 Vrab04) fastened {if(Game->Database->Data[Vrab01] == 0 || Game->Database->Data[Vrab02] == 0) return false; if(Vrab03 >= MaximumFrames || Vrab03 < 0 || Vrab04 >= MaximumFrames || Vrab04 < 0) return false; Game->Database->Data[Vrab02]->Frame[Vrab04] = Game->Database->Data[Vrab01]->Frame[Vrab03]; return true;}
   uint32 L_Address(int32 Vrab01) fastened {uint32 Vrab02 = 0; while(Game->Database->Data[Vrab02] != 0){if(Game->Database->Data[Vrab02]->id == Vrab01) return Vrab02; Vrab02 += 1;} return ruint32(-1);}
   int32  L_Random(int32 Vrab01)  fastened
   {
    int32  Vrab02 = 0;  // eax@2
    sint32 Vrab03 = 0; // eax@3
    DWORD  &Dwrd01 = *((DWORD*)0x450C34);
    DWORD  &Dwrd02 = *((DWORD*)0x450BCC);
    if(Vrab01 > 0)
    {
     Dwrd01 = (Dwrd01 + 1) % 1234;
     Vrab03 = Dwrd01 + (unsigned __int8)*(((BYTE*)0x44FF90) + (Dwrd02 + 1) % 3000);
     Dwrd02 = (Dwrd02 + 1) % 3000;
     Vrab02 = Vrab03 % Vrab01;
    } else {Vrab02 = 0;}
    return Vrab02;
   }
   uint32 L_Generate(int32 Vrab01, int32 Vrab02, int32 Vrab03, xint64 Vrab04, xint64 Vrab05, xint64 Vrab06, uint8 Vrab07) fastened
   {
    if(Vrab01 < 0 || Vrab01 >= MaximumObject) return ruint32(-1);
    uint32 Vrab08 = MaximumObject - 1;
    while(Vrab08 > 49)
    {
     if(!Game->Object_Exist[Vrab08])
     {
      if(Database.InjectorNUM == -1) break;
      if(Vrab08 != ruint32(Database.InjectorNUM)) break;
     }
     Vrab08 -= 1;
    }
    if(Vrab08 == 49) return ruint32(-1);
    //Game->Object[Vrab08] = Game->Object[ruint32(Vrab01)];
    Game->Object_Exist[Vrab08] = Game->Object_Exist[ruint32(Vrab01)];
    *Game->Object[Vrab08]->Data = *Game->Database->Data[ruint32(Vrab02)];
    if(Vrab03 < 0){Game->Object[Vrab08]->Frame = -Vrab03;} else {Game->Object[Vrab08]->Frame = Vrab03;}
    Game->Object[Vrab08]->Facing = Vrab07;
    Game->Object[Vrab08]->X = Vrab04;
    Game->Object[Vrab08]->Y = Vrab05;
    Game->Object[Vrab08]->Z = Vrab06;
    Game->Object[Vrab08]->Health = 500;
    if(Game->Object[Vrab08]->Data->type == 0){Game->Object[Vrab08]->Potential_Health = 500;} else {Game->Object[Vrab08]->Potential_Health = 0;}
    Game->Object[Vrab08]->Max_Health = 500;
    Game->Object[Vrab08]->Mana = MaximumMP;
    Game->Object[Vrab08]->X_Acceleration = 0;
    Game->Object[Vrab08]->Y_Acceleration = 0;
    Game->Object[Vrab08]->Z_Acceleration = 0;
    Game->Object[Vrab08]->X_Velocity = 0;
    Game->Object[Vrab08]->Y_Velocity = 0;
    Game->Object[Vrab08]->Z_Velocity = 0;
    Game->Object[Vrab08]->X_Display = L_Rounding(Vrab04);
    Game->Object[Vrab08]->Y_Display = L_Rounding(Vrab05);
    Game->Object[Vrab08]->Z_Display = L_Rounding(Vrab06);
    Game->Object[Vrab08]->Summary_Host = Vrab01;
    Game->Object[Vrab08]->Attack_Rest = 0;
    for(uint32 Vrab09 = 0; Vrab09 < MaximumObject; ++Vrab09) Game->Object[Vrab08]->Hit_Rest[Vrab09] = 0;
    Game->Object[Vrab08]->Caught = -1;
    Game->Object[Vrab08]->Holder = -1;
    Game->Object[Vrab08]->Cloner = -1;
    Game->Object[Vrab08]->Frame_Calculation = Game->Object[Vrab08]->Frame;
    Game->Object[Vrab08]->Frame_Hit = 0;
    Game->Object[Vrab08]->Frame_Last = 0;
    Game->Object[Vrab08]->Held = 0;
    Game->Object[Vrab08]->Held_Type = -1;
    Game->Object[Vrab08]->Hitlag = 0;
    Game->Object[Vrab08]->Invisibility = 0;
    Game->Object[Vrab08]->Pic_Offset = 0;
    Game->Object[Vrab08]->Target = -1;
    Game->Object[Vrab08]->Team = Game->Object[Vrab01]->Team;
    Game->Object[Vrab08]->Reserve = 0;
    Game->Object[Vrab08]->Thrower = -1;
    Game->Object[Vrab08]->Thrown_Drop_Damage = 0;
    Game->Object[Vrab08]->Catch = -1;
    Game->Object[Vrab08]->Summary_Attack = 0;
    Game->Object[Vrab08]->Summary_HP_Lost = 0;
    Game->Object[Vrab08]->Summary_Kill = 0;
    Game->Object[Vrab08]->Summary_MP_Usage = 0;
    Game->Object[Vrab08]->Summary_Picking = 0;
    for(uint32 Vrab09 = 0; Vrab09 < MaximumObject; ++Vrab09) Game->Object[Vrab09]->Hit_Rest[Vrab08] = 0;
    for(uint32 Vrab09 = 0; Vrab09 < MaximumObject; ++Vrab09) if(Game->Object[Vrab09]->Target == rint32(Vrab08)) Game->Object[Vrab09]->Target = -1;
    for(uint32 Vrab09 = 0; Vrab09 < MaximumObject; ++Vrab09) if(Game->Object[Vrab09]->Thrower == rint32(Vrab08)) Game->Object[Vrab09]->Thrower = -1;
    for(uint32 Vrab09 = 0; Vrab09 < MaximumObject; ++Vrab09) if(Game->Object[Vrab09]->Held == rint32(Vrab08)){Game->Object[Vrab09]->Held = 0; Game->Object[Vrab09]->Held_Type = -1;}
    return Vrab08;
   }
   int32  L_Aggring(int32 Vrab01) fastened {if(User == -1) return -1; if(Vrab01 < 0 || Vrab01 >= MaximumObject) return -1; if(!Game->Object_Exist[Vrab01]) return -1; return (Game->Object[User]->Target = Vrab01);}
   int0   L_InputClear()          fastened {if(User == -1) return; Game->Object[User]->Up = 0; Game->Object[User]->Left = 0; Game->Object[User]->Down = 0; Game->Object[User]->Right = 0; Game->Object[User]->A = 0; Game->Object[User]->D = 0; Game->Object[User]->J = 0; Game->Object[User]->Up_Hold = 0; Game->Object[User]->Left_Hold = 0; Game->Object[User]->Down_Hold = 0; Game->Object[User]->Right_Hold = 0; Game->Object[User]->A_Hold = 0; Game->Object[User]->D_Hold = 0; Game->Object[User]->J_Hold = 0;}
   int0   L_InputUP()             fastened {if(User == -1) return; if(Game->Object[User]->Up == 0){Game->Object[User]->Up = 1;} else {Game->Object[User]->Up = 0;}}
   int0   L_InputLEFT()           fastened {if(User == -1) return; if(Game->Object[User]->Left == 0){Game->Object[User]->Left = 1;} else {Game->Object[User]->Left = 0;}}
   int0   L_InputDOWN()           fastened {if(User == -1) return; if(Game->Object[User]->Down == 0){Game->Object[User]->Down = 1;} else {Game->Object[User]->Down = 0;}}
   int0   L_InputRIGHT()          fastened {if(User == -1) return; if(Game->Object[User]->Right == 0){Game->Object[User]->Right = 1;} else {Game->Object[User]->Right = 0;}}
   int0   L_InputATTACK()         fastened {if(User == -1) return; if(Game->Object[User]->A == 0){Game->Object[User]->A = 1;} else {Game->Object[User]->A = 0;}}
   int0   L_InputDEFEND()         fastened {if(User == -1) return; if(Game->Object[User]->D == 0){Game->Object[User]->D = 1;} else {Game->Object[User]->D = 0;}}
   int0   L_InputJUMP()           fastened {if(User == -1) return; if(Game->Object[User]->J == 0){Game->Object[User]->J = 1;} else {Game->Object[User]->J = 0;}}
   int0   L_InputUPH()            fastened {if(User == -1) return; if(Game->Object[User]->Up == 0){Game->Object[User]->Up = 1;} else {Game->Object[User]->Up_Hold = 1;}}
   int0   L_InputLEFTH()          fastened {if(User == -1) return; if(Game->Object[User]->Left == 0){Game->Object[User]->Left = 1;} else {Game->Object[User]->Left_Hold = 1;}}
   int0   L_InputDOWNH()          fastened {if(User == -1) return; if(Game->Object[User]->Down == 0){Game->Object[User]->Down = 1;} else {Game->Object[User]->Down_Hold = 1;}}
   int0   L_InputRIGHTH()         fastened {if(User == -1) return; if(Game->Object[User]->Right == 0){Game->Object[User]->Right = 1;} else {Game->Object[User]->Right_Hold = 1;}}
   int0   L_InputATTACKH()        fastened {if(User == -1) return; if(Game->Object[User]->A == 0){Game->Object[User]->A = 1;} else {Game->Object[User]->A_Hold = 1;}}
   int0   L_InputDEFENDH()        fastened {if(User == -1) return; if(Game->Object[User]->D == 0){Game->Object[User]->D = 1;} else {Game->Object[User]->D_Hold = 1;}}
   int0   L_InputJUMPH()          fastened {if(User == -1) return; if(Game->Object[User]->J == 0){Game->Object[User]->J = 1;} else {Game->Object[User]->J_Hold = 1;}}
   int0   L_InputDRA()            fastened {if(User == -1) return; Game->Object[User]->Cast_DRA = 3;}
   int0   L_InputDLA()            fastened {if(User == -1) return; Game->Object[User]->Cast_DLA = 3;}
   int0   L_InputDUA()            fastened {if(User == -1) return; Game->Object[User]->Cast_DUA = 3;}
   int0   L_InputDDA()            fastened {if(User == -1) return; Game->Object[User]->Cast_DDA = 3;}
   int0   L_InputDRJ()            fastened {if(User == -1) return; Game->Object[User]->Cast_DRJ = 3;}
   int0   L_InputDLJ()            fastened {if(User == -1) return; Game->Object[User]->Cast_DLJ = 3;}
   int0   L_InputDUJ()            fastened {if(User == -1) return; Game->Object[User]->Cast_DUJ = 3;}
   int0   L_InputDDJ()            fastened {if(User == -1) return; Game->Object[User]->Cast_DDJ = 3;}
   int0   L_InputDJA()            fastened {if(User == -1) return; Game->Object[User]->Cast_DJA = 3;}
   int0   C_Clear() fastened
   {
    HANDLE Hand01 = GetStdHandle(STD_OUTPUT_HANDLE);
    if(Hand01 == INVALID_HANDLE_VALUE) return;
    const COORD Cord01 = {0, 0};
    DWORD Dwrd01, Dwrd02;
    CONSOLE_SCREEN_BUFFER_INFO Csbi01;
    if(!GetConsoleScreenBufferInfo(Hand01, &Csbi01)){return;}
    Dwrd02 = Csbi01.dwSize.X * Csbi01.dwSize.Y;
    if(!FillConsoleOutputCharacterA(Hand01, ' ', Dwrd02, Cord01, &Dwrd01)){return;}
    SetConsoleCursorPosition(Hand01, Cord01);
   }
   int0   C_PrintAddr(const int0 *Vrab01)    fastened {printf("%p", Vrab01);}
   int0   C_Print(const int1 Vrab01)         fastened {if(Vrab01){printf("true");} else {printf("false");}}
   int0   C_Print(const int8 Vrab01)         fastened {printf("%i", Vrab01);}
   int0   C_Print(const int16 Vrab01)        fastened {printf("%i", Vrab01);}
   int0   C_Print(const int32 Vrab01)        fastened {printf("%i", Vrab01);}
   int0   C_Print(const int64 Vrab01)        fastened {printf("%lli", Vrab01);}
   int0   C_Print(const uint8 Vrab01)        fastened {printf("%u", Vrab01);}
   int0   C_Print(const uint16 Vrab01)       fastened {printf("%u", Vrab01);}
   int0   C_Print(const uint32 Vrab01)       fastened {printf("%u", Vrab01);}
   int0   C_Print(const uint64 Vrab01)       fastened {printf("%llu", Vrab01);}
   int0   C_Print(const xint32 Vrab01)       fastened {printf("%f", Vrab01);}
   int0   C_Print(const xint64 Vrab01)       fastened {printf("%Lf", Vrab01);}
   int0   C_Print(const std::string &Temp01) fastened {printf("%s", Temp01.c_str());}
  }; MD_AIDATABASES Base;
  struct MD_GAMEDATA_MAIN_PIC {string Add_Address; uint32 Width = 0; uint32 Height = 0; uint32 Row = 0; uint32 Column = 0;};
  struct MD_GAMEDATA_MAIN {string Name; string Add_Head; string Add_Small; std::vector < MD_GAMEDATA_MAIN_PIC > Pictures; uint32 WalkAnimation = 0; uint32 RunAnimation = 0; string Dob_WalkSpeed; string Dob_WalkSpeedZ; string Dob_RunSpeed; string Dob_RunSpeedZ; string Dob_HeavyWalkSpeed; string Dob_HeavyWalkSpeedZ; string Dob_HeavyRunSpeed; string Dob_HeavyRunSpeedZ; string Dob_JumpHeight; string Dob_JumpSpeed; string Dob_JumpSpeedZ; string Dob_DashHeight; string Dob_DashSpeed; string Dob_DashSpeedZ; string Dob_FlipHeight; string Dob_FlipSpeed; int32 StartingHealth = 0; int32 LandingHurt = 0; string Add_HitSound; string Add_BreakSound; string Add_LandingSound;};
  struct MD_GAMEDATA_STRENGTH {string Name = "G"; int32 ZWidth = 0; int32 XVelocity = 0; int32 YVelocity = 0; int32 AttackerRefresh = 0; int32 VictimRefresh = 0; int32 Power = 0; int32 Damage = 0; int32 Effect = 0; int32 HitRespond = 0; int32 HitEffect = 0;};
  struct MD_GAMEDATA_FRAME_BPOINT {int32 X = 0; int32 Y = 0;};
  struct MD_GAMEDATA_FRAME_CPOINT {int32 Type = 0; int32 X = 0; int32 Y = 0; int32 Z = 0; int32 VictimFrame = 0; int32 InputA = 0; int32 InputD = 0; int32 InputJ = 0; int32 InputThrow = 0; int32 ThrowVelX = 0; int32 ThrowVelY = 0; int32 ThrowVelZ = 0; int32 ThrowDamage = 0; int32 Decrease = 0; int32 Control = 0; int32 Hurtable = 0; int32 Damage = 0; int32 BackHurtAction = 0; int32 FrontHurtAction = 0;};
  struct MD_GAMEDATA_FRAME_WPOINT {int32 Type = 0; int32 X = 0; int32 Y = 0; int32 Z = 0; int32 WeaponFrame = 0; int32 Strength = 0; int32 XVelocityThrow = 0; int32 YVelocityThrow = 0; int32 ZVelocityThrow = 0;};
  struct MD_GAMEDATA_FRAME_OPOINT {int32 Type = 0; int32 X = 0; int32 Y = 0; int32 Frame = 0; int32 ID = 0; int32 Condition = 0; int32 XVelocity = 0; int32 YVelocity = 0;};
  struct MD_GAMEDATA_FRAME_IPOINT {int32 Type = 0; int32 X = 0; int32 Y = 0; uint32 Width = 0; uint32 Height = 0; uint32 ZWidth = 0; int32 XVelocity = 0; int32 YVelocity = 0; int32 AttackerRefresh = 0; int32 VictimRefresh = 0; int32 Power = 0; int32 Damage = 0; int32 Effect = 0; int32 HitRespond = 0; int32 HitEffect = 0; int32 CatchRespond[2]{}; int32 CaughtRespond[2]{};};
  struct MD_GAMEDATA_FRAME_HPOINT {int32 Type = 0; int32 X = 0; int32 Y = 0; uint32 Width = 0; uint32 Height = 0;};
  struct MD_GAMEDATA_FRAME {uint32 Number = 0; string Name = "G"; int32 Picture = 0; int32 State = 0; int32 Wait = 0; int32 Next = 0; int32 CenterX = 0; int32 CenterY = 0; int32 XVelocity = 0; int32 YVelocity = 0; int32 ZVelocity = 0; int32 InputA = 0; int32 InputD = 0; int32 InputJ = 0; int32 InputDFA = 0; int32 InputDFJ = 0; int32 InputDDA = 0; int32 InputDDJ = 0; int32 InputDUA = 0; int32 InputDUJ = 0; int32 InputDJA = 0; int32 MPManage = 0; string Add_SoundEffect; MD_GAMEDATA_FRAME_BPOINT Bpoint; MD_GAMEDATA_FRAME_CPOINT Cpoint; MD_GAMEDATA_FRAME_WPOINT Wpoint; std::vector < MD_GAMEDATA_FRAME_OPOINT > Opoint; std::vector < MD_GAMEDATA_FRAME_IPOINT > Ipoint; std::vector < MD_GAMEDATA_FRAME_HPOINT > Hpoint;};
  struct MD_GAMEDATA {uint32 ID = 0; uint32 Type = 0; string Address; MD_GAMEDATA_MAIN Main; std::vector < MD_GAMEDATA_STRENGTH > Strength; std::vector < MD_GAMEDATA_FRAME > Frame;}; std::vector < MD_GAMEDATA > Data0001;
 //-//
 // Functions
  int0   L_Cleaning()                                                 {/*Vrab0001 = 0; Vrab0002 = 0; Vrab0003 = 0; Vrab0004 = 0; Vrab0005 = 0; Vrab0006 = 0; Temp0001 = ""; Temp0002 = ""; Temp0003 = "";*/ if(File0001.is_open()) File0001.close(); if(File0002.is_open()) File0002.close(); Vect0001.clear(); Strn0001.clear();}
  int0   L_Polish()                                                   {std::ofstream File01(TEMPORAL_FILE, std::ios::binary | std::ios::out); File01 << "Do not erase this file."; File01.close();}
  int0   L_Rename(string &Temp01)                                     {uint32 Vrab01 = Temp01.size(); while(Vrab01 != 1 && Temp01.at(Vrab01 - 1) != '-') Vrab01 -= 1; Vrab01 -= 1; if(Temp01.at(Vrab01) == '-' && Temp01.at(Vrab01 + 1) >= '0' && Temp01.at(Vrab01 + 1) <= '9'){string Temp02 = ""; uint32 Vrab02 = Vrab01; Temp02 += Temp01.at(Vrab02 + 1); while(Temp01.at(Vrab02 + 2) >= '0' && Temp01.at(Vrab02 + 2) <= '9'){Temp02 += Temp01.at(Vrab02 + 2); Vrab02 += 1;} Temp02 = std::to_string(L_Numbering(Temp02) + 1); Temp01.erase(Vrab01 + 1, (Vrab02 + 2) - (Vrab01 + 1)); Temp01.insert(Vrab01 + 1, Temp02);} else {Vrab01 = Temp01.size() - 1; while(Vrab01 != -1 && Temp01.at(Vrab01) != '.') Vrab01 -= 1; if(Vrab01 > 7) if(string(Temp01, Vrab01 - 8, 7) == "_mirror") Vrab01 -= 8; if(Vrab01 > 0){Temp01.insert(Vrab01, "-2");} else {Temp01.insert(Temp01.size() - 1, "-2");}}}
  int0   L_Summary(string Temp01)                                     {std::ofstream File01(L_Execute(Config.ECD_ResultDirectory + "\\summary.edb"), std::ios::binary | std::ios::app); File01 << Temp01; File01.close();}
  int0   L_Copy(uint32 Vrab01, uint32 Vrab02, uint32 Vrab03) fastened {Base.Game->Database->Data[Vrab01]->Frame[Vrab03] = Base.Game->Database->Data[Vrab01]->Frame[Vrab02];}// Base.Game->Database->Data[Vrab01]->Frame[Vrab03].state = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].state; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].wait = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].wait; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].next = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].next; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].dvx = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].dvx; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].dvy = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].dvy; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].dvz = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].dvz; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].centerx = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].centerx; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].centery = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].centery; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].hit_a = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].hit_a; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].hit_d = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].hit_d; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].hit_j = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].hit_j; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].hit_Fa = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].hit_Fa; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].hit_Fj = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].hit_Fj; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].hit_Da = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].hit_Da; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].hit_Dj = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].hit_Dj; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].hit_Ua = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].hit_Ua; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].hit_Uj = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].hit_Uj; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].hit_ja = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].hit_ja; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].mp = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].mp; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].sound = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].sound; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].bpoint.x = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].bpoint.x; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].bpoint.y = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].bpoint.y; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.kind = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.kind; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.x = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.x; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.y = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.y; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.vaction = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.vaction; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.aaction = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.aaction; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.daction = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.daction; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.jaction = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.jaction; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.taction = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.taction; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.dircontrol = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.dircontrol; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.decrease = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.decrease; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.throwvx = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.throwvx; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.throwvy = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.throwvy; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.throwvz = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.throwvz; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.throwinjury = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.throwinjury; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.cover = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.cover; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.hurtable = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.hurtable; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].cpoint.injury = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].cpoint.injury; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].wpoint.kind = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].wpoint.kind; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].wpoint.x = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].wpoint.x; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].wpoint.y = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].wpoint.y; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].wpoint.dvx = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].wpoint.dvx; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].wpoint.dvy = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].wpoint.dvy; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].wpoint.dvz = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].wpoint.dvz; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].wpoint.weaponact = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].wpoint.weaponact; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].wpoint.attacking = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].wpoint.attacking; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].wpoint.cover = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].wpoint.cover; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].opoint.kind = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].opoint.kind; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].opoint.x = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].opoint.x; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].opoint.y = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].opoint.y; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].opoint.dvx = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].opoint.dvx; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].opoint.dvy = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].opoint.dvy; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].opoint.oid = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].opoint.oid; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].opoint.action = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].opoint.action; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].opoint.facing = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].opoint.facing; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].itr_count = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].itr_count; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].itrs = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].itrs; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].itr_x = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].itr_x; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].itr_y = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].itr_y; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].itr_w = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].itr_w; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].itr_h = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].itr_h; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].bdy_count = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].bdy_count; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].bdys = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].bdys; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].bdy_x = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].bdy_x; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].bdy_y = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].bdy_y; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].bdy_w = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].bdy_w; Base.Game->Database->Data[Vrab01]->Frame[Vrab03].bdy_h = Base.Game->Database->Data[Vrab01]->Frame[Vrab02].bdy_h;}
  int1   L_Open(const string &Temp01)                                 {if(File0001.is_open()) File0001.close(); File0001.open(Temp01, std::ios::binary | std::ios::in); if(File0001.is_open()) return true; return false;}
  int1   L_Exist(const string &Temp01)                       fastened {struct stat Vrab01; return (stat(Temp01.c_str(), &Vrab01) == 0);}
  int1   L_Create(const string &Temp01)                               {if(File0002.is_open()) File0002.close(); File0002.open(Temp01, std::ios::binary | std::ios::out); if(File0002.is_open()) return true; return false;}
  int32  L_Positive(int32 Vrab01)                            fastened {if(Vrab01 < 0) return -Vrab01; return Vrab01;}
  int32  L_Rounding(xint64 Vrab01)                           fastened {if(rint64(Vrab01 + 0.5) == rint64(Vrab01)) return rint32(Vrab01); return rint32(Vrab01) + 1;}
  int32  L_Numbering(string Temp01)                          fastened {while(Temp01.size() > 0 && Temp01.at(0) != '-' && (Temp01.at(0) < '0' || Temp01.at(0) > '9')) Temp01.erase(0, 1); uint32 Vrab01 = Temp01.size(); if(Vrab01 == 0) return 0; while(Vrab01 != 1) if(Temp01.at(Vrab01 - 1) < '0' || Temp01.at(Vrab01 - 1) > '9'){Vrab01 -= 1;} else {break;} int32 Vrab02 = 0; if(Temp01.at(0) == '-'){if(Vrab01 == 1) return 0; if(Temp01.at(1) < '0' || Temp01.at(1) > '9') return 0; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 1; break; case '2': Vrab02 -= 2; break; case '3': Vrab02 -= 3; break; case '4': Vrab02 -= 4; break; case '5': Vrab02 -= 5; break; case '6': Vrab02 -= 6; break; case '7': Vrab02 -= 7; break; case '8': Vrab02 -= 8; break; case '9': Vrab02 -= 9; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 10; break; case '2': Vrab02 -= 20; break; case '3': Vrab02 -= 30; break; case '4': Vrab02 -= 40; break; case '5': Vrab02 -= 50; break; case '6': Vrab02 -= 60; break; case '7': Vrab02 -= 70; break; case '8': Vrab02 -= 80; break; case '9': Vrab02 -= 90; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 100; break; case '2': Vrab02 -= 200; break; case '3': Vrab02 -= 300; break; case '4': Vrab02 -= 400; break; case '5': Vrab02 -= 500; break; case '6': Vrab02 -= 600; break; case '7': Vrab02 -= 700; break; case '8': Vrab02 -= 800; break; case '9': Vrab02 -= 900; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 1000; break; case '2': Vrab02 -= 2000; break; case '3': Vrab02 -= 3000; break; case '4': Vrab02 -= 4000; break; case '5': Vrab02 -= 5000; break; case '6': Vrab02 -= 6000; break; case '7': Vrab02 -= 7000; break; case '8': Vrab02 -= 8000; break; case '9': Vrab02 -= 9000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 10000; break; case '2': Vrab02 -= 20000; break; case '3': Vrab02 -= 30000; break; case '4': Vrab02 -= 40000; break; case '5': Vrab02 -= 50000; break; case '6': Vrab02 -= 60000; break; case '7': Vrab02 -= 70000; break; case '8': Vrab02 -= 80000; break; case '9': Vrab02 -= 90000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 100000; break; case '2': Vrab02 -= 200000; break; case '3': Vrab02 -= 300000; break; case '4': Vrab02 -= 400000; break; case '5': Vrab02 -= 500000; break; case '6': Vrab02 -= 600000; break; case '7': Vrab02 -= 700000; break; case '8': Vrab02 -= 800000; break; case '9': Vrab02 -= 900000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 1000000; break; case '2': Vrab02 -= 2000000; break; case '3': Vrab02 -= 3000000; break; case '4': Vrab02 -= 4000000; break; case '5': Vrab02 -= 5000000; break; case '6': Vrab02 -= 6000000; break; case '7': Vrab02 -= 7000000; break; case '8': Vrab02 -= 8000000; break; case '9': Vrab02 -= 9000000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 10000000; break; case '2': Vrab02 -= 20000000; break; case '3': Vrab02 -= 30000000; break; case '4': Vrab02 -= 40000000; break; case '5': Vrab02 -= 50000000; break; case '6': Vrab02 -= 60000000; break; case '7': Vrab02 -= 70000000; break; case '8': Vrab02 -= 80000000; break; case '9': Vrab02 -= 90000000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 100000000; break; case '2': Vrab02 -= 200000000; break; case '3': Vrab02 -= 300000000; break; case '4': Vrab02 -= 400000000; break; case '5': Vrab02 -= 500000000; break; case '6': Vrab02 -= 600000000; break; case '7': Vrab02 -= 700000000; break; case '8': Vrab02 -= 800000000; break; case '9': Vrab02 -= 900000000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; for(int32 Vrab03 = 10; Vrab01 > 0; Vrab03 *= 10){switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 100000000 * Vrab03; break; case '2': Vrab02 -= 200000000 * Vrab03; break; case '3': Vrab02 -= 300000000 * Vrab03; break; case '4': Vrab02 -= 400000000 * Vrab03; break; case '5': Vrab02 -= 500000000 * Vrab03; break; case '6': Vrab02 -= 600000000 * Vrab03; break; case '7': Vrab02 -= 700000000 * Vrab03; break; case '8': Vrab02 -= 800000000 * Vrab03; break; case '9': Vrab02 -= 900000000 * Vrab03; break; default: break;} Vrab01 -= 1;} return Vrab02;} else {Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 1; break; case '2': Vrab02 += 2; break; case '3': Vrab02 += 3; break; case '4': Vrab02 += 4; break; case '5': Vrab02 += 5; break; case '6': Vrab02 += 6; break; case '7': Vrab02 += 7; break; case '8': Vrab02 += 8; break; case '9': Vrab02 += 9; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 10; break; case '2': Vrab02 += 20; break; case '3': Vrab02 += 30; break; case '4': Vrab02 += 40; break; case '5': Vrab02 += 50; break; case '6': Vrab02 += 60; break; case '7': Vrab02 += 70; break; case '8': Vrab02 += 80; break; case '9': Vrab02 += 90; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 100; break; case '2': Vrab02 += 200; break; case '3': Vrab02 += 300; break; case '4': Vrab02 += 400; break; case '5': Vrab02 += 500; break; case '6': Vrab02 += 600; break; case '7': Vrab02 += 700; break; case '8': Vrab02 += 800; break; case '9': Vrab02 += 900; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 1000; break; case '2': Vrab02 += 2000; break; case '3': Vrab02 += 3000; break; case '4': Vrab02 += 4000; break; case '5': Vrab02 += 5000; break; case '6': Vrab02 += 6000; break; case '7': Vrab02 += 7000; break; case '8': Vrab02 += 8000; break; case '9': Vrab02 += 9000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 10000; break; case '2': Vrab02 += 20000; break; case '3': Vrab02 += 30000; break; case '4': Vrab02 += 40000; break; case '5': Vrab02 += 50000; break; case '6': Vrab02 += 60000; break; case '7': Vrab02 += 70000; break; case '8': Vrab02 += 80000; break; case '9': Vrab02 += 90000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 100000; break; case '2': Vrab02 += 200000; break; case '3': Vrab02 += 300000; break; case '4': Vrab02 += 400000; break; case '5': Vrab02 += 500000; break; case '6': Vrab02 += 600000; break; case '7': Vrab02 += 700000; break; case '8': Vrab02 += 800000; break; case '9': Vrab02 += 900000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 1000000; break; case '2': Vrab02 += 2000000; break; case '3': Vrab02 += 3000000; break; case '4': Vrab02 += 4000000; break; case '5': Vrab02 += 5000000; break; case '6': Vrab02 += 6000000; break; case '7': Vrab02 += 7000000; break; case '8': Vrab02 += 8000000; break; case '9': Vrab02 += 9000000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 10000000; break; case '2': Vrab02 += 20000000; break; case '3': Vrab02 += 30000000; break; case '4': Vrab02 += 40000000; break; case '5': Vrab02 += 50000000; break; case '6': Vrab02 += 60000000; break; case '7': Vrab02 += 70000000; break; case '8': Vrab02 += 80000000; break; case '9': Vrab02 += 90000000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 100000000; break; case '2': Vrab02 += 200000000; break; case '3': Vrab02 += 300000000; break; case '4': Vrab02 += 400000000; break; case '5': Vrab02 += 500000000; break; case '6': Vrab02 += 600000000; break; case '7': Vrab02 += 700000000; break; case '8': Vrab02 += 800000000; break; case '9': Vrab02 += 900000000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; for(int32 Vrab03 = 10; Vrab01 != -1; Vrab03 *= 10){switch(Temp01.at(Vrab01)){case '1': Vrab02 += 100000000 * Vrab03; break; case '2': Vrab02 += 200000000 * Vrab03; break; case '3': Vrab02 += 300000000 * Vrab03; break; case '4': Vrab02 += 400000000 * Vrab03; break; case '5': Vrab02 += 500000000 * Vrab03; break; case '6': Vrab02 += 600000000 * Vrab03; break; case '7': Vrab02 += 700000000 * Vrab03; break; case '8': Vrab02 += 800000000 * Vrab03; break; case '9': Vrab02 += 900000000 * Vrab03; break; default: break;} Vrab01 -= 1;} return Vrab02;}}
  uint32 L_Addressing(string Temp01)                         fastened {uint32 Vrab01 = 0; const uint32 Vrab02 = Strn0001.size(); const string Temp02 = L_Lowercase(Temp01); while(Vrab01 != Vrab02){if(Temp02 == L_Lowercase(Strn0001[Vrab01])) break; Vrab01 += 1;} if(Vrab01 == Vrab02) Strn0001.push_back(Temp01); return Vrab01;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
  uint32 L_Indexing(int32 Vrab01)                            fastened {uint32 Vrab02 = 0; const uint32 Vrab03 = Vect0001.size(); while(Vrab02 != Vrab03){if(Vrab01 == Vect0001[Vrab02]) break; Vrab02 += 1;} if(Vrab02 == Vrab03) return 4294967295; return Vrab02;}
  string L_Format(const int32 Vrab01, const int32 Vrab02)    fastened {switch(Config.ECD_ResultCodeFormat){case 3: 
  {
  const int32 Vrab03 = L_Positive(Vrab01); string Temp01;
  if(Vrab03 < 100000000){if(Vrab03 < 10000000){if(Vrab03 < 1000000){if(Vrab03 < 100000){if(Vrab03 < 10000){if(Vrab03 < 1000){if(Vrab03 < 100){if(Vrab03 < 10){Temp01 = "        ";} else {Temp01 = "       ";}} else {Temp01 = "      ";}} else {Temp01 = "     ";}} else {Temp01 = "    ";}} else {Temp01 = "   ";}} else {Temp01 = "  ";}} else {Temp01 = " ";}}
  if(Vrab01 >= 0) Temp01 += " ";
  const uint32 Vrab04 = ruint32(L_Positive(Vrab02));
  if(Temp01.size() >= 9 - Vrab04){if(Vrab02 >= 0){return string(Temp01, 0, Temp01.size() - (9 - Vrab04)) + std::to_string(Vrab01);} else {return std::to_string(Vrab01) + string(Temp01, 0, Temp01.size() - (9 - Vrab04));}}
  }
  
  break; default: break;} return std::to_string(Vrab01);}
  string L_Lowercase(string Temp01)                          fastened {int32 Vrab01 = Temp01.size(); while(Vrab01 != 0){Vrab01 -= 1; if(Temp01.at(Vrab01) >= 'A' && Temp01.at(Vrab01) <= 'Z') Temp01.at(Vrab01) += 32;} return Temp01;}
  string L_Execute(const string Temp01)                               {string Temp02 = Temp01; uint32 Vrab01 = Temp02.size() - 1; while(Vrab01 != 0 && Temp02.at(Vrab01) != '\\') Vrab01 -= 1; if(Vrab01 > 0) Temp02.erase(Vrab01, Temp02.size() - Vrab01); std::filesystem::create_directories(Temp02); return Temp01;}
  string L_Manage(string Temp01)                                      {if(Temp01 == "%") return std::filesystem::current_path().string(); uint32 Vrab01 = Temp01.size(); while(Vrab01 != 0){Vrab01 -= 1; if(Temp01.at(Vrab01) == '%') Temp01.at(Vrab01) = ' ';} return Temp01;}
  string L_Reform(string Temp01)                             fastened {const uint32 Vrab01 = Temp01.size(); uint32 Vrab02 = Vrab01; while(Vrab02 > 0){Vrab02 -= 1; if(Temp01.at(Vrab02) == '\\') break;} return string(Temp01, Vrab02, Vrab01 - Vrab02);}

  int8   S_Decryption94(const int8 Vrab01)                   fastened {if(Vrab01 == Config.ECD_ResultEncryption[0]) return 0; if(Vrab01 == Config.ECD_ResultEncryption[1]) return 1; if(Vrab01 == Config.ECD_ResultEncryption[2]) return 2; if(Vrab01 == Config.ECD_ResultEncryption[3]) return 3; if(Vrab01 == Config.ECD_ResultEncryption[4]) return 4; if(Vrab01 == Config.ECD_ResultEncryption[5]) return 5; if(Vrab01 == Config.ECD_ResultEncryption[6]) return 6; if(Vrab01 == Config.ECD_ResultEncryption[7]) return 7; if(Vrab01 == Config.ECD_ResultEncryption[8]) return 8; if(Vrab01 == Config.ECD_ResultEncryption[9]) return 9; if(Vrab01 == Config.ECD_ResultEncryption[10]) return 10; if(Vrab01 == Config.ECD_ResultEncryption[11]) return 11; if(Vrab01 == Config.ECD_ResultEncryption[12]) return 12; if(Vrab01 == Config.ECD_ResultEncryption[13]) return 13; if(Vrab01 == Config.ECD_ResultEncryption[14]) return 14; if(Vrab01 == Config.ECD_ResultEncryption[15]) return 15; if(Vrab01 == Config.ECD_ResultEncryption[16]) return 16; if(Vrab01 == Config.ECD_ResultEncryption[17]) return 17; if(Vrab01 == Config.ECD_ResultEncryption[18]) return 18; if(Vrab01 == Config.ECD_ResultEncryption[19]) return 19; if(Vrab01 == Config.ECD_ResultEncryption[20]) return 20; if(Vrab01 == Config.ECD_ResultEncryption[21]) return 21; if(Vrab01 == Config.ECD_ResultEncryption[22]) return 22; if(Vrab01 == Config.ECD_ResultEncryption[23]) return 23; if(Vrab01 == Config.ECD_ResultEncryption[24]) return 24; if(Vrab01 == Config.ECD_ResultEncryption[25]) return 25; if(Vrab01 == Config.ECD_ResultEncryption[26]) return 26; if(Vrab01 == Config.ECD_ResultEncryption[27]) return 27; if(Vrab01 == Config.ECD_ResultEncryption[28]) return 28; if(Vrab01 == Config.ECD_ResultEncryption[29]) return 29; if(Vrab01 == Config.ECD_ResultEncryption[30]) return 30; if(Vrab01 == Config.ECD_ResultEncryption[31]) return 31; if(Vrab01 == Config.ECD_ResultEncryption[32]) return 32; if(Vrab01 == Config.ECD_ResultEncryption[33]) return 33; if(Vrab01 == Config.ECD_ResultEncryption[34]) return 34; if(Vrab01 == Config.ECD_ResultEncryption[35]) return 35; if(Vrab01 == Config.ECD_ResultEncryption[36]) return 36; if(Vrab01 == Config.ECD_ResultEncryption[37]) return 37; if(Vrab01 == Config.ECD_ResultEncryption[38]) return 38; if(Vrab01 == Config.ECD_ResultEncryption[39]) return 39; if(Vrab01 == Config.ECD_ResultEncryption[40]) return 40; if(Vrab01 == Config.ECD_ResultEncryption[41]) return 41; if(Vrab01 == Config.ECD_ResultEncryption[42]) return 42; if(Vrab01 == Config.ECD_ResultEncryption[43]) return 43; if(Vrab01 == Config.ECD_ResultEncryption[44]) return 44; if(Vrab01 == Config.ECD_ResultEncryption[45]) return 45; if(Vrab01 == Config.ECD_ResultEncryption[46]) return 46; if(Vrab01 == Config.ECD_ResultEncryption[47]) return 47; if(Vrab01 == Config.ECD_ResultEncryption[48]) return 48; if(Vrab01 == Config.ECD_ResultEncryption[49]) return 49; if(Vrab01 == Config.ECD_ResultEncryption[50]) return 50; if(Vrab01 == Config.ECD_ResultEncryption[51]) return 51; if(Vrab01 == Config.ECD_ResultEncryption[52]) return 52; if(Vrab01 == Config.ECD_ResultEncryption[53]) return 53; if(Vrab01 == Config.ECD_ResultEncryption[54]) return 54; if(Vrab01 == Config.ECD_ResultEncryption[55]) return 55; if(Vrab01 == Config.ECD_ResultEncryption[56]) return 56; if(Vrab01 == Config.ECD_ResultEncryption[57]) return 57; if(Vrab01 == Config.ECD_ResultEncryption[58]) return 58; if(Vrab01 == Config.ECD_ResultEncryption[59]) return 59; if(Vrab01 == Config.ECD_ResultEncryption[60]) return 60; if(Vrab01 == Config.ECD_ResultEncryption[61]) return 61; if(Vrab01 == Config.ECD_ResultEncryption[62]) return 62; if(Vrab01 == Config.ECD_ResultEncryption[63]) return 63; if(Vrab01 == Config.ECD_ResultEncryption[64]) return 64; if(Vrab01 == Config.ECD_ResultEncryption[65]) return 65; if(Vrab01 == Config.ECD_ResultEncryption[66]) return 66; if(Vrab01 == Config.ECD_ResultEncryption[67]) return 67; if(Vrab01 == Config.ECD_ResultEncryption[68]) return 68; if(Vrab01 == Config.ECD_ResultEncryption[69]) return 69; if(Vrab01 == Config.ECD_ResultEncryption[70]) return 70; if(Vrab01 == Config.ECD_ResultEncryption[71]) return 71; if(Vrab01 == Config.ECD_ResultEncryption[72]) return 72; if(Vrab01 == Config.ECD_ResultEncryption[73]) return 73; if(Vrab01 == Config.ECD_ResultEncryption[74]) return 74; if(Vrab01 == Config.ECD_ResultEncryption[75]) return 75; if(Vrab01 == Config.ECD_ResultEncryption[76]) return 76; if(Vrab01 == Config.ECD_ResultEncryption[77]) return 77; if(Vrab01 == Config.ECD_ResultEncryption[78]) return 78; if(Vrab01 == Config.ECD_ResultEncryption[79]) return 79; if(Vrab01 == Config.ECD_ResultEncryption[80]) return 80; if(Vrab01 == Config.ECD_ResultEncryption[81]) return 81; if(Vrab01 == Config.ECD_ResultEncryption[82]) return 82; if(Vrab01 == Config.ECD_ResultEncryption[83]) return 83; if(Vrab01 == Config.ECD_ResultEncryption[84]) return 84; if(Vrab01 == Config.ECD_ResultEncryption[85]) return 85; if(Vrab01 == Config.ECD_ResultEncryption[86]) return 86; if(Vrab01 == Config.ECD_ResultEncryption[87]) return 87; if(Vrab01 == Config.ECD_ResultEncryption[88]) return 88; if(Vrab01 == Config.ECD_ResultEncryption[89]) return 89; if(Vrab01 == Config.ECD_ResultEncryption[90]) return 90; if(Vrab01 == Config.ECD_ResultEncryption[91]) return 91; if(Vrab01 == Config.ECD_ResultEncryption[92]) return 92; if(Vrab01 == Config.ECD_ResultEncryption[93]) return 93; return 0;}
  int8   S_DecryptionINT8(const int8 Vrab01[2])              fastened {return (int8)(ruint8(S_Decryption94(Vrab01[1])) + ruint8(S_Decryption94(Vrab01[0])) * 94);}
  int16  S_DecryptionINT16(const int8 Vrab01[3])             fastened {return (int16)(ruint16(S_Decryption94(Vrab01[2])) + ruint16(S_Decryption94(Vrab01[1])) * 94 + ruint16(S_Decryption94(Vrab01[0])) * 8836);}
  int32  S_DecryptionINT32(const int8 Vrab01[5])             fastened {return (int32)(ruint32(S_Decryption94(Vrab01[4])) + ruint32(S_Decryption94(Vrab01[3])) * 94 + ruint32(S_Decryption94(Vrab01[2])) * 8836 + ruint32(S_Decryption94(Vrab01[1])) * 830584 + ruint32(S_Decryption94(Vrab01[0])) * 78074896);}
  int64  S_DecryptionINT64(const int8 Vrab01[10])            fastened {return (int64)(ruint64(S_Decryption94(Vrab01[9])) + ruint64(S_Decryption94(Vrab01[8])) * 94 + ruint64(S_Decryption94(Vrab01[7])) * 8836 + ruint64(S_Decryption94(Vrab01[6])) * 830584 + ruint64(S_Decryption94(Vrab01[5])) * 78074896 + ruint64(S_Decryption94(Vrab01[4])) * 7339040224 + ruint64(S_Decryption94(Vrab01[3])) * 689869781056 + ruint64(S_Decryption94(Vrab01[2])) * 64847759419264 + ruint64(S_Decryption94(Vrab01[1])) * 6095689385410816 + ruint64(S_Decryption94(Vrab01[0])) * 572994802228616704);}
  uint32 S_DecryptionUINT4(const int8 Vrab01[1])             fastened {return S_Decryption94(Vrab01[0]);}
  uint8  S_DecryptionUINT8(const int8 Vrab01[2])             fastened {return S_Decryption94(Vrab01[1]) + (S_Decryption94(Vrab01[0]) * 94);}
  uint32 S_DecryptionUINT10(const int8 Vrab01[2])            fastened {return S_Decryption94(Vrab01[1]) + (S_Decryption94(Vrab01[0]) * 94);}
  uint16 S_DecryptionUINT16(const int8 Vrab01[3])            fastened {return ruint16(S_Decryption94(Vrab01[2])) + ruint16(S_Decryption94(Vrab01[1])) * 94 + ruint16(S_Decryption94(Vrab01[0])) * 8836;}
  uint32 S_DecryptionUINT18(const int8 Vrab01[3])            fastened {return ruint16(S_Decryption94(Vrab01[2])) + ruint16(S_Decryption94(Vrab01[1])) * 94 + ruint16(S_Decryption94(Vrab01[0])) * 8836;}
  uint32 S_DecryptionUINT24(const int8 Vrab01[4])            fastened {return ruint32(S_Decryption94(Vrab01[3])) + ruint32(S_Decryption94(Vrab01[2])) * 94 + ruint32(S_Decryption94(Vrab01[1])) * 8836 + ruint32(S_Decryption94(Vrab01[0])) * 830584;}
  uint32 S_DecryptionUINT32(const int8 Vrab01[5])            fastened {return ruint32(S_Decryption94(Vrab01[4])) + ruint32(S_Decryption94(Vrab01[3])) * 94 + ruint32(S_Decryption94(Vrab01[2])) * 8836 + ruint32(S_Decryption94(Vrab01[1])) * 830584 + ruint32(S_Decryption94(Vrab01[0])) * 78074896;}
  uint64 S_DecryptionUINT64(const int8 Vrab01[10])           fastened {return ruint64(S_Decryption94(Vrab01[9])) + ruint64(S_Decryption94(Vrab01[8])) * 94 + ruint64(S_Decryption94(Vrab01[7])) * 8836 + ruint64(S_Decryption94(Vrab01[6])) * 830584 + ruint64(S_Decryption94(Vrab01[5])) * 78074896 + ruint64(S_Decryption94(Vrab01[4])) * 7339040224 + ruint64(S_Decryption94(Vrab01[3])) * 689869781056 + ruint64(S_Decryption94(Vrab01[2])) * 64847759419264 + ruint64(S_Decryption94(Vrab01[1])) * 6095689385410816 + ruint64(S_Decryption94(Vrab01[0])) * 572994802228616704;}
  xint64 S_DecryptionXINT64(const int8 Vrab01[11])           fastened {return rxint64(S_Decryption94(Vrab01[0])) * 8836 + rxint64(S_Decryption94(Vrab01[1])) * 94 + rxint64(S_Decryption94(Vrab01[2])) - 400000 + rxint64(S_Decryption94(Vrab01[3])) * 0.064847759419264 + rxint64(S_Decryption94(Vrab01[4])) * 0.000689869781056 + rxint64(S_Decryption94(Vrab01[5])) * 0.000007339040224 + rxint64(S_Decryption94(Vrab01[6])) * 0.000000078074896 +  rxint64(S_Decryption94(Vrab01[7])) * 0.000000000830584 + rxint64(S_Decryption94(Vrab01[8])) * 0.000000000008836 + rxint64(S_Decryption94(Vrab01[9])) * 0.000000000000094 + rxint64(S_Decryption94(Vrab01[10])) * 0.000000000000001;}
  string S_DecryptionSTRING(string Temp01)                   fastened {int8 Vrab01 = 0; const uint32 Vrab02 = Temp01.size(); uint32 Vrab03 = 0;  while(Vrab03 != Vrab02){Vrab01 = Temp01.at(Vrab03); if(Vrab01 >= '!' && Vrab01 <= '~') Temp01.at(Vrab03) = ((S_Decryption94(Vrab01) + 94 - (Vrab03 % 94)) % 94) + 33; Vrab03 += 1;} return Temp01;}
  string S_Encryption94(const uint64 Vrab01)                 fastened {return {Config.ECD_ResultEncryption[(Vrab01 % 94)]};}
  //string S_EncryptionUINT8(const int8 Vrab01)                 fastened {return S_Encryption94(Vrab01 / 94) + S_Encryption94(Vrab01);}
  //string S_EncryptionUINT16(const int16 Vrab01)               fastened {return S_Encryption94(Vrab01 / 8836) + S_Encryption94(Vrab01 / 94) + S_Encryption94(Vrab01);}
  //string S_EncryptionUINT32(const int32 Vrab01)               fastened {return S_Encryption94(Vrab01 / 78074896) + S_Encryption94(Vrab01 / 830584) + S_Encryption94(Vrab01 / 8836) + S_Encryption94(Vrab01 / 94) + S_Encryption94(Vrab01);}
  //string S_EncryptionUINT64(const int64 Vrab01)               fastened {return S_Encryption94(Vrab01 / 572994802228616704) + S_Encryption94(Vrab01 / 6095689385410816) + S_Encryption94(Vrab01 / 64847759419264) + S_Encryption94(Vrab01 / 689869781056) + S_Encryption94(Vrab01 / 7339040224) + S_Encryption94(Vrab01 / 78074896) + S_Encryption94(Vrab01 / 830584) + S_Encryption94(Vrab01 / 8836) + S_Encryption94(Vrab01 / 94) + S_Encryption94(Vrab01);}
  string S_EncryptionUINT4(const uint32 Vrab01)              fastened {return S_Encryption94(Vrab01);}
  string S_EncryptionUINT8(const uint8 Vrab01)               fastened {return S_Encryption94(Vrab01 / 94) + S_Encryption94(Vrab01);}
  string S_EncryptionUINT10(const uint32 Vrab01)             fastened {return S_Encryption94(Vrab01 / 94) + S_Encryption94(Vrab01);}
  string S_EncryptionUINT16(const uint16 Vrab01)             fastened {return S_Encryption94(Vrab01 / 8836) + S_Encryption94(Vrab01 / 94) + S_Encryption94(Vrab01);}
  string S_EncryptionUINT18(const uint32 Vrab01)             fastened {return S_Encryption94(Vrab01 / 8836) + S_Encryption94(Vrab01 / 94) + S_Encryption94(Vrab01);}
  string S_EncryptionUINT24(const uint32 Vrab01)             fastened {return S_Encryption94(Vrab01 / 830584) + S_Encryption94(Vrab01 / 8836) + S_Encryption94(Vrab01 / 94) + S_Encryption94(Vrab01);}
  string S_EncryptionUINT32(const uint32 Vrab01)             fastened {return S_Encryption94(Vrab01 / 78074896) + S_Encryption94(Vrab01 / 830584) + S_Encryption94(Vrab01 / 8836) + S_Encryption94(Vrab01 / 94) + S_Encryption94(Vrab01);}
  string S_EncryptionUINT64(const uint64 Vrab01)             fastened {return S_Encryption94(Vrab01 / 572994802228616704) + S_Encryption94(Vrab01 / 6095689385410816) + S_Encryption94(Vrab01 / 64847759419264) + S_Encryption94(Vrab01 / 689869781056) + S_Encryption94(Vrab01 / 7339040224) + S_Encryption94(Vrab01 / 78074896) + S_Encryption94(Vrab01 / 830584) + S_Encryption94(Vrab01 / 8836) + S_Encryption94(Vrab01 / 94) + S_Encryption94(Vrab01);}
  string S_EncryptionXINT64(const xint64 Vrab01)             fastened {xint64 Vrab02 = Vrab01 + 400000; if(Vrab02 < 0){Vrab02 = 0;} else {if(Vrab02 > 800000) Vrab02 = 800000;} const int64 Vrab03 = rint64(Vrab02); const int64 Vrab04 = Vrab03 / 94; const xint64 Vrab05 = (Vrab02 - rxint64(rint64(Vrab02))) * 100000; const xint64 Vrab06 = (Vrab05 - rxint64(rint64(Vrab05))) * 100000; const xint64 Vrab07 = (Vrab06 - rxint64(rint64(Vrab06))) * 100000; const int64 Vrab08 = rint64(Vrab05) * 10000000000 + rint64(Vrab06) * 100000 + rint64(Vrab07); const int64 Vrab09 = Vrab08 / 94; const int64 Vrab10 = Vrab09 / 94; const int64 Vrab11 = Vrab10 / 94; const int64 Vrab12 = Vrab11 / 94; const int64 Vrab13 = Vrab12 / 94; const int64 Vrab14 = Vrab13 / 94; return S_Encryption94(Vrab04 / 94) + S_Encryption94(Vrab04) + S_Encryption94(Vrab03) + S_Encryption94(Vrab14 / 94) + S_Encryption94(Vrab14) + S_Encryption94(Vrab13) + S_Encryption94(Vrab12) + S_Encryption94(Vrab11) + S_Encryption94(Vrab10) + S_Encryption94(Vrab09) + S_Encryption94(Vrab08);}
  string S_EncryptionSTRING(string Temp01)                   fastened {int8 Vrab01 = 0; const uint32 Vrab02 = Temp01.size(); uint32 Vrab03 = 0; while(Vrab03 != Vrab02){Vrab01 = Temp01.at(Vrab03); if(Vrab01 >= '!' && Vrab01 <= '~') Temp01.at(Vrab03) = (S_Encryption94(rint64(Vrab01) + rint64(Vrab03) - 33)).at(0); Vrab03 += 1;} return Temp01;}
  string S_EncryptionCHARDATA(const string Temp01)           fastened
  {
   std::ifstream File01;
   switch(Vrab0001)
   {
    case 0:
     if(Temp01 == "<bmp_begin>")               {Vrab0001 = 1; return {Config.ECD_ResultEncryption[0]};}
     if(Temp01 == "<weapon_strength_list>")    {Vrab0001 = 2; return {Config.ECD_ResultEncryption[1]};}
     if(Temp01 == "<frame>")                   {Vrab0001 = 17; Vrab0003 = 0; return {Config.ECD_ResultEncryption[2]};}
    break;
    case 1:
     if(Temp01 == "<bmp_end>")                 {Vrab0001 = 0; return {Config.ECD_ResultEncryption[0]};}
     if(Temp01 == "name:")                     {Vrab0001 = 13; return {Config.ECD_ResultEncryption[1]};}
     if(Temp01 == "head:")                     {Vrab0001 = 14; return {Config.ECD_ResultEncryption[2]};}
     if(Temp01 == "small:")                    {Vrab0001 = 14; return {Config.ECD_ResultEncryption[3]};}
     if(string(Temp01, 0, 5) == "file(")       {Vrab0001 = 16; return {Config.ECD_ResultEncryption[4]};}
     if(Temp01 == "w:")                        {Vrab0001 = 19; return {Config.ECD_ResultEncryption[5]};}
     if(Temp01 == "h:")                        {Vrab0001 = 19; return {Config.ECD_ResultEncryption[6]};}
     if(Temp01 == "col:")                      {Vrab0001 = 19; return {Config.ECD_ResultEncryption[7]};}
     if(Temp01 == "row:")                      {Vrab0001 = 19; return {Config.ECD_ResultEncryption[8]};}
     if(Temp01 == "walking_frame_rate")        {Vrab0001 = 19; return {Config.ECD_ResultEncryption[9]};}
     if(Temp01 == "running_frame_rate")        {Vrab0001 = 19; return {Config.ECD_ResultEncryption[10]};}
     if(Temp01 == "walking_speed")             {Vrab0001 = 30; return {Config.ECD_ResultEncryption[11]};}
     if(Temp01 == "walking_speedz")            {Vrab0001 = 30; return {Config.ECD_ResultEncryption[12]};}
     if(Temp01 == "running_speed")             {Vrab0001 = 30; return {Config.ECD_ResultEncryption[13]};}
     if(Temp01 == "running_speedz")            {Vrab0001 = 30; return {Config.ECD_ResultEncryption[14]};}
     if(Temp01 == "heavy_walking_speed")       {Vrab0001 = 30; return {Config.ECD_ResultEncryption[15]};}
     if(Temp01 == "heavy_walking_speedz")      {Vrab0001 = 30; return {Config.ECD_ResultEncryption[16]};}
     if(Temp01 == "heavy_running_speed")       {Vrab0001 = 30; return {Config.ECD_ResultEncryption[17]};}
     if(Temp01 == "heavy_running_speedz")      {Vrab0001 = 30; return {Config.ECD_ResultEncryption[18]};}
     if(Temp01 == "jump_height")               {Vrab0001 = 30; return {Config.ECD_ResultEncryption[19]};}
     if(Temp01 == "jump_distance")             {Vrab0001 = 30; return {Config.ECD_ResultEncryption[20]};}
     if(Temp01 == "jump_distancez")            {Vrab0001 = 30; return {Config.ECD_ResultEncryption[21]};}
     if(Temp01 == "dash_height")               {Vrab0001 = 30; return {Config.ECD_ResultEncryption[22]};}
     if(Temp01 == "dash_distance")             {Vrab0001 = 30; return {Config.ECD_ResultEncryption[23]};}
     if(Temp01 == "dash_distancez")            {Vrab0001 = 30; return {Config.ECD_ResultEncryption[24]};}
     if(Temp01 == "rowing_height")             {Vrab0001 = 30; return {Config.ECD_ResultEncryption[25]};}
     if(Temp01 == "rowing_distance")           {Vrab0001 = 30; return {Config.ECD_ResultEncryption[26]};}
     if(Temp01 == "weapon_hp:")                {Vrab0001 = 19; return {Config.ECD_ResultEncryption[27]};}
     if(Temp01 == "weapon_drop_hurt:")         {Vrab0001 = 19; return {Config.ECD_ResultEncryption[28]};}
     if(Temp01 == "weapon_hit_sound:")         {Vrab0001 = 14; return {Config.ECD_ResultEncryption[29]};}
     if(Temp01 == "weapon_drop_sound:")        {Vrab0001 = 14; return {Config.ECD_ResultEncryption[30]};}
     if(Temp01 == "weapon_broken_sound:")      {Vrab0001 = 14; return {Config.ECD_ResultEncryption[31]};}
    break;
    case 2:
     if(Temp01 == "<weapon_strength_list_end>"){Vrab0001 = 0; return {Config.ECD_ResultEncryption[0]};}
     if(Temp01 == "entry:")                    {Vrab0001 = 48; return {Config.ECD_ResultEncryption[1]};}
     if(Temp01 == "zwidth:")                   {Vrab0001 = 20; return {Config.ECD_ResultEncryption[2]};}
     if(Temp01 == "dvx:")                      {Vrab0001 = 20; return {Config.ECD_ResultEncryption[3]};}
     if(Temp01 == "dvy:")                      {Vrab0001 = 20; return {Config.ECD_ResultEncryption[4]};}
     if(Temp01 == "fall:")                     {Vrab0001 = 20; return {Config.ECD_ResultEncryption[5]};}
     if(Temp01 == "arest:")                    {Vrab0001 = 20; return {Config.ECD_ResultEncryption[6]};}
     if(Temp01 == "vrest:")                    {Vrab0001 = 20; return {Config.ECD_ResultEncryption[7]};}
     if(Temp01 == "respond:")                  {Vrab0001 = 20; return {Config.ECD_ResultEncryption[8]};}
     if(Temp01 == "effect:")                   {Vrab0001 = 20; return {Config.ECD_ResultEncryption[9]};}
     if(Temp01 == "bdefend:")                  {Vrab0001 = 20; return {Config.ECD_ResultEncryption[10]};}
     if(Temp01 == "injury:")                   {Vrab0001 = 20; return {Config.ECD_ResultEncryption[11]};}
    break;
    case 3:
     if(Temp01 == "<frame_end>")               {Vrab0001 = 0; return {Config.ECD_ResultEncryption[0]};}
     if(Temp01 == "pic:")                      {Vrab0001 = 21; return {Config.ECD_ResultEncryption[1]};}
     if(Temp01 == "state:")                    {Vrab0001 = 37; return {Config.ECD_ResultEncryption[2]};}
     if(Temp01 == "wait:")                     {Vrab0001 = 21; return {Config.ECD_ResultEncryption[3]};}
     if(Temp01 == "next:")                     {Vrab0001 = 21; return {Config.ECD_ResultEncryption[4]};}
     if(Temp01 == "dvx:")                      {Vrab0001 = 21; return {Config.ECD_ResultEncryption[5]};}
     if(Temp01 == "dvy:")                      {Vrab0001 = 21; return {Config.ECD_ResultEncryption[6]};}
     if(Temp01 == "dvz:")                      {Vrab0001 = 21; return {Config.ECD_ResultEncryption[7]};}
     if(Temp01 == "centerx:")                  {Vrab0001 = 21; return {Config.ECD_ResultEncryption[8]};}
     if(Temp01 == "centery:")                  {Vrab0001 = 31; return {Config.ECD_ResultEncryption[9]};}
     if(Temp01 == "hit_a:")                    {Vrab0001 = 21; return {Config.ECD_ResultEncryption[10]};}
     if(Temp01 == "hit_d:")                    {Vrab0001 = 21; return {Config.ECD_ResultEncryption[11]};}
     if(Temp01 == "hit_j:")                    {Vrab0001 = 21; return {Config.ECD_ResultEncryption[12]};}
     if(Temp01 == "hit_Fa:")                   {Vrab0001 = 21; return {Config.ECD_ResultEncryption[13]};}
     if(Temp01 == "hit_Fj:")                   {Vrab0001 = 21; return {Config.ECD_ResultEncryption[14]};}
     if(Temp01 == "hit_Da:")                   {Vrab0001 = 21; return {Config.ECD_ResultEncryption[15]};}
     if(Temp01 == "hit_Dj:")                   {Vrab0001 = 21; return {Config.ECD_ResultEncryption[16]};}
     if(Temp01 == "hit_Ua:")                   {Vrab0001 = 21; return {Config.ECD_ResultEncryption[17]};}
     if(Temp01 == "hit_Uj:")                   {Vrab0001 = 21; return {Config.ECD_ResultEncryption[18]};}
     if(Temp01 == "hit_ja:")                   {Vrab0001 = 21; return {Config.ECD_ResultEncryption[19]};}
     if(Temp01 == "mp:")                       {Vrab0001 = 21; return {Config.ECD_ResultEncryption[20]};}
     if(Temp01 == "sound:")                    {Vrab0001 = 15; return {Config.ECD_ResultEncryption[21]};}
     if(Temp01 == "bpoint:")                   {Vrab0001 = 4; return {Config.ECD_ResultEncryption[22]};}
     if(Temp01 == "cpoint:")                   {Vrab0001 = 5; return {Config.ECD_ResultEncryption[23]};}
     if(Temp01 == "wpoint:")                   {Vrab0001 = 6; return {Config.ECD_ResultEncryption[24]};}
     if(Temp01 == "opoint:")                   {Vrab0001 = 7; return {Config.ECD_ResultEncryption[25]};}
     if(Temp01 == "itr:")                      {Vrab0001 = 8; return {Config.ECD_ResultEncryption[26]};}
     if(Temp01 == "bdy:")                      {Vrab0001 = 9; return {Config.ECD_ResultEncryption[27]};}
    break;
    case 4:
     if(Temp01 == "bpoint_end:")               {Vrab0001 = 3; return {Config.ECD_ResultEncryption[0]};}
     if(Temp01 == "x:")                        {Vrab0001 = 22; return {Config.ECD_ResultEncryption[1]};}
     if(Temp01 == "y:")                        {Vrab0001 = 22; return {Config.ECD_ResultEncryption[2]};}
    break;
    case 5:
     if(Temp01 == "cpoint_end:")               {Vrab0001 = 3; return {Config.ECD_ResultEncryption[0]};}
     if(Temp01 == "kind:")                     {Vrab0001 = 23; return {Config.ECD_ResultEncryption[1]};}
     if(Temp01 == "x:")                        {Vrab0001 = 23; return {Config.ECD_ResultEncryption[2]};}
     if(Temp01 == "y:")                        {Vrab0001 = 32; return {Config.ECD_ResultEncryption[3]};}
     if(Temp01 == "vaction:")                  {Vrab0001 = 23; return {Config.ECD_ResultEncryption[4]};}
     if(Temp01 == "aaction:")                  {Vrab0001 = 23; return {Config.ECD_ResultEncryption[5]};}
     if(Temp01 == "daction:")                  {Vrab0001 = 23; return {Config.ECD_ResultEncryption[6]};}
     if(Temp01 == "jaction:")                  {Vrab0001 = 23; return {Config.ECD_ResultEncryption[7]};}
     if(Temp01 == "taction:")                  {Vrab0001 = 23; return {Config.ECD_ResultEncryption[8]};}
     if(Temp01 == "throwvx:")                  {Vrab0001 = 23; return {Config.ECD_ResultEncryption[9]};}
     if(Temp01 == "throwvy:")                  {Vrab0001 = 23; return {Config.ECD_ResultEncryption[10]};}
     if(Temp01 == "throwvz:")                  {Vrab0001 = 23; return {Config.ECD_ResultEncryption[11]};}
     if(Temp01 == "throwinjury:")              {Vrab0001 = 23; return {Config.ECD_ResultEncryption[12]};}
     if(Temp01 == "dircontrol:")               {Vrab0001 = 23; return {Config.ECD_ResultEncryption[13]};}
     if(Temp01 == "hurtable:")                 {Vrab0001 = 23; return {Config.ECD_ResultEncryption[14]};}
     if(Temp01 == "decrease:")                 {Vrab0001 = 23; return {Config.ECD_ResultEncryption[15]};}
     if(Temp01 == "cover:")                    {Vrab0001 = 23; return {Config.ECD_ResultEncryption[16]};}
     if(Temp01 == "injury:")                   {Vrab0001 = 23; return {Config.ECD_ResultEncryption[17]};}
     if(Temp01 == "fronthurtact:")             {Vrab0001 = 23; return {Config.ECD_ResultEncryption[18]};}
     if(Temp01 == "backhurtact:")              {Vrab0001 = 23; return {Config.ECD_ResultEncryption[19]};}
    break;
    case 6:
     if(Temp01 == "wpoint_end:")               {Vrab0001 = 3; return {Config.ECD_ResultEncryption[0]};}
     if(Temp01 == "kind:")                     {Vrab0001 = 24; return {Config.ECD_ResultEncryption[1]};}
     if(Temp01 == "x:")                        {Vrab0001 = 24; return {Config.ECD_ResultEncryption[2]};}
     if(Temp01 == "y:")                        {Vrab0001 = 33; return {Config.ECD_ResultEncryption[3]};}
     if(Temp01 == "dvx:")                      {Vrab0001 = 24; return {Config.ECD_ResultEncryption[4]};}
     if(Temp01 == "dvy:")                      {Vrab0001 = 24; return {Config.ECD_ResultEncryption[5]};}
     if(Temp01 == "dvz:")                      {Vrab0001 = 24; return {Config.ECD_ResultEncryption[6]};}
     if(Temp01 == "weaponact:")                {Vrab0001 = 24; return {Config.ECD_ResultEncryption[7]};}
     if(Temp01 == "attacking:")                {Vrab0001 = 24; return {Config.ECD_ResultEncryption[8]};}
     if(Temp01 == "cover:")                    {Vrab0001 = 24; return {Config.ECD_ResultEncryption[9]};}
    break;
    case 7:
     if(Temp01 == "opoint_end:")               {Vrab0001 = 3; return {Config.ECD_ResultEncryption[0]};}
     if(Temp01 == "kind:")                     {Vrab0001 = 25; return {Config.ECD_ResultEncryption[1]};}
     if(Temp01 == "x:")                        {Vrab0001 = 25; return {Config.ECD_ResultEncryption[2]};}
     if(Temp01 == "y:")                        {Vrab0001 = 34; return {Config.ECD_ResultEncryption[3]};}
     if(Temp01 == "dvx:")                      {Vrab0001 = 25; return {Config.ECD_ResultEncryption[4]};}
     if(Temp01 == "dvy:")                      {Vrab0001 = 25; return {Config.ECD_ResultEncryption[5]};}
     if(Temp01 == "oid:")                      {Vrab0001 = 38; return {Config.ECD_ResultEncryption[6]};}
     if(Temp01 == "action:")                   {Vrab0001 = 25; return {Config.ECD_ResultEncryption[7]};}
     if(Temp01 == "facing:")                   {Vrab0001 = 25; return {Config.ECD_ResultEncryption[8]};}
    break;
    case 8: case 29:
     if(Temp01 == "itr_end:")                  {Vrab0001 = 3; return {Config.ECD_ResultEncryption[0]};}
     if(Temp01 == "kind:")                     {Vrab0001 = 26; return {Config.ECD_ResultEncryption[1]};}
     if(Temp01 == "x:")                        {Vrab0001 = 26; return {Config.ECD_ResultEncryption[2]};}
     if(Temp01 == "y:")                        {Vrab0001 = 35; return {Config.ECD_ResultEncryption[3]};}
     if(Temp01 == "w:")                        {Vrab0001 = 26; return {Config.ECD_ResultEncryption[4]};}
     if(Temp01 == "h:")                        {Vrab0001 = 26; return {Config.ECD_ResultEncryption[5]};}
     if(Temp01 == "zwidth:")                   {Vrab0001 = 26; return {Config.ECD_ResultEncryption[6]};}
     if(Temp01 == "dvx:")                      {Vrab0001 = 26; return {Config.ECD_ResultEncryption[7]};}
     if(Temp01 == "dvy:")                      {Vrab0001 = 26; return {Config.ECD_ResultEncryption[8]};}
     if(Temp01 == "fall:")                     {Vrab0001 = 26; return {Config.ECD_ResultEncryption[9]};}
     if(Temp01 == "arest:")                    {Vrab0001 = 26; return {Config.ECD_ResultEncryption[10]};}
     if(Temp01 == "vrest:")                    {Vrab0001 = 26; return {Config.ECD_ResultEncryption[11]};}
     if(Temp01 == "respond:")                  {Vrab0001 = 26; return {Config.ECD_ResultEncryption[12]};}
     if(Temp01 == "effect:")                   {Vrab0001 = 26; return {Config.ECD_ResultEncryption[13]};}
     if(Temp01 == "bdefend:")                  {Vrab0001 = 26; return {Config.ECD_ResultEncryption[14]};}
     if(Temp01 == "injury:")                   {Vrab0001 = 26; return {Config.ECD_ResultEncryption[15]};}
     if(Temp01 == "catchingact:")              {Vrab0001 = 28; return {Config.ECD_ResultEncryption[16]};}
     if(Temp01 == "caughtact:")                {Vrab0001 = 28; return {Config.ECD_ResultEncryption[17]};}
     if(Vrab0001 == 29){Vrab0001 = 8; return string(1, Config.ECD_ResultEncryption[93]) + S_EncryptionUINT32(L_Numbering(Temp01));}
    break;
    case 9:
     if(Temp01 == "bdy_end:")                  {Vrab0001 = 3; return {Config.ECD_ResultEncryption[0]};}
     if(Temp01 == "kind:")                     {Vrab0001 = 27; return {Config.ECD_ResultEncryption[1]};}
     if(Temp01 == "x:")                        {Vrab0001 = 27; return {Config.ECD_ResultEncryption[2]};}
     if(Temp01 == "y:")                        {Vrab0001 = 36; return {Config.ECD_ResultEncryption[3]};}
     if(Temp01 == "w:")                        {Vrab0001 = 27; return {Config.ECD_ResultEncryption[4]};}
     if(Temp01 == "h:")                        {Vrab0001 = 27; return {Config.ECD_ResultEncryption[5]};}
    break;
    case 10: case 11: case 12:
     switch(Vrab0001){case 10: Vrab0001 = 2; break; case 11: Vrab0001 = 5; break; case 12: Vrab0001 = 8; break; default: break;} return "";
    case 13: case 18: case 41: case 49:
     switch(Vrab0001){case 13: Vrab0001 = 1; break; case 18: Vrab0001 = 3; break; case 41: Vrab0001 = 39; break; case 49: Vrab0001 = 2; break; default: break;} return S_EncryptionUINT32(Temp01.size()) + S_EncryptionSTRING(Temp01);
    case 14: case 15: case 45: case 46:
     switch(Vrab0001){case 14: Vrab0001 = 1; break; case 15: Vrab0001 = 3; break; case 45: Vrab0001 = 50; break; case 46: Vrab0001 = 40; break; default: break;} return S_EncryptionUINT32(L_Addressing(Temp01));
    case 16:
     Vrab0001 = 1; return S_EncryptionUINT32(L_Addressing(Temp01));
    case 32: case 33: case 34: case 35: case 36:
     {
      const int32 Vrab01 = L_Numbering(Temp01);
      const int32 Vrab02 = L_Indexing(L_Positive(Vrab01 - Vrab0003) / 1000000);
      if(Vrab02 != -1){int32 Vrab03 = Vect0001[Vrab02] * 1000000; if(Vrab01 < 0) Vrab03 = -Vrab03; switch(Vrab0001){case 32: Vrab0001 = 5; break; case 33: Vrab0001 = 6; break; case 34: Vrab0001 = 7; break; case 35: Vrab0001 = 8; break; case 36: Vrab0001 = 9; break; default: break;} return string(1, Config.ECD_ResultEncryption[93]) + S_EncryptionUINT32(Vrab02) + S_EncryptionUINT32(Vrab01 - Vrab03);}
     }
    case 17: case 19: case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 42: case 43: case 47: case 48:
     switch(Vrab0001){case 17: Vrab0001 = 18; break; case 19: Vrab0001 = 1; break; case 20: Vrab0001 = 2; break; case 21: Vrab0001 = 3; break; case 22: Vrab0001 = 4; break; case 23: case 32: Vrab0001 = 5; break; case 24: case 33: Vrab0001 = 6; break; case 25: case 34: Vrab0001 = 7; break; case 26: case 35: Vrab0001 = 8; break; case 27: case 36: Vrab0001 = 9; break; case 28: Vrab0001 = 29; break; case 42: Vrab0001 = 39; break; case 43: Vrab0001 = 44; break; case 47: Vrab0001 = 40; break; case 48: Vrab0001 = 49; break; default: break;} return S_EncryptionUINT32(L_Numbering(Temp01));
    case 30:
     {
      uint32 Vrab01 = Temp01.size() - 1;
      while(Vrab01 != ruint32(-1)) if(Temp01.at(Vrab01) == '.'){break;} else {Vrab01 -= 1;}
      int32 Vrab02 = 0; uint32 Vrab03 = 0;
      if(Vrab01 == ruint32(-1)){Vrab02 = L_Numbering(Temp01);} else {Vrab02 = L_Numbering(string(Temp01, 0, Vrab01 + 1)); string Temp02 = string(Temp01, Vrab01 + 1, Temp01.size() - (Vrab01 + 1)); while(Temp02.size() < 9) Temp02.push_back('0'); if(Temp02.at(8) < '0' || Temp02.at(8) > '9') Temp02.at(8) = '0'; Vrab03 = L_Numbering(Temp02);}
      Vrab0001 = 1; return S_EncryptionUINT32(ruint32(Vrab02)) + S_EncryptionUINT32(Vrab03);
     }
    case 31:
     Vrab0003 = L_Numbering(Temp01); Vrab0001 = 3;
     {
      const int32 Vrab01 = L_Indexing(L_Positive(Vrab0003) / 1000000);
      if(Vrab01 != -1){Vrab0003 %= 1000000; return string(1, Config.ECD_ResultEncryption[93]) + S_EncryptionUINT32(Vrab01) + S_EncryptionUINT32(Vrab0003);} else {return S_EncryptionUINT32(Vrab0003);}
     }
    case 37: case 38:
     {
      int32 Vrab01 = L_Numbering(Temp01); if(Vrab0001 == 37) if(Vrab01 / 1000 != 8){Vrab0001 = 3; return S_EncryptionUINT32(Vrab01);} else {Vrab01 %= 1000;}
      const int32 Vrab02 = L_Indexing(Vrab01);
      if(Vrab02 != -1){switch(Vrab0001){case 37: Vrab0001 = 3; break; case 38: Vrab0001 = 7; break; default: break;} return string(1, Config.ECD_ResultEncryption[93]) + S_EncryptionUINT32(Vrab02);}
     }
     switch(Vrab0001){case 37: Vrab0001 = 3; break; case 38: Vrab0001 = 7; break; default: break;} return S_EncryptionUINT32(L_Numbering(Temp01));
    case 50:
     Vrab0001 = 43; return "";
    break;
    case 39: case 44:
     if(Temp01 == "name:")                     {Vrab0001 = 41; return {Config.ECD_ResultEncryption[0]};}
     if(Temp01 == "width:")                    {Vrab0001 = 42; return {Config.ECD_ResultEncryption[1]};}
     if(Temp01 == "zboundary:")                {Vrab0001 = 43; return {Config.ECD_ResultEncryption[2]};}
     if(Temp01 == "perspective:")              {Vrab0001 = 43; return {Config.ECD_ResultEncryption[3]};}
     if(Temp01 == "shadow:")                   {Vrab0001 = 45; return {Config.ECD_ResultEncryption[4]};}
     if(Temp01 == "layer:")                    {Vrab0001 = 46; return {Config.ECD_ResultEncryption[5]};}
     if(Vrab0001 == 44){Vrab0001 = 39; return string(1, Config.ECD_ResultEncryption[93]) + S_EncryptionUINT32(L_Numbering(Temp01));}
    break;
    case 40:
     if(Temp01 == "layer_end")                 {Vrab0001 = 39; return {Config.ECD_ResultEncryption[0]};}
     if(Temp01 == "transparency:")             {Vrab0001 = 47; return {Config.ECD_ResultEncryption[1]};}
     if(Temp01 == "width:")                    {Vrab0001 = 47; return {Config.ECD_ResultEncryption[2]};}
     if(Temp01 == "height:")                   {Vrab0001 = 47; return {Config.ECD_ResultEncryption[3]};}
     if(Temp01 == "x:")                        {Vrab0001 = 47; return {Config.ECD_ResultEncryption[4]};}
     if(Temp01 == "y:")                        {Vrab0001 = 47; return {Config.ECD_ResultEncryption[5]};}
     if(Temp01 == "cc:")                       {Vrab0001 = 47; return {Config.ECD_ResultEncryption[6]};}
     if(Temp01 == "c1:")                       {Vrab0001 = 47; return {Config.ECD_ResultEncryption[7]};}
     if(Temp01 == "c2:")                       {Vrab0001 = 47; return {Config.ECD_ResultEncryption[8]};}
     if(Temp01 == "rect:")                     {Vrab0001 = 47; return {Config.ECD_ResultEncryption[9]};}
     if(Temp01 == "rect32:")                   {Vrab0001 = 47; return {Config.ECD_ResultEncryption[10]};}
    break;
    default: break;
   }
   Vrab0002 = 1;
   return "";
  }

  int1   M_EncryptionFile(const uint8 Vrab01, string Temp01)
  {
   std::ifstream File01; std::ifstream File02; string Temp02; string Temp03; std::vector < uint32 > Vect01; uint32 Vrab02 = 0; uint32 Vrab03 = 0; uint32 Vrab04 = 0; uint8 Vrab07 = 0; uint32 Vrab08 = 0;
   
   switch(Vrab01)
   {
    case 1: case 3: case 4: goto Labl01;
    case 2: case 6:
     if(L_Lowercase(string(Temp01, Temp01.size() - 4, 4)) == ".dat")
     {
      File01.open(Temp01, std::ios::binary | std::ios::in); 
      std::stringstream Temp04; Temp04 << File01.rdbuf(); File01.close();
      Temp02 = Temp04.str(); Temp03 = ENCODING_KEY;
      Vrab02 = Temp02.size(); Vrab03 = 12; Vrab04 = Temp03.size();
      for(uint32 Vrab05 = 123; Vrab05 < Vrab02; ++Vrab05){Temp02.at(Vrab05) -= Temp03.at(Vrab03); Vrab03 += 1; if(Vrab03 == Vrab04) Vrab03 = 0;}
      std::ofstream File03(TEMPORAL_FILE, std::ios::binary | std::ios::out); Temp02.erase(0, 123); File03 << Temp02; File03.close();
      File01.open(TEMPORAL_FILE, std::ios::binary | std::ios::in);
     } else {File01.open(Temp01, std::ios::binary | std::ios::in);}
     Temp03 = ""; if(Vrab01 == 6){Vrab0001 = 39;} else {Vrab0001 = 0;} Vrab0002 = 0; Vrab02 = 0;
     while(File01)
     {
      File01 >> Temp02; if(!File01) break; if(Temp02[0] == '#'){std::getline(File01, Temp02); continue;}
      switch(Vrab0001)
      { 
      case 14: case 15: case 16: case 45: case 46: Vrab03 = Strn0001.size(); L_Addressing(Temp02); if(Vrab03 == Strn0001.size()){break;} else {Strn0001.pop_back();} if(Temp02 == Temp01){Console.PrintWrite(">< >> >> ERROR - Requesting for \"" + Temp02 + "\", but are you sure about it?\n"); Console.PrintSet(); break;} File02.open(Temp02, std::ios::binary | std::ios::in); if(File02.is_open())
       {
        string Temp05 = string(Temp02, 0, Temp02.size() - 4) + "_mirror" + string(Temp02, Temp02.size() - 4, 4);
        if(Vrab0001 == 16)
        {Console.PrintWrite("[] >> >> Requesting for \"" + Temp02 + "\" and it's mirror to be packed into the package.\n"); Console.PrintSet();} else 
        {Console.PrintWrite("[] >> >> Requesting for \"" + Temp02 + "\" to be packed into the package.\n"); Console.PrintSet();} std::stringstream Temp04; Temp04 << File02.rdbuf(); if(L_Lowercase(string(Temp02, Temp02.size() - 4, 4)) == ".bmp")
        {
         Console.PrintWrite("[] >> Packing \"" + Temp02 + "\" into the package.\n"); Console.PrintSet();
        if(Vrab0001 == 16)
        {
         if(M_EncryptionFile(3, Temp02))
         {
          M_EncryptionFile(0, S_EncryptionUINT32(L_Addressing(Temp02)) + Temp04.str()); Temp04.str(""); File02.close();
          File02.open(Temp05, std::ios::binary | std::ios::in); if(File02.is_open())
          {
           Console.PrintWrite("[] >> Packing \"" + Temp05 + "\" into the package.\n"); Console.PrintSet();
           Temp04 << File02.rdbuf(); if(M_EncryptionFile(4, Temp05)) M_EncryptionFile(5, Temp04.str());
          } else
          {Console.PrintWrite(">< >> ERROR - Either \"" + Temp05 + "\" cannot be opened or it does not exist. Please provide the mirrored image if your image already compressed.\n"); Console.PrintSet();}
         } else {Console.PrintWrite("() >> INFO - \"" + Temp05 + "\" is skipped due to \"" + Temp02 + "\" is uncompressed, means the mirror could be generated on installation.\n"); Console.PrintSet();}
        } else
        {
         if(M_EncryptionFile(1, Temp02)) M_EncryptionFile(0, S_EncryptionUINT32(L_Addressing(Temp02)) + Temp04.str());}
        } else {Console.PrintWrite("[] >> Including \"" + Temp02 + "\" into the package.\n"); Console.PrintSet(); M_EncryptionFile(0, S_EncryptionUINT32(L_Addressing(Temp02)) + Temp04.str());} if(File02.is_open()) File02.close();} else {Console.PrintWrite(">< >> >> ERROR - Either \"" + Temp02 + "\" cannot be opened or it does not exist.\n"); Console.PrintSet();} break;
       default: break;
      }
      Temp03 += S_EncryptionCHARDATA(Temp02);
      if(Vrab0002 != 0){switch(Vrab0002)
      {
      case 1: if(Vrab02 < 10){Console.PrintWrite(")( >> >> WARNING - Unknown syntax, \"" + Temp02 + "\", detected. [Exit code : " + std::to_string(Vrab0001) + "]\n"); Console.PrintSet(); Vrab02 += 1;} if(Vrab02 == 10){Console.PrintWrite(")( >> >> WARNING - Too many unknown syntaxes detected.\n"); Console.PrintSet(); Vrab02 += 1;} break;
       default: break;
      } Vrab0002 = 0;}
     }
     File01.close(); L_Polish(); if(Vrab01 == 6){if(Vrab0001 != 39){return true;} else {File0002 << Config.ECD_ResultEncryption[8];}} else {if(Vrab0001 != 0){return true;} else {File0002 << Config.ECD_ResultEncryption[4];}}
     File0002 << S_EncryptionUINT32(L_Addressing(Temp01)) << S_EncryptionUINT32(Temp03.size()) << S_EncryptionSTRING(Temp03);
    break;
    case 5: default:
     if(Vrab01 == 5){File0002 << Config.ECD_ResultEncryption[7];} else {File0002 << Config.ECD_ResultEncryption[2];} File0002 << string(Temp01, 0, 5) << S_EncryptionUINT32(Temp01.size() - 5) << S_EncryptionSTRING(string(Temp01, 5, Temp01.size() - 5));
    break;
   }
   return false;
   Labl01:
   BMP Bitm01(Temp01.c_str()); Vrab02 = Bitm01.bmp_info_header.width * Bitm01.bmp_info_header.height; if(Bitm01.bmp_info_header.compression != 3 && Bitm01.bmp_info_header.bit_count != 3 && Bitm01.bmp_info_header.size_image != 0 && Bitm01.data.size() != Vrab02 * 3) return true;
   Vrab04 = Bitm01.data.size();
   Labl02: Vrab03 = 0; Temp02 = ""; Vect01.clear(); Vrab02 = 0;
   while(Vrab03 != Vrab04)
   {
    const uint32 Vrab05 = ruint32(Bitm01.data[Vrab03]) + (ruint32(Bitm01.data[Vrab03 + 1]) << 8) + (ruint32(Bitm01.data[Vrab03 + 2]) << 16);
    if(Vrab05 == Vrab02){Vrab08 += 1; if(Vrab08 > 281){Temp02 += Config.ECD_ResultEncryption[91]; Temp02 += Config.ECD_ResultEncryption[93]; Vrab08 = 0;} Vrab03 += 3; continue;} else {if(Vrab08 > 0){Temp02 += Config.ECD_ResultEncryption[93 - ((Vrab08 - 1) / 94)]; Temp02 += Config.ECD_ResultEncryption[(Vrab08 - 1) % 94];} Vrab08 = 0;}
    const uint32 Vrab06 = Vect01.size(); Vrab02 = 0; while(Vrab02 != Vrab06){if(Vect01[Vrab02] == Vrab05) break; Vrab02 += 1;} if(Vrab02 == Vrab06) Vect01.push_back(Vrab05);
    switch(Vrab07){case 1: if(Vrab02 == 8833){Vrab07 = 2; goto Labl02;} break; case 2: if(Vrab02 == 830581){Vrab07 = 3; goto Labl02;} break; case 4: break; default: if(Vrab02 == 91){Vrab07 = 1; goto Labl02;} break;}
    switch(Vrab07){case 1: Temp02 += S_EncryptionUINT10(Vrab02); break; case 2: Temp02 += S_EncryptionUINT18(Vrab02); break; case 3: Temp02 += S_EncryptionUINT24(Vrab02); break; default: Temp02 += S_EncryptionUINT4(Vrab02); break;} Vrab02 = Vrab05;
    Vrab03 += 3;
   }
   Vrab02 = 0; Vrab03 = Vect01.size();
   if(Vrab01 == 4){File0002 << Config.ECD_ResultEncryption[6];} else {if(Vrab01 == 3){File0002 << Config.ECD_ResultEncryption[5];} else {File0002 << Config.ECD_ResultEncryption[3];}}
   File0002 << S_EncryptionUINT32(L_Addressing(Temp01)) << S_EncryptionUINT32(Bitm01.bmp_info_header.width) << S_EncryptionUINT32(Bitm01.bmp_info_header.height) << Config.ECD_ResultEncryption[Vrab07] << S_EncryptionUINT24(Vrab03);
   while(Vrab02 != Vrab03){File0002 << S_EncryptionUINT24(Vect01[Vrab02]); Vrab02 += 1;} File0002 << S_EncryptionUINT32(Temp02.size()) << S_EncryptionSTRING(Temp02);
   return false;
  }

  int0   C_MAIN_Configuration()                               
  {
   uint32 Vrab01 = 0; int32 Vrab02 = 0; string Temp01 = "true"; string Temp02 = "false"; string Temp03; if(L_Open(TEMPORAL_FILE)){File0001.seekg(0, File0001.end); if(File0001.tellg() > 295){File0001.seekg(File0001.tellg() - static_cast < std::streampos > (94)); Temp01.resize(94); File0001.read(&Temp01.at(0), 94); if(Temp01 == BASE_ENCRYPTION){Vrab01 = 1; File0001.seekg(0, File0001.beg); std::stringstream Temp04; Temp04 << File0001.rdbuf(); Temp03 = Temp04.str(); Temp03.erase(0, 200); Temp03.erase(Temp03.size() - 94, 94); strcpy(&Config.ECD_ResultEncryption[0], string(BASE_ENCRYPTION).c_str()); L_Create(TEMPORAL_FILE); File0002 << S_EncryptionSTRING(Temp03); File0002.close();}}} else {L_Create(TEMPORAL_FILE); File0002 << "Do not erase this file."; File0002.close();}
   Labl01: strcpy(&Config.ECD_ResultEncryption[0], string(BASE_ENCRYPTION).c_str()); if(Vrab01 == 1){Temp03 = TEMPORAL_FILE;} else {Temp03 = CONFIGURATION;}
   if(L_Open(Temp03))
   {
    while(File0001){File0001 >> Temp03; if(Temp03 == INJECTOR_VERSION) goto Labl03;} goto Labl02; Labl03: File0001.seekg(0, File0001.beg); while(File0001){File0001 >> Temp03; if(Temp03 == "Mesujin.") goto Labl04;} goto Labl02; Labl04: File0001.seekg(0, File0001.beg); while(File0001){File0001 >> Temp03; if(Temp03 == "Doix,") goto Labl05;} goto Labl02; Labl05: File0001.seekg(0, File0001.beg); while(File0001){File0001 >> Temp03; if(Temp03 == "Som1Lse,") goto Labl06;} goto Labl02; Labl06: File0001.seekg(0, File0001.beg); while(File0001){File0001 >> Temp03; if(Temp03 == "zort,") goto Labl07;} goto Labl02; Labl07: File0001.seekg(0, File0001.beg); while(File0001){File0001 >> Temp03; if(Temp03 == "Determination,"){File0001 >> Temp01 >> Temp03 >> Temp02; break;}} File0001.seekg(0, File0001.beg);
    while(File0001)
    {
     File0001 >> Temp03; if(!File0001) break;
	 if(Temp03.at(0) == '/') if(Temp03.at(1) == '/'){std::getline(File0001, Temp03); continue;}
     if(Temp03 == "Determination,"){File0001 >> Temp03 >> Temp03 >> Temp03; continue;}

     if(Temp03 == "AI")                 {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.MAIN_AI = Temp03 == Temp01; continue;}
     if(Temp03 == "DLL")                {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.MAIN_DLL = Temp03 == Temp01; continue;}
     if(Temp03 == "ECD")                {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.MAIN_ECD = Temp03 == Temp01; continue;}
     if(Temp03 == "MOD")                {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.MAIN_MOD = Temp03 == Temp01; continue;}
     if(Temp03 == "Hidden_Mode")        {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; if(Temp03 == Temp01){Config.MAIN_HiddenMode = true; if(Vrab01 != 1) Vrab01 = 2;} else {Config.MAIN_HiddenMode = false; Vrab01 = 0;} continue;}

     #ifdef MULTI_STATE
      if(Temp03 == "AI_Console")        {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.AI_Console = Temp03 == Temp01; continue;}
     #endif
     #ifdef DEBUG_VERSION
      if(Temp03 == "AI_ConsoleSize")    {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.AI_ConsoleSize = rint16(Vrab02); continue;}
      if(Temp03 == "AI_ConsoleStyle")   {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.AI_ConsoleStyle = rint8(Vrab02); continue;}
      if(Temp03 == "AI_ConsoleScroll")  {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.AI_ConsoleScroll = Temp03 == Temp01; continue;}
     #endif
     if(Temp03 == "AI_Directory")       {File0001 >> Temp03 >> Temp03; Config.AI_Directory = L_Manage(Temp03); continue;}
     if(Temp03 == "AI_OldDirectory")    {File0001 >> Temp03 >> Temp03; Config.AI_OldDirectory = L_Manage(Temp03); continue;}

     if(Temp03 == "DLL_Directory")      {File0001 >> Temp03 >> Temp03; Config.DLL_Directory = L_Manage(Temp03); continue;}
     if(Temp03 == "DLL_Progressive")    {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.DLL_Progressive = Temp03 == Temp01; continue;}
     
     if(Temp03 == "ECD_Console")        {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.ECD_Console = Temp03 == Temp01; continue;}
     if(Temp03 == "ECD_ConsoleStyle")   {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_ConsoleStyle = rint16(Vrab02); continue;}
     if(Temp03 == "ECD_ConsoleDelay")   {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_ConsoleDelay = rint16(Vrab02); continue;}
     if(Temp03 == "ECD_ResultDirectory"){File0001 >> Temp03 >> Temp03; Config.ECD_ResultDirectory = Temp03; continue;}
     
     if(Temp03 == "Directory")          {File0001 >> Temp03 >> Temp03; Config.ECD_BuildDirectory = L_Manage(Temp03); continue;}

     if(Temp03 == "Inputs")             {File0001 >> Temp03 >> Temp03; Config.ECD_InstallDirectory = L_Manage(Temp03); continue;}
     if(Temp03 == "Insight")            {File0001 >> Temp03 >> Temp03; Config.ECD_InstallDataDirectory = L_Manage(Temp03); continue;}
     if(Temp03 == "Outsight")           {File0001 >> Temp03 >> Temp03; Config.ECD_InstallODataDirectory = L_Manage(Temp03); continue;}
     if(Temp03 == "Overwrite")          {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.ECD_InstallOverwrite = Temp03 == Temp01; continue;}
     if(Temp03 == "NoMirroring")        {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.ECD_InstallNoMirrors = Temp03 == Temp01; continue;}
     if(Temp03 == "Permanentness")      {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.ECD_InstallPermanent = Temp03 == Temp01; continue;}
     if(Temp03 == "DefaultLocation")    {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.ECD_InstallSeparated = Temp03 == Temp01; continue;}
     if(Temp03 == "HiddenIDs")          {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[0] = Vrab02; File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[1] = Vrab02; continue;}
     if(Temp03 == "WeaponIDs")          {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[2] = Vrab02; File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[3] = Vrab02; continue;}
     if(Temp03 == "MinionIDs")          {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[4] = Vrab02; File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[5] = Vrab02; continue;}
     if(Temp03 == "MinionIDs2")         {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[6] = Vrab02; File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[7] = Vrab02; continue;}
     if(Temp03 == "AvailableIDs")       {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[8] = Vrab02; File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[9] = Vrab02; continue;}
     if(Temp03 == "AvailableIDs2")      {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[10] = Vrab02; File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[11] = Vrab02; continue;}
     if(Temp03 == "AvailableIDs3")      {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[12] = Vrab02; File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_InstallDataIDs[13] = Vrab02; continue;}
     if(Temp03 == "CodeFormat")         {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.ECD_ResultCodeFormat = rint8(Vrab02); continue;}
     if(Temp03 == "Key")                {File0001 >> Temp03 >> Temp03; if(Temp03.size() != 94) goto Labl02; strcpy(&Config.ECD_ResultEncryption[0], Temp03.c_str()); continue;}
     
     if(Temp03 == "MOD_Level")          {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.MOD_ModulingLevel = rint8(Vrab02); continue;}
     if(Temp03 == "MOD_StartingFrame")  {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.MOD_ModulingLevelStartingFrame = Vrab02; continue;}
     
     if(Temp03 == "MOD_Info")           {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.MOD_ModulingInfo = Temp03 == Temp01; continue;}
     if(Temp03 == "MOD_InfoTrans")      {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.MOD_ModulingInfoTrans = Temp03 == Temp01; continue;}
     if(Temp03 == "MOD_InfoPosition")   {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.MOD_ModulingInfoPostition = Vrab02; continue;}
     
     if(Temp03 == "ResultFormat")       {File0001 >> Temp03 >> Temp03; Vrab02 = L_Numbering(Temp03); if(Vrab02 < 0) goto Labl02; Config.MOD_ResultFormat = Vrab02; continue;}
     if(Temp03 == "ResultFraming")      {File0001 >> Temp03 >> Temp03; if(Temp03 != Temp01 && Temp03 != Temp02) goto Labl02; Config.MOD_ResultFraming = Temp03 == Temp01; continue;}
     if(Temp03 == "ResultExtension")    {File0001 >> Temp03 >> Temp03; if(Temp03 == "_"){Config.MOD_ResultExtension = "";} else {Config.MOD_ResultExtension = Temp03;} if(L_Lowercase(Config.MOD_ResultExtension) == "dat") goto Labl02; continue;}
     if(Temp03 == "ResultDirectory")    {File0001 >> Temp03 >> Temp03; Config.MOD_ResultDirectory = Temp03; continue;}
     
     if(Temp03 == "sagasofkoasjgkasfjaksgraoidjaskhlasjfikshfrkentmheifjhaskfasflaksjoinufiasjfkasjfkastjgttwnaokd i just want to get a perfect size in this case ;p iajidjaiodhasoig///////////////////dagsaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaasaijdioasjdkashfasjkdhafkhaskdjwhglnjefhsdjeighwkjajbhjds,gewjkfhfhdsjfhw,kahw,faewgdjfkjkawgopewhbkdscmsdklbndow;fjasflaskjdlsahgldjsokkdgfkhdghdsl.fjdsopbe,fnekthakmeyaiofamkdmfa oags  im surely this is stupid idea but who cares, :< aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa this string not even have asodkaoskdaoskdokosakfoakwoawjifawjkwawwfnlaskfslkfjaslkjsalkdajslkdjaskd size sdaidjsiajdasfoasdjoasdjaosdjsaodjasodasj doathisfskdajsjkdnsakgask lasjfhsakhd aks k fkasfka k afa                                                                                hlaskhasdihakgnakfnasdkasbdasjdbaifjabdasdnsaj  aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa alsdaaaaaaaaaaanbkdnf;osfdskjfsaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaafdafaddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddfd/"){File0001 >> Temp03; continue;}

     goto Labl02;
    }
   } else {Labl02: Vrab01 = 0; if(!L_Create(CONFIGURATION)) return; File0002 << CONFIG_TEXT; File0002.close(); goto Labl01;}
   
   if(Vrab01 != 0){if(Vrab01 == 1){Temp03 = TEMPORAL_FILE;} else {Temp03 = CONFIGURATION;} if(L_Open(Temp03)){std::stringstream Temp04; Temp04 << File0001.rdbuf(); Database.Config = Temp04.str(); File0001.close(); std::remove(CONFIGURATION);} else {Database.Config = "";} L_Create(TEMPORAL_FILE); File0002 << "Do not erase this file."; File0002.close();} if(L_Exist(Config.ECD_ResultDirectory + "\\summary.edb") || L_Exist(Config.ECD_InstallODataDirectory)){if(Config.ECD_InstallPermanent){Config.ECD_InstallPermanent = false; G_Cleaning(); Config.ECD_InstallPermanent = true;} else {G_Cleaning();}}
   L_Cleaning();
  }
  int0   C_ECD_Construction()                                         {Console.PrintWrite("[] Preparing the construction.\n"); Console.PrintSet(); int8 Varb01[95]; strcpy(&Varb01[0], &Config.ECD_ResultEncryption[0]);
   Console.PrintWrite("[] Seeking for constructor(s) in \"" + Config.ECD_BuildDirectory + "\".\n"); Console.PrintSet();
   if(L_Exist(Config.ECD_BuildDirectory))
   {
    uint32 Vrab01 = 0; int1 Vrab08 = false;
    for(auto const &Temp01 : std::filesystem::recursive_directory_iterator(Config.ECD_BuildDirectory))
    {
     string Temp02 = Temp01.path().string(); if(Temp02.at(Config.ECD_BuildDirectory.size()) == '#') continue; 
     uint32 Vrab02 = Temp02.size() - 1; while(Vrab02 != -1) if(Temp02.at(Vrab02) == '\\'){break;} else {Vrab02 -= 1;} Vrab02 += 1;
     if(L_Lowercase(string(Temp02, Vrab02, Temp02.size() - Vrab02)) == "build.txt")
     {
      if(Vrab08){Console.PrintWrite("() INFO - Construction failed.\n"); Console.PrintSet();} else {Vrab08 = true;}
      Vrab01 += 1; Console.PrintWrite("[] \"" + Temp01.path().string() + "\" found.\n"); Console.PrintSet();
      if(L_Open(Temp01.path().string()))
      {
       strcpy(&Config.ECD_ResultEncryption[0], string(BASE_ENCRYPTION).c_str()); Vrab02 = 0;
       while(File0001){File0001 >> Temp02; if(!File0001) break; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
       if(Temp02 == "<data>")
       {
        while(File0001){File0001 >> Temp02; if(!File0001) break; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
        if(Temp02 == "back:"){if(Vrab02 == 0){Vrab02 = 2;} else {if(Vrab02 == 1) Vrab02 = 3;} continue;}
         if(Temp02 == "file:"){if(Vrab02 == 0){Vrab02 = 1;} else {if(Vrab02 == 2) Vrab02 = 3;} continue;}
         if(Temp02 == "data:"){if(Vrab02 == 0){Vrab02 = 1;} else {if(Vrab02 == 2) Vrab02 = 3;} continue;}
          if(Temp02 == "<data_end>") break;
        }
        break;
       }
       }
       if(Vrab02 == 0){Console.PrintWrite(">< ERROR - This constructor has nothing to construct.\n"); Console.PrintSet(); continue;} if(File0001){File0001.seekg(0);} else {L_Open(Temp01.path().string());} int1 Vrab03 = false;
       while(File0001)
       {
        File0001 >> Temp02; if(!File0001) break; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
        if(Temp02 == "<config>")
        {
         while(File0001)
         {
          File0001 >> Temp02; if(!File0001) break; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
          if(Temp02 == "module:"){if(Vrab02 == 3){Vrab02 = 5;} else {if(Vrab02 == 2){Vrab02 = 6;} else {Vrab02 = 4;}} continue;}
          if(Temp02 == "overwrite:"){File0001 >> Temp02; Vrab03 = Temp02 != "true"; continue;}
          if(Temp02 == "<config_end>") break;
         }
         break;
        }
       } if(File0001){File0001.seekg(0);} else {L_Open(Temp01.path().string());} string Temp03;
       while(File0001)
       {
        File0001 >> Temp02; if(!File0001) break; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
        if(Temp02 == "<config>")
        {
         while(File0001)
         {
          File0001 >> Temp02; if(!File0001) break; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
          if(Temp02 == "out:"){File0001 >> Temp03; Temp03 = L_Manage(Temp03); switch(Vrab02){case 1: Temp03 += ".ecd"; break; case 2: Temp03 += ".ebd"; break; case 3: Temp03 += ".egd"; break; case 4: Temp03 += ".pcd"; break; case 5: Temp03 += ".pgd"; break; default: Temp03 += ".pbd"; break;} if(Vrab03) while(L_Exist(Config.ECD_ResultDirectory + "\\" + Temp03)) L_Rename(Temp03); continue;}
          if(Temp03 == "key:"){File0001 >> Temp03; if(Temp03.size() != 94) goto Labl02; strcpy(&Config.ECD_ResultEncryption[0], Temp03.c_str()); continue;}
          if(Temp02 == "<config_end>"){if(Temp03 == ""){Labl02: Console.PrintWrite(")( WARNING - \"out:\" is undefined, naming the result as \""); Temp03 = "0000 - Unknown"; switch(Vrab02){case 1: Temp03 += ".ecd"; break; case 2: Temp03 += ".ebd"; break; case 3: Temp03 += ".egd"; break; case 4: Temp03 += ".pcd"; break; case 5: Temp03 += ".pgd"; break; default: Temp03 += ".pbd"; break;} if(Vrab03) while(L_Exist(Config.ECD_ResultDirectory + "\\" + Temp03)) L_Rename(Temp03); Console.PrintWrite(Temp03 + "\" instead.\n"); Console.PrintSet();} goto Labl01;}
         }
         goto Labl01;
        }
       }
       Console.PrintWrite(")( WARNING - \"<config>\" is undefined, forcefully resuming the process.\n"); Console.PrintSet(); goto Labl02;
       Labl01:
       if(L_Create(L_Execute(Config.ECD_ResultDirectory + "\\" + Temp03))){Console.PrintWrite("[] Constructing \"" + Config.ECD_ResultDirectory + "\\" + Temp03 + "\".\n"); Console.PrintSet();} else {Console.PrintWrite(">< ERROR - Cannot construct \"" + Config.ECD_ResultDirectory + "\\" + Temp03 + "\".\n"); Console.PrintSet(); continue;}
       if(File0001){File0001.seekg(0);} else {L_Open(Temp01.path().string());} Vect0001.clear(); std::vector < int32 > Vect01; std::vector < int32 > Vect02; std::vector < int32 > Vect03; Vect02; std::vector < uint32 > Vect04;
       while(File0001)
       {
        File0001 >> Temp02; if(!File0001) break; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
        if(Temp02 == "<data>")
        {
         Vrab02 = 0;
         while(File0001)
         {
          File0001 >> Temp02; if(!File0001) break; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
          if(Temp02 == "num:"){File0001 >> Temp02; if(Vect04.size() > 0) Vect04[Vect04.size() - 1] = L_Positive(L_Numbering(Temp02));}
          if(Temp02 == "back:"){File0001 >> Temp02; Vect04.resize(Vect04.size() + 1); continue;}
          if(Temp02 == "id:"){File0001 >> Temp02; Vect0001.push_back(L_Positive(L_Numbering(Temp02))); Vrab02 += 1; Vect01.push_back(0); Vect02.push_back(0); Vect03.push_back(0); continue;}
          if(Temp02 == "type:"){File0001 >> Temp02; if(Vrab02 != 0) Vect01[Vrab02 - 1] = L_Positive(L_Numbering(Temp02)); continue;}
          if(Temp02 == "set:"){File0001 >> Temp02; if(Vrab02 != 0) Vect02[Vrab02 - 1] = L_Positive(L_Numbering(Temp02)); continue;}
          if(Temp02 == "range:"){File0001 >> Temp02; if(Vrab02 != 0) Vect03[Vrab02 - 1] = L_Positive(L_Numbering(Temp02)); continue;}
          if(Temp02 == "<data_end>") break;
         }
         break;
        }
       }
       if(File0001){File0001.seekg(0);} else {L_Open(Temp01.path().string());} std::vector < string > Strn01; std::vector < string > Strn02; std::vector < std::ifstream > Init01;
       while(File0001)
       {
        File0001 >> Temp02; if(!File0001) break; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
        if(Temp02 == "<config>")
        {
         while(File0001)
         {
          File0001 >> Temp02; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
          if(Temp02 == "module:"){File0001 >> Temp02; Vrab03 = true; Init01.resize(Init01.size() + 1); Strn01.push_back(Temp02); string Temp04 = L_Lowercase(Temp02); Vrab02 = Temp04.size(); while(Vrab02 != 1 && Temp04.at(Vrab02 - 1) != '\\') Vrab02 -= 1; Temp04.erase(0, Vrab02); Strn02.push_back(Temp04); if(Temp04.at(0) != '_' && string(Temp04, Temp04.size() - 3, 3) != ".as"){Console.PrintWrite(">< >> ERROR - \"" + Temp04 + "\" is a wrong filename for a Module, the filename should be started with \"_\" character and it's should be an \".as\" file.\n"); Console.PrintSet(); Vrab03 = false;} else {Init01[Init01.size() - 1].open(Temp02, std::ios::binary | std::ios::in);} if(!Init01[Init01.size() - 1].is_open()) if(Vrab03){Console.PrintWrite(">< >> ERROR - Requesting a Module, but either \"" + Temp02 + "\" cannot be opened or it does not exist.\n"); Console.PrintSet();} continue;}
          if(Temp02 == "<config_end>") break;
         }
         break;
        }
       }
       const uint32 Vrab06 = Strn01.size(); uint32 Vrab07 = 0;
       while(Vrab07 != Vrab06)
       {
        if(Init01[Vrab07].is_open()) break;
        Vrab07 += 1;
       }
       if(Vrab07 == Vrab06 && Vrab02 > 3){File0002.close(); std::remove((Config.ECD_ResultDirectory + "\\" + Temp03).c_str()); Console.PrintWrite("() INFO - Reconstructing \"" + Config.ECD_ResultDirectory + "\\" + Temp03 + "\" as \""); Temp03.erase(Temp03.size() - 3, 1); Temp03.insert(Temp03.size() - 2, "e"); Console.PrintWrite(Config.ECD_ResultDirectory + "\\" + Temp03 + "\" instead.\n"); Console.PrintSet(); L_Create(L_Execute(Config.ECD_ResultDirectory + "\\" + Temp03));}
       File0002 << "# ===      An encrypted file, which is especially made for LF2.      === #\n\n\n\n\n\n\n     Are you trying to read this file with a Notepad?\n\n                                           What a nice move, dude.\n\n\n\n\n\n\n# ===       Created using Modified DDraw, modified by Mesujin.       === #\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
       Vrab07 = 0;
       while(Vrab07 != Vrab06)
       {
        if(Init01[Vrab07].is_open()){Console.PrintWrite("[] >> Module detected, including \"" + Strn01[Vrab07] + "\" "); File0002 << Config.ECD_ResultEncryption[0]; const uint32 Vrab04 = L_Positive(L_Numbering(string(Strn02[Vrab07], 1, Strn02[Vrab07].size() - 3))); Vrab02 = 0; const uint32 Vrab05 = Vect0001.size(); while(Vrab02 != Vrab05){if(Vrab04 == ruint32(Vect0001[Vrab02])) break; Vrab02 += 1;} if(Vrab02 != Vrab05){File0002 << Config.ECD_ResultEncryption[0] << S_EncryptionUINT32(Vrab02); Console.PrintWrite("into the package.\n");} else {Temp02 = "_" + std::to_string(Vrab04) + ".as"; File0002 << Config.ECD_ResultEncryption[1] << S_EncryptionUINT32(Vrab04); if(Temp02 == Strn02[Vrab07]){Console.PrintWrite("into the package.\n");} else {Console.PrintWrite("as \"_" + std::to_string(Vrab04) + ".as\" into the package.\n");}} Console.PrintSet(); std::stringstream Temp05; Temp05 << Init01[Vrab07].rdbuf(); Temp02 = Temp05.str(); File0002 << S_EncryptionUINT32(Temp02.size()) << S_EncryptionSTRING(Temp02); Init01[Vrab07].close();}
        Vrab07 += 1;
       }
       Strn01.clear(); Strn02.clear(); Init01.clear(); Init01.resize(1); if(Init01[0].is_open()) Init01[0].close(); if(File0001){File0001.seekg(0);} else {L_Open(Temp01.path().string());}
       
       while(File0001)
       {
        File0001 >> Temp02; if(!File0001) break; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
        if(Temp02 == "<config>")
        {
         while(File0001)
         {
          File0001 >> Temp02; if(!File0001) break; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
          if(Temp02 == "ai:"){File0001 >> Temp02; string Temp04 = L_Lowercase(Temp02); Vrab02 = Temp04.size(); while(Vrab02 != 1 && Temp04.at(Vrab02 - 1) != '\\') Vrab02 -= 1; Temp04.erase(0, Vrab02); if(string(Temp04, Temp04.size() - 3, 3) != ".as"){Console.PrintWrite(">< >> ERROR - \"" + Temp04 + "\" is a wrong file for an AI-Script, it's should be an \".as\" file.\n"); Console.PrintSet(); continue;} else {const uint32 Vrab04 = L_Positive(L_Numbering(string(Temp04, 0, Temp04.size() - 3))); Vrab02 = 0; const uint32 Vrab05 = Vect0001.size(); while(Vrab02 != Vrab05){if(Vrab04 == ruint32(Vect0001[Vrab02])) break; Vrab02 += 1;} if(Vrab02 != Vrab05){Init01[0].open(Temp02, std::ios::binary | std::ios::in);} else {Console.PrintWrite(">< >> ERROR - The number of this AI-Script, \"" + Temp04 + "\", doesn't match with any of the Object's ID in this constructor.\n"); Console.PrintSet(); continue;}} if(!Init01[0].is_open()){Console.PrintWrite(">< >> ERROR - Requesting an AI-Script, but either \"" + Temp02 + "\" cannot be opened or it does not exist.\n"); Console.PrintSet(); continue;} Console.PrintWrite("[] >> AI-Script detected, including \"" + Temp02 + "\" into the package.\n"); std::stringstream Temp05; Temp05 << Init01[0].rdbuf(); Init01[0].close(); Temp02 = Temp05.str(); File0002 << Config.ECD_ResultEncryption[1] << S_EncryptionUINT32(Vrab02) << S_EncryptionUINT32(Temp02.size()) << S_EncryptionSTRING(Temp02); continue;}
          if(Temp02 == "<config_end>") goto Labl03;
         }
         Console.PrintWrite(")( WARNING - Unexpected end of \"<config>\".\n"); Console.PrintSet();
         Labl03: break;
        }
       } if(File0001){File0001.seekg(0);} else {L_Open(Temp01.path().string());} Strn0001.clear(); uint32 Vrab47 = 0;

       while(File0001)
       {
        File0001 >> Temp02; if(!File0001) break; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
        if(Temp02 == "<data>")
        {
         while(File0001)
         {
          File0001 >> Temp02; if(!File0001) break; if(Temp02[0] == '#'){std::getline(File0001, Temp02); continue;}
          if(Temp02 == "back:"){File0001 >> Temp02; Init01[0].open(Temp02, std::ios::binary | std::ios::in); const string Temp04 = L_Lowercase(string(Temp02, Temp02.size() - 4, 4)); if(Init01[0].is_open()){if(Temp04 == ".dat" || Temp04 == ".txt"){Vrab02 = Strn0001.size(); L_Addressing(Temp02); if(Vrab02 == Strn0001.size()){Init01[0].close(); continue;} Console.PrintWrite("[] >> Processing \"" + Temp02 + "\" into the package.\n"); Console.PrintSet(); if(M_EncryptionFile(6, Temp02)){Console.PrintWrite(">< >> ERROR - Failed in processing \"" + Temp02 + "\" into the package.\n"); Console.PrintSet();} else {File0002 << S_EncryptionUINT32(Vect04[Vrab47]); Vrab47 += 1;}} else {Console.PrintWrite(">< >> ERROR - \"" + Temp02 + "\" is not a Background for LF2.\n"); Console.PrintSet();} Init01[0].close();} else {Console.PrintWrite(">< >> ERROR - Either \"" + Temp02 + "\" cannot be opened or it does not exist.\n"); Console.PrintSet();} continue;}
          if(Temp02 == "file:"){File0001 >> Temp02; Init01[0].open(Temp02, std::ios::binary | std::ios::in); const string Temp04 = L_Lowercase(string(Temp02, Temp02.size() - 4, 4)); if(Init01[0].is_open()){if(Temp04 == ".dat" || Temp04 == ".txt"){Vrab02 = Strn0001.size(); L_Addressing(Temp02); if(Vrab02 == Strn0001.size()){Console.PrintWrite(")( WARNING - Why would you load \"" + Temp02 + "\" more than once? Well, i'll just going to warn this and keep the file to be packed more than once.\n"); Console.PrintSet();} Console.PrintWrite("[] >> Processing \"" + Temp02 + "\" into the package.\n"); Console.PrintSet(); if(M_EncryptionFile(2, Temp02)){Console.PrintWrite(">< >> ERROR - Failed in processing \"" + Temp02 + "\" into the package.\n"); Console.PrintSet();}} else {Console.PrintWrite(">< >> ERROR - \"" + Temp02 + "\" is not an Object for LF2.\n"); Console.PrintSet();} Init01[0].close();} else {Console.PrintWrite(">< >> ERROR - Either \"" + Temp02 + "\" cannot be opened or it does not exist.\n"); Console.PrintSet();} continue;}
          if(Temp02 == "data:"){File0001 >> Temp02; Init01[0].open(Temp02, std::ios::binary | std::ios::in); if(Init01[0].is_open()){Vrab02 = Strn0001.size(); L_Addressing(Temp02); if(Vrab02 == Strn0001.size()){Init01[0].close(); continue;} std::stringstream Temp05; Temp05 << Init01[0].rdbuf(); if(L_Lowercase(string(Temp02, Temp02.size() - 4, 4)) == ".bmp"){Console.PrintWrite("[] >> Packing \"" + Temp02 + "\" into the package.\n"); Console.PrintSet(); if(M_EncryptionFile(1, Temp02)) M_EncryptionFile(0, S_EncryptionUINT32(L_Addressing(Temp02)) + Temp05.str());} else {Console.PrintWrite("[] >> Including \"" + Temp02 + "\" into the package.\n"); Console.PrintSet(); M_EncryptionFile(0, Temp05.str());} Init01[0].close();} else {Console.PrintWrite(">< >> ERROR - Either \"" + Temp02 + "\" cannot be opened or it does not exist.\n"); Console.PrintSet();} continue;}
          if(Temp02 == "<data_end>") goto Labl04;
         }
         Console.PrintWrite(")( WARNING - Unexpected end of \"<data>\".\n"); Console.PrintSet();
         Labl04: break;
        }
       }
       {
        Vrab02 = 0; const uint32 Vrab09 = Strn0001.size(); uint32 Vrab04 = 0;
        while(Vrab02 != Vrab09){const uint32 Vrab05 = Strn0001[Vrab02].size(); File0002 << S_EncryptionUINT32(Vrab05) << S_EncryptionSTRING(Strn0001[Vrab02]); Vrab04 += Vrab05 + 5; Vrab02 += 1;}
        File0002 << S_EncryptionUINT32(Vrab04);
       }
       {
        Vrab02 = 0; const uint32 Vrab09 = Vect0001.size(); uint32 Vrab04 = 0;
        while(Vrab02 != Vrab09){File0002 << S_EncryptionUINT32(Vect0001[Vrab02]) << S_EncryptionUINT32(Vect01[Vrab02]) << S_EncryptionUINT32(Vect02[Vrab02]) << S_EncryptionUINT4(Vect03[Vrab02]); Vrab04 += 16; Vrab02 += 1;}
        File0002 << S_EncryptionUINT32(Vrab04);
       } Vect0001.clear(); Strn0001.clear();

       File0002 << "\n# ===                         " INJECTOR_VERSION "                         === #";
       Console.PrintWrite("[] Construction complete.\n"); Console.PrintSet(); Vrab08 = false;
      } else {Console.PrintWrite(">< ERROR - \"" + Temp01.path().string() + "\" inaccessible.\n"); Console.PrintSet(); continue;}
     }
    }
    if(Vrab01 == 0){Console.PrintWrite(">< ERROR - Found no constructor, the constructor suppossed to be named as \"build.txt\".\n"); Console.PrintSet();} else {if(Vrab08){Console.PrintWrite("() INFO - Construction failed.\n"); Console.PrintSet();}}
   } else {Console.PrintWrite("() INFO - \"" + Config.ECD_BuildDirectory + "\" directory does not exist.\n"); Console.PrintSet();}
   strcpy(&Config.ECD_ResultEncryption[0], &Varb01[0]); L_Cleaning();
  }
  int0   C_ECD_Installation()                                         
  {
   if(!Config.MAIN_ECD && (!Config.MAIN_MOD || Config.MOD_ModulingLevel == 0)) return;
   if(Config.MAIN_ECD){Console.PrintOut(); Console.PrintWrite("[] Preparing the installation. With the encryption key : [ " + string(Config.ECD_ResultEncryption, 94) + " ].\n"); Console.PrintOut();}
   std::vector < int1 > Vect01; std::vector < uint32 > Vect69; std::vector < string > Strn01; std::vector < string > Strn02;
   {
    string Temp01;
   Console.PrintWrite("[] Accessing \"" + Config.ECD_InstallDataDirectory + "\".\n"); Console.PrintOut();
   Labl01:
   if(L_Open(Config.ECD_InstallDataDirectory))
   {
    int1 Vrab03 = true; int1 Vrab04 = true;
    while(File0001)
    {
     File0001 >> Temp01; if(!File0001) break; if(Temp01.at(0) == '#'){std::getline(File0001, Temp01); continue;}
     if(Temp01 == "<object>")
     {
      while(File0001)
      {
       File0001 >> Temp01; if(!File0001) break; if(Temp01.at(0) == '#'){std::getline(File0001, Temp01); continue;}
       if(Temp01 == "id:")
       {
        File0001 >> Temp01; const int32 Vrab01 = L_Numbering(Temp01); if(Vrab01 < 0 || Vrab01 > 999){Console.PrintWrite(")( WARNING - \"id: " + Temp01 + "\" detected, this ID is out of supported range in LF2.\n"); Console.PrintOut();}
        const uint32 Vrab02 = L_Positive(Vrab01); if(Vrab02 + 1 > Vect01.size()) Vect01.resize(Vrab02 + 1);
        Vect01[Vrab02] = true;
        continue;
       }
       if(Temp01 == "file:"){File0001 >> Temp01; continue;}
       if(Temp01 == "type:"){File0001 >> Temp01; continue;}
       if(Temp01 == "<object_end>"){Vrab03 = false; break;}
       Console.PrintWrite(")( WARNING - Unknown syntax in \"<object>\", \"" + Temp01 + "\", detected.\n"); Console.PrintOut(); 
      }
      if(Vrab03){Console.PrintWrite(">< ERROR - Unexpected end of \"<object>\", cancel the installation.\n"); Console.PrintOut(); if(Config.MOD_ModulingLevel > 1) Config.MOD_ModulingLevel = 1; return;}
      continue;
     }
     if(Temp01 == "<background>")
     {
      while(File0001)
      {
       File0001 >> Temp01; if(!File0001) break; if(Temp01.at(0) == '#'){std::getline(File0001, Temp01); continue;}
       if(Temp01 == "id:"){File0001 >> Temp01; continue;}
       if(Temp01 == "file:"){File0001 >> Temp01; Strn02.push_back(Temp01); continue;}
       if(Temp01 == "<background_end>"){Vrab04 = false; break;}
       Console.PrintWrite(")( WARNING - Unknown syntax in \"<background>\", \"" + Temp01 + "\", detected.\n"); Console.PrintOut(); 
      }
      if(Vrab04){Console.PrintWrite(">< ERROR - Unexpected end of \"<background>\", cancel the installation.\n"); Console.PrintOut(); if(Config.MOD_ModulingLevel > 1) Config.MOD_ModulingLevel = 1; return;}
      continue;
     }
    }
    if(Vrab03){Console.PrintWrite(">< ERROR - Cannot find \"<object>\" in \"" + Config.ECD_InstallDataDirectory + "\", cancel the installation.\n"); Console.PrintOut(); if(Config.MOD_ModulingLevel > 1) Config.MOD_ModulingLevel = 1; return;}
    if(Vrab04){Console.PrintWrite(")( WARNING - Cannot find \"<background>\" in \"" + Config.ECD_InstallDataDirectory + "\".\n"); Console.PrintOut();}
    if(Strn02.size() < 12){Console.PrintWrite(")( WARNING - The default background in \"" + Config.ECD_InstallDataDirectory + "\" is less than 12 background, error may occur if you're not providing background(s).\n"); Console.PrintOut();}
    if(File0001){File0001.seekg(0);} else {L_Open(Config.ECD_InstallDataDirectory);}
    L_Create(L_Execute(Config.ECD_InstallODataDirectory)); File0002 << File0001.rdbuf(); File0002.close(); File0001.close();
   } else {if(L_Exist(Config.ECD_InstallDataDirectory)){Console.PrintWrite(">< ERROR - \"" + Config.ECD_InstallDataDirectory + "\" inaccessible, cancel the installation.\n"); Console.PrintOut(); if(Config.MOD_ModulingLevel > 1) Config.MOD_ModulingLevel = 1; return;} if(L_Create(L_Execute(Config.ECD_InstallDataDirectory))){Console.PrintWrite(")( WARNING - \"" + Config.ECD_InstallDataDirectory + "\" cannot be found.\n"); Console.PrintOut(); Console.PrintWrite("() INFO - Modified DDraw will providing the original \"data.txt\" to \"" + Config.ECD_InstallDataDirectory + "\".\n"); Console.PrintOut(); File0002 << "<object>\nid:  0  type: 0  file: data\\template.dat\nid:  52  type: 0  file: data\\julian.dat\nid:  51  type: 0  file: data\\firzen.dat\nid:  50  type: 0  file: data\\louisEX.dat\nid:  38  type: 0  file: data\\bat.dat\nid:  39  type: 0  file: data\\justin.dat\nid:  37  type: 0  file: data\\knight.dat\nid:  36  type: 0  file: data\\jan.dat\nid:  35  type: 0  file: data\\monk.dat\nid:  34  type: 0  file: data\\sorcerer.dat\nid:  33  type: 0  file: data\\jack.dat\nid:  32  type: 0  file: data\\mark.dat\nid:  31  type: 0  file: data\\hunter.dat\nid:  30  type: 0  file: data\\bandit.dat\nid:  1  type: 0  file: data\\deep.dat\nid:  2  type: 0  file: data\\john.dat\nid:  4  type: 0  file: data\\henry.dat\nid:  5  type: 0  file: data\\rudolf.dat\nid:  6  type: 0  file: data\\louis.dat\nid:  7  type: 0  file: data\\firen.dat\nid:  8  type: 0  file: data\\freeze.dat\nid:  9  type: 0  file: data\\dennis.dat\nid: 10  type: 0  file: data\\woody.dat\nid: 11  type: 0  file: data\\davis.dat\n\nid: 100  type: 1  file: data\\weapon0.dat   #stick\nid: 101  type: 1  file: data\\weapon2.dat   #hoe\nid: 120  type: 1  file: data\\weapon4.dat   #knife\nid: 121  type: 4  file: data\\weapon5.dat   #baseball\nid: 122  type: 6  file: data\\weapon6.dat   #milk\nid: 150  type: 2  file: data\\weapon1.dat   #stone\nid: 151  type: 2  file: data\\weapon3.dat   #wooden_box\nid: 123  type: 6  file: data\\weapon8.dat   #beer\nid: 124  type: 1  file: data\\weapon9.dat   #<\nid: 217  type: 2  file: data\\weapon10.dat  #louis_armour\nid: 218  type: 2  file: data\\weapon11.dat  #louis_armour\nid: 300  type: 5  file: data\\criminal.dat  #criminal\n\nid: 200  type: 3  file: data\\john_ball.dat\nid: 201  type: 1  file: data\\henry_arrow1.dat\nid: 202  type: 1  file: data\\rudolf_weapon.dat\nid: 203  type: 3  file: data\\deep_ball.dat\nid: 204  type: 3  file: data\\henry_wind.dat\nid: 205  type: 3  file: data\\dennis_ball.dat\nid: 206  type: 3  file: data\\woody_ball.dat\nid: 207  type: 3  file: data\\davis_ball.dat\nid: 208  type: 3  file: data\\henry_arrow2.dat\nid: 209  type: 3  file: data\\freeze_ball.dat\nid: 210  type: 3  file: data\\firen_ball.dat\nid: 211  type: 3  file: data\\firen_flame.dat\nid: 212  type: 3  file: data\\freeze_column.dat\nid: 213  type: 1  file: data\\weapon7.dat   #ice_sword\nid: 214  type: 3  file: data\\john_biscuit.dat\nid: 215  type: 3  file: data\\dennis_chase.dat\nid: 216  type: 3  file: data\\jack_ball.dat\nid: 219  type: 3  file: data\\jan_chaseh.dat\nid: 220  type: 3  file: data\\jan_chase.dat\nid: 221  type: 3  file: data\\firzen_chasef.dat\nid: 222  type: 3  file: data\\firzen_chasei.dat\nid: 223  type: 3  file: data\\firzen_ball.dat\nid: 224  type: 3  file: data\\bat_ball.dat\nid: 225  type: 3  file: data\\bat_chase.dat\nid: 226  type: 3  file: data\\justin_ball.dat\nid: 228  type: 3  file: data\\julian_ball.dat\nid: 229  type: 3  file: data\\julian_ball2.dat\n\nid: 998  type: 5  file: data\\etc.dat\nid: 999  type: 5  file: data\\broken_weapon.dat\n<object_end>\n\n<file_editing>\ndata\\nothing.txt\n<file_editing_end>\n\n<background>\nid: 4    file: bg\\sys\\hkc\\bg.dat\nid: 2    file: bg\\sys\\lf\\bg.dat\nid: 3    file: bg\\sys\\sp\\bg.dat\nid: 5    file: bg\\sys\\gw\\bg.dat\nid: 6    file: bg\\sys\\qi\\bg.dat\nid: 7    file: bg\\sys\\ft\\bg.dat\nid: 8    file: bg\\sys\\bc\\bg.dat\nid: 1    file: bg\\sys\\cuhk\\bg.dat\nid: 0    file: bg\\sys\\thv\\bg.dat\nid: 10    file: bg\\template\\1\\bg.dat\nid: 11    file: bg\\template\\2\\bg.dat\nid: 12    file: bg\\template\\3\\bg.dat\n<background_end>"; File0002.close(); Console.PrintWrite("[] Re-accessing \"" + Config.ECD_InstallDataDirectory + "\".\n"); Console.PrintOut(); goto Labl01;} else {Console.PrintWrite(">< ERROR - Either \"" + Config.ECD_InstallDataDirectory + "\" cannot be opened or it does not exist. Also cannot reproduce it out.\n"); Console.PrintOut(); return;}}
  
   if(Config.MAIN_MOD)
   if(Config.MOD_ModulingLevel > 0)
   {
    uint32 Vrab01 = 0; std::vector < uint32 > Vect02; Vect02.resize(2); uint32 Vrab03 = Config.ECD_InstallDataIDs[1];
    for(uint32 Vrab02 = Config.ECD_InstallDataIDs[0]; Vrab02 <= Vrab03; ++Vrab02)
    {
     if(Vect01.size() < Vrab02 + 1) Vect01.resize(Vrab02 + 1);
     if(!Vect01[Vrab02]){Vect01[Vrab02] = true; Vect02[Vrab01] = Vrab02; Vrab01 += 1; goto Labl03;}
    } Vrab03 = Config.ECD_InstallDataIDs[9];
    for(uint32 Vrab02 = Config.ECD_InstallDataIDs[8]; Vrab02 <= Vrab03; ++Vrab02)
    {
     if(Vect01.size() < Vrab02 + 1) Vect01.resize(Vrab02 + 1);
     if(!Vect01[Vrab02]){Vect01[Vrab02] = true; Vect02[Vrab01] = Vrab02; Vrab01 += 1; goto Labl03;}
    } Vrab03 = Config.ECD_InstallDataIDs[11];
    for(uint32 Vrab02 = Config.ECD_InstallDataIDs[10]; Vrab02 <= Vrab03; ++Vrab02)
    {
     if(Vect01.size() < Vrab02 + 1) Vect01.resize(Vrab02 + 1);
     if(!Vect01[Vrab02]){Vect01[Vrab02] = true; Vect02[Vrab01] = Vrab02; Vrab01 += 1; goto Labl03;}
    }
    Labl03: if(Vrab01 >= 2) goto Labl04; Vrab03 = Config.ECD_InstallDataIDs[13];
    for(uint32 Vrab02 = Config.ECD_InstallDataIDs[12]; Vrab02 <= Vrab03; ++Vrab02)
    {
     if(Vect01.size() < Vrab02 + 1) Vect01.resize(Vrab02 + 1);
     if(!Vect01[Vrab02]){Vect01[Vrab02] = true; Vect02[Vrab01] = Vrab02; Vrab01 += 1; goto Labl03;}
    }
    for(uint32 Vrab02 = 0; Vrab02 < 4294967295; ++Vrab02)
    {
     if(Vect01.size() < Vrab02 + 1) Vect01.resize(Vrab02 + 1);
     if(!Vect01[Vrab02]){Vect01[Vrab02] = true; Vect02[Vrab01] = Vrab02; Vrab01 += 1; goto Labl03;}
    }
    Labl04:
    Database.InjectorID = Vect02[0]; Database.InjectorID2 = Vect02[1];
   }
   }

   if(Config.MAIN_ECD)
   {
    L_Execute(Config.ECD_InstallDirectory); Console.PrintWrite("[] Seeking for package(s) in \"" + Config.ECD_InstallDirectory + "\".\n"); Console.PrintOut(); uint32 Vrab01 = 0; const uint32 Vrab02 = L_Numbering(SUPPORTED_ECD_VERSION);
    for(auto const &Temp01 : std::filesystem::directory_iterator(Config.ECD_InstallDirectory))
    {
     string Temp02 = Temp01.path().string(); 
     {const string Temp03 = L_Lowercase(string(Temp02, Temp02.size() - 4, 4));
      if(Temp03 == ".ecd") goto Labl05;
      if(Temp03 == ".egd") goto Labl05;
      if(Temp03 == ".ebd") goto Labl05;
      if(Config.MAIN_MOD)
      {
       if(Temp03 == ".pcd") goto Labl05;
       if(Temp03 == ".pgd") goto Labl05;
       if(Temp03 == ".pbd") goto Labl05;
      }
     }
     continue;
     Labl05:
     Vrab01 += 1; Console.PrintWrite("[] \"" + Temp02 + "\" found.\n"); Console.PrintOut();
     if(L_Open(Temp02))
     {
      File0001.seekg(0, File0001.end); std::streampos Post01 = File0001.tellg(); Post01 -= 44; if(Post01 < 57){Console.PrintWrite(">< ERROR - Either \"" + Temp02 + "\" is corrupt or it is not the package made using Modified DDraw.\n"); Console.PrintOut(); continue;} File0001.seekg(Post01);
      string Temp03 = Temp02;
      File0001 >> Temp02;
      const uint32 Vrab03 = L_Numbering(Temp02); if(Vrab03 < Vrab02){Console.PrintWrite(">< ERROR - This package is not supported anymore, the version of the Modified DDraw in constructing this package should equal or higher than " + string(SUPPORTED_ECD_VERSION, 1, string(SUPPORTED_ECD_VERSION).size() - 2) + ".\n"); Console.PrintOut(); continue;}
      File0001.seekg(0, File0001.end); Post01 = File0001.tellg(); const std::streampos Post04 = Post01; File0001.seekg(Post01 -= 80); const std::streampos Post02 = Post01;
      Temp02.resize(5); File0001.read(&Temp02.at(0), 5);
      const uint64 Vrab04 = S_DecryptionUINT32(Temp02.c_str()); Post01 -= 5 + Vrab04; File0001.seekg(Post01); const std::streampos Post03 = Post01;
      File0001.read(&Temp02.at(0), 5);
      Post01 -= rint64(S_DecryptionUINT32(Temp02.c_str())); File0001.seekg(Post01); const std::streampos Post05 = Post01;
      if(Post01 <= 336 || Post01 >= Post04){Console.PrintWrite(">< ERROR - Either \"" + Temp03 + "\" is corrupt or it is not the package made using Modified DDraw. [" + std::to_string(Post01) + "]\n"); Console.PrintOut(); continue;}
      Console.PrintWrite("[] >> Seeking data(s) in the package.\n"); Console.PrintOut(); Strn0001.clear(); uint32 Vrab99 = 0;
      while(Post01 != Post03 && Post01 >= 336 && Post01 <= Post04)
      {
       Temp02.resize(5); File0001.read(&Temp02.at(0), 5);
       const uint32 Vrab05 = S_DecryptionUINT32(Temp02.c_str()); 
       Post01 += 5 + ruint64(Vrab05);
       if(Post01 <= 336 || Post01 >= Post04) break;

       Temp02.resize(Vrab05 + 1); File0001.read(&Temp02.at(0), Vrab05); Temp02.pop_back();
       Strn0001.push_back(S_DecryptionSTRING(Temp02));
       Console.PrintWrite("() >> INFO - \"" + Strn0001[Strn0001.size() - 1] + "\" found in the package.\n"); Console.PrintOut(); Vrab99 += 1;
      }
      if(Post01 <= 336 || Post01 >= Post04){Console.PrintWrite(">< ERROR - Either \"" + Temp03 + "\" is corrupt or it is not the package made using Modified DDraw. [" + std::to_string(Post01) + "]\n"); Console.PrintOut(); continue;}
      Console.PrintWrite("[] >> " + std::to_string(Vrab99) + " data(s) are located in the package.\n"); Console.PrintOut(); 
      Post01 += 5; File0001.seekg(Post01); Temp02.resize(5);
      Console.PrintWrite("[] >> Seeking object(s) in the package.\n"); Console.PrintOut(); Vect0001.clear(); std::vector < uint32 > Vect02; std::vector < uint32 > Vect03; std::vector < uint32 > Vect04; Vrab99 = 0;
      while(Post01 != Post02 && Post01 >= 336 && Post01 <= Post04)
      {
       Temp02.resize(5); File0001.read(&Temp02.at(0), 5); Vect0001.push_back(S_DecryptionUINT32(Temp02.c_str()));
       File0001.read(&Temp02.at(0), 5); Vect02.push_back(S_DecryptionUINT32(Temp02.c_str()));
       File0001.read(&Temp02.at(0), 5); Vect03.push_back(S_DecryptionUINT32(Temp02.c_str()));
       Temp02.resize(1); File0001.read(&Temp02.at(0), 1); Vect04.push_back(S_DecryptionUINT4(Temp02.c_str())); const uint32 Vrab05 = Vect0001.size() - 1;
       Console.PrintWrite("[] >> An Object with \"id: " + std::to_string(Vect0001[Vrab05]) + " type: " + std::to_string(Vect02[Vrab05]) + " set: " + std::to_string(Vect03[Vrab05]) + " range: " + std::to_string(Vect04[Vrab05]) + "\" found in the package.\n"); Console.PrintOut(); Vrab99 += 1;
       
       if(Vect0001[Vrab05] < 0 || Vect0001[Vrab05] > 999){Console.PrintWrite(")( >> WARNING - \"id: " + std::to_string(Vect0001[Vrab05]) + "\" is out of supported range of ID in LF2.\n"); Console.PrintOut();}
       if(Vect01.size() < ruint32(Vect0001[Vrab05]) + 1) Vect01.resize(Vect0001[Vrab05] + 1);
       if(Vect01[Vect0001[Vrab05]])
       {
        if(Vect03[Vrab05] == 2){Vect69[Vect0001[Vrab05]] += 1; Post01 += 16; continue;}
        if(Vect03[Vrab05] == 1){Vect03[Vrab05] = 3; Post01 += 16; continue;}
        uint32 Vrab06 = 7; string Temp69 = std::to_string(Vect0001[Vrab05]);
        if(Vect04[Vrab05] == 0)
        {
         const int32 Vrab07 = Vect0001[Vrab05];
         if(Vrab07 >= Config.ECD_InstallDataIDs[0] && Vrab07 <= Config.ECD_InstallDataIDs[1]){Vrab06 = 3; goto Labl69;}
         if(Vrab07 >= Config.ECD_InstallDataIDs[2] && Vrab07 <= Config.ECD_InstallDataIDs[3]){Vrab06 = 0; goto Labl69;}
         if(Vrab07 >= Config.ECD_InstallDataIDs[4] && Vrab07 <= Config.ECD_InstallDataIDs[5]){Vrab06 = 1; goto Labl69;}
         if(Vrab07 >= Config.ECD_InstallDataIDs[6] && Vrab07 <= Config.ECD_InstallDataIDs[7]){Vrab06 = 2; goto Labl69;}
         if(Vrab07 >= Config.ECD_InstallDataIDs[8] && Vrab07 <= Config.ECD_InstallDataIDs[9]){Vrab06 = 4; goto Labl69;}
         if(Vrab07 >= Config.ECD_InstallDataIDs[10] && Vrab07 <= Config.ECD_InstallDataIDs[11]){Vrab06 = 5; goto Labl69;}
         if(Vrab07 >= Config.ECD_InstallDataIDs[12] && Vrab07 <= Config.ECD_InstallDataIDs[13]){Vrab06 = 6; goto Labl69;}
        } else
        {
         Vrab06 = Vect04[Vrab05] - 1;
         switch(Vrab06)
         {
          case 0: Vrab06 = 3; break;
          case 1: Vrab06 = 0; break;
          case 2: Vrab06 = 1; break;
          case 3: Vrab06 = 2; break;
          default: break;
         }
        }
        Labl69:
        while(true)
        {
         int1 Vrab07 = false; uint32 Vrab08 = 0; uint32 Vrab09 = 0;
         switch(Vrab06)
         {
          case 0: Vrab08 = Config.ECD_InstallDataIDs[2]; Vrab09 = Config.ECD_InstallDataIDs[3]; Vrab06 = 6; break;
          case 1: Vrab08 = Config.ECD_InstallDataIDs[4]; Vrab09 = Config.ECD_InstallDataIDs[5]; Vrab06 += 1; break;
          case 2: Vrab08 = Config.ECD_InstallDataIDs[6]; Vrab09 = Config.ECD_InstallDataIDs[7]; Vrab06 += 1; break;
          case 3: Vrab08 = Config.ECD_InstallDataIDs[0]; Vrab09 = Config.ECD_InstallDataIDs[1]; Vrab06 = 5; break;
          case 4: Vrab08 = Config.ECD_InstallDataIDs[8]; Vrab09 = Config.ECD_InstallDataIDs[9]; Vrab06 += 1; break;
          case 5: Vrab08 = Config.ECD_InstallDataIDs[10]; Vrab09 = Config.ECD_InstallDataIDs[11]; Vrab06 += 1; break;
          case 6: Vrab08 = Config.ECD_InstallDataIDs[12]; Vrab09 = Config.ECD_InstallDataIDs[13]; Vrab06 += 1; break;
          default: Vrab08 = 0; Vrab09 = ruint32(-2); Vrab07 = true; break;
         }
         if(Vect01.size() < Vrab09 + 1) Vect01.resize(Vrab09 + 1);
         while(Vrab08 <= Vrab09)
         {
          if(!Vect01[Vrab08]){Vect01[Vrab08] = true; Vect0001[Vrab05] = Vrab08; Vrab07 = true; break;}
          Vrab08 += 1;
         }
         if(Vrab07) break;
        }
        Console.PrintWrite("() >> INFO - \"id: " + Temp69 + "\" was used by other object, this object will be installed with \"id: " + std::to_string(Vect0001[Vrab05]) + "\" instead.\n"); Console.PrintOut();
       } else {Vect01[Vect0001[Vrab05]] = true;}
       Post01 += 16;
      }
      if(Post01 <= 336 || Post01 >= Post04){Console.PrintWrite(">< ERROR - Either \"" + Temp03 + "\" is corrupt or it is not the package made using Modified DDraw. [" + std::to_string(Post01) + "]\n"); Console.PrintOut(); continue;}
      Console.PrintWrite("[] >> " + std::to_string(Vrab99) + " object(s) are located in the package.\n"); Console.PrintOut();
      Console.PrintWrite("[] >> Parsing file(s) in the package.\n"); Console.PrintOut();
      File0001.seekg(336); int1 Vrab06 = true; uint32 Vrab69 = 0; int1 Vrab88 = false;
      while(Post05 != (Post01 = File0001.tellg()))
      {
       Temp02.resize(1); File0001.read(&Temp02.at(0), 1);
       if(Temp02.at(0) == Config.ECD_ResultEncryption[0] || Temp02.at(0) == Config.ECD_ResultEncryption[1])
       {
        string Temp05; if(Post01 > Post05 - static_cast < std::streampos > (12)) break;
        if(Temp02.at(0) == Config.ECD_ResultEncryption[0])
        {
         Temp05 = "_";
         File0001.read(&Temp02.at(0), 1);
         if(Temp02.at(0) == Config.ECD_ResultEncryption[1])
         {
          Temp02.resize(5); File0001.read(&Temp02.at(0), 5);
          Temp05 += std::to_string(S_DecryptionUINT32(Temp02.c_str())) + ".as";
         } else
         {
          Temp02.resize(5); File0001.read(&Temp02.at(0), 5);
          Temp05 += std::to_string(Vect0001[S_DecryptionUINT32(Temp02.c_str())]) + ".as";
         }
        } else
        {
        
        Temp02.resize(5); File0001.read(&Temp02.at(0), 5);
        Temp05 += std::to_string(Vect0001[S_DecryptionUINT32(Temp02.c_str())]) + ".as";
        }
        Console.PrintWrite("[] >> Parsing \"" + Temp05 + "\" from the package to \"");
        Temp05.insert(0, Config.AI_OldDirectory + "\\");
        Console.PrintWrite(Temp05 + "\".\n"); Console.PrintOut();
        File0001.read(&Temp02.at(0), 5); const uint32 Vrab05 = S_DecryptionUINT32(Temp02.c_str());
        if(Post01 > Post05 - static_cast < std::streampos > (7 + ruint64(Vrab05))) break;
        Temp02.resize(Vrab05); File0001.read(&Temp02.at(0), Vrab05);
        if(!Config.ECD_InstallOverwrite && L_Exist(Temp05)){Console.PrintWrite("() >> INFO - \"" + Temp05 + "\" skipped due to a file with same name already exist.\n"); Console.PrintOut(); continue;}
        L_Create(L_Execute(Temp05)); File0002 << S_DecryptionSTRING(Temp02); File0002.close(); L_Summary(Temp05 + "\n"); continue;
       }
       if(Temp02.at(0) == Config.ECD_ResultEncryption[2] || Temp02.at(0) == Config.ECD_ResultEncryption[7])
       {
        Temp02.resize(5); File0001.read(&Temp02.at(0), 5);
        const uint32 Vrab05 = S_DecryptionUINT32(Temp02.c_str());
        File0001.read(&Temp02.at(0), 5);
        const uint32 Vrab07 = S_DecryptionUINT32(Temp02.c_str());
        if(Post01 > Post05 - static_cast < std::streampos > (11 + ruint64(Vrab07))) break;
        if(Temp02.at(0) == Config.ECD_ResultEncryption[7]) if(Config.ECD_InstallNoMirrors)
        {
         File0001.seekg(File0001.tellg() + static_cast < std::streampos > (Vrab07)); continue;
        }
        Temp02.resize(Vrab07); File0001.read(&Temp02.at(0), Vrab07);
        if(!Config.ECD_InstallOverwrite && L_Exist(Strn0001[Vrab05])){Console.PrintWrite("() >> INFO - \"" + Strn0001[Vrab05] + "\" skipped due to a file with same name already exist.\n"); Console.PrintOut(); continue;}
        Console.PrintWrite("[] >> Parsing \"" + Strn0001[Vrab05] + "\" from the package");
        if(!Config.ECD_InstallSeparated)
        {
         Strn0001[Vrab05] = Config.ECD_ResultDirectory + L_Reform(Strn0001[Vrab05]); while(L_Exist(Strn0001[Vrab05])) L_Rename(Strn0001[Vrab05]); Console.PrintWrite(" as \"" + Strn0001[Vrab05] + "\"");
        }
        Console.PrintWrite(".\n"); Console.PrintOut();
        L_Create(L_Execute(Strn0001[Vrab05])); File0002 << S_DecryptionSTRING(Temp02); File0002.close(); L_Summary(Strn0001[Vrab05] + "\n"); continue;
       }
       if(Temp02.at(0) == Config.ECD_ResultEncryption[3] || Temp02.at(0) == Config.ECD_ResultEncryption[5] || Temp02.at(0) == Config.ECD_ResultEncryption[6])
       {
        const uint8 Vrab18 = Temp02.at(0);
        if(Post01 > Post05 - static_cast < std::streampos > (27)) break;
        Temp02.resize(5); File0001.read(&Temp02.at(0), 5); const uint32 Vrab05 = S_DecryptionUINT32(Temp02.c_str());
        File0001.read(&Temp02.at(0), 5); const uint32 Vrab07 = S_DecryptionUINT32(Temp02.c_str());
        File0001.read(&Temp02.at(0), 5); const uint32 Vrab08 = S_DecryptionUINT32(Temp02.c_str());
        File0001.read(&Temp02.at(0), 1); const uint32 Vrab09 = S_DecryptionUINT4(&Temp02.at(0)); Temp02.resize(4);
        File0001.read(&Temp02.at(0), 4); const uint32 Vrab10 = S_DecryptionUINT24(Temp02.c_str()); if(Vrab10 == 0) break;
        if(Post01 > Post05 - static_cast < std::streampos > (27 + (ruint64(Vrab10) * 4))) break;

        std::vector < uint8 > Vect05; std::vector < uint8 > Vect06; std::vector < uint8 > Vect07;

        uint32 Vrab11 = 0; while(Vrab11 != Vrab10)
        {
         File0001.read(&Temp02.at(0), 4); const uint32 Vrab12 = S_DecryptionUINT24(Temp02.c_str()); Vect05.push_back(Vrab12 & 0xFF); Vect06.push_back((Vrab12 >> 8) & 0xFF); Vect07.push_back((Vrab12 >> 16) & 0xFF);
         Vrab11 += 1;
        }

        BMP Bitm01(Vrab07, Vrab08, false);
        Temp02.resize(5); File0001.read(&Temp02.at(0), 5); const uint32 Vrab13 = S_DecryptionUINT32(Temp02.c_str());
        Post01 = File0001.tellg();
        if(Post01 > Post05 - static_cast < std::streampos > (ruint64(Vrab13))) break;
        Temp02.resize(Vrab13); File0001.read(&Temp02.at(0), Vrab13);

        if(Config.ECD_InstallNoMirrors) if(Vrab18 == Config.ECD_ResultEncryption[6]) continue;
        if(!Config.ECD_InstallOverwrite && L_Exist(Strn0001[Vrab05])){Console.PrintWrite("() >> INFO - \"" + Strn0001[Vrab05] + "\" skipped due to a file with same name already exist.\n"); Console.PrintOut(); continue;}
        Console.PrintWrite("[] >> Parsing \"" + Strn0001[Vrab05] + "\" from the package");
        if(!Config.ECD_InstallSeparated)
        {
         Strn0001[Vrab05] = Config.ECD_ResultDirectory + L_Reform(Strn0001[Vrab05]); while(L_Exist(Strn0001[Vrab05])) L_Rename(Strn0001[Vrab05]); Console.PrintWrite(" as \"" + Strn0001[Vrab05] + "\"");
        }
        if(Vrab18 == Config.ECD_ResultEncryption[5]) Console.PrintWrite(" along with it's mirror");
        Console.PrintWrite(".\n"); Console.PrintOut();
        
        Temp02 = S_DecryptionSTRING(Temp02); Vrab11 = 0; const uint32 Vrab12 = Bitm01.data.size(); uint32 Vrab14 = 0; uint32 Vrab15 = 0;
        while(Vrab14 != Vrab13)
        {
         if(Vrab11 + 3 > Vrab12) break;
         const uint8 Vrab16 = Temp02.at(Vrab14);
         if(Vrab16 == Config.ECD_ResultEncryption[93] || Vrab16 == Config.ECD_ResultEncryption[92] || Vrab16 == Config.ECD_ResultEncryption[91])
         {
          uint32 Vrab17 = S_DecryptionUINT4(&Temp02.at(Vrab14 + 1));
          if(Vrab16 == Config.ECD_ResultEncryption[92]) Vrab17 += 94;
          if(Vrab16 == Config.ECD_ResultEncryption[91]) Vrab17 += 188;
          Vrab17 += 1;
          while(Vrab17 != 0)
          {
           Bitm01.data[Vrab11] = Vect05[Vrab15];
           Bitm01.data[Vrab11 + 1] = Vect06[Vrab15];
           Bitm01.data[Vrab11 + 2] = Vect07[Vrab15];
           Vrab11 += 3; if(Vrab11 + 3 > Vrab12) break;
           Vrab17 -= 1;
          }
          Vrab14 += 2;
          continue;
         }
         switch(Vrab09)
         {
          case 0: Vrab15 = S_DecryptionUINT4(string(Temp02, Vrab14, 1).c_str()); Vrab14 += 1; break;
          case 1: Vrab15 = S_DecryptionUINT10(string(Temp02, Vrab14, 2).c_str()); Vrab14 += 2; break;
          case 2: Vrab15 = S_DecryptionUINT18(string(Temp02, Vrab14, 3).c_str()); Vrab14 += 3; break;
          default: Vrab15 = S_DecryptionUINT24(string(Temp02, Vrab14, 4).c_str()); Vrab14 += 4; break;
         }
         if(Vrab15 >= Vrab10) break;
         Bitm01.data[Vrab11] = Vect05[Vrab15];
         Bitm01.data[Vrab11 + 1] = Vect06[Vrab15];
         Bitm01.data[Vrab11 + 2] = Vect07[Vrab15];
         Vrab11 += 3;
        }
        if(Vrab14 != Vrab13) break;
        Bitm01.write(L_Execute(Strn0001[Vrab05]).c_str()); L_Summary(Strn0001[Vrab05] + "\n");
        if(Vrab18 == Config.ECD_ResultEncryption[5])
        {
         BMP Bitm02(Vrab07, Vrab08, false);
         uint32 Vrab20 = Vrab08;
         while(Vrab20 != 0)
         {
          Vrab20 -= 1; uint32 Vrab21 = Vrab20 * Vrab07; uint32 Vrab22 = ((Vrab21 + Vrab07) * 3) + 3; const uint32 Vrab23 = Vrab21 * 3; const uint32 Vrab24 = Vrab22; Vrab21 = Vrab23;
          while(Vrab22 != Vrab23)
          {
           Bitm02.data[Vrab22 - 1] = Bitm01.data[Vrab21 - 1];
           Bitm02.data[Vrab22 - 2] = Bitm01.data[Vrab21 - 2];
           Bitm02.data[Vrab22 - 3] = Bitm01.data[Vrab21 - 3];
           Vrab21 += 3; Vrab22 -= 3;
          }
         }
         string Temp69 = string(Strn0001[Vrab05], 0, Strn0001[Vrab05].size() - 4) + "_mirror.bmp";
         Bitm02.write(L_Execute(Temp69).c_str()); L_Summary(Temp69 + "\n");
        }
        continue;
       }
       if(Temp02.at(0) == Config.ECD_ResultEncryption[4])
       {
        if(Post01 > Post05 - static_cast < std::streampos > (11)) break;
        Temp02.resize(5); File0001.read(&Temp02.at(0), 5); const uint32 Vrab05 = S_DecryptionUINT32(Temp02.c_str());
        File0001.read(&Temp02.at(0), 5); const uint32 Vrab07 = S_DecryptionUINT32(Temp02.c_str());
        if(Post01 > Post05 - static_cast < std::streampos > (11 + ruint64(Vrab07))) break;
        Temp02.resize(Vrab07); File0001.read(&Temp02.at(0), Vrab07); Temp02 = S_DecryptionSTRING(Temp02);

        if(Vect03[Vrab69] == 3){Console.PrintWrite("() >> INFO - \"" + Strn0001[Vrab05] + "\" skipped due to it's \"set:\".\n"); Console.PrintOut(); Vrab69 += 1; continue;}

        if(!Config.ECD_InstallOverwrite && L_Exist(Strn0001[Vrab05])){Console.PrintWrite("() >> INFO - \"" + Strn0001[Vrab05] + "\" skipped due to a file with same name already exist.\n"); Console.PrintOut(); Strn01.push_back(std::to_string(Vect0001[Vrab69]) + " type: " + std::to_string(Vect02[Vrab69]) + " file: " + Strn0001[Vrab05]); Vrab69 += 1; continue;}
        Console.PrintWrite("[] >> Parsing \"" + Strn0001[Vrab05] + "\" from the package");
        if(!Config.ECD_InstallSeparated || string(Strn0001[Vrab05], Strn0001[Vrab05].size() - 4, 4) != ".txt")
        {
         Strn0001[Vrab05] = string(Strn0001[Vrab05], 0, Strn0001[Vrab05].size() - 4) + ".txt";
         if(!Config.ECD_InstallSeparated){Strn0001[Vrab05] = Config.ECD_ResultDirectory + L_Reform(Strn0001[Vrab05]); while(L_Exist(Strn0001[Vrab05])) L_Rename(Strn0001[Vrab05]);} Console.PrintWrite(" as \"" + Strn0001[Vrab05] + "\"");
        }
        Console.PrintWrite(".\n"); Console.PrintOut();

        L_Create(L_Execute(Strn0001[Vrab05])); L_Summary(Strn0001[Vrab05] + "\n");
        Strn01.push_back(std::to_string(Vect0001[Vrab69]) + " type: " + std::to_string(Vect02[Vrab69]) + " file: " + Strn0001[Vrab05]); Vrab69 += 1;
        std::vector < int32 > Vect05; uint32 Vrab08 = ruint32(-1); uint32 Vrab09 = 0;
        switch(Config.ECD_ResultCodeFormat)
        {
         case 0:
          while((Vrab08 += 1) != Vrab07)
          {
           if(Vrab08 != 0) File0002 << " "; const uint8 Vrab10 = Temp02.at(Vrab08);
           switch(Vrab09)
           {
            case 0:
             if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 1;  File0002 << "<bmp_begin>"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 2;  File0002 << "<weapon_strength_list>"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 11; File0002 << "<frame>"; continue;}
            break;
            case 1:
             if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 0;  File0002 << "<bmp_end>"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 23; File0002 << "name:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 24; File0002 << "head:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 24; File0002 << "small:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 24; File0002 << "file(0-0):"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 12; File0002 << "w:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 12; File0002 << "h:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 12; File0002 << "col:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 12; File0002 << "row:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[9]) {Vrab09 = 12; File0002 << "walking_frame_rate"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[10]){Vrab09 = 12; File0002 << "running_frame_rate"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[11]){Vrab09 = 26; File0002 << "walking_speed"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[12]){Vrab09 = 26; File0002 << "walking_speedz"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[13]){Vrab09 = 26; File0002 << "running_speed"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[14]){Vrab09 = 26; File0002 << "running_speedz"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[15]){Vrab09 = 26; File0002 << "heavy_walking_speed"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[16]){Vrab09 = 26; File0002 << "heavy_walking_speedz"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[17]){Vrab09 = 26; File0002 << "heavy_running_speed"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[18]){Vrab09 = 26; File0002 << "heavy_running_speedz"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[19]){Vrab09 = 26; File0002 << "jump_height"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[20]){Vrab09 = 26; File0002 << "jump_distance"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[21]){Vrab09 = 26; File0002 << "jump_distancez"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[22]){Vrab09 = 26; File0002 << "dash_height"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[23]){Vrab09 = 26; File0002 << "dash_distance"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[24]){Vrab09 = 26; File0002 << "dash_distancez"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[25]){Vrab09 = 26; File0002 << "rowing_height"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[26]){Vrab09 = 26; File0002 << "rowing_distance"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[27]){Vrab09 = 12; File0002 << "weapon_hp:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[28]){Vrab09 = 12; File0002 << "weapon_drop_hurt:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[29]){Vrab09 = 24; File0002 << "weapon_hit_sound:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[30]){Vrab09 = 24; File0002 << "weapon_drop_sound:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[31]){Vrab09 = 24; File0002 << "weapon_broken_sound:"; continue;}
            break;
            case 2:
             if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 0;  File0002 << "<weapon_strength_list_end>"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 35; File0002 << "entry:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 13; File0002 << "zwidth:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 13; File0002 << "dvx:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 13; File0002 << "dvy:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 13; File0002 << "fall:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 13; File0002 << "arest:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 13; File0002 << "vrest:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 13; File0002 << "respond:"; ""; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[9]) {Vrab09 = 13; File0002 << "effect:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[10]){Vrab09 = 13; File0002 << "bdefend:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[11]){Vrab09 = 13; File0002 << "injury:"; continue;}
            break;
            case 3:
             if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 0;  File0002 << "<frame_end>"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 14; File0002 << "pic:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 27; File0002 << "state:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 14; File0002 << "wait:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 14; File0002 << "next:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 14; File0002 << "dvx:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 14; File0002 << "dvy:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 14; File0002 << "dvz:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 14; File0002 << "centerx:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[9]) {Vrab09 = 29; File0002 << "centery:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[10]){Vrab09 = 14; File0002 << "hit_a:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[11]){Vrab09 = 14; File0002 << "hit_d:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[12]){Vrab09 = 14; File0002 << "hit_j:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[13]){Vrab09 = 14; File0002 << "hit_Fa:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[14]){Vrab09 = 14; File0002 << "hit_Fj:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[15]){Vrab09 = 14; File0002 << "hit_Da:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[16]){Vrab09 = 14; File0002 << "hit_Dj:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[17]){Vrab09 = 14; File0002 << "hit_Ua:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[18]){Vrab09 = 14; File0002 << "hit_Uj:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[19]){Vrab09 = 14; File0002 << "hit_ja:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[20]){Vrab09 = 14; File0002 << "mp:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[21]){Vrab09 = 25; File0002 << "sound:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[22]){Vrab09 = 4;  File0002 << "bpoint:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[23]){Vrab09 = 5;  File0002 << "cpoint:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[24]){Vrab09 = 6;  File0002 << "wpoint:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[25]){Vrab09 = 7;  File0002 << "opoint:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[26]){Vrab09 = 8;  File0002 << "itr:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[27]){Vrab09 = 9;  File0002 << "bdy:"; continue;}
            break;
            case 4:
             if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 3;  File0002 << "bpoint_end:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 15; File0002 << "x:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 15; File0002 << "y:"; continue;}
            break;
            case 5:
             if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 3;  File0002 << "cpoint_end:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 16; File0002 << "kind:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 16; File0002 << "x:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 30; File0002 << "y:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 16; File0002 << "vaction:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 16; File0002 << "aaction:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 16; File0002 << "daction:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 16; File0002 << "jaction:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 16; File0002 << "taction:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[9]) {Vrab09 = 16; File0002 << "throwvx:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[10]){Vrab09 = 16; File0002 << "throwvy:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[11]){Vrab09 = 16; File0002 << "throwvz:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[12]){Vrab09 = 16; File0002 << "throwinjury:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[13]){Vrab09 = 16; File0002 << "dircontrol:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[14]){Vrab09 = 16; File0002 << "hurtable:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[15]){Vrab09 = 16; File0002 << "decrease:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[16]){Vrab09 = 16; File0002 << "cover:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[17]){Vrab09 = 16; File0002 << "injury:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[18]){Vrab09 = 16; File0002 << "fronthurtact:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[19]){Vrab09 = 16; File0002 << "backhurtact:"; continue;}
            break;
            case 6:
             if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 3;  File0002 << "wpoint_end:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 17; File0002 << "kind:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 17; File0002 << "x:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 31; File0002 << "y:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 17; File0002 << "dvx:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 17; File0002 << "dvy:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 17; File0002 << "dvz:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 17; File0002 << "weaponact:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 17; File0002 << "attacking:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[9]) {Vrab09 = 17; File0002 << "cover:"; continue;}
            break;
            case 7:
             if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 3;  File0002 << "opoint_end:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 18; File0002 << "kind:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 18; File0002 << "x:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 32; File0002 << "y:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 18; File0002 << "dvx:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 18; File0002 << "dvy:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 28; File0002 << "oid:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 18; File0002 << "action:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 18; File0002 << "facing:"; continue;}
            break;
            case 8: case 10:
             if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 3;  File0002 << "itr_end:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 19; File0002 << "kind:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 19; File0002 << "x:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 33; File0002 << "y:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 19; File0002 << "w:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 19; File0002 << "h:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 19; File0002 << "zwidth:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 19; File0002 << "dvx:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 19; File0002 << "dvy:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[9]) {Vrab09 = 19; File0002 << "fall:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[10]){Vrab09 = 19; File0002 << "arest:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[11]){Vrab09 = 19; File0002 << "vrest:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[12]){Vrab09 = 19; File0002 << /*"respond:";*/ ""; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[13]){Vrab09 = 19; File0002 << "effect:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[14]){Vrab09 = 19; File0002 << "bdefend:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[15]){Vrab09 = 19; File0002 << "injury:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[16]){Vrab09 = 21; File0002 << "catchingact:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[17]){Vrab09 = 21; File0002 << "caughtact:"; continue;}
             if(Vrab09 == 10) if(Vrab10 == Config.ECD_ResultEncryption[93]){Vrab09 = 8; File0002 << S_DecryptionINT32(string(Temp02, Vrab08 + 1, 5).c_str()); Vrab08 += 5; continue;}
            break;
            case 9:
             if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 3;  File0002 << "bdy_end:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 20; File0002 << "kind:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 20; File0002 << "x:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 34; File0002 << "y:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 20; File0002 << "w:"; continue;}
             if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 20; File0002 << "h:"; continue;}
            break;
            case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 35:
             File0002 << S_DecryptionINT32(string(Temp02, Vrab08, 5).c_str()); Vrab08 += 4;
             switch(Vrab09){case 11: Vrab09 = 22; continue; case 12: Vrab09 = 1; continue; case 13: Vrab09 = 2; continue; case 14: Vrab09 = 3; continue; case 15: Vrab09 = 4; continue; case 16: Vrab09 = 5; continue; case 17: Vrab09 = 6; continue; case 18: Vrab09 = 7; continue; case 19: Vrab09 = 8; continue; case 20: Vrab09 = 9; continue; case 21: Vrab09 = 10; continue; case 35: Vrab09 = 36; continue; default: break;}
            break;
            case 22: case 23: case 36:
             {
              const uint32 Vrab11 = S_DecryptionINT32(string(Temp02, Vrab08, 5).c_str()); Vrab08 += 5; File0002 << S_DecryptionSTRING(string(Temp02, Vrab08, Vrab11)); Vrab08 += Vrab11 - 1;
             }
             if(Vrab09 == 22){Vrab09 = 3;} else {if(Vrab09 == 23){Vrab09 = 1;} else {Vrab09 = 2;}}  continue;
            case 24: case 25:
             File0002 << Strn0001[S_DecryptionUINT32(string(Temp02, Vrab08, 5).c_str())]; Vrab08 += 4;
             switch(Vrab09){case 24: Vrab09 = 1; continue; case 25: Vrab09 = 3; continue; default: break;}
            break;
            case 26:
             {
              File0002 << S_DecryptionINT32(string(Temp02, Vrab08, 5).c_str()) << "."; Vrab08 += 5;
              const uint32 Vrab11 = S_DecryptionUINT32(string(Temp02, Vrab08, 5).c_str()); Vrab08 += 4;
              if(Vrab11 < 100000000){if(Vrab11 < 10000000){if(Vrab11 < 1000000){if(Vrab11 < 100000){if(Vrab11 < 10000){if(Vrab11 < 1000){if(Vrab11 < 100){if(Vrab11 < 10){File0002 << "00000000";} else {File0002 << "0000000";}} else {File0002 << "000000";}} else {File0002 << "00000";}} else {File0002 << "0000";}} else {File0002 << "000";}} else {File0002 << "00";}} else {File0002 << "0";}}
              File0002 << Vrab11;
             }
             Vrab09 = 1; continue;
            case 27: case 28:
             if(Vrab10 == Config.ECD_ResultEncryption[93])
             {if(Vrab09 == 27){const uint32 Vrab11 = Vect0001[S_DecryptionINT32(string(Temp02, Vrab08 + 1, 5).c_str())]; if(Vrab11 > 1000){File0002 << "0";} else {File0002 << Vect0001[S_DecryptionINT32(string(Temp02, Vrab08 + 1, 5).c_str())] + 8000;}} else {File0002 << Vect0001[S_DecryptionINT32(string(Temp02, Vrab08 + 1, 5).c_str())];} Vrab08 += 5;} else
             {File0002 << S_DecryptionINT32(string(Temp02, Vrab08, 5).c_str()); Vrab08 += 4;}
             if(Vrab09 == 27){Vrab09 = 3;} else {Vrab09 = 7;} continue;
            break;
            case 29: case 30: case 31: case 32: case 33: case 34:
             if(Vrab10 == Config.ECD_ResultEncryption[93])
             {
              const int32 Vrab11 = S_DecryptionINT32(string(Temp02, Vrab08 + 6, 5).c_str()); if(Vrab11 < 0){File0002 << -(Vect0001[S_DecryptionINT32(string(Temp02, Vrab08 + 1, 5).c_str())] * 1000000) + Vrab11;} else {File0002 << (Vect0001[S_DecryptionINT32(string(Temp02, Vrab08 + 1, 5).c_str())] * 1000000) + Vrab11;} Vrab08 += 10;
             } else {File0002 << S_DecryptionINT32(string(Temp02, Vrab08, 5).c_str()); Vrab08 += 4;}
             switch(Vrab09){case 29: Vrab09 = 3; continue; case 30: Vrab09 = 5; continue; case 31: Vrab09 = 6; continue; case 32: Vrab09 = 7; continue; case 33: Vrab09 = 8; continue; case 34: Vrab09 = 9; continue; default: break;}
            break;
            default: break;
           }
           break;
          }
         break;
         default:
          {
           std::vector < string > Strn03; std::vector < int32 > Vect06; std::vector < uint32 > Vect07; uint32 Vrab11 = 0; uint32 Vrab12 = 0; int1 Vrab98 = false; string Temp99;
           while((Vrab08 += 1) != Vrab07)
           {
            const uint8 Vrab10 = Temp02.at(Vrab08);
            switch(Vrab09)
            {
             case 0:
              if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 1; Strn03.resize(17); Vect06.resize(44); Vect07.resize(15); Vrab12 = ruint32(-1); for(uint32 Vrab13 = 0; Vrab13 < 15; ++Vrab13) Vect07[Vrab13] = ruint32(-1); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 2; Strn03.resize(7); Vect06.resize(7); Vrab12 = ruint32(-1); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 11; Strn03.resize(1); Vect06.resize(169); Vect07.resize(2); Vrab11 = 168; Vrab12 = ruint32(-1); Vect07[0] = (Vect07[1] = ruint32(-1)); continue;}
             break;
             case 1:
              if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 0;
               if(Vrab98){File0002 << "\n"; Vrab98 = false;}
              
              switch(Config.ECD_ResultCodeFormat)
              {
               case 2: case 3:
               {
                std::vector < string > Strn04; uint32 Vrab13 = 0;
                while(Vrab13 < 10){if(Vect07[Vrab13] == -1) break; Strn04.push_back(" file("); Vrab13 += 1;}
                uint32 Vrab14 = 0; uint32 Vrab15 = 0; if(Vrab13 != 0) Strn04[0] += "0-";
                while(Vrab14 != Vrab13)
                {
                 Vrab15 += (Vect06[(Vrab14 * 4) + 2] * Vect06[(Vrab14 * 4) + 3]);
                 if(Vrab14 + 1 != Vrab13) Strn04[Vrab14 + 1] += std::to_string(Vrab15) + "-";
                 Vrab15 -= 1; Strn04[Vrab14] += std::to_string(Vrab15) + "): "; Vrab15 += 1;
                 Vrab14 += 1;
                }
                if(Vrab13 != 0)
                {
                 Vrab15 = Strn04[Strn04.size() - 1].size();
                 Vrab14 = 0; uint32 Vrab17 = 0;
                 while(Vrab14 != Vrab13)
                 {
                  uint32 Vrab16 = Strn04[Vrab14].size();
                  while(Vrab16 != Vrab15){Strn04[Vrab14] += ' '; Vrab16 += 1;}
                  Strn04[Vrab14] += Strn0001[Vect07[Vrab14]] + " "; Vrab16 = Strn04[Vrab14].size(); if(Vrab17 < Vrab16) Vrab17 = Vrab16;
                  Vrab14 += 1;
                 }
                 Vrab14 = 0; Vrab15 = Vrab17; Vrab17 = 0;
                 while(Vrab14 != Vrab13)
                 {
                  uint32 Vrab16 = Strn04[Vrab14].size();
                  while(Vrab16 != Vrab15){Strn04[Vrab14] += ' '; Vrab16 += 1;}
                  switch(Config.ECD_ResultCodeFormat)
                  {
                   case 3: Strn04[Vrab14] += "       "; break;
                   default: break;
                  }
                  Strn04[Vrab14] += "w: " + std::to_string(Vect06[Vrab14 * 4]) + " "; Vrab16 = Strn04[Vrab14].size(); if(Vrab17 < Vrab16) Vrab17 = Vrab16;
                  Vrab14 += 1;
                 }
                 Vrab14 = 0; Vrab15 = Vrab17; Vrab17 = 0;
                 while(Vrab14 != Vrab13)
                 {
                  uint32 Vrab16 = Strn04[Vrab14].size();
                  while(Vrab16 != Vrab15){Strn04[Vrab14] += ' '; Vrab16 += 1;}
                  Strn04[Vrab14] += "h: " + std::to_string(Vect06[(Vrab14 * 4) + 1]) + " "; Vrab16 = Strn04[Vrab14].size(); if(Vrab17 < Vrab16) Vrab17 = Vrab16;
                  Vrab14 += 1;
                 }
                 Vrab14 = 0; Vrab15 = Vrab17; Vrab17 = 0;
                 while(Vrab14 != Vrab13)
                 {
                  uint32 Vrab16 = Strn04[Vrab14].size();
                  while(Vrab16 != Vrab15){Strn04[Vrab14] += ' '; Vrab16 += 1;}
                  Strn04[Vrab14] += "row: " + std::to_string(Vect06[(Vrab14 * 4) + 3]) + " "; Vrab16 = Strn04[Vrab14].size(); if(Vrab17 < Vrab16) Vrab17 = Vrab16;
                  Vrab14 += 1;
                 }
                 Vrab14 = 0; Vrab15 = Vrab17;
                 while(Vrab14 != Vrab13)
                 {
                  uint32 Vrab16 = Strn04[Vrab14].size();
                  while(Vrab16 != Vrab15){Strn04[Vrab14] += ' '; Vrab16 += 1;}
                  Strn04[Vrab14] += "col: " + std::to_string(Vect06[(Vrab14 * 4) + 2]) + "\n";
                  Vrab14 += 1;
                 }
                }

                File0002 << "<bmp_begin>";
                switch(Config.ECD_ResultCodeFormat)
                {
                 case 3: if(Strn03[0].size() != 0) File0002 << "\n name: " + Strn03[0]; break;
                 default: if(Strn03[0].size() != 0) File0002 << "\n name:  " + Strn03[0]; break;
                }
                if(Vect07[10] < ruint32(-1)) File0002 << "\n head:  " + Strn0001[Vect07[10]];
                if(Vect07[11] < ruint32(-1)) File0002 << "\n small: " + Strn0001[Vect07[11]];
                if(Vrab13 != 0)
                {
                 File0002 << "\n"; Vrab14 = 0; while(Vrab14 != Vrab13){File0002 << Strn04[Vrab14]; Vrab14 += 1;}
                }
                std::vector < int32 > Vect08; Vect08.resize(17); Vect08[0] = 10; std::vector < string > Strn05; Strn05.resize(17);
                for(Vrab14 = 1; Vrab14 < 17; ++Vrab14)
                {
                 if(Strn03[Vrab14].size() < 10) continue;
                 Vect08[Vrab14] = S_DecryptionINT32(string(Strn03[Vrab14], 0, 5).c_str()); const int32 Vrab18 = L_Positive(Vect08[Vrab14]);
                 if(Vrab18 < 100000000){if(Vrab18 < 10000000){if(Vrab18 < 1000000){if(Vrab18 < 100000){if(Vrab18 < 10000){if(Vrab18 < 1000){if(Vrab18 < 100){if(Vrab18 < 10){Strn05[Vrab14] = "        ";} else {Strn05[Vrab14] = "       ";}} else {Strn05[Vrab14] = "      ";}} else {Strn05[Vrab14] = "     ";}} else {Strn05[Vrab14] = "    ";}} else {Strn05[Vrab14] = "   ";}} else {Strn05[Vrab14] = "  ";}} else {Strn05[Vrab14] = " ";}}
                 if(Vect08[Vrab14] >= 0) Strn05[Vrab14] += " ";
                 const uint32 Vrab17 = Strn05[Vrab14].size(); if(ruint32(Vect08[0]) > Vrab17) Vect08[0] = Vrab17;
                 if(Strn05[0].size() < Vrab17) Strn05[0] = Strn05[Vrab14];
                }
                for(Vrab14 = 0; Vrab14 < 17; ++Vrab14) Strn05[Vrab14].erase(0, Vect08[0]);
                switch(Config.ECD_ResultCodeFormat)
                {
                 case 3: File0002 << " walking_frame_rate  " << Vect06[40]; break;
                 default: if(Vect06[40] != 0 || Vect06[41] != 0) File0002 << " walking_frame_rate   " << Strn05[0] << Vect06[40] << "\n running_frame_rate   " << Strn05[0] << Vect06[41]; break;
                }
                for(Vrab14 = 1; Vrab14 < 17; ++Vrab14)
                {
                 if(Strn03[Vrab14].size() < 10) continue;
                 switch(Vrab14)
                 {
                  case 1: File0002 << "\n walking_speed        "; break;
                  case 2: File0002 << "\n walking_speedz       "; break;
                  case 3: 
                   switch(Config.ECD_ResultCodeFormat)
                   {
                    case 3: File0002 << "\n running_frame_rate  " << Vect06[41] << "\n running_speed        "; break;
                    default: File0002 << "\n running_speed        "; break;
                   }
                  break;
                  case 4: File0002 << "\n running_speedz       "; break;
                  case 5: File0002 << "\n heavy_walking_speed  "; break;
                  case 6: File0002 << "\n heavy_walking_speedz "; break;
                  case 7: File0002 << "\n heavy_running_speed  "; break;
                  case 8: File0002 << "\n heavy_running_speedz "; break;
                  case 9: File0002 << "\n jump_height          "; break;
                  case 10: File0002 << "\n jump_distance        "; break;
                  case 11: File0002 << "\n jump_distancez       "; break;
                  case 12: File0002 << "\n dash_height          "; break;
                  case 13: File0002 << "\n dash_distance        "; break;
                  case 14: File0002 << "\n dash_distancez       "; break;
                  case 15: File0002 << "\n rowing_height        "; break;
                  default: File0002 << "\n rowing_distance      "; break;
                 }
                 File0002 << Strn05[Vrab14] << Vect08[Vrab14] << ".";
                 const uint32 Vrab16 = S_DecryptionUINT32(string(Strn03[Vrab14], 5, 5).c_str());
                 if(Vrab16 < 100000000){if(Vrab16 < 10000000){if(Vrab16 < 1000000){if(Vrab16 < 100000){if(Vrab16 < 10000){if(Vrab16 < 1000){if(Vrab16 < 100){if(Vrab16 < 10){File0002 << "00000000";} else {File0002 << "0000000";}} else {File0002 << "000000";}} else {File0002 << "00000";}} else {File0002 << "0000";}} else {File0002 << "000";}} else {File0002 << "00";}} else {File0002 << "0";}}
                 File0002 << Vrab16; 
                 if(Vrab14 == 16) File0002 << "\n";
                }
                if(Vect06[42] != 0 || Vect06[43] != 0) File0002 << " weapon_hp:        " << Vect06[42] << "\n weapon_drop_hurt: " << Vect06[43] << "\n";
                if(Vect07[12] < ruint32(-1)) File0002 << " weapon_hit_sound:    " + Strn0001[Vect07[12]] + "\n";
                if(Vect07[13] < ruint32(-1)) File0002 << " weapon_drop_sound:   " + Strn0001[Vect07[13]] + "\n";
                if(Vect07[14] < ruint32(-1)) File0002 << " weapon_broken_sound: " + Strn0001[Vect07[14]] + "\n";
                File0002 << "<bmp_end>\n\n";
               }
               break;
               default:
               File0002 << "<bmp_begin>";
               if(Strn03[0].size() != 0) File0002 << "\n   name: " + Strn03[0];
               if(Vect07[10] < ruint32(-1)) File0002 << "\n   head: " + Strn0001[Vect07[10]];
               if(Vect07[11] < ruint32(-1)) File0002 << "\n   small: " + Strn0001[Vect07[11]];
               {
                std::vector < string > Strn04; uint32 Vrab13 = 0;
                while(Vrab13 < 10){if(Vect07[Vrab13] == -1) break; Strn04.push_back("\n   file("); Vrab13 += 1;}
                uint32 Vrab14 = 0; uint32 Vrab15 = 0; if(Vrab13 != 0) Strn04[0] += "0-";
                while(Vrab14 != Vrab13)
                {
                 Vrab15 += (Vect06[(Vrab14 * 4) + 2] * Vect06[(Vrab14 * 4) + 3]);
                 if(Vrab14 + 1 != Vrab13) Strn04[Vrab14 + 1] += std::to_string(Vrab15) + "-";
                 Vrab15 -= 1;
                 Strn04[Vrab14] += std::to_string(Vrab15) + "): ";
                 Vrab14 += 1;
                }
                uint32 Vrab16 = 0; const uint32 Vrab17 = Strn04.size();
                while(Vrab16 != Vrab17)
                {
                 File0002 << Strn04[Vrab16] + Strn0001[Vect07[Vrab16]] + "  w: " << Vect06[Vrab16 * 4] << "  h: " << Vect06[(Vrab16 * 4) + 1] << "  row: " << Vect06[(Vrab16 * 4) + 3] << "  col: " << Vect06[(Vrab16 * 4) + 2];
                 Vrab16 += 1;
                }
               }
               if(Vect06[40] != 0) File0002 << "\n   walking_frame_rate " << Vect06[40];
               {
                for(uint32 Vrab14 = 1; Vrab14 < 17; ++Vrab14)
                {
                 if(Strn03[Vrab14].size() < 10) continue;
                 switch(Vrab14)
                 {
                  case 1: File0002 << "\n   walking_speed "; break;
                  case 2: File0002 << "\n   walking_speedz "; break;
                  case 3: if(Vect06[41] != 0) File0002 << "\n   running_frame_rate " << Vect06[41]; File0002 << "\n   running_speed "; break;
                  case 4: File0002 << "\n   running_speedz "; break;
                  case 5: File0002 << "\n   heavy_walking_speed "; break;
                  case 6: File0002 << "\n   heavy_walking_speedz "; break;
                  case 7: File0002 << "\n   heavy_running_speed "; break;
                  case 8: File0002 << "\n   heavy_running_speedz "; break;
                  case 9: File0002 << "\n   jump_height "; break;
                  case 10: File0002 << "\n   jump_distance "; break;
                  case 11: File0002 << "\n   jump_distancez "; break;
                  case 12: File0002 << "\n   dash_height "; break;
                  case 13: File0002 << "\n   dash_distance "; break;
                  case 14: File0002 << "\n   dash_distancez "; break;
                  case 15: File0002 << "\n   rowing_height "; break;
                  default: File0002 << "\n   rowing_distance "; break;
                 }
                 File0002 << S_DecryptionINT32(string(Strn03[Vrab14], 0, 5).c_str()) << ".";
                 const uint32 Vrab16 = S_DecryptionUINT32(string(Strn03[Vrab14], 5, 5).c_str());
                 if(Vrab16 < 100000000){if(Vrab16 < 10000000){if(Vrab16 < 1000000){if(Vrab16 < 100000){if(Vrab16 < 10000){if(Vrab16 < 1000){if(Vrab16 < 100){if(Vrab16 < 10){File0002 << "00000000";} else {File0002 << "0000000";}} else {File0002 << "000000";}} else {File0002 << "00000";}} else {File0002 << "0000";}} else {File0002 << "000";}} else {File0002 << "00";}} else {File0002 << "0";}}
                 File0002 << Vrab16;
                }
               }
               if(Vect06[42] != 0) File0002 << "\n   weapon_hp: " << Vect06[42];
               if(Vect06[43] != 0) File0002 << "\n   weapon_drop_hurt: " << Vect06[43];
               if(Vect07[12] < ruint32(-1)) File0002 << "\n   weapon_hit_sound: " + Strn0001[Vect07[12]];
               if(Vect07[13] < ruint32(-1)) File0002 << "\n   weapon_drop_sound: " + Strn0001[Vect07[13]];
               if(Vect07[14] < ruint32(-1)) File0002 << "\n   weapon_broken_sound: " + Strn0001[Vect07[14]];
               
               File0002 << "\n<bmp_end>\n\n";
               break;
              }
              
              Strn03.clear(); Vect06.clear(); Vect07.clear(); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 23; Vrab11 = 0; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 24; Vrab11 = 10; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 24; Vrab11 = 11; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 24; Vrab12 += 1; if(Vrab12 > 9) Vrab12 = 25; Vrab11 = Vrab12; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 12; Vrab11 = Vrab12 * 4; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 12; Vrab11 = (Vrab12 * 4) + 1; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 12; Vrab11 = (Vrab12 * 4) + 2; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 12; Vrab11 = (Vrab12 * 4) + 3; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[9]) {Vrab09 = 12; Vrab11 = 40; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[10]){Vrab09 = 12; Vrab11 = 41; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[11]){Vrab09 = 26; Vrab11 = 1; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[12]){Vrab09 = 26; Vrab11 = 2; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[13]){Vrab09 = 26; Vrab11 = 3; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[14]){Vrab09 = 26; Vrab11 = 4; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[15]){Vrab09 = 26; Vrab11 = 5; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[16]){Vrab09 = 26; Vrab11 = 6; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[17]){Vrab09 = 26; Vrab11 = 7; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[18]){Vrab09 = 26; Vrab11 = 8; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[19]){Vrab09 = 26; Vrab11 = 9; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[20]){Vrab09 = 26; Vrab11 = 10; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[21]){Vrab09 = 26; Vrab11 = 11; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[22]){Vrab09 = 26; Vrab11 = 12; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[23]){Vrab09 = 26; Vrab11 = 13; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[24]){Vrab09 = 26; Vrab11 = 14; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[25]){Vrab09 = 26; Vrab11 = 15; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[26]){Vrab09 = 26; Vrab11 = 16; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[27]){Vrab09 = 12; Vrab11 = 42; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[28]){Vrab09 = 12; Vrab11 = 43; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[29]){Vrab09 = 24; Vrab11 = 12; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[30]){Vrab09 = 24; Vrab11 = 13; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[31]){Vrab09 = 24; Vrab11 = 14; continue;}
             break;
             case 2:
              if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 0;
               if(Vrab98){File0002 << "\n"; Vrab98 = false;}
               uint32 Vrab14 = 0; int1 Vrab15 = true;
               while(Vrab14 != 7)
               {
                if(Vect06[Vrab14 * 11] != 0)
                {
                 if(Vrab15)
                 {
                  File0002 << "<weapon_strength_list>";
                  Vrab15 = false;
                 }
                 switch(Config.ECD_ResultCodeFormat)
                 {
                 case 1:
                  File0002 << "\n   entry: " << Vect06[Vrab14 * 11] << " " + Strn03[Vrab14] + "\n    ";
                  if(Vect06[(Vrab14 * 11) + 1] != 0) File0002 << "  zwidth: " << Vect06[(Vrab14 * 11) + 1];
                 File0002 << "  dvx: " << Vect06[(Vrab14 * 11) + 2] << "  dvy: " << Vect06[(Vrab14 * 11) + 3];
                  if(Vect06[(Vrab14 * 11) + 4] != 0) File0002 << "  fall: " << Vect06[(Vrab14 * 11) + 4];
                  if(Vect06[(Vrab14 * 11) + 5] != 0) File0002 << "  arest: " << Vect06[(Vrab14 * 11) + 5];
                  if(Vect06[(Vrab14 * 11) + 6] != 0) File0002 << "  vrest: " << Vect06[(Vrab14 * 11) + 6];
                  if(Vect06[(Vrab14 * 11) + 7] != 0) File0002 << "  respond: " << Vect06[(Vrab14 * 11) + 7];
                  if(Vect06[(Vrab14 * 11) + 8] != 0) File0002 << "  effect: " << Vect06[(Vrab14 * 11) + 8];
                  if(Vect06[(Vrab14 * 11) + 9] != 0) File0002 << "  bdefend: " << Vect06[(Vrab14 * 11) + 9];
                  if(Vect06[(Vrab14 * 11) + 10] != 0) File0002 << "  injury: " << Vect06[(Vrab14 * 11) + 10];
                 break;
                 default:
                 File0002 << "\n entry: " << Vect06[Vrab14 * 11] << " " + Strn03[Vrab14] + "\n ";
                 if(Vect06[(Vrab14 * 11) + 1] != 0) File0002 << " zwidth: " << Vect06[(Vrab14 * 11) + 1];
                 File0002 << " dvx: " << Vect06[(Vrab14 * 11) + 2] << " dvy: " << Vect06[(Vrab14 * 11) + 3];
                 if(Vect06[(Vrab14 * 11) + 4] != 0) File0002 << " fall: " << Vect06[(Vrab14 * 11) + 4];
                 if(Vect06[(Vrab14 * 11) + 5] != 0) File0002 << " arest: " << Vect06[(Vrab14 * 11) + 5];
                 if(Vect06[(Vrab14 * 11) + 6] != 0) File0002 << " vrest: " << Vect06[(Vrab14 * 11) + 6];
                 if(Vect06[(Vrab14 * 11) + 7] != 0) File0002 << " respond: " << Vect06[(Vrab14 * 11) + 7];
                 if(Vect06[(Vrab14 * 11) + 8] != 0) File0002 << " effect: " << Vect06[(Vrab14 * 11) + 8];
                 if(Vect06[(Vrab14 * 11) + 9] != 0) File0002 << " bdefend: " << Vect06[(Vrab14 * 11) + 9];
                 if(Vect06[(Vrab14 * 11) + 10] != 0) File0002 << " injury: " << Vect06[(Vrab14 * 11) + 10];
                 break;
                 }
                }
                Vrab14 += 1;
               }
               if(!Vrab15){File0002 << "\n<weapon_strength_list_end>\n\n";}
              
              Strn03.clear(); Vect06.clear(); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 35; Vrab12 += 1; Vrab11 = Vrab12 * 11; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 13; Vrab11 = (Vrab12 * 11) + 1; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 13; Vrab11 = (Vrab12 * 11) + 2; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 13; Vrab11 = (Vrab12 * 11) + 3; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 13; Vrab11 = (Vrab12 * 11) + 4; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 13; Vrab11 = (Vrab12 * 11) + 5; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 13; Vrab11 = (Vrab12 * 11) + 6; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 13; Vrab11 = (Vrab12 * 11) + 7; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[9]) {Vrab09 = 13; Vrab11 = (Vrab12 * 11) + 8; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[10]){Vrab09 = 13; Vrab11 = (Vrab12 * 11) + 9; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[11]){Vrab09 = 13; Vrab11 = (Vrab12 * 11) + 10; continue;}
             break;
             case 3:
              if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 0;
              if(Vrab98) if(Temp99 != Strn03[0]) File0002 << "\n";

              File0002 << "<frame> " << Vect06[168] << " " + Strn03[0];
               switch(Config.ECD_ResultCodeFormat)
                   {
               case 1:
                    File0002 << "\n   pic: " << L_Format(Vect06[0], 2) << "  state: " << L_Format(Vect06[1], 3);

               break;
               default:
                    File0002 << "\n pic: " << L_Format(Vect06[0], 2) << " state: " << L_Format(Vect06[1], 3);
                    break;
               }
              
                   switch(Config.ECD_ResultCodeFormat)
                   {
                    case 1: File0002 << "  wait: " << Vect06[2] << "  next: " << Vect06[3] << "  centerx: " << Vect06[7] << "  centery: " << Vect06[8]; break;
                    case 2: File0002 << " wait: " << Vect06[2] << " next: " << Vect06[3] << " centerx: " << Vect06[7] << " centery: " << Vect06[8]; break;
                    default: File0002 << " centerx: " << L_Format(Vect06[7], -4) << " centery: " << L_Format(Vect06[8], -4) << " wait: " << L_Format(Vect06[2], 3) << " next: " << L_Format(Vect06[3], 3); break;
                   }

              switch(Config.ECD_ResultCodeFormat)
              {
              case 1:
              
              if(Vect06[4] != 0) File0002 << "  dvx: " << Vect06[4];
              if(Vect06[5] != 0) File0002 << "  dvy: " << Vect06[5];
              if(Vect06[6] != 0) File0002 << "  dvz: " << Vect06[6];
               if(Vect06[9] != 0) File0002 << "  hit_a: " << Vect06[9];
               if(Vect06[10] != 0) File0002 << "  hit_d: " << Vect06[10];
               if(Vect06[11] != 0) File0002 << "  hit_j: " << Vect06[11];
               if(Vect06[12] != 0) File0002 << "  hit_Fa: " << Vect06[12];
               if(Vect06[13] != 0) File0002 << "  hit_Fj: " << Vect06[13];
               if(Vect06[14] != 0) File0002 << "  hit_Da: " << Vect06[14];
               if(Vect06[15] != 0) File0002 << "  hit_Dj: " << Vect06[15];
               if(Vect06[16] != 0) File0002 << "  hit_Ua: " << Vect06[16];
               if(Vect06[17] != 0) File0002 << "  hit_Uj: " << Vect06[17];
               if(Vect06[18] != 0) File0002 << "  hit_ja: " << Vect06[18];
              if(Vect06[19] != 0) File0002 << "  mp: " << Vect06[19];

              break;
              default:
              if(Vect06[4] != 0) File0002 << " dvx: " << L_Format(Vect06[4], 3);
              if(Vect06[5] != 0) File0002 << " dvy: " << L_Format(Vect06[5], 3);
              if(Vect06[6] != 0) File0002 << " dvz: " << L_Format(Vect06[6], 3);
              if(Vect06[19] != 0) File0002 << " mp: " << L_Format(Vect06[19], -4);

              switch(Config.ECD_ResultCodeFormat)
               {
               case 3:
               if(Vect07[0] < ruint32(-1)) File0002 << " sound: " << Strn0001[Vect07[0]];

               break;
               default:
               if(Vect06[9] != 0) File0002 << " hit_a: " << Vect06[9];
               if(Vect06[10] != 0) File0002 << " hit_d: " << Vect06[10];
               if(Vect06[11] != 0) File0002 << " hit_j: " << Vect06[11];
               if(Vect06[12] != 0) File0002 << " hit_Fa: " << Vect06[12];
               if(Vect06[13] != 0) File0002 << " hit_Fj: " << Vect06[13];
               if(Vect06[14] != 0) File0002 << " hit_Da: " << Vect06[14];
               if(Vect06[15] != 0) File0002 << " hit_Dj: " << Vect06[15];
               if(Vect06[16] != 0) File0002 << " hit_Ua: " << Vect06[16];
               if(Vect06[17] != 0) File0002 << " hit_Uj: " << Vect06[17];
               if(Vect06[18] != 0) File0002 << " hit_ja: " << Vect06[18];
               break;
              }
              break;
              }
              {
               int1 Vrab13 = true;
               switch(Config.ECD_ResultCodeFormat)
               {
               case 1:
               if(Vect07[0] < ruint32(-1)) File0002 << "\n   sound: " << Strn0001[Vect07[0]];
               break;
               case 3:
                if(Vect06[9] != 0){if(Vrab13){File0002 << "\n"; Vrab13 = false;} File0002 << " hit_a: " << L_Format(Vect06[9], 2);}
                if(Vect06[10] != 0){if(Vrab13){File0002 << "\n"; Vrab13 = false;} File0002 << " hit_d: " << L_Format(Vect06[10], 2);}
                if(Vect06[11] != 0){if(Vrab13){File0002 << "\n"; Vrab13 = false;} File0002 << " hit_j: " << L_Format(Vect06[11], 2);}
                if(Vect06[12] != 0){if(Vrab13){File0002 << "\n"; Vrab13 = false;} File0002 << " hit_Fa: " << L_Format(Vect06[12], 2);}
                if(Vect06[13] != 0){if(Vrab13){File0002 << "\n"; Vrab13 = false;} File0002 << " hit_Fj: " << L_Format(Vect06[13], 2);}
                if(Vect06[14] != 0){if(Vrab13){File0002 << "\n"; Vrab13 = false;} File0002 << " hit_Da: " << L_Format(Vect06[14], 2);}
                if(Vect06[15] != 0){if(Vrab13){File0002 << "\n"; Vrab13 = false;} File0002 << " hit_Dj: " << L_Format(Vect06[15], 2);}
                if(Vect06[16] != 0){if(Vrab13){File0002 << "\n"; Vrab13 = false;} File0002 << " hit_Ua: " << L_Format(Vect06[16], 2);}
                if(Vect06[17] != 0){if(Vrab13){File0002 << "\n"; Vrab13 = false;} File0002 << " hit_Uj: " << L_Format(Vect06[17], 2);}
                if(Vect06[18] != 0){if(Vrab13){File0002 << "\n"; Vrab13 = false;} File0002 << " hit_ja: " << L_Format(Vect06[18], 2);}
               break;
               default:
                if(Vect07[0] < ruint32(-1)) File0002 << "\n sound: " << Strn0001[Vect07[0]];
               break;
               }
              }
              File0002 << "\n";
              uint32 Vrab16 = 0; if(Config.ECD_ResultCodeFormat == 3) Vrab16 = 4;
              while(Vrab16 != 6)
              {
               switch(Vrab16)
               {
                case 0:
                 {
                  uint32 Vrab13 = 20; int1 Vrab14 = false;
                  while(Vrab13 <= 21){if(Vect06[Vrab13] != 0){Vrab14 = true; break;} Vrab13 += 1;} if(Vrab14)
                  {
                   switch(Config.ECD_ResultCodeFormat)
                   {
                    case 1: File0002 << "   bpoint:\n      x: " << Vect06[20] << "  y: " << Vect06[21] << "\n   bpoint_end:\n"; break;
                    case 3: File0002 << " bpoint: y: " << L_Format(Vect06[21], -2) << " x: " << L_Format(Vect06[20], -2) << " bpoint_end:\n"; break;
                    default: File0002 << " bpoint: x: " << Vect06[20] << " y: " << Vect06[21] << " bpoint_end:\n"; break;
                   }
                  }
                 }
                break;
                case 1:
                 {
                  uint32 Vrab13 = 22; int1 Vrab14 = false;
                  while(Vrab13 <= 40){if(Vect06[Vrab13] != 0){Vrab14 = true; break;} Vrab13 += 1;} if(Vrab14)
                  {
                   switch(Config.ECD_ResultCodeFormat)
                   {
                    case 3: File0002 << " cpoint: kind: " << Vect06[22] << " y: " << L_Format(Vect06[24], 9) << " cover: " << L_Format(Vect06[37], 1) << " x: " << L_Format(Vect06[23], 4); break;
                    default: File0002 << " cpoint: kind: " << Vect06[22] << " x: " << Vect06[23] << " y: " << Vect06[24]; break;
                   }
                   if(Vect06[25] != 0) File0002 << " vaction: " << Vect06[25];
                   if(Vect06[26] != 0) File0002 << " aaction: " << Vect06[26];
                   if(Vect06[27] != 0) File0002 << " daction: " << Vect06[27];
                   if(Vect06[28] != 0) File0002 << " jaction: " << Vect06[28];
                   if(Vect06[29] != 0) File0002 << " taction: " << Vect06[29];
                   if(Vect06[30] != 0) File0002 << " throwvx: " << Vect06[30];
                   if(Vect06[31] != 0) File0002 << " throwvy: " << Vect06[31];
                   if(Vect06[32] != 0) File0002 << " throwvz: " << Vect06[32];
                   if(Vect06[33] != 0) File0002 << " throwinjury: " << Vect06[33];
                   if(Vect06[34] != 0) File0002 << " dircontrol: " << Vect06[34];
                   if(Vect06[35] != 0) File0002 << " hurtable: " << Vect06[35];
                   if(Vect06[36] != 0) File0002 << " decrease: " << Vect06[36];
                   if(Config.ECD_ResultCodeFormat == 2) if(Vect06[37] != 0) File0002 << " cover: " << Vect06[37];
                   if(Vect06[38] != 0) File0002 << " injury: " << Vect06[38];
                   if(Vect06[39] != 0) File0002 << " fronthurtact: " << Vect06[39];
                   if(Vect06[40] != 0) File0002 << " backhurtact: " << Vect06[40];
                   File0002 << " cpoint_end:\n";
                  }
                 }
                break;
                case 2:
                 {
                  uint32 Vrab13 = 41; int1 Vrab14 = false;
                  while(Vrab13 <= 49){if(Vect06[Vrab13] != 0){Vrab14 = true; break;} Vrab13 += 1;} if(Vrab14)
                  {
                   switch(Config.ECD_ResultCodeFormat)
                   {
                    case 3: File0002 << " wpoint: kind: " << Vect06[41] << " y: " << L_Format(Vect06[43], 9) << " cover: " << L_Format(Vect06[49], 1) << " x: " << L_Format(Vect06[42], 4); break;
                    default: File0002 << " wpoint: kind: " << Vect06[41] << " x: " << Vect06[42] << " y: " << Vect06[43]; break;
                   }
                   
                if(Vect06[47] != 0) File0002 << " weaponact: " << L_Format(Vect06[47], 2);
                if(Vect06[48] != 0) File0002 << " attacking: " << L_Format(Vect06[48], 1);
                if(Config.ECD_ResultCodeFormat == 2) File0002 << " cover: " << Vect06[49];
                if(Vect06[44] != 0) File0002 << " dvx: " << L_Format(Vect06[44], 3);
                if(Vect06[45] != 0) File0002 << " dvy: " << L_Format(Vect06[45], 3);
                if(Vect06[46] != 0) File0002 << " dvz: " << L_Format(Vect06[46], -2);
                File0002 << " wpoint_end:\n";
               }
              }
                break;
                case 3:
              {
               uint32 Vrab13 = 50; int1 Vrab14 = false;
               while(Vrab13 <= 57){if(Vect06[Vrab13] != 0){Vrab14 = true; break;} Vrab13 += 1;} if(Vrab14)
               {
                
                  switch(Config.ECD_ResultCodeFormat)
                   {
                    case 3: File0002 << " opoint: kind: " << Vect06[41] << " y: " << L_Format(Vect06[52], 9) << " oid: " << L_Format(Vect06[55], 3) << " x: " << L_Format(Vect06[51], 4) << " action: " << L_Format(Vect06[56], 5) << " facing: " << L_Format(Vect06[57], -4); break;
                    default: File0002 << " opoint: kind: " << Vect06[50] << " x: " << Vect06[51] << " y: " << Vect06[52] << " oid: " << Vect06[55] << " action: " << Vect06[56] << " facing: " << Vect06[57]; break;
                   }
                
                if(Vect06[53] != 0) File0002 << " dvx: " << L_Format(Vect06[53], 3);
                if(Vect06[54] != 0) File0002 << " dvy: " << L_Format(Vect06[54], 3);
                File0002 << " opoint_end:\n";
               }
              }
                break;
                case 4: 
              {
               for(uint32 Vrab13 = 0; Vrab13 < 5; ++Vrab13)
               {
                uint32 Vrab14 = 58 + (Vrab13 * 17); int1 Vrab15 = false;
                while(Vrab14 <= 74 + (Vrab13 * 17)){if(Vect06[Vrab14] != 0){Vrab15 = true; break;} Vrab14 += 1;} if(Vrab15)
                {
                 Vrab14 = 58 + (Vrab13 * 17);
                 switch(Config.ECD_ResultCodeFormat)
                   {
                    case 3: 
                     File0002 << " itr: kind: " << L_Format(Vect06[Vrab14], -3) << " y: " << L_Format(Vect06[Vrab14 + 2], 9) << " h: " << L_Format(Vect06[Vrab14 + 4], 5) << " x: " << L_Format(Vect06[Vrab14 + 1], 4) << " w: " << L_Format(Vect06[Vrab14 + 3], 3);
                     
                     if(Vect06[Vrab14 + 8] != 0) File0002 << " fall: " << L_Format(Vect06[Vrab14 + 8], 3);
                     if(Vect06[Vrab14 + 5] != 0) File0002 << " zwidth: " << L_Format(Vect06[Vrab14 + 5], 2);
                     if(Vect06[Vrab14 + 9] != 0) File0002 << " arest: " << L_Format(Vect06[Vrab14 + 9], 2);
                     if(Vect06[Vrab14 + 10] != 0) File0002 << " vrest: " << L_Format(Vect06[Vrab14 + 10], 2);
                     if(Vect06[Vrab14 + 6] != 0) File0002 << " dvx: " << L_Format(Vect06[Vrab14 + 6], 3);
                     if(Vect06[Vrab14 + 7] != 0) File0002 << " dvy: " << L_Format(Vect06[Vrab14 + 7], 3);
                    break;
                    default: File0002 << " itr: kind: " << Vect06[Vrab14] << " x: " << Vect06[Vrab14 + 1] << " y: " << Vect06[Vrab14 + 2] << " w: " << Vect06[Vrab14 + 3] << " h: " << Vect06[Vrab14 + 4] << " zwidth: ";
                     if(Vect06[Vrab14 + 5] == 0){File0002 << "15";} else {File0002 << Vect06[Vrab14 + 5];}
                     if(Vect06[Vrab14 + 6] != 0) File0002 << " dvx: " << Vect06[Vrab14 + 6];
                     if(Vect06[Vrab14 + 7] != 0) File0002 << " dvy: " << Vect06[Vrab14 + 7];
                     if(Vect06[Vrab14 + 9] != 0) File0002 << " arest: " << Vect06[Vrab14 + 9];
                     if(Vect06[Vrab14 + 10] != 0) File0002 << " vrest: " << Vect06[Vrab14 + 10];
                     if(Vect06[Vrab14 + 8] != 0) File0002 << " fall: " << Vect06[Vrab14 + 8];
                    break;
                   }
                 if(Vect06[Vrab14 + 13] != 0) File0002 << " bdefend: " << L_Format(Vect06[Vrab14 + 13], 2);
                 if(Vect06[Vrab14 + 14] != 0) File0002 << " injury: " << L_Format(Vect06[Vrab14 + 14], 3);
                 if(Vect06[Vrab14 + 12] != 0) File0002 << " effect: " << L_Format(Vect06[Vrab14 + 12], 1);
                 if(Vect06[Vrab14 + 11] != 0) File0002 << " respond: " << Vect06[Vrab14 + 11];
                 if(Vect06[Vrab14 + 15] != 0) File0002 << " catchingact: " << Vect06[Vrab14 + 15] << " " << Vect06[Vrab14 + 15];
                   if(Vect06[Vrab14 + 16] != 0) File0002 << " caughtact: " << Vect06[Vrab14 + 16] << " " << Vect06[Vrab14 + 16];
                   File0002 << " itr_end:\n";
                  } else {break;}
                 }
                }
                break;
                case 5:
                {
                 for(uint32 Vrab13 = 0; Vrab13 < 5; ++Vrab13)
                 {
                  uint32 Vrab14 = 143 + (Vrab13 * 5); int1 Vrab15 = false;
                  while(Vrab14 <= 147 + (Vrab13 * 5)){if(Vect06[Vrab14] != 0){Vrab15 = true; break;} Vrab14 += 1;} if(Vrab15)
                  {
                   Vrab14 = 143 + (Vrab13 * 5);
                   File0002 << " bdy:";
                    switch(Config.ECD_ResultCodeFormat)
                   {
                    case 3: File0002 << " kind: " << L_Format(Vect06[Vrab14], -3) << " y: " << L_Format(Vect06[Vrab14 + 2], 9) << " h: " << L_Format(Vect06[Vrab14 + 4], 5) << " x: " << L_Format(Vect06[Vrab14 + 1], 4) << " w: " << L_Format(Vect06[Vrab14 + 3], 3); break;
                    default: 
                     if(Vect06[Vrab14] != 0) File0002 << " kind: " << Vect06[Vrab14];
                     File0002 << " x: " << Vect06[Vrab14 + 1] << " y: " << Vect06[Vrab14 + 2] << " w: " << Vect06[Vrab14 + 3] << " h: " << Vect06[Vrab14 + 4];
                    break;
                   }
                   File0002 << " bdy_end:\n";
                  } else {break;}
                 }
                }
                break;
                default: break;
               }
               switch(Config.ECD_ResultCodeFormat)
               {
                case 3:
                 switch(Vrab16)
                 {
                  case 4: Vrab16 += 1; break;
                  case 5: Vrab16 = 1; break;
                  case 1: Vrab16 = 3; break;
                  case 3: Vrab16 = 2; break;
                  case 2: Vrab16 = 0; break;
                  default: Vrab16 = 6; break;
                 }
                break;
                default: Vrab16 += 1; break;
               }
              }
              File0002 << "<frame_end>\n"; Temp99 = Strn03[0]; Vrab98 = true;
              
              Strn03.clear(); Vect06.clear(); Vect07.clear(); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 14; Vrab11 = 0; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 27; Vrab11 = 1; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 14; Vrab11 = 2; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 14; Vrab11 = 3; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 14; Vrab11 = 4; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 14; Vrab11 = 5; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 14; Vrab11 = 6; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 14; Vrab11 = 7; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[9]) {Vrab09 = 29; Vrab11 = 8; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[10]){Vrab09 = 14; Vrab11 = 9; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[11]){Vrab09 = 14; Vrab11 = 10; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[12]){Vrab09 = 14; Vrab11 = 11; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[13]){Vrab09 = 14; Vrab11 = 12; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[14]){Vrab09 = 14; Vrab11 = 13; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[15]){Vrab09 = 14; Vrab11 = 14; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[16]){Vrab09 = 14; Vrab11 = 15; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[17]){Vrab09 = 14; Vrab11 = 16; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[18]){Vrab09 = 14; Vrab11 = 17; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[19]){Vrab09 = 14; Vrab11 = 18; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[20]){Vrab09 = 14; Vrab11 = 19; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[21]){Vrab09 = 25; Vrab11 = 0; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[22]){Vrab09 = 4; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[23]){Vrab09 = 5; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[24]){Vrab09 = 6; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[25]){Vrab09 = 7; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[26]){Vrab09 = 8; Vrab12 += 1; if(Vrab12 > 4) Vrab12 = 4; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[27]){Vrab09 = 9; Vect07[1] += 1; if(Vect07[1] > 4) Vect07[1] = 4; continue;}
             break;
             case 4:
              if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 3; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 15; Vrab11 = 20; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 15; Vrab11 = 21; continue;}
             break;
             case 5:
              if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 3; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 16; Vrab11 = 22; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 16; Vrab11 = 23; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 30; Vrab11 = 24; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 16; Vrab11 = 25; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 16; Vrab11 = 26; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 16; Vrab11 = 27; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 16; Vrab11 = 28; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 16; Vrab11 = 29; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[9]) {Vrab09 = 16; Vrab11 = 30; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[10]){Vrab09 = 16; Vrab11 = 31; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[11]){Vrab09 = 16; Vrab11 = 32; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[12]){Vrab09 = 16; Vrab11 = 33; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[13]){Vrab09 = 16; Vrab11 = 34; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[14]){Vrab09 = 16; Vrab11 = 35; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[15]){Vrab09 = 16; Vrab11 = 36; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[16]){Vrab09 = 16; Vrab11 = 37; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[17]){Vrab09 = 16; Vrab11 = 38; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[18]){Vrab09 = 16; Vrab11 = 39; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[19]){Vrab09 = 16; Vrab11 = 40; continue;}
             break;
             case 6:
              if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 3; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 17; Vrab11 = 41; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 17; Vrab11 = 42; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 31; Vrab11 = 43; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 17; Vrab11 = 44; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 17; Vrab11 = 45; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 17; Vrab11 = 46; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 17; Vrab11 = 47; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 17; Vrab11 = 48; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[9]) {Vrab09 = 17; Vrab11 = 49; continue;}
             break;
             case 7:
              if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 3; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 18; Vrab11 = 50; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 18; Vrab11 = 51; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 32; Vrab11 = 52; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 18; Vrab11 = 53; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 18; Vrab11 = 54; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 28; Vrab11 = 55; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 18; Vrab11 = 56; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 18; Vrab11 = 57; continue;}
             break;
             case 8: case 10:
              if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 3; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 19; Vrab11 = 58 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 19; Vrab11 = 59 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 33; Vrab11 = 60 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 19; Vrab11 = 61 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 19; Vrab11 = 62 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[6]) {Vrab09 = 19; Vrab11 = 63 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[7]) {Vrab09 = 19; Vrab11 = 64 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[8]) {Vrab09 = 19; Vrab11 = 65 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[9]) {Vrab09 = 19; Vrab11 = 66 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[10]){Vrab09 = 19; Vrab11 = 67 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[11]){Vrab09 = 19; Vrab11 = 68 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[12]){Vrab09 = 19; Vrab11 = 69 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[13]){Vrab09 = 19; Vrab11 = 70 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[14]){Vrab09 = 19; Vrab11 = 71 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[15]){Vrab09 = 19; Vrab11 = 72 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[16]){Vrab09 = 21; Vrab11 = 73 + (Vrab12 * 17); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[17]){Vrab09 = 21; Vrab11 = 74 + (Vrab12 * 17); continue;}
              if(Vrab09 == 10) if(Vrab10 == Config.ECD_ResultEncryption[93]){Vrab09 = 8; Vrab08 += 5; continue;}
             break;
             case 9:
              if(Vrab10 == Config.ECD_ResultEncryption[0]) {Vrab09 = 3; continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[1]) {Vrab09 = 20; Vrab11 = 143 + (Vect07[1] * 5); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[2]) {Vrab09 = 20; Vrab11 = 144 + (Vect07[1] * 5); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[3]) {Vrab09 = 34; Vrab11 = 145 + (Vect07[1] * 5); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[4]) {Vrab09 = 20; Vrab11 = 146 + (Vect07[1] * 5); continue;}
              if(Vrab10 == Config.ECD_ResultEncryption[5]) {Vrab09 = 20; Vrab11 = 147 + (Vect07[1] * 5); continue;}
             break;
             case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 35:
              if(Vrab11 < Vect06.size() && Vrab11 >= 0) Vect06[Vrab11] = S_DecryptionINT32(string(Temp02, Vrab08, 5).c_str()); Vrab08 += 4;
              switch(Vrab09){case 11: Vrab09 = 22; Vrab11 = 0; continue; case 12: Vrab09 = 1; continue; case 13: Vrab09 = 2; continue; case 14: Vrab09 = 3; continue; case 15: Vrab09 = 4; continue; case 16: Vrab09 = 5; continue; case 17: Vrab09 = 6; continue; case 18: Vrab09 = 7; continue; case 19: Vrab09 = 8; continue; case 20: Vrab09 = 9; continue; case 21: Vrab09 = 10; continue; case 35: Vrab09 = 36; Vrab11 = Vrab12; continue; default: break;}
             break;
             case 22: case 23: case 36:
              {
               const uint32 Vrab13 = S_DecryptionINT32(string(Temp02, Vrab08, 5).c_str()); Vrab08 += 5; Strn03[Vrab11] = S_DecryptionSTRING(string(Temp02, Vrab08, Vrab13)); Vrab08 += Vrab13 - 1;
              }
              if(Vrab09 == 22){Vrab09 = 3;} else {if(Vrab09 == 23){Vrab09 = 1;} else {Vrab09 = 2;}} continue;
             case 24: case 25:
              if(Vrab11 < Vect07.size() && Vrab11 >= 0) Vect07[Vrab11] = S_DecryptionUINT32(string(Temp02, Vrab08, 5).c_str()); Vrab08 += 4;
              switch(Vrab09){case 24: Vrab09 = 1; continue; case 25: Vrab09 = 3; continue; default: break;}
             break;
             case 26:
              if(Vrab11 < Strn03.size() && Vrab11 >= 0) Strn03[Vrab11] = string(Temp02, Vrab08, 10); Vrab08 += 9; Vrab09 = 1; continue;
             case 27: case 28:
              if(Vrab10 == Config.ECD_ResultEncryption[93])
              {if(Vrab09 == 27){const uint32 Vrab13 = Vect0001[S_DecryptionINT32(string(Temp02, Vrab08 + 1, 5).c_str())]; if(Vrab13 > 1000){if(Vrab11 < Vect06.size() && Vrab11 >= 0) Vect06[Vrab11] = 0;} else {if(Vrab11 < Vect06.size() && Vrab11 >= 0) Vect06[Vrab11] = Vect0001[S_DecryptionINT32(string(Temp02, Vrab08 + 1, 5).c_str())] + 8000;}} else {if(Vrab11 < Vect06.size() && Vrab11 >= 0) Vect06[Vrab11] = Vect0001[S_DecryptionINT32(string(Temp02, Vrab08 + 1, 5).c_str())];} Vrab08 += 5;} else
              {if(Vrab11 < Vect06.size() && Vrab11 >= 0) Vect06[Vrab11] = S_DecryptionINT32(string(Temp02, Vrab08, 5).c_str()); Vrab08 += 4;}
              if(Vrab09 == 27){Vrab09 = 3;} else {Vrab09 = 7;} continue;
             break;
             case 29: case 30: case 31: case 32: case 33: case 34:
              if(Vrab10 == Config.ECD_ResultEncryption[93])
              {
               const int32 Vrab13 = S_DecryptionINT32(string(Temp02, Vrab08 + 6, 5).c_str()); if(Vrab13 < 0){if(Vrab11 < Vect06.size() && Vrab11 >= 0) Vect06[Vrab11] = -(Vect0001[S_DecryptionINT32(string(Temp02, Vrab08 + 1, 5).c_str())] * 1000000) + Vrab13;} else {if(Vrab11 < Vect06.size() && Vrab11 >= 0) Vect06[Vrab11] = (Vect0001[S_DecryptionINT32(string(Temp02, Vrab08 + 1, 5).c_str())] * 1000000) + Vrab13;} Vrab08 += 10;
              } else {if(Vrab11 < Vect06.size() && Vrab11 >= 0) Vect06[Vrab11] = S_DecryptionINT32(string(Temp02, Vrab08, 5).c_str()); Vrab08 += 4;}
              switch(Vrab09){case 29: Vrab09 = 3; continue; case 30: Vrab09 = 5; continue; case 31: Vrab09 = 6; continue; case 32: Vrab09 = 7; continue; case 33: Vrab09 = 8; continue; case 34: Vrab09 = 9; continue; default: break;}
             break;
             default: break;
            }
           }
          }
         break;
        }
        if(Vrab08 != Vrab07) break;
        File0002.close();
        continue;
       }
       if(Temp02.at(0) == Config.ECD_ResultEncryption[8])
       {
        if(Post01 > Post05 - static_cast < std::streampos > (11)) break;
        Temp02.resize(5); File0001.read(&Temp02.at(0), 5); const uint32 Vrab05 = S_DecryptionUINT32(Temp02.c_str());
        File0001.read(&Temp02.at(0), 5); const uint32 Vrab07 = S_DecryptionUINT32(Temp02.c_str());
        if(Post01 > Post05 - static_cast < std::streampos > (11 + ruint64(Vrab07))) break;
        Temp02.resize(Vrab07); File0001.read(&Temp02.at(0), Vrab07); Temp02 = S_DecryptionSTRING(Temp02);
        string Temp04; Temp04.resize(5); File0001.read(&Temp04.at(0), 5); const uint32 Vrab08 =  S_DecryptionUINT32(Temp04.c_str());

        if(!Config.ECD_InstallOverwrite && L_Exist(Strn0001[Vrab05])){Console.PrintWrite("() >> INFO - \"" + Strn0001[Vrab05] + "\" skipped due to a file with same name already exist.\n"); Console.PrintOut(); continue;}
        Console.PrintWrite("[] >> Parsing \"" + Strn0001[Vrab05] + "\" from the package");
        if(!Config.ECD_InstallSeparated || string(Strn0001[Vrab05], Strn0001[Vrab05].size() - 4, 4) != ".txt")
        {
         Strn0001[Vrab05] = string(Strn0001[Vrab05], 0, Strn0001[Vrab05].size() - 4) + ".txt";
         if(!Config.ECD_InstallSeparated){Strn0001[Vrab05] = Config.ECD_ResultDirectory + L_Reform(Strn0001[Vrab05]); while(L_Exist(Strn0001[Vrab05])) L_Rename(Strn0001[Vrab05]);} Console.PrintWrite(" as \"" + Strn0001[Vrab05] + "\"");
        }
        Console.PrintWrite(".\n"); Console.PrintOut();

        L_Create(L_Execute(Strn0001[Vrab05])); L_Summary(Strn0001[Vrab05] + "\n");
        if(Vrab08 != 0)
        {
         if(Strn02.size() >= Vrab08)
         {
          Strn02[Vrab08 - 1] = Strn0001[Vrab05];
         } else
         {
          string Temp05; uint32 Vrab09 = Strn02.size();
          if(Strn02.size() > 0){Temp05 = Strn02[0];} else {Temp05 = Strn0001[Vrab05];}
          while(Vrab09 != Vrab08){Strn02.push_back(Temp05); Vrab09 += 1;}
          Strn02[Vrab08 - 1] = Strn0001[Vrab05];
         }
        } else
        {
         Strn02.push_back(Strn0001[Vrab05]);
        }

        uint32 Vrab09 = ruint32(-1); uint32 Vrab10 = 0;
        switch(Config.ECD_ResultCodeFormat)
        {
         case 1:
         default:
          while((Vrab09 += 1) != Vrab07)
          {
           if(Vrab09 != 0) File0002 << " "; const uint8 Vrab11 = Temp02.at(Vrab09);
           switch(Vrab10)
           {
            case 0: case 4:
             if(Vrab11 == Config.ECD_ResultEncryption[0]) {Vrab10 = 5; File0002 << "name:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[1]) {Vrab10 = 2; File0002 << "width:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[2]) {Vrab10 = 3; File0002 << "zboundary:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[3]) {Vrab10 = 3; File0002 << "perspective:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[4]) {Vrab10 = 6; File0002 << "shadow:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[5]) {Vrab10 = 7; File0002 << "layer:"; continue;}
             if(Vrab10 == 4) if(Vrab11 == Config.ECD_ResultEncryption[93]){Vrab10 = 0; File0002 << S_DecryptionINT32(string(Temp02, Vrab09 + 1, 5).c_str()); Vrab09 += 5; continue;}
            break;
            case 1:
             if(Vrab11 == Config.ECD_ResultEncryption[0]) {Vrab10 = 0;  File0002 << "layer_end"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[1]) {Vrab10 = 8;  File0002 << "transparency:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[2]) {Vrab10 = 8;  File0002 << "width:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[3]) {Vrab10 = 8;  File0002 << "height:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[4]) {Vrab10 = 8;  File0002 << "x:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[5]) {Vrab10 = 8;  File0002 << "y:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[6]) {Vrab10 = 8;  File0002 << "cc:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[7]) {Vrab10 = 8;  File0002 << "c1:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[8]) {Vrab10 = 8;  File0002 << "c2:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[9]) {Vrab10 = 8;  File0002 << "rect:"; continue;}
             if(Vrab11 == Config.ECD_ResultEncryption[10]) {Vrab10 = 8; File0002 << "rect32:"; continue;}
            break;
            case 2: case 3: case 8:
             File0002 << S_DecryptionINT32(string(Temp02, Vrab09, 5).c_str()); Vrab09 += 4;
             switch(Vrab10){case 2: Vrab10 = 0; continue; case 3: Vrab10 = 4; continue; case 8: Vrab10 = 1; continue; default: break;}
            break;
            case 5:
             {
              const uint32 Vrab12 = S_DecryptionINT32(string(Temp02, Vrab09, 5).c_str()); Vrab09 += 5; File0002 << S_DecryptionSTRING(string(Temp02, Vrab09, Vrab12)); Vrab09 += Vrab12 - 1;
             }
             switch(Vrab10){case 5: Vrab10 = 0; continue; default: break;}
            break;
            case 6: case 7:
             File0002 << Strn0001[S_DecryptionUINT32(string(Temp02, Vrab09, 5).c_str())]; Vrab09 += 4;
             switch(Vrab10){case 6: Vrab10 = 3; File0002 << " :"; continue; case 7: Vrab10 = 1; continue; default: break;}
            break;
            default: break;
           }
          }
         break;
        }
       }
       Vrab88 = true; break;
      }
      if(File0001.tellg() == Post05) Vrab06 = false;
      Post01 = File0001.tellg(); if(Vrab06 || Post01 <= 336 || Post01 >= Post04)
      {Console.PrintWrite(">< ERROR - Either \"" + Temp03 + "\" "); if(Vrab88){Console.PrintWrite("is from higher version of Modified DDraw, it is corrupt,");} else {Console.PrintWrite("is corrupt");} Console.PrintWrite(" or it is not the package made using Modified DDraw. [" + std::to_string(Post01) + "]\n"); Console.PrintOut(); continue;}

      Console.PrintWrite("[] Complete.\n"); Console.PrintOut();
     } else {Console.PrintWrite(">< ERROR - \"" + Temp02 + "\" inaccessible.\n"); Console.PrintOut();}
    }
    if(File0001.is_open()) File0001.close();
    if(Vrab01 == 0){Console.PrintWrite("() INFO - Found no package.\n"); Console.PrintOut();}
   }
   L_Cleaning();

   string Temp03; string Temp04;

       if(Config.MAIN_MOD)
       if(Config.MOD_ModulingLevel > 0)
       {
        string Temp01 = Config.ECD_ResultDirectory + "\\none.bmp";
        while(L_Exist(Temp01)) L_Rename(Temp01);
        string Temp02 = Config.ECD_ResultDirectory + "\\notification.bmp";
        while(L_Exist(Temp02)) L_Rename(Temp02);
        Temp03 = Config.ECD_ResultDirectory + "\\modifier.txt";
        while(L_Exist(Temp03)) L_Rename(Temp03);
        Temp04 = Config.ECD_ResultDirectory + "\\modifier_display.txt";
        while(L_Exist(Temp04)) L_Rename(Temp04);

        if(L_Create(L_Execute(Temp03)))
        {
         File0002 << "<bmp_begin>\n name: Modifier\n head: " + Temp01 + "\n small: " + Temp01 + "\n file(0-0): " + Temp01 + " w: 1 h: 1 row: 1 col: 1\n<bmp_end>\n\n<frame> 180 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 9999999\n<frame_end>\n<frame> 182 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 186 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 188 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 219 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 212 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 0 Injection\n pic: -1 state: 3005 next: 1 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 1 Injection\n pic: -1 wait: 1 state: 3005 next: 240 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 240 Injection\n pic: -1 state: 9998 next: 1000 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n\n<frame> 235 Injection\n pic: -1 state: 3005 next: 236 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 236 Injection\n pic: -1 state: 3005 next: 235 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 237 Injection\n pic: -1 state: 3005 wait: 2 next: 238 dvx: -2147483648 dvy: 550 dvz: 99999999\n<frame_end>\n<frame> 238 Injection\n pic: -1 state: 3005 next: 239 dvx: -2147483648 dvy: 550 dvz: 99999999\n opoint: kind: 1 x: 100 y: 0 action: 0 oid: " << Database.InjectorID2 << " facing: 10 opoint_end:\n<frame_end>\n<frame> 239 Injection\n pic: -1 state: 3005 next: 235 dvx: -2147483648 dvy: 550 dvz: 99999999\n opoint: kind: 1 x: 100 y: 0 action: 1 oid: " << Database.InjectorID2 << " facing: 10 opoint_end:\n<frame_end>";
         File0002.close(); L_Summary(Temp03 + "\n");
         L_Create(L_Execute(Temp04));
         File0002 << "<bmp_begin>\nfile(0-1): " + Temp02 + " w: 207 h: 34 row: 1 col: 2\n<bmp_end>\n\n<frame> 0 Injection\n pic: 0 state: 3005 wait: 121 next: 2 dvx: 550 dvy: 550 dvz: 99999999 centerx: 1000 centery: -1000\n<frame_end>\n<frame> 1 Injection\n pic: 1 state: 3005 wait: 140 next: 2 dvx: 550 dvy: 550 dvz: 9999999 centerx: 1000 centery: -1000\n<frame_end>\n\n<frame> 2 Injection\n pic: -1 state: 9998 next: 0 dvx: 550 dvy: 550 dvz: 9999999\n<frame_end>";
         File0002.close(); L_Summary(Temp04 + "\n");
         const string Temp05 = Config.AI_OldDirectory + "\\" + std::to_string(Database.InjectorID) + ".as";
         L_Create(L_Execute(Temp05));
         File0002 << "void id(){return;}";
         File0002.close(); L_Summary(Temp05 + "\n");
         BMP Bitm01(208, 70, false); constexpr uint8 Temp06[] = "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\377\377\377\376\377\377\377\377\377\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\377\377\377\376\377\377\377\377\377\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377" "\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377" "\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\154\040\020\376\377\377\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\326\163\132\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000";
         Bitm01.data.insert(Bitm01.data.begin(), &Temp06[0], &Temp06[43680]); Bitm01.data.resize(43680);
         if(Config.MOD_ModulingInfoTrans){for(int32 Vrab01 = 0; Vrab01 < 208 * 70 * 3; Vrab01 += 3) if(Bitm01.data[Vrab01] == 254) if(Bitm01.data[Vrab01 + 1] == 255) if(Bitm01.data[Vrab01 + 2] == 255){Bitm01.data[Vrab01] = 108; Bitm01.data[Vrab01 + 1] = 32; Bitm01.data[Vrab01 + 2] = 16;}} else
         {for(int32 Vrab01 = 0; Vrab01 < 208 * 70 * 3; Vrab01 += 3) if(Bitm01.data[Vrab01] == 254) if(Bitm01.data[Vrab01 + 1] == 255) if(Bitm01.data[Vrab01 + 2] == 255){Bitm01.data[Vrab01] = 0; Bitm01.data[Vrab01 + 1] = 0; Bitm01.data[Vrab01 + 2] = 0;}}
         Bitm01.write(L_Execute(Temp02).c_str()); L_Summary(Temp02 + "\n");
         Bitm01.bmp_info_header.width = 1; Bitm01.bmp_info_header.height = 1; Bitm01.data = {'\000', '\000', '\000', '\000', '\000', '\000'};
         Bitm01.write(L_Execute(Temp01).c_str()); L_Summary(Temp01 + "\n");
        } else {Config.MOD_ModulingLevel = 0;}
       }

   L_Open(Config.ECD_InstallODataDirectory);
   L_Create(L_Execute(Config.ECD_InstallDataDirectory));

   string Temp01; Vect69.resize(Vect01.size());

   while(File0001)
   {
    File0001 >> Temp01; if(!File0001) break; if(Temp01.at(0) == '#'){std::getline(File0001, Temp01); continue;}
    if(Temp01 == "<object>")
    {
     File0002 << "<object>\n"; int1 Vrab76 = false;
     while(File0001)
     {
      File0001 >> Temp01; if(!File0001) break; if(Temp01.at(0) == '#'){std::getline(File0001, Temp01); continue;}
      if(Temp01 == "id:"){File0001 >> Temp01; const int32 Vrab01 = L_Positive(L_Numbering(Temp01)); if(Vect69[Vrab01] == 0){File0002 << " id: " << Vrab01; Vrab76 = true;} else {Vect69[Vrab01] -= 1; Vrab76 = false;} continue;}
      if(Temp01 == "type:"){File0001 >> Temp01; if(Vrab76) File0002 << " type: " << L_Numbering(Temp01); continue;}
      if(Temp01 == "file:"){File0001 >> Temp01; if(Vrab76) File0002 << " file: " + Temp01 + "\n"; continue;}
      if(Temp01 == "<object_end>")
      {
       const uint32 Vrab01 = Strn01.size();
       for(uint32 Vrab02 = 0; Vrab02 < Vrab01; ++Vrab02)
       {
        uint32 Vrab03 = 0; while(Strn01[Vrab02].at(Vrab03) != 't') Vrab03 += 1;
        const uint32 Vrab04 = L_Numbering(string(Strn01[Vrab02], 0, Vrab03 - 1));
        if(Vect69[Vrab04] == 0){File0002 << " id: " + Strn01[Vrab02] + "\n";} else {Vect69[Vrab01] -= 1;}
       }
       if(Config.MAIN_MOD)
       if(Config.MOD_ModulingLevel > 0)
       {
        File0002 << " id: " << Database.InjectorID << " type: 0 file: " + Temp03 + "\n id: " << Database.InjectorID2 << " type: 3 file: " + Temp04 + "\n";
       }
       File0002 << "<object_end>\n\n";
       break;
      }
     }
     continue;
    }
    if(Temp01 == "<file_editing>")
    {
     File0002 << "<file_editing>\n ";
     while(File0001)
     {
      File0001 >> Temp01; if(!File0001) break; if(Temp01.at(0) == '#'){std::getline(File0001, Temp01); continue;}
      if(Temp01 == "<file_editing_end>"){File0002 << "\n<file_editing_end>\n\n"; break;}
      File0002 << Temp01 + " ";
     }
     continue;
    }
    if(Temp01 == "<background>")
    {
     File0002 << "<background>\n";
     while(File0001)
     {
      File0001 >> Temp01; if(!File0001) break; if(Temp01.at(0) == '#'){std::getline(File0001, Temp01); continue;}
      if(Temp01 == "id:"){File0001 >> Temp01; continue;}
      if(Temp01 == "file:"){File0001 >> Temp01; continue;}
      if(Temp01 == "<background_end>")
      {
       const uint32 Vrab01 = Strn02.size();
       for(uint32 Vrab02 = 0; Vrab02 < Vrab01; ++Vrab02)
       {
        File0002 << " id: " << Vrab02 << " file: " + Strn02[Vrab02] + "\n";
       }
       File0002 << "<background_end>\n\n";
       break;
      }
     }
     continue;
    }
   }

   L_Cleaning();
  }
  int0   C_DLL_Load()                                                 {Hins0001.clear(); if(L_Exist(Config.DLL_Directory)) for(auto const &Vrab01 : std::filesystem::recursive_directory_iterator(Config.DLL_Directory)){string Temp01 = Vrab01.path().string(); if(L_Lowercase(string(Temp01, Temp01.size() - 4, 4)) == ".dll") Hins0001.push_back(LoadLibraryA(Temp01.c_str()));}}
  int0   C_DLL_Unload()                                               {const uint32 Vrab01 = Hins0001.size(); uint32 Vrab02 = 0; while(Vrab02 < Vrab01){FreeLibrary(Hins0001.at(Vrab02)); Vrab02 += 1;} Hins0001.clear();}
  /*int0   C_MOD_Initialization()                              fastened {
    if(!Config.MAIN_MOD) return;
    if(Config.MOD_ModulingLevel != 1) return;
	int1 Vrab01 = false; uint32 Vrab02 = 0;
    while(Base.Game->Database->Data[Vrab02] != 0)
    {
     if(Base.Game->Database->Data[Vrab02]->id == Database.InjectorID) goto Labl0012;
     if(Base.Game->Database->Data[Vrab02]->type == 0)
     {
      uint32 Vrab03 = 0;
      while(Base.Game->Database->Data[Vrab02]->Frame[Vrab03].Exist){Vrab03 += 1; if(Vrab03 == MaximumFrames){Vrab01 = true; goto Labl0012;}}
      if(Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].Exist)
      {
       if(Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wait <= 0){Vrab01 = true; goto Labl0012;}
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].Exist = true;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wait = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wait - 1;
       Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wait = 0;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].next = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].next;
       Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].next = Vrab03;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].centerx = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].centerx;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].centery = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].centery;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].opoint.kind = 1;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].opoint.x = Base.Game->Database->Data[Vrab02]->Frame[Vrab03].centerx;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].opoint.y = Base.Game->Database->Data[Vrab02]->Frame[Vrab03].centery;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].opoint.oid = Database.InjectorID;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].opoint.action = 0;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].opoint.facing = 10;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].pic = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].pic;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].state = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].state;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].mp = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].mp;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_a = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_a;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_d = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_d;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_j = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_j;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_Fa = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_Fa;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_Fj = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_Fj;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_Da = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_Da;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_Dj = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_Dj;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_Ua = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_Ua;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_Uj = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_Uj;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_ja = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_ja;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].bdy_Count = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].bdy_Count;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].bdy = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].bdy;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].bdy_Rectangle = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].bdy_Rectangle;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].itr_Count = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].itr_Count;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].itr = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].itr;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].itr_Rectangle = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].itr_Rectangle;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.kind = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.kind;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.x = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.x;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.y = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.y;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.dvx = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.dvx;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.dvy = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.dvy;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.dvz = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.dvz;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.weaponact = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.weaponact;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.attacking = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.attacking;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.cover = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.cover;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.kind = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.kind;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.x = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.x;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.y = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.y;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.vaction = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.vaction;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.aaction = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.aaction;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.daction = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.daction;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.jaction = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.jaction;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.taction = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.taction;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.dircontrol = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.dircontrol;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.decrease = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.decrease;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.throwvx = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.throwvx;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.throwvy = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.throwvy;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.throwvz = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.throwvz;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.throwinjury = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.throwinjury;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.cover_backhurtact = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.cover_backhurtact;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.hurtable = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.hurtable;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.injury_fronthurtact = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.injury_fronthurtact;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].bpoint.x = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].bpoint.x;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].bpoint.y = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].bpoint.y;
      } else {Vrab01 = true;}
     }
     Labl0012:
	 Vrab02 += 1;
    }
    if(Vrab01)
	{
	  
	}
   }
  int0 C_MOD_Preprocessing()
   {
    if(!Config.MAIN_MOD) return;
    if(Config.MOD_ModulingInfo && Config.MOD_ModulingLevel == 0)
    {
     for(uint32 Vrab01 = 0; Vrab01 < MaximumObject; ++Vrab01) if(Base.Game->Object[Vrab01]->Data->id == Database.InjectorID2)
     {
      switch(Base.Game->Object[Vrab01]->Frame)
      {
       case 0:
        Vrab0001 = 20;
        if(Base.Game->Object[Vrab01]->Wait > 1)
        if(Base.Game->Object[Vrab01]->Wait < 22)
        {
         Vrab0001 = 20 - (Base.Game->Object[Vrab01]->Wait - 2);
        } else 
        {
         Vrab0001 = 0;
         if(Base.Game->Object[Vrab01]->Wait > 97) Vrab0001 = Base.Game->Object[Vrab01]->Wait - 97;
        }
        Vrab0003 = 20;
        if(Base.Game->Object[Vrab01]->Wait > 13) Vrab0003 = 20 - (Base.Game->Object[Vrab01]->Wait - 13);
        if(Base.Game->Object[Vrab01]->Wait > 33) Vrab0003 = 0;
        Base.Game->Object[Vrab01]->Data->Frame[0].centerx = (Vrab0001 * (Vrab0001 + ((Vrab0001 - 1) / -2))) - *(int*)0x450bc4;
        Base.Game->Object[Vrab01]->Data->Frame[0].centery = Base.Game->Database->Background[*(int*)0x44d024].zboundary[1] - Config.MOD_ModulingInfoPostition - (210 - ((int32)Vrab0003 * ((int32)Vrab0003 + (((int32)Vrab0003 - 1) / -2)))) / 5;
       break;
       case 1:
        if(Base.Game->Object[Vrab01]->Data->Frame[0].pic == -1)
        {
         Vrab0001 = 20;
         if(Base.Game->Object[Vrab01]->Wait > 0)
         if(Base.Game->Object[Vrab01]->Wait < 21)
         {
          Vrab0001 = 20 - (Base.Game->Object[Vrab01]->Wait - 1);
         } else 
         {
          Vrab0001 = 0;
          if(Base.Game->Object[Vrab01]->Wait > 96) Vrab0001 = Base.Game->Object[Vrab01]->Wait - 96;
         }
         Base.Game->Object[Vrab01]->Data->Frame[1].centerx = (Vrab0001 * (Vrab0001 + ((Vrab0001 - 1) / -2))) - *(int*)0x450bc4;
         Base.Game->Object[Vrab01]->Data->Frame[1].centery = Base.Game->Database->Background[*(int*)0x44d024].zboundary[1] - Config.MOD_ModulingInfoPostition;
        } else
        {
         Vrab0001 = 20;
         if(Base.Game->Object[Vrab01]->Wait > 20)
         if(Base.Game->Object[Vrab01]->Wait < 41)
         {
          Vrab0001 = 20 - (Base.Game->Object[Vrab01]->Wait - 21);
         } else 
         {
          Vrab0001 = 0;
          if(Base.Game->Object[Vrab01]->Wait > 116) Vrab0001 = Base.Game->Object[Vrab01]->Wait - 116;
         }
         Base.Game->Object[Vrab01]->Data->Frame[1].centerx = (Vrab0001 * (Vrab0001 + ((Vrab0001 - 1) / -2))) - *(int*)0x450bc4;
         Base.Game->Object[Vrab01]->Data->Frame[1].centery = Base.Game->Database->Background[*(int*)0x44d024].zboundary[1] - Config.MOD_ModulingInfoPostition;
        }
       break;
       default: break;
      }
     }
    }
   }
   int0   C_MOD_Ending()                                           {
   {
    if(Database.InjectorNUM == -1) return;
    const uint32 Vrab02 = Strn0001.size();
    if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
    for(uint32 Vrab01 = 0; Vrab01 < Vrab02; ++Vrab01)
    {
     if(Strn0001[Vrab01] == "") continue;
     Base.ModuleID = Vect0001[Vrab01];
     const string Temp01 = "Mod_" + std::to_string(Vrab01);
     asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void last()");
     if(Func01)
     {
      if(Base.Cont0002->Prepare(Func01) < 0)
	  {
	   #ifdef DEBUG_VERSION
	    #ifdef MULTI_STATE
         if(Config.AI_Console)
         {
        #endif
	    Base.Engi0002->WriteMessage(Strn0001[Vrab01].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	   #endif
	   #ifdef MULTI_STATE
        }
       #endif
	   continue;
	  }
	  if(Base.Cont0002->Execute() < 0)
	  {
	   #ifdef DEBUG_VERSION
	    #ifdef MULTI_STATE
         if(Config.AI_Console)
         {
        #endif
	    Base.Engi0002->WriteMessage(Strn0001[Vrab01].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	   #endif
	   #ifdef MULTI_STATE
        }
       #endif
	   continue;
      }
     }
    }
    if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
   }
   C_MOD_Preprocessing();
  }
  int0   C_MOD_Processing()                                           {
   {
    if(Database.InjectorNUM == -1) return;
    const uint32 Vrab02 = Strn0001.size();
    if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
    for(uint32 Vrab01 = 0; Vrab01 < Vrab02; ++Vrab01)
    {
     if(Strn0001[Vrab01] == "") continue;
     Base.ModuleID = Vect0001[Vrab01];
     const string Temp01 = "Mod_" + std::to_string(Vrab01);
     asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void mids()");
     if(Func01)
     {
      if(Base.Cont0002->Prepare(Func01) < 0)
	  {
	   #ifdef DEBUG_VERSION
	    #ifdef MULTI_STATE
         if(Config.AI_Console)
         {
        #endif
	    Base.Engi0002->WriteMessage(Strn0001[Vrab01].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	   #endif
	   #ifdef MULTI_STATE
        }
       #endif
	   continue;
	  }
	  if(Base.Cont0002->Execute() < 0)
	  {
	   #ifdef DEBUG_VERSION
	    #ifdef MULTI_STATE
         if(Config.AI_Console)
         {
        #endif
	    Base.Engi0002->WriteMessage(Strn0001[Vrab01].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	   #endif
	   #ifdef MULTI_STATE
        }
       #endif
	   continue;
      }
     }
    }
    if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
   }
  }
  int0   C_MOD_Deprocessing()                                           {
   {
    const uint32 Vrab02 = Strn0001.size();
    if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
    for(uint32 Vrab01 = 0; Vrab01 < Vrab02; ++Vrab01)
    {
     if(Strn0001[Vrab01] == "") continue;
     Base.ModuleID = Vect0001[Vrab01];
     const string Temp01 = "Mod_" + std::to_string(Vrab01);
     asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void fins()");
     if(Func01)
     {
      if(Base.Cont0002->Prepare(Func01) < 0)
	  {
	   #ifdef DEBUG_VERSION
	    #ifdef MULTI_STATE
         if(Config.AI_Console)
         {
        #endif
	    Base.Engi0002->WriteMessage(Strn0001[Vrab01].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	   #endif
	   #ifdef MULTI_STATE
        }
       #endif
	   continue;
	  }
	  if(Base.Cont0002->Execute() < 0)
	  {
	   #ifdef DEBUG_VERSION
	    #ifdef MULTI_STATE
         if(Config.AI_Console)
         {
        #endif
	    Base.Engi0002->WriteMessage(Strn0001[Vrab01].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	   #endif
	   #ifdef MULTI_STATE
        }
       #endif
	   continue;
      }
     }
    }
    if(Config.MOD_ModulingLevel > 0)if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
   }
  }
  int0   C_MOD_Process()                                              {
   const uint32 Vrab01 = Strn0001.size();
   if(Database.Init)
   {
    C_MOD_Initialization();
    if(Database.InjectorNUM == -1) return;
	Database.Init = false;
    {
     if(Config.MOD_ModulingLevel > 0){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
     for(uint32 Vrab02 = 0; Vrab02 < Vrab01; ++Vrab02)
     {
      if(Strn0001[Vrab02] == "") continue;
      Base.ModuleID = Vect0001[Vrab02];
      const string Temp01 = "Mod_" + std::to_string(Vrab02);
      asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void once()"); int1 Vrab03 = true;
      if(!Func01){Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void init()"); Vrab03 = false;}
      if(Func01)
      {
       if(Base.Cont0002->Prepare(Func01) < 0)
	   {
	    #ifdef DEBUG_VERSION
	     #ifdef MULTI_STATE
          if(Config.AI_Console)
          {
         #endif
	     Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	    #endif
	    #ifdef MULTI_STATE
         }
        #endif
        if(Vrab03) Strn0001[Vrab02] = "";
	    continue;
	   }
	   if(Base.Cont0002->Execute() < 0)
	   {
	    #ifdef DEBUG_VERSION
	     #ifdef MULTI_STATE
          if(Config.AI_Console)
          {
         #endif
	     Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	    #endif
	    #ifdef MULTI_STATE
         }
        #endif
        if(Vrab03) Strn0001[Vrab02] = "";
	    continue;
       }
      }
     }
     if(Config.MOD_ModulingLevel > 0){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
    }
   }
   if(Database.InjectorNUM == -1) return;
   {
    if(Config.MOD_ModulingLevel > 0){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
    for(uint32 Vrab02 = 0; Vrab02 < Vrab01; ++Vrab02)
    {
     if(Strn0001[Vrab02] == "") continue;
     Base.ModuleID = Vect0001[Vrab02];
     const string Temp01 = "Mod_" + std::to_string(Vrab02);
     #ifdef DEBUG_VERSION
	  #ifdef MULTI_STATE
       if(Config.AI_Console)
       {
      #endif
      if(L_Rebuilding(Vrab02, "_" + Strn0001[Vrab02]))
      {
       asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void init()");
       if(Func01)
       {
        if(Base.Cont0002->Prepare(Func01) < 0)
	    {
	     #ifdef DEBUG_VERSION
	      #ifdef MULTI_STATE
           if(Config.AI_Console)
           {
          #endif
	      Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	     #endif
	     #ifdef MULTI_STATE
          }
         #endif
	     continue;
	    }
	    if(Base.Cont0002->Execute() < 0)
	    {
	     #ifdef DEBUG_VERSION
	      #ifdef MULTI_STATE
           if(Config.AI_Console)
           {
          #endif
	      Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	     #endif
	     #ifdef MULTI_STATE
          }
         #endif
	     continue;
        }
       }
      }
     #endif
     #ifdef MULTI_STATE
      }
     #endif
     asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void main()");
     if(Func01)
     {
      if(Base.Cont0002->Prepare(Func01) < 0)
	  {
	   #ifdef DEBUG_VERSION
	    #ifdef MULTI_STATE
         if(Config.AI_Console)
         {
        #endif
	    Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	   #endif
	   #ifdef MULTI_STATE
        }
       #endif
	   continue;
	  }
	  if(Base.Cont0002->Execute() < 0)
	  {
	   #ifdef DEBUG_VERSION
	    #ifdef MULTI_STATE
         if(Config.AI_Console)
         {
        #endif
	    Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	   #endif 
	   #ifdef MULTI_STATE
        }
       #endif
 	   continue;
      }
     }
    }
    if(Config.MOD_ModulingLevel > 0){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
   }
   C_MOD_Processing();
   C_MOD_Ending();
  }
  int0   C_MOD_Reset()                                       
  {
   Base.ElapsedTime = *(int32*)0x450b8c;
   if(Config.MOD_ModulingLevel == 0)
   {
    if(ruint32(Database.InjectorFRAME) < Base.ElapsedTime){Database.InjectorFRAME = Base.ElapsedTime; return;}
    Database.InjectorFRAME = Base.ElapsedTime;
   }
   {
    uint32 Vrab01 = 0;
    if(Config.MOD_ModulingLevel > 0){while(Base.Game->Database->Data[Vrab01] != 0){if(Base.Game->Database->Data[Vrab01]->id == Database.InjectorID2){Base.Game->Database->Data[Vrab01]->Frame[0].centerx = 1000; Base.Game->Database->Data[Vrab01]->Frame[1].centerx = 1000; Base.Game->Database->Data[Vrab01]->Frame[0].centery = -1000; Base.Game->Database->Data[Vrab01]->Frame[1].centery = -1000; break;} Vrab01 += 1;}}
   }
    {
     const uint32 Vrab02 = Strn0001.size();
     if(Vrab02 != 0)
     {
      Base.Difficulty = *(int32*)0x450c30; Base.Mode = *(int32*)0x451160;
      if(Base.BackgroundID != *(int32*)0x44d024)
      {
       Base.BackgroundID = *(int32*)0x44d024;
       Base.Background_width = Base.Game->Database->Background[Base.BackgroundID].width;
       Base.Background_zwidth1 = Base.Game->Database->Background[Base.BackgroundID].zboundary[0];
       Base.Background_zwidth2 = Base.Game->Database->Background[Base.BackgroundID].zboundary[1];
       Base.Stage_bound = Base.Background_width;
       Base.Stage_clear = false;
      }
      if(Base.Mode == 1)
      {
       Base.Stage_bound = *(int32*)0x450bb4;
       Base.Stage_clear = Base.Stage_bound == 0;
      }
      Base.Phase = *(int32*)0x44fb6c;
      Base.Phase_Count = *(int32*)0x44f880;
      Base.Stage = *(int32*)0x450b94;
     }
     if(Config.MOD_ModulingLevel > 0){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
     for(uint32 Vrab01 = 0; Vrab01 < Vrab02; ++Vrab01)
     {
      if(Strn0001[Vrab01] == "") continue;
      Base.ModuleID = Vect0001[Vrab01];
      const string Temp01 = "Mod_" + std::to_string(Vrab01);
      asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void play()");
      if(Func01)
      {
       if(Base.Cont0002->Prepare(Func01) < 0)
	   {
	    #ifdef DEBUG_VERSION
	     #ifdef MULTI_STATE
          if(Config.AI_Console)
          {
         #endif
	     Base.Engi0002->WriteMessage(Strn0001[Vrab01].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	    #endif
	    #ifdef MULTI_STATE
         }
        #endif
	    continue;
	   }
	   if(Base.Cont0002->Execute() < 0)
	   {
	    #ifdef DEBUG_VERSION
	     #ifdef MULTI_STATE
          if(Config.AI_Console)
          {
         #endif
	     Base.Engi0002->WriteMessage(Strn0001[Vrab01].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	    #endif
	    #ifdef MULTI_STATE
         }
        #endif
	    continue;
       }
      }
     }
     if(Config.MOD_ModulingLevel > 0){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
    }
  }*/
  int0   C_MOD_Redeclaration()                               fastened
  {
   Database.NumberOfExist = 0; Database.NumberOfExistT0 = 0; Database.NumberOfExistT0COM = 0;
   int1 Vrab03 = false; if(Database.InjectorNUM != -1) if(Base.Game->Object_Exist[Database.InjectorNUM]){if(Base.Game->Object[Database.InjectorNUM]->Data->id == Database.InjectorID){if(Base.Game->Object[Database.InjectorNUM]->Frame < 235) Vrab03 = true;} else {Vrab03 = true;}} else {Vrab03 = true;}
   for(uint32 Vrab01 = 0; Vrab01 < MaximumObject; ++Vrab01) if(Base.Game->Object_Exist[Vrab01]) if(Base.Game->Object[Vrab01]->Frame != 9998 && Base.Game->Object[Vrab01]->Data->Frame[Base.Game->Object[Vrab01]->Frame].state != 9998)
   switch(Base.Game->Object[Vrab01]->Data->type)
   {
    case 0:
     if(Config.MOD_ModulingLevel > 0)
     {
      if(Base.Game->Object[Vrab01]->Data->id != Database.InjectorID)
      {
       Database.Exist[Database.NumberOfExist] = Vrab01; Database.NumberOfExist += 1;
       Database.ExistT0[Database.NumberOfExistT0] = Vrab01; Database.NumberOfExistT0 += 1;
       if(Vrab01 >= 10){Database.ExistT0COM[Database.NumberOfExistT0COM] = Vrab01; Database.NumberOfExistT0COM += 1;}
      } else
      {
       Base.Game->Object[Vrab01]->Health = 0; Base.Game->Object[Vrab01]->Mana = 0; Base.Game->Object[Vrab01]->Max_Health = 0; Base.Game->Object[Vrab01]->Invisibility = -199;
       if(Vrab01 < 10){Base.Game->Object[Vrab01]->Frame = 240; continue;}
       if(!Database.InGame && (Database.InjectorNUM == -1 || Vrab03))
       {
        Database.InjectorNUM = Vrab01; Base.Game->Object[Vrab01]->Team = 2147483647; Base.Game->Object[Vrab01]->Frame = 237; Database.InjectorFRAME = 237;
        Database.InGame = true; Database.OutGame = true; Database.Reset = true;
        if(Database.Done){uint32 Vrab02 = 0; while(Base.Game->Database->Data[Vrab02] != 0){if(Base.Game->Database->Data[Vrab02]->id == Database.InjectorID2){Base.Game->Database->Data[Vrab02]->Frame[0].pic = -1; break;} Vrab02 += 1;}} else
        {Database.Done = true;}
       } else
       {
        const uint32 Vrab02 = Database.InjectorNUM; 
        if(Vrab01 == Vrab02){if(Database.InjectorFRAME == Base.Game->Object[Vrab01]->Frame){Database.InGame = false;} else {Database.InGame = true;} if(Database.InjectorFRAME == 237) Database.InGame = true; Database.InjectorFRAME = Base.Game->Object[Vrab01]->Frame;} else
        {Base.Game->Object[Vrab01]->Frame = 240;}
       }
       Database.ExistT0COM[Database.NumberOfExistT0COM] = Vrab01; Database.NumberOfExistT0COM += 1;
      }
     } else
     {
      Database.Exist[Database.NumberOfExist] = Vrab01; Database.NumberOfExist += 1;
      Database.ExistT0[Database.NumberOfExistT0] = Vrab01; Database.NumberOfExistT0 += 1;
      if(Vrab01 >= 10){Database.ExistT0COM[Database.NumberOfExistT0COM] = Vrab01; Database.NumberOfExistT0COM += 1;}
     }
    break;
    default:
     if(Config.MOD_ModulingLevel > 0){if(Base.Game->Object[Vrab01]->Data->id != Database.InjectorID2){Database.Exist[Database.NumberOfExist] = Vrab01; Database.NumberOfExist += 1;}} else
     {Database.Exist[Database.NumberOfExist] = Vrab01; Database.NumberOfExist += 1;}
    break;
   }
  }
  int0 C_MOD_Reset() fastened
  {
   if(Config.MOD_ModulingLevel == 0)
   {
    if(Database.InjectorFRAME < *(int32*)0x450b8c){Database.InjectorFRAME = *(int32*)0x450b8c; return;}
    Database.InjectorFRAME = *(int32*)0x450b8c;
   }
   {
    uint32 Vrab01 = 0;
    if(Config.MOD_ModulingLevel > 0){while(Base.Game->Database->Data[Vrab01] != 0){if(Base.Game->Database->Data[Vrab01]->id == Database.InjectorID2){Base.Game->Database->Data[Vrab01]->Frame[0].centerx = 1000; Base.Game->Database->Data[Vrab01]->Frame[1].centerx = 1000; Base.Game->Database->Data[Vrab01]->Frame[0].centery = -1000; Base.Game->Database->Data[Vrab01]->Frame[1].centery = -1000; break;} Vrab01 += 1;}}
   }
   {
    const uint32 Vrab01 = Strn0001.size();
    if(Config.MOD_ModulingLevel > 0){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
    for(uint32 Vrab02 = 0; Vrab02 < Vrab01; ++Vrab02)
    {
     if(Strn0001[Vrab02] == "") continue;
     Base.ModuleID = Vect0001[Vrab02];
     const string Temp01 = "Mod_" + std::to_string(Vrab02);
     asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void play()");
     if(Func01)
     {
      if(Base.Cont0002->Prepare(Func01) < 0)
	  {
	   #ifdef DEBUG_VERSION
	    #ifdef MULTI_STATE
         if(Config.AI_Console)
         {
        #endif
	    Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	   #endif
	   #ifdef MULTI_STATE
        }
       #endif
	   continue;
	  }
	  if(Base.Cont0002->Execute() < 0)
	  {
	   #ifdef DEBUG_VERSION
	    #ifdef MULTI_STATE
         if(Config.AI_Console)
         {
        #endif
	    Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	   #endif
	   #ifdef MULTI_STATE
        }
       #endif
       continue;
      }
     }
    }
    if(Config.MOD_ModulingLevel > 0){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
   }
  }
  int0 C_MOD_Initialization() fastened 
  {
   if(!Database.Init) return;
   if(Config.MOD_ModulingLevel == 1)
   {
	int1 Vrab01 = false; uint32 Vrab02 = 0;
    while(Base.Game->Database->Data[Vrab02] != 0)
    {
     if(Base.Game->Database->Data[Vrab02]->id == Database.InjectorID) goto Labl01;
     if(Base.Game->Database->Data[Vrab02]->type == 0)
     {
      uint32 Vrab03 = 0;
      while(Base.Game->Database->Data[Vrab02]->Frame[Vrab03].Exist){Vrab03 += 1; if(Vrab03 == MaximumFrames){Vrab01 = true; goto Labl01;}}
      if(Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].Exist)
      {
       if(Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wait <= 0){Vrab01 = true; goto Labl01;}
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].Exist = true;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wait = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wait - 1;
       Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wait = 0;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].next = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].next;
       Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].next = Vrab03;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].centerx = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].centerx;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].centery = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].centery;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].opoint.kind = 1;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].opoint.x = Base.Game->Database->Data[Vrab02]->Frame[Vrab03].centerx;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].opoint.y = Base.Game->Database->Data[Vrab02]->Frame[Vrab03].centery;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].opoint.oid = Database.InjectorID;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].opoint.action = 0;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].opoint.facing = 10;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].pic = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].pic;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].state = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].state;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].mp = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].mp;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_a = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_a;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_d = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_d;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_j = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_j;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_Fa = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_Fa;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_Fj = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_Fj;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_Da = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_Da;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_Dj = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_Dj;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_Ua = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_Ua;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_Uj = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_Uj;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].hit_ja = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].hit_ja;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].bdy_Count = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].bdy_Count;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].bdy = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].bdy;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].bdy_Rectangle = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].bdy_Rectangle;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].itr_Count = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].itr_Count;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].itr = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].itr;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].itr_Rectangle = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].itr_Rectangle;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.kind = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.kind;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.x = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.x;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.y = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.y;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.dvx = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.dvx;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.dvy = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.dvy;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.dvz = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.dvz;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.weaponact = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.weaponact;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.attacking = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.attacking;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].wpoint.cover = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].wpoint.cover;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.kind = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.kind;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.x = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.x;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.y = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.y;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.vaction = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.vaction;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.aaction = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.aaction;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.daction = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.daction;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.jaction = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.jaction;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.taction = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.taction;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.dircontrol = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.dircontrol;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.decrease = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.decrease;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.throwvx = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.throwvx;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.throwvy = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.throwvy;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.throwvz = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.throwvz;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.throwinjury = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.throwinjury;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.cover_backhurtact = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.cover_backhurtact;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.hurtable = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.hurtable;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].cpoint.injury_fronthurtact = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].cpoint.injury_fronthurtact;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].bpoint.x = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].bpoint.x;
       Base.Game->Database->Data[Vrab02]->Frame[Vrab03].bpoint.y = Base.Game->Database->Data[Vrab02]->Frame[Config.MOD_ModulingLevelStartingFrame].bpoint.y;
      } else {Vrab01 = true;}
     }
     Labl01:
	 Vrab02 += 1;
    }
    if(Vrab01)
	{
	  
	}
   }
   if((Config.MOD_ModulingLevel > 0 && Database.InjectorNUM != -1) || Config.MOD_ModulingLevel == 0)
   {
    Database.Init = false;
    if(Config.MOD_ModulingLevel > 0){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
    const uint32 Vrab01 = Strn0001.size();
    for(uint32 Vrab02 = 0; Vrab02 < Vrab01; ++Vrab02)
    {
     if(Strn0001[Vrab02] == "") continue;
     Base.ModuleID = Vect0001[Vrab02];
     const string Temp01 = "Mod_" + std::to_string(Vrab02);
     asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void once()"); int1 Vrab03 = true;
     if(!Func01){Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void init()"); Vrab03 = false;}
     if(Func01)
     {
      if(Base.Cont0002->Prepare(Func01) < 0)
	  {
	   #ifdef DEBUG_VERSION
	    #ifdef MULTI_STATE
         if(Config.AI_Console)
         {
        #endif
	    Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	   #endif
	   #ifdef MULTI_STATE
        }
       #endif
       if(Vrab03) Strn0001[Vrab02] = "";
	   continue;
	  }
	  if(Base.Cont0002->Execute() < 0)
	  {
	   #ifdef DEBUG_VERSION
	    #ifdef MULTI_STATE
         if(Config.AI_Console)
         {
        #endif
	    Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	   #endif
	   #ifdef MULTI_STATE
        }
       #endif
       if(Vrab03) Strn0001[Vrab02] = "";
	   continue;
      }
     }
    }
    if(Config.MOD_ModulingLevel > 0){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
   }
  }
  int0 C_MOD_Processing() fastened
  {
   if(Database.InjectorNUM == -1) return;
   if(Config.MOD_ModulingLevel > 0){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
   const uint32 Vrab01 = Strn0001.size();
   for(uint32 Vrab02 = 0; Vrab02 < Vrab01; ++Vrab02)
   {
    if(Strn0001[Vrab02] == "") continue;
    Base.ModuleID = Vect0001[Vrab02];
    const string Temp01 = "Mod_" + std::to_string(Vrab02);
    #ifdef DEBUG_VERSION
	 #ifdef MULTI_STATE
      if(Config.AI_Console)
      {
     #endif
     if(L_Rebuilding(Vrab02, "_" + Strn0001[Vrab02]))
     {
      asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void init()");
      if(Func01)
      {
       if(Base.Cont0002->Prepare(Func01) < 0)
	   {
	    #ifdef DEBUG_VERSION
	     #ifdef MULTI_STATE
          if(Config.AI_Console)
          {
         #endif
	     Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	    #endif
	    #ifdef MULTI_STATE
         }
        #endif
	    continue;
	   }
	   if(Base.Cont0002->Execute() < 0)
	   {
	    #ifdef DEBUG_VERSION
	     #ifdef MULTI_STATE
          if(Config.AI_Console)
          {
         #endif
	     Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	    #endif
	    #ifdef MULTI_STATE
         }
        #endif
        continue;
       }
      }
     }
    #endif
    #ifdef MULTI_STATE
     }
    #endif
    asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void main()");
    if(Func01)
    {
     if(Base.Cont0002->Prepare(Func01) < 0)
	 {
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	  continue;
	 }
	 if(Base.Cont0002->Execute() < 0)
	 {
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	  #endif 
	  #ifdef MULTI_STATE
       }
      #endif
 	  continue;
     }
    }
   }
   if(Config.MOD_ModulingLevel > 0){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
  }
  int0 C_MOD_Preprocessing() fastened
  {
   if(!Config.MAIN_MOD) return;
   if(Database.InjectorNUM == -1 && Config.MOD_ModulingLevel > 0) return;
   const uint32 Vrab01 = Strn0001.size();
   if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
   for(uint32 Vrab02 = 0; Vrab02 < Vrab01; ++Vrab02)
   {
    if(Strn0001[Vrab02] == "") continue;
    Base.ModuleID = Vect0001[Vrab02];
    const string Temp01 = "Mod_" + std::to_string(Vrab02);
    asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void mids()");
    if(Func01)
    {
     if(Base.Cont0002->Prepare(Func01) < 0)
	 {
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	  continue;
	 }
	 if(Base.Cont0002->Execute() < 0)
	 {
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	  continue;
     }
    }
   }
   if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
  }
  int0 C_MOD_Inprocessing() fastened
  {
   if(!Config.MAIN_MOD) return;
   if(Database.InjectorNUM == -1 && Config.MOD_ModulingLevel > 0) return;
   const uint32 Vrab01 = Strn0001.size();
   if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
   for(uint32 Vrab02 = 0; Vrab02 < Vrab01; ++Vrab02)
   {
    if(Strn0001[Vrab02] == "") continue;
    Base.ModuleID = Vect0001[Vrab02];
    const string Temp01 = "Mod_" + std::to_string(Vrab02);
    asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void last()");
    if(Func01)
    {
     if(Base.Cont0002->Prepare(Func01) < 0)
	 {
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	  continue;
	 }
	 if(Base.Cont0002->Execute() < 0)
	 {
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	  continue;
     }
    }
   }
   if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
   if(Config.MOD_ModulingInfo && Config.MOD_ModulingLevel != 0)
   {
    for(uint32 Vrab02 = 0; Vrab02 < MaximumObject; ++Vrab02) if(Base.Game->Object[Vrab02]->Data->id == Database.InjectorID2)
    {
     switch(Base.Game->Object[Vrab02]->Frame)
     {
      case 0:
       Vrab0001 = 20;
       if(Base.Game->Object[Vrab02]->Wait > 1)
       if(Base.Game->Object[Vrab02]->Wait < 22)
       {
        Vrab0001 = 20 - (Base.Game->Object[Vrab02]->Wait - 2);
       } else 
       {
        Vrab0001 = 0;
        if(Base.Game->Object[Vrab02]->Wait > 97) Vrab0001 = Base.Game->Object[Vrab02]->Wait - 97;
       }
       Vrab0003 = 20;
       if(Base.Game->Object[Vrab02]->Wait > 13) Vrab0003 = 20 - (Base.Game->Object[Vrab02]->Wait - 13);
       if(Base.Game->Object[Vrab02]->Wait > 33) Vrab0003 = 0;
       Base.Game->Object[Vrab02]->Data->Frame[0].centerx = (Vrab0001 * (Vrab0001 + ((Vrab0001 - 1) / -2))) - *(int*)0x450bc4;
       Base.Game->Object[Vrab02]->Data->Frame[0].centery = Base.Game->Database->Background[*(int*)0x44d024].zboundary[1] - Config.MOD_ModulingInfoPostition - (210 - ((int32)Vrab0003 * ((int32)Vrab0003 + (((int32)Vrab0003 - 1) / -2)))) / 5;
      break;
      case 1:
       if(Base.Game->Object[Vrab02]->Data->Frame[0].pic == -1)
       {
        Vrab0001 = 20;
        if(Base.Game->Object[Vrab02]->Wait > 0)
        if(Base.Game->Object[Vrab02]->Wait < 21)
        {
         Vrab0001 = 20 - (Base.Game->Object[Vrab02]->Wait - 1);
        } else 
        {
         Vrab0001 = 0;
         if(Base.Game->Object[Vrab02]->Wait > 96) Vrab0001 = Base.Game->Object[Vrab02]->Wait - 96;
        }
        Base.Game->Object[Vrab02]->Data->Frame[1].centerx = (Vrab0001 * (Vrab0001 + ((Vrab0001 - 1) / -2))) - *(int*)0x450bc4;
        Base.Game->Object[Vrab02]->Data->Frame[1].centery = Base.Game->Database->Background[*(int*)0x44d024].zboundary[1] - Config.MOD_ModulingInfoPostition;
       } else
       {
        Vrab0001 = 20;
        if(Base.Game->Object[Vrab02]->Wait > 20)
        if(Base.Game->Object[Vrab02]->Wait < 41)
        {
         Vrab0001 = 20 - (Base.Game->Object[Vrab02]->Wait - 21);
        } else 
        {
         Vrab0001 = 0;
         if(Base.Game->Object[Vrab02]->Wait > 116) Vrab0001 = Base.Game->Object[Vrab02]->Wait - 116;
        }
        Base.Game->Object[Vrab02]->Data->Frame[1].centerx = (Vrab0001 * (Vrab0001 + ((Vrab0001 - 1) / -2))) - *(int*)0x450bc4;
        Base.Game->Object[Vrab02]->Data->Frame[1].centery = Base.Game->Database->Background[*(int*)0x44d024].zboundary[1] - Config.MOD_ModulingInfoPostition;
       }
      break;
      default: break;
     }
    }
   }
  }
  int0 C_MOD_Deprocessing() fastened
  {
   if(!Config.MAIN_MOD) return;
   if(Database.InjectorNUM == -1 && Config.MOD_ModulingLevel > 0) return;
   const uint32 Vrab01 = Strn0001.size();
   if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
   for(uint32 Vrab02 = 0; Vrab02 < Vrab01; ++Vrab02)
   {
    if(Strn0001[Vrab02] == "") continue;
    Base.ModuleID = Vect0001[Vrab02];
    const string Temp01 = "Mod_" + std::to_string(Vrab02);
    asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void fins()");
    if(Func01)
    {
     if(Base.Cont0002->Prepare(Func01) < 0)
	 {
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	  continue;
	 }
	 if(Base.Cont0002->Execute() < 0)
	 {
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   Base.Engi0002->WriteMessage(Strn0001[Vrab02].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	  continue;
     }
    }
   }
   if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
  }
 //-//
 // Core Functions
  int0   G_Process(const int32 Vrab01) fastened
  {
   Base.User = -1;
   if(!Config.MAIN_MOD) return;
   if(Database.First){C_MOD_Redeclaration(); if(Config.MOD_ModulingLevel == 0) Database.Reset = true; Database.First = false;}
   if(ruint32(Vrab01) == Database.ExistT0COM[Database.NumberOfExistT0COM - 1])
   {
    if(Database.InGame || (!Database.Done && !Database.InGame))
    {
     if(Database.Reset){C_MOD_Reset(); Database.Reset = false;}
     C_MOD_Initialization();
     C_MOD_Processing();
     C_MOD_Preprocessing();
     C_MOD_Inprocessing();
    } else {if(Database.OutGame){C_MOD_Deprocessing(); Database.OutGame = false;}}
    Database.First = true;
   }
  }
  int0   G_Initialization()
  {
   C_MAIN_Configuration();
   Console.Starting();
   if(Config.MAIN_ECD) C_ECD_Construction();
   C_ECD_Installation();
   Console.Ending();
   if(Config.MAIN_DLL) C_DLL_Load();
  }
  int0   G_Hiding()                       {if(Config.MAIN_DLL && Config.DLL_Progressive) C_DLL_Unload(); if(Database.Config == "") return; strcpy(&Config.ECD_ResultEncryption[0], BASE_ENCRYPTION); if(L_Create(L_Execute(TEMPORAL_FILE))){File0002 << "Do not erase this file.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" + S_DecryptionSTRING(Database.Config) + BASE_ENCRYPTION; File0002.close();} else {L_Create("safdasf.txt");}}
  int0   G_Cleaning()                     {L_Cleaning(); Console.Ending(); 
  if(!Config.ECD_InstallPermanent)
  {
   if(L_Open(Config.ECD_InstallODataDirectory))
   {
    if(L_Open(Config.ECD_InstallDataDirectory))
    {
     File0001.close(); std::remove(Config.ECD_InstallDataDirectory.c_str());
    }
    std::filesystem::copy_file(Config.ECD_InstallODataDirectory, Config.ECD_InstallDataDirectory); std::remove(Config.ECD_InstallODataDirectory.c_str());
   }
   if(L_Open(Config.ECD_ResultDirectory + "\\summary.edb"))
   {
    string Temp01; uint32 Vrab01 = 0;
    while(File0001)
    {
     File0001 >> Temp01; if(!File0001) break; 
     if(Temp01 == "B")
     {
      string Temp02; File0001 >> Temp01 >> Temp02; std::remove(Temp02.c_str()); std::filesystem::copy_file(Temp01, Temp02);
     }
     if(!L_Exist(Temp01)) continue;
     if(std::remove(Temp01.c_str()) != 0) continue;
     while(Temp01 != "")
     {
      Vrab01 = Temp01.size() - 1;
      while(Temp01.at(Vrab01) != '\\' && Temp01 != ""){Temp01.pop_back(); Vrab01 -= 1; if(Vrab01 == -1) break;}
      if(Temp01 != "")
      {
       if(Temp01.at(Vrab01) == '\\') Temp01.pop_back();
      } else {break;}
      if(L_Exist(Temp01))
      {
       if(std::distance(std::filesystem::directory_iterator{Temp01}, std::filesystem::directory_iterator{}) == 0)
       {std::filesystem::remove_all(Temp01.c_str());} else {break;}
      } else {break;}
     }
    } File0001.close(); std::remove(string(Config.ECD_ResultDirectory + "\\summary.edb").c_str());
   }
  } L_Cleaning();
  }
 //-//
 // AI Script Engine
  // Variables
   #ifdef _MD_OLD_SCRIPT
   class MD_AIINFO
   {
    public:
     int32 x; int32 y; int32 z;
     Vector3 position; xint64 x_real; xint64 y_real; xint64 z_real;
     int8 facing;
     int8 holding_up; int8 holding_down; int8 holding_left; int8 holding_right; int8 holding_a; int8 holding_j; int8 holding_d;
     int8 up; int8 down; int8 left; int8 right; int8 A; int8 J; int8 D;
     int8 DrA; int8 DlA; int8 DuA; int8 DdA; int8 DrJ; int8 DlJ; int8 DuJ; int8 DdJ; int8 DJA;
     int32 hp; int32 dark_hp; int32 max_hp; int32 mp;
     int32 frame;
     int32 bdefend;
     int32 fall;
     int32 team;
     int32 id;
     int32 blink;
     int32 state;
     int32 weapon_type; int32 weapon_held; int32 weapon_holder;
     int32 shake;
     int32 wait_counter;
     int32 num;
     int32 ctimer;
     int32 arest;
     int8 vrests[MaximumObject];
     int32 vrest;
     Vector3 velocity; xint64 x_velocity; xint64 y_velocity; xint64 z_velocity;
     int32 clone;
     int32 type;
     int32 reserve;
     sDataFile* data;
     MD_AIINFO()                       {num = -1; type = -1; RefCount = 1;}
     MD_AIINFO(const int32 Vrab01)     {MD_AIINFO(); operator=(Vrab01);}
     MD_AIINFO(const MD_AIINFO& Info01){MD_AIINFO(); operator=(Info01.num);}
     int0 AddRef(){RefCount++;}
     int0 RelRef(){if(--RefCount == 0) delete this;}

     int32 operator=(int32 Vrab01)
     {
      if(Vrab01 < 0 || Vrab01 >= MaximumObject) return -1;
      if(!Base.game->exists[Vrab01]) return -1; 
      x = Base.game->objects[Vrab01]->x;
      y = Base.game->objects[Vrab01]->y;
      z = Base.game->objects[Vrab01]->z;
      x_real = Base.game->objects[Vrab01]->x_real;
      y_real = Base.game->objects[Vrab01]->y_real;
      z_real = Base.game->objects[Vrab01]->z_real;
      position = Vector3(x_real, y_real, z_real);
      facing = Base.game->objects[Vrab01]->facing;
      holding_up = Base.game->objects[Vrab01]->holding_up;
      holding_down = Base.game->objects[Vrab01]->holding_down;
      holding_left = Base.game->objects[Vrab01]->holding_left;
      holding_right = Base.game->objects[Vrab01]->holding_right;
      holding_a = Base.game->objects[Vrab01]->holding_a;
      holding_j = Base.game->objects[Vrab01]->holding_j;
      holding_d = Base.game->objects[Vrab01]->holding_d;
      up = Base.game->objects[Vrab01]->up;
      down = Base.game->objects[Vrab01]->down;
      left = Base.game->objects[Vrab01]->left;
      right = Base.game->objects[Vrab01]->right;
      A = Base.game->objects[Vrab01]->A;
      J = Base.game->objects[Vrab01]->J;
      D = Base.game->objects[Vrab01]->D;
      DrA = Base.game->objects[Vrab01]->DrA;
      DlA = Base.game->objects[Vrab01]->DlA;
      DuA = Base.game->objects[Vrab01]->DuA;
      DdA = Base.game->objects[Vrab01]->DdA;
      DrJ = Base.game->objects[Vrab01]->DrJ;
      DlJ = Base.game->objects[Vrab01]->DlJ;
      DuJ = Base.game->objects[Vrab01]->DuJ;
      DdJ = Base.game->objects[Vrab01]->DdJ;
      DJA = Base.game->objects[Vrab01]->DJA;
      hp = Base.game->objects[Vrab01]->hp;
      dark_hp = Base.game->objects[Vrab01]->dark_hp;
      max_hp = Base.game->objects[Vrab01]->max_hp;
      mp = Base.game->objects[Vrab01]->mp;
      frame = Base.game->objects[Vrab01]->frame1;
      fall = Base.game->objects[Vrab01]->fall;
      bdefend = Base.game->objects[Vrab01]->bdefend;
      team = Base.game->objects[Vrab01]->team;
      id = Base.game->objects[Vrab01]->data->id;
      blink = Base.game->objects[Vrab01]->blink;
      state = Base.game->objects[Vrab01]->data->frames[frame].state;
      weapon_type = Base.game->objects[Vrab01]->weapon_type;
      if(weapon_type == 0){weapon_held = -1;} else {weapon_held = Base.game->objects[Vrab01]->weapon_held;}
      weapon_holder = Base.game->objects[Vrab01]->weapon_holder;
      shake = Base.game->objects[Vrab01]->shake;
      wait_counter = Base.game->objects[Vrab01]->wait_counter;
      num = Vrab01;
      ctimer = Base.game->objects[Vrab01]->ctimer;
      arest = Base.game->objects[Vrab01]->arest;
      memcpy(&vrests[0], &Base.game->objects[Vrab01]->vrests[0], MaximumObject);
      vrest = (int32)(*(int8*)(*(int32*)(0x458c94 + Vrab01 * 4) + 0xF0));
      if (vrest < (int32)(*(int8*)(*(int32*)(0x458c94 + Vrab01 * 4) + 0xF3))) vrest = (int32)(*(int8*)(*(int32*)(0x458c94 + Vrab01 * 4) + 0xF3));
      x_velocity = Base.game->objects[Vrab01]->x_velocity;
      y_velocity = Base.game->objects[Vrab01]->y_velocity;
      z_velocity = Base.game->objects[Vrab01]->z_velocity;
      velocity = Vector3(x_velocity, y_velocity, z_velocity);
      clone = Base.game->objects[Vrab01]->clone;
      type = Base.game->objects[Vrab01]->data->type;
      reserve = Base.game->objects[Vrab01]->reserve;
      data = Base.game->objects[Vrab01]->data;
      return type;
     }
     int32 operator= (const MD_AIINFO& Info01){return operator=(Info01.num);}
     int32 operator+=(const int32 Vrab01)     {return operator=(num + Vrab01);}
     int32 operator+=(const MD_AIINFO& Info01){return operator=(num + Info01.num);}
     int32 operator-=(const int32 Vrab01)     {return operator=(num - Vrab01);}
     int32 operator-=(const MD_AIINFO& Info01){return operator=(num - Info01.num);}
     int32 operator++()                       {return operator=(num + 1);}
     int32 operator--()                       {return operator=(num - 1);}
    private:
     uint32 RefCount;
   };
 
   MD_AIINFO *INFO_Create()                       {return new MD_AIINFO();}
   MD_AIINFO *INFO_Create(const int32 Vrab01)     {return new MD_AIINFO(Vrab01);}
   MD_AIINFO *INFO_Create(const MD_AIINFO& Info01){return new MD_AIINFO(Info01);}
   MD_AIINFO Info0001; // self
   MD_AIINFO Info0002; // target
   #endif

   typedef enum {INVALID, VALID, MODULE} MD_VALIDITY;
  //-//
  // Functions
   // Shared
   #ifdef _MD_OLD_SCRIPT
    //int0  L_Copying(uint32 Vrab01, uint32 Vrab02, uint32 Vrab03, uint32 Vrab04) fastened {Base.game->files->datas[Vrab02]->frames[Vrab04].exists = true; Base.game->files->datas[Vrab02]->frames[Vrab04].pic = Base.game->files->datas[Vrab01]->frames[Vrab03].pic; Base.game->files->datas[Vrab02]->frames[Vrab04].state = Base.game->files->datas[Vrab01]->frames[Vrab03].state; Base.game->files->datas[Vrab02]->frames[Vrab04].wait = Base.game->files->datas[Vrab01]->frames[Vrab03].wait; Base.game->files->datas[Vrab02]->frames[Vrab04].next = Base.game->files->datas[Vrab01]->frames[Vrab03].next; Base.game->files->datas[Vrab02]->frames[Vrab04].dvx = Base.game->files->datas[Vrab01]->frames[Vrab03].dvx; Base.game->files->datas[Vrab02]->frames[Vrab04].dvy = Base.game->files->datas[Vrab01]->frames[Vrab03].dvy; Base.game->files->datas[Vrab02]->frames[Vrab04].dvz = Base.game->files->datas[Vrab01]->frames[Vrab03].dvz; Base.game->files->datas[Vrab02]->frames[Vrab04].centerx = Base.game->files->datas[Vrab01]->frames[Vrab03].centerx; Base.game->files->datas[Vrab02]->frames[Vrab04].centery = Base.game->files->datas[Vrab01]->frames[Vrab03].centery; Base.game->files->datas[Vrab02]->frames[Vrab04].hit_a = Base.game->files->datas[Vrab01]->frames[Vrab03].hit_a; Base.game->files->datas[Vrab02]->frames[Vrab04].hit_d = Base.game->files->datas[Vrab01]->frames[Vrab03].hit_d; Base.game->files->datas[Vrab02]->frames[Vrab04].hit_j = Base.game->files->datas[Vrab01]->frames[Vrab03].hit_j; Base.game->files->datas[Vrab02]->frames[Vrab04].hit_Fa = Base.game->files->datas[Vrab01]->frames[Vrab03].hit_Fa; Base.game->files->datas[Vrab02]->frames[Vrab04].hit_Fj = Base.game->files->datas[Vrab01]->frames[Vrab03].hit_Fj; Base.game->files->datas[Vrab02]->frames[Vrab04].hit_Da = Base.game->files->datas[Vrab01]->frames[Vrab03].hit_Da; Base.game->files->datas[Vrab02]->frames[Vrab04].hit_Dj = Base.game->files->datas[Vrab01]->frames[Vrab03].hit_Dj; Base.game->files->datas[Vrab02]->frames[Vrab04].hit_Ua = Base.game->files->datas[Vrab01]->frames[Vrab03].hit_Ua; Base.game->files->datas[Vrab02]->frames[Vrab04].hit_Uj = Base.game->files->datas[Vrab01]->frames[Vrab03].hit_Uj; Base.game->files->datas[Vrab02]->frames[Vrab04].hit_ja = Base.game->files->datas[Vrab01]->frames[Vrab03].hit_ja; Base.game->files->datas[Vrab02]->frames[Vrab04].mp = Base.game->files->datas[Vrab01]->frames[Vrab03].mp; Base.game->files->datas[Vrab02]->frames[Vrab04].sound = Base.game->files->datas[Vrab01]->frames[Vrab03].sound; Base.game->files->datas[Vrab02]->frames[Vrab04].bpoint.x = Base.game->files->datas[Vrab01]->frames[Vrab03].bpoint.x; Base.game->files->datas[Vrab02]->frames[Vrab04].bpoint.y = Base.game->files->datas[Vrab01]->frames[Vrab03].bpoint.y; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.kind = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.kind; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.x = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.x; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.y = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.y; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.vaction = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.vaction; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.aaction = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.aaction; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.daction = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.daction; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.jaction = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.jaction; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.taction = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.taction; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.dircontrol = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.dircontrol; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.decrease = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.decrease; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.throwvx = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.throwvx; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.throwvy = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.throwvy; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.throwvz = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.throwvz; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.throwinjury = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.throwinjury; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.cover = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.cover; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.hurtable = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.hurtable; Base.game->files->datas[Vrab02]->frames[Vrab04].cpoint.injury = Base.game->files->datas[Vrab01]->frames[Vrab03].cpoint.injury; Base.game->files->datas[Vrab02]->frames[Vrab04].wpoint.kind = Base.game->files->datas[Vrab01]->frames[Vrab03].wpoint.kind; Base.game->files->datas[Vrab02]->frames[Vrab04].wpoint.x = Base.game->files->datas[Vrab01]->frames[Vrab03].wpoint.x; Base.game->files->datas[Vrab02]->frames[Vrab04].wpoint.y = Base.game->files->datas[Vrab01]->frames[Vrab03].wpoint.y; Base.game->files->datas[Vrab02]->frames[Vrab04].wpoint.dvx = Base.game->files->datas[Vrab01]->frames[Vrab03].wpoint.dvx; Base.game->files->datas[Vrab02]->frames[Vrab04].wpoint.dvy = Base.game->files->datas[Vrab01]->frames[Vrab03].wpoint.dvy; Base.game->files->datas[Vrab02]->frames[Vrab04].wpoint.dvz = Base.game->files->datas[Vrab01]->frames[Vrab03].wpoint.dvz; Base.game->files->datas[Vrab02]->frames[Vrab04].wpoint.weaponact = Base.game->files->datas[Vrab01]->frames[Vrab03].wpoint.weaponact; Base.game->files->datas[Vrab02]->frames[Vrab04].wpoint.attacking = Base.game->files->datas[Vrab01]->frames[Vrab03].wpoint.attacking; Base.game->files->datas[Vrab02]->frames[Vrab04].wpoint.cover = Base.game->files->datas[Vrab01]->frames[Vrab03].wpoint.cover; Base.game->files->datas[Vrab02]->frames[Vrab04].opoint.kind = Base.game->files->datas[Vrab01]->frames[Vrab03].opoint.kind; Base.game->files->datas[Vrab02]->frames[Vrab04].opoint.x = Base.game->files->datas[Vrab01]->frames[Vrab03].opoint.x; Base.game->files->datas[Vrab02]->frames[Vrab04].opoint.y = Base.game->files->datas[Vrab01]->frames[Vrab03].opoint.y; Base.game->files->datas[Vrab02]->frames[Vrab04].opoint.dvx = Base.game->files->datas[Vrab01]->frames[Vrab03].opoint.dvx; Base.game->files->datas[Vrab02]->frames[Vrab04].opoint.dvy = Base.game->files->datas[Vrab01]->frames[Vrab03].opoint.dvy; Base.game->files->datas[Vrab02]->frames[Vrab04].opoint.oid = Base.game->files->datas[Vrab01]->frames[Vrab03].opoint.oid; Base.game->files->datas[Vrab02]->frames[Vrab04].opoint.action = Base.game->files->datas[Vrab01]->frames[Vrab03].opoint.action; Base.game->files->datas[Vrab02]->frames[Vrab04].opoint.facing = Base.game->files->datas[Vrab01]->frames[Vrab03].opoint.facing; Base.game->files->datas[Vrab02]->frames[Vrab04].itr_count = Base.game->files->datas[Vrab01]->frames[Vrab03].itr_count; Base.game->files->datas[Vrab02]->frames[Vrab04].itrs = Base.game->files->datas[Vrab01]->frames[Vrab03].itrs; Base.game->files->datas[Vrab02]->frames[Vrab04].itr_x = Base.game->files->datas[Vrab01]->frames[Vrab03].itr_x; Base.game->files->datas[Vrab02]->frames[Vrab04].itr_y = Base.game->files->datas[Vrab01]->frames[Vrab03].itr_y; Base.game->files->datas[Vrab02]->frames[Vrab04].itr_w = Base.game->files->datas[Vrab01]->frames[Vrab03].itr_w; Base.game->files->datas[Vrab02]->frames[Vrab04].itr_h = Base.game->files->datas[Vrab01]->frames[Vrab03].itr_h; Base.game->files->datas[Vrab02]->frames[Vrab04].bdy_count = Base.game->files->datas[Vrab01]->frames[Vrab03].bdy_count; Base.game->files->datas[Vrab02]->frames[Vrab04].bdys = Base.game->files->datas[Vrab01]->frames[Vrab03].bdys; Base.game->files->datas[Vrab02]->frames[Vrab04].bdy_x = Base.game->files->datas[Vrab01]->frames[Vrab03].bdy_x; Base.game->files->datas[Vrab02]->frames[Vrab04].bdy_y = Base.game->files->datas[Vrab01]->frames[Vrab03].bdy_y; Base.game->files->datas[Vrab02]->frames[Vrab04].bdy_w = Base.game->files->datas[Vrab01]->frames[Vrab03].bdy_w; Base.game->files->datas[Vrab02]->frames[Vrab04].bdy_h = Base.game->files->datas[Vrab01]->frames[Vrab03].bdy_h;}
    uint32 L_Address(int32 Vrab01) fastened
    {
     return Base.L_Address(Vrab01);
    }
   // int32 L_NumSet(int32 Vrab01) fastened {return ((int32)(uint8)Base.game->objects[Vrab01]->data->unkwn2[144] + ((int32)(uint8)Base.game->objects[Vrab01]->data->unkwn2[145] << 8) + ((int32)(uint8)Base.game->objects[Vrab01]->data->unkwn2[146] << 16) + ((int32)(uint8)Base.game->objects[Vrab01]->data->unkwn2[147] << 24));}
    //int32 L_DataSet(int32 Vrab01) fastened {return ((int32)(uint8)Base.game->files->datas[Vrab01]->unkwn2[144] + ((int32)(uint8)Base.game->files->datas[Vrab01]->unkwn2[145] << 8) + ((int32)(uint8)Base.game->files->datas[Vrab01]->unkwn2[146] << 16) + ((int32)(uint8)Base.game->files->datas[Vrab01]->unkwn2[147] << 24));}
    int32 L_Random(int32 Vrab01) fastened//random function that works with replays
    {
     return Base.L_Random(Vrab01);
    }
    int32 L_Targetting(int32 Vrab01) fastened
    {
     return Info0002 = Vrab01;
    }
    int32 L_Aggring(int32 Vrab01) fastened
    {
     if(Vrab01 < 0 || Vrab01 >= MaximumObject) return -1;
     if(!Base.game->exists[Vrab01]) return -1;
     return Base.game->objects[Info0001.num]->enemy = Vrab01;
    }
    int0 L_InputUP(int8 Vrab01, int8 Vrab02) fastened
    {
     Base.game->objects[Info0001.num]->up = Vrab01;
     Base.game->objects[Info0001.num]->holding_up = Vrab02;
     Info0001.up = Vrab01; Info0001.holding_up = Vrab02;
    }
    int0 L_InputLEFT(int8 Vrab01, int8 Vrab02) fastened
    {
     Base.game->objects[Info0001.num]->left = Vrab01;
     Base.game->objects[Info0001.num]->holding_left = Vrab02;
     Info0001.left = Vrab01; Info0001.holding_left = Vrab02;
    }
    int0 L_InputDOWN(int8 Vrab01, int8 Vrab02) fastened
    {
     Base.game->objects[Info0001.num]->down = Vrab01;
     Base.game->objects[Info0001.num]->holding_down = Vrab02;
     Info0001.down = Vrab01; Info0001.holding_down = Vrab02;
    }
    int0 L_InputRIGHT(int8 Vrab01, int8 Vrab02) fastened
    {
     Base.game->objects[Info0001.num]->right = Vrab01;
     Base.game->objects[Info0001.num]->holding_right = Vrab02;
     Info0001.right = Vrab01; Info0001.holding_right = Vrab02;
    }
    int0 L_InputATTACK(int8 Vrab01,int8 Vrab02) fastened
    {
     Base.game->objects[Info0001.num]->A = Vrab01;
     Base.game->objects[Info0001.num]->holding_a = Vrab02;
     Info0001.A = Vrab01; Info0001.holding_a = Vrab02;
    }
    int0 L_InputJUMP(int8 Vrab01,int8 Vrab02) fastened
    {
     Base.game->objects[Info0001.num]->J = Vrab01;
     Base.game->objects[Info0001.num]->holding_j = Vrab02;
     Info0001.J = Vrab01; Info0001.holding_j = Vrab02;
    }
    int0 L_InputDEFEND(int8 Vrab01,int8 Vrab02) fastened
    {
     Base.game->objects[Info0001.num]->D = Vrab01;
     Base.game->objects[Info0001.num]->holding_d = Vrab02;
     Info0001.D = Vrab01; Info0001.holding_d = Vrab02;
    }
    int0 L_InputDrA() fastened {Base.game->objects[Info0001.num]->DrA = 3; Info0001.DrA = 3;}
    int0 L_InputDlA() fastened {Base.game->objects[Info0001.num]->DlA = 3; Info0001.DlA = 3;}
    int0 L_InputDuA() fastened {Base.game->objects[Info0001.num]->DuA = 3; Info0001.DuA = 3;}
    int0 L_InputDdA() fastened {Base.game->objects[Info0001.num]->DdA = 3; Info0001.DdA = 3;}
    int0 L_InputDrJ() fastened {Base.game->objects[Info0001.num]->DrJ = 3; Info0001.DrJ = 3;}
    int0 L_InputDlJ() fastened {Base.game->objects[Info0001.num]->DlJ = 3; Info0001.DlJ = 3;}
    int0 L_InputDuJ() fastened {Base.game->objects[Info0001.num]->DuJ = 3; Info0001.DuJ = 3;}
    int0 L_InputDdJ() fastened {Base.game->objects[Info0001.num]->DdJ = 3; Info0001.DdJ = 3;}
    int0 L_InputDJA() fastened {Base.game->objects[Info0001.num]->DJA = 3; Info0001.DJA = 3;}

    int0 C_Clear() fastened
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
    int0 C_PrintAddr(const int0 *Vrab01)    fastened {printf("%p", Vrab01);}
    int0 C_Print(const int1 Vrab01)         fastened {if(Vrab01){printf("true");} else {printf("false");}}
    int0 C_Print(const int8 Vrab01)         fastened {printf("%i", Vrab01);}
    int0 C_Print(const int16 Vrab01)        fastened {printf("%i", Vrab01);}
    int0 C_Print(const int32 Vrab01)        fastened {printf("%i", Vrab01);}
    int0 C_Print(const int64 Vrab01)        fastened {printf("%lli", Vrab01);}
    int0 C_Print(const uint8 Vrab01)        fastened {printf("%u", Vrab01);}
    int0 C_Print(const uint16 Vrab01)       fastened {printf("%u", Vrab01);}
    int0 C_Print(const uint32 Vrab01)       fastened {printf("%u", Vrab01);}
    int0 C_Print(const uint64 Vrab01)       fastened {printf("%llu", Vrab01);}
    int0 C_Print(const xint32 Vrab01)       fastened {printf("%f", Vrab01);}
    int0 C_Print(const xint64 Vrab01)       fastened {printf("%Lf", Vrab01);}
    int0 C_Print(const std::string &Temp01) fastened {printf("%s", Temp01.c_str());}
    #endif
   //-//
   // Private
    // Declaration
     string getFileName(int32);
     string getModuleName(const string&);
     MD_VALIDITY isValidFileName(string);
    //-//
    #ifdef DEBUG_VERSION
	 int1 hasFileTimeChanged(const int8 *Vrab01, FILETIME *Time01)
	 {
	  const HANDLE Hand01 = CreateFile(Vrab01, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
      FILETIME Time02;
      if(Hand01 == INVALID_HANDLE_VALUE){Time02.dwLowDateTime = 0; Time02.dwHighDateTime = 0;} else
	  {
	   if(!GetFileTime(Hand01, NULL, NULL, &Time02)){CloseHandle(Hand01); return false;}
	   CloseHandle(Hand01);
	  }
      if(CompareFileTime(&Time02, Time01) != 0){(*Time01) = Time02; return true;}
      return false;
	 }
	 int1 L_Rebuilding(int32 Vrab01, const string &Temp01)
	 {
      uint32 Vrab02 = Temp01.size();
      while(Vrab02 > 0){Vrab02 -= 1; if(Temp01.at(Vrab02) == '\\') break;} Vrab02 += 1;
      string Temp02 = string(Temp01, Vrab02, Temp01.size() - Vrab02);
      if(Temp02.at(0) != '_')
      {
       if(Moti0001.count(Vrab01))
       {
        if(hasFileTimeChanged(Temp01.c_str(), &(Moti0001[Vrab01])))
	    {
         CScriptBuilder Bild01;
         Bild01.DefineWord("debug"); Bild01.DefineWord("character");
         Base.Engi0001->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_INFORMATION, "Rebuilding.");
         Bild01.StartNewModule(Base.Engi0001, getModuleName(Temp01).c_str());
         if(Bild01.AddSectionFromFile(Temp01.c_str()) < 0)
         {
          Base.Engi0001->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to load file.");
          Base.Engi0001->DiscardModule(getModuleName(Temp01).c_str());
          return false;
         }
         if(Bild01.BuildModule() < 0)
         {
          Base.Engi0001->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to build module.");
          Base.Engi0001->DiscardModule(getModuleName(Temp01).c_str());
          return false;
         }
         return true;
        }
       } else
       {
        FILETIME Time01 = {0, 0};
        if(hasFileTimeChanged(Temp01.c_str(), &Time01))
        {
         Moti0001.insert(std::pair < int32, FILETIME > (Vrab01, Time01));
         CScriptBuilder Bild01;
         Bild01.DefineWord("debug"); Bild01.DefineWord("character");
         Base.Engi0001->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_INFORMATION, "Building.");
         Bild01.StartNewModule(Base.Engi0001, getModuleName(Temp01).c_str());
         if(Bild01.AddSectionFromFile(Temp01.c_str()) < 0)
         {
          Base.Engi0001->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to load file.");
          Base.Engi0001->DiscardModule(getModuleName(Temp01).c_str());
          return false;
         }
         if(Bild01.BuildModule() < 0)
         {
          Base.Engi0001->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to build module.");
          Base.Engi0001->DiscardModule(getModuleName(Temp01).c_str());
          return false;
         }
         return true;
        }
       }
      } else
      {
       const string Temp03 = string(Temp01, 1, Temp01.size() - 1);
       if(Moti0002.count(Vrab01))
       {
        if(hasFileTimeChanged(Temp03.c_str(), &(Moti0002[Vrab01])))
	    {
         CScriptBuilder Bild01;
         Bild01.DefineWord("debug"); Bild01.DefineWord("character");
         Base.Engi0002->WriteMessage(Temp03.c_str(), 0, 0, asMSGTYPE_INFORMATION, "Rebuilding.");
         Bild01.StartNewModule(Base.Engi0002, L_Moduling(Temp03).c_str());
         if(Bild01.AddSectionFromFile(Temp03.c_str()) < 0)
         {
          Base.Engi0002->WriteMessage(Temp03.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to load file.");
          Base.Engi0002->DiscardModule(getModuleName(Temp03).c_str());
          return false;
         }
         if(Bild01.BuildModule() < 0)
         {
          Base.Engi0002->WriteMessage(Temp03.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to build module.");
          Base.Engi0002->DiscardModule(getModuleName(Temp03).c_str());
          return false;
         }
         return true;
        }
       } else
       {
        FILETIME Time01 = {0, 0};
        if(hasFileTimeChanged(Temp03.c_str(), &Time01))
        {
         Moti0002.insert(std::pair < int32, FILETIME > (Vrab01, Time01));
         CScriptBuilder Bild01;
         Bild01.DefineWord("debug"); Bild01.DefineWord("character");
         Base.Engi0002->WriteMessage(Temp03.c_str(), 0, 0, asMSGTYPE_INFORMATION, "Building.");
         Bild01.StartNewModule(Base.Engi0002, L_Moduling(Temp03).c_str());
         if(Bild01.AddSectionFromFile(Temp03.c_str()) < 0)
         {
          Base.Engi0002->WriteMessage(Temp03.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to load file.");
          Base.Engi0002->DiscardModule(getModuleName(Temp03).c_str());
          return false;
         }
         if(Bild01.BuildModule() < 0)
         {
          Base.Engi0002->WriteMessage(Temp03.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to build module.");
          Base.Engi0002->DiscardModule(getModuleName(Temp03).c_str());
          return false;
         }
         return true;
        }
       }
      }
      return false;
     }
     int32 getIdFromFileName(const string &Temp01){int32 Vrab01; std::stringstream(getModuleName(Temp01)) >> Vrab01; return Vrab01;}
    #endif

    int0 Preparation(int32 Vrab01)
    {
     #ifdef _MD_OLD_SCRIPT
     {
      Base.ElapsedTime = *(int*)0x450b8c; Base.Difficulty = *(int*)0x450c30; Base.Mode = *(int*)0x451160;
      if(Base.BackgroundID != *(int*)0x44d024)
      {
       Base.BackgroundID = *(int*)0x44d024;
       Base.Background_width = Base.Game->Database->Background[Base.BackgroundID].width;
       Base.Background_zwidth1 = Base.Game->Database->Background[Base.BackgroundID].zboundary[0];
       Base.Background_zwidth2 = Base.Game->Database->Background[Base.BackgroundID].zboundary[1];
       Base.Stage_bound = Base.Background_width;
       Base.Stage_clear = false;
      }
      if(Base.Mode == 1)
      {
       Base.Stage_bound = *(int*)0x450bb4;
       Base.Stage_clear = Base.Stage_bound == 0;
      }
      Base.Phase = *(int*)0x44fb6c;
      Base.Phase_Count = *(int*)0x44f880;
      Base.Stage = *(int*)0x450b94;
     }
     #endif

     if(Vrab01 >= 0 && Vrab01 < MaximumObject) if(Base.Game->Object_Exist[ruint32(Base.User = Vrab01)]) return;
	 #ifdef DEBUG_VERSION
	  #ifdef MULTI_STATE
       if(Config.AI_Console)
       {
      #endif
	  Base.Engi0001->WriteMessage(getFileName(Base.Game->Object[Vrab01]->Data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare self.");
	 #endif
	 #ifdef MULTI_STATE
      }
     #endif
    }
    int32 callEgo(int32 Vrab01, int32 Vrab02, asIScriptFunction *Func01)
    {
     Preparation(Vrab01);
     if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
     int1 Vrab03 = (Vrab02 >= 0 && Vrab02 < MaximumObject);
     if(Vrab03){Vrab03 = !Base.Game->Object_Exist[Vrab02];} else {Vrab03 = true;}
     if(Vrab03)
	 {
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   Base.Engi0001->WriteMessage(getFileName(Base.Game->Object[Vrab01]->Data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare target.");
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	 }
	 if(Base.Cont0001->Prepare(Func01) < 0)
	 {
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   Base.Engi0001->WriteMessage(getFileName(Base.Game->Object[Vrab01]->Data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	  return 0;
	 }
	 if(Base.Cont0001->Execute() < 0)
	 {
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   Base.Engi0001->WriteMessage(getFileName(Base.Game->Object[Vrab01]->Data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	  return 0;
     }
     if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
     G_Process(Vrab01);
     return Base.Cont0001->GetReturnDWord();
    }
    int0 callId(int32 Vrab01, asIScriptFunction *Func01)
    {
     Preparation(Vrab01);
     if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = -1; Base.Game->Object_Exist[Database.InjectorNUM] = false;}
     if(Base.Cont0001->Prepare(Func01) < 0)
	 {
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   Base.Engi0001->WriteMessage(getFileName(Base.Game->Object[Vrab01]->Data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	  return;
	 }
	 if(Base.Cont0001->Execute() < 0)
	 {
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   Base.Engi0001->WriteMessage(getFileName(Base.Game->Object[Vrab01]->Data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	 }
     if(Config.MOD_ModulingLevel > 0) if(Database.InjectorNUM != -1){Base.Game->Object[Database.InjectorNUM]->Data->type = 0; Base.Game->Object_Exist[Database.InjectorNUM] = true;}
	 G_Process(Vrab01);
    }
    int32 __stdcall AI(int32 Vrab01, int32 Vrab02, int32 Vrab03, int32 Vrab04, int32 Vrab05, int32 Vrab06, int32 Vrab07)
    {
	 DWORD Dwrd01;
	 DWORD Dwrd02;
	 __asm
	 {
	  mov dword ptr ds:[Dwrd02], ecx;
	 }
     if(Config.MAIN_AI)
	 if(Base.Modu0001 = Base.Engi0001->GetModule(getModuleName(getFileName(Base.Game->Object[Vrab02]->Data->id)).c_str()))
	 {
	  asIScriptFunction *Func01 = Base.Modu0001->GetFunctionByDecl("int ego()");
      if(Func01){return callEgo(Vrab02, Vrab01, Func01);}
	 }
	 __asm
	 {
	  mov ecx, dword ptr ds:[Vrab07];
	  push ecx;
	  mov ecx, dword ptr ds:[Vrab06];
	  push ecx;
	  mov ecx, dword ptr ds:[Vrab05];
	  push ecx;
	  mov ecx, dword ptr ds:[Vrab04];
	  push ecx;
	  mov ecx, dword ptr ds:[Vrab03];
	  push ecx;
	  mov ecx, dword ptr ds:[Vrab02];
	  push ecx;
	  mov ecx, dword ptr ds:[Vrab01];
	  push ecx;
	  mov ecx, dword ptr ds:[Dwrd02];
	  call AI_o;
	  mov dword ptr ds:[Dwrd01], eax;
	 }
	 return Dwrd01;
    }
    int0 __stdcall AIa(int32 Vrab01, int32 Vrab02)
    {
	 DWORD Dwrd01;
	 _asm
	 {
	  mov dword ptr ds:[Dwrd01], ecx;
	 }
     if(Config.MAIN_AI)
     {
	  const int32 Vrab03 = Base.Game->Object[Vrab01]->Data->id;
	  string Temp01 = getFileName(Vrab03);
	  #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
	   L_Rebuilding(Vrab03, Temp01);
	  #endif
	  #ifdef MULTI_STATE
       }
      #endif
	  if(Base.Modu0001 = Base.Engi0001->GetModule(getModuleName(Temp01).c_str()))
	  {
	   asIScriptFunction *Func01 = Base.Modu0001->GetFunctionByDecl("void id()");
       if(Func01){callId(Vrab01, Func01); return;}
	   #ifdef DEBUG_VERSION
        else
        {
         #ifdef MULTI_STATE
          if(Config.AI_Console)
         #endif
         if(!Base.Modu0001->GetFunctionByDecl("int ego()"))
         Base.Engi0001->WriteMessage(getFileName(Base.Game->Object[Vrab01]->Data->id).c_str(), 0, 0, asMSGTYPE_ERROR, "Neither 'void id()' nor 'int ego()' are defined.");
        }
	   #endif
	  }
     }
	 G_Process(Vrab01);
	 _asm
	 {
	  mov ecx, dword ptr ds:[Vrab02];
	  push ecx;
	  mov ecx, dword ptr ds:[Vrab01];
	  push ecx;
	  mov ecx, dword ptr ds:[Dwrd01];
	  call AIa_o;
	 }
    }
   
    #ifdef DEBUG_VERSION
     string Revoke(const string Temp01)
     {
      uint32 Vrab01 = Temp01.size();
      while(Vrab01 != 0){Vrab01 -= 1; const int8 Vrab02 = Temp01.at(Vrab01); if(Vrab02 == '\\' || Vrab02 == '/'){Vrab01 += 1; return string(Temp01, Vrab01, Temp01.size() - Vrab01);}}
      return Temp01;
     }
     int0 MessageCallback(const asSMessageInfo *Mesg01, int0*)
     {
	  if(Mesg01->section[0] == '\0')
	  {
	   printf("%s - %s\n", Mesg01->type == asMSGTYPE_ERROR ? ">< ERROR" : Mesg01->type == asMSGTYPE_WARNING ? ")( WARNING" : "() INFO", Mesg01->message);
	  } else if(Mesg01->row == 0 && Mesg01->col == 0)
	  {
	   printf("%s { %s } - %s\n", Mesg01->type == asMSGTYPE_ERROR ? ">< ERROR" : Mesg01->type == asMSGTYPE_WARNING ? ")( WARNING" : "() INFO", Revoke(Mesg01->section).c_str(), Mesg01->message);
	  } else
	  {
	   printf("%s { %s [%d, %d] } - %s\n", Mesg01->type == asMSGTYPE_ERROR ? ">< ERROR" : Mesg01->type == asMSGTYPE_WARNING ? ")( WARNING" : "() INFO", Revoke(Mesg01->section).c_str(), Mesg01->row, Mesg01->col, Mesg01->message);
	  }
	 }
    #endif

    int0 RegisterScriptFunctions(asIScriptEngine* Engi01, int1 Vrab02)
    {
     RegisterScriptMath(Engi01);
     RegisterScriptMathComplex(Engi01); 
     RegisterScriptMath3D(Engi01);
     RegisterStdString(Engi01);
     RegisterScriptArray(Engi01, true);
     RegisterStdStringUtils(Engi01);
     RegisterGameEnums(Engi01);
     RegisterGameArrays(Engi01, Vrab02);
     
     Engi01->RegisterObjectType("ENGINE", 0, asOBJ_REF | asOBJ_NOCOUNT);
     Engi01->RegisterObjectMethod("ENGINE", "void Print(bool Value)", asMETHODPR(MD_AIDATABASES, C_Print, (int1 Vrab01), int0), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Print(int8 Value)", asMETHODPR(MD_AIDATABASES, C_Print, (int8 Vrab01), int0), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Print(int16 Value)", asMETHODPR(MD_AIDATABASES, C_Print, (int16 Vrab01), int0), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Print(int32 Value)", asMETHODPR(MD_AIDATABASES, C_Print, (int32 Vrab01), int0), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Print(int64 Value)", asMETHODPR(MD_AIDATABASES, C_Print, (int64 Vrab01), int0), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Print(uint8 Value)", asMETHODPR(MD_AIDATABASES, C_Print, (uint8 Vrab01), int0), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Print(uint16 Value)", asMETHODPR(MD_AIDATABASES, C_Print, (uint16 Vrab01), int0), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Print(uint32 Value)", asMETHODPR(MD_AIDATABASES, C_Print, (uint32 Vrab01), int0), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Print(uint64 Value)", asMETHODPR(MD_AIDATABASES, C_Print, (uint64 Vrab01), int0), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Print(float Value)", asMETHODPR(MD_AIDATABASES, C_Print, (xint32 Vrab01), int0), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Print(double Value)", asMETHODPR(MD_AIDATABASES, C_Print, (xint64 Vrab01), int0), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Print(const string &in String)", asMETHODPR(MD_AIDATABASES, C_Print, (const string &Temp01), int0), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Print_Clear()", asMETHOD(MD_AIDATABASES, C_Clear), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Input_Clear()", asMETHOD(MD_AIDATABASES, L_InputClear), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Up()", asMETHOD(MD_AIDATABASES, L_InputUP), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Left()", asMETHOD(MD_AIDATABASES, L_InputLEFT), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Down()", asMETHOD(MD_AIDATABASES, L_InputDOWN), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Right()", asMETHOD(MD_AIDATABASES, L_InputRIGHT), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Attack()", asMETHOD(MD_AIDATABASES, L_InputATTACK), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Defend()", asMETHOD(MD_AIDATABASES, L_InputDEFEND), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Jump()", asMETHOD(MD_AIDATABASES, L_InputJUMP), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Up_Hold()", asMETHOD(MD_AIDATABASES, L_InputUPH), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Left_Hold()", asMETHOD(MD_AIDATABASES, L_InputLEFTH), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Down_Hold()", asMETHOD(MD_AIDATABASES, L_InputDOWNH), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Right_Hold()", asMETHOD(MD_AIDATABASES, L_InputRIGHTH), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Attack_Hold()", asMETHOD(MD_AIDATABASES, L_InputATTACKH), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Defend_Hold()", asMETHOD(MD_AIDATABASES, L_InputDEFENDH), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "void Jump_Hold()", asMETHOD(MD_AIDATABASES, L_InputJUMPH), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "int32 Random(int32 Value)", asMETHOD(MD_AIDATABASES, L_Random), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("ENGINE", "int32 Set_Enemy(int32 Object)", asMETHOD(MD_AIDATABASES, L_Aggring), asCALL_THISCALL);
     Engi01->RegisterObjectProperty("ENGINE", "const uint32 Background", asOFFSET(MD_AIDATABASES, BackgroundID));
     Engi01->RegisterObjectProperty("ENGINE", "const uint32 Maximum_Frame", asOFFSET(MD_AIDATABASES, MaximumFrame));
     Engi01->RegisterObjectProperty("ENGINE", "const uint32 Maximum_Object", asOFFSET(MD_AIDATABASES, MaximumObj));
     Engi01->RegisterObjectProperty("ENGINE", "const int32 Maximum_MP", asOFFSET(MD_AIDATABASES, MaximumMP));
     if(Vrab02)
     {
      Engi01->RegisterObjectMethod("ENGINE", "uint32 Copy_Frame(uint32 Data, uint32 Frame1, uint32 Frame2)", asMETHOD(MD_AIDATABASES, L_Copy), asCALL_THISCALL);
      Engi01->RegisterObjectMethod("ENGINE", "uint32 Copy_Data_Frame(uint32 Data1, uint32 Data2, uint32 Frame1, uint32 Frame2)", asMETHOD(MD_AIDATABASES, L_Copys), asCALL_THISCALL);
      Engi01->RegisterObjectMethod("ENGINE", "uint32 Get_ID_Data(int32 Data_ID)", asMETHOD(MD_AIDATABASES, L_Address), asCALL_THISCALL);
      Engi01->RegisterObjectMethod("ENGINE", "uint32 Set_Object(int32 Owner, int32 Data, int32 Frame, double X, double Y, double Z, bool Facing)", asMETHOD(MD_AIDATABASES, L_Generate), asCALL_THISCALL);
      Engi01->RegisterObjectProperty("ENGINE", "const int32 Module_ID", asOFFSET(MD_AIDATABASES, ModuleID));
     }
     
     Engi01->RegisterObjectType("CORE", 0, asOBJ_REF | asOBJ_NOCOUNT);
     
     Engi01->RegisterGlobalProperty("const GAME Game", Base.Game);
     Engi01->RegisterGlobalProperty("ENGINE Engine", &Base);
     Engi01->RegisterGlobalProperty("CORE Core", &Control);

     #ifdef _MD_OLD_SCRIPT
	Engi01->RegisterGlobalFunction("void clr()", asFUNCTION(C_Clear), asCALL_CDECL);

	Engi01->RegisterGlobalFunction("void print(bool Value)", asFUNCTIONPR(C_Print, (int1 Vrab01), int0), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void print(int8 Value)", asFUNCTIONPR(C_Print, (int8 Vrab01), int0), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void print(int16 Value)", asFUNCTIONPR(C_Print, (int16 Vrab01), int0), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void print(int32 Value)", asFUNCTIONPR(C_Print, (int32 Vrab01), int0), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void print(int64 Value)", asFUNCTIONPR(C_Print, (int64 Vrab01), int0), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void print(uint8 Value)", asFUNCTIONPR(C_Print, (uint8 Vrab01), int0), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void print(uint16 Value)", asFUNCTIONPR(C_Print, (uint16 Vrab01), int0), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void print(uint32 Value)", asFUNCTIONPR(C_Print, (uint32 Vrab01), int0), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void print(uint64 Value)", asFUNCTIONPR(C_Print, (uint64 Vrab01), int0), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void print(float Value)", asFUNCTIONPR(C_Print, (xint32 Vrab01), int0), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void print(double Value)", asFUNCTIONPR(C_Print, (xint64 Vrab01), int0), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void print(const string &in String)", asFUNCTIONPR(C_Print, (const string &Temp01), int0), asCALL_CDECL);
    
    if(Vrab02)
    {
     Engi01->RegisterGlobalProperty("const uint32 maximumFrame", &Base.MaximumFrame);
     Engi01->RegisterGlobalProperty("const uint32 maximumObject", &Base.MaximumObj);
     Engi01->RegisterGlobalProperty("const int32 maximumManaPoint", &Base.MaximumMP);
     Engi01->RegisterGlobalProperty("const int32 moduleID", &Base.ModuleID);
	 Engi01->RegisterGlobalFunction("uint32 getobjectData(int32 Object_ID)", asFUNCTION(L_Address), asCALL_CDECL);
	 //Engi01->RegisterGlobalFunction("int32 getobjectSet(int32 Object_Num)", asFUNCTION(L_NumSet), asCALL_CDECL);
	 //Engi01->RegisterGlobalFunction("int32 getdataSet(int32 Object_Data)", asFUNCTION(L_NumSet), asCALL_CDECL);
	 //Engi01->RegisterGlobalFunction("void frameCopy(int32 Object_Data, int32 Frame1, int32 Frame2)", asFUNCTION(L_Copy), asCALL_CDECL);
	 //Engi01->RegisterGlobalFunction("void frameCopying(int32 Object_Data1, int32 Object_Data2, int32 Frame1, int32 Frame2)", asFUNCTION(L_Copying), asCALL_CDECL);
    }

	Engi01->RegisterGlobalFunction("int32 rand(int32 Value)", asFUNCTION(L_Random), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("int32 loadTarget(int32 Object_Number)", asFUNCTION(L_Targetting), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("int32 setEnemy(int32 Object_Number)", asFUNCTION(L_Aggring), asCALL_CDECL);

	Engi01->RegisterGlobalFunction("void up(int8 Value1 = 1, int8 Value2 = 0)", asFUNCTION(L_InputUP), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void up(bool Value1, int8 Value2 = 0)", asFUNCTION(L_InputUP), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void up(int8 Value1, bool Value2)", asFUNCTION(L_InputUP), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void up(bool Value1, bool Value2)", asFUNCTION(L_InputUP), asCALL_CDECL);

	Engi01->RegisterGlobalFunction("void down(int8 Value1 = 1, int8 Value2 = 0)", asFUNCTION(L_InputDOWN), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void down(bool Value1, int8 Value2 = 0)", asFUNCTION(L_InputDOWN), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void down(int8 Value1, bool Value2)", asFUNCTION(L_InputDOWN), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void down(bool Value1, bool Value2)", asFUNCTION(L_InputDOWN), asCALL_CDECL);

	Engi01->RegisterGlobalFunction("void left(int8 Value1 = 1, int8 Value2 = 0)", asFUNCTION(L_InputLEFT), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void left(bool Value1, int8 Value2 = 0)", asFUNCTION(L_InputLEFT), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void left(int8 Value1, bool Value2)", asFUNCTION(L_InputLEFT), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void left(bool Value1, bool Value2)", asFUNCTION(L_InputLEFT), asCALL_CDECL);

	Engi01->RegisterGlobalFunction("void right(int8 Value1 = 1, int8 Value2 = 0)", asFUNCTION(L_InputRIGHT), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void right(bool Value1, int8 Value2 = 0)", asFUNCTION(L_InputRIGHT), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void right(int8 Value1, bool Value2)", asFUNCTION(L_InputRIGHT), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void right(bool Value1, bool Value2)", asFUNCTION(L_InputRIGHT), asCALL_CDECL);

	Engi01->RegisterGlobalFunction("void A(int8 Value1 = 1,int8 Value2 = 0)", asFUNCTION(L_InputATTACK), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void A(bool Value1, int8 Value2 = 0)", asFUNCTION(L_InputATTACK), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void A(int8 Value1, bool Value2)", asFUNCTION(L_InputATTACK), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void A(bool Value1, bool Value2)", asFUNCTION(L_InputATTACK), asCALL_CDECL);

	Engi01->RegisterGlobalFunction("void J(int8 Value1 = 1,int8 Value2 = 0)", asFUNCTION(L_InputJUMP), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void J(bool Value1, int8 Value2 = 0)", asFUNCTION(L_InputJUMP), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void J(int8 Value1, bool Value2)", asFUNCTION(L_InputJUMP), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void J(bool Value1, bool Value2)", asFUNCTION(L_InputJUMP), asCALL_CDECL);

	Engi01->RegisterGlobalFunction("void D(int8 Value1 = 1,int8 Value2 = 0)", asFUNCTION(L_InputDEFEND), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void D(bool Value1, int8 Value2 = 0)", asFUNCTION(L_InputDEFEND), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void D(int8 Value1, bool Value2)", asFUNCTION(L_InputDEFEND), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void D(bool Value1, bool Value2)", asFUNCTION(L_InputDEFEND), asCALL_CDECL);

	Engi01->RegisterGlobalFunction("void DrA()", asFUNCTION(L_InputDrA), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void DlA()", asFUNCTION(L_InputDlA), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void DuA()", asFUNCTION(L_InputDuA), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void DdA()", asFUNCTION(L_InputDdA), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void DrJ()", asFUNCTION(L_InputDrJ), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void DlJ()", asFUNCTION(L_InputDlJ), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void DuJ()", asFUNCTION(L_InputDuJ), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void DdJ()", asFUNCTION(L_InputDdJ), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void DJA()", asFUNCTION(L_InputDJA), asCALL_CDECL);

	Engi01->RegisterGlobalProperty("const int32 mode", &Base.Mode);
	Engi01->RegisterGlobalProperty("const int32 difficulty", &Base.Difficulty);
	Engi01->RegisterGlobalProperty("const int32 elapsed_time", &Base.ElapsedTime);
	Engi01->RegisterGlobalProperty("const int32 background", &Base.BackgroundID);
	Engi01->RegisterGlobalProperty("const int32 bg_width", &Base.Background_width);
	Engi01->RegisterGlobalProperty("const int32 bg_zwidth1", &Base.Background_zwidth1);
	Engi01->RegisterGlobalProperty("const int32 bg_zwidth2", &Base.Background_zwidth2);
	Engi01->RegisterGlobalProperty("const int32 stage_bound", &Base.Stage_bound);
	Engi01->RegisterGlobalProperty("const bool stage_clear", &Base.Stage_clear);
	Engi01->RegisterGlobalProperty("const int32 current_phase", &Base.Phase);
	Engi01->RegisterGlobalProperty("const int32 current_phase_count", &Base.Phase_Count);
	Engi01->RegisterGlobalProperty("const int32 current_stage", &Base.Stage);

	Engi01->RegisterGlobalFunction("void printAddr(const IntArray @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const BoolArray @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const CharArray @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const CharArrayArray30 @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const CharArrayArray40 @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const DataFileArray @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const ObjectArray @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const FrameArray @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const BackgroundArray @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const SpawnArray @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const PhaseArray @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const StageArray @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const ItrArray @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const BdyArray @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const OGame @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const FileManager @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const Stage @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const Phase @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const Spawn @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const Background @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const Object @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const DataFile @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const Frame @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const Bdy @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const Itr @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const Wpoint @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const Cpoint @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const Bpoint @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
	Engi01->RegisterGlobalFunction("void printAddr(const Opoint @addr)", asFUNCTION(C_PrintAddr), asCALL_CDECL);
    
    if(!Vrab02)
    {
     Engi01->RegisterObjectType("Info", 0, asOBJ_REF);

     Engi01->RegisterObjectBehaviour("Info", asBEHAVE_ADDREF, "void f()", asMETHOD(MD_AIINFO, AddRef), asCALL_THISCALL);
     Engi01->RegisterObjectBehaviour("Info", asBEHAVE_RELEASE, "void f()", asMETHOD(MD_AIINFO, RelRef), asCALL_THISCALL);
     Engi01->RegisterObjectBehaviour("Info", asBEHAVE_FACTORY, "Info @f()", asFUNCTIONPR(INFO_Create, (), MD_AIINFO*), asCALL_CDECL);
     Engi01->RegisterObjectBehaviour("Info", asBEHAVE_FACTORY, "Info @f(int32)", asFUNCTIONPR(INFO_Create, (int32 Vrab01), MD_AIINFO*), asCALL_CDECL);
     Engi01->RegisterObjectBehaviour("Info", asBEHAVE_FACTORY, "Info @f(const Info &in Information)", asFUNCTIONPR(INFO_Create, (const MD_AIINFO &Info01), MD_AIINFO*), asCALL_CDECL);

     Engi01->RegisterObjectMethod("Info", "int32 opAssign(int32 Object_Number)", asMETHODPR(MD_AIINFO, operator=, (int32 Vrab01), int32), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("Info", "int32 opAssign(const Info &in Information)", asMETHODPR(MD_AIINFO, operator=, (const MD_AIINFO &Info01), int32), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("Info", "int32 opAddAssign(int32 Object_Number)", asMETHODPR(MD_AIINFO, operator+=, (int32 Vrab01), int32), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("Info", "int32 opAddAssign(const Info &in Information)", asMETHODPR(MD_AIINFO, operator+=,(const MD_AIINFO &Info01), int32), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("Info", "int32 opSubAssign(int32 Object_Number)", asMETHODPR(MD_AIINFO, operator-=, (int32 Vrab01), int32), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("Info", "int32 opSubAssign(const Info &in Information)", asMETHODPR(MD_AIINFO, operator-=, (const MD_AIINFO &Info01), int32), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("Info", "int32 opPreInc()", asMETHODPR(MD_AIINFO, operator++, (), int32), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("Info", "int32 opPreSub()", asMETHODPR(MD_AIINFO, operator--, (), int32), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("Info", "int32 opPostInc()", asMETHODPR(MD_AIINFO, operator++, (), int32), asCALL_THISCALL);
     Engi01->RegisterObjectMethod("Info", "int32 opPostSub()", asMETHODPR(MD_AIINFO, operator--, (), int32), asCALL_THISCALL);

     Engi01->RegisterObjectProperty("Info", "int32 x", asOFFSET(MD_AIINFO, x));
     Engi01->RegisterObjectProperty("Info", "int32 y", asOFFSET(MD_AIINFO, y));
     Engi01->RegisterObjectProperty("Info", "int32 z", asOFFSET(MD_AIINFO, z));
     Engi01->RegisterObjectProperty("Info", "vector3 position", asOFFSET(MD_AIINFO, position));
     Engi01->RegisterObjectProperty("Info", "double x_real", asOFFSET(MD_AIINFO, x_real));
     Engi01->RegisterObjectProperty("Info", "double y_real", asOFFSET(MD_AIINFO, y_real));
     Engi01->RegisterObjectProperty("Info", "double z_real", asOFFSET(MD_AIINFO, z_real));
     Engi01->RegisterObjectProperty("Info", "bool facing", asOFFSET(MD_AIINFO, facing));
     Engi01->RegisterObjectProperty("Info", "bool holding_up", asOFFSET(MD_AIINFO, holding_up));
     Engi01->RegisterObjectProperty("Info", "bool holding_down", asOFFSET(MD_AIINFO, holding_down));
     Engi01->RegisterObjectProperty("Info", "bool holding_left", asOFFSET(MD_AIINFO, holding_left));
     Engi01->RegisterObjectProperty("Info", "bool holding_right", asOFFSET(MD_AIINFO, holding_right));
     Engi01->RegisterObjectProperty("Info", "bool holding_a", asOFFSET(MD_AIINFO, holding_a));
     Engi01->RegisterObjectProperty("Info", "bool holding_j", asOFFSET(MD_AIINFO, holding_j));
     Engi01->RegisterObjectProperty("Info", "bool holding_d", asOFFSET(MD_AIINFO, holding_d));
     Engi01->RegisterObjectProperty("Info", "bool up", asOFFSET(MD_AIINFO, up));
     Engi01->RegisterObjectProperty("Info", "bool down", asOFFSET(MD_AIINFO, down));
     Engi01->RegisterObjectProperty("Info", "bool left", asOFFSET(MD_AIINFO, left));
     Engi01->RegisterObjectProperty("Info", "bool right", asOFFSET(MD_AIINFO, right));
     Engi01->RegisterObjectProperty("Info", "bool A", asOFFSET(MD_AIINFO, A));
     Engi01->RegisterObjectProperty("Info", "bool J", asOFFSET(MD_AIINFO, J));
     Engi01->RegisterObjectProperty("Info", "bool D", asOFFSET(MD_AIINFO, D));
     Engi01->RegisterObjectProperty("Info", "int8 DrA", asOFFSET(MD_AIINFO, DrA));
     Engi01->RegisterObjectProperty("Info", "int8 DlA", asOFFSET(MD_AIINFO, DlA));
     Engi01->RegisterObjectProperty("Info", "int8 DuA", asOFFSET(MD_AIINFO, DuA));
     Engi01->RegisterObjectProperty("Info", "int8 DdA", asOFFSET(MD_AIINFO, DdA));
     Engi01->RegisterObjectProperty("Info", "int8 DrJ", asOFFSET(MD_AIINFO, DrJ));
     Engi01->RegisterObjectProperty("Info", "int8 DlJ", asOFFSET(MD_AIINFO, DlJ));
     Engi01->RegisterObjectProperty("Info", "int8 DuJ", asOFFSET(MD_AIINFO, DuJ));
     Engi01->RegisterObjectProperty("Info", "int8 DdJ", asOFFSET(MD_AIINFO, DdJ));
     Engi01->RegisterObjectProperty("Info", "int8 DJA", asOFFSET(MD_AIINFO, DJA));
     Engi01->RegisterObjectProperty("Info", "int32 hp", asOFFSET(MD_AIINFO, hp));
     Engi01->RegisterObjectProperty("Info", "int32 dark_hp", asOFFSET(MD_AIINFO, dark_hp));
     Engi01->RegisterObjectProperty("Info", "int32 max_hp", asOFFSET(MD_AIINFO, max_hp));
     Engi01->RegisterObjectProperty("Info", "int32 mp", asOFFSET(MD_AIINFO, mp));
     Engi01->RegisterObjectProperty("Info", "int32 frame", asOFFSET(MD_AIINFO, frame));
     Engi01->RegisterObjectProperty("Info", "int32 bdefend", asOFFSET(MD_AIINFO, bdefend));
     Engi01->RegisterObjectProperty("Info", "int32 fall", asOFFSET(MD_AIINFO, fall));
     Engi01->RegisterObjectProperty("Info", "int32 team", asOFFSET(MD_AIINFO, team));
     Engi01->RegisterObjectProperty("Info", "int32 id", asOFFSET(MD_AIINFO, id));
     Engi01->RegisterObjectProperty("Info", "int32 blink", asOFFSET(MD_AIINFO, blink));
     Engi01->RegisterObjectProperty("Info", "int32 state", asOFFSET(MD_AIINFO, state));
     Engi01->RegisterObjectProperty("Info", "int32 weapon_type", asOFFSET(MD_AIINFO, weapon_type));
     Engi01->RegisterObjectProperty("Info", "int32 weapon_held", asOFFSET(MD_AIINFO, weapon_held));
     Engi01->RegisterObjectProperty("Info", "int32 weapon_holder", asOFFSET(MD_AIINFO, weapon_holder));
     Engi01->RegisterObjectProperty("Info", "int32 shake", asOFFSET(MD_AIINFO, shake));
     Engi01->RegisterObjectProperty("Info", "int32 wait_counter", asOFFSET(MD_AIINFO, wait_counter));
     Engi01->RegisterObjectProperty("Info", "int32 num", asOFFSET(MD_AIINFO, num));
     Engi01->RegisterObjectProperty("Info", "int32 ctimer", asOFFSET(MD_AIINFO, ctimer));
     Engi01->RegisterObjectProperty("Info", "int32 arest", asOFFSET(MD_AIINFO, arest));
     Engi01->RegisterObjectProperty("Info", "CharArray vrests", asOFFSET(MD_AIINFO, vrests[0]));
     Engi01->RegisterObjectProperty("Info", "int32 vrest", asOFFSET(MD_AIINFO, vrest));
     Engi01->RegisterObjectProperty("Info", "vector3 velocity", asOFFSET(MD_AIINFO, velocity));
     Engi01->RegisterObjectProperty("Info", "double x_velocity", asOFFSET(MD_AIINFO, x_velocity));
     Engi01->RegisterObjectProperty("Info", "double y_velocity", asOFFSET(MD_AIINFO, y_velocity));
     Engi01->RegisterObjectProperty("Info", "double z_velocity", asOFFSET(MD_AIINFO, z_velocity));
     Engi01->RegisterObjectProperty("Info", "int32 clone", asOFFSET(MD_AIINFO, clone));
     Engi01->RegisterObjectProperty("Info", "int32 type", asOFFSET(MD_AIINFO, type)); 
     Engi01->RegisterObjectProperty("Info", "int32 reserve", asOFFSET(MD_AIINFO, reserve));
     Engi01->RegisterObjectProperty("Info", "DataFile @data", asOFFSET(MD_AIINFO, data));
     
	 Engi01->RegisterGlobalProperty("const Info self", &Info0001);
	 Engi01->RegisterGlobalProperty("Info target", &Info0002);
    }
	 Engi01->RegisterGlobalProperty("const OGame game", Base.Game);
    #endif
   }
   int0 G_Releasing(){if(Base.Cont0001) Base.Cont0001->Release(); if(Base.Cont0002) Base.Cont0002->Release(); if(Base.Engi0001) Base.Engi0001->Release(); if(Base.Engi0002) Base.Engi0002->Release();}
   BOOL APIENTRY DllMain(HANDLE Hand01, DWORD Dwrd01, LPVOID Lpvd01)
   {
    LPVOID Lpvd02 = Lpvd01; Lpvd02 = NULL;
    switch(Dwrd01)
    {
     case DLL_PROCESS_ATTACH: G_Initialization(); G_Starting(); InitInstance(Hand01); break;
     case DLL_PROCESS_DETACH: G_Hiding(); G_Cleaning(); G_Releasing(); ExitInstance(); break;
     case DLL_THREAD_ATTACH: break;
     case DLL_THREAD_DETACH: break;
    }
    return(true);
   }
   HRESULT WINAPI DirectDrawCreate(GUID FAR *Lpgd01, LPDIRECTDRAW FAR *Lpdd01, IUnknown FAR *Iunk01)
   {
    if(!Hins0002) LoadOriginalDll();
    typedef HRESULT (WINAPI* DirectDrawCreate_Type)(GUID FAR *, LPVOID *, IUnknown FAR *);
    DirectDrawCreate_Type Ddct01 = (DirectDrawCreate_Type)GetProcAddress(Hins0002, _T("DirectDrawCreate"));
    if(!Ddct01){::ExitProcess(0);}
    LPDIRECTDRAW7 FAR Lpdr01;
    HRESULT Hrsl01 = Ddct01(Lpgd01, (LPVOID*) &Lpdr01, Iunk01);
    *Lpdd01 = (LPDIRECTDRAW) new myIDDraw7(Lpdr01);
    return (Hrsl01);
   }
   int0 InitInstance(HANDLE Hand01){Hins0002 = NULL; Hins0003 = NULL; Hins0003 = (HINSTANCE)Hand01;}
   int0 LoadOriginalDll(int0){int8 Vrab01[MAX_PATH]; ::GetSystemDirectory(Vrab01, MAX_PATH); strcat(Vrab01,"\\ddraw.dll"); if(!Hins0002) Hins0002 = ::LoadLibrary(Vrab01); if(!Hins0002){::ExitProcess(0);}}
   int0 ExitInstance(){if(Hins0002){::FreeLibrary(Hins0002); Hins0002 = NULL;}}

   string getFileName(int32 Vrab01){return Config.AI_Directory + "\\" + std::to_string(Vrab01) + ".as";}
   MD_VALIDITY isValidFileName(string Temp01)
   {
    if(Temp01.size() < Config.AI_Directory.size() + 5) return INVALID;
    Temp01.erase(0, Config.AI_Directory.size() + 1);
    Temp01 = L_Lowercase(Temp01);
    if(string(Temp01, Temp01.size() - 3, 3) != ".as") return INVALID;
    if(Temp01.at(0) == '_') if(Config.MAIN_MOD){return MODULE;} else {return INVALID;}
    if(Config.MAIN_AI)
    {
     if(Temp01.at(0) == '0') if(Temp01 != "0.as") return INVALID;
     uint32 Vrab01 = Temp01.size() - 3;
     while(Vrab01 > 0){Vrab01 -= 1; if(Temp01.at(Vrab01) < '0' || Temp01.at(Vrab01) > '9' ) return INVALID;}
     return VALID;
    } else {return INVALID;}
   }
   string L_Moduling(const string &Temp01){uint32 Vrab01 = 0; const uint32 Vrab02 = Strn0001.size(); while(Vrab01 != Vrab02){if(Temp01 == Strn0001[Vrab01]) break; Vrab01 += 1;} if(Vrab01 == Vrab02){Strn0001.push_back(Temp01); uint32 Vrab03 = Temp01.size(); while(Vrab03 > 0){Vrab03 -= 1; if(Temp01.at(Vrab03) == '_') break;} Vrab03 += 1; Vect0001.push_back(L_Numbering(string(Temp01, Vrab03, Temp01.size() - Vrab03 - 2))); return "Mod_" + std::to_string(Vrab02);} else {return "Mod_" + std::to_string(Vrab01);}}
   string getModuleName(const string &Temp01){return Temp01.substr(Config.AI_Directory.size() + 1);}
   int0 G_Starting()
   {
    {
     for(auto const &Temp01 : std::filesystem::directory_iterator(Config.AI_OldDirectory))
     {
      string Temp02 = Temp01.path().string();

      if(Temp02.size() < Config.AI_OldDirectory.size() + 5) continue;
      const string Temp03 = L_Lowercase(string(Temp02, Config.AI_OldDirectory.size() + 1, Temp02.size() - (Config.AI_OldDirectory.size() + 1)));
      if(string(Temp03, Temp03.size() - 3, 3) != ".as") continue;
      if(Temp03.at(0) == '_') if(Config.MAIN_MOD){goto Labl01;} else {continue;}
      if(Config.MAIN_AI)
      {
       if(Temp03.at(0) == '0') if(Temp03 != "0.as") continue;
       uint32 Vrab01 = Temp03.size() - 3;
       while(Vrab01 > 0){Vrab01 -= 1; if(Temp03.at(Vrab01) < '0' || Temp03.at(Vrab01) > '9' ) goto Labl02;}
       goto Labl01;
      } else {continue;}
      Labl02: continue;
      Labl01:
      if(L_Open(Temp02))
      {
       Temp02.erase(0, Config.AI_OldDirectory.size() + 1);
       Temp02 = Config.AI_Directory + "\\" + Temp02;
       if(L_Create(L_Execute(Temp02)))
       {File0002 << File0001.rdbuf(); L_Summary(Temp02 + "\n"); File0002.close();}
       File0001.close();
      }
     }
    }
    if(Config.MAIN_MOD)
    {
     int1 Vrab01 = true;
     for(auto const &Temp01 : std::filesystem::directory_iterator(Config.AI_Directory))
     {
      string Temp02 = Temp01.path().string();
      Temp02.erase(0, Config.AI_Directory.size() + 1);
      Temp02 = L_Lowercase(Temp02);
      if(Temp02.at(0) != '_') continue;
      if(string(Temp02, Temp02.size() - 3, 3) != ".as") continue;
      Vrab01 = false; break;
     }
     if(Vrab01) Config.MAIN_MOD = false;
    }
    if(Config.MAIN_AI || Config.MAIN_MOD)
    {
     #ifdef DEBUG_VERSION
      #ifdef MULTI_STATE 
       if(Config.AI_Console)
       {
      #endif
      const int32 Vrab01 = Config.AI_ConsoleStyle & 0xFF;
      int32 Vrab02 = 0;
      const int16 Vrab03 = Config.AI_ConsoleSize & 0xFF;
      int16 Vrab04 = 0; if(Config.AI_ConsoleScroll) Vrab04 = 400;
      if(Vrab01 > 127){Vrab02 = 0;} else {Vrab02 = 255;}
      AllocConsole();
      HANDLE Hand01 = GetStdHandle(STD_OUTPUT_HANDLE);
      freopen("CONIN$", "rb", stdin);   // reopen stdin handle as console window input
      freopen("CONOUT$", "wb", stdout); // reopen stout handle as console window output
      freopen("CONOUT$", "wb", stderr); // reopen stderr handle as console window output
      SMALL_RECT Rect01 = {0, 0, Vrab03, (Vrab03 / 2)};
      CONSOLE_SCREEN_BUFFER_INFOEX Info01; Info01.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
      SetConsoleScreenBufferSize(Hand01, {Vrab03, (int16)((Vrab03 / 2) - 2 + Vrab04)});
      GetConsoleScreenBufferInfoEx(Hand01, &Info01);
      Info01.wAttributes = true; Info01.srWindow = Rect01;
      Info01.ColorTable[0] = RGB(Vrab01, Vrab01, Vrab01);
      Info01.ColorTable[1] = RGB(Vrab02, Vrab02, Vrab02);
      Info01.ColorTable[7] = Info01.ColorTable[1];
      SetConsoleScreenBufferInfoEx(Hand01, &Info01);
      SetConsoleScreenBufferSize(Hand01, {Vrab03, (int16)((Vrab03 / 2) - 2 + Vrab04)});
      if(Config.MAIN_AI){SetConsoleTitleA("AI's Console");} else {SetConsoleTitleA("MOD's Console");}
     #endif
     #ifdef MULTI_STATE
      }
     #endif
     Base.Modu0001 = NULL;
     if(Config.MAIN_AI) Base.Engi0001 = asCreateScriptEngine(ANGELSCRIPT_VERSION); if(!Base.Engi0001){Config.MAIN_AI = false;}
     if(Config.MAIN_MOD) Base.Engi0002 = asCreateScriptEngine(ANGELSCRIPT_VERSION); if(!Base.Engi0002){Config.MAIN_MOD = false;}
     #ifdef DEBUG_VERSION
      #ifdef MULTI_STATE
       if(Config.AI_Console)
       {
      #endif
	  if(Config.MAIN_AI) Base.Engi0001->SetMessageCallback(asFUNCTION(MessageCallback), NULL, asCALL_CDECL);
	  if(Config.MAIN_MOD) Base.Engi0002->SetMessageCallback(asFUNCTION(MessageCallback), NULL, asCALL_CDECL);
     #endif
     #ifdef MULTI_STATE
      }
     #endif
     if(Config.MAIN_AI) Base.Cont0001 = Base.Engi0001->CreateContext();
     if(Config.MAIN_MOD) Base.Cont0002 = Base.Engi0002->CreateContext();
     if(Config.MAIN_AI) RegisterScriptFunctions(Base.Engi0001, false);
     if(Config.MAIN_MOD) RegisterScriptFunctions(Base.Engi0002, true);
    }

    if(Config.MAIN_AI || Config.MAIN_MOD)
    {
     AI_o = (int32 (__stdcall*)(int32, int32, int32, int32, int32, int32, int32))DetourFunction((PBYTE)0x00403a40, (PBYTE)AI);
     AIa_o = (int32 (__stdcall*)(int32, int32))DetourFunction((PBYTE)0x004094b0, (PBYTE)AIa);
    }

    if(Config.MAIN_AI || Config.MAIN_MOD)
    {
     HANDLE Hand01; WIN32_FIND_DATA Wfnd01; Strn0001.clear(); Vect0001.clear();
     int8 Varb01[MAX_PATH]; strcpy(&Varb01[0], (Config.AI_Directory + "\\").c_str());
     int8 Varb02[MAX_PATH]; strcpy(&Varb02[0], &Varb01[0]);
     strcat(&Varb01[0], "*.as");
     if((Hand01 = FindFirstFile(&Varb01[0], &Wfnd01)) == INVALID_HANDLE_VALUE) return;
     strcpy(&Varb01[0], &Varb02[0]);
     do 
     {
      strcpy(&Varb02[0], &Varb01[0]);
      strcat(&Varb02[0], Wfnd01.cFileName);
      if(!(Wfnd01.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY))
      {
       const MD_VALIDITY Valy01 = isValidFileName(Varb02);
       if(Valy01 != INVALID)
       {
        #ifdef DEBUG_VERSION
	     #ifdef MULTI_STATE
          if(Config.AI_Console)
          {
         #endif
	     FILETIME Time01;
	     hasFileTimeChanged(&Varb02[0], &Time01);
         if(Valy01 == MODULE){Moti0002.insert(std::pair < int32, FILETIME > (Strn0001.size(), Time01));} else
         {Moti0001.insert(std::pair < int32, FILETIME > (getIdFromFileName(&Varb02[0]), Time01));}
	    #endif
	    #ifdef MULTI_STATE
         }
        #endif
	    CScriptBuilder Bild01;
	    #ifdef DEBUG_VERSION
	     #ifdef MULTI_STATE
          if(Config.AI_Console)
          {
         #endif
	     Bild01.DefineWord("debug");
         if(Valy01 == MODULE){Base.Engi0002->WriteMessage(&Varb02[0], 0, 0, asMSGTYPE_INFORMATION, "Building.");} else 
         {Base.Engi0001->WriteMessage(&Varb02[0], 0, 0, asMSGTYPE_INFORMATION, "Building.");}
	     #ifdef MULTI_STATE
          }
         #endif
	    #else
	     Bild01.DefineWord("release");
	    #endif
	    if(Valy01 == MODULE)
        {
         Bild01.DefineWord("module");
	     Bild01.StartNewModule(Base.Engi0002, L_Moduling(&Varb02[0]).c_str());
        } else 
        {
         Bild01.DefineWord("character");
	     Bild01.StartNewModule(Base.Engi0001, getModuleName(&Varb02[0]).c_str());
        }
	    if(Bild01.AddSectionFromFile(&Varb02[0]) < 0)
	    {
         #ifdef DEBUG_VERSION
	      #ifdef MULTI_STATE
           if(Config.AI_Console)
           {
          #endif
          if(Valy01 == MODULE){Base.Engi0002->WriteMessage(&Varb02[0], 0, 0, asMSGTYPE_ERROR, "Unable to load file.");} else 
          {Base.Engi0001->WriteMessage(&Varb02[0], 0, 0, asMSGTYPE_ERROR, "Unable to load file.");}
         #endif
	     #ifdef MULTI_STATE
          }
         #endif
         if(Valy01 == MODULE){Base.Engi0002->DiscardModule(getModuleName(&Varb02[0]).c_str());} else
         {Base.Engi0001->DiscardModule(getModuleName(&Varb02[0]).c_str());}
         continue;
        }
        if(Bild01.BuildModule() < 0)
	    {
         #ifdef DEBUG_VERSION
	      #ifdef MULTI_STATE
           if(Config.AI_Console)
           {
          #endif
          if(Valy01 == MODULE){Base.Engi0002->WriteMessage(&Varb02[0], 0, 0, asMSGTYPE_ERROR, "Unable to build module.");} else
          {Base.Engi0001->WriteMessage(&Varb02[0], 0, 0, asMSGTYPE_ERROR, "Unable to build module.");}
         #endif
         #ifdef MULTI_STATE
          }
         #endif
         if(Valy01 == MODULE){Base.Engi0002->DiscardModule(getModuleName(&Varb02[0]).c_str());} else
         {Base.Engi0001->DiscardModule(getModuleName(&Varb02[0]).c_str());}
         continue;
	    }
	   }
      }
     } while(FindNextFile(Hand01, &Wfnd01));
     FindClose(Hand01);
    }

    string Temp99;
    if(Config.MAIN_MOD)
    {
     if(Config.MOD_ModulingLevel > 1)
     {
      #ifdef DEBUG_VERSION
	   #ifdef MULTI_STATE
        if(Config.AI_Console)
        {
       #endif
       Base.Engi0002->WriteMessage("", 0, 0, asMSGTYPE_INFORMATION, "Rundown the data(s) in order to get the Modifier to work finely.");
      #endif
      #ifdef MULTI_STATE
       }
      #endif
      if(L_Open(Config.ECD_InstallDataDirectory))
      {
       string Temp01; Data0001.clear(); uint32 Vrab01 = 0;
       while(File0001)
       {
        File0001 >> Temp01; if(!File0001) break; if(Temp01.at(0) == '#'){std::getline(File0001, Temp01); continue;}
        if(Temp01 == "<object>")
        {
         while(File0001)
         {
          File0001 >> Temp01; if(!File0001) break; if(Temp01.at(0) == '#'){std::getline(File0001, Temp01); continue;}
          if(Temp01 == "id:"){Vrab01 += 1; Data0001.resize(Vrab01); File0001 >> Temp01; Data0001[Vrab01 - 1].ID = ruint32(L_Positive(L_Numbering(Temp01))); continue;}
          if(Temp01 == "file:"){File0001 >> Temp01; if(Vrab01 > 0) Data0001[Vrab01 - 1].Address = Temp01; continue;}
          if(Temp01 == "type:"){File0001 >> Temp01; if(Vrab01 > 0) Data0001[Vrab01 - 1].Type = ruint32(L_Positive(L_Numbering(Temp01)));continue;}
          if(Temp01 == "<object_end>"){break;}
         }
         continue;
        }
        if(Temp01 == "<file_editing>")
        {
         Temp99 += Temp01 + "\n";
         while(File0001)
         {
          File0001 >> Temp01; if(!File0001) break; if(Temp01.at(0) == '#'){std::getline(File0001, Temp01); continue;}
          if(Temp01 == "<file_editing_end>"){Temp99 += Temp01 + "\n\n"; break;}
          Temp99 += " " + Temp01 + "\n";
         }
         continue;
        }
        if(Temp01 == "<background>")
        {
         Temp99 += Temp01 + "\n";
         while(File0001)
         {
          File0001 >> Temp01; if(!File0001) break; if(Temp01.at(0) == '#'){std::getline(File0001, Temp01); continue;}
          if(Temp01 == "id:"){Temp99 += " " + Temp01 + " "; File0001 >> Temp01; Temp99 += Temp01 + " "; if(Temp01.size() < 2) Temp99 += " "; continue;}
          if(Temp01 == "file:"){Temp99 += Temp01 + " "; File0001 >> Temp01; Temp99 += Temp01 + "\n"; continue;}
          if(Temp01 == "<background_end>"){Temp99 += Temp01 + "\n\n"; break;}
         }
         continue;
        }
       } File0001.close();
       while(Vrab01 != 0)
       {
        Vrab01 -= 1;
        #ifdef DEBUG_VERSION
	     #ifdef MULTI_STATE
          if(Config.AI_Console)
          {
         #endif
         Base.Engi0002->WriteMessage("", 0, 0, asMSGTYPE_INFORMATION, ("Accessing \"" + Data0001[Vrab01].Address + "\".").c_str());
        #endif
        #ifdef MULTI_STATE
         }
        #endif
        if(L_Lowercase(string(Data0001[Vrab01].Address, Data0001[Vrab01].Address.size() - 4, 4)) == ".dat")
        {
         if(L_Open(Data0001[Vrab01].Address) && L_Create(L_Execute(TEMPORAL_FILE)))
         {
          std::stringstream Temp02; Temp02 << File0001.rdbuf(); File0001.close();
          Temp01 = Temp02.str(); string Temp03 = ENCODING_KEY;
          const uint32 Vrab02 = Temp01.size(); uint32 Vrab03 = 12; const uint32 Vrab04 = Temp03.size();
          for(uint32 Vrab05 = 123; Vrab05 < Vrab02; ++Vrab05){Temp01.at(Vrab05) -= Temp03.at(Vrab03); Vrab03 += 1; if(Vrab03 == Vrab04) Vrab03 = 0;}
          Temp01.erase(0, 123); File0002 << Temp01; File0002.close();
          if(!L_Open(TEMPORAL_FILE))
          {
           #ifdef DEBUG_VERSION
	        #ifdef MULTI_STATE
             if(Config.AI_Console)
             {
            #endif
            Base.Engi0002->WriteMessage("", 0, 0, asMSGTYPE_ERROR, "\"" TEMPORAL_FILE "\" inaccesible, cancel the whole process and reduce the Moduling level into 1.");
           #endif
           #ifdef MULTI_STATE
            }
           #endif
           Config.MOD_ModulingLevel = 1; Data0001.clear();
           break;
          }
         } else 
         {
          #ifdef DEBUG_VERSION
	       #ifdef MULTI_STATE
            if(Config.AI_Console)
            {
           #endif
           Base.Engi0002->WriteMessage("", 0, 0, asMSGTYPE_ERROR, ("Either \"" + Data0001[Vrab01].Address + "\" or \"" TEMPORAL_FILE "\" inaccesible.").c_str());
          #endif
          #ifdef MULTI_STATE
           }
          #endif
          continue;
         }
        } else 
        {
         if(!L_Open(Data0001[Vrab01].Address))
         {
          #ifdef DEBUG_VERSION
	       #ifdef MULTI_STATE
            if(Config.AI_Console)
            {
           #endif
           Base.Engi0002->WriteMessage("", 0, 0, asMSGTYPE_ERROR, ("\"" + Data0001[Vrab01].Address + "\" inaccesible.").c_str());
          #endif
          #ifdef MULTI_STATE
           }
          #endif
          continue;
         }
        }

        if(Config.MOD_ResultFraming) Data0001[Vrab01].Frame.resize(MaximumFrames);
        uint32 Vrab02 = 0; uint32 Vrab04 = 0; uint32 Vrab05 = 0; uint32 Vrab96 = 11;
        while(File0001)
        {
         File0001 >> Temp01; if(!File0001) break; if(Temp01.at(0) == '#'){std::getline(File0001, Temp01); continue;}
         switch(Vrab02)
         {
          case 0:
           if(Temp01 == "<bmp_begin>")               {Vrab02 = 1; continue;}
           if(Temp01 == "<weapon_strength_list>")    {Vrab02 = 2; continue;}
           if(Temp01 == "<frame>")                   {Vrab02 = 3; File0001 >> Temp01; if(Config.MOD_ResultFraming){Vrab04 = ruint32(L_Numbering(Temp01)); if(Vrab04 >= Data0001[Vrab01].Frame.size()) Data0001[Vrab01].Frame.resize(Vrab04 + 1); Data0001[Vrab01].Frame[Vrab04].Number = ruint32(-1);} else {Vrab04 = Data0001[Vrab01].Frame.size(); Data0001[Vrab01].Frame.resize(Data0001[Vrab01].Frame.size() + 1); Data0001[Vrab01].Frame[Vrab04].Number = ruint32(L_Numbering(Temp01));} File0001 >> Data0001[Vrab01].Frame[Vrab04].Name; continue;}
          break;
          case 1:
           if(Temp01 == "<bmp_end>")                 {Vrab02 = 0; continue;}
           if(Temp01 == "name:")                     {File0001 >> Data0001[Vrab01].Main.Name; continue;}
           if(Temp01 == "head:")                     {File0001 >> Data0001[Vrab01].Main.Add_Head; continue;}
           if(Temp01 == "small:")                    {File0001 >> Data0001[Vrab01].Main.Add_Small; continue;}
           if(string(Temp01, 0, 5) == "file(")       {const uint32 Vrab03 = Data0001[Vrab01].Main.Pictures.size(); Data0001[Vrab01].Main.Pictures.resize(Vrab03 + 1); File0001 >> Data0001[Vrab01].Main.Pictures[Vrab03].Add_Address; continue;}
           if(Temp01 == "w:")                        {const uint32 Vrab03 = Data0001[Vrab01].Main.Pictures.size(); if(Vrab03 > 0){File0001 >> Temp01; Data0001[Vrab01].Main.Pictures[Vrab03 - 1].Width = ruint32(L_Numbering(Temp01));} else {File0001 >> Temp01;} continue;}
           if(Temp01 == "h:")                        {const uint32 Vrab03 = Data0001[Vrab01].Main.Pictures.size(); if(Vrab03 > 0){File0001 >> Temp01; Data0001[Vrab01].Main.Pictures[Vrab03 - 1].Height = ruint32(L_Numbering(Temp01));} else {File0001 >> Temp01;} continue;}
           if(Temp01 == "col:")                      {const uint32 Vrab03 = Data0001[Vrab01].Main.Pictures.size(); if(Vrab03 > 0){File0001 >> Temp01; Data0001[Vrab01].Main.Pictures[Vrab03 - 1].Column = ruint32(L_Numbering(Temp01));} else {File0001 >> Temp01;} continue;}
           if(Temp01 == "row:")                      {const uint32 Vrab03 = Data0001[Vrab01].Main.Pictures.size(); if(Vrab03 > 0){File0001 >> Temp01; Data0001[Vrab01].Main.Pictures[Vrab03 - 1].Row = ruint32(L_Numbering(Temp01));} else {File0001 >> Temp01;} continue;}
           if(Temp01 == "walking_frame_rate")        {File0001 >> Temp01; Data0001[Vrab01].Main.WalkAnimation = ruint32(L_Numbering(Temp01)); continue;}
           if(Temp01 == "running_frame_rate")        {File0001 >> Temp01; Data0001[Vrab01].Main.RunAnimation = ruint32(L_Numbering(Temp01)); continue;}
           if(Temp01 == "walking_speed")             {File0001 >> Data0001[Vrab01].Main.Dob_WalkSpeed; continue;}
           if(Temp01 == "walking_speedz")            {File0001 >> Data0001[Vrab01].Main.Dob_WalkSpeedZ; continue;}
           if(Temp01 == "running_speed")             {File0001 >> Data0001[Vrab01].Main.Dob_RunSpeed; continue;}
           if(Temp01 == "running_speedz")            {File0001 >> Data0001[Vrab01].Main.Dob_RunSpeedZ; continue;}
           if(Temp01 == "heavy_walking_speed")       {File0001 >> Data0001[Vrab01].Main.Dob_HeavyWalkSpeed; continue;}
           if(Temp01 == "heavy_walking_speedz")      {File0001 >> Data0001[Vrab01].Main.Dob_HeavyWalkSpeedZ; continue;}
           if(Temp01 == "heavy_running_speed")       {File0001 >> Data0001[Vrab01].Main.Dob_HeavyRunSpeed; continue;}
           if(Temp01 == "heavy_running_speedz")      {File0001 >> Data0001[Vrab01].Main.Dob_HeavyRunSpeedZ; continue;}
           if(Temp01 == "jump_height")               {File0001 >> Data0001[Vrab01].Main.Dob_JumpHeight; continue;}
           if(Temp01 == "jump_distance")             {File0001 >> Data0001[Vrab01].Main.Dob_JumpSpeed; continue;}
           if(Temp01 == "jump_distancez")            {File0001 >> Data0001[Vrab01].Main.Dob_JumpSpeedZ; continue;}
           if(Temp01 == "dash_height")               {File0001 >> Data0001[Vrab01].Main.Dob_DashHeight; continue;}
           if(Temp01 == "dash_distance")             {File0001 >> Data0001[Vrab01].Main.Dob_DashSpeed; continue;}
           if(Temp01 == "dash_distancez")            {File0001 >> Data0001[Vrab01].Main.Dob_DashSpeedZ; continue;}
           if(Temp01 == "rowing_height")             {File0001 >> Data0001[Vrab01].Main.Dob_FlipHeight; continue;}
           if(Temp01 == "rowing_distance")           {File0001 >> Data0001[Vrab01].Main.Dob_FlipSpeed; continue;}
           if(Temp01 == "weapon_hp:")                {File0001 >> Temp01; Data0001[Vrab01].Main.StartingHealth = L_Numbering(Temp01); continue;}
           if(Temp01 == "weapon_drop_hurt:")         {File0001 >> Temp01; Data0001[Vrab01].Main.LandingHurt = L_Numbering(Temp01); continue;}
           if(Temp01 == "weapon_hit_sound:")         {File0001 >> Data0001[Vrab01].Main.Add_HitSound; continue;}
           if(Temp01 == "weapon_drop_sound:")        {File0001 >> Data0001[Vrab01].Main.Add_LandingSound; continue;}
           if(Temp01 == "weapon_broken_sound:")      {File0001 >> Data0001[Vrab01].Main.Add_BreakSound; continue;}
          break;
          case 2:
           if(Temp01 == "<weapon_strength_list_end>"){Vrab02 = 0; continue;}
           if(Temp01 == "entry:")                    {File0001 >> Temp01; const uint32 Vrab03 = L_Numbering(Temp01); if(Data0001[Vrab01].Strength.size() < Vrab03) Data0001[Vrab01].Strength.resize(Vrab03); File0001 >> Temp01; if(Vrab03 > 0) Data0001[Vrab01].Strength[Vrab03 - 1].Name = Temp01; continue;}
           if(Temp01 == "zwidth:")                   {File0001 >> Temp01; const uint32 Vrab03 = Data0001[Vrab01].Strength.size(); if(Vrab03 > 0) Data0001[Vrab01].Strength[Vrab03 - 1].ZWidth = L_Numbering(Temp01); continue;}
           if(Temp01 == "dvx:")                      {File0001 >> Temp01; const uint32 Vrab03 = Data0001[Vrab01].Strength.size(); if(Vrab03 > 0) Data0001[Vrab01].Strength[Vrab03 - 1].XVelocity = L_Numbering(Temp01); continue;}
           if(Temp01 == "dvy:")                      {File0001 >> Temp01; const uint32 Vrab03 = Data0001[Vrab01].Strength.size(); if(Vrab03 > 0) Data0001[Vrab01].Strength[Vrab03 - 1].YVelocity = L_Numbering(Temp01); continue;}
           if(Temp01 == "fall:")                     {File0001 >> Temp01; const uint32 Vrab03 = Data0001[Vrab01].Strength.size(); if(Vrab03 > 0) Data0001[Vrab01].Strength[Vrab03 - 1].HitEffect = L_Numbering(Temp01); continue;}
           if(Temp01 == "arest:")                    {File0001 >> Temp01; const uint32 Vrab03 = Data0001[Vrab01].Strength.size(); if(Vrab03 > 0) Data0001[Vrab01].Strength[Vrab03 - 1].AttackerRefresh = L_Numbering(Temp01); continue;}
           if(Temp01 == "vrest:")                    {File0001 >> Temp01; const uint32 Vrab03 = Data0001[Vrab01].Strength.size(); if(Vrab03 > 0) Data0001[Vrab01].Strength[Vrab03 - 1].VictimRefresh = L_Numbering(Temp01); continue;}
           if(Temp01 == "respond:")                  {File0001 >> Temp01; const uint32 Vrab03 = Data0001[Vrab01].Strength.size(); if(Vrab03 > 0) Data0001[Vrab01].Strength[Vrab03 - 1].HitRespond = L_Numbering(Temp01); continue;}
           if(Temp01 == "effect:")                   {File0001 >> Temp01; const uint32 Vrab03 = Data0001[Vrab01].Strength.size(); if(Vrab03 > 0) Data0001[Vrab01].Strength[Vrab03 - 1].Effect = L_Numbering(Temp01); continue;}
           if(Temp01 == "bdefend:")                  {File0001 >> Temp01; const uint32 Vrab03 = Data0001[Vrab01].Strength.size(); if(Vrab03 > 0) Data0001[Vrab01].Strength[Vrab03 - 1].Power = L_Numbering(Temp01); continue;}
           if(Temp01 == "injury:")                   {File0001 >> Temp01; const uint32 Vrab03 = Data0001[Vrab01].Strength.size(); if(Vrab03 > 0) Data0001[Vrab01].Strength[Vrab03 - 1].Damage = L_Numbering(Temp01); continue;}
          break;
          case 3:
           if(Temp01 == "<frame_end>")               {Vrab02 = 0; continue;}
           if(Temp01 == "pic:")                      {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Picture = L_Numbering(Temp01); continue;}
           if(Temp01 == "state:")                    {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].State = L_Numbering(Temp01); continue;}
           if(Temp01 == "wait:")                     {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Wait = L_Numbering(Temp01); continue;}
           if(Temp01 == "next:")                     {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Next = L_Numbering(Temp01); continue;}
           if(Temp01 == "dvx:")                      {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].XVelocity = L_Numbering(Temp01); continue;}
           if(Temp01 == "dvy:")                      {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].YVelocity = L_Numbering(Temp01); continue;}
           if(Temp01 == "dvz:")                      {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].ZVelocity = L_Numbering(Temp01); continue;}
           if(Temp01 == "centerx:")                  {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].CenterX = L_Numbering(Temp01); continue;}
           if(Temp01 == "centery:")                  {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].CenterY = L_Numbering(Temp01); continue;}
           if(Temp01 == "hit_a:")                    {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].InputA = L_Numbering(Temp01); continue;}
           if(Temp01 == "hit_d:")                    {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].InputD = L_Numbering(Temp01); continue;}
           if(Temp01 == "hit_j:")                    {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].InputJ = L_Numbering(Temp01); continue;}
           if(Temp01 == "hit_Fa:")                   {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].InputDFA = L_Numbering(Temp01); continue;}
           if(Temp01 == "hit_Fj:")                   {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].InputDFJ = L_Numbering(Temp01); continue;}
           if(Temp01 == "hit_Da:")                   {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].InputDDA = L_Numbering(Temp01); continue;}
           if(Temp01 == "hit_Dj:")                   {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].InputDDJ = L_Numbering(Temp01); continue;}
           if(Temp01 == "hit_Ua:")                   {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].InputDUA = L_Numbering(Temp01); continue;}
           if(Temp01 == "hit_Uj:")                   {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].InputDUJ = L_Numbering(Temp01); continue;}
           if(Temp01 == "hit_ja:")                   {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].InputDJA = L_Numbering(Temp01); continue;}
           if(Temp01 == "mp:")                       {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].MPManage = L_Numbering(Temp01); continue;}
           if(Temp01 == "sound:")                    {File0001 >> Data0001[Vrab01].Frame[Vrab04].Add_SoundEffect; continue;}
           if(Temp01 == "bpoint:")                   {Vrab02 = 4; continue;}
           if(Temp01 == "cpoint:")                   {Vrab02 = 5; continue;}
           if(Temp01 == "wpoint:")                   {Vrab02 = 6; continue;}
           if(Temp01 == "opoint:")                   {Vrab02 = 7; Vrab05 = Data0001[Vrab01].Frame[Vrab04].Opoint.size(); Data0001[Vrab01].Frame[Vrab04].Opoint.resize(Vrab05 + 1); continue;}
           if(Temp01 == "itr:")                      {Vrab02 = 8; Vrab05 = Data0001[Vrab01].Frame[Vrab04].Ipoint.size(); Data0001[Vrab01].Frame[Vrab04].Ipoint.resize(Vrab05 + 1); continue;}
           if(Temp01 == "bdy:")                      {Vrab02 = 9; Vrab05 = Data0001[Vrab01].Frame[Vrab04].Hpoint.size(); Data0001[Vrab01].Frame[Vrab04].Hpoint.resize(Vrab05 + 1); continue;}
          break;
          case 4:
           if(Temp01 == "bpoint_end:")               {Vrab02 = 3; continue;}
           if(Temp01 == "x:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Bpoint.X = L_Numbering(Temp01); continue;}
           if(Temp01 == "y:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Bpoint.Y = L_Numbering(Temp01); continue;}
          break;
          case 5:
           if(Temp01 == "cpoint_end:")               {Vrab02 = 3; continue;}
           if(Temp01 == "kind:")                     {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.Type = L_Numbering(Temp01); continue;}
           if(Temp01 == "x:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.X = L_Numbering(Temp01); continue;}
           if(Temp01 == "y:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.Y = L_Numbering(Temp01); continue;}
           if(Temp01 == "vaction:")                  {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.VictimFrame = L_Numbering(Temp01); continue;}
           if(Temp01 == "aaction:")                  {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.InputA = L_Numbering(Temp01); continue;}
           if(Temp01 == "daction:")                  {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.InputD = L_Numbering(Temp01); continue;}
           if(Temp01 == "jaction:")                  {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.InputJ = L_Numbering(Temp01); continue;}
           if(Temp01 == "taction:")                  {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.InputThrow = L_Numbering(Temp01); continue;}
           if(Temp01 == "throwvx:")                  {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.ThrowVelX = L_Numbering(Temp01); continue;}
           if(Temp01 == "throwvy:")                  {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.ThrowVelY = L_Numbering(Temp01); continue;}
           if(Temp01 == "throwvz:")                  {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.ThrowVelZ = L_Numbering(Temp01); continue;}
           if(Temp01 == "throwinjury:")              {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.ThrowDamage = L_Numbering(Temp01); continue;}
           if(Temp01 == "dircontrol:")               {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.Control = L_Numbering(Temp01); continue;}
           if(Temp01 == "hurtable:")                 {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.Hurtable = L_Numbering(Temp01); continue;}
           if(Temp01 == "decrease:")                 {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.Decrease = L_Numbering(Temp01); continue;}
           if(Temp01 == "cover:")                    {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.Z = L_Numbering(Temp01); continue;}
           if(Temp01 == "injury:")                   {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.Damage = L_Numbering(Temp01); continue;}
           if(Temp01 == "fronthurtact:")             {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.FrontHurtAction = L_Numbering(Temp01); continue;}
           if(Temp01 == "backhurtact:")              {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Cpoint.BackHurtAction = L_Numbering(Temp01); continue;}
          break;
          case 6:
           if(Temp01 == "wpoint_end:")               {Vrab02 = 3; continue;}
           if(Temp01 == "kind:")                     {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Wpoint.Type = L_Numbering(Temp01); continue;}
           if(Temp01 == "x:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Wpoint.X = L_Numbering(Temp01); continue;}
           if(Temp01 == "y:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Wpoint.Y = L_Numbering(Temp01); continue;}
           if(Temp01 == "dvx:")                      {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Wpoint.XVelocityThrow = L_Numbering(Temp01); continue;}
           if(Temp01 == "dvy:")                      {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Wpoint.YVelocityThrow = L_Numbering(Temp01); continue;}
           if(Temp01 == "dvz:")                      {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Wpoint.ZVelocityThrow = L_Numbering(Temp01); continue;}
           if(Temp01 == "weaponact:")                {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Wpoint.WeaponFrame = L_Numbering(Temp01); continue;}
           if(Temp01 == "attacking:")                {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Wpoint.Strength = L_Numbering(Temp01); continue;}
           if(Temp01 == "cover:")                    {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Wpoint.Z = L_Numbering(Temp01); continue;}
          break;
          case 7:
           if(Temp01 == "opoint_end:")               {Vrab02 = 3; continue;}
           if(Temp01 == "kind:")                     {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Opoint[Vrab05].Type = L_Numbering(Temp01); continue;}
           if(Temp01 == "x:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Opoint[Vrab05].X = L_Numbering(Temp01); continue;}
           if(Temp01 == "y:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Opoint[Vrab05].Y = L_Numbering(Temp01); continue;}
           if(Temp01 == "dvx:")                      {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Opoint[Vrab05].XVelocity = L_Numbering(Temp01); continue;}
           if(Temp01 == "dvy:")                      {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Opoint[Vrab05].YVelocity = L_Numbering(Temp01); continue;}
           if(Temp01 == "oid:")                      {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Opoint[Vrab05].ID = L_Numbering(Temp01); continue;}
           if(Temp01 == "action:")                   {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Opoint[Vrab05].Frame = L_Numbering(Temp01); continue;}
           if(Temp01 == "facing:")                   {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Opoint[Vrab05].Condition = L_Numbering(Temp01); continue;}
          break;
          case 8: case 10: case 11:
           if(Temp01 == "itr_end:")                  {Vrab02 = 3; continue;}
           if(Temp01 == "kind:")                     {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].Type = L_Numbering(Temp01); continue;}
           if(Temp01 == "x:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].X = L_Numbering(Temp01); continue;}
           if(Temp01 == "y:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].Y = L_Numbering(Temp01); continue;}
           if(Temp01 == "w:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].Width = ruint32(L_Numbering(Temp01)); continue;}
           if(Temp01 == "h:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].Height = ruint32(L_Numbering(Temp01)); continue;}
           if(Temp01 == "zwidth:")                   {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].ZWidth = ruint32(L_Numbering(Temp01)); continue;}
           if(Temp01 == "dvx:")                      {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].XVelocity = L_Numbering(Temp01); continue;}
           if(Temp01 == "dvy:")                      {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].YVelocity = L_Numbering(Temp01); continue;}
           if(Temp01 == "fall:")                     {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].HitEffect = L_Numbering(Temp01); continue;}
           if(Temp01 == "arest:")                    {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].AttackerRefresh = L_Numbering(Temp01); continue;}
           if(Temp01 == "vrest:")                    {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].VictimRefresh = L_Numbering(Temp01); continue;}
           if(Temp01 == "respond:")                  {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].HitRespond = L_Numbering(Temp01); continue;}
           if(Temp01 == "effect:")                   {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].Effect = L_Numbering(Temp01); continue;}
           if(Temp01 == "bdefend:")                  {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].Power = L_Numbering(Temp01); continue;}
           if(Temp01 == "injury:")                   {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].Damage = L_Numbering(Temp01); continue;}
           if(Temp01 == "catchingact:")              {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].CatchRespond[0] = L_Numbering(Temp01); Vrab02 = 10; continue;}
           if(Temp01 == "caughtact:")                {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].CaughtRespond[0] = L_Numbering(Temp01); Vrab02 = 11; continue;}
           if(Vrab02 == 10){Vrab02 = 8; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].CatchRespond[1] = L_Numbering(Temp01); continue;}
           if(Vrab02 == 11){Vrab02 = 8; Data0001[Vrab01].Frame[Vrab04].Ipoint[Vrab05].CaughtRespond[1] = L_Numbering(Temp01); continue;}
          break;
          case 9:
           if(Temp01 == "bdy_end:")                  {Vrab02 = 3; continue;}
           if(Temp01 == "kind:")                     {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Hpoint[Vrab05].Type = L_Numbering(Temp01); continue;}
           if(Temp01 == "x:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Hpoint[Vrab05].X = L_Numbering(Temp01); continue;}
           if(Temp01 == "y:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Hpoint[Vrab05].Y = L_Numbering(Temp01); continue;}
           if(Temp01 == "w:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Hpoint[Vrab05].Width = ruint32(L_Numbering(Temp01)); continue;}
           if(Temp01 == "h:")                        {File0001 >> Temp01; Data0001[Vrab01].Frame[Vrab04].Hpoint[Vrab05].Height = ruint32(L_Numbering(Temp01)); continue;}
          break;
          default: break;
         }
         if(Vrab96 > 1)
         {
          Vrab96 -= 1;
          #ifdef DEBUG_VERSION
	       #ifdef MULTI_STATE
            if(Config.AI_Console)
            {
           #endif
           Base.Engi0002->WriteMessage(Data0001[Vrab01].Address.c_str(), 0, 0, asMSGTYPE_WARNING, ("Unknown syntax, \"" + Temp01 + "\", found.").c_str());
          #endif
          #ifdef MULTI_STATE
           }
          #endif
         } else
         {
          if(Vrab96 == 0) continue;
          Vrab96 -= 1;
          #ifdef DEBUG_VERSION
	       #ifdef MULTI_STATE
            if(Config.AI_Console)
            {
           #endif
           Base.Engi0002->WriteMessage(Data0001[Vrab01].Address.c_str(), 0, 0, asMSGTYPE_WARNING, "Too many unknown syntax. (unknown syntax won't be wrote!)");
          #endif
          #ifdef MULTI_STATE
           }
          #endif
         }
        }
       }
       if(File0001.is_open()) File0001.close(); if(File0002.is_open()) File0002.close();
       {
       	uint32 Vrab02 = 0; int1 Vrab04 = false; const uint32 Vrab05 = Data0001.size();
        while(Vrab02 != Vrab05)
        {
         if(Data0001[Vrab02].ID == ruint32(Database.InjectorID)) goto Labl0012;
         if(Data0001[Vrab02].Type == 0)
         {
          uint32 Vrab03 = 0; const uint32 Vrab06 = Data0001[Vrab02].Frame.size();
          if(Config.MOD_ResultFraming)
          {
           while(Data0001[Vrab02].Frame[Vrab03].Number != 0){Vrab03 += 1; if(Vrab03 == Vrab06){Vrab04 = true; goto Labl0012;}}
          } else
          {
           std::vector < int1 > Vect01; Vect01.resize(MaximumFrames);
           for(uint32 Vrab07 = 0; Vrab07 < Vrab06; ++Vrab07) Vect01[Data0001[Vrab02].Frame[Vrab07].Number] = true;
           while(Vect01[Vrab03]){Vrab03 += 1; if(Vrab03 == MaximumFrames){Vrab04 = true; goto Labl0012;}}
           const uint32 Vrab08 = Data0001[Vrab02].Frame.size(); Data0001[Vrab02].Frame.resize(Vrab08 + 1);
           Data0001[Vrab02].Frame[Vrab08].Number = Vrab03; Vrab03 = Vrab08;
          }
          int1 Vrab07 = false; uint32 Vrab09 = 0;
          if(Config.MOD_ResultFraming){Vrab07 = Data0001[Vrab02].Frame[Config.MOD_ModulingLevelStartingFrame].Number != 0; Vrab09 = Config.MOD_ModulingLevelStartingFrame;} else
          {
           for(uint32 Vrab08 = 0; Vrab08 < Vrab06; ++Vrab08) if(Data0001[Vrab02].Frame[Vrab08].Number == ruint32(Config.MOD_ModulingLevelStartingFrame)){Vrab09 = Vrab08; Vrab07 = true; break;}
          }
          if(Vrab07)
          {
           if(Data0001[Vrab02].Frame[Vrab09].Wait <= 0){Vrab04 = true; goto Labl0012;}
           if(Config.MOD_ResultFraming) Data0001[Vrab02].Frame[Vrab03].Number = ruint32(-1);
           Data0001[Vrab02].Frame[Vrab03].Wait = Data0001[Vrab02].Frame[Vrab09].Wait - 1;
           Data0001[Vrab02].Frame[Vrab09].Wait = 0;
           Data0001[Vrab02].Frame[Vrab03].Next = Data0001[Vrab02].Frame[Vrab09].Next;
           if(Config.MOD_ResultFraming){Data0001[Vrab02].Frame[Vrab09].Next = Vrab03;} else {Data0001[Vrab02].Frame[Vrab09].Next = Data0001[Vrab02].Frame[Vrab03].Number;}
           Data0001[Vrab02].Frame[Vrab03].CenterX = Data0001[Vrab02].Frame[Vrab09].CenterX;
           Data0001[Vrab02].Frame[Vrab03].CenterY = Data0001[Vrab02].Frame[Vrab09].CenterY;
           uint32 Vrab10 = Data0001[Vrab02].Frame[Vrab09].Opoint.size(); Data0001[Vrab02].Frame[Vrab03].Opoint.resize(Vrab10);
           while(Vrab10 > 0)
           {
            Vrab10 -= 1;
            Data0001[Vrab02].Frame[Vrab03].Opoint[Vrab10] = Data0001[Vrab02].Frame[Vrab09].Opoint[Vrab10];
           }
           Vrab10 = Data0001[Vrab02].Frame[Vrab03].Opoint.size(); Data0001[Vrab02].Frame[Vrab03].Opoint.resize(Vrab10 + 1);
           Data0001[Vrab02].Frame[Vrab03].Opoint[Vrab10].Type = 1;
           Data0001[Vrab02].Frame[Vrab03].Opoint[Vrab10].X = Data0001[Vrab02].Frame[Vrab03].CenterX;
           Data0001[Vrab02].Frame[Vrab03].Opoint[Vrab10].Y = Data0001[Vrab02].Frame[Vrab03].CenterY;
           Data0001[Vrab02].Frame[Vrab03].Opoint[Vrab10].ID = Database.InjectorID;
           Data0001[Vrab02].Frame[Vrab03].Opoint[Vrab10].Frame = 0;
           Data0001[Vrab02].Frame[Vrab03].Opoint[Vrab10].Condition = 10;
           Data0001[Vrab02].Frame[Vrab03].Name = Data0001[Vrab02].Frame[Vrab09].Name;
           Data0001[Vrab02].Frame[Vrab03].Picture = Data0001[Vrab02].Frame[Vrab09].Picture;
           Data0001[Vrab02].Frame[Vrab03].State = Data0001[Vrab02].Frame[Vrab09].State;
           Data0001[Vrab02].Frame[Vrab03].MPManage = Data0001[Vrab02].Frame[Vrab09].MPManage;
           Data0001[Vrab02].Frame[Vrab03].InputA = Data0001[Vrab02].Frame[Vrab09].InputA;
           Data0001[Vrab02].Frame[Vrab03].InputD = Data0001[Vrab02].Frame[Vrab09].InputD;
           Data0001[Vrab02].Frame[Vrab03].InputJ = Data0001[Vrab02].Frame[Vrab09].InputJ;
           Data0001[Vrab02].Frame[Vrab03].InputDFA = Data0001[Vrab02].Frame[Vrab09].InputDFA;
           Data0001[Vrab02].Frame[Vrab03].InputDFJ = Data0001[Vrab02].Frame[Vrab09].InputDFJ;
           Data0001[Vrab02].Frame[Vrab03].InputDDA = Data0001[Vrab02].Frame[Vrab09].InputDDA;
           Data0001[Vrab02].Frame[Vrab03].InputDDJ = Data0001[Vrab02].Frame[Vrab09].InputDDJ;
           Data0001[Vrab02].Frame[Vrab03].InputDUA = Data0001[Vrab02].Frame[Vrab09].InputDUA;
           Data0001[Vrab02].Frame[Vrab03].InputDUJ = Data0001[Vrab02].Frame[Vrab09].InputDUJ;
           Data0001[Vrab02].Frame[Vrab03].InputDJA = Data0001[Vrab02].Frame[Vrab09].InputDJA;
           Vrab10 = Data0001[Vrab02].Frame[Vrab09].Hpoint.size(); Data0001[Vrab02].Frame[Vrab03].Hpoint.resize(Vrab10);
           while(Vrab10 > 0)
           {
            Vrab10 -= 1;
            Data0001[Vrab02].Frame[Vrab03].Hpoint[Vrab10] = Data0001[Vrab02].Frame[Vrab09].Hpoint[Vrab10];
           }
           Vrab10 = Data0001[Vrab02].Frame[Vrab09].Ipoint.size(); Data0001[Vrab02].Frame[Vrab03].Ipoint.resize(Vrab10);
           while(Vrab10 > 0)
           {
            Vrab10 -= 1;
            Data0001[Vrab02].Frame[Vrab03].Ipoint[Vrab10] = Data0001[Vrab02].Frame[Vrab09].Ipoint[Vrab10];
           }
           Data0001[Vrab02].Frame[Vrab03].Wpoint = Data0001[Vrab02].Frame[Vrab09].Wpoint;
           Data0001[Vrab02].Frame[Vrab03].Cpoint = Data0001[Vrab02].Frame[Vrab09].Cpoint;
           Data0001[Vrab02].Frame[Vrab03].Bpoint = Data0001[Vrab02].Frame[Vrab09].Bpoint;
          } else {Vrab04 = true;}
         }
         Labl0012:
	     Vrab02 += 1;
        }
        if(Vrab01)
	    {
	  
        }  
       }
      } else {Config.MOD_ModulingLevel = 1;}
     }
     const uint32 Vrab02 = Strn0001.size();
     for(uint32 Vrab01 = 0; Vrab01 < Vrab02; ++Vrab01)
     {
      if(Strn0001[Vrab01] == "") continue;
      Base.ModuleID = Vect0001[Vrab01];
      const string Temp01 = "Mod_" + std::to_string(Vrab01);
      asIScriptFunction *Func01 = Base.Engi0002->GetModule(Temp01.c_str())->GetFunctionByDecl("void core()");
      if(Func01)
      {
       if(Base.Cont0002->Prepare(Func01) < 0)
	   {
	    #ifdef DEBUG_VERSION
	     #ifdef MULTI_STATE
          if(Config.AI_Console)
          {
         #endif
	     Base.Engi0002->WriteMessage(Strn0001[Vrab01].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
	    #endif
	    #ifdef MULTI_STATE
         }
        #endif
	    continue;
	   }
	   if(Base.Cont0002->Execute() < 0)
	   {
	    #ifdef DEBUG_VERSION
	     #ifdef MULTI_STATE
          if(Config.AI_Console)
          {
         #endif
	     Base.Engi0002->WriteMessage(Strn0001[Vrab01].c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
	    #endif
	    #ifdef MULTI_STATE
         }
        #endif
	    continue;
       }
      }
     }
     if(Config.MOD_ModulingLevel > 1)
     {
      if(L_Create(Config.ECD_InstallDataDirectory))
      {
       File0002 << "<object>\n";
       uint32 Vrab01 = 0; const uint32 Vrab05 = Data0001.size();
       while(Vrab01 != Vrab05)
       {
        std::ofstream File01;
        #ifdef DEBUG_VERSION
	     #ifdef MULTI_STATE
          if(Config.AI_Console)
          {
         #endif
         std::cout << "() INFO - Rewrite \"" + Data0001[Vrab01].Address + "\" as ";
        #endif
        #ifdef MULTI_STATE
         }
        #endif
        uint32 Vrab03 = Data0001[Vrab01].Address.size();
        while(Vrab03 > 0){Vrab03 -= 1; if(Data0001[Vrab01].Address.at(Vrab03) == '\\'){Vrab03 += 1; break;}}
        uint32 Vrab04 = Data0001[Vrab01].Address.size();
        while(Vrab04 > 0){Vrab04 -= 1; if(Data0001[Vrab01].Address.at(Vrab04) == '.') break;}
        Data0001[Vrab01].Address = Config.MOD_ResultDirectory + "\\" + string(Data0001[Vrab01].Address, Vrab03, Data0001[Vrab01].Address.size() - Vrab03 - (Data0001[Vrab01].Address.size() - Vrab04)) + "." + Config.MOD_ResultExtension;
        while(L_Exist(Data0001[Vrab01].Address)) L_Rename(Data0001[Vrab01].Address);
        #ifdef DEBUG_VERSION
	     #ifdef MULTI_STATE
          if(Config.AI_Console)
          {
         #endif
         std::cout << "\"" + Data0001[Vrab01].Address + "\".\n";
        #endif
        #ifdef MULTI_STATE
         }
        #endif
        File01.open(L_Execute(Data0001[Vrab01].Address), std::ios::binary | std::ios::out);
        if(File01.is_open())
        {
         File0002 << " id: " << Data0001[Vrab01].ID;
         if(Data0001[Vrab01].ID < 100) if(Data0001[Vrab01].ID < 10) {File0002 << "  ";} else {File0002 << " ";}
         File0002 << " type: " << Data0001[Vrab01].Type << " file: " + Data0001[Vrab01].Address + "\n"; L_Summary(Data0001[Vrab01].Address + "\n");
         switch(Config.MOD_ResultFormat)
         {
          case 1:
           File01 << "<bmp_begin>\n";
          break;
          default:
           File01 << "<bmp_begin> ";
           if(Data0001[Vrab01].Main.Name != "") File01 << "name: " + Data0001[Vrab01].Main.Name + " ";
           if(Data0001[Vrab01].Main.Add_Head != "") File01 << "head: " + Data0001[Vrab01].Main.Add_Head + " ";
           if(Data0001[Vrab01].Main.Add_Small != "") File01 << "small: " + Data0001[Vrab01].Main.Add_Small + " ";
           {
            const uint32 Vrab06 = Data0001[Vrab01].Main.Pictures.size();
            uint32 Vrab07 = 0;
            while(Vrab07 != Vrab06)
            {
             File01 << "file(0-0): " + Data0001[Vrab01].Main.Pictures[Vrab07].Add_Address + " w: " << Data0001[Vrab01].Main.Pictures[Vrab07].Width << " h: " << Data0001[Vrab01].Main.Pictures[Vrab07].Height << " row: " << Data0001[Vrab01].Main.Pictures[Vrab07].Row << " col: " << Data0001[Vrab01].Main.Pictures[Vrab07].Column << " ";
             Vrab07 += 1;
            }
           }
           if(Data0001[Vrab01].Main.WalkAnimation != 0) File01 << "walking_frame_rate " << Data0001[Vrab01].Main.WalkAnimation << " ";
           if(Data0001[Vrab01].Main.RunAnimation != 0) File01 << "running_frame_rate " << Data0001[Vrab01].Main.RunAnimation << " ";
           if(Data0001[Vrab01].Main.Dob_WalkSpeed != "") File01 << "walking_speed " + Data0001[Vrab01].Main.Dob_WalkSpeed + " ";
           if(Data0001[Vrab01].Main.Dob_WalkSpeedZ != "") File01 << "walking_speedz " + Data0001[Vrab01].Main.Dob_WalkSpeedZ + " ";
           if(Data0001[Vrab01].Main.Dob_RunSpeed != "") File01 << "running_speed " + Data0001[Vrab01].Main.Dob_RunSpeed + " ";
           if(Data0001[Vrab01].Main.Dob_RunSpeedZ != "") File01 << "running_speedz " + Data0001[Vrab01].Main.Dob_RunSpeedZ + " ";
           if(Data0001[Vrab01].Main.Dob_HeavyWalkSpeed != "") File01 << "heavy_walking_speed " + Data0001[Vrab01].Main.Dob_HeavyWalkSpeed + " ";
           if(Data0001[Vrab01].Main.Dob_HeavyWalkSpeedZ != "") File01 << "heavy_walking_speedz " + Data0001[Vrab01].Main.Dob_HeavyWalkSpeedZ + " ";
           if(Data0001[Vrab01].Main.Dob_HeavyRunSpeed != "") File01 << "heavy_running_speed " + Data0001[Vrab01].Main.Dob_HeavyRunSpeed + " ";
           if(Data0001[Vrab01].Main.Dob_HeavyRunSpeedZ != "") File01 << "heavy_running_speedz " + Data0001[Vrab01].Main.Dob_HeavyRunSpeedZ + " ";
           if(Data0001[Vrab01].Main.Dob_JumpHeight != "") File01 << "jump_height " + Data0001[Vrab01].Main.Dob_JumpHeight + " ";
           if(Data0001[Vrab01].Main.Dob_JumpSpeed != "") File01 << "jump_distance " + Data0001[Vrab01].Main.Dob_JumpSpeed + " ";
           if(Data0001[Vrab01].Main.Dob_JumpSpeedZ != "") File01 << "jump_distancez " + Data0001[Vrab01].Main.Dob_JumpSpeedZ + " ";
           if(Data0001[Vrab01].Main.Dob_DashHeight != "") File01 << "dash_height " + Data0001[Vrab01].Main.Dob_DashHeight + " ";
           if(Data0001[Vrab01].Main.Dob_DashSpeed != "") File01 << "dash_distance " + Data0001[Vrab01].Main.Dob_DashSpeed + " ";
           if(Data0001[Vrab01].Main.Dob_DashSpeedZ != "") File01 << "dash_distancez " + Data0001[Vrab01].Main.Dob_DashSpeedZ + " ";
           if(Data0001[Vrab01].Main.Dob_FlipHeight != "") File01 << "rowing_height " + Data0001[Vrab01].Main.Dob_FlipHeight + " ";
           if(Data0001[Vrab01].Main.Dob_FlipSpeed != "") File01 << "rowing_distance " + Data0001[Vrab01].Main.Dob_FlipSpeed + " ";
           if(Data0001[Vrab01].Main.StartingHealth != 0) File01 << "weapon_hp: " << Data0001[Vrab01].Main.StartingHealth << " ";
           if(Data0001[Vrab01].Main.LandingHurt != 0) File01 << "weapon_drop_hurt: " << Data0001[Vrab01].Main.LandingHurt << " ";
           if(Data0001[Vrab01].Main.Add_HitSound != "") File01 << "weapon_hit_sound: " + Data0001[Vrab01].Main.Add_HitSound + " ";
           if(Data0001[Vrab01].Main.Add_LandingSound != "") File01 << "weapon_drop_sound: " + Data0001[Vrab01].Main.Add_LandingSound + " ";
           if(Data0001[Vrab01].Main.Add_BreakSound != "") File01 << "weapon_broken_sound: " + Data0001[Vrab01].Main.Add_BreakSound + " ";
           File01 << "<bmp_end> ";
           {
            int1 Vrab06 = true;
            const uint32 Vrab07 = Data0001[Vrab01].Strength.size();
            uint32 Vrab08 = 0;
            while(Vrab08 != Vrab07)
            {
             if(Vrab06){File01 << "<weapon_strength_list> "; Vrab06 = false;}
             File01 << "entry: " << Vrab08 + 1 << " " + Data0001[Vrab01].Strength[Vrab08].Name + " ";
             if(Data0001[Vrab01].Strength[Vrab08].ZWidth != 0) File01 << "zwidth: " << Data0001[Vrab01].Strength[Vrab08].ZWidth << " ";
             if(Data0001[Vrab01].Strength[Vrab08].AttackerRefresh != 0) File01 << "arest: " << Data0001[Vrab01].Strength[Vrab08].AttackerRefresh << " ";
             if(Data0001[Vrab01].Strength[Vrab08].VictimRefresh != 0) File01 << "vrest: " << Data0001[Vrab01].Strength[Vrab08].VictimRefresh << " ";
             if(Data0001[Vrab01].Strength[Vrab08].XVelocity != 0) File01 << "dvx: " << Data0001[Vrab01].Strength[Vrab08].XVelocity << " ";
             if(Data0001[Vrab01].Strength[Vrab08].YVelocity != 0) File01 << "dvy: " << Data0001[Vrab01].Strength[Vrab08].YVelocity << " ";
             if(Data0001[Vrab01].Strength[Vrab08].Power != 0) File01 << "bdefend: " << Data0001[Vrab01].Strength[Vrab08].Power << " ";
             if(Data0001[Vrab01].Strength[Vrab08].Effect != 0) File01 << "effect: " << Data0001[Vrab01].Strength[Vrab08].Effect << " ";
             if(Data0001[Vrab01].Strength[Vrab08].Damage != 0) File01 << "injury: " << Data0001[Vrab01].Strength[Vrab08].Damage << " ";
             if(Data0001[Vrab01].Strength[Vrab08].HitEffect != 0) File01 << "fall: " << Data0001[Vrab01].Strength[Vrab08].HitEffect << " ";
             if(Data0001[Vrab01].Strength[Vrab08].HitRespond != 0) File01 << "respond: " << Data0001[Vrab01].Strength[Vrab08].HitRespond << " ";
             Vrab08 += 1;
            }
            if(!Vrab06) File01 << "<weapon_strength_list_end> ";
           }
           {
            const uint32 Vrab06 = Data0001[Vrab01].Frame.size();
            uint32 Vrab07 = 0;
            while(Vrab07 != Vrab06)
            {
             if(Config.MOD_ResultFraming)
             {
              if(Data0001[Vrab01].Frame[Vrab07].Number != ruint32(-1)) continue;
              File01 << "<frame> " << Vrab07 << " " + Data0001[Vrab01].Frame[Vrab07].Name + " ";
             } else
             {
              File01 << "<frame> " << Data0001[Vrab01].Frame[Vrab07].Number << " " + Data0001[Vrab01].Frame[Vrab07].Name + " ";
             }
             
             if(Data0001[Vrab01].Frame[Vrab07].Picture != 0) File01 << "pic: " << Data0001[Vrab01].Frame[Vrab07].Picture << " ";
             if(Data0001[Vrab01].Frame[Vrab07].State != 0) File01 << "state: " << Data0001[Vrab01].Frame[Vrab07].State << " ";
             if(Data0001[Vrab01].Frame[Vrab07].Wait != 0) File01 << "wait: " << Data0001[Vrab01].Frame[Vrab07].Wait << " ";
             if(Data0001[Vrab01].Frame[Vrab07].Next != 0) File01 << "next: " << Data0001[Vrab01].Frame[Vrab07].Next << " ";
             if(Data0001[Vrab01].Frame[Vrab07].CenterX != 0) File01 << "centerx: " << Data0001[Vrab01].Frame[Vrab07].CenterX << " ";
             if(Data0001[Vrab01].Frame[Vrab07].CenterY != 0) File01 << "centery: " << Data0001[Vrab01].Frame[Vrab07].CenterY << " ";
             if(Data0001[Vrab01].Frame[Vrab07].XVelocity != 0) File01 << "dvx: " << Data0001[Vrab01].Frame[Vrab07].XVelocity << " ";
             if(Data0001[Vrab01].Frame[Vrab07].YVelocity != 0) File01 << "dvy: " << Data0001[Vrab01].Frame[Vrab07].YVelocity << " ";
             if(Data0001[Vrab01].Frame[Vrab07].ZVelocity != 0) File01 << "dvz: " << Data0001[Vrab01].Frame[Vrab07].ZVelocity << " ";
             if(Data0001[Vrab01].Frame[Vrab07].InputA != 0) File01 << "hit_a: " << Data0001[Vrab01].Frame[Vrab07].InputA << " ";
             if(Data0001[Vrab01].Frame[Vrab07].InputD != 0) File01 << "hit_d: " << Data0001[Vrab01].Frame[Vrab07].InputD << " ";
             if(Data0001[Vrab01].Frame[Vrab07].InputJ != 0) File01 << "hit_j: " << Data0001[Vrab01].Frame[Vrab07].InputJ << " ";
             if(Data0001[Vrab01].Frame[Vrab07].InputDFA != 0) File01 << "hit_Fa: " << Data0001[Vrab01].Frame[Vrab07].InputDFA << " ";
             if(Data0001[Vrab01].Frame[Vrab07].InputDFJ != 0) File01 << "hit_Fj: " << Data0001[Vrab01].Frame[Vrab07].InputDFJ << " ";
             if(Data0001[Vrab01].Frame[Vrab07].InputDDA != 0) File01 << "hit_Da: " << Data0001[Vrab01].Frame[Vrab07].InputDDA << " ";
             if(Data0001[Vrab01].Frame[Vrab07].InputDDJ != 0) File01 << "hit_Dj: " << Data0001[Vrab01].Frame[Vrab07].InputDDJ << " ";
             if(Data0001[Vrab01].Frame[Vrab07].InputDUA != 0) File01 << "hit_Ua: " << Data0001[Vrab01].Frame[Vrab07].InputDUA << " ";
             if(Data0001[Vrab01].Frame[Vrab07].InputDUJ != 0) File01 << "hit_Uj: " << Data0001[Vrab01].Frame[Vrab07].InputDUJ << " ";
             if(Data0001[Vrab01].Frame[Vrab07].InputDJA != 0) File01 << "hit_ja: " << Data0001[Vrab01].Frame[Vrab07].InputDJA << " ";
             if(Data0001[Vrab01].Frame[Vrab07].MPManage != 0) File01 << "mp: " << Data0001[Vrab01].Frame[Vrab07].MPManage << " ";
             if(Data0001[Vrab01].Frame[Vrab07].Add_SoundEffect != "") File01 << "sound: " + Data0001[Vrab01].Frame[Vrab07].Add_SoundEffect + " ";

             if(Data0001[Vrab01].Frame[Vrab07].Bpoint.X != 0 || Data0001[Vrab01].Frame[Vrab07].Bpoint.Y != 0) File01 << "bpoint: x: " << Data0001[Vrab01].Frame[Vrab07].Bpoint.X << " y: " << Data0001[Vrab01].Frame[Vrab07].Bpoint.Y << " bpoint_end: ";

             {
              int1 Vrab08 = true;
              uint32 Vrab09 = 0;
              while(Vrab09 <= 18)
              {
               int1 Vrab10 = false;
               switch(Vrab09)
               {
                case 0: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.Type != 0) Vrab10 = true; break;
                case 1: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.X != 0) Vrab10 = true; break;
                case 2: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.Y != 0) Vrab10 = true; break;
                case 3: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.VictimFrame != 0) Vrab10 = true; break;
                case 4: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.InputA != 0) Vrab10 = true; break;
                case 5: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.InputD != 0) Vrab10 = true; break;
                case 6: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.InputJ != 0) Vrab10 = true; break;
                case 7: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.InputThrow != 0) Vrab10 = true; break;
                case 8: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.ThrowVelX != 0) Vrab10 = true; break;
                case 9: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.ThrowVelY != 0) Vrab10 = true; break;
                case 10: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.ThrowVelZ != 0) Vrab10 = true; break;
                case 11: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.ThrowDamage != 0) Vrab10 = true; break;
                case 12: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.Z != 0) Vrab10 = true; break;
                case 13: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.Damage != 0) Vrab10 = true; break;
                case 14: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.Control != 0) Vrab10 = true; break;
                case 15: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.Decrease != 0) Vrab10 = true; break;
                case 16: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.Hurtable != 0) Vrab10 = true; break;
                case 17: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.FrontHurtAction != 0) Vrab10 = true; break;
                default: if(Data0001[Vrab01].Frame[Vrab07].Cpoint.BackHurtAction != 0) Vrab10 = true; break;
               }
               if(Vrab10)
               {
                if(Vrab08){File01 << "cpoint: "; Vrab08 = false;}
                switch(Vrab09)
                {
                 case 0: File01 << "kind: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.Type; break;
                 case 1: File01 << "x: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.X; break;
                 case 2: File01 << "y: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.Y; break;
                 case 3: File01 << "vaction: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.VictimFrame; break;
                 case 4: File01 << "aaction: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.InputA; break;
                 case 5: File01 << "daction: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.InputD; break;
                 case 6: File01 << "jaction: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.InputJ; break;
                 case 7: File01 << "taction: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.InputThrow; break;
                 case 8: File01 << "throwvx: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.ThrowVelX; break;
                 case 9: File01 << "throwvy: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.ThrowVelY; break;
                 case 10: File01 << "throwvz: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.ThrowVelZ; break;
                 case 11: File01 << "throwinjury: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.ThrowDamage; break;
                 case 12: File01 << "cover: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.Z; break;
                 case 13: File01 << "injury: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.Damage; break;
                 case 14: File01 << "dircontrol: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.Control; break;
                 case 15: File01 << "decrease: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.Decrease; break;
                 case 16: File01 << "hurtable: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.Hurtable; break;
                 case 17: File01 << "fronthurtact: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.FrontHurtAction; break;
                 default: File01 << "backhurtact: " << Data0001[Vrab01].Frame[Vrab07].Cpoint.BackHurtAction; break;
                }
                File01 << " ";
               }
               Vrab09 += 1;
              }
              if(!Vrab08) File01 << "cpoint_end: ";
             }

             {
              int1 Vrab08 = true;
              uint32 Vrab09 = 0;
              while(Vrab09 <= 8)
              {
               int1 Vrab10 = false;
               switch(Vrab09)
               {
                case 0: if(Data0001[Vrab01].Frame[Vrab07].Wpoint.Type != 0) Vrab10 = true; break;
                case 1: if(Data0001[Vrab01].Frame[Vrab07].Wpoint.X != 0) Vrab10 = true; break;
                case 2: if(Data0001[Vrab01].Frame[Vrab07].Wpoint.Y != 0) Vrab10 = true; break;
                case 3: if(Data0001[Vrab01].Frame[Vrab07].Wpoint.WeaponFrame != 0) Vrab10 = true; break;
                case 4: if(Data0001[Vrab01].Frame[Vrab07].Wpoint.Strength != 0) Vrab10 = true; break;
                case 5: if(Data0001[Vrab01].Frame[Vrab07].Wpoint.Z != 0) Vrab10 = true; break;
                case 6: if(Data0001[Vrab01].Frame[Vrab07].Wpoint.XVelocityThrow != 0) Vrab10 = true; break;
                case 7: if(Data0001[Vrab01].Frame[Vrab07].Wpoint.YVelocityThrow != 0) Vrab10 = true; break;
                default: if(Data0001[Vrab01].Frame[Vrab07].Wpoint.ZVelocityThrow != 0) Vrab10 = true; break;
               }
               if(Vrab10)
               {
                if(Vrab08){File01 << "wpoint: "; Vrab08 = false;}
                switch(Vrab09)
                {
                 case 0: File01 << "kind: " << Data0001[Vrab01].Frame[Vrab07].Wpoint.Type; break;
                 case 1: File01 << "x: " << Data0001[Vrab01].Frame[Vrab07].Wpoint.X; break;
                 case 2: File01 << "y: " << Data0001[Vrab01].Frame[Vrab07].Wpoint.Y; break;
                 case 3: File01 << "weaponact: " << Data0001[Vrab01].Frame[Vrab07].Wpoint.WeaponFrame; break;
                 case 4: File01 << "attacking: " << Data0001[Vrab01].Frame[Vrab07].Wpoint.Strength; break;
                 case 5: File01 << "cover: " << Data0001[Vrab01].Frame[Vrab07].Wpoint.Z; break;
                 case 6: File01 << "dvx: " << Data0001[Vrab01].Frame[Vrab07].Wpoint.XVelocityThrow; break;
                 case 7: File01 << "dvy: " << Data0001[Vrab01].Frame[Vrab07].Wpoint.YVelocityThrow; break;
                 default: File01 << "dvz: " << Data0001[Vrab01].Frame[Vrab07].Wpoint.ZVelocityThrow; break;
                }
                File01 << " ";
               }
               Vrab09 += 1;
              }
              if(!Vrab08) File01 << "wpoint_end: ";
             }

             {
              const uint32 Vrab08 = Data0001[Vrab01].Frame[Vrab07].Opoint.size();
              uint32 Vrab09 = 0;
              while(Vrab09 != Vrab08)
              {
               File01 << "opoint: ";
               if(Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].Type != 0) File01 << "kind: " << Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].Type << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].X != 0) File01 << "x: " << Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].X << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].Y != 0) File01 << "y: " << Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].Y << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].ID != 0) File01 << "oid: " << Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].ID << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].Frame != 0) File01 << "action: " << Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].Frame << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].Condition != 0) File01 << "facing: " << Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].Condition << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].XVelocity != 0) File01 << "dvx: " << Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].XVelocity << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].YVelocity != 0) File01 << "dvy: " << Data0001[Vrab01].Frame[Vrab07].Opoint[Vrab09].YVelocity << " ";
               File01 << "opoint_end: ";
               Vrab09 += 1;
              }
             }

             {
              const uint32 Vrab08 = Data0001[Vrab01].Frame[Vrab07].Ipoint.size();
              uint32 Vrab09 = 0;
              while(Vrab09 != Vrab08)
              {
               File01 << "itr: ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Type != 0) File01 << "kind: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Type << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].X != 0) File01 << "x: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].X << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Y != 0) File01 << "y: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Y << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Width != 0) File01 << "w: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Width << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Height != 0) File01 << "h: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Height << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].ZWidth != 0) File01 << "zwidth: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].ZWidth << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].AttackerRefresh != 0) File01 << "arest: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].AttackerRefresh << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].VictimRefresh != 0) File01 << "vrest: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].VictimRefresh << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Power != 0) File01 << "bdefend: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Power << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Damage != 0) File01 << "injury: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Damage << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Effect != 0) File01 << "effect: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].Effect << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].HitEffect != 0) File01 << "fall: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].HitEffect << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].HitRespond != 0) File01 << "respond: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].HitRespond << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].XVelocity != 0) File01 << "dvx: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].XVelocity << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].YVelocity != 0) File01 << "dvy: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].YVelocity << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].CatchRespond[0] != 0) File01 << "catchingact: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].CatchRespond[0] << " " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].CatchRespond[1] << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].CaughtRespond[0] != 0) File01 << "caughtact: " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].CaughtRespond[0] << " " << Data0001[Vrab01].Frame[Vrab07].Ipoint[Vrab09].CaughtRespond[1] << " ";
               File01 << "itr_end: ";
               Vrab09 += 1;
              }
             }

             {
              const uint32 Vrab08 = Data0001[Vrab01].Frame[Vrab07].Hpoint.size();
              uint32 Vrab09 = 0;
              while(Vrab09 != Vrab08)
              {
               File01 << "bdy: ";
               if(Data0001[Vrab01].Frame[Vrab07].Hpoint[Vrab09].Type != 0) File01 << "kind: " << Data0001[Vrab01].Frame[Vrab07].Hpoint[Vrab09].Type << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Hpoint[Vrab09].X != 0) File01 << "x: " << Data0001[Vrab01].Frame[Vrab07].Hpoint[Vrab09].X << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Hpoint[Vrab09].Y != 0) File01 << "y: " << Data0001[Vrab01].Frame[Vrab07].Hpoint[Vrab09].Y << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Hpoint[Vrab09].Width != 0) File01 << "w: " << Data0001[Vrab01].Frame[Vrab07].Hpoint[Vrab09].Width << " ";
               if(Data0001[Vrab01].Frame[Vrab07].Hpoint[Vrab09].Height != 0) File01 << "h: " << Data0001[Vrab01].Frame[Vrab07].Hpoint[Vrab09].Height << " ";
               File01 << "bdy_end: ";
               Vrab09 += 1;
              }
             }

             File01 << "<frame_end> ";
             Vrab07 += 1;
            }
           }
          break;
         }
         File01.close();
        }
        Vrab01 += 1;
       }
       File0002 << "<object_end>\n\n" + Temp99;
       File0002.close();
      }
      Data0001.clear();
      L_Polish();
     }
    }
   }
  //-//
 //-//
//-//