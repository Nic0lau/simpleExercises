function randomColor() {
/*
	var letters = '0123456789ABCDEF';
	var color = '#';
	for (var i = 0; i < 3; i++)
		color += letters[Math.floor(Math.random() * 16)];
  	return color;
*/
	let colors = [
		"black",
		"blue",
		"gray",
		"green",
		"purple",
		"red",
		"white",
		"yellow"
	];

	return colors[Math.floor(Math.random() * colors.length)];
}

let canv = document.getElementById("canv");
let ctx = canv.getContext("2d");
let plan = createPlan(POINT_AMOUNT); 
let lines = createLines(plan);

ctx.fillStyle = "red";

/* 
plan.forEach((e, i, arr) => {
	arr[i].x = Math.floor(Math.random() * canv.width);
	arr[i].y = Math.floor(Math.random() * canv.height);
	ctx.fillStyle = "red";
	ctx.fillRect(arr[i].x, arr[i].y, 5, 5);
});
*/

lines.forEach(e => {	
	let pointsWithCoords = [];

	e.points.forEach(p => {
		if (plan[p].x)
			pointsWithCoords.push(plan[p]);
	});

	if (pointsWithCoords.length === 0) {
		e.intercept = Math.floor(Math.random() * canv.height) - (canv.height / 2);
		e.slope = (Math.random() * 2) - 1;
	} else if (pointsWithCoords.length === 1) {
		e.slope = (Math.random() * 2) - 1;
		e.intercept = pointsWithCoords[0].y - (e.slope * pointsWithCoords[0].x);
	} else {
		let tmp = getLineEquation(pointsWithCoords[0], pointsWithCoords[1]);
		e.intercept = tmp.intercept;
		e.slope = tmp.slope;
	}

	e.points.forEach(p => {
		if (!plan[p].x) {
			for (let i = 0;(!plan[p].y || plan[p].y < 0 || plan[p].y > canv.height) && i < 10000;i++) {
				plan[p].x = Math.floor(Math.random() * canv.width);
				plan[p].y = (plan[p].x * e.slope) + e.intercept;
				ctx.fillRect(plan[p].x, plan[p].y, 15, 15);
			}
		}
	});

	ctx.strokeStyle = randomColor();
	ctx.lineWidth = 5;
	for (let i = 0;i < e.points.length - 1;i++) {
		ctx.moveTo(plan[e.points[i]].x, plan[e.points[i]].y);
		ctx.lineTo(plan[e.points[i + 1]].x, plan[e.points[i + 1]].y);
	}

	ctx.stroke();
});
