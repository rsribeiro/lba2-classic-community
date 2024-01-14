		.386p

		.MODEL	SMALL, SYSCALL

		include	aff_obj.inc

;*──────────────────────────────────────────────────────────────────────────*

		.DATA

;*──────────────────────────────────────────────────────────────────────────*
		EXTRN	SYSCALL	TimerRefHR		:DWORD

;*──────────────────────────────────────────────────────────────────────────*
		EXTRN	SYSCALL	Lib3DBufferAnim		:DWORD
		EXTRN	SYSCALL	EndLib3DBufferAnim	:DWORD
		EXTRN	SYSCALL	PtrLib3DBufferAnim	:DWORD

;*──────────────────────────────────────────────────────────────────────────*
		.CODE

;*──────────────────────────────────────────────────────────────────────────*
		PUBLIC	SYSCALL	ObjectStoreFrame

;*──────────────────────────────────────────────────────────────────────────*
;void	ObjectStoreFrame(T_OBJ *Obj)

;#pragma aux ObjectStoreFrame		\
;	parm		[ebx]		\
;	modify exact	[eax ecx esi edi]

ObjectStoreFrame proc

		mov	edi, PtrLib3DBufferAnim	; edi -> looping anim buffer

		mov	eax, TimerRefHR
		mov	[ebx].OBJ_3D.LastTimer, eax	; struct -> LastTimer
		mov	[ebx].OBJ_3D.ObjTime, eax	; struct -> ObjTime
		xor	eax, eax
		mov	ecx, [ebx].OBJ_3D.NbGroups
		inc	eax
		mov	[ebx].OBJ_3D.LastNbGroups, ecx	; struct -> LastNbGroups
		lea	ecx, [ecx*2-2]		; 2 DWORDs per group, no group 0
		mov	[ebx].OBJ_3D.LastOfsFrame, edi	; copy will be last frame
		mov	[ebx].OBJ_3D.LastOfsIsPtr, eax
		add	edi, 16
		dec	eax
		lea	esi, [ebx].OBJ_3D.CurrentFrame	; esi -> CurrentFrame

		mov	[ebx].OBJ_3D.Status, eax
		mov	dword ptr[edi-16], eax
		mov	dword ptr[edi-12], eax
		mov	dword ptr[edi-8], eax
		mov	dword ptr[edi-4], eax
		dec	eax
		rep	movsd			; do copy...

		cmp	edi, EndLib3DBufferAnim	; check buffer for next time
		jle	okbuf

		mov	edi, Lib3DBufferAnim
okbuf:
		mov	PtrLib3DBufferAnim, edi	; write back buffer pointer
		mov	[ebx].OBJ_3D.LastFrame, eax	; LastFrame = -1

		ret

ObjectStoreFrame endp

;*──────────────────────────────────────────────────────────────────────────*
;		The
		END
