<?php declare(strict_types=1);
use PHPUnit\Framework\TestCase;
include '_base.php';


final class pagesTest extends _base {

    /**
     * @test
     * @dataProvider myTestProvider
     */
    public function test_pages($pURL, $asserto, $user, $pass) {
        $this->login($user, $pass);
        $result = $this->get($pURL);
        $this->assertStringContainsString($asserto, $result);
    }
    
    public function myTestProvider()
    {
        return [
            //submit attempt
            ['/index.php', 'Welcome', "", ""],
            ['/index.php', 'Welcome', "admin", "secret"],
            ['/index.php', 'Welcome', "notJudge", "aaa"],
            //Login
            ["/login.php", "Login", "", ""],
            ["/login.php", "Login", "admin", "secret"],
            ["/login.php", "Login", "notJudge", "aaa"],
            //View
            ["/view_problems.php", "login.php", "", ""],
            ["/view_problems.php", "Judge Menu", "admin", "secret"],
            ["/view_problems.php", "Problems", "notJudge", "aaa"],
            //EDIT
            //EditProblems
            ["/edit_problems.php", "refresh", "", ""],
            ["/edit_problems.php", "Edit Problem", "admin", "secret"],
            ["/edit_problems.php", "refresh", "notJudge", "aaa"],
            //EDIT Notes
            ["/edit_notes.php", "refresh", "", ""],
            ["/edit_notes.php", "Message", "admin", "secret"],
            ["/edit_notes.php", "refresh", "notJudge", "aaa"],
            //EDIT Contests
            ["/edit_contests.php", "refresh", "", ""],
            ["/edit_contests.php", "Freeze", "admin", "secret"],
            ["/edit_contests.php", "refresh", "notJudge", "aaa"],
            //EDIT Contestants
            ["/edit_contestants.php", "refresh", "", ""],
            ["/edit_contestants.php", "Last login", "admin", "secret"],
            ["/edit_contestants.php", "refresh", "notJudge", "aaa"],
            //Rules
            ['/view_file.php?file=rules.html', 'Contest Rules', "", ""],
            ['/view_file.php?file=rules.html', 'Contest Rules', "admin", "secret"],
            ['/view_file.php?file=rules.html', 'Contest Rules', "notJudge", "aaa"],
            //View Standings
            ['/view_standings.php', 'Standings', "", ""],
            ['/view_standings.php', 'Standings', "admin", "secret"],
            ['/view_standings.php', 'Standings', "notJudge", "aaa"],
            //View Prints
            ['/view_prints.php', 'refresh', "", ""],
            ['/view_prints.php', 'Queue', "admin", "secret"],
            ['/view_prints.php', 'refresh', "notJudge", "aaa"],
            //View attempts
            ['/view_attempts.php', 'refresh', "", ""],
            ['/view_attempts.php', 'Minutes', "admin", "secret"],
            ['/view_attempts.php', 'refresh', "notJudge", "aaa"],
            //test attempt
            ['/test_attempt.php', 'refresh', "", ""],
            ['/test_attempt.php', 'Judge Submission', "admin", "secret"],
            ['/test_attempt.php', 'refresh', "notJudge", "aaa"],
            //submit attempt
            ['/submit_attempt.php', 'refresh', "", ""],
            ['/submit_attempt.php', 'refresh', "admin", "secret"],
            ['/submit_attempt.php', 'Submit Solution', "notJudge", "aaa"],
        ];
    }

}
