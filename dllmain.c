#include "framework.h"

#define TIMELINE_LENGTH 40

HIE_tdstSuperObject* rayman;
int inAirFrames = 0;
char timelineText[TIMELINE_LENGTH+1];

void CALLBACK MyTextCallback(SPTXT_tdstTextInfo* p_stString)
{
	p_stString->X = 10;
	p_stString->Y = 900;
	p_stString->xSize = 10.0f;
	p_stString->ucAlpha = 255;
	p_stString->bFrame = TRUE;

	AI_tdeDsgVarType dsgVarType;
	char* statePtr; // 11 or 13 for jump, 15 for flight

	rayman = HIE_fn_p_stFindObjectByName("rayman");

	if (AI_fn_bGetDsgVar(rayman, 9, &dsgVarType, &statePtr)) {

		char state = *statePtr;

		if (state == 11 || state == 13 || state == 15)
		{
			SPTXT_vPrintLine("ooooooooooooooooooooooooooo--o----------");

			if (inAirFrames < TIMELINE_LENGTH)
			{
				if (IPT_M_bActionIsValidated(IPT_E_Entry_Action_Sauter))
				{
					timelineText[inAirFrames] = 'o';
				}
				else
				{
					timelineText[inAirFrames] = '-';
				}

				timelineText[inAirFrames + 1] = '\0';
			}

			SPTXT_vPrintFmtLine("%s%s%s", TXT_Seq_Red, timelineText, TXT_Seq_Reset);
			inAirFrames++;
		} else {
			inAirFrames = 0;
			memset(&timelineText[0], '-', sizeof(timelineText));
			timelineText[TIMELINE_LENGTH] = '\0';
		}
	}
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	switch ( dwReason )
	{
		case DLL_PROCESS_ATTACH: /* create function hooks here */

			SPTXT_vInit();
			SPTXT_vAddTextCallback(MyTextCallback);
			break;

		case DLL_PROCESS_DETACH: /* destroy function hooks here*/
			SPTXT_vRemoveTextCallback(MyTextCallback);
			break;

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}
	return TRUE;
}
