;int 9外中断
;5535, 粉色'5'
;6636, 橙色'6'

assume cs:code

data segment
		  ;0123456789abcdef	
SCREEN		db 18 dup('1000000000000001')
		db 	  '1111111111111111'

SCREEN_ROW		dw 19
SCREEN_COL		dw 16
SCREEN_LOCATION 	dw 160*3

BLOCK0		db '1100'
		db '1100'
		db '0000'
		db '0000'

BLOCK1		db '0000'
		db '1111'
		db '0000'
		db '0000'

BLOCK1_1	db '0100'
		db '0100'
		db '0100'
		db '0100'

BLOCK_S		db '0000'
		db '0110'
		db '1100'
		db '0000'

BLOCK_S_1	db '0100'
		db '0110'
		db '0010'
		db '0000'

BLOCK_Z		db '0000'
		db '1100'
		db '0110'
		db '0000'

BLOCK_Z_1	db '0010'
		db '0110'
		db '0100'
		db '0000'

BLOCK_T		db '0100'
		db '1110'
		db '0000'
		db '0000'

BLOCK_T_1	db '0100'
		db '0110'
		db '0100'
		db '0000'

BLOCK_T_2	db '0000'
		db '1110'
		db '0100'
		db '0000'

BLOCK_T_3	db '0100'
		db '1100'
		db '0100'
		db '0000'

BLOCK_J 	db '0010'
		db '0010'
		db '0110'
		db '0000'

BLOCK_J_1	db '0000'
		db '1000'
		db '1110'
		db '0000'

BLOCK_J_2	db '0110'
		db '0100'
		db '0100'
		db '0000'

BLOCK_J_3	db '0000'
		db '1110'
		db '0010'
		db '0000'

BLOCK_L		db '0100'
		db '0100'
		db '0110'
		db '0000'

BLOCK_L_1	db '0000'
		db '1110'
		db '1000'
		db '0000'

BLOCK_L_2	db '0110'
		db '0010'
		db '0010'
		db '0000'

BLOCK_L_3	db '0000'
		db '0010'
		db '1110'
		db '0000'

BLOCK		dw OFFSET BLOCK_0_A0
	;	dw OFFSET BLOCK0
		dw OFFSET BLOCK_1_A0
		dw OFFSET BLOCK_S_A0
		dw OFFSET BLOCK_Z_A0
		dw OFFSET BLOCK_T_A0
		dw OFFSET BLOCK_J_A0
		dw OFFSET BLOCK_L_A0



BLOCK_0_A0	dw OFFSET BLOCK0
		dw OFFSET BLOCK_0_A0

BLOCK_1_A0	dw OFFSET BLOCK1
		dw OFFSET BLOCK_1_A1

BLOCK_1_A1	dw OFFSET BLOCK1_1
		dw OFFSET BLOCK_1_A0

BLOCK_S_A0	dw OFFSET BLOCK_S
		dw OFFSET BLOCK_S_A1

BLOCK_S_A1	dw OFFSET BLOCK_S_1
		dw OFFSET BLOCK_S_A0

BLOCK_Z_A0	dw OFFSET BLOCK_Z
		dw OFFSET BLOCK_Z_A1

BLOCK_Z_A1	dw OFFSET BLOCK_Z_1
		dw OFFSET BLOCK_Z_A0

BLOCK_T_A0	dw OFFSET BLOCK_T
		dw OFFSET BLOCK_T_A1

BLOCK_T_A1	dw OFFSET BLOCK_T_1
		dw OFFSET BLOCK_T_A2

BLOCK_T_A2	dw OFFSET BLOCK_T_2
		dw OFFSET BLOCK_T_A3

BLOCK_T_A3	dw OFFSET BLOCK_T_3
		dw OFFSET BLOCK_T_A0

BLOCK_J_A0	dw OFFSET BLOCK_J
		dw OFFSET BLOCK_J_A1

BLOCK_J_A1	dw OFFSET BLOCK_J_1
		dw OFFSET BLOCK_J_A2

BLOCK_J_A2	dw OFFSET BLOCK_J_2
		dw OFFSET BLOCK_J_A3

