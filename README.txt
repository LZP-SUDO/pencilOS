👾欢迎使用pencilUIos👾
这个系统是基于liunx内核制作的开源图形化操作系统
这个系统适用于PC，树莓派等硬件设备
如果您是一个小白
请阅读以下文档

pencilUIos开发文档

一.了解系统
这个系统是基于liunx内核制作的，结构如下
linux/
├── boot/      #启动文件
├── arch/       # 体系结构相关代码
├── block/     # 块设备层
├── crypto/    # 加密算法
├── drivers/   # 设备驱动程序
├── fs/        # 文件系统
├── include/   # 头文件
├── init/      # 初始化代码
├── ipc/       # 进程间通信
├── kernel/    # 核心子系统
├── lib/       # 库函数
├── mm/        # 内存管理
├── net/       # 网络协议栈
├── scripts/   # 构建脚本
├── security/  # 安全模块
├── sound/     # 音频子系统
└── tools/     # 开发工具
二.了解命令
因为pencilUIos是基于liunx制作的，所以命令和liunx相同
在启动器在找到终端就可以运行命令
*注：需要打开开发者模式
shell教程（基于菜鸟教程制作）
Shell 是一个用 C 语言编写的程序，它是用户使用 Linux 的桥梁。Shell 既是一种命令语言，又是一种程序设计语言。

Shell 是指一种应用程序，这个应用程序提供了一个界面，用户通过这个界面访问操作系统内核的服务。

Ken Thompson 的 sh 是第一种 Unix Shell，Windows Explorer 是一个典型的图形界面 Shell。
Shell 编程跟 JavaScript、php 编程一样，只要有一个能编写代码的文本编辑器和一个能解释执行的脚本解释器就可以了。

Linux 的 Shell 种类众多，常见的有：

Bourne Shell（/usr/bin/sh或/bin/sh）
Bourne Again Shell（/bin/bash）
C Shell（/usr/bin/csh）
K Shell（/usr/bin/ksh）
Shell for Root（/sbin/sh）
……
第一个shell脚本
打开文本编辑器(可以使用 vi/vim 命令来创建文件)，新建一个文件 test.sh，扩展名为 sh（sh代表shell），
扩展名并不影响脚本执行，见名知意就好，如果你用 php 写 shell 脚本，扩展名就用 php 好了。

输入一些代码，第一行一般是这样：
#!/bin/bash
echo "Hello World !"

#! 是一个约定的标记，它告诉系统这个脚本需要什么解释器来执行，即使用哪一种 Shell。

echo 命令用于向窗口输出文本。
运行 Shell 脚本有两种方法：
1、作为可执行程序

将上面的代码保存为 test.sh，并 cd 到相应目录：
chmod +x ./test.sh  #使脚本具有执行权限
./test.sh  #执行脚本
注意，一定要写成 ./test.sh，而不是 test.sh，运行其它二进制的程序也一样，直接写 test.sh，linux 系统会
去 PATH 里寻找有没有叫 test.sh 的，而只有 /bin, /sbin, /usr/bin，/usr/sbin 等在 PATH 里，你的当前
目录通常不在 PATH 里，所以写成 test.sh 是会找不到命令的，要用 ./test.sh 告诉系统说，就在当前目录找。

2、作为解释器参数

这种运行方式是，直接运行解释器，其参数就是 shell 脚本的文件名，如：
/bin/sh test.sh
/bin/php test.php

Shell 变量
在 Shell 编程中，变量是用于存储数据值的名称。

定义变量时，变量名不加美元符号（$，PHP语言中变量需要），如：
your_name="runoob"
注意，变量名和等号之间不能有空格，这可能和你熟悉的所有编程语言都不一样。同时，变量名的命名须遵循如下规则：

只包含字母、数字和下划线： 变量名可以包含字母（大小写敏感）、数字和下划线 _，不能包含其他特殊字符。
不能以数字开头： 变量名不能以数字开头，但可以包含数字。
避免使用 Shell 关键字： 不要使用Shell的关键字（例如 if、then、else、fi、for、while 等）作为变量名，以免引起混淆。
使用大写字母表示常量： 习惯上，常量的变量名通常使用大写字母，例如 PI=3.14。
避免使用特殊符号： 尽量避免在变量名中使用特殊符号，因为它们可能与 Shell 的语法产生冲突。
避免使用空格： 变量名中不应该包含空格，因为空格通常用于分隔命令和参数。
有效的 Shell 变量名示例如下：
RUNOOB="www.runoob.com"
LD_LIBRARY_PATH="/bin/"
_var="123"
var2="abc"

