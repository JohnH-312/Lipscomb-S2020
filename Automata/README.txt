This folder contains scripts for testing formal grammars and language acceptors of various formats. The scripts are written and lightly tested in PHP 7.3.11; please report any errors that you find.

Sample grammars are provided, as:
sample-RG.txt   : regular grammar, produces all strings in form 1*(01)*0*
sample-CFG1.txt : context-free grammar, produces all strings in form 0^n 1^n
sample-CFG2.txt : context-free grammar, produces all strings in form 0^i 1^j 2^k, i=k
sample-UG.txt   : unrestricted grammar, produces all strings in {0,1}* in form ww

Sample acceptors are provided, as:
sample-DFA.txt  : deterministic finite automaton, accepting all strings ending with 00
sample-eNFA.txt : epsilon-transitions nondeterministic finite automaton, accepting all strings that begin and/or end with 01
sample-PDA.txt  : pushdown automaton, accepts all strings in form 0^n 1^n
sample-TM.txt   : Turing machine, accepts all strings in form 0^n 1^n 2^n

For grammars and acceptors that fit the forms demonstrated in the sample files, testing scripts are provided, as:
finiteAutomata.php      : test DFA, NFA, eNFA
pushdownAutomata.php    : test PDA
turingMachine.php       : test TM
regularGrammar.php      : test RG
contextFreeGrammar.php  : test CFG
unrestrictedGrammar.php : test UG

For testing, run the script with an input file provided as a command-line argument.

For example:
	"php contextFreeGrammar.php sample-CFG2.txt"
	This execution will show all strings produced by the grammar up to some length limit (default 10)

	"php turingMachine.php sample-TM.txt"
	This execution will show all strings accepted by the Turing machine up to some length limit

You can also specify an input string, to determine only if that string is generated or accepted. For example:
	"php finiteAutomata.php sample-DFA.txt 11100" - indicates string is accepted
	"php finiteAutomata.php sample-DFA.txt 10101" - indicates string is rejected
	"php unrestrictedGrammar.php sample-UG.txt 001001" - indicates string is generated

If there is an error in the format of your definition, the script may detect that (or may not).

I'm willing to improve these as you provide feedback.