#ifndef _GAMEARRAYS_H_
 #define _GAMEARRAYS_H_
 #include "sgame.h"
 #include "angelscript.h"

 struct CharArray {char *opIndex(unsigned int);};
 struct CharArrayArray {template < int size > CharArray *opIndex(unsigned int);};
 struct IntArray {int *opIndex(unsigned int);};
 struct BoolArray {bool *opIndex(unsigned int);};
 struct ItrArray {sItr *opIndex(unsigned int);};
 struct BdyArray {sBdy *opIndex(unsigned int);};
 struct DataFileArray {sDataFile *opIndex(unsigned int);};
 struct ObjectArray {sObject *opIndex(unsigned int);};
 struct FrameArray {sFrame *opIndex(unsigned int);};
 struct BackgroundArray {sBackground *opIndex(unsigned int);};
 struct SpawnArray {sSpawn *opIndex(unsigned int);};
 struct PhaseArray {sPhase *opIndex(unsigned int);};
 struct StageArray {sStage *opIndex(unsigned int);};

 void RegisterGameArrays(asIScriptEngine *, bool);
#endif