<?php
include_once __DIR__.'/../helper.php';


if(empty($_REQUEST['key']) || ( !empty($_REQUEST['key']) && empty(Channels[ $_REQUEST['key'] ]) ) ) {
	echo 'noting found';
	die();
}

$stateColor = getChannelColor($_REQUEST['key']);
$oldColor = $stateColor;
if(!empty($_REQUEST['state'])) $oldColor = $_REQUEST['state'];

$durationInSeconds = 10;//how long should the tally system wait for state changes
$timeoutInSeconds = .5;//how often will the system check for state changes

$targetCount = 1/$timeoutInSeconds * $durationInSeconds;
$count = 0;
while($stateColor === $oldColor && $count < $targetCount) {
	usleep($timeoutInSeconds * 1000000);
	$count++;
	$stateColor = getChannelColor($_REQUEST['key']);
}
echo 'tallyChange("'.$stateColor.'");';
die();