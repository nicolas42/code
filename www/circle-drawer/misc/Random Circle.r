rebol[]

random/seed now/precise

win: center-face layout [
	backcolor black	origin 0 
	
	;canvas
	canvas: box black 380x380 edge none effect [draw []]
	;timer -10x-10 rate 1 [draw-turtle]
	key keycode [left right] [draw-turtle]
	key #"^M" [draw-turtle]
	key #"^[" [quit]
]

turn: func [angle] [ang: ang + angle]

move: func [distance] [
	x: x - (distance * cosine ang)
	y: y - (distance * sine ang)
	append canvas/effect/draw as-pair x y
]

;Initialize all vars, generate draw-args and show the canvas.
draw-turtle: does [

	;canvas canvas for your painting

	ang: 90
	x: canvas/size/x / 2
	y: canvas/size/y / 2
	
	canvas/effect/draw: reduce [
		
		'pen random 255.255.255
		'fill-pen black
		
		'box -1x-1 canvas/size + 1
		'line-width 2 
		'line as-pair x y
	]
	
	t: random 360
	for m 1 360 1 [
		move m
		turn t
	]
	
	show canvas
	
]

insert-event-func [
	probe event/key
if event/type = 'resize [
	canvas/size: win/size
	show canvas
] event]

draw-turtle

view/options/title win [resize] "Turn"

