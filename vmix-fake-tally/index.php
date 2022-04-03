<?php 
include_once __DIR__.'/helper.php';


?>
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>vMix Tally Lights</title>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1" />
    <link href="<?php BASE_URL ?>/assets/bootstrap.min.css" rel="stylesheet">
  </head>
  <body>
    <div class="container mt-3">
      <a class="btn btn-primary btn-sm" href="<?php echo BASE_URL ?>controll">Kontrolle</a>
      <h2>This is a fake vmix tally server.</h2>
      <?php foreach(Channels as $key=>$name) : ?>
        <div>
          <a href="<?php echo BASE_URL ?>tallyupdate/?key=<?php echo $key ?>" class="tallyLink"><?php echo $name ?></a>
        </div>
      <?php endforeach; ?>
    </div>
  </body>
</html>