无效的变量命名：
# 避免使用if作为变量名
if="some_value"
# 避免使用 $ 等特殊符号
variable_with_$=42
?var=123
user*name=runoob
# 避免空格
variable with space="value"

等号两侧避免使用空格：
# 正确的赋值
variable_name=value

# 有可能会导致错误
variable_name = value

除了显式地直接赋值，还可以用语句给变量赋值，如：
for file in `ls /etc`
或
for file in $(ls /etc)
以上语句将 /etc 下目录的文件名循环出来。

使用变量
使用一个定义过的变量，只要在变量名前面加美元符号即可，如：
your_name="qinjx"
echo $your_name
echo ${your_name}
变量名外面的花括号是可选的，加不加都行，加花括号是为了帮助解释器识别变量的边界，比如下面这种情况：
for skill in Ada Coffe Action Java; do
    echo "I am good at ${skill}Script"
done
如果不给skill变量加花括号，写成echo "I am good at $skillScript"，解释器就会把$skillScript当成一个变量（其值为空），代码执行结果就不是我们期望的样子了。

推荐给所有变量加上花括号，这是个好的编程习惯。

已定义的变量，可以被重新定义，如：
your_name="tom"
echo $your_name
your_name="alibaba"
echo $your_name
这样写是合法的，但注意，第二次赋值的时候不能写$your_name="alibaba"，使用变量的时候才加美元符（$）。

只读变量
使用 readonly 命令可以将变量定义为只读变量，只读变量的值不能被改变。

下面的例子尝试更改只读变量，结果报错：
#!/bin/bash

myUrl="https://www.google.com"
readonly myUrl
myUrl="https://www.runoob.com"
运行脚本，结果如下：

/bin/sh: NAME: This variable is read only.
删除变量
使用 unset 命令可以删除变量。语法：

unset variable_name
变量被删除后不能再次使用。unset 命令不能删除只读变量。
实例：
#!/bin/sh

myUrl="https://www.runoob.com"
unset myUrl
echo $myUrl
以上实例执行将没有任何输出。
变量类型
Shell 支持不同类型的变量，其中一些主要的类型包括：

字符串变量： 在 Shell中，变量通常被视为字符串。

你可以使用单引号 ' 或双引号 " 来定义字符串，例如：

my_string='Hello, World!'

或者

my_string="Hello, World!"
整数变量： 在一些Shell中，你可以使用 declare 或 typeset 命令来声明整数变量。

这样的变量只包含整数值，例如：

declare -i my_integer=42
这样的声明告诉 Shell 将 my_integer 视为整数，如果尝试将非整数值赋给它，Shell会尝试将其转换为整数。

数组变量： Shell 也支持数组，允许你在一个变量中存储多个值。

数组可以是整数索引数组或关联数组，以下是一个简单的整数索引数组的例子：

my_array=(1 2 3 4 5)
或者关联数组：

declare -A associative_array
associative_array["name"]="John"
associative_array["age"]=30
环境变量： 这些是由操作系统或用户设置的特殊变量，用于配置 Shell 的行为和影响其执行环境。

例如，PATH 变量包含了操作系统搜索可执行文件的路径：

echo $PATH
特殊变量： 有一些特殊变量在 Shell 中具有特殊含义，例如 $0 表示脚本的名称，$1, $2, 等表示脚本的参数。

$#表示传递给脚本的参数数量，$? 表示上一个命令的退出状态等。

Shell 字符串
字符串是shell编程中最常用最有用的数据类型（除了数字和字符串，也没啥其它类型好用了），字符串可以用单引号，也可以用双引号，也可以不用引号。

单引号
str='this is a string'
单引号字符串的限制：

单引号里的任何字符都会原样输出，单引号字符串中的变量是无效的；
单引号字符串中不能出现单独一个的单引号（对单引号使用转义符后也不行），但可成对出现，作为字符串拼接使用。
双引号
实例
your_name="runoob"
str="Hello, I know you are \"$your_name\"! \n"
echo -e $str
输出结果为：

