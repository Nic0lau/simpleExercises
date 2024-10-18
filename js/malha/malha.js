/* Axiomas 
 * M1 - Toda reta têm exatamente três pontos
 * M2 - Por cada ponto passam exatamente duas retas
 * M3 - Por dois pontos passa no máximo uma reta
 * M4 - Há ao menos um ponto no plano
 * 2-3 com 12: 
 * P = {A, B, C, D, E, F, G, H, I, J, K, L}
 * R = {{A, B, C}, {A, D, E}, {B, D, F}, {C, E, F}, {G, H, I}, {G, J, K}, {H, J, L}, {I, K, L}}
 * 2-3 com 18:
 * P = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R}
 * R = {{A, B, C}, {A, D, E}, {B, D, F}, {C, E, F}, {G, H, I}, {G, J, K}, {H, J, L}, {I, K, L}, {M, N, O}, {M, P, Q}, {N, P, R}, {O, Q, R}}
 * 2-n com 2^n:
 * P = {1, 2, 3, 4, ..., 2^n}
 * R = {{1, 2, 3}, {1, 4, 5}, {2, 4, 6}, {3, 5, 6},
 * 	{7, 8, 9}, {7, 10, 11}, {8, 10, 12}, {9, 11, 12},
 * 	{13, 14, 15}, {13, 16, 17}, {14, 16, 18}, {15, 17, 18}...}
*/
"use strict";

class Point {
	constructor(n) {
		this.n = n;
		this.lineNum = 0;
	}
}

class Line {
	constructor(points) {
		this.points = points;
		this.slope = undefined;
		this.intercept = undefined;
	}
}

const LINES_PER_POINT = 2;
const LINE_SIZE = 3;
const POINT_AMOUNT = 6;

function createPlan(n) {
	let plan = new Array(n);
	for (let i = 0;i < n;i++)
		plan[i] = new Point(i);

	return plan;
}

function checkArrayEquality(a1, a2) {
	return a1.every(e => a2.includes(e));
}

function getAllLinePairs(l) {
	let pairs = [];
	for (let i = 0;i < l.length;i++)
		for (let j = i + 1;j < l.length;j++)
			pairs.push([l[i], l[j]]);
	return pairs;
}

function checkCollision(l1, l2) {
	let p1 = getAllLinePairs(l1);
	let p2 = getAllLinePairs(l2);

	return p1.every(e => p2.every(f => !checkArrayEquality(e, f)));
}

function checkLine(lines, line) {
	for (let e = lines.head;e;e = e.next)
		if (!checkCollision(e.points, line))
			return false
	return true;
}

function createLines(plan) {
	let lines, time;

	lines = new LinkedList();
	time = performance.now();

	while (!plan.every(e => e.lineNum === LINES_PER_POINT)) {
		lines.clear();
		
		plan.forEach(e => { e.lineNum = 0; });

		for (let k = 0;k < plan.length*2 && !plan.every(e => e.lineNum === LINES_PER_POINT);k++) {
			let currentLine = [], tryFailed = false;
			
			for (let i = 0, breakCounter = 0;i < LINE_SIZE;i++, breakCounter++) {
				if (breakCounter >= plan.length) { /* TODO: Change this shit later */
					tryFailed = true;
					break;
				}
				let rng = Math.floor(Math.random() * plan.length);
				if (plan[rng].lineNum === LINES_PER_POINT || currentLine.includes(plan[rng].n))
					i--;
				else 
					currentLine[i] = plan[rng].n;			
			}

			if (tryFailed)
				break;

			if (checkLine(lines, currentLine)) {
				lines.add(new Line(currentLine));
				currentLine.forEach(e => { plan[e].lineNum++; });
			}
		}
	}

	console.log(`Time: ${performance.now() - time}ms`);
	console.log(lines.toArray());
	return lines.toArray();
}

function getLineEquation(p1, p2) {
	let slope = (p2.y - p1.y)/(p2.x - p1.x);
	let intercept = p1.y - (slope * p1.x);
	return {
		slope: slope,
		intercept: intercept
	};
}
