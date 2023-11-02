;-----------------------------------------------------------------------------
; fontdata.inc
; Part of penetrator, the zx spectrum game, made for Commodore Plus4
;
; Stefan Wessels, 2019, 2023
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "RODATA"

;-----------------------------------------------------------------------------
; With charmap_ascii the upper and lower case were swapped so I just swapped
; them in the font data as well
font:
.byte $00   ;--------   32
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------

.byte $00   ;--------   33
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $00   ;--------
.byte $10   ;---X----
.byte $00   ;--------

.byte $00   ;--------   34
.byte $24   ;--X--X--
.byte $24   ;--X--X--
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------

.byte $00   ;--------   35
.byte $24   ;--X--X--
.byte $7E   ;-XXXXXX-
.byte $24   ;--X--X--
.byte $24   ;--X--X--
.byte $7E   ;-XXXXXX-
.byte $24   ;--X--X--
.byte $00   ;--------

.byte $00   ;--------   36
.byte $08   ;----X---
.byte $1E   ;---XXXX-
.byte $28   ;--X-X---
.byte $1C   ;---XXX--
.byte $0A   ;----X-X-
.byte $3C   ;--XXXX--
.byte $08   ;----X---

.byte $00   ;--------   37
.byte $62   ;-XX---X-
.byte $64   ;-XX--X--
.byte $08   ;----X---
.byte $10   ;---X----
.byte $26   ;--X--XX-
.byte $46   ;-X---XX-
.byte $00   ;--------

.byte $00   ;--------   38
.byte $10   ;---X----
.byte $28   ;--X-X---
.byte $10   ;---X----
.byte $2A   ;--X-X-X-
.byte $44   ;-X---X--
.byte $3A   ;--XXX-X-
.byte $00   ;--------

.byte $00   ;--------   39
.byte $08   ;----X---
.byte $10   ;---X----
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------

.byte $00   ;--------   40
.byte $04   ;-----X--
.byte $08   ;----X---
.byte $08   ;----X---
.byte $08   ;----X---
.byte $08   ;----X---
.byte $04   ;-----X--
.byte $00   ;--------

.byte $00   ;--------   41
.byte $20   ;--X-----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $20   ;--X-----
.byte $00   ;--------

.byte $00   ;--------   42
.byte $00   ;--------
.byte $14   ;---X-X--
.byte $08   ;----X---
.byte $3E   ;--XXXXX-
.byte $08   ;----X---
.byte $14   ;---X-X--
.byte $00   ;--------

.byte $00   ;--------   43
.byte $00   ;--------
.byte $08   ;----X---
.byte $08   ;----X---
.byte $3E   ;--XXXXX-
.byte $08   ;----X---
.byte $08   ;----X---
.byte $00   ;--------

.byte $00   ;--------   44
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $08   ;----X---
.byte $08   ;----X---
.byte $10   ;---X----

.byte $00   ;--------   45
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $3E   ;--XXXXX-
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------

.byte $00   ;--------   46
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $18   ;---XX---
.byte $18   ;---XX---
.byte $00   ;--------

.byte $00   ;--------   47
.byte $00   ;--------
.byte $02   ;------X-
.byte $04   ;-----X--
.byte $08   ;----X---
.byte $10   ;---X----
.byte $20   ;--X-----
.byte $00   ;--------

.byte $00   ;--------   48
.byte $3C   ;--XXXX--
.byte $46   ;-X---XX-
.byte $4A   ;-X--X-X-
.byte $52   ;-X-X--X-
.byte $62   ;-XX---X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   49
.byte $18   ;---XX---
.byte $28   ;--X-X---
.byte $08   ;----X---
.byte $08   ;----X---
.byte $08   ;----X---
.byte $3E   ;--XXXXX-
.byte $00   ;--------

.byte $00   ;--------   50
.byte $3C   ;--XXXX--
.byte $42   ;-X----X-
.byte $02   ;------X-
.byte $3C   ;--XXXX--
.byte $40   ;-X------
.byte $7E   ;-XXXXXX-
.byte $00   ;--------

