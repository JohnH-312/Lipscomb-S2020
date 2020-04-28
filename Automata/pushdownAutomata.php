<?php

/*

This script accepts a formatted text file describing a pushdown automaton,
 reads the PDA definition, verifies its properties 
 and allows the user to check acceptance of a specific input string
 or find all input strings up to specified length that are accepted

*/

/* SAMPLE PDA INPUT
    PDA
    ---
    A B C
    ---
    0 1
    ---
    M Z
    ---
    A
    ---
    Z
    ---
    C
    ---
    A,0,Z,A,MZ
    A,0,M,A,MM
    A,e,Z,B,Z
    A,e,M,B,M
    B,1,M,B,e
    B,e,Z,C,Z
    ---
    this PDA demonstrates format for input:
    states, input alphabet, stack alphabet, start state, initial stack symbol, accepting states, transitions
*/
// Place shorter strings before longer strings,
// use string ordering when equal length
function lensort($a,$b){
    if( strlen($a) == strlen($b) )
        return strcmp($a,$b);
    
    return strlen($a)-strlen($b);
}

function verifyPDA($pda)
{
    list($states, $alphabet, $stackalphabet, $initial, $stackinitial, $accepting, $delta) = $pda;
    
    array_push($stackalphabet,"e");
    array_push($alphabet,"e");

    // check initial state
    if( ! in_array($initial,$states) )
    {
        echo("$initial is not a recognized state and cannot be the initial state.\n");
        return false;
    }
    
    // check initial stack symbol
    if( ! in_array($stackinitial,$stackalphabet) )
    {
        echo("$stackinitial is not an element of the stack alphabet and cannot be the initial stack symbol.\n");
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
    
    foreach( array_keys($delta) as $key )
    {
        list($source,$symbol,$top) = explode(",",$key);
        if( ! in_array($source,$states) )
        {
            echo("$source is not a recognized state and cannot appear in a delta transition\n");
            return false;
        }
        if( ! in_array($symbol,$alphabet ) )
        {  
            echo("$symbol is not a recognized input character in this language and cannot appear in a delta transition\n");
            return false;
        }
        if( ! in_array($top,$stackalphabet ) )
        {  
            echo("$top is not a recognized stack symbol and cannot appear in a delta transition\n");
            return false;
        } 
        foreach( $delta[$key] as $where )
        {
            list($d,$s) = explode(",",$where);
            if( ! in_array($d,$states) )
            {
                echo("$d is not a recognized state and cannot appear in a delta transition\n");
                return false;
            }
            $push = str_split($s);
            foreach( $push as $p )
                if( ! in_array($p,$stackalphabet) )
                {
                    echo("$p is not a recognized stack symbol and cannot be pushed onto the stack\n");
                    return false;
                }
        }
    }
    return true;    
}

function acceptPDA($pda,$input)
{
    list($states, $alphabet, $stackalphabet, $initial, $stackinitial, $accepting, $delta) = $pda;
    $count = 0;
    $limit = strlen($input) + 1000; // stop infinite consideration (via cyclic epsilon transitions)
    $possible = array("$initial,$input,$stackinitial");

    while( !empty($possible) && $count < $limit)
    {
        list($here,$input,$stack) = explode(",",array_pop($possible));
        
        // Accept if reached accepting state at end of input
        if( ($input === "" || $input === FALSE ) && in_array($here,$accepting) )
            return true;
        
        // consider all possible transitions consuming next input symbol
        $symbol = $input[0]; // $input = substr($input,0,1);
        $top = $stack[0];    // $top = substr($stack,0,1);
        if( array_key_exists("$here,$symbol,$top",$delta) )
            foreach( $delta["$here,$symbol,$top"] as $transition )
            {
                list($next,$push) = explode(",",$transition);
                array_push($possible,"$next,".substr($input,1).",".( $push == "e" ? "" : $push ).substr($stack,1));
            }
        // consider all possible epsilon transitions (consuming no input)
        if( array_key_exists("$here,e,$top",$delta) )
            foreach( $delta["$here,e,$top"] as $transition )
            {
                list($next,$push) = explode(",",$transition);
                array_push($possible,"$next,$input,".( $push == "e" ? "" : $push ).substr($stack,1));
            }
        $count = $count + 1; // count how many paths considered
    }
    // exhausted all possible paths and found no accepting path
    return false;
}

function listPDA($pda,$limit=10)
{
   list($states, $alphabet, $stackalphabet, $initial, $accepting, $stackinitial, $delta) = $pda;
   
   $accepted = array( "" );
   $strings = $alphabet;
   while( count($strings) > 0 )
   {
      $s = array_shift($strings);
      if( strlen($s) < $limit )
         foreach( $alphabet as $letter ) // remember to check longer strings
            array_push($strings,$s.$letter);
      //echo "Check string $s\n";
      if( acceptPDA($pda,$s) )
         array_push($accepted,$s);
   }
   
   $accepted = array_unique($accepted);
   usort($accepted,"lensort");
   if( $accepted[0] == "" )
       $accepted[0] = "[empty]";
   return $accepted;
}

// ORDER: states, input alphabet, stack alphabet, initial state, accepting states, stack initial symbol, delta

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
//echo "======\n$contents\n======\n\n";
list($type, $states, $alphabet, $stackalphabet, $initial, $stackinitial, $accepting, $transitions, $comments) = explode("---",$contents);

$type = trim($type);
$states = explode(" ",trim($states)); 
$alphabet = explode(" ",trim($alphabet));
$stackalphabet = explode(" ",trim($stackalphabet));
$initial = trim($initial);
$stackinitial = trim($stackinitial);
$accepting = explode(" ",trim($accepting));
$transitions = explode("\n",trim($transitions));
    $delta = array( );
    foreach( $transitions as $t )
    {
        list($a,$b,$c,$d,$e) = explode(",",$t);
        $a = trim($a); $b = trim($b); $c = trim($c); $d = trim($d); $e = trim($e);
        $key = "$a,$b,$c";
        //echo("a = $a\nb = $b\nc = $c\nd = $d\ne = $e\n---\n");
        if( array_key_exists($key,$delta) ) // transition already defined
            array_push($delta[$key],"$d,$e");
        else // first definition for this transition
            $delta[$key] = array("$d,$e");
    }
    
$pda = array($states, $alphabet, $stackalphabet, $initial, $stackinitial, $accepting, $delta);

// PDA
if( $type == "PDA" )
{
    $r = verifyPDA($pda);
    if( $r === true )
    { 
        echo "PDA is valid\n";
        if( strlen($input) > 0 )
            echo("PDA  ".( acceptPDA($pda,$input) ? "accepts" : "rejects" )." the input $input\n");
        else
            echo "PDA accepts ".implode(listPDA($pda),", ")."\n";
    }
    else // invalid PDA
        echo "PDA is not valid:\n$r\n";
}        
else
    echo "This script can only process pushdown automata\n";
