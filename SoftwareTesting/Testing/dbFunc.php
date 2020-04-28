<?php

/* To use the function in other files, use

if (!function_exists("dbQuery")) {
	include "dbFunc.php";
}

at the top of your test files.
*/

$db = new SQLite3('contest.db'); // The parameter for the SQLite3 constructor is the relative path to the database file.

function dbQuery($q) {
	global $db;
	$stmt = $db->prepare($q);
	if (!$stmt) {
		print("Invalid query");
		return;
	}
	
	$result = $stmt->execute();
	if (!$result) {
		print("Invalid query");
		return;
	}
	
	return $result;
}

?>