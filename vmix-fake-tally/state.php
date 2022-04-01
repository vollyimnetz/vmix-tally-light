<?php
$stateTypes = [
	'live' => '#ff0000',
	'preview' => '#deac01',
	'misc' => '#1a3c75',
];

$fakeState = [
	'bf3928a3-cc06-4f79-b0b2-47639d9a405f' => [ 'color' => $stateTypes['live'], 'name' => 'CAM1 links 20x' ],
	'0e1c08d9-e872-4a78-ac99-2d35b2b0ada5' => [ 'color' => $stateTypes['misc'], 'name' => 'CAM2 rechts 30x' ],
	'80a05fcf-066b-43cf-a4ad-fd183a5b39ed' => [ 'color' => $stateTypes['misc'], 'name' => 'Overlay (O)' ],
	'fca608b5-1e62-4822-9a1b-c916a9eab746' => [ 'color' => $stateTypes['misc'], 'name' => 'Beamer-PC (P)' ],
	'f9dd3663-a0ec-407a-9705-cedb8ee84e64' => [ 'color' => $stateTypes['misc'], 'name' => 'Beamer-PC gedimmt(F)' ],
];


$fakeState['0e1c08d9-e872-4a78-ac99-2d35b2b0ada5']['color'] = 
	#$stateTypes['live'];
	$stateTypes['preview'];
	#$stateTypes['misc'];

