const fs = require('fs');

let first = true;

for (const file of fs.readdirSync('src')) {
	if (first) first = false;
	else process.stdout.write('\n\n');
	process.stdout.write(`/* ${file} */\n\n`);
	process.stdout.write(fs.readFileSync(`src/${file}`));
}
