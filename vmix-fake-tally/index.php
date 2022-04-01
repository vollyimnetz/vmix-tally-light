<?php 
include_once __DIR__.'/state.php';

$html = '';
foreach($fakeState as $key=>$state) {
	$html.= '<a href="/tallyupdate/?key='.$key.'" class="tallyLink">'.$state['name'].'</a>'."\n";
}
?>
<!doctype html>
<html>
  <head>
    <title>vMix Tally Lights</title>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1" />
  </head>
  <body>
    <h2>This is a fake tally server.</h2>
    <pre><?php echo $html; ?></pre>
  </body>
</html>