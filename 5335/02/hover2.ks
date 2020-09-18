
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
    local alt_err is 1000 - ship:altitude.
    local zero_th is (9.8*ship:mass)/ship:maxthrust.
    local control is alt_err / 1000.
    lock throttle to clamp(0.0, zero_th + control, 1.0).
    wait 0.01.
}


