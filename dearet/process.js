#!/usr/bin/env node

var m = {};
m["66000066"] = ")";
m["66111166"] = "(";
m["62233226"] = ",";
m["XXXXXXXX"] = ".";
m["57667066"] = "+";
m["51662667"] = "=";
m["57655566"] = "E";
m["57666061"] = "^";
m["51660676"] = "<=";
m["51664667"] = ">=";
m["57676066"] = "*";
m["51777776"] = "set";
m["36327777"] = "[x]";
m["34154444"] = "[y]";
m["51636366"] = "!=";
m["35745555"] = "[z]";
m["37536666"] = "[w]";
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
m["06656642"] = "reference_duration";
m["06656673"] = "reference_distance";
m["06656676"] = "c_light";
m["06656645"] = "reference_watt";
m["12665554"] = "triplet?";
m["05663370"] = "c1";
m["04665767"] = "c2";
m["04665764"] = "c3";


m["53444476"] = "or";

m["33033333"] = "b";
m["32432222"] = "a";
m["30230000"] = "c";

m["06656667"] = "electron2proton";
m["06656666"] = "fine_structure";
m["06656664"] = "alpha_G";

m["06656665"] = "mass_electron";
m["06656662"] = "mass_proton";
m["06656660"] = "planck_mass";
m["06656663"] = "mass_neutron";
m["06656661"] = "h";
m["06656677"] = "two_pi_G";

m["06656674"] = "neg?_elementary_charge";
m["06656672"] = "electric_constant";
m["06656675"] = "hbar";

m["06656670"] = "sqrt_hbar_c_over_coulomb_const";

m["06656646"] = "planck_energy";

// xxxx
m["17756166"] = "n1";
m["17756266"] = "n2";
m["17756366"] = "n3";
m["17757666"] = "n4";
m["17756066"] = "n5";
m["17756766"] = "n6";


m["05665765"] = "sixful";

m["04665676"] = "mass?";
m["17756666"] = "solar_mass?";
m["04665677"] = "charge?";

m["07666664"] = "neutron";
m["07666667"] = "proton";
m["07666665"] = "electron";

m["07646677"] = "hydrogen_1";
m["07646674"] = "hydrogen_2";
m["07646647"] = "helium_3";
m["07646644"] = "helium_4";
m["07646607"] = "carbon_12";
m["07646604"] = "carbon_13";
m["07646605"] = "carbon_14";
m["07646614"] = "nitrogen_14";
m["07646615"] = "nitrogen_15";
m["07646767"] = "oxygen_16";
m["07646764"] = "oxygen_17";
m["07646765"] = "oxygen_18";
m["07646747"] = "neon_20";
m["07646744"] = "neon_21";
m["07646745"] = "neon_22";
m["07646742"] = "sodium_23";
m["07646726"] = "magnesium_24";
m["07646477"] = "sulpher_32";
m["07646464"] = "argon_40";
m["07646275"] = "iron_56";
//m[""] = "/";
//m[""] = "/";
//m[""] = "/";
//m[""] = "/";

m["07647667"] = "H2";
m["07647664"] = "H2O";
m["07647665"] = "O2";
m["07647676"] = "O3";
m["07647677"] = "N2";
m["07647674"] = "NO";
m["07647675"] = "CO";
m["07647646"] = "CO2";
m["07647647"] = "SO2";
m["07647644"] = "NH3";
m["07647645"] = "CH4";
m["07647656"] = "C2H6";
m["07647657"] = "?NSH5?";

m["04665766"] = "thinginess?";
m["04665674"] = "dist1?";
m["05665762"] = "dist2?";
m["05665763"] = "0_to_1_iness?";
m["05665760"] = "dur1?";
m["05665761"] = "dur2?";

m["05665776"] = "maybe_relative_to?";

// 07646... -- last line

// 07646 6 77 --> 11
// 07646 6 44 --> 22
// 07646 7 67 --> 01
// 07646 6 07 --> 61
// 07646 2 75 --> 13
// 07646 4 77 --> 11
// 07646 6 14 --> 72
// 07646 4 66 --> 00
// 07646 6 74 --> 12
// 07646 7 47 --> 21

// ( sqrt_hbar_c_over_coulomb_const = * ( [11].07062 , elementary_charge ) )
// should be something like 11.7062 no?

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
txt = txt.replace(/\) \(/g,")\n(");
txt = txt.replace(/ E /g,".");

console.log(txt);
