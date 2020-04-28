<?php

/*
 
 This script accepts a formatted text file describing a finite automaton,
  reads the FA definition, verifies its properties (deterministic, etc),
  and allows the user to check acceptance of a specific input string
  or find all input strings up to specified length that are accepted
 
 */

/* SAMPLE DFA INPUT
 DFA
 ---
 A B C
 ---
 0 1
 ---
 A
 ---
 C
 ---
 A,0,B
 A,1,A
 B,0,C
 B,1,A
 C,0,C
 C,1,A
 ---
 This DFA defines the language accepting all strings ending in 00
 */
    
    
    
// Place shorter strings before longer strings,
// use string ordering when equal length
function lensort($a,$b){
    if( strlen($a) == strlen($b) )
        return strcmp($a,$b);
    
    return strlen($a)-strlen($b);
}

// verify overall structure/format, deterministic, epsilon transitions
function verifyFA($fa,$deterministic=true,$epsilonAllowed=false)
{
    list($states, $alphabet, $initial, $accepting, $delta) = $fa;
    
    foreach( $states as $s )
    {
        foreach( $alphabet as $a )
        {
            if( $deterministic && ! array_key_exists("$s,$a",$delta) )
                return "In a deterministic finite automaton, the delta function must ".
                       "define exactly one transition for each state/symbol pair. ".
                       "You have not defined ($s,$a).";
            if( $deterministic && count($delta["$s,$a"]) > 1 ) 
                return "In a deterministic finite automaton, the delta function must ".
                       "define exactly one transition for each state/symbol pair. ".
                       "You have defined multiple transitions for ($s,$a).";
        }
        // check epsilon transitions
        if( (! $epsilonAllowed) && array_key_exists("$s,e",$delta) )
            return "No epsilon transitions should be defined in this FA. ".
                   "You have defined a transition for ($s,e)";
    }
    return true;
}

// determine (T/F) if $input is accepted by $fa
function acceptFA($fa,$input)
{
    list($states, $alphabet, $initial, $accepting, $delta) = $fa;
    $count = 0;
    $limit = strlen($input) + 1000; // stop infinite consideration (via cyclic epsilon transitions)
    $possible = array("$initial,$input");
    
    while( !empty($possible) && $count < $limit)
    {
        list($here,$input) = explode(",",array_pop($possible));
        //echo("At state $here, consider input $input\n");
    
        // Accept if reached accepting state at end of input
        if( ($input === "" || $input === FALSE ) && in_array($here,$accepting) )
            return true;
            
        // consider all possible transitions consuming next input symbol
        $symbol = $input[0];        
        if( array_key_exists("$here,$symbol",$delta) )
            foreach( $delta["$here,$symbol"] as $next )
                array_push($possible,$next.",".substr($input,1));
        // consider all possible epsilon transitions (consuming no input)
        if( array_key_exists("$here,e",$delta) )
            foreach( $delta["$here,e"] as $next )
                array_push($possible,$next.",".$input);
        $count = $count + 1; // count how many paths considered
    }
    // exhausted all possible paths and found no accepting path
    return false;
}

// identify and list all input strings in alphabet up to length $limit
//  that are accepted by $fa
function listFA($fa,$limit=10)
{
   list($states, $alphabet, $initial, $accepting, $delta) = $fa;
   
   $accepted = array( );
   $strings = $alphabet;
   while( count($strings) > 0 )
   {
      $s = array_shift($strings);
      if( strlen($s) < $limit )
         foreach( $alphabet as $letter ) // remember to check longer strings
            array_push($strings,$s.$letter);
      //echo "Check string $s\n";
      if( acceptFA($fa,$s) )
         array_push($accepted,$s);
   }
   
   $accepted = array_unique($accepted);
   usort($accepted,"lensort");
   if( $accepted[0] == "" )
       $accepted[0] = "[empty]";
   return $accepted;
}

// check that filename provided as command-line argument
if( $argc == 1 ) 
{
    exit("You must provide input filename as command-line argument.\n");
}

$filename = $argv[1];

$input = ( $argc > 2 ? $argv[2] : "" );
    
/****** READ AUTOMATON DEFINITION FROM INPUT FILE ******/
$contents = file_get_contents($filename) 
          or exit("Unable to read file \"$filename\"");
    
list($type, $states, $alphabet, $initial, $accepting, $transitions, $comments) = explode("---",$contents);

$type = trim($type);
$states = explode(" ",trim($states)); 
$alphabet = explode(" ",trim($alphabet));
$initial = trim($initial);
$accepting = explode(" ",trim($accepting));
$transitions = explode("\n",trim($transitions));
    $delta = array( );
    foreach( $transitions as $t )
    {
        list($a,$b,$c) = explode(",",$t);
        $a = trim($a); $b = trim($b); $c = trim($c);
        $key = "$a,$b";
        if( array_key_exists($key,$delta) ) // transition already defined
            array_push($delta[$key],$c);
        else // first definition for this transition
            $delta[$key] = array("$c");
    }

$fa = array($states, $alphabet, $initial, $accepting, $delta);

/*** CHECK VALIDITY **/
if( $type == "DFA" )
{
    $r = verifyFA($fa);
    echo( $r === true ? "DFA verified.\n" : "$r\n" );
}
else if( $type == "NFA" )
{
    $r = verifyFA($fa);
    echo( $r === true ? "NFA verified.\n" : "$r\n" );
}
else // $type == eNFA
{
    $r = verifyFA($fa, false, true);
    echo( $r === true ? "eNFA verified.\n" : "$r\n" );
}

/* if format was not verified, don't test FA */
if( $r === true ) // if verified
{
    // check specified input string, if available
    if( strlen($input) > 0 ) // have input string to check
        echo( "FA ".( acceptFA($fa,$input) ? "accepts" : "rejects" )." the input string $input\n");
    // otherwise, list all accepted strings within length limit
    else
        echo "FA accepts these strings:\n".implode(listFA($fa),", ")."\n";
}
