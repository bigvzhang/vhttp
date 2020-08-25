//
// Copyright (c) 2019-2020 Vic Zhang(VicBig at qq dot com)
//
// Distributed under the GNU General Public License, Version 3.(Please see
// more information at https://www.gnu.org/licenses/)
//
// Official repository: https://github.com/bigvzhang/vhttp
//

/**
 * start the http server 
 */
function start(port, docroot) {
	var server_file = require('koa-static');
	var range = require('koa-range');
	var koa = require('koa');
	var app = new koa();
	app.use(range);
	app.use(server_file(docroot));

	// omit error
	app.on("error",(err,ctx)=>{
		//console.log(err.toString() + " => " +ctx[0].toString()+ctx[1].toString());
	})
	app.listen(port);
}

/**
 * print help
 */
function print_help() {
	console.log(
		"Usage: node vhttp <port> <doc_root> \n" + 
		"Example:\n"                             +
		"    node vhttp  8080 . \n"
	)
}

/**
 *
 */
function direxits(path) {
	try {
		let stats = require('fs').lstatSync(path);
		if (stats.isDirectory()) {
			return true
		}
	}
	catch (e) {
	}
	return false
}

const args = process.argv;
if(args.length != 4 || !args[2].match(/^\d+$/)){
	return print_help()
}

let port = args[2] 
let doc_root = args[3] 

if(!direxits(doc_root)){
	console.error(`Directory ${doc_root} doesn't exist!`) 
	process.exit(1)
}
start(port, doc_root)
