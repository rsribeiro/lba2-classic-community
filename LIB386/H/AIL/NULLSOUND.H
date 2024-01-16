#ifndef	LIB_AIL_NULLSOUND
#define	LIB_AIL_NULLSOUND

#define HREDBOOK int
#define HMDIDRIVER void *
#define HDIGDRIVER void *
#define HSEQUENCE void *
#define HWAVESYNTH void *
#define HSAMPLE void *
#define HTIMER void *
#define HSTREAM void *

#define REDBOOK_ERROR                                   (FALSE)
#define REDBOOK_STOPPED                                 (FALSE)

#define	AIL_redbook_status(cd)			                (TRUE)
#define	AIL_redbook_open_drive(cd)		                (TRUE)
#define	AIL_redbook_tracks(cd)			                (2)
#define	AIL_redbook_stop(cd)
#define	AIL_redbook_close(cd)
#define AIL_redbook_track_info(cd, track, start, end)
#define AIL_redbook_play(cd, start, end)
#define AIL_redbook_set_volume(cd, volume)
#define AIL_redbook_volume(cd)                          (0)
#define AIL_redbook_position(cd)                        (0)

#endif//LIB_AIL_NULLSOUND