.byte $00   ;--------   51
.byte $3C   ;--XXXX--
.byte $42   ;-X----X-
.byte $0C   ;----XX--
.byte $02   ;------X-
.byte $42   ;-X----X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   52
.byte $08   ;----X---
.byte $18   ;---XX---
.byte $28   ;--X-X---
.byte $48   ;-X--X---
.byte $7E   ;-XXXXXX-
.byte $08   ;----X---
.byte $00   ;--------

.byte $00   ;--------   53
.byte $7E   ;-XXXXXX-
.byte $40   ;-X------
.byte $7C   ;-XXXXX--
.byte $02   ;------X-
.byte $42   ;-X----X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   54
.byte $3C   ;--XXXX--
.byte $40   ;-X------
.byte $7C   ;-XXXXX--
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   55
.byte $7E   ;-XXXXXX-
.byte $02   ;------X-
.byte $04   ;-----X--
.byte $08   ;----X---
.byte $10   ;---X----
.byte $10   ;---X----
.byte $00   ;--------

.byte $00   ;--------   56
.byte $3C   ;--XXXX--
.byte $42   ;-X----X-
.byte $3C   ;--XXXX--
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   57
.byte $3C   ;--XXXX--
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $3E   ;--XXXXX-
.byte $02   ;------X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   58
.byte $00   ;--------
.byte $00   ;--------
.byte $10   ;---X----
.byte $00   ;--------
.byte $00   ;--------
.byte $10   ;---X----
.byte $00   ;--------

.byte $00   ;--------   59
.byte $00   ;--------
.byte $10   ;---X----
.byte $00   ;--------
.byte $00   ;--------
.byte $10   ;---X----
.byte $10   ;---X----
.byte $20   ;--X-----

.byte $00   ;--------   60
.byte $00   ;--------
.byte $04   ;-----X--
.byte $08   ;----X---
.byte $10   ;---X----
.byte $08   ;----X---
.byte $04   ;-----X--
.byte $00   ;--------

.byte $00   ;--------   61
.byte $00   ;--------
.byte $00   ;--------
.byte $3E   ;--XXXXX-
.byte $00   ;--------
.byte $3E   ;--XXXXX-
.byte $00   ;--------
.byte $00   ;--------

.byte $00   ;--------   62
.byte $00   ;--------
.byte $10   ;---X----
.byte $08   ;----X---
.byte $04   ;-----X--
.byte $08   ;----X---
.byte $10   ;---X----
.byte $00   ;--------

.byte $00   ;--------   63
.byte $3C   ;--XXXX--
.byte $42   ;-X----X-
.byte $04   ;-----X--
.byte $08   ;----X---
.byte $00   ;--------
.byte $08   ;----X---
.byte $00   ;--------

.byte $00   ;--------   64
.byte $3C   ;--XXXX--
.byte $4A   ;-X--X-X-
.byte $56   ;-X-X-XX-
.byte $5E   ;-X-XXXX-
.byte $40   ;-X------
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   97
.byte $3C   ;--XXXX--
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $7E   ;-XXXXXX-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $00   ;--------

.byte $00   ;--------   98
.byte $7C   ;-XXXXX--
.byte $42   ;-X----X-
.byte $7C   ;-XXXXX--
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $7C   ;-XXXXX--
.byte $00   ;--------

.byte $00   ;--------   99
.byte $3C   ;--XXXX--
.byte $42   ;-X----X-
.byte $40   ;-X------
.byte $40   ;-X------
.byte $42   ;-X----X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   100
.byte $78   ;-XXXX---
.byte $44   ;-X---X--
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $44   ;-X---X--
.byte $78   ;-XXXX---
.byte $00   ;--------

.byte $00   ;--------   101
.byte $7E   ;-XXXXXX-
.byte $40   ;-X------
.byte $7C   ;-XXXXX--
.byte $40   ;-X------
.byte $40   ;-X------
.byte $7E   ;-XXXXXX-
.byte $00   ;--------

