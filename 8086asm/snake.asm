assume cs:code

data segment
UP		db 48h
DOWN		db 50h
LEFT		db 4bh
RIGHT		db 4dh

SCREEN_COLOR	dw 0700h

SNAKE_		dw 200 dup(0)
SNAKE_COLOR	dw 2201h
SNAKE_LEN	dw 3
	
SNAKE_HEAD	dw 0
SNAKE_TAIL	dw 8
SNAKE_NODE	dw 12

MOVE		dw OFFSET isMoveUp - OFFSET snake + 7e00h	;0	
		dw OFFSET isMoveDown - OFFSET snake + 7e00h	;2
		dw OFFSET isMoveLeft - OFFSET snake + 7e00h	;4
		dw OFFSET isMoveRight - OFFSET snake + 7e00h	;6

MOVE_ADDRESS	dw 3

KEY_SEQUENCE	dw 200 dup(0ffh)
	
KEY_SEQUENCE_TOP	dw 0
		
data ends

stack segment
	db 128 dup(0)
stack ends

code segment
start:
	mov ax, stack
	mov ss, ax
	mov sp, 128
	
	call cpySnake
	call saveOldInt9
	call setNewInt9

	mov bx, 0
	push bx
	mov bx, 7e00h
	push bx
	retf	;retf相当于执行了`pop ip, pop cs`,

	mov ax, 4c00h
	int 21h
;==============================
snake:	
	call initReg
	call clearScreen
	call initSnake
	
;nextMove:
;	call delay	;延时, 消耗cpu	
;	cli
;	call isMoveDirection
;	sti
;	jmp nextMove
	
;	mov bx, OFFSET KEY_SEQUENCE

;play:	
;	cmp byte ptr ds:KEY_SEQUENCE[bx], 9
;	je playRet
;	call delay
;	cli
;	call word ptr ds:MOVE[bx]
;	sti	
;	jmp play

;playRet:	
;	mov word ptr es:[160*10+30*2], 4432h	;食物
	call randomFood 

s:	mov ax, 1000h
	jmp s

replayGame:	
	call initReg
	call clearScreen
	
	mov KEY_SEQUENCE_TOP, 0
	call initSnake
	
nextReplay:
	call delay
	cli
	call replayDirection
	sti
	jmp nextReplay

replayOver:
	mov ax, 4c00h
	int 21h
;===============================
randomFood:
	push ax
	push bx
	push cx

	mov al, 0
	out 70h, al
	in al, 71h
	
	mov dl, al
	mov cl, 4
	shr al, cl

	mov bl, 10
	mul bl
	and dl, 00001111b
	add al, dl
	
	mul al
	and al, 11111110b	;保证al为偶数
	mov ah, 0
	mov bx, ax
		
	cmp bx, 3400
	jb noBound
	sub bx, 160*4	;防止食物越界

noBound:
	cmp word ptr es:[bx], 0700h
	jne randomFoodRet
	
	mov word ptr es:[bx], 4432h
randomFoodRet:
	pop cx
	pop bx
	pop ax
	ret
;===============================
replayDirection:
	mov bx,  KEY_SEQUENCE_TOP
	mov bl, ds:KEY_SEQUENCE[bx]
	
	cmp bl, 0ffh
	je replayOver
	mov bh, 0
	add bx, bx
	call word ptr ds:MOVE[bx]
	
	inc  KEY_SEQUENCE_TOP
	ret
;===============================
isMoveDirection:
	mov bx, MOVE_ADDRESS
	add bx, bx
	call word ptr ds:MOVE[bx]
	ret
delay:	;延时, 消耗cpu
	push ax
	push dx

	mov ax, 0
	mov dx, 1000h

delay_:	
	sub ax, 2000h
	sbb dx, 0
	cmp dx, 0
	je delayRet
	jmp delay_

delayRet:
	pop dx
	pop ax
	ret
