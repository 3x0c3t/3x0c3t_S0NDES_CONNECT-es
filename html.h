#ifndef HTML_H
#define HTML_H


const char htmlPage[] PROGMEM = R"rawliteral(

<!DOCTYPE html>

<html>

<head>

<meta charset="utf-8">

<meta name="viewport" content="width=device-width,initial-scale=1">

<title>FRIGO</title>

<style>

%CSS%

</style>

</head>


<body>

<h1>FRIGO_20260803</h1>

<div id="content">
Connexion...
</div>


<script>

%JS%

</script>


</body>

</html>

)rawliteral";


#endif
