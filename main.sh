echo 请更改./Py-crawler/list.cpp第5行引号内的内容、style.css里import指向的css文件、update.php第四行网址指向你的wikidot网站，然后在此按下换行。
read anykey
cd Py-crawler
g++ all.cpp -o all
g++ crawler.cpp -o crawler
g++ get-all-page.cpp -o get-all-page
g++ list.cpp -o list
g++ main.cpp -o main
g++ other-page.cpp -o other-page
echo 安装成功。