BLOCK_J_A3	dw OFFSET BLOCK_J_3
		dw OFFSET BLOCK_J_A0

BLOCK_L_A0	dw OFFSET BLOCK_L
		dw OFFSET BLOCK_L_A1

BLOCK_L_A1	dw OFFSET BLOCK_L_1
		dw OFFSET BLOCK_L_A2

BLOCK_L_A2	dw OFFSET BLOCK_L_2
		dw OFFSET BLOCK_L_A3

BLOCK_L_A3	dw OFFSET BLOCK_L_3
		dw OFFSET BLOCK_L_A0


BLOCK_NOW_ADDRESS	dw 0
		
BLOCK_ROW	dw 4
BLOCK_COL	dw 4
BLOCK_COLOR	dw 2201h	;绿色笑脸😊

LEFT		db 4bh
RIGHT		db 4Dh
DOWN		db 50h
BLANK		db 39h
isAllowMoveDown	dw 0

BLOCK_NOW_STATUS	dw 0		
BLOCK_MAX		dw 0
BLOCK_FIRST		dw 0
;BLOCK_MAX_STATUS	dw 1, 2, 2, 2, 4, 4, 4 
BLOCK_MAX_STATUS	dw 0, 1, 1, 1, 3, 3, 3 

BLOCK_HIGHT		dw 3680
data ends

string segment
	db 'Game over', 0
string ends

stack segment
	db 128 dup(0)
stack ends

code segment
start:
	mov ax, stack 
	mov ss, ax
	mov sp, 128

	call cpyTetris	
	call saveOldInt9
	call setNewInt9
		
	mov bx, 0
	push bx
	mov bx, 7e00h	
	push bx
	retf
	
	;call restoreOldInt9	;恢复int9
	mov ax, 4c00h
	int 21h
;======================================
tetris:
	call initReg
	call clearScreen
	call initScreen	

nextBlock:
	cli
	call initBlockType
	call initBlockLocation
	call checkGameOver
	call printBlock
	sti

nextMoveDown:
	call delay
	cli	;屏蔽键盘外中断	
	call isMOveDown
	cmp isAllowMoveDown, 0
	je nextBlock
	sti
	jmp nextMoveDown

gameOver:
	add sp, 12	;还要加上ret的pop
	call printOver
	mov ax, 4c00h
	int 21h
;========================================
delay:
	push ax
	push dx

	mov ax, 0
	mov dx ,200h
delay_:
	sub ax, 100h
	sbb dx, 0
	cmp dx, 0
	jne delay_

	pop dx
	pop ax
	ret
;========================================
printOver:
	push ax
	push bx
	push ds
	push si

	mov bx, string
	mov ds, bx
	mov bx, 0
	mov si, 160*10+80

print_over:
	mov al, ds:[bx]
	cmp al, 0
	je printOverRet
	mov es:[si], al
	inc bx
	add si, 2
	jmp print_over 
	
printOverRet:
	pop si
	pop ds
	pop bx
	pop ax
	ret
;========================================
checkGameOver:
	push bx
	push si
	
	mov cx, BLOCK_ROW
checkOverRow:
	push bx
	push cx
	push si
	mov cx, BLOCK_COL

checkOverCol:	
	cmp byte ptr ds:[si], '1'
	jne nCheckOverCol
	cmp word ptr es:[bx], 0030h
	jne gameOver

nCheckOverCol:
	add bx, 2
	inc si
	loop checkOverCol

	pop si
	pop cx
	pop bx
	add si, 4
	add bx, 160
	loop checkOverRow
	
	pop si
	pop bx
	ret
;========================================
printBlock:
	push si
	push bx

	mov cx, BLOCK_ROW
	mov dx, BLOCK_COLOR

printBLOCK_ROW:
	push cx
	push si
	push bx

	mov cx, BLOCK_COL

printBLOCK_COL:
	cmp byte ptr ds:[si], '1'
	jne nPrintBLOCK_COL
	mov es:[bx], dx

nPrintBLOCK_COL:
	inc si
	add bx, 2
	loop printBLOCK_COL

	pop bx
	pop si
	pop cx
	
	add bx, 160
	add si, 4
	loop printBLOCK_ROW
	
	pop bx
	pop si
	ret
