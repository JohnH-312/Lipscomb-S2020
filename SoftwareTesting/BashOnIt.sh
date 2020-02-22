#!/bin/bash

#view standings
curl 'http://localhost:8000/view_standings.php' -H 'Connection: keep-alive' -H 'Upgrade-Insecure-Requests: 1' 
-H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.88 Safari/537.36' 
-H 'Sec-Fetch-User: ?1' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' 
-H 'Sec-Fetch-Site: same-origin' -H 'Sec-Fetch-Mode: navigate' -H 'Referer: http://localhost:8000/' -H 'Accept-Encoding: gzip, deflate, br' 
-H 'Accept-Language: en-US,en;q=0.9' -H 'Cookie: PHPSESSID=drrtdqh9vp76rrjsk2fmgnacf4' --compressed | grep \'refresh\'

#again but not signed in
curl 'http://localhost:8000/view_standings.php' -H 'Connection: keep-alive' -H 'Upgrade-Insecure-Requests: 1' 
-H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.88 Safari/537.36' 
-H 'Sec-Fetch-User: ?1' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' 
-H 'Sec-Fetch-Site: same-origin' -H 'Sec-Fetch-Mode: navigate' -H 'Referer: http://localhost:8000/' -H 'Accept-Encoding: gzip, deflate, br' 
-H 'Accept-Language: en-US,en;q=0.9'  --compressed | grep \'refresh\'

#View problem
curl 'http://localhost:8000/view_file.php?file=12345.html' -H 'Connection: keep-alive' -H 'Upgrade-Insecure-Requests: 1' 
-H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.88 Safari/537.36' 
-H 'Sec-Fetch-User: ?1' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' 
-H 'Sec-Fetch-Site: same-origin' -H 'Sec-Fetch-Mode: navigate' -H 'Referer: http://localhost:8000/view_standings.php' -H 'Accept-Encoding: gzip, deflate, br' 
-H 'Accept-Language: en-US,en;q=0.9' -H 'Cookie: PHPSESSID=drrtdqh9vp76rrjsk2fmgnacf4' --compressed | grep \'refresh\'

#again but not signed in
curl 'http://localhost:8000/view_file.php?file=12345.html' -H 'Connection: keep-alive' -H 'Upgrade-Insecure-Requests: 1' 
-H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.88 Safari/537.36' 
-H 'Sec-Fetch-User: ?1' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' 
-H 'Sec-Fetch-Site: same-origin' -H 'Sec-Fetch-Mode: navigate' -H 'Referer: http://localhost:8000/view_standings.php' -H 'Accept-Encoding: gzip, deflate, br' 
-H 'Accept-Language: en-US,en;q=0.9'  --compressed | grep \'refresh\'

#Main Sample COntest
curl 'http://localhost:8000/' -H 'Connection: keep-alive' -H 'Upgrade-Insecure-Requests: 1' -H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.88 Safari/537.36' 
-H 'Sec-Fetch-User: ?1' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' 
-H 'Sec-Fetch-Site: same-origin' -H 'Sec-Fetch-Mode: navigate' -H 'Referer: http://localhost:8000/' -H 'Accept-Encoding: gzip, deflate, br' 
-H 'Accept-Language: en-US,en;q=0.9' -H 'Cookie: PHPSESSID=drrtdqh9vp76rrjsk2fmgnacf4' --compressed | grep \'refresh\'

# again but not signed in
curl 'http://localhost:8000/' -H 'Connection: keep-alive' -H 'Upgrade-Insecure-Requests: 1' -H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.88 Safari/537.36' 
-H 'Sec-Fetch-User: ?1' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' 
-H 'Sec-Fetch-Site: same-origin' -H 'Sec-Fetch-Mode: navigate' -H 'Referer: http://localhost:8000/' -H 'Accept-Encoding: gzip, deflate, br' 
-H 'Accept-Language: en-US,en;q=0.9' --compressed | grep \'refresh\'

#view attemots
curl 'http://localhost:8000/view_attempts.php' -H 'Connection: keep-alive' -H 'Upgrade-Insecure-Requests: 1' 
-H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.88 Safari/537.36' -H 'Sec-Fetch-User: ?1' 
-H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' 
-H 'Sec-Fetch-Site: same-origin' -H 'Sec-Fetch-Mode: navigate' -H 'Referer: http://localhost:8000/' -H 'Accept-Encoding: gzip, deflate, br' 
-H 'Accept-Language: en-US,en;q=0.9' -H 'Cookie: PHPSESSID=drrtdqh9vp76rrjsk2fmgnacf4' --compressed | grep \'refresh\'

#again not signed in
curl 'http://localhost:8000/view_attempts.php' -H 'Connection: keep-alive' -H 'Upgrade-Insecure-Requests: 1' 
-H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.88 Safari/537.36' -H 'Sec-Fetch-User: ?1' 
-H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' 
-H 'Sec-Fetch-Site: same-origin' -H 'Sec-Fetch-Mode: navigate' -H 'Referer: http://localhost:8000/' -H 'Accept-Encoding: gzip, deflate, br' 
-H 'Accept-Language: en-US,en;q=0.9' -H 'Cookie: PHPSESSID=drrtdqh9vp76rrjsk2fmgnacf4' --compressed | grep \'refresh\'

#cookies as admin
curl 'http://localhost:8000/submit_attempt.php?id=1' -H 'Connection: keep-alive' -H 'Upgrade-Insecure-Requests: 1' 
-H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.88 Safari/537.36' -H 'Sec-Fetch-User: ?1' 
-H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' -H 'Sec-Fetch-Site: same-origin' 
-H 'Sec-Fetch-Mode: navigate' -H 'Referer: http://localhost:8000/view_problems.php' -H 'Accept-Encoding: gzip, deflate, br' -H 'Accept-Language: en-US,en;q=0.9' 
-H 'Cookie: PHPSESSID=drrtdqh9vp76rrjsk2fmgnacf4' --compressed | grep \'refresh\'

# no cookies
curl 'http://localhost:8000/submit_attempt.php?id=1' -H 'Connection: keep-alive' -H 'Upgrade-Insecure-Requests: 1' 
-H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.88 Safari/537.36' -H 'Sec-Fetch-User: ?1' 
-H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' -H 'Sec-Fetch-Site: same-origin' 
-H 'Sec-Fetch-Mode: navigate' -H 'Referer: http://localhost:8000/view_problems.php' -H 'Accept-Encoding: gzip, deflate, br' -H 'Accept-Language: en-US,en;q=0.9' 
 --compressed | grep \'refresh\'