.byte $00   ;--------   102
.byte $7E   ;-XXXXXX-
.byte $40   ;-X------
.byte $7C   ;-XXXXX--
.byte $40   ;-X------
.byte $40   ;-X------
.byte $40   ;-X------
.byte $00   ;--------

.byte $00   ;--------   103
.byte $3C   ;--XXXX--
.byte $42   ;-X----X-
.byte $40   ;-X------
.byte $4E   ;-X--XXX-
.byte $42   ;-X----X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   104
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $7E   ;-XXXXXX-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $00   ;--------

.byte $00   ;--------   105
.byte $3E   ;--XXXXX-
.byte $08   ;----X---
.byte $08   ;----X---
.byte $08   ;----X---
.byte $08   ;----X---
.byte $3E   ;--XXXXX-
.byte $00   ;--------

.byte $00   ;--------   106
.byte $02   ;------X-
.byte $02   ;------X-
.byte $02   ;------X-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   107
.byte $44   ;-X---X--
.byte $48   ;-X--X---
.byte $70   ;-XXX----
.byte $48   ;-X--X---
.byte $44   ;-X---X--
.byte $42   ;-X----X-
.byte $00   ;--------

.byte $00   ;--------   108
.byte $40   ;-X------
.byte $40   ;-X------
.byte $40   ;-X------
.byte $40   ;-X------
.byte $40   ;-X------
.byte $7E   ;-XXXXXX-
.byte $00   ;--------

.byte $00   ;--------   109
.byte $42   ;-X----X-
.byte $66   ;-XX--XX-
.byte $5A   ;-X-XX-X-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $00   ;--------

.byte $00   ;--------   110
.byte $42   ;-X----X-
.byte $62   ;-XX---X-
.byte $52   ;-X-X--X-
.byte $4A   ;-X--X-X-
.byte $46   ;-X---XX-
.byte $42   ;-X----X-
.byte $00   ;--------

.byte $00   ;--------   111
.byte $3C   ;--XXXX--
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   112
.byte $7C   ;-XXXXX--
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $7C   ;-XXXXX--
.byte $40   ;-X------
.byte $40   ;-X------
.byte $00   ;--------

.byte $00   ;--------   113
.byte $3C   ;--XXXX--
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $52   ;-X-X--X-
.byte $4A   ;-X--X-X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   114
.byte $7C   ;-XXXXX--
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $7C   ;-XXXXX--
.byte $44   ;-X---X--
.byte $42   ;-X----X-
.byte $00   ;--------

.byte $00   ;--------   115
.byte $3C   ;--XXXX--
.byte $40   ;-X------
.byte $3C   ;--XXXX--
.byte $02   ;------X-
.byte $42   ;-X----X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   116
.byte $FE   ;XXXXXXX-
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $00   ;--------

.byte $00   ;--------   117
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   118
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $24   ;--X--X--
.byte $18   ;---XX---
.byte $00   ;--------

.byte $00   ;--------   119
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $42   ;-X----X-
.byte $5A   ;-X-XX-X-
.byte $24   ;--X--X--
.byte $00   ;--------

.byte $00   ;--------   120
.byte $42   ;-X----X-
.byte $24   ;--X--X--
.byte $18   ;---XX---
.byte $18   ;---XX---
.byte $24   ;--X--X--
.byte $42   ;-X----X-
.byte $00   ;--------

.byte $00   ;--------   121
.byte $82   ;X-----X-
.byte $44   ;-X---X--
.byte $28   ;--X-X---
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $00   ;--------

.byte $00   ;--------   122
.byte $7E   ;-XXXXXX-
.byte $04   ;-----X--
.byte $08   ;----X---
.byte $10   ;---X----
.byte $20   ;--X-----
.byte $7E   ;-XXXXXX-
.byte $00   ;--------

.byte $00   ;--------   91
.byte $0E   ;----XXX-
.byte $08   ;----X---
.byte $08   ;----X---
.byte $08   ;----X---
.byte $08   ;----X---
.byte $0E   ;----XXX-
.byte $00   ;--------

.byte $00   ;--------   92
.byte $00   ;--------
.byte $40   ;-X------
.byte $20   ;--X-----
.byte $10   ;---X----
.byte $08   ;----X---
.byte $04   ;-----X--
.byte $00   ;--------

