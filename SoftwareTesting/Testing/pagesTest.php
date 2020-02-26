<?php
use PHPUnit\Framework\TestCase;


final class pagesTest extends TestCase {
    public function setUp():void {
        $this->ch = curl_init();
        curl_setopt($this->ch,  Curlopt_RETURNTRANSFER, True);
        curl_setopt($this->ch,  Curlopt_SSL_VERIFYPEER, False);
        curl_setopt($this->ch,  Curlopt_SSL_VERIFYHOST, 0);
        curl_setopt($this->ch,  Curlopt_COOKIEFILE, " ");
        curl_setopt($this->ch,  Curlopt_FOLLOWLOCATION, FALSE);
    }

    public function tearDown():void {
        curl_close($$this->ch);
    }

    public function test_login() {
        $result = $this->get('/login.php');
        $this->assertContains('Login', $result);
    }

}