;===============================
printSnake:
	push bx
	push cx

	mov cx, SNAKE_LEN
	mov bx, OFFSET SNAKE_
	mov dx, SNAKE_COLOR

print_snake:
	mov di, ds:[bx]		;取到ds:bx处的数字
	mov es:[di], dx
	add bx, 2
	loop print_snake
	
	pop cx
	pop bx
	ret
;===============================
initSnake:
;	push bx
;	mov bx, OFFSET SNAKE_
;	mov word ptr ds:[bx+0], 160*10+40*2+0
;	mov word ptr ds:[bx+2], 160*10+40*2-2
;	mov word ptr ds:[bx+4], 160*10+40*2-4
;	
;	call printSnake
;	pop bx
	
	mov bx, OFFSET SNAKE_
	mov si, 160*10 + 40*2
	mov dx, SNAKE_COLOR
	
	mov word ptr ds:[bx], 0
	mov ds:[bx+2], si
	mov es:[si], dx

	sub si, 2
	add bx, 4

	mov word ptr ds:[bx], 0
	mov ds:[bx+2], si
	mov es:[si], dx

	sub si, 2
	add bx, 4

	mov word ptr ds:[bx], 4
	mov ds:[bx+2], si
	mov es:[si], dx

	ret
;===============================
initReg:
	mov ax, 0b800h
	mov es, ax
	mov ax, data
	mov ds, ax
	ret
;===============================
clearScreen:
	push bx
	push cx

	mov bx, 0
	mov cx, 2000
	mov dx, 0700h

clear_screen:
	mov es:[bx], dx
;	mov byte ptr es:[bx], 0
	add bx, 2
	loop clear_screen

	pop cx
	pop bx
	ret
;===============================
newInt9:
	push ax
	in al, 60h 	;从60h端口读取一个字节
	pushf
	call dword ptr cs:[200h]
	
	cmp al, 01h 	;ESC
	je play
	
	cmp al, UP
	je isUp
	cmp al, DOWN
	je isDown
	cmp al, LEFT
	je isLeft
	cmp al, RIGHT
	je isRight

	cmp al, 3bh	;F1
	jne newInt9Ret
	call changeScreenColor
	
newInt9Ret:
	pop ax
	iret
;===============================
;play:	
;	cmp byte ptr ds:KEY_SEQUENCE[bx], 9
;	je playRet
;	call delay
;	cli
;	call word ptr ds:MOVE[bx]
;	sti	
;	jmp play

;playRet:	

play:
	pop ax
	add sp, 4
	popf
	jmp replayGame
;	mov bx, OFFSET KEY_SEQUENCE
;	cmp byte ptr ds:KEY_SEQUENCE[bx], 0ffh
;	je playRet
;	call delay
;	cli
;	call word ptr ds:MOVE[bx]
;	sti	
	
;playRet:	
;===============================
;MOVE		dw OFFSET isMoveUp	0	
;		dw OFFSET isMoveDown	2
;		dw OFFSET isMoveRight	4
;		dw OFFSET isMoveLeft	6

isUp:
	mov byte ptr es:[160*24+40*2], 'U'
;	mov dl, 0
;	call setKeySequence
	cmp MOVE_ADDRESS, 1
	je newInt9Ret
	call isMoveUp
	jmp newInt9Ret
	
isDown:
	mov byte ptr es:[160*24+40*2], 'D'
;	mov dl, 1
;	call setKeySequence
	cmp MOVE_ADDRESS, 0
	je newInt9Ret
	call isMoveDown1
	jmp newInt9Ret
	
isLeft:
	mov byte ptr es:[160*24+40*2], 'L'
	;mov dl, 2
	;call setKeySequence
	;cmp MOVE_ADDRESS, 3
	;je newInt9Ret
	call isMoveLeft1
	jmp newInt9Ret
	
isRight:
	mov byte ptr es:[160*24+40*2], 'R'
;	mov dl, 3
;	call setKeySequence
	cmp MOVE_ADDRESS, 2
	je newInt9Ret
	call isMoveRight1
	jmp newInt9Ret
