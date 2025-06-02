"use strict";

class Vector {
	constructor(x, y) {
		this.x = x;
		this.y = y;
	}
	get mod() {
		return Math.sqrt((this.x * this.x) + (this.y * this.y));
	}
	static print(v) {
		console.log(`(${v.x.toFixed(2)}, ${v.y.toFixed(2)}); Mod: ${v.mod.toFixed(2)}`);

	}
	static add(u, v) {
		return new Vector(u.x + v.x, u.y + v.y);
	}
	static subtract(u, v) {
		return new Vector(u.x - v.x, u.y - v.y);
	}
	static dotProduct(u, v) {
		return (u.x * v.x) + (u.y * v.y);
	}
	static scale(r, v) {
		return new Vector(v.x * r, v.y * r);
	}
	static normalize(v) {
		if (v.mod === 0)
			return new Vector(0, 0);
		return new Vector(v.x / v.mod, v.y / v.mod);
	}
}
