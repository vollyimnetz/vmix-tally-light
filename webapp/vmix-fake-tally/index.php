<?php 
include_once __DIR__.'/state.php';

$html = '';
foreach($fakeState as $key=>$state) {
	$html.= '<a href="./tally/?key='.$key.'" class="tallyLink">'.$state['name'].'</a>'."\n";
}
?>
<!doctype html>
<html>
  <head>
    <title>vMix Tally Lights</title>
    <link href="/stylesheet.css" rel="stylesheet" type="text/css" />
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1" />
  </head>
  <body>
    <script src="/jquery.js" type="text/javascript"></script>
<div class="menu">
<a href="/"><img src="/buttons/?type=shortcuts" class="menuButton" alt="Shortcuts" /></a>
<a href="/controller"><img src="/buttons/?type=controller" class="menuButton" alt="Controller" /></a>
<a href="/tally"><img src="/buttons/?type=tallyselected" class="menuButton" alt="Tally" /></a>
<a href="/titles"><img src="/buttons/?type=titles" class="menuButton" alt="Titles" /></a>
</div>
<?php echo $html; ?>

  </body>
</html>