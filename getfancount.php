<?php

//find the Fancount on the internet. Copy the html source around the number and paste it. Replace the number with (.*)

$content = file_get_contents('https://wherever-you-find-your-fancount.com/without-the-api');

preg_match('#<somehtmltags>(.*)</somehtmltags>#', $content, $match);
$count = $match[1];
echo "$count";
?>
