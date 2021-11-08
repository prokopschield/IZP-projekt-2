const { default: store } = require('@prokopschield/nstore/lib/functions/store');

store('src')
	.then((_) => process.stdout.write(_))
	.then(() => process.exit(0));
