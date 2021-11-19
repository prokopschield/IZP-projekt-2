const fetch = require('node-fetch');
const fs = require('fs');
const { nsblob } = require('nsblob');
const { nsprt } = require('nsprt');
const path = require('path');
const { watch } = require('ts-hound');

nsprt('.');

console.log(`Watching ${path.resolve('.')} for changes...`);

const good = new Set();

async function process_file(file) {
	const fp = path.resolve('.', file);
	const body = await fs.promises.readFile(fp);
	if (body.length < 3) return;
	const hash_body = await nsblob.store(body);
	if (good.has(hash_body)) return;
	const prettied = await fetch('https://cformat.nodesite.eu:20122/', {
		method: 'POST',
		body,
	}).then((a) => a.text());
	const hash_pretty = await nsblob.store(prettied);
	if (hash_body === hash_pretty) return;
	if (prettied.length < 12) return;
	good.add(hash_pretty);
	await fs.promises.writeFile(fp, prettied);
	console.log(
		`Prettied ${path.relative('.', file)} (${hash_body.substr(
			0,
			7
		)} -> ${hash_pretty.substr(0, 7)})`
	);
}

const hound = watch('.');
hound.on(
	'change',
	(file) =>
		path.relative('.', file).match(/^src\/.+\.c$/) && process_file(file)
);

process.on('unhandledRejection', () => {}).on('uncaughtException', () => {});
