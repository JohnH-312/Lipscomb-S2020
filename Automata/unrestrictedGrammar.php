<?php

/*
 
 This script accepts a formatted text file describing an unrestricted grammar,
  reads the UG definition, verifies its properties,
  and allows the user to check generation of a specific input string
  or find all input strings up to specified length that are generated
 
 */

/* SAMPLE 
UG
---
S Q E A B X Y
---
0 1
---
S
---
S,QE
Q,0QA
Q,1QB
Q,e
E,e
AE,XE
AX,XA
BX,XB
0X,00
1X,10
BE,YE
AY,YA
BY,YB
0Y,01
1Y,11
---
This unrestricted grammar produces all strings in form ww, in {0,1}*
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

    // need to verify format for LHS/RHS of each production
//    foreach( array_keys($productions) as $key )
//    {
//        if( ! in_array($key,$variables) )
//        {
//            return("$key is not a variable and cannot appear as the LHS in a production.\n");
//        }
//        foreach( $productions[$key] as $what )
//        {
//            if( $what == 'e' ) // epsilon production
//                continue;
//            for( $i = 0; $i < strlen($what); $i++ )
//            {
//                $sym = $what[$i];
//                if( (! in_array($sym,$variables)) && (! in_array($sym,$terminals)) )
//                {
//                    return("$sym is not a recognized variable or terminal and cannot appear in production RHS.\n");
//                }
//            }
//        }
//    }
    
    return true;
}

function listGrammar($g,$limit=10)
{
    list($variables, $terminals, $initial, $productions) = $g;
    $D = $productions[$initial];
    $A = array( );
    $seen = array( ); // all sentential forms seen so far

    while( count($D) > 0 )
    {
        // get sentential form
        $s = array_shift($D);
   
        // produced empty string
        if( $s == 'e' || $s == "" )
        {
            array_push($A,"");
            array_push($seen,"");
            continue;
        }
   
        // count variables in sentential form
        $n = 0;
        for( $i = 0; $i < strlen($s); $i++ )
            $n += in_array($s[$i],$variables);
        
        // if no variables left, remember generated sentence   
        if( $n == 0 && strlen($s) <= $limit )
            array_push($A,$s);
      
        // otherwise, expand if still within limit (not counting variable)
        else if( $n > 0 && strlen($s) <= $limit+3 )
        {
            // for each index in string
            for( $i = 0; $i < strlen($s); $i++ )
            {
                // if this substring begins with LHS form
                foreach( array_keys($productions) as $key )
                {
                    if( strpos($s,$key,$i) === $i )
                    {
                        $before = substr($s,0,$i);
                        $after  = substr($s,$i+strlen($key),strlen($s));
                        foreach( $productions[$key] as $rhs )
                        {
                            // replace LHS with RHS, unless epsilon production
                            $next = $before.($rhs == 'e' ? "" : $rhs).$after;
                            if( ! in_array($next,$seen) ) // if haven't seen this yet
                            {
                                array_push($D,$next);
                                array_push($seen,$next);
                            }
                        }
                    }
                }
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
if( in_array($type,array("RG","CFG","ENG","UG")) )
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
    echo "This script can processes unrestricted grammars (not $type)\n";



