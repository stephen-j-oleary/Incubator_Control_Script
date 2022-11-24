
const char htmlPage[] PROGMEM = R"=(
  <!DOCTYPE HTML>
  <html>
    <head>
      <title>Incubator</title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    </head>
    <body class="container">
      <div class="row">
        <header id="main-header" class="col">
          <h1 class="w-100 text-center">Incubator</h1>
        </header>
      </div>
      <div class="row row-cols-1 row-cols-md-2 row-cols-lg-3">
        <div id="expected-temperature" class="col card rounded" onclick="">
          <div class="card-body">
            <h2 class="title">Expected Temperature</h2>
            <form class="d-flex justify-content-between flex-wrap-none value" action="/">
              <input id="EXPECTED_INTERNAL_TEMPERATURE" name="EXPECTED_INTERNAL_TEMPERATURE" type="text" class="value" value="{{EXPECTED_INTERNAL_TEMPERATURE}}" />
              <p> &#8451</p>
              <input type="submit" class="button" value="Set"/>
            </form>
          </div>
        </div>
        <div id="indicator-light" class="col card rounded" onclick="window.location.assign('/indicator-light/toggle')">
          <div class="card-body">
            <h2 class="card-title">D1 Mini Built-in Led</h2>
            <p class="card-text">{{INDICATOR_LIGHT}}</p>
          </div>
        </div>
        <div id="internal-temperature" class="col card rounded" onclick="">
          <div class="card-body">
            <h2 class="title">Internal Temperature</h2>
            <p class="value">{{INTERNAL_TEMPERATURE}} &#8451</p>
          </div>
        </div>
        <div id="internal-humidity" class="col card rounded" onclick="">
          <div class="card-body">
            <h2 class="title">Internal Humidity</h2>
            <p class="value">{{INTERNAL_HUMIDITY}} %</p>
          </div>
        </div>
        <div id="heat-tape" class="col card rounded" onclick="window.location.assign('/heat-tape/toggle')">
          <div class="card-body">
            <h2 class="title">Heat Tape</h2>
            <p class="value">{{HEAT_TAPE}}</p>
          </div>
        </div>
      </div>
      <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
      <script src="https://code.jquery.com/jquery-3.5.1.min.js"></script>
    </body>
    <style>
      .card { cursor: pointer; }
    </style>
  </html>
)=";
