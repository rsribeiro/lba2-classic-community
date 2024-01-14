
		.386p

		.MODEL	SMALL, SYSCALL

		include	aff_obj.inc

;*──────────────────────────────────────────────────────────────────────────*
		.CODE

;*──────────────────────────────────────────────────────────────────────────*
		PUBLIC	SYSCALL	ObjectInitBody

;*══════════════════════════════════════════════════════════════════════════*
;void	ObjectInitBody(T_OBJ *obj, T_BODY *body)

;#pragma aux ObjectInitBody		\
;	parm		[ebx] [eax]	\
;	modify exact 	[ecx]

ObjectInitBody	proc
;		pobj:edx, body:eax

		mov	ecx, [ebx].OBJ_3D.Status
		mov	[ebx].OBJ_3D.NextBody, eax
		or	ecx, STATUS_BODY
		cmp	[ebx].OBJ_3D.Body, -1
		mov	[ebx].OBJ_3D.Status, ecx
		je	firstBody
		ret
firstBody:
		mov	[ebx].OBJ_3D.Body, eax
		ret

ObjectInitBody	endp

;*══════════════════════════════════════════════════════════════════════════*
; 		The
		END