;========================================
initBlockLocation:
	mov bx,  SCREEN_LOCATION
	add bx, 7*2
	ret
;========================================
;BLOCK		dw OFFSET BLOCK0
;		dw OFFSET BLOCK1
;		dw OFFSET BLOCK_S
;		dw OFFSET BLOCK_Z
;		dw OFFSET BLOCK_T
;		dw OFFSET BLOCK_J
;		dw OFFSET BLOCK_L
;利用CMOS的秒/7得到随机数
initBlockType:
	call getBlockType	
;	mov bx, 1

	add bx, bx
	mov si, ds:BLOCK[bx]
	mov BLOCK_NOW_ADDRESS, si
	mov si, ds:[si+0]

	mov BLOCK_ROW, 4
	mov BLOCK_COL, 4
	
	mov isAllowMoveDown, 1

	mov BLOCK_NOW_STATUS, 0
	mov BLOCK_FIRST, si
	push ds:BLOCK_MAX_STATUS[bx]
	pop BLOCK_MAX

	ret
;========================================
getBlockType:
	mov al, 0
	out 70h, al
	in al, 71h
		
	mov dl, al	;保存个位
	and dl, 00001111b
	mov cl, 4
	shr al, cl
		
	mov bl, 10
	mul bl
	add al, dl

	mov dx, 0
	mov bx, 7
	div bx	;dx为余数

	mov bx, dx	
	ret
;========================================
initScreen:
	mov si, OFFSET SCREEN
	mov di, SCREEN_LOCATION
	mov cx, SCREEN_ROW

init_screen_row:	
	push cx
	push si
	push di
	mov cx, SCREEN_COL

init_screen_col:
	mov dh, 0
	mov dl, ds:[si]
	cmp dl, '1'
	jne init_screen_col_
	mov dh, 00010001b

init_screen_col_:
	mov es:[di], dx
	inc si
	add di, 2
	loop init_screen_col

	pop di
	pop si
	pop cx	
	
	add si, 16
	add di, 160
	loop init_screen_row
	ret
;============================================
clearScreen:
	mov cx, 2000
	mov di, 0
	mov dx, 0700h
clear_screen:
	mov es:[di], dx
	add di, 2
	loop clear_screen
;============================================
initReg:
	mov bx, 0b800h
	mov es, bx
	mov bx, data
	mov ds, bx
	ret
;--------------------------------------------
newInt9:
	push ax
	in al, 60h ;从60h端口读入一个字节
	pushf
	call dword ptr cs:[200h]

	cmp al, 4bh
	je isLeft
	cmp al, 4dh
	je isRight
	cmp al, 50h
	je isDown
	cmp al, 39h
	je isBlank
	
	cmp al, 3bh ;	F1键
	jne newInt9Ret
	call changeScreenColor

newInt9Ret:
	pop ax
	iret
;==========================================
isLeft:
	;mov bx, 0b800h
	;mov es, bx
	mov di, 160*10+40
	mov byte ptr es:[di], 'L'
	call isMoveLeft
	jmp newInt9Ret

isRight:
;	mov bx, 0b800h
;	mov es, bx
	mov di, 160*10+40
	mov byte ptr es:[di], 'R'
	call isMoveRight
	jmp newInt9Ret

isDown:
;	mov bx, 0b800h
;	mov es, bx
	mov di, 160*10+40
	mov byte ptr es:[di], 'D'
;	call isMoveDown
	cmp isAllowMoveDown, 0
	je isNextBlock
	jmp newInt9Ret

isNextBlock:
	pop ax
	add sp, 4
	popf
	jmp nextBlock

isBlank:
;	mov bx, 0b800h
;	mov es, bx
	mov di, 160*10+40
	mov byte ptr es:[di], 'B'
	call isTurnBlock
	jmp newInt9Ret
;=====================================
isTurnBlock:
;	inc BLOCK_NOW_STATUS
;	mov dx, BLOCK_NOW_STATUS
;	cmp dx, BLOCK_MAX
;	jna checkTurn	;不高于则转移
;	mov si, BLOCK_FIRST
;	mov BLOCK_NOW_STATUS, 0
;	jmp isTurn

