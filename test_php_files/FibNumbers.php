<?php

function fib($n) {
    if ($n == 1 || $n == 0) {
        return $n;
    } else {
        return fib($n-1) + fib($n-2);
    }
}

echo fib((int) readline()); //13
