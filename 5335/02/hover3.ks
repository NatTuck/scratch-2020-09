
lock steering to up.
lock throttle to 1.0.
stage.

function clamp {
    parameter x0.
    parameter x.
    parameter x1.
    return min(max(x0, x), x1).
}

until false {
    local zero_th is (9.8*ship:mass)/ship:maxthrust.
    print "zero th: " + zero_th.

    local alt_tgt is 1000.
    local alt_err is ship:altitude - alt_tgt.
    local alt_fix is -(alt_err / alt_tgt).
    print "alt tgt, err, fix: " + alt_tgt + "," + alt_err + "," + alt_fix.

    local vel_tgt is clamp(-100, -alt_err, 100).
    local vel_err is ship:verticalspeed - vel_tgt.
    local vel_fix is -(vel_err / 200).
    print "vel tgt, err, fix: " + vel_tgt + "," + vel_err + "," + vel_fix.

    lock throttle to clamp(0.0, zero_th + alt_fix + 0.0 * vel_fix, 1.0).
    wait 0.1.
}


