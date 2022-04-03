<?php
define('VMIX_STATE_FILENAME',__DIR__.'/state.json');
define('BASE_URL','/');
const StateTypes = [
	'live' => '#ff0000',
	'preview' => '#deac01',
	'misc' => '#1a3c75',
];

const Channels = [
	'bf3928a3-cc06-4f79-b0b2-47639d9a405f' => 'CAM1 links 20x',
	'0e1c08d9-e872-4a78-ac99-2d35b2b0ada5' => 'CAM2 rechts 30x',
	'80a05fcf-066b-43cf-a4ad-fd183a5b39ed' => 'Overlay (O)',
	'fca608b5-1e62-4822-9a1b-c916a9eab746' => 'Beamer-PC (P)',
	'f9dd3663-a0ec-407a-9705-cedb8ee84e64' => 'Beamer-PC gedimmt(F)',
];

function resetStates() {
	setState('bf3928a3-cc06-4f79-b0b2-47639d9a405f','live');
	setState('0e1c08d9-e872-4a78-ac99-2d35b2b0ada5','preview');
}

function getStates() {
	$state = loadFile();

	foreach(Channels as $key => $channel) {
		$tmp = [
			'id' => $key,
			'name' => $channel,
			'state' => 'misc',
		];
		if(is_array($state)) {
			$existingState = array_search($key, $state, true);
			if(!empty($existingState)) $tmp['state'] = $existingState;
		}
		$tmp['color'] = getColorByState( $tmp['state'] );
		$result[] = $tmp;
	}
	return $result;
}


function setState($id, $state) {
	if(empty(Channels[$id])) return;//validation
	$result = loadFile();
	if($state === 'live') {
		if(!empty($result['live']) && $result['live']===$id) {
			//do nothing
		} else {
			if(!empty($result['live'])) {
				$result['preview'] = $result['live'];
			}
			$result['live'] = $id;
		}
	}
	if($state === 'preview' && !empty($result['live'])) {
		if(!empty($result['live']) && $result['live']===$id && !empty($result['preview'])) {
			$result['live'] = $result['preview'];
		}
		$result['preview'] = $id;
	}
	if(!empty($result)) file_put_contents(VMIX_STATE_FILENAME, json_encode($result));
}

function getColorByState($state) {
	return (!empty(StateTypes[$state])) ? StateTypes[$state] : '#ffffff';
}

function getChannelColor($id) {
	$currentStates = getStates();
	if(is_array($currentStates)) foreach($currentStates as $s) {
		if($s['id']===$id) return StateTypes[ $s['state'] ];
	}
	return 'ERROR';
}

function loadFile() {
	$content = @file_get_contents(VMIX_STATE_FILENAME);
	if(empty($content)) return null;
	return json_decode($content, true);
}

function deleteFile() {
	@unlink(VMIX_STATE_FILENAME);
}