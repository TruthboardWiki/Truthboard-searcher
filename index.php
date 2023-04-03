<html><head>
<link rel="stylesheet" href="/style.css">
<link rel="stylesheet" href="https://api.helloos.eu.org/css/grid.css">
<title>站内搜索引擎</title>
<script>
function httpPost(URL, PARAMS) {
 var temp = document.createElement("form");
 temp.action = URL;
 temp.method = "post";
 temp.style.display = "none";
 for (var x in PARAMS) {
  var opt = document.createElement("textarea");
  opt.name = x;
  opt.value = PARAMS[x];
  temp.appendChild(opt);
 }
 document.body.appendChild(temp);
 temp.submit();
 return temp;
}
function search(values){
var url = "/search.php";
var params = {
    "search":values
}
httpPost(url,params);
}
function get_val(){
  return document.getElementById('search').value;
}
</script>
</head>
<body>
<div id="box">
<div class="center">
<h3>Wikidot站内搜索</h3>
<p>
<input name="search" id="search" type="text">
<button id="searchbtn" onclick="search(get_val());">搜索</button>
</p>
</div></div>
</body></html>