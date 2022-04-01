<?php
include_once __DIR__.'/../state.php';

if( empty($_REQUEST['key']) || ( !empty($_REQUEST['key']) && empty($fakeState[ $_REQUEST['key'] ]) ) ) {
	echo 'noting found';
	die();
}

$current = $fakeState[ $_REQUEST['key'] ];
if(!empty($_REQUEST['state']) && $_REQUEST['state'] === $current['color']) {
	sleep(5);//sleep for 3 seconds
}
echo 'tallyChange("'.$current['color'].'");';
die();