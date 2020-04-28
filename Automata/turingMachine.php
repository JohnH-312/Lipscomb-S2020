<?php
/*

This script accepts a formatted text file describing a Turing machine,
 reads the TM definition, verifies its properties 
 and allows the user to check acceptance of a specific input string
 or find all input strings up to specified length that are accepted

*/

/* SAMPLE TM INPUT
    TM
    ---
    A B C D E F
    ---
    0 1 2 X b
    ---
    0 1 2
    ---
    b
    ---
    A
    ---
    F
    ---
    A,0,B,b,R
    A,b,F,b,L
    A,X,A,b,R
    B,0,B,0,R
    B,1,C,X,R
    B,X,B,X,R
    C,1,C,1,R
    C,2,C,2,R
    C,b,D,b,L
    D,2,E,b,L
    E,0,E,0,L
    E,1,E,1,L
    E,2,E,2,L
    E,X,E,X,L
    E,b,A,b,R
    ---
    language : 0^n 1^n 2^n
    this TM demonstrates format for input:
    states, tape alphabet, input alphabet, blank symbol, start state, accepting states, transitions*/

// Place shorter strings before longer strings,
// use string ordering when equal length
function lensort($a,$b){
    if( strlen($a) == strlen($b) )
        return strcmp($a,$b);
    
    return strlen($a)-strlen($b);
}

function verifyTM($tm)
{
    list($states,$tapeAlpha,$inputAlpha,$blank,$initial,$accepting,$delta) = $tm;

    // check initial state
    if( ! in_array($initial,$states) )
    {
        echo("$initial is not a recognized state and cannot be the initial state.\n");
        return false;
    }

    // check input alphabet
    foreach( $inputAlpha as $letter )
    {
        if( ! in_array($letter,$tapeAlpha) )
        {
            echo("$letter is identified as part of the input alphabet but does not appear in the tape alphabet.\n");
            return false;
        }
    }
    
    // check blank symbol
    if( ! in_array($blank,$tapeAlpha) )
    {
        echo("$blank is not an element of the tape alphabet and cannot be the blank symbol.\n");
        return false;
    }
    
    // check each accepting state
    foreach( $accepting as $a )
    {
        if( ! in_array($a,$states) )
        {
            echo("$a is not a recognized state and cannot be an accepting state\n");
            return false;
        }
    }
    
    // each delta: current state, scanned symbol, new state, write symbol, move direction
    foreach( array_keys($delta) as $key )
    {
        list($current,$scanned) = explode(",",$key);
        list($next,$write,$move) = explode(",",$delta[$key]);
        if( ! in_array($current,$states) )
        {
            echo("$current is not a recognized state and cannot appear in a delta transition\n");
            return false;
        }
        if( ! in_array($scanned,$tapeAlpha ) )
        {  
            echo("$symbol is not a recognized tape alphabet character in this language and cannot be scanned in a delta transition\n");
            return false;
        }
        if( ! in_array($next,$states) )
        {
            echo("$next is not a recognized state and cannot be the destination in a delta transition\n");
            return false;
        } 
        if( ! in_array($write,$tapeAlpha) )
        {
            echo("$write is not a recognized tape alphabet character in this language and cannot be written in a delta transition\n");
            return false;
        }
        if( $move != 'L' && $move != 'R' )
        {
            echo("$move is not a recognized direction for movement (must be L/R) and cannot be part of any delta transition\n");
            return false;            
        }
    }
    return true;    
}
    
// parameters: turing machine, input, move limit (default 1000)
function acceptTM($tm, $input,$limit=1000)
{
    // copy input onto tape
    $tape = array( );
    for( $i = 0; $i < strlen($input); $i++ )
        $tape[$i] = $input[$i];
        
    list($states,$tapeAlpha,$inputAlpha,$blank,$initial,$accepting,$delta) = $tm;

    $s = $initial; // start in initial state
    $head = 0;
    $n = 0;
    while( ! in_array($s,$accepting) && $n < $limit )
    {
        // if this is the first time we look at this cell, write a blank here
        if( ! array_key_exists($head,$tape) )
            $tape[$head] = $blank;
        $key = "$s,".strval($tape[$head]);
        // if transition undefined for current state & tape symbol, fail
        if( ! array_key_exists($key,$delta) )
        {
            //echo "No transition is defined from ($key)\n";
            break;
        }
        // follow defined transition
        list($s,$write,$dir) = explode(",",$delta[$key]);
        $tape[$head] = $write;
        $head = $head + ( $dir == "R" ? 1 : ( $dir == "L" ? -1 : 0 ) );
    }
//    print_r($tape);
    return in_array($s,$accepting);
}

function listTM($tm,$limit=10)
{
   list($states, $tapeAlpha, $inputAlpha, $blank, $initial, $accepting, $delta) = $tm;
   
   $alphabet = $inputAlpha;
   $accepted = array( );
   $strings = $alphabet;
   while( count($strings) > 0 )
   {
      $s = array_shift($strings);
      if( strlen($s) < $limit )
         foreach( $alphabet as $letter ) // remember to check longer strings
            array_push($strings,$s.$letter);
      //echo "Check string $s\n";
      if( acceptTM($tm,$s) )
         array_push($accepted,$s);
   }
   
   $accepted = array_unique($accepted);
   usort($accepted,"lensort");
   return $accepted;
}

// ORDER: states, tape symbols, input alphabet, blank symbol, initial, accepting, delta

// check that filename provided as command-line argument
if( $argc == 1 ) 
{
    exit("You must provide input filename as command-line argument.\n");
}

$filename = $argv[1];

$input = ( $argc > 2 ? $argv[2] : "" );
    
/****** READ DEFINITION FROM INPUT FILE ******/
$contents = file_get_contents($filename) 
          or exit("Unable to read file \"$filename\"");
//echo "======\n$contents\n======\n\n";
list($type, $states, $tapeAlpha, $inputAlpha, $blank, $initial, $accepting, $transitions, $comments) = explode("---",$contents);
$type = trim($type);
$states = explode(" ",trim($states)); 
$tapeAlpha = explode(" ",trim($tapeAlpha));
$inputAlpha = explode(" ",trim($inputAlpha));
$blank = trim($blank);
$initial = trim($initial);
$accepting = explode(" ",trim($accepting));
$transitions = explode("\n",trim($transitions));
    $delta = array( );
    foreach( $transitions as $t )
    {
        // each: current state, scanned symbol, new state, write symbol, move direction
        list($a,$b,$c,$d,$e) = explode(",",trim($t));
        $key = "$a,$b";
        $delta[$key] = "$c,$d,$e"; // only one defined transition for state/symbol
        //echo("a = $a\nb = $b\nc = $c\nd = $d\ne = $e\n---\n");
        //if( array_key_exists($key,$delta) ) // transition already defined
        //    array_push($delta[$key],"$c,$d,$e");
        //else // first definition for this transition
        //    $delta[$key] = array("$c,$d,$e");
    }
$tm = array($states, $tapeAlpha, $inputAlpha, $blank, $initial, $accepting, $delta);

// TM
if( $type == "TM" )
{
    $r = verifyTM($tm);
    if( $r === true )
    { 
        echo "TM is valid\n";
        if( strlen($input) > 0 )
            echo("TM  ".( acceptTM($tm,$input) ? "accepts" : "rejects" )." the input $input\n");
        else
            echo "TM accepts ".implode(listTM($tm),", ")."\n";
    }
    else // invalid TM
        echo "TM is not valid:\n$r\n";
}        