Hello, I know you are "runoob"! 
双引号的优点：

双引号里可以有变量
双引号里可以出现转义字符
拼接字符串
实例
your_name="runoob"
# 使用双引号拼接
greeting="hello, "$your_name" !"
greeting_1="hello, ${your_name} !"
echo $greeting  $greeting_1

# 使用单引号拼接
greeting_2='hello, '$your_name' !'
greeting_3='hello, ${your_name} !'
echo $greeting_2  $greeting_3
输出结果为：

hello, runoob ! hello, runoob !
hello, runoob ! hello, ${your_name} !
获取字符串长度
实例
string="abcd"
echo ${#string}   # 输出 4
变量为字符串时，${#string} 等价于 ${#string[0]}:

实例
string="abcd"
echo ${#string[0]}   # 输出 4
提取子字符串
以下实例从字符串第 2 个字符开始截取 4 个字符：

实例
string="runoob is a great site"
echo ${string:1:4} # 输出 unoo
注意：第一个字符的索引值为 0。

查找子字符串
查找字符 i 或 o 的位置(哪个字母先出现就计算哪个)：

实例
string="runoob is a great site"
echo `expr index "$string" io`  # 输出 4
注意： 以上脚本中 ` 是反引号，而不是单引号 '，不要看错了哦。

Shell 数组
bash支持一维数组（不支持多维数组），并且没有限定数组的大小。

类似于 C 语言，数组元素的下标由 0 开始编号。获取数组中的元素要利用下标，下标可以是整数或算术表达式，其值应大于或等于 0。

定义数组
在 Shell 中，用括号来表示数组，数组元素用"空格"符号分割开。定义数组的一般形式为：

数组名=(值1 值2 ... 值n)
例如：

array_name=(value0 value1 value2 value3)
或者

array_name=(
value0
value1
value2
value3
)
还可以单独定义数组的各个分量：

array_name[0]=value0
array_name[1]=value1
array_name[n]=valuen
可以不使用连续的下标，而且下标的范围没有限制。

读取数组
读取数组元素值的一般格式是：

${数组名[下标]}
例如：

valuen=${array_name[n]}
使用 @ 符号可以获取数组中的所有元素，例如：

echo ${array_name[@]}
获取数组的长度
获取数组长度的方法与获取字符串长度的方法相同，例如：

实例
# 取得数组元素的个数
length=${#array_name[@]}
# 或者
length=${#array_name[*]}
# 取得数组单个元素的长度
length=${#array_name[n]}
Shell 注释
以 # 开头的行就是注释，会被解释器忽略。

通过每一行加一个 # 号设置多行注释，像这样：

实例
#--------------------------------------------
# 这是一个注释
# author：菜鸟教程
# site：www.runoob.com
# slogan：学的不仅是技术，更是梦想！
#--------------------------------------------
##### 用户配置区 开始 #####
#
#
# 这里可以添加脚本描述信息
#
#
##### 用户配置区 结束  #####
如果在开发过程中，遇到大段的代码需要临时注释起来，过一会儿又取消注释，怎么办呢？

每一行加个#符号太费力了，可以把这一段要注释的代码用一对花括号括起来，定义成一个函数，没有地方调用这个函数，这块代码就不会执行，达到了和注释一样的效果。

多行注释
使用 Here 文档

多行注释还可以使用以下格式：

:<<EOF
注释内容...
注释内容...
注释内容...
EOF
以上例子中，: 是一个空命令，用于执行后面的 Here 文档，<<'EOF' 表示开启 Here 文档，COMMENT 是 Here 文档的标识符，在这两个标识符之间的内容都会被视为注释，不会被执行。
EOF 也可以使用其他符号:

实例
: <<'COMMENT'
这是注释的部分。
可以有多行内容。
COMMENT

:<<'
注释内容...
注释内容...
注释内容...
'

:<<!
注释内容...
注释内容...
注释内容...
!
直接使用 : 号

我们也可以使用了冒号 : 命令，并用单引号 ' 将多行内容括起来。由于冒号是一个空命令，这些内容不会被执行。

格式为：: + 空格 + 单引号。

实例
: '
这是注释的部分。
可以有多行内容。
'
