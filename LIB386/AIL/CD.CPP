#include	<system\adeline.h>

#include	<stdio.h>
#include	<string.h>
#include	<dos.h>

#include	<ail\cd.h>

#include 	<stdlib.h>

#ifdef USE_MSS
#ifdef	_WIN32
#include	<ail\mssw.h>
#else
#include	<ail\mss.h>
#endif
#else
#include	<ail\nullsound.h>
#endif

//████████████████████████████████████████████████████████████████████████████

static	HREDBOOK	Cd		;
static	U32		Tracks		;
static	U32		Track		;
static	U32		PausedTrack	;
static	U32		Cur		;
static	U32		End		;

static	S32		OldVolumeCD	;

//████████████████████████████████████████████████████████████████████████████

static	S32	CheckCD()
{
#ifdef USE_MSS
	if(!Cd)	return	FALSE	;

	return(AIL_redbook_status(Cd) != REDBOOK_ERROR) ;
#else
	return FALSE;
#endif
}

//████████████████████████████████████████████████████████████████████████████

char	OpenCD(char *volume_name)
{
#ifdef USE_MSS
	char	drive	;

	for(drive='A'; drive<='Z'; drive++)
	{
		Cd = AIL_redbook_open_drive(drive)	;
		if(CheckCD())
		{
			Tracks = AIL_redbook_tracks(Cd)	;

			if(Tracks>1)
			{
				AIL_redbook_stop(Cd)	;

				if(!volume_name||!volume_name[0])	break	;
#ifdef	_WIN32
				{
					char		rootpath[4]		;
					char		volume[_MAX_PATH]	;
					unsigned long	maxlength, fsflags	;

					sprintf(rootpath, "%c:\\", drive);

					if(GetDriveType(rootpath)!=DRIVE_CDROM)
					{
						goto error 	;
					}

					if(!GetVolumeInformation(	rootpath,
									volume,
									_MAX_PATH,
									NULL,
									&maxlength,
									&fsflags,
									NULL,
									0
								   ))
					{
						goto error 	;
					}

					if(!strcmp(volume, volume_name))
					{
						break		;
					}
				}
#else
				{
					struct find_t	fileinfo	;
					char		filter[7]	;

					sprintf(filter, "%c:\\*.*", drive);

					if(!_dos_findfirst(filter, _A_VOLID, &fileinfo))
					{
						if(!strcmp(volume_name, fileinfo.name))
						{
							break	;
						}
					}
				}
#endif
			}
		}
error:
		if(Cd)
		{
			AIL_redbook_close(Cd)	;
			Cd = NULL		;
		}
	}

	if(Cd)
	{
		atexit(CloseCD)		;

		OldVolumeCD = GetVolumeCD()	;

		return	drive		;
	}
	else
	{
		return 0		;
	}
#else
	return 0		;
#endif
}

//████████████████████████████████████████████████████████████████████████████

void	CloseCD()
{
#ifdef USE_MSS
	if(!Cd)		return	;

	StopCD()		;

	PausedTrack = 0		;

	ChangeVolumeCD(OldVolumeCD);

	AIL_redbook_close(Cd)	;

	Cd = NULL		;
#endif
}

//████████████████████████████████████████████████████████████████████████████

void	PlayCD(S32 track)
{
#ifdef USE_MSS
	U32	start, end	;

	if(!CheckCD() || !track || (track>Tracks))	return	;

	StopCD()		;

	AIL_redbook_track_info(Cd, track, &start, &end);

	AIL_redbook_play(Cd, start, end);
	Track = track		;
#endif
}

//████████████████████████████████████████████████████████████████████████████

void	ChangeVolumeCD(S32 volume)
{
#ifdef USE_MSS
	if( !CheckCD() )	return ;

	if(volume>127)
	{
		volume = 127	;
	}
	else if (volume<0)
	{
		volume = 0	;
	}

	AIL_redbook_set_volume(Cd, volume)	;
#endif
}

//████████████████████████████████████████████████████████████████████████████

S32	GetVolumeCD()
{
#ifdef USE_MSS
	return	AIL_redbook_volume(Cd)	;
#else
	return 0;
#endif
}

//████████████████████████████████████████████████████████████████████████████

void	StopCD()
{
#ifdef USE_MSS
	if( !CheckCD() || !Track)	return 	;

	AIL_redbook_stop(Cd)	;
	Track = 0		;
#endif
}

//████████████████████████████████████████████████████████████████████████████

void	PauseCD()
{
#ifdef USE_MSS
	if( !CheckCD() || !Track || !IsCDPlaying())	return	;

	AIL_redbook_track_info(Cd, Track, NULL, &End);
	Cur = AIL_redbook_position(Cd)	;
	PausedTrack = Track		;

	StopCD()			;
#endif
}

//████████████████████████████████████████████████████████████████████████████

void	ResumeCD()
{
#ifdef USE_MSS
	if( !CheckCD() || !PausedTrack)	return	;

	AIL_redbook_play(Cd, Cur, End)	;
	Track = PausedTrack		;
	PausedTrack = 0			;
#endif
}

//████████████████████████████████████████████████████████████████████████████

S32	IsCDPlaying()
{
#ifdef USE_MSS
	S32	playing	;

	if( !CheckCD() || !Track)	return FALSE ;

	playing = (AIL_redbook_status(Cd) != REDBOOK_STOPPED) || PausedTrack ;

	if(playing)
	{
		if(Track)	playing = Track		;
		else		playing = PausedTrack	;
	}
	else
	{
		Track = 0	;
	}


	return	playing		;
#else
	return FALSE		;
#endif
}

//████████████████████████████████████████████████████████████████████████████
