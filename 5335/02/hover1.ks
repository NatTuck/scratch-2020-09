
lock steering to up.
lock throttle to 1.0.
stage.

until false {
    if ship:altitude < 1000 {
        lock throttle to 1.0.
    }
    else {
        lock throttle to 0.0.
    }

    wait 0.01.
}


