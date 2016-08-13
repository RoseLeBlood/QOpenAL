#include "include/openalsoft.h"
bool isc = false;

#include <AL/alext.h>

LPALBUFFERSAMPLESSOFT alBufferSamplesSOFT;
LPALISBUFFERFORMATSUPPORTEDSOFT alIsBufferFormatSupportedSOFT;

LPALSOURCEDSOFT alSourcedSOFT;
LPALSOURCE3DSOFT alSource3dSOFT;
LPALSOURCEDVSOFT alSourcedvSOFT;
LPALGETSOURCEDSOFT alGetSourcedSOFT;
LPALGETSOURCE3DSOFT alGetSource3dSOFT;
LPALGETSOURCEDVSOFT alGetSourcedvSOFT;
LPALSOURCEI64SOFT alSourcei64SOFT;
 LPALSOURCE3I64SOFT alSource3i64SOFT;
LPALSOURCEI64VSOFT alSourcei64vSOFT;
LPALGETSOURCEI64SOFT alGetSourcei64SOFT;
 LPALGETSOURCE3I64SOFT alGetSource3i64SOFT;
LPALGETSOURCEI64VSOFT alGetSourcei64vSOFT;

void alCreateHelpers()
{
  if(isc) return ;

  /* Define a macro to help load the function pointers. */
#define LOAD_PROC(x,y)  ((x) = (y)alGetProcAddress(#x))
  LOAD_PROC(alSourcedSOFT, LPALSOURCEDSOFT);
  LOAD_PROC(alSource3dSOFT, LPALSOURCE3DSOFT);
  LOAD_PROC(alSourcedvSOFT, LPALSOURCEDVSOFT);
  /*LOAD_PROC(alGetSourcedSOFT);
  LOAD_PROC(alGetSource3dSOFT);
  LOAD_PROC(alGetSourcedvSOFT);
  LOAD_PROC(alSourcei64SOFT);
  LOAD_PROC(alSource3i64SOFT);
  LOAD_PROC(alSourcei64vSOFT);
  LOAD_PROC(alGetSourcei64SOFT);
  LOAD_PROC(alGetSource3i64SOFT);
  LOAD_PROC(alGetSourcei64vSOFT);

  if(alIsExtensionPresent("AL_SOFT_buffer_samples"))
  {
      LOAD_PROC(alBufferSamplesSOFT);
      LOAD_PROC(alIsBufferFormatSupportedSOFT);
  }
#undef LOAD_PROC*/

  isc = true;
}
