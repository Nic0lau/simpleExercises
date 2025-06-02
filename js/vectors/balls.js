"use strict";
const MIN_MASS = 1;
const MAX_MASS = 5;
const MIN_VELOCITY = 1;
const MAX_VELOCITY = 10;
const MAX_RADIUS = Math.sqrt(MAX_MASS/Math.PI) * 20;

class Ball {
	constructor(position, velocity, mass, color) {
		this.position = position;
		this.velocity = velocity;
		this.mass = mass;
		this.radius = Math.sqrt(mass/Math.PI) * 20;
		this.color = color;
	}
}
