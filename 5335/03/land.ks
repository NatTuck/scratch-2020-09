
// accel due to grav is ~0.5
global g is 0.5.

//lock steering to up.
stage.

function burn {
    print "burn". 
    SET SHIP:CONTROL:PILOTMAINTHROTTLE TO 1.0.
}

function coast {
    print "coast". 
    SET SHIP:CONTROL:PILOTMAINTHROTTLE TO 0.0.
}

function clamp {
    parameter x0.
    parameter x.
    parameter x1.
    return min(max(x0, x), x1).
}

coast().

// Hard-coding the start of the burn is bit too lazy 
// to be part of an "excellent" submission.
wait until alt:radar < 7500.

burn().

wait until abs(ship:verticalspeed) < 10.

coast().
//lock throttle to 0.0.

print "final seq".

SAS OFF.
lock steering to up.

until alt:radar < 5.0 {
    local zero_th is (g*ship:mass)/ship:maxthrust. 

    local alt_tgt is 1.
    local alt_err is alt:radar - alt_tgt.

    local vel_tgt is clamp(-100, -alt_err, 100).
    local vel_err is ship:verticalspeed - vel_tgt. 
    local vel_fix is -(vel_err / 200).

    lock throttle to clamp(0.0, zero_th + vel_fix, 1.0).
    wait 0.1.
} 