;===============================	
setKeySequence:
	mov bx, KEY_SEQUENCE_TOP
	mov byte ptr ds:KEY_SEQUENCE[bx], dl
	inc KEY_SEQUENCE_TOP
	ret
;===============================
isFood:
	mov bx, OFFSET SNAKE_
	add bx, SNAKE_LEN
	add bx, SNAKE_LEN
	
	mov cx, SNAKE_LEN
eat_food:
	push ds:[bx-2]
	pop ds:[bx+0]
	sub bx, 2
	loop eat_food
	
	mov ds:SNAKE_[0], si

	push SNAKE_COLOR
	pop es:[si]	;改食物的颜色
	
	inc SNAKE_LEN

	ret
;===============================
;isMoveUp:
;	mov bx, OFFSET SNAKE_
;	mov si, ds:[bx+0]
;	sub si, 160	
;	cmp word ptr es:[si], 0700h
;	jne isMoveUpRet	;如果遇到边界, 则不能移动
;	
;	call drawNewSnake
;	mov MOVE_ADDRESS, 0
;	ret

;isMoveUpRet:
;	call isFood1	
;	ret
;===============================
isMoveUp:
	mov bx, OFFSET SNAKE_
	add bx, SNAKE_HEAD
	mov si, ds:[bx+2]
	sub si, 160
	
	cmp word ptr es:[si], 0700h
	jne noMoveUp
	call drawNewSnake1
	ret
	
noMoveUp:
	call isFood1
	ret
;===============================
isMoveDown1:
	mov bx, OFFSET SNAKE_
	add bx, SNAKE_HEAD
	mov si, ds:[bx+2]
	add si, 160
	
	cmp word ptr es:[si], 0700h
	jne noMoveDown1
	call drawNewSnake1
	ret
	
noMoveDown1:
	call isFood1
	ret
;===============================
isMoveLeft1:
	mov bx, OFFSET SNAKE_
	add bx, SNAKE_HEAD
	mov si, ds:[bx+2]
	sub si, 2
	
	cmp word ptr es:[si], 0700h
	jne noMoveLeft1
	call drawNewSnake1
	ret
	
noMoveLeft1:
	call isFood1
	ret
;===============================
isMoveRight1:
	mov bx, OFFSET SNAKE_
	add bx, SNAKE_HEAD
	mov si, ds:[bx+2]
	add si, 2
	
	cmp word ptr es:[si], 0700h
	jne noMoveRight1
	call drawNewSnake1
	ret
noMoveRight1:	
	call isFood1
	ret
;===============================
isFood1:
	cmp word ptr es:[si], 4432h
	jne noFood
	call eatFood
	call randomFood 
noFood:
	ret
;===============================
eatFood:
	push SNAKE_NODE
	pop ds:[bx+0]
	
	mov bx, OFFSET SNAKE_
	add bx, SNAKE_NODE
	
	mov word ptr ds:[bx+0], 0
	mov ds:[bx+2], si
	
	push SNAKE_COLOR
	pop es:[si]
	
	push SNAKE_NODE
	pop SNAKE_HEAD
	
	add SNAKE_NODE, 4
	ret
;===============================
isMoveDown:
	mov bx, OFFSET SNAKE_
	mov si, ds:[bx+0]
	add si, 160		
	
	cmp word ptr es:[si], 0700h
	jne isMoveDownRet	;如果遇到边界, 则不能移动
	
	call drawNewSnake
	mov MOVE_ADDRESS, 1
	ret

isMoveDownRet:	
	call isFood1	
	ret
;===============================
isMoveLeft:
	mov bx, OFFSET SNAKE_
	mov si, ds:[bx+0]
	sub si, 2		
	
	cmp word ptr es:[si], 0700h
	jne isMoveLeftRet	;如果遇到边界, 则不能移动
	
	call drawNewSnake
	mov MOVE_ADDRESS, 2

	ret
