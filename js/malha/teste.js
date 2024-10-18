let success, res;

console.log("----- Testando getLineEquation() -----");

success = 0;

console.log("Reta vertical:");
res = getLineEquation({x: 0, y: 10}, {x: 0, y: 20});
if (res.slope === Infinity) {
	console.log("Passou");
	success++;
}
console.log(res);

console.log("Reta horizontal:");
res = getLineEquation({x: 10, y: 0}, {x: 20, y: 0});
if (res.slope === 0 && res.intercept === 0) {
	console.log("Passou");
	success++;
}
console.log(res);

console.log("Reta comum passando pela origem:");
res = getLineEquation({x: 0, y: 0}, {x: 1, y: 1});
if (res.slope === 1 && res.intercept === 0) {
	console.log("Passou");
	success++;
}
console.log(res);

console.log("Reta comum que não passa pela origem:");
res = getLineEquation({x: 0, y: 1}, {x: 1, y: 2});
if (res.slope === 1 && res.intercept === 1) {
	console.log("Passou");
	success++;
}
console.log(res);

console.log(`Taxa de sucesso: ${success}/4`);
