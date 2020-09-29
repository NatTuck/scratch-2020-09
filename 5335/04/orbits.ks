// Author: Nat Tuck
// From class meeting demo

function t2ea {
  parameter ta.
  parameter e.
  local y is sqrt(1-(e*e))*sin(ta).
  local x is e+cos(ta).
  return atan2(y, x).
}

// given an orbit, show angle from
// vernal equinox to body
// assume an equatorial orbit (inc = 0)
function absang {
  parameter obt.
  return mod(obt:lan +    // moves with AN
             obt:argumentofperiapsis + // move with AN
             obt:trueanomaly, 360). 
}

function norm {
    parameter ang.
    return mod(ang, 360).
}

function ang_diff {
  parameter a0. // future angle
  parameter a1. // current angle
  set a0 to norm(a0).
  set a1 to norm(a1).
  if (a0 > a1) {
    return a0 - a1.
  }
  else {
    return a0 - a1 + 360.
  }
}

print "mun ang".
local mun_ang is absang(mun:orbit).
print mun_ang.

print "ship ang.".
local ship_ang is absang(ship:orbit).
print ship_ang.

// burn angle
local burn_ang is absang(mun:orbit) + 180.
local d_theta is ang_diff(burn_ang, ship_ang).

local orbit_rate is ship:orbit:period / 360.

// this works if d_theta is talking about
// mean anomaly, not true anomaly
local burn_time is d_theta * orbit_rate.

// burn time
// how long until we get to burn_angle?
// assume circular orbit, fixed degrees/second
print "burn time".
print burn_time.

local nn is node(time:seconds + burn_time, 0, 0, 100).
add nn.


// Complication: non-circular orbit.

