<?php
include_once __DIR__.'/../helper.php';

if(!empty($_GET['reset'])) {
  deleteFile();
  header('location: http://'.$_SERVER['SERVER_NAME'].BASE_URL.'/controll');
  exit();
}
if(!empty($_GET['id']) && !empty($_GET['setState'])) {
  setState($_GET['id'], $_GET['setState']);
}
$state = getStates();
?>
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>vMix Tally Lights</title>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1" />
    <link href="<?php BASE_URL ?>/assets/bootstrap.min.css" rel="stylesheet">
    <style>
      .preview { display:inline-block; margin-right:10px; border:1px solid rgba(0,0,0,0.1); width: 25px; height:25px; vertical-align: middle; }
      .previewLabel { display:inline-block; vertical-align: middle; }
    </style>
  </head>
  <body>
    <div class="container mt-3">
      <a class="btn btn-primary btn-sm" href="<?php echo BASE_URL ?>">main</a>
      <h2>fake vmix tally controll room</h2>
      
      <table class="table">
        <thead>
          <tr>
            <th>Name</th>
            <th>aktueller Zustand</th>
            <th>Aktion</th>
            <th>Öffnen</th>
          </tr>
        </thead>
        <tbody>
        <?php foreach($state as $channel) : ?>
          <tr>
            <td>
              <strong><?php echo $channel['name'] ?></strong><br />
              <small><?php echo $channel['id'] ?></small>
            </td>
            <td>
              <?php
              if($channel['color']) echo '<div class="preview" style="background: '.$channel['color'].';"></div>';
              switch($channel['state']) {
                case 'live': echo 'LIVE'; break;
                case 'preview': echo 'PREVIEW'; break;
                default: echo '-'; break;
              }
              ?>
            </td>
            <td>
              <a class="btn btn-secondary btn-sm" href="?id=<?php echo $channel['id'] ?>&amp;setState=live">auf LIVE schalten</a>
              <a class="btn btn-secondary btn-sm" href="?id=<?php echo $channel['id'] ?>&amp;setState=preview">auf PREVIEW schalten</a>
            </td>
            <td>
              <a class="btn btn-success btn-sm" target="_blank" href="<?php echo BASE_URL ?>tallyupdate/?key=<?php echo $channel['id'] ?>">öffnen</a>
              <a class="btn btn-warning btn-sm" target="_blank" href="<?php echo BASE_URL ?>tallyupdate/?key=<?php echo $channel['id'] ?>&amp;state=<?php echo $channel['color'] ?>">öffnen mit Farbewert</a>
            </td>
          </tr>
        <?php endforeach; ?>
        </tbody>
      </table>
      <div>
        <a class="btn btn-secondary btn-sm" href="?reset=1">Reset</a>
      </div>
      <?php
      #echo '<pre>'.print_r(loadFile(),true).'</pre>';
      ?>
    </div>
  </body>
</html>