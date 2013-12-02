; $Id: toc.asm 956 2008-10-19 22:24:23Z hsc $

;******************************************************************************
;* Betriebssysteme                                                            *
;*----------------------------------------------------------------------------*
;*                                                                            *
;*                               T O C . A S M                                *
;*                                                                            *
;*----------------------------------------------------------------------------*
;*
;******************************************************************************

%include "machine/toc.inc"

; EXPORTIERTE FUNKTIONEN

[GLOBAL toc_switch]
[GLOBAL toc_go]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; TOC_GO : Startet den ersten Prozess ueberhaupt.
;
; C Prototyp: void toc_go (struct toc* regs);

toc_go:
  mov eax, [esp + 4] ; eax <- regs

  mov ebx, [eax + ebx_offset]
  mov esi, [eax + esi_offset]
  mov edi, [eax + edi_offset]
  mov ebp, [eax + ebp_offset]
  mov esp, [eax + esp_offset]

  ret

; TOC_SWITCH : Prozessumschaltung. Der aktuelle Registersatz wird     
;              gesichert und der Registersatz des neuen "thread of control"
;              wird in den Prozessor eingelesen.  
;
; C Prototyp: void toc_switch (struct toc* regs_now,
;                              struct toc* reg_then);

toc_switch:
  mov eax, [esp + 4] ; eax <- regs_now

  mov [eax + ebx_offset], ebx
  mov [eax + esi_offset], esi
  mov [eax + edi_offset], edi
  mov [eax + ebp_offset], ebp
  mov [eax + esp_offset], esp

  mov eax, [esp + 8] ; eax <- regs_then
  mov ebx, [eax + ebx_offset]
  mov esi, [eax + esi_offset]
  mov edi, [eax + edi_offset]
  mov ebp, [eax + ebp_offset]
  mov esp, [eax + esp_offset]

  ret
