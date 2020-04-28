<?php

// This script tests a 4-state, 2-symbol busy beaver Turing machine
// We assume states A, B, C, D, plus halting state H; A is the initial state
// The symbols are 0 (blank) and 1
// Maximize the number of 1's on the tape when the program halts

// action table
// for example, "A,0" => "1,R,B" means that
//  if we read a 0 while in state A, then write a 1, move to the right, and enter state B
$delta = array(
    "A,0" => "1,R,B", 	// to B0, unless coming from A1 or , which  
    "A,1" => "1,L,A", 	// to A1 untill hit 0 
    "B,0" => "1,R,C", 	// to C1,
    "B,1" => "1,L,B", 	// to B0
    "C,0" => "1,L,A", 	// to A1
    "C,1" => "1,R,D", 	// to C0,
    "D,0" => "1,R,H", 	// to B0
    "D,1" => "1,R,D" 	// to B0
);

$state = "A"; // current state of machine
$head  = 0; // index on tape where head currently scans
$tape  = array( ); // tape contents (initially empty)
$limit = 150; // how many steps to run before assume infinite and kill
$steps = 0; // number of steps taken so far

while( $state != "H" && $steps < $limit )
{
    // if this is the first time we look at this cell, write a blank here
    if( ! array_key_exists($head,$tape) )
        $tape[$head] = 0;

    list($write,$dir,$state) = explode(",",$delta["$state,".strval($tape[$head])]);
    $tape[$head] = $write;
    $head = $head + ( $dir == "R" ? 1 : -1 ); // move right or left

    $steps = $steps + 1;
}

// count 1's on tape
$count = array_count_values($tape);
$ones = $count[1];

echo( $steps < $limit 
      ? "\nTM halted with $ones 1's on the tape after $steps steps.\n\n"
      : "\nTM was killed after $limit steps.\n\n"
    );

