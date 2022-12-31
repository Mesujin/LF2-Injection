#ifndef _MD_GAMEARRAYS_H_DECL
 #define _MD_GAMEARRAYS_H_DECL
 #include "sgame.h"
 #include "angelscript.h"

 #ifdef _MD_OLD_SCRIPT
  struct CharArray       {char *opIndex(unsigned int) noexcept;};
  struct CharArrayArray  {template < int size > CharArray *opIndex(unsigned int) noexcept;};
  struct IntArray        {int *opIndex(unsigned int) noexcept;};
  struct BoolArray       {bool *opIndex(unsigned int) noexcept;};
  struct ItrArray        {sItr *opIndex(unsigned int) noexcept;};
  struct BdyArray        {sBdy *opIndex(unsigned int) noexcept;};
  struct DataFileArray   {sDataFile *opIndex(unsigned int) noexcept;};
  struct ObjectArray     {sObject *opIndex(unsigned int) noexcept;};
  struct FrameArray      {sFrame *opIndex(unsigned int) noexcept;};
  struct LayerArray      {sLayer *opIndex(unsigned int) noexcept;};
  struct BackgroundArray {sBackground *opIndex(unsigned int) noexcept;};
  struct SpawnArray      {sSpawn *opIndex(unsigned int) noexcept;};
  struct PhaseArray      {sPhase *opIndex(unsigned int) noexcept;};
  struct StageArray      {sStage *opIndex(unsigned int) noexcept;};
 #endif

 struct MD_ARRAY_INT1       {bool *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_INT8       {char *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_INT32      {int  *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_ARRAY_INT8 {template < int Vrab01 > MD_ARRAY_INT8 *opIndex(unsigned int) noexcept;};

 struct MD_ARRAY_OBJECT     {MD_OBJECT     *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_DATA       {MD_DATA       *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_FILE       {MD_FILE       *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_ENTRY      {MD_ENTRY      *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_FRAME      {MD_FRAME      *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_ITR        {MD_ITR        *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_BDY        {MD_BDY        *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_BACKGROUND {MD_BACKGROUND *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_LAYER      {MD_LAYER      *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_STAGE      {MD_STAGE      *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_PHASE      {MD_PHASE      *opIndex(unsigned int) noexcept;};
 struct MD_ARRAY_SPAWN      {MD_SPAWN      *opIndex(unsigned int) noexcept;};

 void RegisterGameArrays(asIScriptEngine *, bool);
#endif