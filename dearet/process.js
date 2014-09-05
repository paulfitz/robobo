#!/usr/bin/env node

var m = {};
m["66000066"] = "A";
m["66111166"] = "B";
m["62233226"] = "C";
m["XXXXXXXX"] = ".";
m["57667066"] = "+";
m["51662667"] = "=";
m["57655566"] = "E";
m["57666061"] = "^";
m["51660676"] = "<=";
m["51664667"] = ">=";
m["57676066"] = "*";
m["51777776"] = "set";
m["36327777"] = "[a]";
m["34154444"] = "[b]";
m["51636366"] = "!=";
m["35745555"] = "[c]";
m["37536666"] = "[d]";
m["57766566"] = "-";
m["57666566"] = "/";
m["27666000"] = "i";
m["06666664"] = "pi";
m["06666667"] = "e";

m["76666666"] = "[0]";
m["76666667"] = "[1]";
m["76666664"] = "[2]";
m["46666664"] = "[-2]";
m["76666662"] = "[4]";
m["76666767"] = "[101]";
m["46666647"] = "[-21]";
//m["76664636"]

var oct = {};
oct["0"] = 6;
oct["1"] = 7;
oct["2"] = 4;
oct["3"] = 5;
oct["4"] = 2;
oct["5"] = 3;
oct["6"] = 0;
oct["7"] = 1;

/*
-3 Hz, LCP => 0   [6]? 
-3 Hz, RCP => 1   [7]?
-1 Hz, LCP => 2   [4]?
-1 Hz, RCP => 3   [5]?
+1 Hz, LCP => 4   [2]
+1 Hz, RCP => 5   [3]?
+3 Hz, LCP => 6   [0]
+3 Hz, RCP => 7   [1]

// 76666451 C 76667475 A D 76667234 A 
//      237  +    1213  =      1452  octal? yay

*/

var fs = require("fs");
var txt = fs.readFileSync(process.argv[2],'utf-8');

var ks = Object.keys(m);
for (var i=0; i<ks.length; i++) {
    txt = txt.replace(new RegExp(ks[i], "g"),m[ks[i]]);
}
txt = txt.replace(/\n/g," ");
txt = txt.replace(/  +/g," ");

var parts = txt.split(" ");
var prev = "";
for (var i=0; i<parts.length; i++) {
    var p = parts[i];
    var ch = p.charAt(0);
    if (prev=="E") {
	var nf = 0;
	var f = 1;
	for (var j=0; j<p.length; j++) {
	    f /= 8.0;
	    var v = oct[p[j]];
	    nf += v*f;
	}
	var tf = "" + nf.toFixed(5);
	tf = tf.replace("0.","");
	parts[i] = tf;
    } else {
	if (ch=='7'||ch=='4') {
	    var ns = p.substr(1,p.length);
 	    var ni = 0;
	    for (var j=0; j<ns.length; j++) {
		ni *= 8;
		ni += oct[ns.charAt(j)];
	    }
	    parts[i] = "[" + (ch=='4'?'-':'') + ni + "]";
	}
    }
    prev = p;
}

txt = parts.join(" ");
txt = txt.replace(/A B/g,"\nA B");
txt = txt.replace(/ E /g,".");

console.log(txt);
