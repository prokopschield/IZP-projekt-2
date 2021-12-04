const fs = require('fs');

let first = true;

{
	const set = fs.readFileSync('src/130-set.c', 'utf-8');
	const rel = set
		.replace(/set/g, 'rel')
		.replace(/element/g, 'pair')
		.replace(/\-\>uid/g, '')
		.replace("'S'", "'R'");
	fs.writeFileSync('src/140-rel.c', rel);
}

for (const file of fs.readdirSync('src')) {
	if (first) first = false;
	else process.stdout.write('\n\n');
	process.stdout.write(`/* ${file} */\n\n`);
	process.stdout.write(`#line 1 "src/${file}"\n`);
	process.stdout.write(fs.readFileSync(`src/${file}`));
}

// fs.unlinkSync('src/140-rel.c');
