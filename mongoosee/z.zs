#!../../bin/zhscript2/gtksh --。
定义提示、内容以下代码
	显示“# ‘内容’”换行。
上代码。
定义运行、命令以下代码
	提示‘命令’。
	赋予错以执行‘命令’。
	提示‘错’。
上代码。
定义命令行解析以下代码
	调用‘命令行解析’、‘参数栈’。
上代码。

加载lib/clpars4。
调用‘命令行加回调’、
	g、下代码
		加载lib/mongoosee。
		赋予出、错以调用‘抓网页’、baidu.com。
		显示‘错’换行‘出’换行。
		结束。
	上代码、0、、
	s、下代码
		加载lib/mongoosee。
		赋予错以调用‘网页服务’、4001、.、1。
		显示‘错’换行。
		结束。
	上代码、0、、
	s2、、0、下代码
		加载lib/mongoosee。
		赋予错、服务以调用‘网页服务’、4001、.、0。
		显示‘错’换行。
		如果‘错’那么退出。
		加载lib/timer4。
		调用‘新建定时器’、、10、下代码
			调用‘转动网页服务’、
		上代码“‘服务’、1000”。
		调用‘启动定时’。
		（调用‘停止网页服务’、‘服务’。）
	上代码、
	c|c2、“生成 Release/libmongoosee.so”、0、下代码
		运行先分支‘参数0’先
			c：下原样
d=Release
d2=$d
上原样。
			下原样
d=/tmp/zs2/mongoosee
d2=/tmp/zhscript2/lib
上原样。
		了了下原样
mkdir -p $d $d2
g++ -std=c++1y -DMG_INTERNAL= -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$d/main.d"     -MT"$d/main.o"     -o "$d/main.o"     "main.cpp"
gcc -std=c11   -DMG_INTERNAL= -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$d/mongoose.d" -MT"$d/mongoose.o" -o "$d/mongoose.o" "mongoose.c"
g++ -shared -o "$d2/mongoosee.so"  "$d/main.o" "$d/mongoose.o"   
上原样。
		结束。
	上代码、
	#、、h、下代码
		命令行解析-h。
	上代码。
命令行解析‘参数栈’。
