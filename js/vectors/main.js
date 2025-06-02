"use strict";

const ctx = canv.getContext("2d");

const DPR = window.devicePixelRatio;
const RECT = canv.getBoundingClientRect();

const BALL_AMOUNT = 20;

let balls = Array(BALL_AMOUNT);

function resize_canv() {
	canv.width = RECT.width * DPR;
	canv.height = RECT.height * DPR;
	
	ctx.scale(DPR, DPR);
	
	canv.style.width = `${RECT.width}px`;
	canv.style.height = `${RECT.height}px`;
}

function random_color() {
	return `#${Math.floor(Math.random()*0xFFFFFF).toString(16).padStart(6, '0')}`;
}

function rand(min, max) {
	return (Math.random() * (max - min) + min);
}

function setup() {
	for (let i = 0; i < BALL_AMOUNT; i++)
		balls[i] = new Ball(
			new Vector(rand(MAX_RADIUS, canv.width - MAX_RADIUS), rand(MAX_RADIUS, canv.height - MAX_RADIUS)),
			new Vector(rand(MIN_VELOCITY, MAX_VELOCITY), rand(MIN_VELOCITY, MAX_VELOCITY)),
			rand(MIN_MASS, MAX_MASS),
			random_color()
		)
}

/* Collision not working */
function update() {
	ctx.clearRect(0, 0, canv.width, canv.height);
	balls.forEach((b, i) => {
		if (b.position.x + b.velocity.x + b.radius > canv.width || b.position.x + b.velocity.x - b.radius < 0) {
			b.velocity.x *= -1;
			b.color = random_color();
		}

		if (b.position.y + b.velocity.y + b.radius > canv.height || b.position.y + b.velocity.y - b.radius < 0) {
			b.velocity.y *= -1;
			b.color = random_color();
		}

		for (let j = i + 1; j < BALL_AMOUNT; j++) {
			let dist = Vector.subtract(b.position, balls[j].position);

			if (dist.mod <= b.radius + balls[j].radius) {
				let normal = Vector.normalize(dist);
				let relVel = Vector.subtract(b.velocity, balls[j].velocity);
				let velDotNormal = Vector.dotProduct(relVel, normal);

				if (velDotNormal > 0)
					continue;

				let impulse = Vector.scale(-(2 * velDotNormal) / (1 / b.mass + 1 / balls[j].mass), normal);


				b.velocity = Vector.add(b.velocity, Vector.scale(1 / b.mass, impulse));
				balls[j].velocity = Vector.subtract(balls[j].velocity, Vector.scale(1 / balls[j].mass, impulse));

				let overlap = b.radius + balls[j].radius - dist.mod;
				let correction = Vector.scale(overlap / 2, normal);
				b.position = Vector.add(b.position, correction);
				balls[j].position = Vector.subtract(balls[j].position, correction);

				b.color = random_color();
				balls[j].color = random_color();
			}
		}

		b.position = Vector.add(b.position, b.velocity);
	});
}

function draw(ball) {
	ctx.strokeStyle = ball.color;
	ctx.fillStyle = ball.color;

	ctx.beginPath();
	ctx.arc(ball.position.x, ball.position.y, ball.radius, 0, Math.PI*2, false);
	ctx.fill();

	ctx.strokeStyle = "#FF0000";
	ctx.beginPath();
	ctx.moveTo(ball.position.x, ball.position.y);
	ctx.lineTo(ball.position.x + ball.velocity.x * 5, ball.position.y + ball.velocity.y * 5);
	ctx.stroke();
}

function loop() {
	update();
	balls.forEach(b => { draw(b) });
	window.requestAnimationFrame(loop);
}

resize_canv();
setup();

window.requestAnimationFrame(loop);
