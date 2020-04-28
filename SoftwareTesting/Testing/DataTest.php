<?php declare(strict_types=1);
use PHPUnit\Framework\TestCase;
include '_base.php';
if (!function_exists("dbQuery")) {
	include "dbFunc.php";
}
final class DataTest extends _base {
    public function test_insert() {
        $this->login($user, $pass);
        $result = $this->get($pURL);
        $this->assertStringContainsString($asserto, $result);
    }
}