const { exec } = require('child_process');
const fetch = require('node-fetch');
const fs = require('fs');
const { nsblob } = require('nsblob');
const { ask } = require('nsmt-nslibmgr/lib/ask');
const { run } = require('nsmt-nslibmgr/lib/run');
const { selector } = require('nsmt-nslibmgr/lib/selector');
const { nsprt } = require('nsprt');
const path = require('path');

nsprt('.');

console.log('Please write commit messages in the IMPERATIVE tense, lowercase.');
console.log('E.g. "improve search function" or "create file"\n');

async function process_file(file) {
	const fp = path.resolve('.', file);
	const body = await fs.promises.readFile(fp);
	const hash_body = await nsblob.store(body);
	const prettied = await fetch('https://cformat.nodesite.eu:20122/', {
		method: 'POST',
		body,
	}).then((a) => a.text());
	const hash_pretty = await nsblob.store(prettied);
	while (true) {
		const ans = await selector(`Commit ${file}?`, [
			'do not commit',
			`commit original (${hash_body.substr(0, 8)})`,
			`commit prettied (${hash_pretty.substr(0, 8)})`,
		]);
		if (!ans || !+ans) return false;
		const msg = await ask('What did you modify?');
		if (msg) {
			const full = `${file.replace('src/', '')}: ${msg}`;
			if (ans === 2) {
				await fs.promises.writeFile(fp, prettied);
			}
			await run(`git add ${file}`);
			await run(`git commit -m ${JSON.stringify(full)}`);
			return true;
		}
	}
}

async function go_through_files() {
	for (const file of process.argv.slice(2)) {
		await process_file(file).catch((error) => {
			console.error(error);
		});
	}
	const files = await new Promise((resolve) =>
		exec('git diff --name-only', (error, stdout, stderr) => {
			resolve(stdout.toString());
		})
	);
	for (const file of files.split(/[\r\n]+/g)) {
		if (file) {
			await process_file(file);
		}
	}
	process.exit(0);
}

go_through_files();

process.on('unhandledRejection', () => {}).on('uncaughtException', () => {});
