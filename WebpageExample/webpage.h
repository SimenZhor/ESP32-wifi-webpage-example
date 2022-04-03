R"(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  </head>
  <body>
    <div class="container-fluid">
      <div class="col-xs-12"  style="height: 100vh">
        <div class="row" style="height: 33.33%; padding-top: 1em; padding-bottom:1em">
          <div class="col-xs-8" ></div>
          <div class="col-xs-4" style="text-align: center; height: 100%">
            <button id="UP" type="button" class="btn btn-default" style="height: 100%; width: 100%" onpointerdown='makeAjaxCall("up")' onpointerup='makeAjaxCall("buttonrelease")'>Up</button>
          </div>
        </div>
        <div class="row" style="height: 33.33%; padding-bottom:1em">
          <div class="col-xs-4" style="height: 100%; text-align: center">
            <button id="LEFT" type="button" class="btn btn-default" style="height: 100%; width: 100%" onpointerdown='makeAjaxCall("left")' onpointerup='makeAjaxCall("buttonrelease")'>Left</button>
          </div>
          <div class="col-xs-4" style="height: 100%; text-align: center">
            <button id="RIGHT" type="button" class="btn btn-default" style="height: 100%; width: 100%" onpointerdown='makeAjaxCall("right")' onpointerup='makeAjaxCall("buttonrelease")'>Right</button>
          </div>
          <div class="col-xs-4" ></div>
        </div>
        <div class="row" style="height: 33.33%; padding-bottom:1em">
          <div class="col-xs-8" ></div>
          <div class="col-xs-4" style="height: 100%; text-align: center">
            <button id="DOWN" type="button" class="btn btn-default" style="height: 100%; width: 100%" onpointerdown='makeAjaxCall("down")' onpointerup='makeAjaxCall("buttonrelease")'>Down</button>
          </div>
        </div>
      </div>
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    <script> function makeAjaxCall(url){$.ajax({"url": url})}</script>
    <!--<script>
       document.addEventListener('keydown', function(event) {
          if(event.keyCode == 37) {
              //Left Arrow
              makeAjaxCall("left");            
          }
          else if(event.keyCode == 39) {
              //Right Arrow
              makeAjaxCall("right");   
          } else if(event.keyCode == 38) {
              //Up Arrow
              makeAjaxCall("up");   
          } else if(event.keyCode == 40) {
              //Down Arrow
              makeAjaxCall("down");   
          }
      });

      document.addEventListener('keyup', function(event) {
          if(event.keyCode == 37 ||event.keyCode == 39 ) {
              //Left or Right Arrow
              makeAjaxCall("buttonrelease");            
          }
          else if(event.keyCode == 38 ||event.keyCode == 40 ) {
              //Up or Down Arrow
              makeAjaxCall("buttonrelease");            
          }
      });
    </script>-->
  </body>
</html>

)"