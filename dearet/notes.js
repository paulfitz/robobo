#!/usr/bin/env node

var reference_distance = 1.616e-35;  // meters
var reference_duration = 5.391e-44;  // seconds
var reference_watt = 3.629e52;       // watts
var plank_mass = 2.177e-8;           // kilograms

var mass_jupiter_in_kg = 1.89813e27;
var radius_jupiter_in_m = 6.9173e7;
var au_in_m = 1.496e11;
var day_in_s = 60*60*24;

var planets = [
    {
	"name": "planety1_e",
	"dist1": 6.51790e41,
	"dist2": 1.99700e43,
	"dur1": 1.18100e48,
	"dur2": 1.18100e48,
	"mass": 2.355e33
    },
    {
	"name": "planety2_b",
	"dist1": 6.13558e42,
	"dist2": 1.06256e45,
	"dur1": 2.34790e49,
	"dur2": 1.56528e49,
	"mass": 1.43936e34
    },
    {
	"name": "planety3_c",
	"dist1": 2.52650e42,
	"dist2":  2.22420e45,
	"dur1": 7.10978e49,
	"dur2": 7.97170e47,
	"mass": 1.59638e34
    },
    {
	"name": "planety4_f",
	"dist1": 2.16550e42,
	"dist2": 7.22880e45,
	"dur1": 4.16585e50,
	"dur2": 7.37196e47,
	"mass": 1.43936e34
    },
    {
	"name": "planety5_d",
	"dist1": 1.81905e43,
	"dist2": 5.31284e46,
	"dur1": 8.41464e51,
	"dur2": 6.91126e47,
	"mass": 3.75106e35
    },
    {
	"name": "moony",
	"dist1": 1.855e41,
	"dist2": 3.84840e43,
	"dur1": 1.99119e48,
	"dur2": 1.99119e48,
	"mass": 2.03180e31
    }
];

for (var i=0; i<planets.length; i++) {
    var planet = planets[i];
    var name = planet["name"];
    var mass_in_kg = planet["mass"] * plank_mass;
    var mass_in_jupiters = mass_in_kg / mass_jupiter_in_kg;
    var dist1_in_jupiters = planet["dist1"] * reference_distance / radius_jupiter_in_m;
    var dist2_in_au = planet["dist2"] * reference_distance / au_in_m;
    var dist2_in_jupiters = planet["dist2"] * reference_distance / radius_jupiter_in_m;
    var dur1_in_days = planet["dur1"] * reference_duration / day_in_s;
    var dur2_in_days = planet["dur2"] * reference_duration / day_in_s;
    console.log(name + " mass: j*" + mass_in_jupiters + " dist1: j*" + dist1_in_jupiters + " dist2: au*" + dist2_in_au + " dist2: j*" + dist2_in_jupiters + " dur1: day*" + dur1_in_days, "dur2: day*" + dur2_in_days);
}


var ticks = [
    5.94757e53,
    5.96576e53,
    5.99021e53,
    6.04122e53,
    6.05938e53,
    6.07606e53
];

var prev = 0;
for (var i=0; i<ticks.length; i++) {
    var tick = ticks[i];
    var triplet_time = tick*reference_duration;
    
    console.log("time signal: " + triplet_time + " seconds");
    console.log("  " + triplet_time/(60*60*24*365.2525) + " years");
    console.log("  elapsed " + ((tick-ticks[0])*reference_duration) + " seconds");
    console.log("  step " + ((tick-prev)*reference_duration) + " seconds");
    console.log("  step " + ((tick-prev)*reference_duration/(60*60*24)) + " days");
    prev = tick;
}

var star_age = 4.04900e60;
console.log("star age " + star_age*reference_duration/(60*60*24*365.2525*1e9) + " billion years");

var half_life = 3.35398e54*reference_duration;
console.log("half life " + half_life/(60*60*24*365.2525) + " years");

var planck_temperature = 1.41683e32;
console.log("temperature " + ((3.66110e-29)*planck_temperature) + " K");

var power = 6.66583e-27;
console.log("power " + (power*reference_watt) + " W");
