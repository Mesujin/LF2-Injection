#ifndef _GAMEARRAYS_H_
 #define _GAMEARRAYS_H_
 #include "sgame.h"
 #include "angelscript.h"

 struct CharArray {char opIndex(unsigned int x);};
 struct CharArrayArray {template < int size > CharArray *opIndex(unsigned int x);};
 struct IntArray {int opIndex(unsigned int x);};
 struct BoolArray {bool opIndex(unsigned int x);};
 struct ItrArray {sItr *opIndex(unsigned int x);};
 struct BdyArray {sBdy *opIndex(unsigned int x);};
 struct DataFileArray {sDataFile *opIndex(unsigned int x);};
 struct ObjectArray {sObject *opIndex(unsigned int x);};
 struct FrameArray {sFrame *opIndex(unsigned int x);};
 struct BackgroundArray {sBackground *opIndex(unsigned int x);};
 struct SpawnArray {sSpawn *opIndex(unsigned int x);};
 struct PhaseArray {sPhase *opIndex(unsigned int x);};
 struct StageArray {sStage *opIndex(unsigned int x);};

 void RegisterGameArrays(asIScriptEngine *ScriptEngine);
#endif