;BLOCK_NOW_STATUS	dw 0		
;BLOCK_MAX		dw 0
;BLOCK_FIRST		dw 0
;BLOCK_MAX_STATUS	dw 0, 1, 1, 1, 3, 3, 3 
;自己优化 利用余数模拟环形

;	inc BLOCK_NOW_STATUS
;	push ax
;	push bx
;	push dx
;
;	mov dx, 0
;	mov ax, BLOCK_NOW_STATUS
;;	div BLOCK_MAX_STATUS	;dx为余数, si = dx*16
;		
;	pop dx
;	pop bx
;;	pop ax

;checkTurn:
;	add si, 16

;isTurn:
	push bx
	push si	
	push BLOCK_NOW_ADDRESS

	mov si, BLOCK_NOW_ADDRESS
	mov si, ds:[si+2]
	mov BLOCK_NOW_ADDRESS, si
	mov si, ds:[si+0]

	push si
	mov cx, BLOCK_ROW

checkTurnBlock:
	push cx
	push bx
	push si
	mov cx, BLOCK_COL

nCheckTurnRow:
	cmp byte ptr ds:[si], '1'
	jne nCheckTurnCol
	cmp word ptr es:[bx], 2201h
	je nCheckTurnCol
	cmp word ptr es:[bx], 0030h
	jne noTurnBlock

nCheckTurnCol:
	add bx, 2
	inc si
	loop nCheckTurnRow
	
	pop si
	pop bx
	pop cx
	add si, 4
	add bx, 160
	loop checkTurnBlock

	pop si
	add sp, 4
	pop bx
	
	mov dx, 0030h
	call setBottomBlock

	call printBlock
	ret

noTurnBlock:
	add sp, 8	
	pop BLOCK_NOW_ADDRESS
	pop si
	pop bx

	ret
;=====================================
isMoveLeft:
	push bx
	mov cx, BLOCK_ROW

moveLeft:	
	push bx
	push cx

	mov cx, BLOCK_COL

nMoveLeftRow:
	cmp word ptr es:[bx], 2201h
	jne nMoveLeftCol
	cmp word ptr es:[bx-2], 0030h
	jne noMoveLeft
	jmp nextLeftRow

nMoveLeftCol:
	add bx, 2
	
	loop nMoveLeftRow
nextLeftRow:
	pop cx
	pop bx
	add bx, 160
	loop moveLeft
	
	pop bx
        mov dx, 0030h
	call setBottomBlock
        sub bx, 2
        call printBlock
	ret

noMoveLeft:
	add sp, 4
	pop bx	
        ret
;====================================
isMoveRight:
      	push bx
	mov cx, BLOCK_ROW

moveRight:	
	push bx
	push cx
	mov cx, BLOCK_COL

nMoveRightRow:
	cmp word ptr es:[bx], 2201h
	jne nMoveRightCol
	cmp word ptr es:[bx+2], 2201h	;'笑脸'
	je nMoveRightCol
	cmp word ptr es:[bx+2], 0030h	;'0'
	jne noMoveRight
	jmp nextRightRow
nMoveRightCol:
	add bx, 2
	loop nMoveRightRow
nextRightRow:
	pop cx
	pop bx
	add bx, 160
	loop moveRight
	
	pop bx
        mov dx, 0030h 
	call setBottomBlock
        add bx, 2
        call printBlock
	ret

noMoveRight:
	add sp, 4
	pop bx	
        ret
;====================================
isMoveDown:	
	push bx
	mov cx, BLOCK_ROW
moveDown:	
	push cx
	push bx
	mov cx, BLOCK_COL
nMoveDownRow:
	cmp word ptr es:[bx], 2201h
	jne nMoveDownCol
	cmp word ptr es:[bx+160], 2201h
	je nMoveDownCol
	cmp word ptr es:[bx+160], 0030h	;'0'
	jne noMoveDown

nMoveDownCol:
	add bx, 2
	loop nMoveDownRow

	pop  bx
	pop cx
	add bx, 160
	loop moveDown	
	
	pop bx
        mov dx, 0030h
	call setBottomBlock
        add bx, 160
        call printBlock
	ret
	