.byte $00   ;--------   93
.byte $70   ;-XXX----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $70   ;-XXX----
.byte $00   ;--------

.byte $00   ;--------   94
.byte $10   ;---X----
.byte $38   ;--XXX---
.byte $54   ;-X-X-X--
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $00   ;--------

.byte $00   ;--------   95
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $FF   ;XXXXXXXX

.byte $00   ;--------   96
.byte $1C   ;---XXX--
.byte $22   ;--X---X-
.byte $78   ;-XXXX---
.byte $20   ;--X-----
.byte $20   ;--X-----
.byte $7E   ;-XXXXXX-
.byte $00   ;--------

.byte $00   ;--------   65
.byte $00   ;--------
.byte $38   ;--XXX---
.byte $04   ;-----X--
.byte $3C   ;--XXXX--
.byte $44   ;-X---X--
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   66
.byte $20   ;--X-----
.byte $20   ;--X-----
.byte $3C   ;--XXXX--
.byte $22   ;--X---X-
.byte $22   ;--X---X-
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   67
.byte $00   ;--------
.byte $1C   ;---XXX--
.byte $20   ;--X-----
.byte $20   ;--X-----
.byte $20   ;--X-----
.byte $1C   ;---XXX--
.byte $00   ;--------

.byte $00   ;--------   68
.byte $04   ;-----X--
.byte $04   ;-----X--
.byte $3C   ;--XXXX--
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $3C   ;--XXXX--
.byte $00   ;--------

.byte $00   ;--------   69
.byte $00   ;--------
.byte $38   ;--XXX---
.byte $44   ;-X---X--
.byte $78   ;-XXXX---
.byte $40   ;-X------
.byte $38   ;--XXX---
.byte $00   ;--------

.byte $00   ;--------   70
.byte $0C   ;----XX--
.byte $10   ;---X----
.byte $18   ;---XX---
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $00   ;--------

.byte $00   ;--------   71
.byte $00   ;--------
.byte $3C   ;--XXXX--
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $3C   ;--XXXX--
.byte $04   ;-----X--
.byte $38   ;--XXX---

.byte $00   ;--------   72
.byte $40   ;-X------
.byte $40   ;-X------
.byte $78   ;-XXXX---
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $00   ;--------

.byte $00   ;--------   73
.byte $10   ;---X----
.byte $00   ;--------
.byte $30   ;--XX----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $38   ;--XXX---
.byte $00   ;--------

.byte $00   ;--------   74
.byte $04   ;-----X--
.byte $00   ;--------
.byte $04   ;-----X--
.byte $04   ;-----X--
.byte $04   ;-----X--
.byte $24   ;--X--X--
.byte $18   ;---XX---

.byte $00   ;--------   75
.byte $20   ;--X-----
.byte $28   ;--X-X---
.byte $30   ;--XX----
.byte $30   ;--XX----
.byte $28   ;--X-X---
.byte $24   ;--X--X--
.byte $00   ;--------

.byte $00   ;--------   76
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $0C   ;----XX--
.byte $00   ;--------

.byte $00   ;--------   77
.byte $00   ;--------
.byte $68   ;-XX-X---
.byte $54   ;-X-X-X--
.byte $54   ;-X-X-X--
.byte $54   ;-X-X-X--
.byte $54   ;-X-X-X--
.byte $00   ;--------

.byte $00   ;--------   78
.byte $00   ;--------
.byte $78   ;-XXXX---
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $00   ;--------

.byte $00   ;--------   79
.byte $00   ;--------
.byte $38   ;--XXX---
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $38   ;--XXX---
.byte $00   ;--------

.byte $00   ;--------   80
.byte $00   ;--------
.byte $78   ;-XXXX---
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $78   ;-XXXX---
.byte $40   ;-X------
.byte $40   ;-X------

.byte $00   ;--------   81
.byte $00   ;--------
.byte $3C   ;--XXXX--
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $3C   ;--XXXX--
.byte $04   ;-----X--
.byte $02   ;------X-

