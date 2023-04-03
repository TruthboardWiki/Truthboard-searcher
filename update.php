<?php
echo "Waiting...<br/>";
$pages=$_SERVER['QUERY_STRING'];
exec("cd ./Py-crawler ; ./main https://truthboard.wikidot.com/ {$pages}");//调用C++以更新数据库。
echo "Done.";
?>