noMoveDown:
	add sp, 4
	pop bx
        mov isAllowMoveDown, 0
	mov dx, 4432h
	call setBottomBlock
	call getRow	;得到一行最左边的位置
	call checkClearRow
	ret
;===============================
checkClearRow:	
	push bx
	mov cx, 4
	
checkRow:
	push bx
	push cx
	mov dx, bx
	mov cx, 14
checkCol:
	cmp word ptr es:[bx], 4432h
	jne nCheckCol
	
	add bx, 2
	loop checkCol
	
	mov bx, dx
	call clearRow
	call drawNewScreen

nCheckCol:
	pop cx
	pop bx
	add bx, 160
	loop checkRow
	
	pop bx
	ret
;===============================
clearRow:
	push bx

	mov cx, 14
clear_check_row:
	mov word ptr es:[bx], 0030h
	add bx, 2
	loop clear_check_row
	
	pop bx
	ret
;===============================
drawNewScreen:
	mov bx, BLOCK_HIGHT

;	mov word ptr es:[bx], 6636h 	;橙色'6'
;	mov bx, dx
;	mov word ptr es:[bx], 5535h	;粉红'5'

;s3:
;	mov ax, 1000h
;	jmp s3

	cmp bx, dx
	je drawNewScreenRet	;相等则直接退出

	mov ax, dx
	sub ax, bx

	push dx
	mov dx, 0
	mov cx, 160
	div cx
	mov cx, ax
	pop dx

	mov si, dx
	sub si, 160
	mov di, dx
	
drawRow:
	push si
	push di
	push cx	
	
	mov cx, 14
drawCol:
	push es:[si]
	pop es:[di]
	add si, 2
	add di, 2
	loop drawCol

	pop cx
	pop di
	pop si	
	sub si, 160
	sub di, 160
	loop drawRow
	mov bx, BLOCK_HIGHT
	call clearRow
	
drawNewScreenRet:
	add BLOCK_HIGHT, 160
	ret
;===============================
getRow:
	cmp byte ptr es:[bx], '1'
	je get_row
	sub bx, 2
	jmp getRow
	
get_row:
	add bx, 2
	cmp bx, BLOCK_HIGHT
	jnb getRowRet	;>=
	mov BLOCK_HIGHT, bx
;	mov word ptr es:[bx], 5535h
getRowRet:
	ret
;====================================
setBottomBlock:	
	push bx
	mov cx, BLOCK_ROW

setBottomRow:
	push bx
	push cx
	mov cx, BLOCK_COL
	
setBottomCol:
	cmp word ptr es:[bx], 2201h
	jne setBottomRet
	;mov word ptr es:[bx], 4432h
	mov es:[bx], dx

setBottomRet:
	add bx, 2

	loop setBottomCol
	pop cx
	pop bx
	
	add bx, 160
	loop setBottomRow
	pop bx

	ret
;====================================
changeScreenColor:
	push bx
	push cx
	push es
	push di

	mov bx, 0b800h
	mov es, bx
	mov cx, 2000
	mov di, 1
change_screen_color:
	inc byte ptr es:[di]
	add di, 2
	loop change_screen_color

	pop di
	pop es
	pop cx
	pop bx		
	ret
;===============================================
tetrisEnd:
	nop
;======================================

setNewInt9:
	mov bx, 0
	mov es, bx
	
	cli	
	mov word ptr es:[9*4], OFFSET newInt9 - OFFSET tetris + 7e00h
	mov word ptr es:[9*4+2], 0
	sti
	ret
;======================================
restoreOldInt9:
	mov bx, 0
	mov es, bx
	
	push  es:[200h]
	pop es:[9*4]
	push  es:[202h]
	pop es:[9*4+2]
	ret
;======================================
saveOldInt9:
	mov bx, 0
	mov es, bx
	
	push  es:[9*4]
	pop es:[200h]
	push  es:[9*4+2]
	pop es:[202h]
	ret
;======================================
cpyTetris:
	mov ax, cs
	mov ds, ax
	mov ax, 0
	mov es, ax

	mov si, OFFSET tetris
	mov di, 7e00h
	mov cx, OFFSET tetrisEnd - OFFSET tetris
	cld
	rep movsb
 
	ret

code ends

end start