.byte $00   ;--------   82
.byte $00   ;--------
.byte $1C   ;---XXX--
.byte $20   ;--X-----
.byte $20   ;--X-----
.byte $20   ;--X-----
.byte $20   ;--X-----
.byte $00   ;--------

.byte $00   ;--------   83
.byte $00   ;--------
.byte $38   ;--XXX---
.byte $40   ;-X------
.byte $38   ;--XXX---
.byte $04   ;-----X--
.byte $78   ;-XXXX---
.byte $00   ;--------

.byte $00   ;--------   84
.byte $10   ;---X----
.byte $38   ;--XXX---
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $0C   ;----XX--
.byte $00   ;--------

.byte $00   ;--------   85
.byte $00   ;--------
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $38   ;--XXX---
.byte $00   ;--------

.byte $00   ;--------   86
.byte $00   ;--------
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $28   ;--X-X---
.byte $28   ;--X-X---
.byte $10   ;---X----
.byte $00   ;--------

.byte $00   ;--------   87
.byte $00   ;--------
.byte $44   ;-X---X--
.byte $54   ;-X-X-X--
.byte $54   ;-X-X-X--
.byte $54   ;-X-X-X--
.byte $28   ;--X-X---
.byte $00   ;--------

.byte $00   ;--------   88
.byte $00   ;--------
.byte $44   ;-X---X--
.byte $28   ;--X-X---
.byte $10   ;---X----
.byte $28   ;--X-X---
.byte $44   ;-X---X--
.byte $00   ;--------

.byte $00   ;--------   89
.byte $00   ;--------
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $44   ;-X---X--
.byte $3C   ;--XXXX--
.byte $04   ;-----X--
.byte $38   ;--XXX---

.byte $00   ;--------   90
.byte $00   ;--------
.byte $7C   ;-XXXXX--
.byte $08   ;----X---
.byte $10   ;---X----
.byte $20   ;--X-----
.byte $7C   ;-XXXXX--
.byte $00   ;--------

.byte $00   ;--------   123
.byte $06   ;-----XX-
.byte $08   ;----X---
.byte $30   ;--XX----
.byte $08   ;----X---
.byte $08   ;----X---
.byte $06   ;-----XX-
.byte $00   ;--------

.byte $00   ;--------   124
.byte $08   ;----X---
.byte $08   ;----X---
.byte $08   ;----X---
.byte $08   ;----X---
.byte $08   ;----X---
.byte $08   ;----X---
.byte $00   ;--------

.byte $00   ;--------   125
.byte $60   ;-XX-----
.byte $10   ;---X----
.byte $0C   ;----XX--
.byte $10   ;---X----
.byte $10   ;---X----
.byte $60   ;-XX-----
.byte $00   ;--------

.byte $00   ;--------   126
.byte $14   ;---X-X--
.byte $28   ;--X-X---
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------

.byte $3C   ;--XXXX--   127
.byte $42   ;-X----X-
.byte $99   ;X--XX--X
.byte $A1   ;X-X----X
.byte $A1   ;X-X----X
.byte $99   ;X--XX--X
.byte $42   ;-X----X-
.byte $3C   ;--XXXX--

.byte $00   ;--------   128
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $80   ;X-------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------

.byte $00   ;--------   129
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $80   ;X-------
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------

.byte $00   ;--------   130
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $A0   ;X-X-----
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------

.byte $00   ;--------   131
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $A8   ;X-X-X---
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------

.byte $00   ;--------   132
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------
.byte $AA   ;X-X-X-X-
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------

.byte $10   ;---X----   133
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $54   ;-X-X-X--
.byte $38   ;--XXX---
.byte $10   ;---X----

.byte $10   ;---X----   134
.byte $38   ;--XXX---
.byte $54   ;-X-X-X--
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----
.byte $10   ;---X----

.byte $10   ;---x----   135
.byte $00   ;--------
.byte $54   ;-X-x-x--
.byte $00   ;--------
.byte $10   ;---x----
.byte $00   ;--------
.byte $00   ;--------
.byte $00   ;--------

endFont:
