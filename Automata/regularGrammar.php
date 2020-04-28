<?php

/*
 
 This script accepts a formatted text file describing a finite automaton,
  reads the FA definition, verifies its properties (deterministic, etc),
  and allows the user to check acceptance of a specific input string
  or find all input strings up to specified length that are accepted
 
 */

/* SAMPLE DFA INPUT
 RG
 ---
 S A B
 ---
 0 1
 ---
 S
 ---
 S,1S
 S,A
 A,01A
 A,B
 B,0B
 B,e
 ---
 This regular right-linear defines the language containing all strings in 1*(01)*0*
 */

// Place shorter strings before longer strings,
// use string ordering when equal length
function lensort($a,$b){
    if( strlen($a) == strlen($b) )
        return strcmp($a,$b);
    
    return strlen($a)-strlen($b);
}

function verifyGrammar($g)
{
    list($variables,$terminals,$initial,$productions) = $g;

    // check initial variable
    if( ! in_array($initial,$variables) )
    {
        return("$initial is not a recognized variable and cannot be the initial variable.\n");
    }

    foreach( array_keys($productions) as $key )
    {
        if( ! in_array($key,$variables) )
        {
            return("$key is not a variable and cannot appear as the LHS in a production.\n");
        }
        foreach( $productions[$key] as $what )
        {
            if( $what == 'e' ) // epsilon production
                continue;
            $len = strlen($what);
            $sym = $what[$len-1];
            if( (! in_array($sym,$variables)) && (! in_array($sym,$terminals)) )
            {
                return("$sym is not a recognized symbol and cannot appear in production RHS.\n");
            }
            for( $i = 0; $i < $len-1; $i++ )
            {
                $sym = $what[$i];
                if( in_array($sym,$variables) )
                {
                    return("$sym is a variable and cannot appear in production RHS except as last symbol.\n");
                }
                if( ! in_array($sym,$terminals) )
                {
                    return("$sym is not a recognized symbol and cannot appear in production RHS.\n");
                }
            }
        }
    }
    
    return true;
}

function listGrammar($g,$limit=10)
{
    list($variables, $terminals, $initial, $productions) = $g;
    $D = $productions[$initial];
    $A = array( );

    while( count($D) > 0 )
    {
        // get sentential form
        $s = array_shift($D);
   
        // produced empty string
        if( $s == 'e' || $s == "" )
        {
            array_push($A,"");
            continue;
        }
   
        // only variable could be last symbol
        // if no variables left, remember generated sentence   
        if( in_array($s[strlen($s)-1],$terminals) && strlen($s) <= $limit )
            array_push($A,$s);
      
        // otherwise, expand if still within limit (not counting variable)
        else if( strlen($s)-1 <= $limit )
        {
            $v = $s[strlen($s)-1]; // get trailing variable
            $w = substr($s,0,strlen($s)-1); // get prefix of terminals
            foreach( $productions[$v] as $rhs )
            {
                if( $rhs == 'e' ) // epsilon production
                    array_push($D,$w);
                else 
                    array_push($D,$w.$rhs);
            }
        }
    }

   $A = array_unique($A);
   usort($A,"lensort");

   if( $A[0] == "" )
       $A[0] = "[empty]";
       
   return $A;
}

// check that filename provided as command-line argument
if( $argc == 1 ) 
{
    exit("You must provide input filename as command-line argument.\n");
}

$filename = $argv[1];

$input = ( $argc > 2 ? $argv[2] : "" );
    
/****** READ GRAMMAR DEFINITION FROM INPUT FILE ******/
$contents = file_get_contents($filename) 
          or exit("Unable to read file \"$filename\"");
//echo "======\n$contents\n======\n\n";
list($type, $variables, $terminals, $initial, $productions, $comments) = explode("---",$contents);

$type = trim($type);
$variables = explode(" ",trim($variables)); 
$terminals = explode(" ",trim($terminals));
$initial = trim($initial);
$productions = explode("\n",trim($productions));
    $prod = array( );
    foreach( $productions as $t )
    {
        list($var,$str) = explode(",",trim($t));
        if( array_key_exists($var,$prod) ) // transition already defined
            array_push($prod[$var],$str);
        else // first definition for this transition
            $prod[$var] = array($str);
    }
    
$g = array($variables, $terminals, $initial, $prod);

// Regular grammar
if( $type == "RG" )
{
    $r = verifyGrammar($g);
    if( $r === true )
    { 
        echo "Grammar is valid\n";
        $all_strings = listGrammar($g);
        if( strlen($input) > 0 )
            echo "Grammar ".(in_array($input,$all_strings) ? "produces" : "does not produce" )." the string $input\n";
        else
            echo "Grammar produces ".implode($all_strings,", ")."\n";
    }
    else // invalid 
        echo "Grammar is not valid:\n$r\n";
}        
else
    echo "This script can only process regular grammars (not $type)\n";

