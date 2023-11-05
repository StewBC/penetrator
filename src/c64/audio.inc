;-----------------------------------------------------------------------------
; audio.inc
; Part of penetrator, the zx spectrum game, made for Commodore C64
;
; Stefan Wessels, 2020, 2023
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "CODE"
;-----------------------------------------------------------------------------
; Runs in the IRQ
; As long as audioChannel? is <> 0, keep the sound going.  When it is 0, see
; if audioChan?Lo points at 0.  If yes, turn off sound.  If no, put the
; freq and delay in place - delay in audioChannel?
.proc audioService
    lda audioChannel1
    beq c2
    dec audioChannel1
    bne c2
    lda #32
    sta SID_Ctl1
    ldy #0
    lda (audioChan1Lo),y
    bne :+
    lda #0
    sta SID_Ctl1
    beq c2                                      ; BRA
:
    sta SID_S1Lo
    iny
    lda (audioChan1Lo),y
    sta SID_S1Hi
    lda #33
    sta SID_Ctl1
    iny
    lda (audioChan1Lo),y
    sta audioChannel1
    clc
    lda audioChan1Lo
    adc #3
    sta audioChan1Lo
    bcc c2
    inc audioChan1Hi

c2: lda audioChannel2
    beq c3
    dec audioChannel2
    bne c3
    lda #32
    sta SID_Ctl2
    ldy #0
    lda (audioChan2Lo),y
    bne :+
    lda #0
    sta SID_Ctl2
    beq c3
:
    sta SID_S2Lo
    iny
    lda (audioChan2Lo),y
    sta SID_S2Hi
    lda #33
    sta SID_Ctl2
    iny
    lda (audioChan2Lo),y
    sta audioChannel2
    clc
    lda audioChan2Lo
    adc #3
    sta audioChan2Lo
    bcc c3
    inc audioChan2Hi

c3: lda audioChannel3
    beq dn
    dec audioChannel3
    bne dn
    lda #32
    sta SID_Ctl3
    ldy #0
    lda (audioChan3Lo),y
    bne :+
    lda #0
    sta SID_Ctl3
    beq dn
:
    sta SID_S3Lo
    iny
    lda (audioChan3Lo),y
    sta SID_S3Hi
    lda #33
    sta SID_Ctl3
    iny
    lda (audioChan3Lo),y
    sta audioChannel3
    clc
    lda audioChan3Lo
    adc #3
    sta audioChan3Lo
    bcc dn
    inc audioChan3Hi

dn: jmp PLACEHOLDER

.endproc

;-----------------------------------------------------------------------------
.proc audioStart

    lda audioMask                               ; get the active channels
    and audioFrame                              ; see if any channel needs to play this frame
    bne makeSounds                              ; make a sound if a channel needs audio
    rts

makeSounds:
    sta makeThisSound
    bit Bit6Mask                                ; AUDIO_FIRE
    beq :+
    jsr fire
    lda makeThisSound

:   bit Bit7Mask                                ; AUDIO_EXPLOSION
    beq :+
    jsr bombDrop
    lda makeThisSound

:   bit Bit5Mask                                ; AUDIO_EXPLOSION
    beq :+
    jsr explosion                               ; pre-empt the engine from running
    lda makeThisSound

:   bit Bit8432Mask                             ; AUDIO_ENGINE - Not that bit 8 is erroneously checked
    beq :+
    jsr engine                                  ; only because I didn't want to make a new constant
    lda makeThisSound

:   bit Bit1Mask                                ; AUDIO_UI_TICK
    beq :+
    jmp ui

:   rts

explosion:
    lda #128
    sta SID_Ctl3                                ; Reset noise for rolling player explosion
    lda #129
    sta SID_Ctl3                                ; Start noise

    inc audioExplFrame                          ; make sure off-screen ticks to end
    lda audioExplFrame
    cmp #5
    bcc :+
    lda #AUDIO_MOTOR_PLAY
    sta audioFrame                              ; turn off the explosion
    lda #128
    sta SID_Ctl3                                ; stop the noise
:   rts

bombDrop:
    lda #<bombSound
    ldx #>bombSound
    ldy #0
    jmp audioPlayNote

ui:
    lda #<uiSound
    ldx #>uiSound
    ldy #0
    jmp audioPlayNote

engine:
    bit Bit4Mask                                ; AUDIO_MOTOR_FWD
    beq :+
    lda #<engineSoundF
    ldx #>engineSoundF
    ldy #1
    jmp audioPlayNote
:
    bit Bit3Mask                                ; AUDIO_MOTOR_REW
    beq :+
    lda #<engineSoundS
    ldx #>engineSoundS
    ldy #1
    jmp audioPlayNote
:
    lda #<engineSoundN
    ldx #>engineSoundN
    ldy #1
    jmp audioPlayNote

fire:
    lda #<gunSound
    ldx #>gunSound
    ldy #0
; Fall through intentionally

.endproc

;-----------------------------------------------------------------------------
; Load Y just before calling with the channel
; (Y=0) C 1 - Fire (shoot), Bomb, UI
; (Y=1) C 2 - Engine
;       C 3 - Explosion (Noise) - does not come here
.proc audioPlayNote

    sei
    bne c2
    sta audioChan1Lo
    stx audioChan1Hi
    ldy #0
    lda (audioChan1Lo),y
    sta SID_S1Lo
    iny
    lda (audioChan1Lo),y
    sta SID_S1Hi
    iny
    lda (audioChan1Lo),y
    sta audioChannel1
    clc
    lda audioChan1Lo
    adc #3
    sta audioChan1Lo
    bcc :+
    inc audioChan1Hi
:   lda #33
    sta SID_Ctl1
    bne e

c2: cpy #1
    bne c3
    sta audioChan2Lo
    stx audioChan2Hi
    ldy #0
    lda (audioChan2Lo),y
    sta SID_S2Lo
    iny
    lda (audioChan2Lo),y
    sta SID_S2Hi
    iny
    lda (audioChan2Lo),y
    sta audioChannel2
    clc
    lda audioChan2Lo
    adc #3
    sta audioChan2Lo
    bcc :+
    inc audioChan2Hi
:   lda #33
    sta SID_Ctl2
    bne e

c3: sta audioChan3Lo
    stx audioChan3Hi
    ldy #0
    lda (audioChan3Lo),y
    sta SID_S3Lo
    iny
    lda (audioChan3Lo),y
    sta SID_S3Hi
    iny
    lda (audioChan3Lo),y
    sta audioChannel3
    clc
    lda audioChan3Lo
    adc #3
    sta audioChan3Lo
    bcc :+
    inc audioChan3Hi
:   lda #33
    sta SID_Ctl3

e:  cli
    lda #AUDIO_EXPLOSION                        ; reset the audio frame (serviced)
    and audioFrame                              ; but keep explosion if it was set
    ora #AUDIO_MOTOR_PLAY                       ; and always add the MOTOR
    sta audioFrame

    rts

.endproc
