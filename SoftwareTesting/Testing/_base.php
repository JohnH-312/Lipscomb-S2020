<?php
use PHPUnit\Framework\TestCase;

abstract class _base extends TestCase {
    public function setUpBefore():void {
        //see query_or_die
        //OR see php - sqlite3 functions and class
    }

    public function setUp():void {
        $this->ch = curl_init();
        curl_setopt($this->ch,  CURLOPT_RETURNTRANSFER, True);
        curl_setopt($this->ch,  CURLOPT_SSL_VERIFYPEER, False);
        curl_setopt($this->ch,  CURLOPT_SSL_VERIFYHOST, 0);
        curl_setopt($this->ch,  CURLOPT_COOKIEFILE, " ");
        curl_setopt($this->ch,  CURLOPT_FOLLOWLOCATION, FALSE);
    }

    public function get(string $url, array $headers=[],int $code=200):string {
        $this->assertEquals('/',$url[0]);
	    curl_setopt($this->ch, CURLOPT_URL,"http://localhost:8000$url");
        curl_setopt($this->ch, CURLOPT_HEADER, False);
        curl_setopt($this->ch,CURLOPT_FAILONERROR,TRUE);
        curl_setopt($this->ch, CURLOPT_HTTPHEADER, $headers);
        $result = curl_exec($this->ch);
        $this->assertTrue($result!==FALSE,'https request failed');
        $result_code = curl_getinfo($this->ch,CURLINFO_HTTP_CODE);
        $this->assertEquals($code, $result_code, "get failed: $url $result_code $result");
        return $result;
    }

    public function login(String $username, String $password):void {
        //Go to login page properly
        $result = $this->get('/login.php');

        //Login as Admin
        if ($username != "" and $password != "") {
            curl_setopt($this->ch,CURLOPT_POST,true);
            curl_setopt($this->ch,CURLOPT_URL,"http://localhost:8000/login.php");
            curl_setopt($this->ch,CURLOPT_POSTFIELDS,['user'=>$username,'password'=>$password,'login'=>true]);
            $result = curl_exec($this->ch);
            $this->assertTrue($result!==FALSE);
            $result_code = curl_getinfo($this->ch,CURLINFO_HTTP_CODE);
            $this->assertEquals(200,$result_code,$result);
            $this->assertStringContainsString("refresh",$result);
        }


/*
        curl_setopt($this->ch,CURLOPT_POST,false);
        curl_setopt($this->ch,CURLOPT_URL,"http://localhost:8000/view_problems.php");
        $result = curl_exec($this->ch);
        $this->assertTrue($result!==FALSE);
        $result_code = curl_getinfo($this->ch,CURLINFO_HTTP_CODE);
        $this->assertEquals(200,$result_code);
        $this->assertContains("Judge Menu",$result);*/
    }

    public function setCookie (string $mycookie):void                                          {
        curl_setopt($this->ch,  CURLOPT_COOKIE, $mycookie);
    }

    public function tearDown():void {
        curl_close($this->ch);
    }

    
}