;-----------------------------------------------------------------------------
; audio.inc
; Part of penetrator, the zx spectrum game, made for Commodore Plus4
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
    ldy #0
    lda (audioChan1Lo),y
    bne :+
    lda #%11101111
    and TED_snd_ctrl
    sta TED_snd_ctrl
    bne c2                                      ; BRA
:   sta TED_snd1_freq_lo
    iny
    lda TED_misc
    and #%11111100
    ora (audioChan1Lo),y
    sta TED_misc
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
    beq dn
    dec audioChannel2
    bne dn
    ldy #0
    lda (audioChan2Lo),y
    bne :+
    lda #%11011111
    and TED_snd_ctrl
    sta TED_snd_ctrl
    bne dn
:   sta TED_snd2_freq_lo
    iny
    lda (audioChan2Lo),y
    sta TED_snd2_freq_hi
    iny
    lda (audioChan2Lo),y
    sta audioChannel2
    clc
    lda audioChan2Lo
    adc #3
    sta audioChan2Lo
    bcc dn
    inc audioChan2Hi

dn: rts

.endproc

;-----------------------------------------------------------------------------
.proc audioStart

    lda audioMask                               ; get the active channels
    and audioFrame                              ; see if any channel needs to play this frame
    bne makeSounds                              ; make a sound if a channel needs audio
    rts

makeSounds:
    bit Bit6Mask                                ; AUDIO_FIRE
    bne fire

    bit Bit7Mask                                ; AUDIO_EXPLOSION
    bne bombDrop

    bit Bit5Mask                                ; AUDIO_EXPLOSION
    bne explosion

    bit Bit8432Mask                             ; AUDIO_ENGINE - Not that bit 8 is erroneously checked
    bne engine                                  ; only because I didn't want to make a new constant

    bit Bit1Mask                                ; AUDIO_UI_TICK
    bne ui

    rts

explosion:
    lda #%01000000                              ; Turn on the noise
    ora TED_snd_ctrl
    sta TED_snd_ctrl

    inc audioExplFrame                          ; make sure off-screen ticks to end
    lda audioExplFrame
    cmp #5
    bcc :+
    lda #AUDIO_MOTOR_PLAY
    sta audioFrame                              ; turn off the explosion
    lda #%10111111
    and TED_snd_ctrl
    sta TED_snd_ctrl
:
    rts

bombDrop:
    lda #<bombSound
    ldx #>bombSound
    ldy #1
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
; (Y=0) C 1 - Shoot, UI
; (Y=1) C 2 - Engine, Bomb
;       C Noise - Explosion - does not come here
.proc audioPlayNote

    sei
    bne c2
    sta audioChan1Lo
    stx audioChan1Hi
    ldy #0
    lda (audioChan1Lo),y
    sta TED_snd1_freq_lo
    iny
    lda TED_misc
    and #%11111100
    ora (audioChan1Lo),y
    sta TED_misc
    iny
    lda (audioChan1Lo),y
    sta audioChannel1
    clc
    lda audioChan1Lo
    adc #3
    sta audioChan1Lo
    bcc :+
    inc audioChan1Hi
:   lda #%00010000
    ora TED_snd_ctrl
    sta TED_snd_ctrl
    bne e

c2: sta audioChan2Lo
    stx audioChan2Hi
    ldy #0
    lda (audioChan2Lo),y
    sta TED_snd2_freq_lo
    iny
    lda (audioChan2Lo),y
    sta TED_snd2_freq_hi
    iny
    lda (audioChan2Lo),y
    sta audioChannel2
    clc
    lda audioChan2Lo
    adc #3
    sta audioChan2Lo
    bcc :+
    inc audioChan2Hi
:   lda #%00100000
    ora TED_snd_ctrl
    sta TED_snd_ctrl

e:  cli
    lda #AUDIO_EXPLOSION                        ; reset the audio frame (serviced)
    and audioFrame                              ; but keep explosion if it was set
    ora #AUDIO_MOTOR_PLAY                       ; and always add the MOTOR
    sta audioFrame

    rts

.endproc
