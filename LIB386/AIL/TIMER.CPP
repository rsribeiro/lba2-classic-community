#include	<system\adeline.h>
#include	<system\exit.h>
#include	<system\initimer.h>
#include	<system\timerdos.h>

#include	<ail\timer.h>

#ifdef USE_MSS
#ifdef	_WIN32
#include	<ail\mssw.h>
#else//	_WIN32
#include	<ail\mss.h>
#endif//_WIN32
#endif

//████████████████████████████████████████████████████████████████████████████
VOID_FUNC	ClearAIL;

//████████████████████████████████████████████████████████████████████████████
void	InitAIL()
{
#ifdef USE_MSS
	AIL_startup()	;

	RegisterInitClear( InitAIL, ClearAIL ) ;
#endif
}

//████████████████████████████████████████████████████████████████████████████
void	ClearAIL()
{
#ifdef USE_MSS
	AIL_shutdown()	;
#endif
}

//████████████████████████████████████████████████████████████████████████████
#ifndef	_WIN32

//████████████████████████████████████████████████████████████████████████████
S32	InitTimerAIL()
{
#ifdef USE_MSS
	HTIMER  HandleTimer ;

	LockVMMTimer();
	HandleTimer = AIL_register_timer( (AILTIMERCB)NewProc08 ) ;
	if (HandleTimer == -1)
	{
		return FALSE ;
	}

	AIL_set_timer_frequency( HandleTimer, 200 ) ;
	AIL_start_timer( HandleTimer ) ;

	RegisterInitClear( (VOID_FUNC *)InitTimerAIL, NULL ) ;

	return TRUE;
#else
	return FALSE ;
#endif
}

//████████████████████████████████████████████████████████████████████████████
#endif//_WIN32

//████████████████████████████████████████████████████████████████████████████