isMoveLeftRet:	
	call isFood1
	ret
;===============================
isMoveRight:
	mov bx, OFFSET SNAKE_
	mov si, ds:[bx+0]
	add si, 2		
	
	cmp word ptr es:[si], 0700h
	jne isMoveRightRet	;如果遇到边界, 则不能移动
	
	call drawNewSnake
	mov MOVE_ADDRESS, 3
	ret

isMoveRightRet:	
	call isFood1	
	ret
;===============================
drawNewSnake1:
	push SNAKE_TAIL
	pop ds:[bx+0]
	
	mov bx, OFFSET SNAKE_
	add bx, SNAKE_TAIL
	
	mov di, ds:[bx+2]	
	mov word ptr es:[di], 0700h
	
	mov ds:[bx+2], si
	push SNAKE_COLOR
	pop es:[si]
	
	push SNAKE_TAIL
	pop SNAKE_HEAD
	
	push ds:[bx+0]
	pop SNAKE_TAIL
	mov word ptr ds:[bx+0], 0

	ret
;===============================
drawNewSnake:
	call clearOldSnake
	call setNewSnake
	call printSnake

	ret
;===============================
setNewSnake:
;	mov word ptr ds:[bx+0], 160*10+40*2+0	;头
;	mov word ptr ds:[bx+2], 160*10+40*2-2	;身体
;	mov word ptr ds:[bx+4], 160*10+40*2-4	;尾

;	mov bx, OFFSET SNAKE_
;	mov ax, ds:[bx+0]	;身体
;	mov dx, ds:[bx+2]	;尾
;	
;;	;原来的头变为身体
;	;原来的身体变尾
;	mov ds:[bx+2], ax
;	mov ds:[bx+4], dx
;	mov ds:[bx+0], si

;	mov bx, OFFSET SNAKE_
;	add bx, SNAKE_LEN
;	add bx, SNAKE_LEN
;;	sub bx, 2
;	
;	mov cx, SNAKE_LEN
;	dec cx

;set_new_snake:
;	push ds:[bx-2]
;	pop ds:[bx+0]
;	sub bx, 2
;	loop set_new_snake
;	
;	mov ds:SNAKE_[0], si

;	push ds:[bx+2]
;	pop ds:[bx+4]
;	push ds:[bx+0]
;	pop ds:[bx+2]
;	mov ds:[bx+0], si
	
	mov bx, OFFSET SNAKE_
	add bx, SNAKE_LEN
	dec bx
	mov ds:SNAKE_[bx], si
	ret
;===============================
clearOldSnake:	
	mov bx, OFFSET SNAKE_
	mov cx, SNAKE_LEN
	mov dx, SCREEN_COLOR

clear_old_snake:
	mov di, ds:[bx]
	mov word ptr es:[di], dx
	add bx, 2
	loop clear_old_snake
	ret
;===============================
changeScreenColor:
	push bx
	push cx
	push es

	mov bx, 0b800h
	mov es, bx
	mov cx, 2000
	mov bx, 1

change_screen_color:
	inc byte ptr es:[bx]
	add bx, 2
	loop change_screen_color

	pop es
	pop cx
	pop bx
	ret
;==============================
snakeEnd:
	nop
;==============================
setNewInt9:
	mov ax, 0
	mov es, ax

	cli
	mov word ptr es:[9*4], OFFSET newInt9 - OFFSET snake + 7e00h
	mov word ptr es:[9*4+2], 0
	sti
	ret
;==============================
saveOldInt9:
	mov bx, 0
	mov es, bx

	push es:[9*4]
	pop es:[200h]
	push es:[9*4+2]
	pop es:[202h]

	ret
;==============================
cpySnake:
	mov bx, 0
	mov es, bx
	mov ax, cs
	mov ds, ax
	mov si, OFFSET snake
	mov di, 7e00h
	mov cx, OFFSET snakeEnd - OFFSET snake
	cld
	rep movsb
	ret

code ends

end start

